
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

//////////////////////////////////////////////////////////////////////////////////

///// Forward Declarations /////

char* getContentsOfFile(const char*);

bool isBrainfuckSymbol(char);

//////////////////////////////////////////////////////////////////////////////////

///// Code /////

int main(void)
{
	char* contents = getContentsOfFile(INFILENAME);

	printf("Here is file contents maybe...\n");
	for (int i = 0; i < 30; i++)
	{
		printf("%c", contents[i]);
	}

	free(contents);

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
		
		char* contents = malloc(sizeof(char) * fileSize);

		int cntr = 0;
		char nextChar;
		do
		{
			nextChar = fgetc(file);
			if (isBrainfuckSymbol(nextChar))
			{
				contents[cntr] = nextChar;
				cntr++;
			}
		}
		while (nextChar != EOF);

		fclose(file);
		return contents;
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
