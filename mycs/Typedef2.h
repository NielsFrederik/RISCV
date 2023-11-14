/*
 * Typedef2.h
 *
 *  Created on: 13. nov. 2023
 *      Author: oscar
 */

#ifndef TYPEDEF2_H_
#define TYPEDEF2_H_

#include <stdint.h>
//#include <Typedef2.c>

typedef struct {
	uint32_t pc;
	uint32_t regs[32];
} CPU_t;

#endif /* TYPEDEF2_H_ */
