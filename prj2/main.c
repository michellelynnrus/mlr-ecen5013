#include "data.h"
#include "memory.h"
#include "project_1.h"
#include "project_2.h"
#include "project_3.h"
#include "project_4.h"

#define PROJECT 4

int main(void){
	
#if (PROJECT==1)
	//Only call project_1_report() if compile time switch is defined as project 1
	project_1_report();
#elif (PROJECT==2)
	project_2_report();
#elif (PROJECT==3)
	project_3_report();
#elif (PROJECT==4)
	project_4_report();
#else
	//Future projects go here
	//Compile time switch can be defined as 2, 3, etc to specify different projects
#endif
	
	return 0;
}
