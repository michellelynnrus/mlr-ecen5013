#ifndef __CMDIF_H__
#define __CMDIF_H__

#include <stdint.h>
#include "cmdDefs.h"

/*
 * typedef enum cmdIf_Status_t
 * enum to indicate success or failure of binary log functions
 */
typedef enum {
	CMDIF_OK,
	CMDIF_NULLPTR,
	CMDIF_ERROR
} cmdIf_Status_t;

/**************
* cmdIf_Receive()
*	description:
*		receives command
*	params:
*		none
*	returns:
*		cmdIf_Status_t status - returns OK or NULLPTR
**************/
cmdIf_Status_t cmdIf_Receive(void);

/**************
* cmdIf_CreateCmdObj()
*	description:
*		allocates memory for a CMD_t object
*	params:
*		CMD_t ** cmd - pointer to cmd pointer
*		uint32_t payloadLength - length of the payload
*	returns:
*		cmdIf_Status_t status - returns OK or NULLPTR
**************/
cmdIf_Status_t cmdIf_CreateCmdObj(CMD_t ** cmd, uint32_t payloadLength);


/**************
* cmdIf_DestroyCmdObj()
*	description:
*		Frees the cmd item from dynamic memory
*	params:
*		CMD_t * cmd - pointer to cmd object
*	returns:
*		cmdIf_Status_t status - returns OK or NULLPTR
**************/
cmdIf_Status_t cmdIf_DestroyCmdObj(CMD_t *cmd);


/**************
* cmdIf_Decode()
*	description:
*		Decodes the command to determine what function needs to be 
* 		called to service the command
*	params:
*		CMD_t * cmd - pointer to cmd object
*	returns:
*		cmdIf_Status_t status - returns OK or NULLPTR
**************/
cmdIf_Status_t cmdIf_Decode(CMD_t *cmd);

/**************
* cmdIf_SendCmd()
*	description:
*		Creates and sends a command
*	params:
*		CMD_ID_t cmdID - command ID to sends
*		uint32_t payloadLength - length of payload to sends
*		uint8_t * payload - payload to send
*	returns:
*		cmdIf_Status_t status - returns OK or NULLPTR
**************/
cmdIf_Status_t cmdIf_SendCmd(CMD_ID_t cmdID, uint32_t payloadLength, uint8_t * payload);


/**************
* cmdIf_VerifyCS()
*	description:
*		Verifys the command's checksum
*	params:
*		CMD_t * cmd - pointer to cmd object
*	returns:
*		cmdIf_Status_t status - returns OK or NULLPTR
**************/
cmdIf_Status_t cmdIf_VerifyCS(CMD_t *cmd);

#endif /* __CMDIF_H__*/
