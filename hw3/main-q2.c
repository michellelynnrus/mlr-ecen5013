#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void ptrQuestion(void){
	unsigned char origData[8] = {0xEE, 0x12, 0x77, 0xBE, 0x66, 0x54, 0x33, 0xF0};

	unsigned char * ptr = origData;

	
	/*printf("Dumping original table...\n");
	printf("ADDR: \tNewData:\n");
	for (int i = 0; i < 8; i++){
		//ptr++, startAddress+offset simulates 100+index
		printf("%d \t0x%02x\n", (100+i), *ptr++);
	}
	ptr = origData;*/

	*ptr = 0xF1 & 127;
	ptr++;

	*ptr += 17;
	ptr += 2;

	*ptr = 15 % 4;
	ptr--;

	*ptr >>= 4;
	ptr = (char *)(origData + 5); //not actually address 105, rather 5 offset of start addr

	*ptr = (1<<5)|(4<<2);
	*((char *)(origData + 7)) = 22; //not actually address 107, rather 7 offset of start addr
	
	ptr = origData;

	printf("Dumping updated table...\n");
	printf("ADDR: \tNewData:\n");
	for (int i = 0; i < 8; i++){
		//ptr++, startAddress+offset simulates 100+index
		printf("%d \t0x%02x\n", (100+i), *ptr++);
	}
	return;
}

void main(){
  ptrQuestion();
  return;
}
