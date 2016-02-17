/****************************************************************************/
/** @file fwk_log.cpp
 *  @brief Provide logging utility functions.
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

/*****************************************************************************
 * Include List
 ****************************************************************************/
#include "fwk_inc.h"
#include <sys/time.h>     //$ for gettimeofday
#include <stdarg.h>

/*****************************************************************************
 * Local defines & local structures
 ****************************************************************************/

#define mGetLogLev(id)       (stFwkCtx.aTasks[id]->logCfg.u8DbgLv)

/*****************************************************************************
 * Local global variables
 ****************************************************************************/
#define FORMAT_STRING_LEN 255
static char fmt_string[FORMAT_STRING_LEN];
static char result_string[1024];

/*****************************************************************************
 * Function Prototype Declaration
 ****************************************************************************/



/*F**************************************************************************/
/** @brief Get current time into a string.  
 *  @return Current time as a string.
 ****************************************************************************/
static char* 
fwk_log_get_time(void) 
{
    struct timeval now;
    static char str[30];
    char* ptr;
    if (gettimeofday(&now, NULL) < 0) 
    {
        perror("gettimeofday");
        return NULL;
    }
    ptr = ctime(&now.tv_sec);
    strcpy(str, ptr+11);
    snprintf(str+8, sizeof(str)-8, ".%06ld", now.tv_usec);
    return str;
}


/*F**************************************************************************/
/** @brief Formatting the output string.
 *  @param[in] type Type string for logging. 
 *  @param[in] fmt Logging string format.
 *  @param[in] ap Logging string parameter list.  
 *  @return Formatted result string.
 ****************************************************************************/
char*
fwk_log_do_logging(const char *type, const char *fmt, va_list ap)
{
    char *time = fwk_log_get_time();

    vsnprintf(fmt_string, FORMAT_STRING_LEN, fmt, ap);
    
    sprintf(result_string, "[%s][%s] %s", time, type, fmt_string);
    return result_string;
}



/*F**************************************************************************/
/** @brief Logging error message.
 *  @param[in] funcname Source code file name for logging. 
 *  @param[in] mod_id The logging module.
 *  @param[in] line Number of line of the code.
 *  @param[in] fmt Logging string format.         
 *  @return Void.
 ****************************************************************************/ 
void 
fwk_log_err(const char* funcname, int mod_id, int line, const char *fmt, ...)
{
    char *ptr_str;
    va_list	ap;
    
    if (mGetLogLev(mod_id) < LOG_ERR)
    {
        return;//$ not print debug msg
    }    
    
    va_start(ap, fmt);
    ptr_str = fwk_log_do_logging("ERROR", fmt, ap);
    va_end(ap);
    std::cout << ptr_str; 
}

/*F**************************************************************************/
/** @brief Logging warning message.
 *  @param[in] filename Source code file name for logging. 
 *  @param[in] mod_id The logging module.
 *  @param[in] line Number of line of the code.
 *  @param[in] fmt Logging string format.         
 *  @return Void.
 ****************************************************************************/ 
void 
fwk_log_warn(const char* filename, int mod_id, int line, const char *fmt, ...)
{
    char *ptr_str;
    va_list	ap;
    
    if (mGetLogLev(mod_id) < LOG_WARN)
    {
        return;//$ not print warning msg
    }
        
    va_start(ap, fmt);
    ptr_str = fwk_log_do_logging("WARN", fmt, ap);
    va_end(ap);
    std::cout << ptr_str; 
}

/*F**************************************************************************/
/** @brief Logging information message.
 *  @param[in] filename Source code file name for logging. 
 *  @param[in] mod_id The logging module.
 *  @param[in] line Number of line of the code.
 *  @param[in] fmt Logging string format.         
 *  @return Void.
 ****************************************************************************/ 
void 
fwk_log_info(const char* filename, int mod_id, int line, const char *fmt, ...)
{
    char *ptr_str;
    va_list	ap;
    
    if (mGetLogLev(mod_id) < LOG_INFO)
    {
        return;//$ not print info msg
    }
    
    va_start(ap, fmt);
    ptr_str = fwk_log_do_logging("INFO", fmt, ap);
    va_end(ap);
    std::cout << ptr_str; 
}

/*F**************************************************************************/
/** @brief Logging debug message.
 *  @param[in] filename Source code file name for logging. 
 *  @param[in] mod_id The logging module.
 *  @param[in] line Number of line of the code.
 *  @param[in] fmt Logging string format.         
 *  @return Void.
 ****************************************************************************/ 
void 
fwk_log_debug(const char* filename, int mod_id, int line, const char *fmt, ...)
{
    char *ptr_str;
    va_list	ap;
    
    if (mGetLogLev(mod_id) < LOG_DEBUG)
    {
        return;//$ not print debug msg
    }
    
    va_start(ap, fmt);
    ptr_str = fwk_log_do_logging("DEBUG", fmt, ap);
    va_end(ap);
    std::cout << ptr_str;    
}
