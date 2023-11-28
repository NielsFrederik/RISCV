
#ifndef CPUtype_H_
#define CPUtype_H_

#include <stdint.h>

typedef struct {
	uint32_t	pc;
	uint32_t	regs[32];
	uint8_t		mem[0x100000];
} CPU_t;

#endif /* CPUtype_H_ */
