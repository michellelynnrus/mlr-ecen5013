#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void) {
	
	// simple main function to print data type sizes
	printf("data type: \tbytes:\tbits:\n");
	printf("char \t\t%d\t%d\n", sizeof(char), sizeof(char)*8);
	printf("int \t\t%d\t%d\n", sizeof(int), sizeof(int)*8);
	printf("float \t\t%d\t%d\n", sizeof(float), sizeof(float)*8);
	printf("double \t\t%d\t%d\n", sizeof(double), sizeof(double)*8);
	printf("short \t\t%d\t%d\n", sizeof(short), sizeof(short)*8);
	printf("long \t\t%d\t%d\n", sizeof(long), sizeof(long)*8);
	printf("long int \t%d\t%d\n", sizeof(long int), sizeof(long int)*8);
	printf("long \t\t%d\t%d\n", sizeof(long long), sizeof(long long)*8);
	printf("int8_t \t\t%d\t%d\n", sizeof(int8_t), sizeof(int8_t)*8);
	printf("uint8_t \t%d\t%d\n", sizeof(uint8_t), sizeof(uint8_t)*8);
	printf("uint16_t \t%d\t%d\n", sizeof(uint16_t), sizeof(uint16_t)*8);
	printf("uint32_t \t%d\t%d\n", sizeof(uint32_t), sizeof(uint32_t)*8);
	printf("char *\t\t%d\t%d\n", sizeof(char *), sizeof(char *)*8);
	printf("int *\t\t%d\t%d\n", sizeof(int *), sizeof(int *)*8);
	printf("float *\t\t%d\t%d\n", sizeof(float *), sizeof(float *)*8);
	printf("void *\t\t%d\t%d\n", sizeof(void *), sizeof(void *)*8);
	printf("void **\t\t%d\t%d\n", sizeof(void **), sizeof(void **)*8);
	printf("int8_t *\t%d\t%d\n", sizeof(int8_t *), sizeof(int8_t *)*8);
	printf("int16_t *\t%d\t%d\n", sizeof(int16_t *), sizeof(int16_t *)*8);
	printf("int32_t *\t%d\t%d\n", sizeof(int32_t *), sizeof(int32_t *)*8);
	printf("size_t \t\t%d\t%d\n", sizeof(size_t), sizeof(size_t)*8);

	return 0;
}


