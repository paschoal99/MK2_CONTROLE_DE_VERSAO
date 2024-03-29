/**
 * @file e_eeprom_xmc1.h
 * @date 2016-09-23
 *
 * NOTE:
 * This file is generated by DAVE. Any manual modification done to this file will be lost when the code is regenerated.
 *
 * @cond
 ***********************************************************************************************************************
 * E_EEPROM_XMC1 v4.1.10 - Emulates a portion of flash as an EEPROM for data storage.
 *
 * Copyright (c) 2015-2016, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes
 * with Infineon Technologies AG (dave@infineon.com).
 ***********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2015-02-16:
 *     - Initial version<br>
 *
 * 2015-04-24:
 *     - E_EEPROM_XMC1_ReadBlockWithCRC API renamed to E_EEPROM_XMC1_VerifyBlockCrcStatus<br>
 *     - E_EEPROM_XMC1_OPERATION_STATUS_t enumeration parameter names changed and additional status parameter
 *       E_EEPROM_XMC1_OPERATION_STATUS_NO_CRC_WRITTEN added.
 *
 * 2016-07-08:
 *     - Fixed incorrect case for an included header.<br>
 *
 * @endcond
 *
 */

#ifndef E_EEPROM_XMC1_H
#define E_EEPROM_XMC1_H

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/

#include <xmc_flash.h>
#include <DAVE_Common.h>

/* Include APP configuration header file */
#include "e_eeprom_xmc1_conf.h"

#ifdef E_EEPROM_XMC1_CRC_SW_ENABLED
#include "../CRC_SW/crc_sw.h"
#endif

#if (!((XMC_LIB_MAJOR_VERSION == 2U) && \
       (XMC_LIB_MINOR_VERSION >= 0U) && \
       (XMC_LIB_PATCH_VERSION >= 0U)))
#error "E_EEPROM_XMC1 requires XMC Peripheral Library v2.0.0 or higher"
#endif

/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/

/** Physical flash Block size and Page size defined*/
#define E_EEPROM_XMC1_FLASH_BLOCK_SIZE  (16U)
#define E_EEPROM_XMC1_FLASH_PAGE_SIZE   (256U)


/*
 *  These are global variables used only for internal testing purpose.
 *  Application code shall not use these variables by enabling E_EEPROM_XMC1_TEST_HOOK_ENABLE macro definition.
 */
#ifdef E_EEPROM_XMC1_TEST_HOOK_ENABLE
uint32_t e_eeprom_xmc1_test_hook_readblock;
uint32_t e_eeprom_xmc1_test_hook_writeblock;
uint32_t e_eeprom_xmc1_test_hook_writepage;
uint32_t e_eeprom_xmc1_test_hook_erasepage;
uint32_t e_eeprom_xmc1_test_hook_readword;
uint32_t e_eeprom_xmc1_test_hook_getflashstatus;
#endif

/**********************************************************************************************************************
* ENUMS
**********************************************************************************************************************/

/**
 * @ingroup E_EEPROM_XMC1_enumerations
 * @{
 */

/** Defines the error codes for E_EEPROM_XMC1 APP. Use @ref E_EEPROM_XMC1_STATUS_t type for accessing the member.  */
typedef enum E_EEPROM_XMC1_STATUS
{
  E_EEPROM_XMC1_STATUS_SUCCESS        = 0U, /**< Successful completion of APP initialization */
  E_EEPROM_XMC1_STATUS_FAILURE        = 1U, /**< Initialization failed due to internal operational error*/
  E_EEPROM_XMC1_STATUS_UNINITIALIZED  = 2U, /**< APP is in Uninitialized state*/
  E_EEPROM_XMC1_STATUS_IDLE           = 3U, /**< APP is in IDLE state. Only used in E_EEPROM_XMC1_GetStatus() API */
  E_EEPROM_XMC1_STATUS_BUSY           = 4U  /**< APP is in BUSY state. Only used in E_EEPROM_XMC1_GetStatus() API */
} E_EEPROM_XMC1_STATUS_t;

/**
 * Defines current status for E_EEPROM_XMC1 APP. Use @ref E_EEPROM_XMC1_OPERATION_STATUS_t type for accessing the
 *  member.
 */
typedef enum E_EEPROM_XMC1_OPERATION_STATUS
{
  E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS            = 0U, /**< Successful completion of operation*/
  E_EEPROM_XMC1_OPERATION_STATUS_FAILURE            = 1U, /**< APP failed due to internal flash operational errors*/
  E_EEPROM_XMC1_OPERATION_STATUS_INCONSISTENT_BLOCK = 2U, /**< Targeted block is inconsistent*/
  E_EEPROM_XMC1_OPERATION_STATUS_INVALID_BLOCK      = 3U, /**< The latest copy of the targeted block was invalidated */
  E_EEPROM_XMC1_OPERATION_STATUS_CRC_FAILED         = 4U, /**< CRC verification failed for the targeted block*/
  E_EEPROM_XMC1_OPERATION_STATUS_NOT_ALLOWED        = 5U, /**< Operation not allowed to continue*/
  E_EEPROM_XMC1_OPERATION_STATUS_MEMORY_BANK_FULL   = 6U, /**< Write/Invalidate operation failed when bank has no space.
                                                             Call E_EEPROM_XMC1_StartGarbageCollection API to proceed */
  E_EEPROM_XMC1_OPERATION_STATUS_NO_CRC_WRITTEN     = 7U  /**< Written block does not have CRC checksum enabled.*/
} E_EEPROM_XMC1_OPERATION_STATUS_t;

