/****************************************************************************/
/** @file fwk_msg.h
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
#ifndef __FWK_MSG_H__  /* __FWK_MSG_H__ */
#define __FWK_MSG_H__

/*****************************************************************************
 * Conditional Compiler Directive if have
 ****************************************************************************/


/*****************************************************************************
 * Include List
 ****************************************************************************/
#include "fwk_basc.h"

/*****************************************************************************
 * Constant & Macro Definition
 ****************************************************************************/



/**
 * @brief Definition of module IDs.
 */
typedef enum 
{
    MOD_SCTP,       /**< SCTP module */
    MOD_S1,         /**< S1 module */
    MOD_NAS,        /**< NAS module */
    MOD_S11,        /**< S11 module */
    MOD_S6a,        /**< S6a module */
    MOD_UDP,        /**< UDP module */
    MOD_MAX         /**< Number of modules */
} teMod;




/*****************************************************************************
 * Type & Structure Declaration
 ****************************************************************************/

typedef U16 tEvent;//!< Use 16 bits for Event type
typedef U8  tModId;//!< Use 8 bits for Module ID



/**
 * @brief Message format between modules (tasks) communication.
 */
typedef struct
{
    tEvent  event;      /**< Message ID */
    tModId  dstMod;     /**< Destination module ID. */
    S16     s16Size;    /**< Size of the parameter, -1: no pointer, others: pointer*/
    tAny    instance;   
    //$ individual parameters (depend on primitive type)
    //U8      info[0];
#if 0
    union
    {
        tAny tAnyInfo;  /**< The only value of parameter. */
        void *ptr;      /**< Pointer to parameter of the primitive. */
    } para;
#endif        
} tMsg;


/**
 * @brief Framework message utility functions.
 */
class FwkMsg
{
public:
   static int send(tMsg *pMsg);
   static int recv(tModId rcvMod, tMsg **ppMsg); 
};


/*****************************************************************************
 * External Variable Declaration
 ****************************************************************************/
 

/*****************************************************************************
 * Function Prototype Declaration
 ****************************************************************************/




#endif  /* __FWK_MSG_H__ */
