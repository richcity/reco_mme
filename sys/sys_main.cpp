/****************************************************************************/
/** @file sys_main.cpp
 *  @brief Main function for Wirelab MME software.
 *  @ingroup SYS  
 *  @author FuCheng Chen (richcity)
 *  $Revision: 1.0 $ 
 *  $Date: 2016/01/26 $
 *   
 *  Create on: 2016/01/26
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
#include "nas_pblc.h"

extern void sys_signal_init(void);
extern int sys_signal_handle(int *end);

/*****************************************************************************
 * Local defines & local structures
 ****************************************************************************/

/*****************************************************************************
 * Local global variables
 ****************************************************************************/


/*F**************************************************************************/
/** @brief RECO MME software main function
 *  @param[in] argc Number of command line parameters. 
 *  @param[in] argv Command line parameters.      
 *  @return Status 0: OK.
 ****************************************************************************/ 
int
main(int argc,char *argv[])
{
    int end;

    

    FwkSig::init();//$ block signals for all threads (before create thread)
    //stFwkCtx.init();
    
    //$ module initialize
    //SctpCtx::init();
    //UdpCtx::init();
    S1Ctx::init();
    NasCtx::init();
    //S6aCtx::init();

    //$ main loop 
    //$ wait for timeout event or other signal
    do
    {
        FwkSig::handle(&end);
    } while (!end);
    
    //$ clean if any
    
    return 0;
}