#include "monty.h"
/**
* push - Pushes an element onto the stack.
* @stack: Double pointer to the top of the stack.
* @value: Value to be pushed onto the stack.
*/

void push(stack_t **stack,unsigned int value)
{
stack_t *newNode = malloc(sizeof(stack_t));
if (!newNode)
{
fprintf(stderr, "Error: malloc failed\n");
exit(EXIT_FAILURE);
}

newNode->n = value;
newNode->prev = NULL;
newNode->next = *stack;


if (*stack)
(*stack)->prev = newNode;

*stack = newNode;

}
/**
* pall - Prints all elements in the stack.
* @stack: Double pointer to the top of the stack.
* @line_number: Line number in the Monty script where pall was called.
*/
void pall(stack_t **stack, unsigned int line_number)
{
stack_t *current;
(void)line_number;/* Unused parameter*/

current = *stack;
while (current)
{
printf("%d\n", current->n);
current = current->next;
}
}
/**
* pint - Print the value at the top of the stack.
* @stack: Double pointer to the head of the stack.
* @line_number: Line number in the Monty bytecode file.
*/
void pint(stack_t **stack, unsigned int line_number)
{
if (*stack == NULL)
{
fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
exit(EXIT_FAILURE);
}

printf("%d\n", (*stack)->n);
}
/**
* pop - Remove the top element of the stack.
* @stack: Double pointer to the head of the stack.
* @line_number: Line number in the Monty bytecode file.
*/
void pop(stack_t **stack, unsigned int line_number)
{
stack_t *temp;
if (*stack == NULL)
{
fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
exit(EXIT_FAILURE);
}

temp = *stack;
*stack = (*stack)->next;

if (*stack)
(*stack)->prev = NULL;

free(temp);
}
/**
* swap - Swaps the top two elements of the stack.
* @stack: Double pointer to the top of the stack.
* @line_number: Line number in the Monty script where swap was called.
*/
void swap(stack_t **stack, unsigned int line_number)
{
stack_t *first, *second;
if (*stack == NULL || (*stack)->next == NULL)
{
fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
exit(EXIT_FAILURE);
}

first = *stack;
second = first->next;

first->next = second->next;
if (second->next != NULL)
{
second->next->prev = first;
}

second->prev = NULL;
second->next = first;
first->prev = second;

*stack = second;
}
