/****************************************************************************/
/** @file fwk_sig.cpp
 *  @brief Define signal processing functions.
 *  @ingroup FWK  
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


/*****************************************************************************
 * Local defines & local structures
 ****************************************************************************/

/*****************************************************************************
 * Local global variables
 ****************************************************************************/

/// Store the blocked signal set to wait for processing
static sigset_t  set;    

/*F**************************************************************************/
/** @brief Initialize signal setting.      
 *  @return Void.
 ****************************************************************************/ 
void
FwkSig::init(void)
{
    sigemptyset (&set);
    //sigaddset (&set, SIGTIMER);
    sigaddset (&set, SIGUSR1);
    sigaddset (&set, SIGABRT);
    sigaddset (&set, SIGSEGV);
    sigaddset (&set, SIGINT);

    if (sigprocmask (SIG_BLOCK, &set, NULL) < 0) 
    {
        perror ("sigprocmask");
        return ;
    }
}


/*F**************************************************************************/
/** @brief Wait for signal and process.
 *  @param[in] argc Number of command line parameters. 
 *  @param[in] argv Command line parameters.      
 *  @return Status 0: OK.
 ****************************************************************************/ 
int
FwkSig::handle(int *end)
{
    int       ret;
    siginfo_t info; 

    *end = 0;

    //$ Block till a signal is received.
    if ((ret = sigwaitinfo (&set, &info)) == -1) 
    {
        perror ("sigwait");
        return ret;
    }
    //printf("Received signal %d\n", info.si_signo);

    //$ Real-time signals are non constant and are therefore not suitable for 
    //$ use in switch.  (richcity: ??)
    //if (info.si_signo == SIGTIMER) {
    if (info.si_signo == TMR_SIG) 
    {
        FwkTmr::expire(info.si_ptr);
    }
    else
    {
        switch (info.si_signo)
        {
        case SIGSEGV:
        case SIGABRT:
            printf("Receive SIGABORT\n");
            *end = 1;
            break;
        case SIGINT:
            printf("receive ctrl+c, exit\n");
            *end = 1;
            break;
        default:
            printf("Unknown signal : %d\n", info.si_signo);
            break;
        }
    }

    return 0;
}