/**
 * @}
 */

/**
 * @ingroup E_EEPROM_XMC1_datastructures
 * @{
 */

/**********************************************************************************************************************
* DATA STRUCTURES
**********************************************************************************************************************/

/**  Data structure to configure the Data Block parameters */
typedef struct E_EEPROM_XMC1_BLOCK
{
  uint8_t block_number; /**< Logical block number (Block ID) */

  uint32_t size; /**< Size of the logical block */

} E_EEPROM_XMC1_BLOCK_t;


/** Data structure to hold the header information about a particular user data block */
typedef struct E_EEPROM_XMC1_BLOCK_HEADER
{
  uint8_t block_number; /**< User data block number */

  uint8_t status; /**< User data block status */

} E_EEPROM_XMC1_BLOCK_HEADER_t;


/*lint -e46 */
/** Bit field data structure holds the overall information about a particular user data block */
typedef struct E_EEPROM_XMC1_CACHE_STATUS
{
  uint32_t valid      : 1; /**< Indicates the data block stored in the flash is valid or invalid */

  uint32_t consistent : 1; /**< Indicates the data block stored in the flash is faulty or not */

  uint32_t copied     : 1; /**< Indicates the data blocks are copied or not to free bank during GC */

  uint32_t crc        : 1; /**< Indicates if the block is enabled with a valid 16 bit CRC */

  uint32_t unused     : 28; /* unused */

} E_EEPROM_XMC1_CACHE_STATUS_t;
/*lint -e46 */


/** Data structure to hold the information about the physical address and status of a user data block */
typedef struct E_EEPROM_XMC1_CACHE
{
  uint32_t address; /**< It has the actual physical address of the flash where the written data block starts */

  E_EEPROM_XMC1_CACHE_STATUS_t status; /**< Status information of the written user data block (Valid/Consistent/CRC)*/

} E_EEPROM_XMC1_CACHE_t;


/** Data structure to hold the count of flash physical blocks and status of a user data block */
typedef struct E_EEPROM_XMC1_TRAVERSE_BLOCK_RESULT
{
  uint32_t block_count; /**< Number of physical flash blocks required for a particular data block */

  E_EEPROM_XMC1_CACHE_STATUS_t status; /**< status of the user data block */

} E_EEPROM_XMC1_TRAVERSE_BLOCK_RESULT_t;


/** Data structure to hold the complete state data information of Emulation APP (Run Time Handler)*/
typedef struct E_EEPROM_XMC1_DATA
{
  E_EEPROM_XMC1_CACHE_t block_info[E_EEPROM_XMC1_MAX_BLOCK_COUNT]; /**< User data block informations are stored here*/

  E_EEPROM_XMC1_TRAVERSE_BLOCK_RESULT_t block_result; /**< get previous data block read result information*/

  uint32_t  current_bank;  /**< Stores the current Bank on which blocks write operation will be done */

  uint32_t  gc_dest_addr; /**< Destination address for copying data during GC */

  uint32_t  gc_src_addr; /**< Source address from which data needs to be copied during GC */

  uint32_t  curr_bank_end_addr; /**< Current bank end address */

  uint32_t  prev_bank_end_addr; /**< previous bank end address */

  uint32_t  next_free_block_addr; /**< Stores the next available flash address for next block write */

  uint32_t  curr_bank_src_addr; /**< Used for cache update and later stores the current Bank base address */

  uint32_t  gc_block_counter; /**< Tracks number of flash blocks read/written during GC process */

  uint32_t  written_block_counter; /**< Keeps track of the number of flash blocks written for an user data block */

  uint8_t   read_write_buffer[E_EEPROM_XMC1_FLASH_BLOCK_SIZE]; /**< Internal buffer to load and store single block */

  uint32_t  crc_buffer; /**< Keeps track the CRC 16 bit CRC value */

  uint8_t   page_write_buffer[E_EEPROM_XMC1_FLASH_PAGE_SIZE]; /**< Internal buffer to load and store single page */

  uint32_t  user_write_bytes_count; /**< Keeps track of the number of bytes written */

  uint32_t  gc_state; /**< State variable to keep track of the current state of the garbage collection procedure */

  uint32_t  init_gc_state; /**< Stores the current state for initialization process */

  uint32_t  gc_log_block_count; /**< Tracks the number of logical blocks covered during GC process  */

  uint32_t  cache_state; /**< Stores current state of the cache update process */

  uint32_t  updated_cache_index; /**< Keeps track of the current block for which cache update is ongoing */

  uint32_t  user_write_state; /**< Current status of the user write */

  uint32_t  read_start_address; /**< Current flash starting address to read the data */

} E_EEPROM_XMC1_DATA_t;


