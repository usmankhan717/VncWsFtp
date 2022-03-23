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
-------------------------- END-OF-HEADER -----------------------------

File    : FS_Start.c
Purpose : Start application for file system.

Additional information:
  Preparations:
    Works out-of-the-box with any storage device.

  Expected behavior:
    The application performs the following actions:
    - Formats the storage device if required
    - Determines the available free space
    - Opens a file
    - Writes some data to the opened file
    - Closes the opened file
    - Determines the available free space
    If the storage device is not formatted the file system formats
    the storage device and generates the following message:
    "Signature invalid or no signature. High-level format required."
    This message is generated each time the sample application is started
    when the system memory is used as storage via the RAMDisk driver.
    The reason for this behavior is that the format information is lost
    as the system memory is reinitialized at startup.

  Sample output:
    Start
    Running sample on ""
      Free space: 7674 MBytes
      Write test data to file \File.txt
      Free space: 7674 MBytes
    Finished
*/

/*********************************************************************
*
*       #include Section
*
**********************************************************************
*/
#include <stdio.h>
#include "FS.h"
#include "SEGGER.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/*********************************************************************
*
*       MainTask
*/
#ifdef __cplusplus
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif
void MainTask(void);
#ifdef __cplusplus
}
#endif
void MainTask(void) {
  U32          v;
  FS_FILE    * pFile;
  char         ac[256];
  char         acFileName[32];
  const char * sVolumeName = "";

  FS_X_Log("Start\n");
  //
  // Initialize file system
  //
  FS_Init();
  //
  // Check if low-level format is required
  //
  FS_FormatLLIfRequired(sVolumeName);
  //
  // Check if volume needs to be high level formatted.
  //
  if (FS_IsHLFormatted(sVolumeName) == 0) {
    FS_X_Log("High-level format\n");
    FS_Format(sVolumeName, NULL);
  }
  SEGGER_snprintf(ac, sizeof(ac), "Running sample on \"%s\"\n", sVolumeName);
  FS_X_Log(ac);
  v = FS_GetVolumeFreeSpaceKB(sVolumeName);
  if (v < 0x8000) {
    SEGGER_snprintf(ac, sizeof(ac), "  Free space: %lu KBytes\n", v);
  } else {
    v >>= 10;
    SEGGER_snprintf(ac, sizeof(ac), "  Free space: %lu MBytes\n", v);
  }
  FS_X_Log(ac);
  SEGGER_snprintf(acFileName, sizeof(acFileName), "%s\\File.txt", sVolumeName);
  SEGGER_snprintf(ac, sizeof(ac), "  Write test data to file %s\n", acFileName);
  FS_X_Log(ac);
  pFile = FS_FOpen(acFileName, "w");
  if (pFile) {
    FS_Write(pFile, "Test", 4);
    FS_FClose(pFile);
  } else {
    SEGGER_snprintf(ac, sizeof(ac), "Could not open file: %s to write.\n", acFileName);
    FS_X_Log(ac);
  }
  v = FS_GetVolumeFreeSpaceKB(sVolumeName);
  if (v < 0x8000) {
    SEGGER_snprintf(ac, sizeof(ac), "  Free space: %lu KBytes\n", v);
  } else {
    v >>= 10;
    SEGGER_snprintf(ac, sizeof(ac), "  Free space: %lu MBytes\n", v);
  }
  FS_X_Log(ac);
  FS_Unmount(sVolumeName);
  FS_X_Log("Finished\n");
  while (1) {
    ;
  }
}

/*************************** End of file ****************************/