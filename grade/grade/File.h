#pragma once
#include "Setting.h"

#define DATASIZE 100
#define BUFFSIZE 1024

void CSV2Array(const char* fileName, Student students[DATASIZE]);
void Array2CSV(const char* fileName, Student students[DATASIZE], int size);