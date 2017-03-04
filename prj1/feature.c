#include "feature.h"




uint8_t findDuplicates(uint16_t * arrPtr, uint16_t len){
	
	for (uint8_t i = 0; i < len; i++){
		
		for (uint8_t j = i; j < len; j++){
			
			if(*(arrPtr+i) == *(arrPtr+j)){
				return 1;
			}
			
		}
		
	}
	
	return 0;
}