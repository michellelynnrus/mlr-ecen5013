#ifndef __CMDDEFS_H__
#define __CMDDEFS_H__

#include <stdint.h>
#define CMD_PAYLOAD_LENGTH_MAX (64)
#define CMD_NO_PAYLOAD (0)



#define NUM_VALID_CIDS (4)
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


/**************
* CMD Callback functions
*	description:
*		CMD_LEDSetEnState - sets the selected RGB LED enable state
*		CMD_LEDSetPWM - sets the selected RGB LED PWM value
*		CMD_Reset - soft reset of the processor
*		CMD_GetTime - gets the current EPOCH/RTC time (currently only logs)
*	params:
*		uint8_t length - length of the pointer (to validate payload)
*		uint8_t * payload - pointer to command payload
*	returns:
*		none
**************/
void CMD_LEDSetEnState(uint8_t length, uint8_t * payload);
void CMD_LEDSetPWM(uint8_t length, uint8_t * payload);
void CMD_Reset(uint8_t length, uint8_t * payload);
void CMD_GetTime(uint8_t length, uint8_t * payload);

/**************
* typedef void (* CMD_CallbackArr_t)(uint8_t * payload)
*	description:
*		Enum of status codes used as return values from CB functions.
*	fields:
*		OK - Nothing is inherently wrong with operation performed
*		FULL - Circular buffer is full
*		EMPTY - Circular buffer is empty
*		NULLPTR - Circular buffer pointer is null
*		UNKNOWN_ERROR - You broke something (may not be used)
**************/
void (* CMD_CallbackArr[NUM_VALID_CIDS])(uint8_t length, uint8_t * payload) = {
	CMD_LEDSetEnState,
	CMD_LEDSetPWM,
	CMD_Reset,
	CMD_GetTime
};

/**************
* typedef struct CMD_t
*	description:
*		Command description structure
*	fields:
*		CMD_ID_t cmdID - command ID
*		uint8_t length - length of payload
*		uint8_t * payload - payload
*		uint8_t checksum - checksum
*		void (* ftnCallback)(uint8_t length, uint8_t * payload) - callback function
**************/
typedef struct {
	CMD_ID_t cmdID;
	uint8_t length;
	uint8_t * payload;
	uint8_t checksum;
	void (* ftnCallback)(uint8_t length, uint8_t * payload);
} CMD_t;

/**************
* typedef struct LED_SET_EN_STATE_Cmd_Payload_t
*	description:
*		Payload structure of LED_SET_EN_STATE_CID command
*	fields:
*		uint8_t ledID - valid options are LED_RED, LED_GREEN, LED_BLUE
*		uint8_t enableState - valid options are 1 for on, 0 for off
**************/
typedef struct __attribute__((__packed__)){
	uint8_t ledID;
	uint8_t enableState;
} LED_SET_EN_STATE_Cmd_Payload_t;

/**************
* typedef struct LED_SET_PWM_Cmd_Payload_t
*	description:
*		Payload structure of LED_SET_PWM_CID command
*	fields:
*		uint8_t ledID - valid options are LED_RED, LED_GREEN, LED_BLUE
*		uint8_t pwmValue - pwm value to set
**************/
typedef struct __attribute__((__packed__)){
	uint8_t ledID;
	uint8_t pwmValue;
} LED_SET_PWM_Cmd_Payload_t;

#endif /* __CMDDEFS_H__*/
