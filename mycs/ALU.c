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
	//int imm_S = ((inst & 0xfe000000 >> 20)) | ((inst >> 7) & 0x1f);

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
					break;
				case 3:
					//sltiu
					break;

				case 4:
					//xori
					CPU->regs[rd] = CPU->regs[rs1] ^ imm_I;
					break;

				case 5:
					switch (funct7){
						case 0:
							//srli
							break;
						case 32:
							//srai
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
					//add
					CPU->regs[rd] = CPU->regs[rs1] + CPU->regs[rs2];
					break;
				case 0b100:
					//xor
					CPU->regs[rd] = CPU->regs[rs1] ^ CPU->regs[rs2];
					break;
				case 0b110://or
					CPU->regs[rd] = CPU->regs[rs1] | CPU->regs[rs2];
					break;
					case 0b111://add
					CPU->regs[rd] = CPU->regs[rs1] & CPU->regs[rs2];
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

