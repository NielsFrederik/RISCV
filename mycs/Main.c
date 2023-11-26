#include <stdio.h>
#include <stdint.h>
#include "fetch.h"
#include "Typedef2.h"
#include "ALU.h"


int main( int argc, char *argv[] ) {
	if(argc < 2 ) {
	//exit the program if a argument was not given.
		printf("file name not supplied");
		return -1;
	}
    readFile_t myFile;
    const char* inputFilePath = argv[1]; //uses the terminal input as the filename.

    if (fetchData(inputFilePath, &myFile) == 0) {
       // Successfully fetched the data

       // Access myFile.data and myFile.size here
        for (size_t i = 0; i < myFile.size; ++i) {

        }

    } else {
        // Error handling
    }

	CPU_t CPU;
	initCPU(&CPU);
	if (myFile.size*4<0x100000){ //reading instructions and data into the memory.
		for(int i=0; i<myFile.size; i++){
			CPU.mem[(4*i)+0]=myFile.data[i]&0x000000ff;
			CPU.mem[(4*i)+1]=(myFile.data[i]&0x0000ff00)>>8;
			CPU.mem[(4*i)+2]=(myFile.data[i]&0x00ff0000)>>16;
			CPU.mem[(4*i)+3]=(myFile.data[i]&0xff000000)>>24;
		}
	}

	int runner =1; //variable to be able to stop the program incase of a ecall 10.
	while(runner){
	if (CPU.pc>=0 && CPU.pc<myFile.size) //makes sure it is reading from inside the data array.
		runner=ALU(&CPU, myFile.data[CPU.pc]); //the ALU takes the instruction as input.
	else{
		printf("index out of bounds %d", CPU.pc); //if the program counter is outside the valid area the program stops.
		return 0;
	}


	CPU.pc+=1;
	}
	for(int i=0; i < 32; i+=4){
		for(int j=0; j<4; j++)
			printf("x%d\t= %08x,\t", i+j , CPU.regs[i+j]); //prints all the registers in a a 4X8 matrix.
		printf("\n");
	}

    return 0;
}
