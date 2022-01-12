#include "monty.h"



int main(int argc, char **argv)
{
	stack_t *_stack = NULL;
	char *buffer = NULL;
	size_t buff_size = 0;
	int line_count = 0;
	ssize_t line_size = 0;
	FILE *monty_file = NULL;
    char **cmds;

	if (argc != 2)
		fprintf(stderr, "USAGE: monty file\n"), exit(1);

	monty_file = read_file(argv[1]);

	while ((line_size = getline(&buffer, &buff_size, monty_file)) != -1)
	{
		line_count++;
		if (buffer[0] != '\n')
            cmds = tokenize(buffer);
			check_opcode(cmds, &_stack, line_count);
	}

	free(buffer);
	freestack(&_stack);
	fclose(monty_file);
	return (0);
}


void check_opcode(char **_cmds, stack_t **_stack, unsigned int line_number)
{
	instruction_t instruction[] = {
		{"push", push},
		{"pall", pall},
		{NULL, NULL}};

	int i = 0;

	for (; instruction[i].opcode != NULL ; i++)
	{
		if (strcmp(_cmds[0], instruction[i].opcode) == 0)
			break;
	}

	if (instruction[i].f != NULL)
        if (i == 0)
            check_push(_stack, _cmds, line_number);
        else
            instruction[i].f(_stack,line_number);
    else
    {
        fprintf(stderr, "L%d: unknown instruction %s\n", line_number, _cmds[i]);
		free(_cmds), freestack(_stack);
		exit(1);
    }
}

char **tokenize(char *buffer)
{
	char **cmds, *cmd;
	int i = 0;

	cmds = malloc(sizeof(char *) * 3);
	if (cmds == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free(buffer);
		exit(1);
	}

	cmd = strtok(buffer, "\t \n");
	while (cmd != NULL && i < 2)
	{
		cmds[i] = cmd;
		cmd = strtok(NULL, "\t \n");
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}

void check_push(stack_t **_stack, char **cmds, unsigned int ln)
{
	int i = 0;

	char *check_is_num;

	if (cmds[1] == NULL)  /* validar si push tiene argumento*/
	{
		fprintf(stderr, "L%d: usage: push integer\n", ln);
		free(cmds), freestack(_stack);
		exit(1);
	}
	check_is_num = cmds[1];

    for (i = 0; check_is_num[i] != '\0'; i++)
    {
            if (_isdigit(check_is_num[i]) == 0)
            {
                fprintf(stderr, "L%d: usage: push integer\n", ln);
                free(cmds), freestack(_stack);
                exit(1);
            }
    }
	push(_stack, atoi(check_is_num));
}


FILE *read_file(char *file_name)
{
    FILE *fp = NULL;

    fp = fopen(file_name, "r");
	if (!fp)
	{
		fprintf(stderr, "Error: Can't open file %s\n", file_name);
		exit(EXIT_FAILURE);
	}
    return (fp);
}
