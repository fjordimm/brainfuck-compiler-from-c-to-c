
/*

"main.c"
Brainfuck compiler from C to C

Takes Brainfuck code from "in\in.bf" and compiles it into C code in "out\out.c"

*/

//////////////////////////////////////////////////////////////////////////////////

///// Includes /////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

//////////////////////////////////////////////////////////////////////////////////

///// Constants /////

const char INFILENAME[] = "..\\in\\in.bf";
const char OUTFILENAME[] = "..\\out\\out.c";

//////////////////////////////////////////////////////////////////////////////////

///// Forward Declarations /////

char* getContentsOfFile(const char*);
void writeToFile(const char*, char*);
bool isBrainfuckSymbol(char);

//////////////////////////////////////////////////////////////////////////////////

///// Code /////

int main(void)
{
	char* brainfuckCode = getContentsOfFile(INFILENAME);

	char testThing[] = "bruh moment cringe";

	writeToFile(OUTFILENAME, testThing);

	// int i = 0;
	// while (brainfuckCode[i] != '\0')
	// {
	// 	printf("%c", brainfuckCode[i]);
	// 	i++;
	// }

	free(brainfuckCode);

	return 0;
}

char* getContentsOfFile(const char* fileName)
{
	FILE* file = fopen(fileName, "r");

	if (file == NULL)
	{
		printf("Could not open file\n");
		return NULL;
	}
	else
	{
		int fileSize;
		fseek(file, 0L, SEEK_END);
		fileSize = ftell(file);
		fseek(file, 0L, SEEK_SET);
		
		char* ret = malloc(sizeof(char) * fileSize);

		int cntr = 0;
		char nextChar;
		do
		{
			nextChar = fgetc(file);
			if (isBrainfuckSymbol(nextChar))
			{
				ret[cntr] = nextChar;
				cntr++;
			}
		}
		while (nextChar != EOF);
		ret[cntr] = '\0';

		fclose(file);
		return ret;
	}
}

void writeToFile(const char* fileName, char* text)
{
	FILE* file = fopen(fileName, "w");

	if (file == NULL)
	{
		printf("Could not open file\n");
	}
	else
	{
		fprintf(file, "hohoho bitches");
		fprintf(file, "bingus schmingus");

		fclose(file);
	}
}

bool isBrainfuckSymbol(char the)
{
	return
		the == '>'
		|| the == '<'
		|| the == '+'
		|| the == '-'
		|| the == '.'
		|| the == ','
		|| the == '['
		|| the == ']'
	;
}
