/**
 * @mainpage RECO Protocol Software MME
 * 
 *
 * \section intro_sec Functional requirements  
 * \subsection ctrl_sw Control software  
 * - Cell initial config / reset
 *   -# User interface
 *   -# Optional: GUI
 * - UDP communication with UE via wired network
 *   -# Sync notification message
 *       - Simulate UE config
 *   -# Beam selection message
 *   -# RLC AM STATUS PDU message (optional)
 * \subsection sys_sw System software
 * - Handle communication interface between MAC and PHY
 *   -# Option 1: UDP socket
 *   -# Option 2: Raw socket
 * - Capture DL data (IP packet) to UE, and enqueue to RLC.
 *   -# Option 1: iptables + netlink netfilter
 *   -# Option 2: libpcap
 *
 * @author FuCheng Chen
 **/


//$ Module definitions

/** 
 *  @defgroup SYS 
 *  @brief System software 
 **/
 
/** 
 *  @defgroup FWK 
 *  @brief Framework software. 
 **/

/** 
 *  @defgroup NAS 
 *  @brief NAS protocol. 
 **/
