#include "cmdDefs.h"
#include <stdint.h>
#include "psp_macros_log.h"
#include "timer.h"

void CMD_LEDSetEnState(uint8_t length, uint8_t * payload){
	int8_t status = 1;
	uint8_t string[100];
	if (length != sizeof(LED_SET_EN_STATE_Cmd_Payload_t)){
		LOG_ITEM_ASCII(ERROR, "Invalid LED SET PWM cmd, expected length = ", sizeof(LED_SET_EN_STATE_Cmd_Payload_t));
		LOG_ITEM_ASCII(ERROR, "Actual length = ", length);
		status = -1;
	} else {

		//cast payload to defined payload struct
		LED_SET_EN_STATE_Cmd_Payload_t * ledSetEnStatePayload = (LED_SET_EN_STATE_Cmd_Payload_t *) payload;
		uint16_t brightPercent = 0;
		if (ledSetEnStatePayload->enableState){
			brightPercent = 100;
		}
		switch (ledSetEnStatePayload->ledID){
		case LED_RED:
			LOG_ITEM_ASCII(INFO, "LED SET EN STATE - RED LED", NO_PAYLOAD);
			pwm_setRedBrightness(brightPercent);
			break;
		case LED_GREEN:
			LOG_ITEM_ASCII(INFO, "LED SET EN STATE - GREEN LED", NO_PAYLOAD);
			pwm_setGreenBrightness(brightPercent);
			break;
		case LED_BLUE:
			LOG_ITEM_ASCII(INFO, "LED SET EN STATE - BLUE LED", NO_PAYLOAD);
			break;
		default:
			LOG_ITEM_ASCII(ERROR, "Invalid LED SET EN STATE cmd, LED ID = ", ledSetEnStatePayload->ledID);
			status = -1;
			break;
		}

		//GPIO_SetLEDEnState(ledSetEnStatePayload->ledID, ledSetEnStatePayload->enableState);

		if(status >= 0){
			if (ledSetEnStatePayload->enableState == 1){
				LOG_ITEM_ASCII(INFO, "LED SET EN STATE cmd = ON", NO_PAYLOAD);
			} else if (ledSetEnStatePayload->enableState == 0) {
				LOG_ITEM_ASCII(INFO, "LED SET EN STATE cmd = OFF", NO_PAYLOAD);
			} else {
				LOG_ITEM_ASCII(ERROR, "Invalid LED SET EN STATE cmd, EN STATE = ", ledSetEnStatePayload->enableState);
				status = -1;
			}
		}

		if(status >= 0){
			LOG_ITEM_ASCII(INFO, "Valid LED SET EN STATE cmd", NO_PAYLOAD);
		}

	}
}

void CMD_LEDSetPWM(uint8_t length, uint8_t * payload){
	int8_t status = 1;

	if (length != sizeof(LED_SET_PWM_Cmd_Payload_t)){
		LOG_ITEM_ASCII(ERROR, "Invalid LED SET PWM cmd, expected length = ", sizeof(LED_SET_PWM_Cmd_Payload_t));
		LOG_ITEM_ASCII(ERROR, "Actual length = ", length);

		status = -1;
	} else {

		//cast payload to defined payload struct
		LED_SET_PWM_Cmd_Payload_t * ledSetPwmCmdPayload = (LED_SET_PWM_Cmd_Payload_t *) payload;

		//for debugging
		switch (ledSetPwmCmdPayload->ledID){
		case LED_RED:
			LOG_ITEM_ASCII(INFO, "LED SET PWM - RED LED", NO_PAYLOAD);
			pwm_setRedBrightness(ledSetPwmCmdPayload->pwmValue);
			break;
		case LED_GREEN:
			LOG_ITEM_ASCII(INFO, "LED SET PWM - GREEN LED", NO_PAYLOAD);
			pwm_setGreenBrightness(ledSetPwmCmdPayload->pwmValue);
			break;
		case LED_BLUE:
			LOG_ITEM_ASCII(INFO, "LED SET PWM - BLUE LED", NO_PAYLOAD);
			break;
		default:
			LOG_ITEM_ASCII(ERROR, "Invalid LED SET PWM cmd, LED ID = ", ledSetPwmCmdPayload->ledID);
			status = -1;
			break;
		}

		if(status >= 0){
			LOG_ITEM_ASCII(INFO, "LED SET PWM cmd, PWM value = ", ledSetPwmCmdPayload->pwmValue);
			LOG_ITEM_ASCII(INFO, "Valid LED SET PWM cmd", NO_PAYLOAD);
		}

	}
}

void CMD_Reset(uint8_t length, uint8_t * payload){
	if (length > 0){
		LOG_ITEM_ASCII(ERROR, "Invalid RESET cmd, expected length = 0, actual = ", length);
	} else {
		LOG_ITEM_ASCII(INFO, "Valid RESET cmd", NO_PAYLOAD);
		NVIC_SystemReset();
	}
}

void CMD_GetTime(uint8_t length, uint8_t * payload){
	if (length > 0){
		LOG_ITEM_ASCII(ERROR, "Invalid GET TIME cmd, expected length = 0, actual = ", length);
	} else {
		LOG_ITEM_ASCII(INFO, "Valid GET TIME cmd", NO_PAYLOAD);
	}

}
