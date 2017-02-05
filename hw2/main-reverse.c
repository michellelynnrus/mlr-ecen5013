#include <stdio.h>
#include <stdlib.h>

char reverse(char * str, int length){
	char * newStrPtr = str + length - 1;
	char tempChar;	
	
	if (length <= 0) {
		//return non-zero code indicating failure, in this case length must be nonzero and positive
     		return 1; 
	}

	//Loop through the array and swap first/last char
	//Repeat until we meet in the middle
	for(int i = 0; i < length/2; i++){
		tempChar = *str;
		*str = *newStrPtr;
		*newStrPtr = tempChar;

		str++;
		newStrPtr--;

	}
	
	return 0;
}

void printAsHex(char * str, int length){
	for (int i = 0; i < length; i++){
		printf("%x",*str);
		str++;
	}
	printf("\n");
}

void printAsString(char*str, int length){
	for (int i = 0; i < length; i++){
		if(*str == '\n'){	
			printf("\\n");
		} else if (*str == '\t'){
			printf("\\t");
		} else if (*str == '\0'){
			printf("\\0");
		} else {
			printf("%c", *str);
		}
		str++;
	}
	printf("\n");

}

void reverseAndPrint(char * str, int length){

	printf("Reversing str: ");
	printAsString(str, length);
	printf("\t");
	printAsHex(str, length);

	reverse(str, length);

	printf("Reversed: ");
	printAsString(str, length);
	printf("\t");
	printAsHex(str, length);

	printf("\n");
}
int main(void) {
	//char blah[8] = "reverse!";

	char str1[17] = "This is a string.";
	reverseAndPrint(str1, 17);

	char str2[18] = "some NUMmbers12345";
	reverseAndPrint(str2, 18);

	char str3[30] = "Does it reverse \n\0\t correctly?";
	reverseAndPrint(str3, 30);
	return 0;
}


