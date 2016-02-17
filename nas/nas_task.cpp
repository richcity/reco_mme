/****************************************************************************/
/** @file nas_task.cpp
 *  @brief Create task for NAS module.
 *  @ingroup NAS  
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
#include "nas_pblc.h"
#include "nas_priv.h"

/*****************************************************************************
 * Local defines & local structures
 ****************************************************************************/


/*****************************************************************************
 * Local global variables
 ****************************************************************************/
/// Global NAS control instance.
NasFsm *pNasFsm;

/*****************************************************************************
 * Function Prototype Declaration
 ****************************************************************************/


/*F**************************************************************************/
/** @brief This is the main function for NAS module.   
 *  @return Void
 *     
 ****************************************************************************/
void*
NasCtx::task_main(void *args_p)
{
    int ret;
    tMsg *pMsg;
    int tmr_stop = 0;
    
    fwk_task_ready(MOD_NAS);

    pNasFsm = new(NasFsm);

    /*{
        int i;//$ timer test
        for (i=0;i<199;i++)
            nas_tmr_start(14, 22, 1100, FALSE);  
    }*/

    NAS_LOG_ERR("log error hahaha\n");
    NAS_LOG_INFO("thread test: NAS\n");
    sleep(3);
    
    nas_tmr_start(pNasFsm->tmr1, 11, 22, 1000, TRUE);
    nas_tmr_start(pNasFsm->tmr2, 12, 22, 1000, TRUE);
    nas_tmr_start(pNasFsm->tmr3, 13, 22, 5000, TRUE);
    
    while (1)
    {
        ret = FwkMsg::recv(MOD_NAS, &pMsg);
        AssertFatal(ret == 0, "fwk_msg_recv error: ret = %d\n", ret);
        
        NAS_LOG_DEBUG("NAS rx --> event: %d, sz: %d\n", pMsg->event, pMsg->s16Size);
        
        if (pMsg->event == 13 && tmr_stop == 0)
        {
            nas_tmr_stop(pNasFsm->tmr1);
            tmr_stop = 1;
        }
        
        mem_free(pMsg);
/*        sleep(2);
        
        pMsg = (tMsg *)mem_alloc(sizeof(tMsg));
        AssertFatal(pMsg != NULL, "Memory alloc for timeout message is NULL!\n");
        
        pMsg->event    = 2;
        pMsg->dstMod   = MOD_S1;
        pMsg->s16Size  = 0;
        pMsg->instance = 99;
        FwkMsg::send(pMsg);*/        
    }    

  return NULL;

}


/*F**************************************************************************/
/** @brief This function is used to initialize NAS module.   
 *  @return Void
 *   
 *  Function flow:
 *  - Initialize variables
 *  - Create thread to run nas_task_main()    
 ****************************************************************************/
void
NasCtx::init(void)
{    
    fwk_log_set(MOD_NAS, LOG_DEBUG);
    
    fwk_task_init(MOD_NAS, task_main);
}

