#include "cmdIf.h"
#include "cmdDefs.h"
#include <stdint.h>
#include "psp_macros_log.h"
#include "psp_macros_cmd.h"
#include "memory.h"
#include "uart.h"

#include <stdlib.h>
#include <string.h>

cmdIf_Status_t cmdIf_Receive(void){
	cmdIf_Status_t status = CMDIF_OK;
	CMD_t * cmd;
	
	//first byte is cmdID
	uint8_t dataIn = 0;
	PSP_CMDIF_RECEIVE(&dataIn);
	CMD_ID_t cmdID_in = (CMD_ID_t)dataIn;
	
	uint8_t string[64];
	sprintf(string, "Byte 0, cmdID = 0x%x", dataIn);
	LOG_ITEM_ASCII(INFO, string, NO_PAYLOAD);
	
	//second byte is payload size
	PSP_CMDIF_RECEIVE(&dataIn);
	uint8_t payloadLen_in = dataIn;
	
	sprintf(string, "Byte 1, size = 0x%x", dataIn);
	LOG_ITEM_ASCII(INFO, string, NO_PAYLOAD);
	
	//go make the cmd object
	cmdIf_CreateCmdObj(&cmd, payloadLen_in);
	
	//set cmdID
	cmd->cmdID = cmdID_in;

	//next bytes are payload
	//loop through length and read data into the payload
	for (uint32_t i = 0; i < payloadLen_in; i++){
		PSP_CMDIF_RECEIVE(&dataIn);
		*(cmd->payload + i) = dataIn;
		
		sprintf(string, "Byte %d, data[i] = 0x%x", i, dataIn);
		LOG_ITEM_ASCII(INFO, string, NO_PAYLOAD);
	
	}
	
	//next byte is checksum
	PSP_CMDIF_RECEIVE(&dataIn);
	cmd->checksum = dataIn;
	
	sprintf(string, "Byte x, CS = 0x%x", dataIn);
	LOG_ITEM_ASCII(INFO, string, NO_PAYLOAD);
	
	status = cmdIf_VerifyCS(cmd);
	
	if (status == CMDIF_OK){
		//decode cmd and decide what callback ftn to call
		status = cmdIf_Decode(cmd);
		
		//call the callback ftn to execute the command
		if (*cmd->ftnCallback != 0) {
			cmd->ftnCallback(cmd->length, cmd->payload);
		} else {
			//todo: probably should log an error here
		}
	} else {
		//todo: probably should log an error here
	}

	//destroy the cmd object
	cmdIf_DestroyCmdObj(cmd);

	return status;
}


cmdIf_Status_t cmdIf_CreateCmdObj(CMD_t ** cmd, uint32_t payloadLength){
	cmdIf_Status_t status = CMDIF_OK;

	if (!cmd){
		status = CMDIF_NULLPTR;
	} else {
		//allocate space for cmd data type
		*cmd = (CMD_t *) malloc(sizeof(CMD_t));

		if (!cmd){
			status = CMDIF_ERROR;
		} else {
		//allocate space for payload
			(*cmd)->payload = (uint8_t *) malloc(payloadLength);

			if (!((*cmd)->payload)){
				status = CMDIF_ERROR;
			} else {
				//initialize logID to 0
				(*cmd)->cmdID = 0;

				//set payload length
				(*cmd)->length = payloadLength;
				
				//initialize function pointer to 0
				(*cmd)->ftnCallback = 0;
			}
		}
	}

	return status;
}

cmdIf_Status_t cmdIf_DestroyCmdObj(CMD_t *cmd){
	cmdIf_Status_t status = CMDIF_OK;

	if (!cmd){
		status = CMDIF_NULLPTR;
	} else {
		free(cmd->payload);
		free(cmd);
	}

	return status;
}

cmdIf_Status_t cmdIf_Decode(CMD_t *cmd){
	cmdIf_Status_t status = CMDIF_OK;
	uint8_t string[64];
	switch(cmd->cmdID){
		sprintf(string, "DECODE cmdID = 0x%x", cmd->cmdID);
		LOG_ITEM_ASCII(INFO, string, NO_PAYLOAD);

		case LED_SET_EN_STATE_CID:
			cmd->ftnCallback = CMD_LEDSetEnState;
			LOG_ITEM_ASCII(INFO, "DECODE CMD_LEDSetEnState", NO_PAYLOAD);
			break;
		case LED_SET_PWM_CID:
			cmd->ftnCallback = CMD_LEDSetPWM;
			LOG_ITEM_ASCII(INFO, "DECODE CMD_LEDSetPWM", NO_PAYLOAD);
			break;
		case RESET_CID:
			cmd->ftnCallback = CMD_Reset;
			LOG_ITEM_ASCII(INFO, "DECODE CMD_Reset", NO_PAYLOAD);
			break;
		case GET_TIME_CID:
			cmd->ftnCallback = CMD_GetTime;
			LOG_ITEM_ASCII(INFO, "DECODE CMD_GetTime", NO_PAYLOAD);
			break;
		default:

			sprintf(string, "Invalid cmdID = 0x%x", cmd->cmdID);
			LOG_ITEM_ASCII(ERROR, string, NO_PAYLOAD);
			break;
	
	}
	
	
	
	return status;
}

cmdIf_Status_t cmdIf_SendCmd(CMD_ID_t cmdID, uint32_t payloadLength, uint8_t * payload){
	cmdIf_Status_t status = CMDIF_OK;

	if (payloadLength > 0 && !payload){
		status = CMDIF_NULLPTR;
	} else {
		// create cmd item
		CMD_t * cmd;
		cmdIf_CreateCmdObj(&cmd, payloadLength);

		//set cmd item values, copy payload
		cmd->cmdID = cmdID;
		my_memmove(payload, cmd->payload, payloadLength);

		//send item
		//UART?

		//destroy log item
		cmdIf_DestroyCmdObj(cmd);
	}

	return status;
}


cmdIf_Status_t cmdIf_VerifyCS(CMD_t *cmd){
	cmdIf_Status_t status = CMDIF_OK;

	
	
	return status;
}

