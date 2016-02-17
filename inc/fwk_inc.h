/****************************************************************************/
/** @file fwk_inc.h
 *  @brief Act as the including file to access the framework.
 *  @ingroup TMP  
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
#ifndef __FWK_INC_H__  /* __FWK_INC_H__ */
#define __FWK_INC_H__

/*****************************************************************************
 * Conditional Compiler Directive if have
 ****************************************************************************/


/*****************************************************************************
 * Include List
 ****************************************************************************/
#include "fwk_basc.h"
#include "fwk_msg.h"
#include "fwk_task.h"
#include "fwk_tmr.h"
#include "fwk_log.h"


/*****************************************************************************
 * Constant & Macro Definition
 ****************************************************************************/



//#define display_backtrace()
#define _Assert_Exit_                           \
{                                               \
    fprintf(stderr, "\nExiting execution\n");   \
    display_backtrace();                        \
    fflush(stdout);                             \
    fflush(stderr);                             \
    exit(EXIT_FAILURE);                         \
}

#define _Assert_(cOND, aCTION, fORMAT, aRGS...)             \
do {                                                        \
    if (!(cOND)) {                                          \
        fprintf(stderr, "\nAssertion ("#cOND") failed!\n"   \
                "In %s() %s:%d\n" fORMAT,                   \
                __FUNCTION__, __FILE__, __LINE__, ##aRGS);  \
        aCTION;                                             \
    }                                                       \
} while(0)

#define AssertFatal(cOND, fORMAT, aRGS...)          _Assert_(cOND, _Assert_Exit_, fORMAT, ##aRGS)

#define AssertError(cOND, aCTION, fORMAT, aRGS...)  _Assert_(cOND, aCTION, fORMAT, ##aRGS)

/*****************************************************************************
 * Type & Structure Declaration
 ****************************************************************************/


/*****************************************************************************
 * External Variable Declaration
 ****************************************************************************/
 

/*****************************************************************************
 * Function Prototype Declaration
 ****************************************************************************/



#endif  /* __FWK_INC_H__ */
