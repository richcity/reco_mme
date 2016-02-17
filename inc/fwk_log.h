/****************************************************************************/
/** @file fwk_log.h
 *  @brief Provide logging utilities
 *  @ingroup FWK  
 *  @author FuCheng Chen (richcity)
 *  $Revision: 1.0 $ 
 *  $Date: 2016/02/15 $
 *   
 *  Create on: 2016/02/15
 *   
 *----------------------------------------------------------------------------
 *
 * Copyright (C) 2016, All Right Reserved.
 *  
 * NCTU WIRELAB
 *  
 ****************************************************************************/
#ifndef __FWK_LOG_H__  /* __FWK_LOG_H__ */
#define __FWK_LOG_H__

/*****************************************************************************
 * Conditional Compiler Directive if have
 ****************************************************************************/


/*****************************************************************************
 * Include List
 ****************************************************************************/
#include <iostream>



/*****************************************************************************
 * Constant & Macro Definition
 ****************************************************************************/

#define fwk_log_set(id, lv)  stFwkCtx.aTasks[id]->logCfg.u8DbgLv = lv


/**
 * @brief Definition of logging levels.
 */
typedef enum 
{
    LOG_NULL,       /**< Disable logging */
    LOG_ERR,        /**< Error message */
    LOG_WARN,       /**< Warning message */
    LOG_INFO,       /**< Information message */
    LOG_DEBUG,      /**< Debug message */
} teLogLev;


/*****************************************************************************
 * Type & Structure Declaration
 ****************************************************************************/


/**
 * @brief Framework timer utility functions.
 */
class FwkLog
{
public:
    FwkLog(void) {u8DbgLv = LOG_ERR; }; //$ default to LOG_ERR
    U8 u8DbgLv;

};

/*****************************************************************************
 * External Variable Declaration
 ****************************************************************************/
 

/*****************************************************************************
 * Function Prototype Declaration
 ****************************************************************************/

#define LOG_ERROR(mod_id, args...) fwk_log_err(__FUNCTION__, mod_id, __LINE__, ##args)
#define LOG_WARN(mod_id, args...)  fwk_log_warn(__FUNCTION__, mod_id, __LINE__, ##args)
#define LOG_INFO(mod_id, args...)  fwk_log_info(__FUNCTION__, mod_id, __LINE__, ##args)
#define LOG_DEBUG(mod_id, args...) fwk_log_debug(__FUNCTION__, mod_id, __LINE__, ##args)


void fwk_log_err(const char* filename, int mod_id, int line, const char *fmt, ...);
void fwk_log_warn(const char* filename, int mod_id, int line, const char *fmt, ...);
void fwk_log_info(const char* filename, int mod_id, int line, const char *fmt, ...);
void fwk_log_debug(const char* filename, int mod_id, int line, const char *fmt, ...);


#endif  /* __FWK_LOG_H__ */
