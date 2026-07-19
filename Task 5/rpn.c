/*==================================Inculdes=================================*/



#include "rpn.h"

#include "stack.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linked_list.h"
#include <math.h>

#define MAX_LINE 256



/*==============================Infix to Postfix=============================*/



/* convert an infix expression to postfix (rpn) using the */
/* shunting yard algorithm. */
/* return a queue containing the postfix expression. */
/* if an error occurs during evaluation, return silently with NULL. */
Queue *infix_to_postfix(char *expr)
{
	int is_left_associative(char);
	int is_operator(char);
	int operator_precedence(char);
	int test_precedence(char, char);
	int is_number(char, char, char);
	void valid_expression(char *);


	char *numbers, previous_char, *current, *top_stack, pre_pre_char;
	int expression_len, i, x;
	Stack *stack;
	Queue *queue;



	/* Checks if the expression is valid or not */
	valid_expression(expr);


	/* Initilise Stack and Queue */
	stack = initialise_stack();
	queue = initialise_queue();


	/* push '(' to stack and add ')' to end of expression */
	push_stack(stack, (void *)"(", sizeof(char));
	strcat(expr, ")");

	/*print_stack(stack, print_string);*/


	/* Gets the length of the expression */
	expression_len = strlen(expr);

	
	/* Allocates memory to numbers char array */
	if(!(numbers = calloc(expression_len + 1, sizeof(char))))
	{
		fprintf(stderr, "error: unable to allocate memory for numbers.\n");
		exit(EXIT_FAILURE);
	}


	/* Allocates memory to the current char array */
	if(!(current = calloc(expression_len + 1, sizeof(char))))
	{
		fprintf(stderr, "Error: unable to allocate memory\n");
		exit(EXIT_FAILURE);
	}







	
	previous_char = '#';
	pre_pre_char = '#';
	for(i = 0; i < expression_len - 1; i++)
	{	

		if(i)
		{
			previous_char = expr[i - 1];
			if(i - 1)
				pre_pre_char = expr[i - 2];
		}



		/* If current character is space then go to next character */
		if(expr[i] == ' ')
		{
			previous_char = expr[i - 1];
			continue;
		}
		



		/* If open bracket then add to stack */
		if(expr[i] == '(')
		{
			current[0] = '(';
			current[1] = '\0';
			push_stack(stack, (void*) current, sizeof(char));
			previous_char = '(';
			continue;
		}


		
		/* checks if the current expression character is a number */
		/*printf("previous_char = %c\n", previous_char);*/
		if(is_number(expr[i], previous_char, pre_pre_char))
		{
			/* stores it in number char array */
			numbers[0] = expr[i];
			previous_char = expr[i];
			x = 1;
			i++;
			
			while(is_number(expr[i], previous_char, pre_pre_char))
			{	
				numbers[x++] = expr[i];
				previous_char = expr[i++];
			}
			
			


			/*printf("number = %s\n", numbers);*/


			/* Adds the number to the queue */
			push_queue(queue, (void *)numbers, sizeof(numbers));

			/* resets the array, decimal and x for the next number */
			memset(numbers, 0, expression_len + 1 * sizeof(char));
			x = 0;
			i--;

			continue;
		}



		/* if the character is an operator */
		if(is_operator(expr[i]))
		{


			/* If right associative then push to stack */
			if(!(is_left_associative(expr[i])))
			{
				current[0] = expr[i];
				current[1] = '\0';
				
				push_stack(stack, (void *) current, sizeof(char));
				previous_char = expr[i];
				continue;
			}


			/* If left associative check precedence of operator on stack */
			top_stack = (char *) peek_stack(stack);

			/*print_stack(stack, print_string);*/
			
			while((is_operator(*top_stack) == 1) && \
				operator_precedence(*top_stack) >= operator_precedence(expr[i]))
			{
				top_stack = pop_stack(stack);
				/*printf("operator = %s\n", top_stack);*/
				push_queue(queue, top_stack, sizeof(char *));
				top_stack = (char *) peek_stack(stack);
			}

			/* Push current operator to stack */
			current[0] = expr[i];
			current[1] = '\0';
			push_stack(stack, (void *)current, sizeof(char));
			previous_char = expr[i];

			continue;
		}


		if(expr[i] == ')')
		{
			top_stack = pop_stack(stack);
			while(*top_stack != '(')
			{
				push_queue(queue, (void *) top_stack, sizeof(char));
				top_stack = pop_stack(stack);
			}

			previous_char = ')';
			continue;
		}


		

	}


	/*printf("=====================\nStack\n");
	print_stack(stack, print_string);
	printf("=====================\n\n");*/


	/* adds the remaining items in the stack to the queue */
	top_stack = pop_stack(stack);
	while(top_stack != NULL)
	{
		if((char) *top_stack == '(')
			top_stack = pop_stack(stack);
		else
		{
			push_queue(queue, (void *)top_stack, sizeof(char));
			top_stack = pop_stack(stack);
		}
	}


	free(numbers);
	free(current);
	free(top_stack);
	free_stack(stack);


	/* this is just a placeholder return */
	/* you will need to replace it */
	return queue;
}



