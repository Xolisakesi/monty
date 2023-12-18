#include "monty.h"
/**
* mod - Computes the rest of the division
* @stack: Double pointer to the top of the stack.
* @line_number: Line number in the Monty script where mod was called.
*/
void mod(stack_t **stack, unsigned int line_number)
{
int result, divisor, dividend;
stack_t *temp1, *temp2, *new_node;

if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
divisor = (*stack)->n;
if (divisor == 0)
{
fprintf(stderr, "L%u: division by zero\n", line_number);
exit(EXIT_FAILURE);
}
*stack = (*stack)->next;
dividend = (*stack)->n;
*stack = (*stack)->prev; /* Move back to the original position*/
/*Pop the top two elements from the stack*/
temp1 = *stack;
*stack = (*stack)->prev;
free(temp1);
temp2 = *stack;
*stack = (*stack)->prev;
free(temp2);
/* Perform the modulo operation*/
result = dividend % divisor;
/*Push the result back onto the stack*/
new_node = malloc(sizeof(stack_t));
if (new_node == NULL)
{
fprintf(stderr, "Memory allocation error\n");
exit(EXIT_FAILURE);
}
new_node->n = result;
new_node->prev = NULL;
new_node->next = *stack;
if (*stack != NULL)
{
(*stack)->prev = new_node;
}
*stack = new_node;
}
/**
* pchar - Prints the char at the top of the stack, followed by a new line.
* @stack: Double pointer to the top of the stack.
* @line_number: Line number in the Monty script where pchar was called.
*/
void pchar(stack_t **stack, unsigned int line_number)
{
int ascii_value;
stack_t *temp;

if (*stack == NULL)
{
fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
exit(EXIT_FAILURE);
}
ascii_value = (*stack)->n;

if (ascii_value < 0 || ascii_value > 127)
{
fprintf(stderr, "L%u: can't pchar, value out of range\n", line_number);
exit(EXIT_FAILURE);
}

printf("%c\n", (char)ascii_value);
/*Pop the top element from the stack*/
temp = *stack;
*stack = (*stack)->prev;
free(temp);
}
/**
* pstr - Prints the string starting at the top of the stack.
* @stack: Double pointer to the top of the stack.
* @line_number: Line number in the Monty script where pstr was called.
*/
void pstr(stack_t **stack, unsigned int line_number)
{
stack_t *current = *stack;
(void) line_number;

while (current != NULL && current->n != 0 && current->n >= 0 && current->n <= 127)
{
printf("%c", (char)current->n);
current = current->prev;
}

printf("\n");
}
/**
* rotl - Rotates the stack to the top.
* @stack: Double pointer to the top of the stack.
* @line_number: Line number in the Monty script where rotl was called.
*/
void rotl(stack_t **stack, unsigned int line_number)
{
stack_t *first, *second, *last;
(void)line_number;

if (*stack != NULL && (*stack)->next != NULL)
{
first = *stack;
second = (*stack)->next;
/* Update pointers*/
(*stack) = second;
second->prev = NULL;
/* Find the last element in the stack*/
last = *stack;
while (last->next != NULL)
{
last = last->next;
}
/* Adjust pointers for rotation*/
last->next = first;
first->prev = last;
first->next = NULL;
}
}
/**
* rotr - Rotates the stack to the bottom.
* @stack: Double pointer to the top of the stack.
* @line_number: Line number in the Monty script where rotr was called.
*/
void rotr(stack_t **stack, unsigned int line_number)
{
stack_t *last;
(void)line_number;

if (*stack != NULL && (*stack)->next != NULL)
{
/* Find the last element in the stack */
last = *stack;
while (last->next != NULL)
last = last->next;
/* Update pointers for rotation*/
last->prev->next = NULL;
last->prev = NULL;
last->next = *stack;
(*stack)->prev = last;
*stack = last;
}
}

