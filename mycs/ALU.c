/*
 * ALU.c
 *
 *  Created on: 13. nov. 2023
 *      Author: oscar
 */
#include "Typedef2.h"
#include "ALU.h"
#include "stdio.h"

int ALU(CPU_t* CPU, int testvalue){

	int inst = testvalue;

	int opcode = inst & 0b1111111;
	int rd = (inst >> 7) & 0b11111;

	int rs1 = (inst >> 15) & 0b11111;
	int rs2 = (inst >> 20) & 0b11111;

	int imm_I = (inst >> 20);
	//int imm_B = ((inst & 0x80000000) >> 19) | ((inst & 0x80) << 4) | ((inst >> 20) & 0x7e0) | ((inst >> 7 ) & 0x1e) ;
	//int imm_J = ((inst & 0x80000000) >> 11) | ((inst & 0xff000)) | ((inst >> 9) & 0x800) | ((inst >> 20 ) & 0x7f3) ;
	int imm_U = ((inst & 0b11111111111111111111000000000000));
	int imm_S = (((unsigned int)(inst&0b10000000000000000000000000000000)>>19)+((unsigned int)(inst&0b01111110000000000000000000000000)>>20)+((unsigned int)(inst&0b00000000000000000000111100000000)>>7)+((unsigned int)(inst&0b00000000000000000000000010000000)<<4))+ 0b11111111111111111110000000000000;

	int funct3 = (inst >> 12) & 0x7 ;
	int funct7 = (inst >> 25) & 0x7f;


	switch (opcode) {
		case 0b0010011: //Opcode
			switch (funct3) {
				case 0: //addi
					CPU->regs[rd] = CPU->regs[rs1] + imm_I;
					break;
				case 1: //slii
					CPU->regs[rd] = CPU->regs[rs1]<< imm_I;
					break;
				case 2:
					//slti
					CPU->regs[rd] = (CPU->regs[rs1]-imm_I)<0? 1:0;
					break;
				case 3:
					//sltiu
					CPU->regs[rd] = (CPU->regs[rs1]) < (imm_I) ? 1:0;
					break;

				case 4:
					//xori
					CPU->regs[rd] = CPU->regs[rs1] ^ imm_I;
					break;

				case 5:
					switch (funct7){
						case 0:
							//srli
							CPU->regs[rd] = CPU->regs[rs1] >> imm_I ;
							break;
						case 0b0100000:
							//srai
							CPU->regs[rd] =(signed int) CPU->regs[rs1] >> imm_I;
							break;
						default:
							break;
					}
					break;

				case 6:
					//ori
					CPU->regs[rd] = CPU->regs[rs1] | imm_I;
					break;

				case 7:
					//andi
					CPU->regs[rd] = CPU->regs[rs1] & imm_I;
					break;
				default:
					//printf("du grim");
					break;

		}
		break;

		default:
			//printf("du grim");
		break;

		case 0b0110111:
			CPU->regs[rd] = imm_U;
			break;
		case 0b0110011:
			switch (funct3){
				case 0:
					//add & sub
					switch(funct7){
						case 0: //
							CPU->regs[rd] = CPU->regs[rs1] + CPU->regs[rs2];
							break;
						case 0b0100000:
							CPU->regs[rd] = CPU->regs[rs1] - CPU->regs[rs2];
							break;
					}
					break;

				case 0b001: //sll
					CPU->regs[rd]= CPU->regs[rs1] << CPU->regs[rs2];
					break;

				case 0b010:
					//slt
					CPU->regs[rd] = (CPU->regs[rs1]<CPU->regs[rs2])? 1:0;
					break;
				case 0b011:
					//sltu
					CPU->regs[rd] = (CPU->regs[rs1]) < (CPU->regs[rs2]) ? 1:0;
					break;
				case 0b100:
					//xor
					CPU->regs[rd] = CPU->regs[rs1] ^ CPU->regs[rs2];
					break;
				case 0b101:
					switch(funct7){
					case 0b0000000: //srl
						CPU->regs[rd] = CPU->regs[rs1] >> CPU->regs[rs2];
						break;
					case 0b0100000: //sra
						CPU->regs[rd] = (signed int) CPU->regs[rs1] >> CPU->regs[rs2];
						break;
					}
					break;
				case 0b110://or
					CPU->regs[rd] = CPU->regs[rs1] | CPU->regs[rs2];
					break;
					case 0b111://and
					CPU->regs[rd] = CPU->regs[rs1] & CPU->regs[rs2];
					break;
			}
			break;
		case 0b1100011:
			switch(funct3){
				case 0b001: //bne
					CPU->pc = CPU->regs[rs1] != CPU->regs[rs2]? CPU->pc+(imm_S/4)-1 : CPU->pc;
					break;
				case 0b100: //blt
					CPU->pc = CPU->regs[rs1] < CPU->regs[rs2]? CPU->pc+(imm_S/4)-1 : CPU->pc;
					break;
			}
			break;
		case 0b1110011:
			switch (funct3){
				case 0:
					printf("Program exited with code: 0 \n");
					return 0;
					break;
			}
			break;

	}
	return 1;
}

