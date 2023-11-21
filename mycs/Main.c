#include <stdio.h>
#include <stdint.h>

#include "fetch.h"
#include "Typedef2.h"
#include "ALU.h"



int main() {
    readFile_t myFile;
    const char* inputFilePath = "N:/Downloads/string.bin";

    if (fetchData(inputFilePath, &myFile) == 0) {
       // Successfully fetched the data

       // Access myFile.data and myFile.size here
        for (size_t i = 0; i < myFile.size; ++i) {
           printf("%d   %08x ,opcode: %02x ,regD: %02x, f3: %01x, udecide %05x \n", i, myFile.data[i] , myFile.data[i] & 0b1111111,myFile.data[i]>>7 & 0b11111,  myFile.data[i]>>12 & 0b111 , myFile.data[i]>>12);

            // You can store the values in your desired array in the main function
            // For example, if you have an array in the main function: uint32_t myArray[MAX_SIZE];
            // myArray[i] = myFile.data[i];
        }

        // Don't forget to free the allocated memory when you're done with it
       // free(myFile.data);
    } else {
        // Error handling
    }
	CPU_t CPU;
	initCPU(&CPU);


	printf("Initialized registers: \n");
	for(int i=0; i < 32; i++){
		printf("Reg%d %08x\n", i , CPU.regs[i]);
	}
	int runner =1;
	int runcount=0;
	while(runner){
	printf("After instruction:%x \n", CPU.pc*4);
	if (CPU.pc>=0 && CPU.pc<myFile.size)
		runner=ALU(&CPU, myFile.data[CPU.pc]);
	else{
		printf("index out of bounds bro %d", CPU.pc);
		return 0;
	}


	CPU.pc+=1;
	if (runcount ==1288)
		printf("lets look");
	runcount+=1;
	}
	for(int i=0; i < 32; i++)
			printf("Reg%d %08x\n", i , CPU.regs[i]);
    return 0;
}
