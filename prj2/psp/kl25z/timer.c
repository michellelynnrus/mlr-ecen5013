#include "timer.h"

/**************
* upCounter_init()
**************/
int32_t upCounter_init(void){
	//Enable the clocks
	//Set UART0 clock source to MCGFLLCLK or MCGPLLCLK/2 clock option
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0x1);

	//Turn on the clk gate (SIM)
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;

	//Initialize counter value TPM0_CNT = 0
	TPM0_CNT = TPM_CNT_COUNT(0);

	//Set Modulo TPM0_MOD = ?
	TPM0_MOD = 0x7FFF;

	//TPM0_SC
	//Enable timer overflow interrupt TOIE = 1
	//Up counting mode CPWMS = 0
	TPM0_SC = TPM_SC_TOIE_MASK;

	//Enable global interrupts
	__enable_irq();

	//Enable interrupts in NVIC
	NVIC_EnableIRQ(TPM0_IRQn);

	//Enable counter: Clock mode on every LPTPM counter clock CMOD = 01
	TPM0_SC |= (TPM_SC_CMOD(0x01) | TPM_SC_PS(0b100));

	//Enable PWM I think - Edge-aligned PWM
	TPM0_C0SC |= (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK);
	return 1;
}

/**************
* upCounter_init()
**************/
uint16_t upCounter_getCount(void){

	uint16_t count = (uint16_t)(TPM0_CNT & TPM_CNT_COUNT_MASK);

	return count;
}

void pwm_init(void){
	//Enable the clocks
	//Turn on the clk gate (SIM)
	SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK;

	//Initialize counter value TPM0_CNT = 0
	TPM2_CNT = TPM_CNT_COUNT(0);

	//Set Modulo TPM0_MOD = ?
	TPM2_MOD = 0x7FFF;

	//TPM0_SC
	//Enable timer overflow interrupt TOIE = 1
	//Up counting mode CPWMS = 0
	//TPM2_SC = TPM_SC_TOIE_MASK;

	//Enable global interrupts
	__enable_irq();

	//Enable interrupts in NVIC
	NVIC_EnableIRQ(TPM0_IRQn);

	//Enable counter: Clock mode on every LPTPM counter clock CMOD = 01
	TPM2_SC |= (TPM_SC_CMOD(0x01) | TPM_SC_PS(0b100));

	//Enable PWM I think - Edge-aligned PWM
	TPM2_C0SC |= (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK);
	TPM2_C1SC |= (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK);

	pwm_setRedBrightness(0);
	pwm_setGreenBrightness(0);
}
void pwm_setRedBrightness(uint16_t brightPercent){
	TPM2_C0V = TPM2_MOD * brightPercent / 100;
}

void pwm_setGreenBrightness(uint16_t brightPercent){
	TPM2_C1V =  TPM2_MOD * brightPercent / 100;
}

extern void TPM0_IRQHandler(){
	//Toggle red LED
	//GPIOB_PTOR = (1 << 18);
	//Clear TOF (clears error bits)
	TPM0_SC |= TPM_SC_TOF_MASK;

}
extern void TPM2_IRQHandler(){
	//Toggle red LED
	//GPIOB_PTOR = (1 << 18);
	//Clear TOF (clears error bits)
	if(TPM2_SC && TPM_SC_TOF_MASK){
		TPM2_SC |= 0xFFFF;
	}
}