/*======= is_left_associative */



/* works out if the operator is lefit associative or not */
int is_left_associative(char operator)
{
	if(operator == '^')
		return 0;
	else
		return 1;
}



/*======== is_operator */



/* Checks if the current char is an operator */
int is_operator(char char_check)
{
	if(char_check == '+' || char_check == '-' || char_check == '*' || \
		char_check == '/' || char_check == '^')
		return 1;
	else
		return 0;
}


/*======== operator_precedence */



/* returns the operators precedence number */
int operator_precedence(char operator)
{
	if(operator == '+' || operator == '-')
		return 1;
	if(operator == '*' || operator == '/')
		return 2;
	if(operator == '^')
		return 3;
	else
		return 0;
}



/*======== test_precedence */



/* compares precedence of 2 operators and returns -1, 0 or 1 */
/*int test_precedence(char operator1, char operator2)
{
	int precedence1, precedence2;

	precedence1 = operator_precedence(operator1);
	precedence2 = operator_precedence(operator2);

	if (precedence1 < precedence2)
		return -1;
	if(precedence1 == precedence2)
		return 0;
	else
		return 1;
}*/



/*======== is_number */



/* checks if the character is a number */
int is_number(char char1, char previous_char, char pre_pre_char)
{
	if(char1 == '+' || char1 == '-')
	{
		if(previous_char == '#' || previous_char == '+' || \
			previous_char == '-' || previous_char == '(')
			return 1;
		if(previous_char == ' ' && (pre_pre_char == '#' || \
			pre_pre_char == '+' || pre_pre_char == '-' || pre_pre_char == '('))
			return 1;
		else
			return 0;
	}

	if(char1 == '.' || isdigit(char1) != 0)
	{
		return 1;
	}
	else
		return 0;
}



/*======== valid_expression */



/* Checks if the expression is valid */
void valid_expression(char *expr)
{
	int i = 0;
	int open = 0, close = 0, alpha = 0;

	while(expr[i] != '\0')
	{
		if(isalpha(expr[i]))
		{
			alpha = 1;
			break;
		}
		if(expr[i] == '(')
			open++;
		if(expr[i] == ')')
			close++;
		i++;
	}

	if(alpha)
	{
		fprintf(stderr, "error: unable to parse expression\n");
		exit(EXIT_FAILURE);
	}

	if(open != close)
	{
		fprintf(stderr, "error: unable to parse expression\n");
		exit(EXIT_FAILURE);
	}
}






/*========================Evaluate Postfix Expression========================*/



/* evaluate the rpn expression given in *queue. */
/* return the value of the evaluated expression. */
/* if an error occurs during evaluation, return silently with HUGE_VAL. */
/* assume a precision of eight decimal places when performing arithmetic. */
double evaluate_rpn(Queue *queue)
{
	char *current, temp[100];
	double operand1, operand2, value;
	Stack *stack;

	/* Initialise Stack */
	stack = initialise_stack();


	current = (char *) pop_queue(queue);
	while(current != NULL)
	{
		/* checks if it is a number */
		if(isdigit(current[0]) || isdigit(current[1]))
		{
			push_stack(stack, (void *) current, sizeof(double));
			current = pop_queue(queue);
		}
		
		/* checks if it is an operator */
		if(is_operator(current[0]) && current[1] == '\0')
		{
			/* if it is an operator convert reicent 2 numbers to float and do operation */
			current = pop_queue(queue);
			operand1 = atof((char *) pop_stack(stack));
			operand2 = atof((char *) pop_stack(stack));

			
			if (current[0] == '+')
			{
				value = operand1 + operand2;
				sprintf(temp, "%f", value);
				push_stack(stack, (void *) temp, sizeof(char *));
			}

			if (current[0] == '-')
			{
				value = operand1 - operand2;
				sprintf(temp, "%f", value);
				push_stack(stack, (void *) temp, sizeof(char *));
			}

			if (current[0] == '*')
			{
				value = operand1 * operand2;
				sprintf(temp, "%f", value);
				push_stack(stack, (void *) temp, sizeof(char *));
			}

			if (current[0] == '/')
			{
				value = operand1 / operand2;
				sprintf(temp, "%f", value);
				push_stack(stack, (void *) temp, sizeof(char *));
			}

			if (current[0] == '^')
			{
				value = pow(operand2, operand1);
				sprintf(temp, "%f", value);
				push_stack(stack, (void *) temp, sizeof(char *));
			}

		}

		if(peek_stack(stack) == NULL)
				break;
		
	}


	/* this is just a placeholder return */
	/* you will need to replace it */
	return atof((char *)pop_stack(stack));
}