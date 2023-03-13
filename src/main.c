
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

bool isBrainfuckSymbol(char);

//////////////////////////////////////////////////////////////////////////////////

///// Code /////

int main(void)
{
	// Reading In file
	char* brainfuckCode;
	{
		FILE* file = fopen(INFILENAME, "r");

		if (file == NULL)
		{
			printf("Could not open file\n");
			exit(0);
		}
		else
		{
			int fileSize;
			fseek(file, 0L, SEEK_END);
			fileSize = ftell(file);
			fseek(file, 0L, SEEK_SET);
			
			brainfuckCode = malloc(sizeof(char) * fileSize);

			int cntr = 0;
			char nextChar;
			do
			{
				nextChar = fgetc(file);
				if (isBrainfuckSymbol(nextChar))
				{
					brainfuckCode[cntr] = nextChar;
					cntr++;
				}
			}
			while (nextChar != EOF);
			brainfuckCode[cntr] = '\0';

			fclose(file);
		}
	}

	// Writing to Out file
	{
		FILE* file = fopen(OUTFILENAME, "w");

		if (file == NULL)
		{
			printf("Could not open file\n");
			exit(0);
		}
		else
		{
			// This is the main compiler part

			fprintf(file, "#include <stdio.h>\n");
			fprintf(file, "int main(void)\n{\n");
			fprintf(file, "char arr[30000] = {0};\n");
			fprintf(file, "char* ptr = arr;\n\n");

			int i = 0;
			while (brainfuckCode[i] != '\0')
			{
				char nex = brainfuckCode[i];

				if (nex == '>')
				{ fprintf(file, "ptr++;\n"); }
				else if (nex == '<')
				{ fprintf(file, "ptr--;\n"); }
				else if (nex == '+')
				{ fprintf(file, "(*ptr)++;\n"); }
				else if (nex == '-')
				{ fprintf(file, "(*ptr)--;\n"); }
				else if (nex == '.')
				{ fprintf(file, "putchar(*ptr);\n"); }
				else if (nex == ',')
				{ fprintf(file, "*ptr = getchar();\n"); }
				else if (nex == '[')
				{ fprintf(file, "while (*ptr)\n{\n"); }
				else if (nex == ']')
				{ fprintf(file, "}\n"); }

				i++;
			}

			fprintf(file, "\nreturn 0;\n");
			fprintf(file, "}\n");

			fclose(file);
		}
	}

	printf("Compilation successful\n");

	free(brainfuckCode);

	return 0;
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
