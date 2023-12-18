#include <stdlib.h>
#include <string.h>
#include "monty.h"
#include <stdio.h>


int _getline(char **line, size_t *len, FILE *file)
{
int c;
size_t i;
char *new_line;

if (*line == NULL || *len == 0)
{
*len = 128;  /* Initial buffer size*/
*line = (char *)malloc(*len);
if (*line == NULL)
{
perror("Error allocating memory");
return -1;
}
}
i = 0;
while ((c = fgetc(file)) != EOF && c != '\n')
{
if (i >= *len - 1)
{
*len *= 2;  /* Double the buffer size*/
new_line = (char *)realloc(*line, *len);
if (new_line == NULL)
{
perror("Error reallocating memory");
free(*line);
*line = NULL;
return (-1);
}
*line = new_line;
}
(*line)[i++] = (char)c;
}
if (i > 0 || c == '\n')
{
(*line)[i++] = '\0';  /* Null-terminate the string*/
return (i);
}
return (-1);  /*Indicates end of file*/
}

/**
* Main function to interpret Monty bytecode file.
*/

int main(int argc, char *argv[])
{
int i;
char *line, *opcode;
size_t len;
unsigned int line_number;
stack_t *stack;
FILE *file;
/*list with necessary opcodes and functions*/
instruction_t instructions[] = {
{"push", push},
{"pall", pall},
{"pint", pint},
{"pop", pop},
{"swap", swap},
{"add", add},
{"nop", nop},
{"sub", sub},
{"div", div_op},
{"mul", mul},
{"mod", mod},
{"pchar", pchar},
{"pstr", pstr},
{"rotl", rotl},
{"rotr", rotr},
/* Add more instructions as needed*/
{NULL, NULL} /*end of the instruction list*/
};

if (argc != 2)
{
fprintf(stderr, "USAGE: monty file\n");
exit(EXIT_FAILURE);
}

file = fopen(argv[1], "r");
if (!file)
{
fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
exit(EXIT_FAILURE);
}

line = NULL;
len = 0;
line_number = 0;
stack = NULL;

while (_getline(&line, &len, file) != -1)
{
line_number++;
/* Tokenize the line*/
opcode = strtok(line, " \t\n");
if (opcode == NULL || *opcode == '#')
{
/*Ignore empty lines and comments*/
continue;
}
/*Search for the corresponding function for the opcode*/
i = 0;
while (instructions[i].opcode != NULL)
{
if (strcmp(opcode, instructions[i].opcode) == 0)
{
instructions[i].f(&stack, line_number);
break;
}
i++;
}
if (instructions[i].opcode == NULL)
{
fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
exit(EXIT_FAILURE);
}
}
free(line);
fclose(file);
/*Clean up remaining nodes in the stack (if needed)*/
return (0);
}
