/****************************************************************************/
/** @file fwk_tmr.cpp
 *  @brief Provide timer utility functions.
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


/*****************************************************************************
 * Function Prototype Declaration
 ****************************************************************************/


/*F**************************************************************************/
/** @brief Start a timer.
 *  @param[in] ev Timeout event to original module. 
 *  @param[in] id The module which starts the timer.
 *  @param[in] instance_id ID for a specific instance if any.
 *  @param[in] ms Timeout duration in ms.
 *  @param[in] bPeriodic Periodic timer or not.         
 *  @return The pointer of timer control block.
 ****************************************************************************/ 
int 
FwkTmr::start(tEvent ev, tModId id, tAny instance_id, U32 ms, BOOL bPeriodic)
{
    int ret;
    struct sigevent sev;
    struct itimerspec its;
    
    AssertFatal(this->st==0, "Try to restart a running timer.\n");
    if (this->st != TMR_ST_OFF)
    {
        //$ timer already started, force to stop ?
        ret = timer_delete(this->tmr);
    }
    
    this->event = ev;
    this->module = id;
    this->bPeriodic = bPeriodic;
    this->instance = instance_id;

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = TMR_SIG;
    sev.sigev_value.sival_ptr = (void*)this;
    ret = timer_create(CLOCK_REALTIME, &sev, &this->tmr);
    AssertFatal(ret==0, "timer_create error (%d).\n", ret);

    its.it_value.tv_sec = ms/1000;
    its.it_value.tv_nsec = (ms%1000)*1000;
    if (bPeriodic)
    {
        its.it_interval.tv_sec = its.it_value.tv_sec;
        its.it_interval.tv_nsec = its.it_value.tv_nsec;
    }
    else
    {
        its.it_interval.tv_sec = 0;
        its.it_interval.tv_nsec = 0;    
    }
    
    ret = timer_settime(this->tmr, 0, &its, NULL);
    AssertFatal(ret==0, "timer_settime error (%d).\n", ret);
    
    this->st = TMR_ST_ON;    
    return ret;
}

/*F**************************************************************************/
/** @brief Stop a running timer
 *  @param[in] pTCB The pointer to the timer to be stoped.       
 *  @return Return the timer_delete() result.
 ****************************************************************************/ 
int
FwkTmr::stop(void)
{
    int ret;
    
    AssertFatal(this->st!=TMR_ST_OFF, "Try to stop a non-running timer.\n");
    if (this->st != TMR_ST_OFF)
    {
        ret = timer_delete(this->tmr);
    }    

    this->st = TMR_ST_OFF;
    return (ret); 
}

/*F**************************************************************************/
/** @brief Handle the timeout event from signal handler.
 *  @param[in] ptr Pointer of timer control block     
 ****************************************************************************/ 
void
FwkTmr::timeout(void)
{
    tMsg *pMsg;

    //printf("timer expire: event = %d, module= %d\n", pTCB->event, pTCB->module);
    
    pMsg = (tMsg *)mem_alloc(sizeof(tMsg));
    AssertFatal(pMsg != NULL, "Memory alloc for timeout message is NULL!\n");
    
    pMsg->event    = this->event;
    pMsg->dstMod   = this->module;
    pMsg->s16Size  = 0;
    pMsg->instance = this->instance;
    
    //$ send timeoute event to module
    FwkMsg::send(pMsg);
    
    if (!this->bPeriodic)
    {
        this->st = TMR_ST_OFF;//$ not periodic, so set timer state OFF
        //mem_free(pTCB);//only free non-periodic timer
    }
}

/*F**************************************************************************/
/** @brief Handle the timeout event from signal handler.
 *  @param[in] ptr Pointer of timer control block     
 ****************************************************************************/ 
void
FwkTmr::expire(void *ptr)
{
    FwkTmr *pTCB = (FwkTmr*)ptr;
    
    pTCB->timeout();
}
