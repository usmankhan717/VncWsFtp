/*********************************************************************
*                     SEGGER Microcontroller GmbH                    *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*       (c) 2003 - 2019  SEGGER Microcontroller GmbH                 *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
----------------------------------------------------------------------
File    : USBH_Conf.h
Purpose : Config file. Modify to reflect your configuration
--------  END-OF-HEADER  ---------------------------------------------
*/

#ifndef USBH_CONF_H      // Avoid multiple inclusion

#define USBH_CONF_H

#if defined(__cplusplus) // Make sure we have C-declarations in C++ programs
  extern "C" {
#endif

#ifdef DEBUG
#if DEBUG
  #define USBH_DEBUG   2// Debug level: 1: Support "Panic" checks, 2: Support warn & log
#endif
#endif


// Make sure we have C-declarations in C++ programs
#if defined(__cplusplus)

}

#endif

#endif // Avoid multiple inclusion

/*************************** End of file ****************************/
