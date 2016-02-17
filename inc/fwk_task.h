/****************************************************************************/
/** @file fwk_task.h
 *  @brief Task create and control definition.
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
#ifndef __FWK_TASK_H__  /* __FWK_TASK_H__ */
#define __FWK_TASK_H__

/*****************************************************************************
 * Conditional Compiler Directive if have
 ****************************************************************************/


/*****************************************************************************
 * Include List
 ****************************************************************************/

#include <pthread.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>

#include "fwk_basc.h"
#include "fwk_log.h"

//$ use C functions in C++ program.
extern "C" {
#include "liblfds611.h"
}



/*****************************************************************************
 * Constant & Macro Definition
 ****************************************************************************/

#define fwk_task_init(id, init_fp)   (stFwkCtx.aTasks[id]->init(init_fp)) 
#define fwk_task_ready(id) (stFwkCtx.aTasks[id]->ready())

/*****************************************************************************
 * Type & Structure Declaration
 ****************************************************************************/

typedef enum
{
    TASK_ST_NULL = 0,   /**< Null state */
    TASK_ST_STARTING,   /**< Starting state */
    TASK_ST_READY,      /**< Thread create ok */
    TASK_ST_END         /**< Terminated state */
} teTaskSt;


/**
 * @brief Control information (context) for a task.
 */
class FwkTask
{
public:
    int                 mod_id;
    int                 epoll_fd;       /**< . */    
    struct epoll_event *events;         /**< Array of events monitored by the task. */
    int                 epoll_nb_events;/**< . */
    U16                 nb_events;      /**< Number of events to monitor. */
    int                 task_event_fd;  /**< . */
    struct lfds611_queue_state *msgQ;   /**< Message queue for a module. */
    int                 queue_size;     /**< Queue size of msgQ. */    
    volatile teTaskSt   task_state;     /**< State of the thread */
    pthread_t           task_thread;    /**< pthread associated with the thread.*/
    FwkLog              logCfg;
    FwkTask(int mod_id){ this->mod_id = mod_id; this->task_state = TASK_ST_NULL; };
    int init(void*(*mod_main)(void*));
    int ready();
};


/**
 * @brief Context for this framework.
 */
class FwkCtx
{
public:
    FwkCtx(void);
    ~FwkCtx(void);
    FwkTask *aTasks[MOD_MAX-1]; /**< Array of pointer to FwkTask class. */
};


/*****************************************************************************
 * External Variable Declaration
 ****************************************************************************/
extern FwkCtx stFwkCtx; 

/*****************************************************************************
 * Function Prototype Declaration
 ****************************************************************************/

//$ Functions in fwk_task.c
void display_backtrace(void);





#endif  /* __FWK_TASK_H__ */
