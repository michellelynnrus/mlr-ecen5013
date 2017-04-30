#include "cmdIf.h"
#include "cmdDefs.h"
#include <stdint.h>
#include "psp_macros_log.h"
#include "memory.h"

cmdIf_Status_t cmdIf_Receive(void){
	cmdIf_Status_t status = CMDIF_OK;
	CMD_t * cmd;
	
	//receive data from somewhere
	//UART?
	
	//first byte is cmdID
	//uint8_t uartIn = UART_READ();
	//CMD_ID_t cmdID_in = (CMD_ID_t)uartIn;
	
	//second byte is payload size
	//uartIn = UART_READ();
	//uint8_t payloadLen_in = uartIn;
	
	//go make the cmd object
	cmdIf_CreateCmdObj(&cmd, payloadLen_in);
	
	//next bytes are payload
	//loop through length and read data into the payload
	for (uint32_t i = 0; i < payloadLen_in; i++){
		//uartIn = UART_READ();
		//*(cmd->payload + i) = uartIn;
	}
	
	//next byte is checksum
	//uartIn = UART_READ();
	//cmd->checksum = uartIn;
	
	status = cmdIf_VerifyCS(cmd);
	
	if (status == CMDIF_OK){
		//decode cmd and decide what callback ftn to call
		status = cmdIf_Decode(cmd);
		
		//call the callback ftn to execute the command
		if (*cmd->ftnCallback != 0) {
			cmd->ftnCallback(cmd->payload);
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
				(*cmd)->payloadSize = payloadLength;
				
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
	
	
	
	
	
	
	return status;
}

cmdIf_Status_t cmdIf_SendCmd(CMD_ID_t cmdID, uint32_t payloadLength, uint8_t * payload){
	cmdIf_Status_t status = CMDIF_OK;

	if (length > 0 && !payload){
		status = CMDIF_NULLPTR;
	} else {
		// create cmd item
		CMD_t * cmd;
		cmdIf_CreateCmdObj(&cmd, length);

		//set cmd item values, copy payload
		cmd->cmdID = cmdID;
		my_memmove(payload, cmd->payload, length);

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

