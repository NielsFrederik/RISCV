#include <stdio.h>
#include <stdint.h>

#include "fetch.h"
#include "Typedef2.h"
#include "ALU.h"


/*int main() {

	CPU_t CPU;
	initCPU(&CPU);
	int opcode	= 0b0010011;
	int rd	 	= 0b00001<<7;
	int f3		= 0b001<<12;
	int rs1		= 0b00001<<15;
	int imm		= 0b00000000001<<20;
	int testvalue = 0x00200093; //adddi 2 reg 2?
	int testvalue2 = opcode+rd+f3+rs1+imm;
	int testvalues[] = {testvalue, testvalue2};

	printf("Initialized registers: \n");
	for(int i=0; i < 4; i++){
		printf("Reg%d %d\n", i , CPU.regs[i]);
	}


	printf("After a single instruction: \n");
	ALU(&CPU, testvalues[0]);
	printf("Initialized registers: \n");
		for(int i=0; i < 4; i++){
			printf("Reg%d %d\n", i , CPU.regs[i]);
		}
		ALU(&CPU, testvalues[1]);
		printf("Initialized registers: \n");
			for(int i=0; i < 4; i++){
				printf("Reg%d %d\n", i , CPU.regs[i]);
			}
	printf("pc is: %d", CPU.pc);
}
*/

int main() {
    readFile_t myFile;
    const char* inputFilePath = "N:/Downloads/addlarge.bin";

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

	//int testvalues[] = myFile.data;

	printf("Initialized registers: \n");
	for(int i=0; i < 32; i++){
		printf("Reg%d %08x\n", i , CPU.regs[i]);
	}

	for (int j=0; j<7; j++){
	printf("After instruction:%d \n", j);
	ALU(&CPU, myFile.data[j]);
	printf("Initialized registers: \n");
		for(int i=0; i < 32; i++){
			printf("Reg%d %08x\n", i , CPU.regs[i]);
		}
	}

    return 0;
}
