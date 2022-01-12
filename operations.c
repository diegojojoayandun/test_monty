#include "monty.h"



void push(stack_t **stack, unsigned int number)
{
	stack_t *new;

	new = malloc(sizeof(stack_t));
	if (new == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		freestack(stack);
		exit(EXIT_FAILURE);
	}

	new->n = number;
	new->prev = NULL;
	new->next = *stack;
	if (*stack != NULL)
		(*stack)->prev = new;
	*stack = new;
}



void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;
	(void)line_number;

	tmp = *stack;
	if (tmp == NULL)
		return;
	while (tmp)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}


void freestack(stack_t **stack)
{
	stack_t *tmp;

	while ((*stack) != NULL)
	{
		tmp = (*stack);
		(*stack) = (*stack)->next;
		free(tmp);
	}
}



int _isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	return (0);
}

