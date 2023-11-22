#include "Typedef2.h"
#include "ALU.h"
#include "stdio.h"

int ALU(CPU_t* CPU, int testvalue){

	CPU->regs[0] = 0;
	int inst = testvalue;

	int opcode = inst & 0b1111111;
	int rd = (inst >> 7) & 0b11111;

	int rs1 = (inst >> 15) & 0b11111;
	int rs2 = (inst >> 20) & 0b11111;

	int imm_I = (inst >> 20);
	int imm_S = (signed int)((inst >>20)&0b11111111111111111111111111100000)|(unsigned int)((inst&0b00000000000000000000111110000000)>>7);
	//int imm_B = ((inst & 0x80000000) >> 19) | ((inst & 0x80) << 4) | ((inst >> 20) & 0x7e0) | ((inst >> 7 ) & 0x1e) ;
	//int imm_J = ((inst & 0x80000000) >> 11) | ((inst & 0xff000)) | ((inst >> 9) & 0x800) | ((inst >> 20 ) & 0x7f3) ;
	int imm_U = (inst & 0b11111111111111111111000000000000);
	int imm_UJ= ((signed int)(inst&0b10000000000000000000000000000000)>>15)|(signed int)((inst&0b01111111111000000000000000000000)>>20)|(signed int)((inst&0b00000000000100000000000000000000)>>9)|(signed int)((inst&0b000000000000111111110000000000));
	int imm_SB = (((signed int)(inst&0b10000000000000000000000000000000)>>19)+((unsigned int)(inst&0b01111110000000000000000000000000)>>20)+((unsigned int)(inst&0b00000000000000000000111100000000)>>7)+((unsigned int)(inst&0b00000000000000000000000010000000)<<4));

	int funct3 = (inst >> 12) & 0x7 ;
	int funct7 = (inst >> 25) & 0x7f;


	switch (opcode) {
		case 0b0000011:
			switch (funct3) {
				case 0b000: //lb
					CPU->regs[rd]= (signed int)((CPU->mem[CPU->regs[rs1]+imm_I])<<24)>>24;
					break;
				case 0b001: //lh
					CPU->regs[rd]= ((signed int)((CPU->mem[CPU->regs[rs1]+imm_I+1])<<24)>>16) | ((CPU->mem[CPU->regs[rs1]+imm_I]));
					break;
				case 0b010: //lw
					CPU->regs[rd]= ((CPU->mem[CPU->regs[rs1]+imm_I+3])<<24) + ((CPU->mem[CPU->regs[rs1]+imm_I+2])<<16)+((CPU->mem[CPU->regs[rs1]+imm_I+1])<<8) + (CPU->mem[CPU->regs[rs1]+imm_I+0]);
					break;
				case 0b100: //lbu
					CPU->regs[rd]= CPU->mem[CPU->regs[rs1]+imm_I];
					break;
				case 0b101: //lhu
					CPU->regs[rd]= ((CPU->mem[CPU->regs[rs1]+imm_I+1])<<8) | ((CPU->mem[CPU->regs[rs1]+imm_I]));
			}
			break;
		case 0b0010011: //Opcode
			switch (funct3) {
				case 0: //addi
					CPU->regs[rd] = CPU->regs[rs1] + imm_I;
					break;
				case 1: //slli
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
					break;

		}
		break;

		break;
		case 0b0100011: //S opcode
			switch(funct3){
				case 0b000://sb
					CPU->mem[CPU->regs[rs1]+imm_S]=CPU->regs[rs2]&0b00000000000000000000000011111111;
					break;
				case 0b001://sh
					CPU->mem[CPU->regs[rs1]+imm_S]=CPU->regs[rs2]&  0b00000000000000000000000011111111;
					CPU->mem[CPU->regs[rs1]+imm_S+1]=(CPU->regs[rs2]&0b00000000000000001111111100000000)>>8;
					break;
				case 0b010://sw
					CPU->mem[CPU->regs[rs1]+imm_S]=CPU->regs[rs2]&  0b00000000000000000000000011111111;
					CPU->mem[CPU->regs[rs1]+imm_S+1]=(CPU->regs[rs2]&0b00000000000000001111111100000000)>>8;
					CPU->mem[CPU->regs[rs1]+imm_S+2]=(CPU->regs[rs2]&0b00000000111111110000000000000000)>>16;
					CPU->mem[CPU->regs[rs1]+imm_S+3]=(CPU->regs[rs2]&0b11111111000000000000000000000000)>>24;
					break;
			}
			break;
		case 0b0110011:
			switch (funct3){
				case 0:
					//add & sub
					switch(funct7){
						case 0: //add
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
					CPU->regs[rd] = (CPU->regs[rs1]<CPU->regs[rs2])? 1:0; //de kan da ikke være det samme
					break;
				case 0b011:
					//sltu
					CPU->regs[rd] = (CPU->regs[rs1]) < (CPU->regs[rs2]) ? 1:0; //her
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
		case 0b0110111: //U opcode
			CPU->regs[rd] = imm_U;
			break;
		case 0b1100011:
			switch(funct3){
				case 0b000: //beq
					CPU->pc = CPU->regs[rs1] == CPU->regs[rs2]? CPU->pc+(imm_SB/4)-1 : CPU->pc;
					break;
				case 0b001: //bne
					CPU->pc = CPU->regs[rs1] != CPU->regs[rs2]? CPU->pc+(imm_SB/4)-1 : CPU->pc;
					break;
				case 0b100: //blt
					CPU->pc = (signed int)CPU->regs[rs1] < (signed int)CPU->regs[rs2]? CPU->pc+(imm_SB/4)-1 : CPU->pc;
					break;
				case 0b101: //bge
					CPU->pc = (signed int)CPU->regs[rs1] >= (signed int)CPU->regs[rs2]? CPU->pc+(imm_SB/4)-1 : CPU->pc;
					break;
				case 0b110: //bltu
					CPU->pc = (unsigned int)CPU->regs[rs1] < (unsigned int)CPU->regs[rs2]? CPU->pc+(imm_SB/4)-1 : CPU->pc;
					break;
				case 0b111: //bgeu
					CPU->pc = (unsigned int)CPU->regs[rs1] >= (unsigned int)CPU->regs[rs2]? CPU->pc+(imm_SB/4)-1 : CPU->pc;
					break;
			}
			break;
		case 0b1100111: //jalr
			CPU->regs[rd]	=CPU->pc+1;
			CPU->pc 		=CPU->regs[rs1]+(imm_I/4)-1;
			break;

		case 0b1101111: //jal
			CPU->regs[rd] = CPU->pc+1;
			CPU->pc		  = CPU->pc+(imm_UJ/4)-1;
			break;

		case 0b1110011:
			switch (funct3){ //ecall
				case 0:
					printf("Program exited with code: 0 \n");
					return 0;
					break;
			}
			break;
		default:
			printf("no opcode found \n");
			break;

	}
	return 1;
}

