#include "monty.h"

/**
* add - Add the top two elements of the stack.
* @stack: Double pointer to the head of the stack.
* @line_number: Line number in the Monty bytecode file.
*/
void add(stack_t **stack, unsigned int line_number)
{
stack_t *temp;

if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
exit(EXIT_FAILURE);
}

(*stack)->next->n += (*stack)->n;

temp = *stack;
*stack = (*stack)->next;

if (*stack)
(*stack)->prev = NULL;

free(temp);
}
/**
* nop - No operation. Does nothing.
* @stack: Double pointer to the head of the stack.
* @line_number: Line number in the Monty bytecode file.
*/
void nop(stack_t **stack, unsigned int line_number)
{
(void)stack; /* Suppress unused parameter warning*/
(void)line_number;
/* No operation*/
}
/**
* sub - Subtract the top element from the second top element of the stack.
* @stack: Double pointer to the head of the stack.
* @line_number: Line number in the Monty bytecode file.
*/

void sub(stack_t **stack, unsigned int line_number)
{
/* Implementation of the sub opcode */
if (*stack != NULL && (*stack)->next != NULL)
{
stack_t *temp = *stack;
(*stack)->next->n -= (*stack)->n;

/* Pop the top element */
*stack = (*stack)->next;
free(temp);

if (*stack != NULL)
(*stack)->prev = NULL;
}
else
{
fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
}

/**
* div_op - Divide the second top element by the top element of the stack.
* @stack: Double pointer to the head of the stack.
* @line_number: Line number in the Monty bytecode file.
*/
void div_op(stack_t **stack, unsigned int line_number)
{
stack_t *temp;

if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%d: can't div, stack too short\n", line_number);
exit(EXIT_FAILURE);
}

if ((*stack)->n == 0)
{
fprintf(stderr, "L%d: division by zero\n", line_number);
exit(EXIT_FAILURE);
}

(*stack)->next->n /= (*stack)->n;

temp = *stack;
*stack = (*stack)->next;

if (*stack)
(*stack)->prev = NULL;

free(temp);
}
/**
* mul - Multiplies the second top element
* @stack: Double pointer to the top of the stack.
* @line_number: Line number
*/
void mul(stack_t **stack, unsigned int line_number)
{
int result, top_element, second_top_element;
stack_t *temp1, *temp2, *new_node;

if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
exit(EXIT_FAILURE);
}
top_element = (*stack)->n;
*stack = (*stack)->next;
second_top_element = (*stack)->n;
*stack = (*stack)->prev;
temp1 = *stack;
*stack = (*stack)->prev;
free(temp1);
temp2 = *stack;
*stack = (*stack)->prev;
free(temp2);
/* Perform the multiplication*/
result = second_top_element *top_element;
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

