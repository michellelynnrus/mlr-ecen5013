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
int main(void) {
	char blah[8] = "reverse!";

	char str1[17] = "This is a string.";
	printf("Reversing:\t '%s'\n",str1);
	reverse(str1,17);
	printf("\t\t '%s'\n",str1);

	char str2[18] = "some NUMmbers12345";
	printf("Reversing:\t '%s'\n",str2);
	reverse(str2,18);
	printf("\t\t '%s'\n",str2);

	char str3[30] = "Does it reverse \n\0\t correctly?";
	printf("Reversing:\t '%s'\n",str3);
	reverse(str3,30);
	printf("\t\t '%s'\n",str3);
	return 0;
}


