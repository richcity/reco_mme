/****************************************************************************/
/** @file fwk_tmr.h
 *  @brief Provide timer related definition.
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
#ifndef __FWK_TMR_H__  /* __FWK_TMR_H__ */
#define __FWK_TMR_H__

/*****************************************************************************
 * Conditional Compiler Directive if have
 ****************************************************************************/


/*****************************************************************************
 * Include List
 ****************************************************************************/
#include "fwk_basc.h"
#include <time.h>   
#include <signal.h>  



/*****************************************************************************
 * Constant & Macro Definition
 ****************************************************************************/

#define TMR_SIG SIGUSR1

#define TMR_ST_OFF 0
#define TMR_ST_ON 1

/*****************************************************************************
 * Type & Structure Declaration
 ****************************************************************************/


/**
 * @brief Framework timer utility functions.
 */
class FwkTmr
{
public:
   FwkTmr(){ st = TMR_ST_OFF; };
   int  start(tEvent, tModId, tAny, U32, BOOL);
   int  stop(void);
   void timeout(void);
   static void expire(void *ptr);
private:
    tEvent  event;      /**< Timeout event. */
    tModId  module;     /**< Module for the timer. */
    BOOL    bPeriodic;  /**< Periodic or not. */
    tAny    instance;   /**< Additional instance id if any. */
    timer_t    tmr;     /**< Actual timer data structure. */    
    U8      st;         /**< Timer state. */
};

/*****************************************************************************
 * External Variable Declaration
 ****************************************************************************/
 

/*****************************************************************************
 * Function Prototype Declaration
 ****************************************************************************/


#endif  /* __FWK_TMR_H__ */
