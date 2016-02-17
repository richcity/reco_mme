/****************************************************************************/
/** @file fwk_msg.c
 *  @brief Inter task message communication.
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
#include <pthread.h>
#include <signal.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>

#include "fwk_inc.h"


/*****************************************************************************
 * Local defines & local structures
 ****************************************************************************/


//$ for further debug, not used now!
typedef struct
{
    tMsg *pMsg;
    int seq;   //$ sequence number   
} tQueueMsg;

/*****************************************************************************
 * Local global variables
 ****************************************************************************/



/*****************************************************************************
 * Function Prototype Declaration
 ****************************************************************************/


/*F**************************************************************************/
/** @brief Receive a message from other module or a timeout event. 
 *  @param[in] rcvMod Which module to receive message.
 *  @param[in] ppMsg Would return the pointer of received message. 
 *  @return 0: success
 ****************************************************************************/
int
FwkMsg::recv(tModId rcvMod, tMsg **ppMsg)
{
    int epoll_ret = 0;
    int epoll_timeout = -1;//$ -1 causes the epoll_wait to wait indefinitely.
    FwkTask *pTask = stFwkCtx.aTasks[rcvMod];
    
    *ppMsg = NULL;

    do 
    {
        epoll_ret = epoll_wait(pTask->epoll_fd, pTask->events, pTask->nb_events, epoll_timeout);
    } while (epoll_ret < 0 && errno == EINTR);

    if (epoll_ret < 0) 
    {
        AssertFatal(0, "epoll_wait failed for task %d: %s!\n", rcvMod, strerror(errno));
    }

    pTask->epoll_nb_events = epoll_ret;

    {
        tMsg *pMsg = NULL;
        eventfd_t  sem_counter;
        ssize_t    read_ret;
        //$ Read will always return 1 
        read_ret = read(pTask->task_event_fd, &sem_counter, sizeof (sem_counter));
        AssertFatal(read_ret == sizeof(sem_counter), "Read from task message FD (%d) failed (%d/%d)!\n", rcvMod, (int)read_ret, (int)sizeof (sem_counter));
        if (lfds611_queue_dequeue(pTask->msgQ, (void **)&pMsg) == 0) 
        {
            //$ No element in list -> this should not happen 
            AssertFatal(0, "No message in queue for task %d while there are %d events and some for the messages queue!\n", rcvMod, epoll_ret);
        }

        AssertFatal(pMsg != NULL, "Message from message queue is NULL!\n");
        *ppMsg = pMsg;
      
        //$ Mark that the event has been processed 
        pTask->events[0].events &= ~EPOLLIN;            
    }
    return 0;
}

/*F**************************************************************************/
/** @brief Send a message to another module.
 *  @param[in] pMsg The pointer of message to be sent.     
 *  @return 0: success.     
 ****************************************************************************/
int
FwkMsg::send(tMsg *pMsg)
{
    FwkTask *pTask = stFwkCtx.aTasks[pMsg->dstMod]; 
    
    //$ Enqueue message in destination task queue
    lfds611_queue_enqueue(pTask->msgQ, (void*)pMsg);

    {
        //$ Call to write for an event fd must be of 8 bytes 
        ssize_t ret;
        eventfd_t sem_counter = 1;
        ret = write(pTask->task_event_fd, &sem_counter, sizeof (sem_counter));
        AssertFatal(ret==sizeof(sem_counter), "Write to task message FD (%d) failed (%d/%d)\n", pMsg->dstMod, (int)ret, (int)sizeof (sem_counter));
    }
    
    return 0;
}




