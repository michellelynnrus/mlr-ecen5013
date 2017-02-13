#include "data.h"
#include "memory.h"
#include "project_1.h"

int main(void){
	
#if (PROJECT==1)
	//Only call project_1_report() if compile time switch is defined as project 1
	project_1_report();
#else
	//Future projects go here
	//Compile time switch can be defined as 2, 3, etc to specify different projects
#endif
	
	return 0;
}