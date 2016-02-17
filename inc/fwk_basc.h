/****************************************************************************/
/** @file fwk_basc.h
 *  @brief Provide basic definitions.
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
#ifndef __FWK_BASC_H__  /* __FWK_BASC_H__ */
#define __FWK_BASC_H__

/*****************************************************************************
 * Conditional Compiler Directive if have
 ****************************************************************************/


/*****************************************************************************
 * Include List
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*****************************************************************************
 * Constant & Macro Definition
 ****************************************************************************/

//$ boolean: true or false
#define TRUE            1
#define FALSE           0

//$ result: success or failure
#define SUCCESS         0
#define FAIL           (-1)

//$ memory utility
#define mem_alloc   malloc
#define mem_free    free

/*****************************************************************************
 * Type & Structure Declaration
 ****************************************************************************/
//$ assume 64 bits OS
typedef unsigned int U32;
typedef int S32;
typedef unsigned short U16;
typedef short S16;
typedef unsigned char U8;
typedef char S8;
typedef unsigned long U64;
typedef long S64;
typedef U64 tAny;
typedef float           FLOAT;
typedef unsigned char BOOL;
 

/**
 * @brief Signal related utilities.
 */
class FwkSig
{
public:
    static void init(void);
    static int  handle(int *end);
};

/*****************************************************************************
 * External Variable Declaration
 ****************************************************************************/
 

/*****************************************************************************
 * Function Prototype Declaration
 ****************************************************************************/


#endif  /* __FWK_BASC_H__ */
