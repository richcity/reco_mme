/****************************************************************************/
/** @file nas_priv.h
 *  @brief NAS private data structure and function.
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
#ifndef __NAS_PRIV_H__  /* __NAS_PRIV_H__ */
#define __NAS_PRIV_H__

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

#define nas_tmr_start(tmr, ev, inst, ms, p) tmr.start(ev, MOD_NAS, inst, ms, p)
#define nas_tmr_stop(tmr) tmr.stop()

#define NAS_LOG_ERR(args...)   LOG_ERROR(MOD_NAS, ##args)
#define NAS_LOG_WARN(args...)  LOG_WARN(MOD_NAS, ##args)
#define NAS_LOG_INFO(args...)  LOG_INFO(MOD_NAS, ##args)
#define NAS_LOG_DEBUG(args...) LOG_DEBUG(MOD_NAS, ##args)


/*****************************************************************************
 * Type & Structure Declaration
 ****************************************************************************/

/**
 * @brief NAS state machine.
 */
class NasFsm
{
public:
    NasFsm(void){u8State = 0;};
    FwkTmr tmr1;
    FwkTmr tmr2;
    FwkTmr tmr3;
private:        
    U8  u8State;    
};





/*****************************************************************************
 * External Variable Declaration
 ****************************************************************************/
extern NasFsm *pNasFsm; 

/*****************************************************************************
 * Function Prototype Declaration
 ****************************************************************************/





#endif  /* __NAS_PRIV_H__ */
