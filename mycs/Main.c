#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "CPUtype.h"
#include "Processor.h"


int main( int argc, char *argv[] ) {
	if(argc < 2 ) {
	//exit the program if a argument was not given.
		printf("file name not supplied");
		return -1;
	}
    const char* inputFilePath = argv[1]; //uses the terminal input as the filename.
	uint32_t filesize;
	FILE* inputFile = fopen(inputFilePath, "rb");
	// Find the size of the file
        fseek(inputFile, 0, SEEK_END); //puts the file cursor at the end of the file.
        size_t fileSize = ftell(inputFile); //then puts the cursor position into "fileSize"
        fseek(inputFile, 0, SEEK_SET);  //puts the cursor back at 0.

        //adjust for uint32 type is 4 bytes.
        filesize = fileSize >> 2;

        // Allocating the array in memory.
        uint32_t * Data = (uint32_t*)malloc(fileSize);
		fread(Data, sizeof(uint32_t), filesize, inputFile);

	CPU_t CPU;
	CPU.pc = 0; //initilzing the CPU.
	for (int i = 0; i <  32; i++) 
		CPU.regs[i] = 0;
	
	if (filesize*4<0x100000){ //reading instructions and data into the memory.
		for(int i=0; i<filesize; i++){
			CPU.mem[(4*i)+0]=Data[i]&0x000000ff;
			CPU.mem[(4*i)+1]=(Data[i]&0x0000ff00)>>8;
			CPU.mem[(4*i)+2]=(Data[i]&0x00ff0000)>>16;
			CPU.mem[(4*i)+3]=(Data[i]&0xff000000)>>24;
		}
	}

	int runner =1; //variable to be able to stop the program incase of a ecall 10.
	while(runner){
	if (CPU.pc>=0 && CPU.pc<filesize*4){ //makes sure it is reading from inside the data array.
		uint32_t instruction = CPU.mem[(CPU.pc)+0]+(CPU.mem[(CPU.pc)+1]<<8)+(CPU.mem[(CPU.pc)+2]<<16)+(CPU.mem[(CPU.pc)+3]<<24); //reads the instruction from the memory.
		runner=Processor(&CPU, instruction); //the ALU takes the instruction as input.
	}
	else{
		printf("index out of bounds %d", CPU.pc); //if the program counter is outside the valid area the program stops.
		return 0;
	}


	CPU.pc+=4;
	}
	for(int i=0; i < 32; i+=4){
		for(int j=0; j<4; j++)
			printf("x%d\t= %08x,\t", i+j , CPU.regs[i+j]); //prints all the registers in a a 4X8 matrix.
		printf("\n");
	}

	//write all CPU.Regs to a file.res.
	FILE* outputFile = fopen("outputregisters.res", "wb");
	for(int i=0; i<32; i++){
		uint32_t temp = CPU.regs[i];
		uint8_t t1 = temp & 0b11111111;
		uint8_t t2 = temp>>8 & 0b11111111;
		uint8_t t3 = temp>>16 & 0b11111111;
		uint8_t t4 = temp>>24 & 0b11111111;
		fwrite(&t1, sizeof(uint8_t), 1, outputFile);
		fwrite(&t2, sizeof(uint8_t), 1, outputFile);
		fwrite(&t3, sizeof(uint8_t), 1, outputFile);
		fwrite(&t4, sizeof(uint8_t), 1, outputFile);
	}
	fclose(outputFile);
	//where is the output file?

    return 0;
}
