/****************************************************************************/
/** @file s1_priv.h
 *  @brief S1 private data structure and function.
 *  @ingroup S1  
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
#ifndef __S1_PRIV_H__  /* __S1_PRIV_H__ */
#define __S1_PRIV_H__

/*****************************************************************************
 * Conditional Compiler Directive if have
 ****************************************************************************/


/*****************************************************************************
 * Include List
 ****************************************************************************/
#include "fwk_inc.h"


/*****************************************************************************
 * Constant & Macro Definition
 ****************************************************************************/

#define s1_tmr_start(tmr, ev, inst, ms, p) tmr.start(ev, MOD_S1, inst, ms, p)
#define s1_tmr_stop(tmr) tmr.stop()

#define S1_LOG_ERR(args...)   LOG_ERROR(MOD_S1, ##args)
#define S1_LOG_WARN(args...)  LOG_WARN(MOD_S1, ##args)
#define S1_LOG_INFO(args...)  LOG_INFO(MOD_S1, ##args)
#define S1_LOG_DEBUG(args...) LOG_DEBUG(MOD_S1, ##args)

/*****************************************************************************
 * Type & Structure Declaration
 ****************************************************************************/

/**
 * @brief S1 state machine.
 */
class S1Fsm
{
public:     
    S1Fsm(void){u8State = 0;};
    FwkTmr tmr1;
    FwkTmr tmr2;
    FwkTmr tmr3;    
private:
    U8  u8State;
};


/*****************************************************************************
 * External Variable Declaration
 ****************************************************************************/
extern S1Fsm *pS1Fsm; 

/*****************************************************************************
 * Function Prototype Declaration
 ****************************************************************************/





#endif  /* __S1_PRIV_H__ */
