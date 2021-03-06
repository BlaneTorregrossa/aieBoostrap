#pragma once
#include <stdio.h>

class PerlinFiler
{
public:
	FILE* fp;
	const char* readIt(const char* fileName)
	{
		fopen_s(&fp, fileName, "r");
		fseek(fp, 0, SEEK_END);
		int size = ftell(fp);
		char* buffer = new char[size + 1];
		fseek(fp, 0, SEEK_SET);
		size_t numerator = fread(buffer, sizeof(char), size + 1, fp);
		fclose(fp);
		buffer[numerator] = '\0';
		const char* ret = buffer;
		return ret;
	}

};