/** Data structure to configure the APP properties. Use @ref E_EEPROM_XMC1_t type for accessing the members */
typedef struct E_EEPROM_XMC1
{
  E_EEPROM_XMC1_BLOCK_t *block_config_ptr; /**< Pointer to user block configurations */

  E_EEPROM_XMC1_DATA_t *data_ptr; /**< Pointer to the state variable data structure */

  #ifdef E_EEPROM_XMC1_CRC_SW_ENABLED
  CRC_SW_t* const crc_handle_ptr;  /**< CRC APP handle pointer*/
  #endif

  E_EEPROM_XMC1_STATUS_t  state; /**< Current state of the APP instance*/

  const uint8_t  block_count; /**< Number of configured user data blocks */

  const uint8_t  erase_all_auto_recovery; /**< Erase Complete emulation area and recover to default state */

  const uint8_t  data_block_crc; /**< Allow to calculate CRC for each data block on write */

  const uint8_t  garbage_collection; /**< Enables garbage collection when no space available for new write*/

} E_EEPROM_XMC1_t;

typedef E_EEPROM_XMC1_t* E_EEPROM_XMC1_HANDLE_PTR_t; /**< Defines a pointer to APP Handle*/

/**
 *@}
 */
 
#ifdef __cplusplus
extern "C"  {
#endif

/**********************************************************************************************************************
 * API Prototypes
 *********************************************************************************************************************/
 
/**
 * @ingroup E_EEPROM_XMC1_apidoc
 * @{
 */

/**
 * @brief Get E_EEPROM_XMC1 APP version
 * @return DAVE_APP_VERSION_t APP version information (major, minor and patch number)
 * <BR>
 * \par<b>Description:</b><br>
 * The function can be used to check application software compatibility with a
 * specific version of the APP.
 *
 * Example Usage:
 * @code
 * #include <DAVE.h>
 * int main(void)
 * {
 *  DAVE_STATUS_t status;
 *  DAVE_APP_VERSION_t app_version;
 *
 *  status = DAVE_Init();   // E_EEPROM_XMC1_Init() is called from DAVE_Init()
 *
 *  if(status == DAVE_STATUS_SUCCESS)
 *  {
 *    app_version = E_EEPROM_XMC1_GetAppVersion();
 *  }
 *
 *  if (app_version.major != 4U)
 *  {
 *    // Probably, not the right version.
 *  }
 *
 *  while(1U)
 *  {
 *  }
 *
 * }
 * @endcode<BR>
 */
DAVE_APP_VERSION_t E_EEPROM_XMC1_GetAppVersion(void);

/**
 * @brief Initializes E_EEPROM_XMC1 APP with the associated configuration handle.
 * @param handle_ptr : Pointer to the handler of the instance for which this API is called<BR>
 *
 * @return<BR> E_EEPROM_XMC1_STATUS_SUCCESS if initialization is successful else E_EEPROM_XMC1_STATUS_FAILURE<BR>
 *
 * \par<b>Description:</b><br>
 *  Configures and initializes the micro-controller flash as an EEPROM associated with the instance handler.
 *  Performs three basic functionalities to support EEPROM related operations.\n\n
 * <OL>
 * <LI><b>Detection of active flash bank and process selection</b></LI><BR>
 *      Reading the marker states from first page of each flash bank detects the active bank and the free bank.
 *      Detection of active flash bank decides the respective process of state machine\n\n
 * <LI><b>State machine process handling</b></LI><BR>
 *      The state machine process finds free space in the flash for writing user data blocks.
 *      If the detection of active bank fails due to corrupted markers, the state machine results in a non recoverable
 *      state. If the configuration option "Erase all and recover" is enabled, the state machine process will bring
 *      the flash to normal state by formatting the flash banks. Else it stalls the initialization until the flash
 *      banks are erased by calling the xmc1_flash low level driver API's.\n\n
 * <LI><b>Building RAM look up table</b></LI><BR>
 *    The RAM lookup table keeps the track of the user data blocks written into flash. The lookup table has the
 *    complete information about a configured user data block.\n\n
 * </OL>
 * <b>IMPORTANT : </b> This API must be successfully called before calling any other E_EEPROM_XMC1 API.<BR>
 *
 * <b>NOTE :</b><BR> This API is called in the definition of DAVE_init by code generation and therefore should not be
 *             explicitly called for the normal operation. Use other APIs only after DAVE_init is called
 *             successfully (returns DAVE_STATUS_SUCCESS).\n\n
 *
 * <b>Related APIs : </b><BR>  DAVE_init\n\n
 *
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 *  @code
 *  #include <DAVE.h>
 *  int main(void)
 *  {
 *    DAVE_STATUS_t status;
 *
 *    status = DAVE_Init();      // Initialization of DAVE Apps
 *
 *    if(status == DAVE_STATUS_SUCCESS)
 *    {
 *     XMC_DEBUG("DAVE Apps initialization success\n");
 *    }
 *    else
 *    {
 *     // Placeholder for error handler code. The while loop below can be replaced with an user error handler
 *     XMC_DEBUG(("DAVE Apps initialization failed with status %d\n", status));
 *     while(1U)
 *     {
 *     }
 *    }
 *    // Placeholder for user application code. The while loop below can be replaced with user application code.
 *    while(1U)
 *    {
 *    }
 *
 *  }
 *  @endcode<BR> </p>
 */
E_EEPROM_XMC1_STATUS_t E_EEPROM_XMC1_Init(E_EEPROM_XMC1_t *const handle_ptr);


/**
 * @brief Programs the user defined data block into the flash.
 * @param block_number : Block ID Name/Number configured in the block table. Use the names defined in
 *                @ref E_EEPROM_XMC1_BLOCK_t configuration structure array.
 * @param data_buffer_ptr : Pointer to the user data buffer which need to be stored in flash
 *
 * @return <BR>
 *    E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS, if the write operation is successful<BR>
 *    E_EEPROM_XMC1_OPERATION_STATUS_NOT_ALLOWED, if APP initialization is not completed or flash is busy<BR>
 *    E_EEPROM_XMC1_OPERATION_STATUS_MEMORY_BANK_FULL, if no space available in flash bank to write the block<BR>
 *    E_EEPROM_XMC1_OPERATION_STATUS_FAILURE, if write failed due to internal flash errors<BR>
 *
 * \par<b>Description:</b><br>
 *  The requested data block is written into the flash immediately, only when free space is available in flash bank.
 *  On non availability of space in active flash bank, the write gets  delayed due to Garbage Collection.
 *<OL>
 * <b>Explicit Garbage Collection on write (Garbage Collection Configuration option Disabled)</b><BR>
 *    Write on insufficient flash bank storage space triggers the garbage collection automatically. But
 *    the configuration option (Garbage collection disabled) restricts to do a garbage collection. Hence the API
 *    returns with the an error status E_EEPROM_XMC1_OPERATION_STATUS_MEMORY_BANK_FULL. The current and future user write
 *    requests will be rejected until an explicit garbage collection is done by calling the API.
 *    E_EEPROM_XMC1_StartGarbageCollection().\n\n
 *</OL>
 *<b>IMPORTANT : </b> This API shall be called only after the successful completion of E_EEPROM_XMC1_Init() API.<BR>
 *              While flash programming operation is in progress, the flash array will be busy and no access to
 *              flash is possible. Hence all other critical functionalities shall be done prior to the execution
 *              of this function.
 *
 *<b>NOTE :</b><BR> It is advised to call this API when the APP in is IDLE state. This can be checked by calling
 *            E_EEPROM_XMC1_GetStatus() API and verifying the status.\n\n
 *
 *<b>Related APIs : </b><BR>  None\n\n
 *
 *<BR><P ALIGN="LEFT"><B>Example:</B>
 *  @code
 *  #include <DAVE.h>
 *  int main(void)
 *  {
 *    DAVE_STATUS_t status;
 *    E_EEPROM_XMC1_OPERATION_STATUS_t oper_status;
 *    uint32_t block_number;
 *
 *    uint8_t data_buffer[12] = {0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB};
 *    block_number = 1U;
 *
 *    status = DAVE_Init();      // Initialization of DAVE apps
 *
 *    if (status == DAVE_STATUS_SUCCESS)
 *    {
 *     oper_status = E_EEPROM_XMC1_Write(block_number,(uint8_t*)data_buffer);
 *    }
 *
 *    // Placeholder for user application code. The while loop below can be replaced with user application code.
 *    while(oper_status == E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS)
 *    {
 *    }
 *
 *    return 1;
 *  }
 *  @endcode<BR> </p>
 */
E_EEPROM_XMC1_OPERATION_STATUS_t E_EEPROM_XMC1_Write(uint8_t block_number, uint8_t *data_buffer_ptr);


/**
 * @brief Reads the data block contents from flash for the requested block number.
 * @param block_number : Block ID Name/Number configured in the block table. Use the names defined in
 *                @ref E_EEPROM_XMC1_BLOCK_t configuration structure array.
 * @param block_offset : Offset position to start the read operation<BR>
 *                Range [0 - (Block size - 1)]
 * @param data_buffer_ptr : Pointer to the data buffer where data has to be stored after read
 * @param length : Number of the data block elements to be read from the FLASH<BR>
 *            Range [1 - (block size - block_offset)]
 *
 * @return <BR>
 *     E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS, if read operation from flash is successful<BR>
 *     E_EEPROM_XMC1_OPERATION_STATUS_FAILURE, if read failed due to ECC errors<BR>
 *     E_EEPROM_XMC1_OPERATION_STATUS_NOT_ALLOWED, if APP initialization is not completed or flash is busy<BR>
 *     E_EEPROM_XMC1_OPERATION_STATUS_INCONSISTENT_BLOCK, if the targeted block was not written properly<BR>
 *     E_EEPROM_XMC1_OPERATION_STATUS_INVALID_BLOCK, if the targeted block was invalidated<BR>
 *
 * \par<b>Description:</b><br>
 *  Reads the data elements starting from the specified offset location. The number of elements read from the flash is
 *  equal to the length specified as input parameter.
 *
 * <b>IMPORTANT : </b> This API do not perform any CRC verification for the read data.
 *
 * <b>NOTE :</b><BR> If the flash is in busy state, the read will not be accepted.
 *
 *  <BR><P ALIGN="LEFT"><B>Example:</B>
 *  @code
 *  #include <DAVE.h>
 *  int main(void)
 *  {
 *    DAVE_STATUS_t status;
 *    E_EEPROM_XMC1_OPERATION_STATUS_t oper_status;
 *    uint32_t block_number;
 *    uint8_t Index;
 *    uint8_t ReadBuffer[12];
 *    uint8_t data_buffer[12] = {0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB};
 *    block_number = 1U;
 *  
 *    status = DAVE_Init();          // Initialization of DAVE apps
 *  
 *    if (status == DAVE_STATUS_SUCCESS)
 *    {
 *     oper_status = E_EEPROM_XMC1_Write(block_number,(uint8_t*)data_buffer);
 *    }
 *  
 *    // Write the first copy of the block into active bank of FEE
 *    if(oper_status == E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS)
 *    {
 *      oper_status = E_EEPROM_XMC1_Write(block_number,data_buffer);
 *    }
 *    // Refill the data buffer with new values
 *    for(Index = 0; Index<12;Index++)
 *    {  data_buffer[Index] = Index; }
 *  
 *    // Write the updated copy of the block into active bank of FEE
 *    if(oper_status == E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS)
 *    {
 *      oper_status = E_EEPROM_XMC1_Write(block_number,data_buffer);
 *    }
 *  
 *    //Clear the Read buffer before accepting the read request
 *    for(Index = 0; Index<12;Index++)
 *    {  ReadBuffer[Index] = 0x00; }
 *  
 *    // Read the latest copy of the written block from the active bank
 *    if(oper_status == E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS)
 *    {
 *      oper_status = E_EEPROM_XMC1_Read(block_number,0U,ReadBuffer,12U);
 *    }
 *  
 *    while(oper_status == E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS)
 *    {}
 *  }
 *  @endcode<BR> </p>
 */
E_EEPROM_XMC1_OPERATION_STATUS_t E_EEPROM_XMC1_Read(uint8_t block_number,
                                                    uint32_t block_offset,
                                                    uint8_t *data_buffer_ptr,
                                                    uint32_t length );

/**
 * @brief Executes garbage collection at runtime.
 * @param None :
 *
 * @return <BR>
 *     E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS, if garbage collection is successful<BR>
 *     Else return E_EEPROM_XMC1_OPERATION_STATUS_FAILURE on internal flash errors<BR>
 *
 * \par<b>Description:</b><br>
 *  Performs an explicit Garbage collection any time during the execution of APP. The function is
 *  accepted only if the E_EEPROM_XMC1 is in IDLE state.
 *
 *<b>NOTE :</b><BR> If the flash is busy this will not be processed. It will check for any read write or erase errors
 *            and if any errors present it will return error.
 *
 *  <BR><P ALIGN="LEFT"><B>Example:</B>
 *  @code
 *  #include <DAVE.h>
 *  int main(void)
 *  {
 *    DAVE_STATUS_t status;
 *
 *    status = DAVE_Init();      // Initialization of DAVE apps
 *
 *    if ( status == DAVE_STATUS_SUCCESS)
 *    {
 *     if(E_EEPROM_XMC1_IsGarbageCollectionNeeded(1U))
 *     {
 *      status = E_EEPROM_XMC1_StartGarbageCollection();
 *     }
 *    }
 *    while(1)
 *    {}
 *  }
 *  @endcode<BR> </p>
 */
E_EEPROM_XMC1_OPERATION_STATUS_t E_EEPROM_XMC1_StartGarbageCollection(void);

/**
 * @brief Invalidate the user defined data block that was written into the flash.
 * @param block_number : Block ID Name/Number configured in the block table
 *
 * @return <BR>
 *    E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS, if the write operation is successful<BR>
 *    E_EEPROM_XMC1_OPERATION_STATUS_NOT_ALLOWED, if APP initialization is not completed or flash is busy<BR>
 *    E_EEPROM_XMC1_OPERATION_STATUS_MEMORY_BANK_FULL, if no space available in flash bank to write the block<BR>
 *    E_EEPROM_XMC1_OPERATION_STATUS_FAILURE, else failed due to internal flash errors<BR>
 *
 * \par<b>Description:</b><br>
 *  The invalidated block is written into the flash immediately, only when free space is available in flash bank.
 *  On non availability of space in active flash bank, the invalidate write gets delayed due to Garbage Collection.
 *  <OL>
 *  <b>Explicit Garbage Collection on write (Garbage Collection Configuration option Disabled)</b><BR>
 *    Invalidation on insufficient flash bank storage space, triggers the garbage collection automatically. But
 *    the configuration option (Garbage collection disabled) restricts to do a garbage collection. Hence the API
 *    returns with the an error status E_EEPROM_XMC1_OPERATION_STATUS_MEMORY_BANK_FULL. The current and future user
 *    write requests will be rejected until an explicit garbage collection is done by calling the API
 *    E_EEPROM_XMC1_StartGarbageCollection().\n\n
 * </OL>
 * <b>IMPORTANT : </b> This API shall be called only after the successful completion of E_EEPROM_XMC1_Init() API.<BR>
 *              While flash programming operation is in progress, the flash array will be busy and no access to
 *              flash is possible. Hence all other critical functionalities shall be done prior to the execution
 *              of this function.
 *
 * <b>NOTE :</b><BR> It is advised to call this API when the APP in is IDLE state. This can be checked by calling
 *            E_EEPROM_XMC1_GetStatus() API and verifying the status.\n\n
 *
 * <b>Related APIs : </b><BR>  None\n\n
 *
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 *  @code
 *  #include <DAVE.h>
 *  int main(void)
 *  {
 *    DAVE_STATUS_t status;
 *    E_EEPROM_XMC1_OPERATION_STATUS_t oper_status;
 *    uint32_t block_number;
 *    uint8_t Index;
 *    uint8_t ReadBuffer[12];
 *  
 *    uint8_t data_buffer[12] = {0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB};
 *    block_number = 1U;
 *  
 *    status = DAVE_Init();          // Initialization of DAVE apps
 *  
 *    if (status == DAVE_STATUS_SUCCESS)
 *    {
 *     oper_status = E_EEPROM_XMC1_Write(block_number,(uint8_t*)data_buffer);
 *    }
 *  
 *    // Invalidate the block for future
 *    if(oper_status == E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS)
 *    {
 *      oper_status = E_EEPROM_XMC1_InvalidateBlock(block_number);
 *    }
 *  
 *    //Clear the Read buffer before accepting the read request
 *    for(Index = 0; Index<12;Index++)
 *    {  ReadBuffer[Index] = 0x00; }
 *  
 *    // Read the last written block from the active bank of FEE
 *    if(oper_status == E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS)
 *    {
 *      oper_status = E_EEPROM_XMC1_Read(block_number,0U,ReadBuffer,12U);
 *    }
 *    while(oper_status == E_EEPROM_XMC1_OPERATION_STATUS_INVALID_BLOCK)
 *    {}
 *    // Placeholder for user application code. The while loop below can be replaced with user application code.
 *    while(1U)
 *    {
 *    }
 *  
 *  }
 *  @endcode<BR> </p>
 */

E_EEPROM_XMC1_OPERATION_STATUS_t E_EEPROM_XMC1_InvalidateBlock(uint8_t block_number);

/**
 * @brief Checks the status of APP.
 * @param None:
 *
 * @return <BR>
 *        E_EEPROM_XMC1_STATUS_IDLE, if APP is in IDLE state to accept any request<BR>
 *        E_EEPROM_XMC1_STATUS_FAILURE, if any previous operation on APP failed due to some internal error<BR>
 *        E_EEPROM_XMC1_STATUS_BUSY, Else APP is in busy state because of flash operations<BR>
 *
 * \par<b>Description:</b><br>
 *  Read the current status of APP.
 *
 *  <BR><P ALIGN="LEFT"><B>Example:</B>
 *  @code
 *  #include <DAVE.h>
 *  int main(void)
 *  {
 *    E_EEPROM_XMC1_STATUS_t status;
 *    E_EEPROM_XMC1_OPERATION_STATUS_t oper_status;
 *    uint32_t block_number;
 *    uint8_t data_buffer[12] = {0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB};
 *    block_number = 1U;
 *    // Initialize DAVE, E_EEPROM_XMC1_Init() will be called within DAVE_Init()
 *
 *    DAVE_Init();
 *
 *    status = E_EEPROM_XMC1_GetStatus();
 *
 *    if(status == E_EEPROM_XMC1_STATUS_IDLE)
 *    {
 *     oper_status = E_EEPROM_XMC1_Write(block_number,(uint8_t*)data_buffer);
 *    }
 *    if(oper_status == E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS)
 *    {
 *      while(1)
 *      {}
 *    }
 *  }
 *  @endcode<BR> </p>
 */
E_EEPROM_XMC1_STATUS_t E_EEPROM_XMC1_GetStatus(void);

/**
 * @brief Check the availability of space in flash bank to write the data block.
 * @param block_number : Block ID Name/Number configured in the block table. Use the names defined in
 *                @ref E_EEPROM_XMC1_BLOCK_t configuration structure array.
 *
 * @return  <BR>
 *        true, if the bank has no space to write the requested block, else returns false.
 *
 * \par<b>Description:</b><br>
 *  During any time of the execution,the need for Garbage collection can be decided by calling this API. This will help
 *  to save time in the runtime write process which triggers a garbage collection automatically.
 *
 * <b>IMPORTANT : </b> This API shall be called only after the successful completion of E_EEPROM_XMC1_Init() API.<BR>
 *
 * <b>NOTE :</b><BR> After initialization of the APP, calling this API can decide the need for Garbage collection.
 *            If this API returns true an explicit garbage collection can be done by calling the API
 *            E_EEPROM_XMC1_StartGarbageCollection().
 *
 *
 *  <BR><P ALIGN="LEFT"><B>Example:</B>
 *  @code
 *  #include <DAVE.h>
 *  int main(void)
 *  {
 *    DAVE_STATUS_t status;
 *
 *    status = DAVE_Init();      // Initialization of DAVE apps
 *
 *    if ( status == DAVE_STATUS_SUCCESS)
 *    {
 *     if(E_EEPROM_XMC1_IsGarbageCollectionNeeded(1U) == true)
 *     {
 *      status = E_EEPROM_XMC1_StartGarbageCollection();
 *     }
 *    }
 *    while(1)
 *    {}
 *  }
 *  @endcode<BR> </p>
 */
bool E_EEPROM_XMC1_IsGarbageCollectionNeeded(uint8_t block_number);


#ifdef E_EEPROM_XMC1_CRC_SW_ENABLED
/**
 * @brief Reads complete data block from flash and verify the data integrity using CRC checksum.
 * @param block_number : Block ID Name/Number configured in the block table. Use the names defined in
 *                       @ref E_EEPROM_XMC1_BLOCK_t configuration structure array.
 * @param data_buffer_ptr : Pointer to the data buffer where data has to be stored after read
 *
 * @return <BR>
 *     E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS, if read operation from flash is successful<BR>
 *     E_EEPROM_XMC1_OPERATION_STATUS_FAILURE, if read failed due to ECC errors<BR>
 *     E_EEPROM_XMC1_OPERATION_STATUS_NOT_ALLOWED, if APP initialization is not completed or flash is busy<BR>
 *     E_EEPROM_XMC1_OPERATION_STATUS_INCONSISTENT_BLOCK, if the targeted block was not written properly<BR>
 *     E_EEPROM_XMC1_OPERATION_STATUS_INVALID_BLOCK, if the targeted block was invalidated<BR>
 *     E_EEPROM_XMC1_OPERATION_STATUS_NO_CRC_WRITTEN, if the targeted block was written before without CRC enabled<BR> 
 *     E_EEPROM_XMC1_OPERATION_STATUS_CRC_FAILED, else CRC verification failed for the targeted block<BR>
 *
 * \par<b>Description:</b><br>
 *  Reads 16 bit CRC from header block. CRC checksum for the complete data block is calculated and compared with the
 *  16 bit CRC read from header block. The API return success only if both the calculated CRC and written CRC matches.
 *
 *  <b>NOTE :</b><BR> If the flash is busy this will not be processed.
 *
 *  <BR><P ALIGN="LEFT"><B>Example:</B>
 *  @code
 *  #include <DAVE.h>
 *  int main(void)
 *  {
 *    DAVE_STATUS_t status;
 *    E_EEPROM_XMC1_OPERATION_STATUS_t oper_status;
 *    uint32_t block_number;
 *    uint8_t Index;
 *    uint8_t ReadBuffer[12];
 *    uint8_t data_buffer[12] = {0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB};
 *    block_number = 1U;
 *  
 *    status = DAVE_Init();          // Initialization of DAVE apps
 *  
 *    if (status == DAVE_STATUS_SUCCESS)
 *    {
 *     oper_status = E_EEPROM_XMC1_Write(block_number,(uint8_t*)data_buffer);
 *    }
 *  
 *    // Write the first copy of the block into active bank of FEE
 *    if(oper_status == E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS)
 *    {
 *      oper_status = E_EEPROM_XMC1_Write(block_number,data_buffer);
 *    }
 *    // Refill the data buffer with new values
 *    for(Index = 0; Index<12;Index++)
 *    {  data_buffer[Index] = Index; }
 *  
 *    // Write the updated copy of the block into active bank of FEE
 *    if(oper_status == E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS)
 *    {
 *      oper_status = E_EEPROM_XMC1_Write(block_number,data_buffer);
 *    }
 *  
 *    //Clear the Read buffer before accepting the read request
 *    for(Index = 0; Index<12;Index++)
 *    {  ReadBuffer[Index] = 0x00; }
 *  
 *    // Read the latest copy of the written block from the active bank
 *    if(oper_status == E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS)
 *    {
 *      oper_status = E_EEPROM_XMC1_VerifyBlockCrcStatus(block_number,ReadBuffer);
 *    }
 *  
 *    while(oper_status == E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS)
 *    {}
 *  }
 *  @endcode<BR> </p>
 */
E_EEPROM_XMC1_OPERATION_STATUS_t E_EEPROM_XMC1_VerifyBlockCrcStatus(uint8_t block_number, uint8_t *data_buffer_ptr);
#endif

/**
 * @brief Reads the just previous copy of the block from flash for the requested block number.
 * @param block_number : Block ID Name/Number configured in the block table. Use the names defined in
 *                @ref E_EEPROM_XMC1_BLOCK_t configuration structure array.
 * @param block_offset : Offset position to start the read operation<BR>
 *                Range [0 - (Block size - 1)]
 * @param data_buffer_ptr : Pointer to the data buffer where data has to be stored after read
 * @param length : Number of the data block elements to be read from the FLASH<BR>
 *            Range [1 - (block size - block_offset)]
 *
 * @return <BR>
 *     E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS, if read operation from flash is successful<BR>
 *     E_EEPROM_XMC1_OPERATION_STATUS_FAILURE, if read failed due to ECC errors<BR>
 *     E_EEPROM_XMC1_OPERATION_STATUS_NOT_ALLOWED, if APP initialization is not completed or flash is busy<BR>
 *     E_EEPROM_XMC1_OPERATION_STATUS_INCONSISTENT_BLOCK, if the targeted block was not written properly<BR>
 *     E_EEPROM_XMC1_OPERATION_STATUS_INVALID_BLOCK, if the targeted block was invalidated<BR>
 *
 * \par<b>Description:</b><br>
 *  It is useful when the latest write is interrupted due to power failures and flash errors. If a block read results
 *  in error, calling this API will search for the very next previous copy in the same bank. If the block is available
 *  then the user buffer will be filled with the data as per the requested length and offset. If the just previous
 *  copy of the data block is also inconsistent or invalid, no search will be done further.
 *
 *  <b>IMPORTANT : </b> This API do not perform any CRC verification for the read data.
 *
 *  <b>NOTE :</b><BR> If the flash is in busy state, the read will not be accepted.
 *
 *  <BR><P ALIGN="LEFT"><B>Example:</B>
 *  @code
 *  #include <DAVE.h>
 *  int main(void)
 *  {
 *    E_EEPROM_XMC1_STATUS_t status;
 *    E_EEPROM_XMC1_OPERATION_STATUS_t oper_status;
 *    uint32_t block_number;
 *    uint8_t DataBuffer[12] =  {  0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,
 *                       0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,
 *                     };
 *    uint8_t Index;
 *    uint8_t ReadBuffer[12];
 *  
 *    block_number = 1;
 *    // Initialize DAVE, E_EEPROM_XMC1_Init() will be called within DAVE_Init()
 *  
 *    // Initialize Dave apps
 *    DAVE_Init();
 *  
 *    status = E_EEPROM_XMC1_GetStatus();
 *  
 *    // Write the first copy of the block into active bank of FEE
 *    if(status == E_EEPROM_XMC1_STATUS_IDLE)
 *    {
 *      oper_status = E_EEPROM_XMC1_Write(block_number,DataBuffer);
 *    }
 *  
 *    // Refill the data buffer with new values
 *    for(Index = 0; Index<12;Index++)
 *    {  DataBuffer[Index] = Index; }
 *  
 *    // Write the updated copy of the block into active bank of FEE
 *    if(oper_status == E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS)
 *    {
 *      E_EEPROM_XMC1_Write(block_number,DataBuffer);
 *    }
 *  
 *    //Clear the Read buffer before accepting the GetPreviousData read request
 *    for(Index = 0; Index<12;Index++)
 *    {  ReadBuffer[Index] = 0x00; }
 *  
 *    // Read the previously copy of the written block from the active bank
 *    if(oper_status == E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS)
 *    {
 *      status = E_EEPROM_XMC1_GetPreviousData(block_number,5U,ReadBuffer,7U);
 *    }
 *  
 *    while(oper_status == E_EEPROM_XMC1_OPERATION_STATUS_SUCCESS)
 *   {}
 *  }
 *   @endcode<BR> </p>
 */
E_EEPROM_XMC1_OPERATION_STATUS_t E_EEPROM_XMC1_GetPreviousData(uint8_t block_number,
                                                               uint32_t block_offset,
                                                               uint8_t *data_buffer_ptr,
                                                               uint32_t length );
/**
 *@}
 */

#ifdef __cplusplus
}
#endif

#include "e_eeprom_xmc1_extern.h"

#endif /* E_EEPROM_XMC1_H_ */
