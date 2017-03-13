#include "uart.h"
#include "psp_macros_log.h"

//#define UART_INT
#define SYS_CLK (20970000)
#define OSR (15)
#define BUF_SIZE (128)

#ifdef UART_INT
//Pointers to TX/RX circular buffers
CB_t * p_uart_TXbuf;
CB_t * p_uart_RXbuf;
#endif

UART_Status_t uart_configure(uint64_t baudRate){
	UART_Status_t uartStat = UART_OK;

	//Enable the clocks
	//Set UART0 clock source to MCGFLLCLK or MCGPLLCLK/2 clock option
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(0x1);

	//Turn on the clk gate (SIM)
	SIM_SCGC4 |= SIM_SCGC4_UART0(0x1);

	//Config peripheral (Peripheral)

	//Set PORTA pin 1 to ALT2 (UART0_TX)
	PORTA_PCR1 = PORT_PCR_MUX(0x2);

	//Set PORTA pin 2 to ALT2 (UART0_RX)
	PORTA_PCR2 = PORT_PCR_MUX(0x2);

	//Calculate and set baud rate divisor
	uint16_t obr = (uint16_t)(SYS_CLK / ((OSR + 1) * baudRate));
	UART0_BDH |= UART_BDH_SBR(obr >> 8);
	UART0_BDL |= UART_BDL_SBR(obr);

	//Enable TX/RX
	UART0_C2 = UART_C2_RE(1) | UART_C2_TE(1);

#ifdef UART_INT
	//Allocate circular buffers
	CB_Status_t txBufStatus = CB_Allocate((CB_t **)&p_uart_TXbuf, BUF_SIZE);
	CB_Status_t rxBufStatus = CB_Allocate((CB_t **)&p_uart_RXbuf, BUF_SIZE);

	if (txBufStatus != CB_OK || rxBufStatus != CB_OK){
		//there has been an error
		//you should probably handle this, Michelle from the future
		uartStat = UART_BUF_ERR;
	} else {

		//Enable global interrupts
		__enable_irq();

		//Enable interrupts in NVIC
		NVIC_EnableIRQ(UART0_IRQn);

		//Enable UART TX/RX interrupts
		//UART0_C2 |= (UART_C2_TIE(1) | UART_C2_RIE(1));
		UART0_C2 |= UART_C2_RIE(1);
	}
#endif

	return uartStat;
}

UART_Status_t uart_send_byte(uint8_t byte){
	UART_Status_t uartStat = UART_OK;
#ifdef UART_INT
	//while (CB_Full(p_TXbuf) == FULL);
		CB_Status_t bufStat = CB_AddItem(p_uart_TXbuf, byte);
		if(bufStat != CB_OK){
			//handle this error, probably
			uartStat = UART_BUF_ERR;
		} else {
			UART0_C2 |= UART_C2_TIE_MASK;
		}

#else
	//Poll the TDRE flag
	while(!(UART0_S1 & UART0_S1_TDRE_MASK));

	//Set UART0 data register to pointer data
	UART0_D = byte;
#endif
	return uartStat;
}

UART_Status_t uart_send_byte_n(uint8_t * bytes, uint8_t n){

	UART_Status_t uartStat = UART_OK;

	if (!bytes){
		uartStat = UART_NULLPTR;
	} else {
#ifdef UART_INT
		CB_Status_t bufStat = CB_OK;
		uint8_t statFlg = 1;

		for (uint8_t i = 0; i < n; i++){
			//while (CB_Full(p_TXbuf) == FULL);
			bufStat = CB_AddItem(p_uart_TXbuf, *(bytes+i));
			if(bufStat != CB_OK){
				//handle this error, probably
				uartStat = UART_BUF_ERR;
				statFlg = 0;
			}
		}
		if (statFlg == 1){
			UART0_C2 |= UART_C2_TIE_MASK;
		}
#else

		for (uint8_t i = 0; i < n; i++){
			uart_send_byte(*(bytes+i));
		}
#endif
	}
	return uartStat;
}

UART_Status_t uart_receive_byte(uint8_t * byte){
	UART_Status_t uartStat = UART_OK;

	if (!byte){
		uartStat = UART_NULLPTR;
	} else {
#ifdef UART_INT
		//while (CB_Empty(p_TXbuf) == EMPTY);
		CB_Status_t bufStat = CB_RemoveItem(p_uart_RXbuf, byte);
		if(bufStat == CB_OK){
			//not empty, no error = have data
			LOG_ITEM(DATA_RECEIVED, byte, sizeof(uint8_t));
			UART0_C2 |= UART_C2_RIE_MASK;
		} else if (bufStat != CB_EMPTY) {
			//not OK, not EMPTY, handle this error, probably
			uartStat = UART_BUF_ERR;
		} else {
			// do nothing if empty
			uartStat = UART_NODATA;
		}

#else
		//Poll the RDRF flag
		while (!(UART0_S1 & UART0_S1_RDRF_MASK));

		//Store data from UART0 data register in data ptr
		*byte = (uint8_t)UART0_D;

		LOG_ITEM(DATA_RECEIVED, byte, sizeof(uint8_t));
#endif

	}

	return uartStat;
}

#ifdef UART_INT
extern void UART0_IRQHandler(){
	CB_Status_t bufStat = CB_OK;
	uint8_t byte;

	//check TX interrupt
	if ((UART0_S1 & UART_S1_TDRE_MASK) && (CB_Empty(p_uart_TXbuf) != CB_EMPTY)) {
		bufStat = CB_RemoveItem(p_uart_TXbuf, &byte);
		UART0_D = byte;

		//disable the interrupt until we request a send
		if (CB_Empty(p_uart_TXbuf) == CB_EMPTY) {
			UART0_C2 &= ~UART_C2_TIE_MASK;
		}
	}

	//check RX interrupt
	if ((UART0_S1 & UART_S1_RDRF_MASK) && (CB_Full(p_uart_RXbuf) != CB_FULL)) {
		byte = UART0_D;
		bufStat = CB_AddItem(p_uart_RXbuf, byte);

		//disable the interrupt until we request a receive
		if(CB_Full(p_uart_RXbuf) == CB_FULL){
			UART0_C2 &= ~UART_C2_RIE_MASK;
		}
	}

	if (bufStat != CB_OK){
		//handle this somehow maybe possibly
	}
}
#endif
