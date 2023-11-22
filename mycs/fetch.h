
#ifndef FETCH_H_
#define FETCH_H_
#include <stdint.h>

typedef struct {
	int32_t* data;
	int32_t size;
} readFile_t;

int fetchData(const char* inputFilePath, readFile_t* readFile);
//int fetch(const char* inputFilePath, readFile_t* readFile);

#endif /* FETCH_H_ */
