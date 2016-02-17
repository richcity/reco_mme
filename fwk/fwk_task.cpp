/****************************************************************************/
/** @file fwk_task.c
 *  @brief Provide task utility for framework.
 *  @ingroup FWK  
 *  @author FuCheng Chen (richcity)
 *  $Revision: 1.0 $ 
 *  $Date: 2016/02/02 $
 *   
 *  Create on: 2016/02/02
 *   
 *----------------------------------------------------------------------------
 *
 * Copyright (C) 2016, All Right Reserved.
 *  
 * NCTU WIRELAB
 *  
 ****************************************************************************/

/*****************************************************************************
 * Include List
 ****************************************************************************/
#include "fwk_inc.h"


/*****************************************************************************
 * Local defines & local structures
 ****************************************************************************/




/*****************************************************************************
 * Local global variables
 ****************************************************************************/
/// global framework instance.
FwkCtx stFwkCtx;


/*****************************************************************************
 * Function Prototype Declaration
 ****************************************************************************/

#include <execinfo.h>
/* Obtain a backtrace and print it to stdout. */
void
display_backtrace(void)
{
    void                                   *array[10];
    size_t                                  size;
    char                                  **strings;
    size_t                                  i;

    size = backtrace (array, 10);
    strings = backtrace_symbols (array, size);
    printf ("Obtained %zd stack frames.\n", size);

    for (i = 0; i < size; i++)
        printf ("%s\n", strings[i]);

    free (strings);
}


/*F**************************************************************************/
/** @brief This function is used to initialize the framework (constructor).    
 *  @return Void. 
 ****************************************************************************/
FwkCtx::FwkCtx(void)
{
    int i;
    
    for (i=0;i<MOD_MAX;i++)
    {
        this->aTasks[i] = new FwkTask(i);
        //this->aTasks[i].task_state = TASK_ST_NULL;
        //this->aTasks[i].mod_id = i;
    }
}

/*F**************************************************************************/
/** @brief This function is used to finish the framework termination.    
 *  @return Void. 
 ****************************************************************************/
FwkCtx::~FwkCtx(void)
{
    int i;
    
    for (i=0;i<MOD_MAX;i++)
    {
        delete(this->aTasks[i]);
        //this->aTasks[i].task_state = TASK_ST_NULL;
        //this->aTasks[i].mod_id = i;
    }
}


/*F**************************************************************************/
/** @brief This function is used to initialize a thread for a module.   
 *  @param[in] id Pre-defined module id.
 *  @param[in] mod_main Main function of the module. 
 *  @return 0: OK. 
 ****************************************************************************/
int
FwkTask::init(void*(*mod_main)(void*))
{
    int ret;
    //tTaskCtx *pTask = &stFwkCtx.aTasks[id];

    this->epoll_fd = epoll_create1 (0);
    if (this->epoll_fd == -1) 
    {
        //$ Always assert on this condition
        AssertFatal(0, "Failed to create new epoll fd: %s!\n", strerror (errno));
    }
    
    this->task_event_fd = eventfd (0, EFD_SEMAPHORE);
    if (this->task_event_fd == -1) 
    {
        //$ Always assert on this condition
        AssertFatal(0, " eventfd failed: %s!\n", strerror (errno));
    }

    this->nb_events = 1;
    this->events = (epoll_event*)calloc(1, sizeof(struct epoll_event));
    this->events->events = EPOLLIN | EPOLLERR;
    this->events->data.fd = this->task_event_fd;   

    //$ Add the event fd to the list of monitored events
    if (epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, this->task_event_fd, this->events) != 0) 
    {
        //$ Always assert on this condition
        AssertFatal(0, " epoll_ctl (EPOLL_CTL_ADD) failed: %s!\n", strerror (errno));
    }
     
    this->queue_size = 200;//$ fixme: change to configurable
    ret = lfds611_queue_new(&this->msgQ, this->queue_size);
    if (ret == 0) 
    {
        //AssertFatal (0, "lfds611_queue_new failed for task %s!\n", fwk_get_task_name(id));
        AssertFatal(0, "lfds611_queue_new failed for task %d!\n", this->mod_id);
    }

    //$ create thread for the module
    AssertFatal(mod_main != NULL, "Start routine is NULL!\n");
    this->task_state = TASK_ST_STARTING;
    //FWK_DEBUG (FWK_DEBUG_INIT, " Creating thread for task %s ...\n", itti_get_task_name (task_id));
    ret = pthread_create(&this->task_thread, NULL, mod_main, NULL);
    AssertFatal(ret >= 0, "Thread creation for module %d failed (%d)!\n", this->mod_id, ret);
    
    //$ Wait till the thread is completely ready
    while (this->task_state != TASK_ST_READY)
        usleep (1000);
    
    return 0;
}

/*F**************************************************************************/
/** @brief This function is used to mark a module has ready.   
 *  @param[in] id Pre-defined module id. 
 *  @return 0: OK. 
 ****************************************************************************/
int
FwkTask::ready(void)
{
    //tTaskCtx *pTask = &stFwkCtx.aTasks[id];
    
    this->task_state = TASK_ST_READY;
    lfds611_queue_use(this->msgQ);
    return 0;    
}




