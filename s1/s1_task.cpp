/****************************************************************************/
/** @file s1_task.c
 *  @brief Template for WIRE 5G Core development.
 *  @ingroup TMP  
 *  @author FuCheng Chen (richcity)
 *  $Revision: 1.0 $ 
 *  $Date: 2016/01/25 $
 *   
 *  Create on: 2016/01/25
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
#include "s1_pblc.h"
#include "s1_priv.h"

/*****************************************************************************
 * Local defines & local structures
 ****************************************************************************/


/*****************************************************************************
 * Local global variables
 ****************************************************************************/
S1Fsm *pS1Fsm;

/*****************************************************************************
 * Function Prototype Declaration
 ****************************************************************************/


/*F**************************************************************************/
/** @brief This function is used to initialize CS module.   
 *  @return Void
 *   
 *  Function flow:
 *  - Initialize log utility for CS module
 *  - Init LOC (cell)
 *  - Init gCsFsm    
 ****************************************************************************/
void*
S1Ctx::task_main(void *args_p)
{
    int ret;
    tMsg *pMsg;
    
    fwk_task_ready(MOD_S1);

    pS1Fsm = new(S1Fsm);

    S1_LOG_INFO("thread test: s1\n");
    sleep(3);
    
    pMsg = (tMsg *)mem_alloc(sizeof(tMsg));
    AssertFatal(pMsg != NULL, "Memory alloc for timeout message is NULL!\n");
        
    pMsg->event    = 1;
    pMsg->dstMod   = MOD_NAS;
    pMsg->s16Size  = 0;
    pMsg->instance = 100;
    FwkMsg::send(pMsg); 
    
    s1_tmr_start(pS1Fsm->tmr1, 21, 22, 1000, TRUE);   
    
    while (1)
    {
        ret = FwkMsg::recv(MOD_S1, &pMsg);
        
        AssertFatal(ret == 0, "fwk_msg_recv error: ret = %d\n", ret);
        S1_LOG_DEBUG("S1 rx --> event type: %d, sz: %d\n", pMsg->event, pMsg->s16Size);
        mem_free(pMsg);
/*
        sleep(2);        
        pMsg = (tMsg *)mem_alloc(sizeof(tMsg));
        AssertFatal(pMsg != NULL, "Memory alloc for timeout message is NULL!\n");
        
        pMsg->event    = 1;
        pMsg->dstMod   = MOD_NAS;
        pMsg->s16Size  = 0;
        pMsg->instance = 100;
        FwkMsg::send(pMsg);            
*/
    }     

  return NULL;

}


/*F**************************************************************************/
/** @brief This function is used to initialize CS module.   
 *  @return Void
 *   
 *  Function flow:
 *  - Initialize log utility for CS module
 *  - Init LOC (cell)
 *  - Init gCsFsm    
 ****************************************************************************/
void
S1Ctx::init(void)
{
    fwk_log_set(MOD_S1, LOG_DEBUG);
    
    fwk_task_init(MOD_S1, task_main);
}

