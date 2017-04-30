#ifndef __CMDDEFS_H__
#define __CMDDEFS_H__

#include <stdint.h>
#define CMD_PAYLOAD_LENGTH_MAX (64)
#define CMD_NO_PAYLOAD (0)

/*
 * typedef enum cmd_ID_t
 * Log ID codes for the 14 existing types of binary log items
 */
typedef enum {
	LED_SET_EN_STATE_CID = 0,	//Set LED enable state cmd, LED_SET_EN_STATE_Cmd_Payload_t
	LED_SET_PWM_CID = 1,		//Set PWM cmd, LED_SET_PWM_Cmd_Payload_t
	RESET_CID = 2,			 	//Remote reset cmd, CMD_NO_PAYLOAD
	GET_TIME_CID = 3			//Get EPOCH/RTC time, CMD_NO_PAYLOAD
} CMD_ID_t;

typedef struct {
	CMD_ID_t cmdID;
	uint8_t length;
	uint8_t * payload;
	uint8_t checksum;
	cmdDefs_Status_t (* ftnCallback)(uint8_t * payload);
} CMD_t;

typedef struct {
	LED_t ledID;
	uint8_t enableState;
} LED_SET_EN_STATE_Cmd_Payload_t;

typedef struct {
	LED_t ledID;
	uint8_t pwmValue;
} LED_SET_PWM_Cmd_Payload_t;

#endif /* __CMDDEFS_H__*/
