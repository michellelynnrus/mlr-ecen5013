#include "dma.h"

/**
 * Guidelines for programming the DMA:
 * 	1. TCDn initialized
 * 		-SARn loaded with source address
 * 		-DARn initialized with the dest address
 * 		-Configure DCRn[SSIZE,DSIZE,SINC,DINC,SMOD,DMOD]
 * 		-BCRn[BCR] must be loaded with total bytes to transfer
 * 		-DSRn[DONE] must be cleared
 * 	2. Start transfer
 * 		-DCRn[START] for SW request
 * 		-Peripheral request depends on status of DCRn[ERQ]
 *
 * If a termination occurs: read - DSRn[BES, DONE] will be set
 * 							write - DSRn[BED, DONE] will be set
 *
 * DMA Channel Operation:
 * 	1. Channel initialization
 * 		Transfer control descriptor (in channel registers) needs to be loaded with
 * 			-address pointers
 * 			-byte-transfer count
 * 			-control information
 * 		using accesses from the slave peripheral bus
 * 	2. Data transfer
 * 		DMA accepts requests for data transfers.
 * 		Upon receipt of a request, it provides address & bus control for the
 * 			transfers via master connection to the system bus and temp storage
 * 			for the read data
 * 		Channel performs one or more source read and dest write data transfers
 * 	3. Channel termination
 * 		After the operation is finished successfully or due to an error
 * 		Channel indicates the operation status in the channel's
 * 			-DMA Status Registers (DSRn)
 * 			-Byte Count Registers (BCRn)
 *
 */


/**************
* dma0_move()
**************/
int8_t dma0_move(uint8_t * src, uint8_t * dst, uint32_t length, uint8_t size){
	//currently only supports both ssize and dsize the same

	// Set source address register DMA_SAR0
	DMA_SAR0 = DMA_SAR_SAR(src);

	// Set dest address register DMA_DAR0
	DMA_DAR0 = DMA_DAR_DAR(dst);

	// Set byte count in register DMA_DSR_BCR0
	DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length);

	// Set source/destination size? SSIZE/DSIZE, DMA_DCR0 register
	// Source/dest increment? SINC/DINC, DMA_DCR0
	uint8_t sizeBits;
		switch (size) {
		case 32:
			sizeBits = 0x00;
			break;
		case 8:
			sizeBits = 0x01;
			break;
		case 16:
			sizeBits = 0x10;
			break;
		default:
			return -1; // invalid size
		}
	DMA_DCR0 = (DMA_DCR_SSIZE(size) | DMA_DCR_DSIZE(size));
	DMA_DCR0 |= (DMA_DCR_SINC_MASK | DMA_DCR_DINC_MASK);

	//Enable global interrupts
	__enable_irq();

	//Enable interrupts in NVIC
	NVIC_EnableIRQ(DMA0_IRQn);

	// set interrupt on completion of transfer EINT, DMA_DCR0 register
	// Start transfer, START, DMA_DCR0
	DMA_DCR0 |= DMA_DCR_EINT_MASK;
	DMA_DCR0 |= DMA_DCR_START_MASK;

	return 1;
}


extern void DMA0_IRQHandler(){
	//Check for errors in DMA_DCR0 register
	// CE = configuration error
	// BES = bus error on source
	// BED = bus error on dest
	if (DMA_DSR_BCR0 && DMA_DSR_BCR_CE_MASK){
		//LOG_ITEM(ERROR, 0xC, sizeof(uint8_t));
	}

	if (DMA_DSR_BCR0 && DMA_DSR_BCR_BES_MASK){
		//LOG_ITEM(ERROR, 0x1, sizeof(uint8_t));
	}

	if (DMA_DSR_BCR0 && DMA_DSR_BCR_BED_MASK){
		//LOG_ITEM(ERROR, 0x2, sizeof(uint8_t));
	}

	//LOG_ITEM(DATA_RECEIVED, 0xFF, sizeof(uint8_t));

	//Clear DONE (clears error bits)
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;

}



