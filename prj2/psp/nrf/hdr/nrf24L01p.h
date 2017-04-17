#ifndef __NRF24L01P_H__
#define __NRF24L01P_H__


// DEFINE SPI COMMANDS HERE
#define NRF_CMD_R_REG 				0x00 // Read command - should be orred with 5 bit reg address
#define NRF_CMD_W_REG	 			0x20 // Write command - should be orred with 5 bit reg address
#define NRF_CMD_R_RX_PAYLOAD 		0b01100001
#define NRF_CMD_W_TX_PAYLOAD 		0b10100000
#define NRF_CMD_FLUSH_TX 			0b11100001
#define NRF_CMD_FLUSH_RX 			0b11100010
#define NRF_CMD_REUSE_TX_PL 		0b11100011
#define NRF_CMD_R_RX_PL_WID			0b01100000
#define NRF_CMD_W_ACK_PAYLOAD_MASK	0b10101000 // or with 3 bit pipe ID
#define NRF_CMD_W_TX_PAYLOAD_NO_ACK 0b10110000
#define NRF_CMD_NOP					0b11111111 // No operation, use to read status


// DEFINE REGISTER ACCESS MACROS HERE
// Register Addresses
#define NRF_CONFIG		0x00
#define NRF_EN_AA		0x01 // For Enhanced ShockBurst
#define NRF_EN_RXADDR 	0x02
#define NRF_SETUP_AW	0x03
#define NRF_SETUP_RETR	0x04
#define NRF_RF_CH		0x05
#define NRF_RF_SETUP	0x06
#define NRF_STATUS		0x07
#define NRF_OBSERVE_TX	0x08
#define NRF_RPD			0x09
#define NRF_RX_ADDR_P0	0x0A
#define NRF_RX_ADDR_P1	0x0B
#define NRF_RX_ADDR_P2	0x0C
#define NRF_RX_ADDR_P3	0x0D
#define NRF_RX_ADDR_P4	0x0E
#define NRF_RX_ADDR_P5	0x0F
#define NRF_TX_ADDR		0x10
#define NRF_RX_PW_P0	0x11
#define NRF_RX_PW_P1	0x12
#define NRF_RX_PW_P2	0x13
#define NRF_RX_PW_P3	0x14
#define NRF_RX_PW_P4	0x15
#define NRF_RX_PW_P5	0x16
#define NRF_FIFO_STATUS	0x17
#define NRF_DNYPD		0x1C

// CONFIG REG BITMASKS
#define NRF_RX_DR_MASK	0x40
#define NRF_TX_DS_MASK	0x20
#define NRF_MAX_RT_MASK	0x10
#define NRF_EN_CRC_MASK		0x08
#define NRF_CRCO_MASK			0x04
#define NRF_PWR_UP_MASK		0x02
#define NRF_PRIM_RX_MASK		0x01

// EN_AA, EN_RXADDR PIPE BITMASKS
#define NRF_P5_MASK	0x02
#define NRF_P4_MASK	0x01
#define NRF_P3_MASK	0x08
#define NRF_P2_MASK	0x04
#define NRF_P1_MASK	0x02
#define NRF_P0_MASK	0x01

// STATUS BITS
#define NRF_RX_DR_MASK	0x40
#define NRF_TX_DS_MASK	0x20
#define NRF_MAX_RT_MASK	0x10
#define NRF_RX_P_NO_MASK	0x0E
#define NRF_TX_FULL_MASK	0x01



#endif /*__NRF24L01P_H__*/
