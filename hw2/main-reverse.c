#include <stdio.h>
#include <stdlib.h>

char reverse(char * str, int length){
	char * newStrPtr = malloc(length);
	if (length <= 0) {
		//return non-zero code indicating failure, in this case length must be nonzero
     		return 1; 
	}
	//copy the array
	for(int i = 0; i < length; i++){
		*newStrPtr = *str;
		newStrPtr++;
		str++;
	}
	
	//reverse and save back to original array address
	str-=length;
	for (int j = 0; j < length; j++){
		newStrPtr--;
		*str = *newStrPtr;
		str++;
	}
	return 0;
}

int main(void) {
	char blah[8] = "reverse!";
	printf("START: %s\n", blah);
	reverse(blah, 8);
	printf("END: %s\n", blah);
	return 0;
}

