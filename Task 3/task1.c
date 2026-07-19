/*==================================Includes=================================*/


#include <stdio.h>
#include <stdlib.h>


/*===========================Function Declarations===========================*/


void elementary_cellular_automation();


/*====================================Main===================================*/


/* Performs sanity checks */
int main(int argc, char **argv)
{
	int i;
	long int arguments[3];
	char *endptr;


	/* Correct number of arguments given */
	if(argc != 4)
	{
		printf("Usage: Incorrect number of arguments\n");
		return 1;		
	}

	/* Converts arguments from char to int */
	for(i = 1; i < 4; i++)
		arguments[i - 1] = strtol(argv[i], &endptr, 10);


	/* Checks value of argument 1 */
	if(arguments[0] <= 0)
	{
		printf("Usage: Argument 1 should be greater than 0\n");
		return 1;
	}

	/* Checks value of argument 2 */
	if(arguments[1] <= 0)
	{
		printf("Usage: Argument 2 should be greater than 0\n");
		return 1;
	}

	/* Checks value of argument 3 */
	if(arguments[2] < 0 || arguments[2] > 255)
	{
		printf("Usage: Argument 3 is out of range\n");
		return 1;
	}



	/* Runs the algorithm */
	elementary_cellular_automation(arguments[0], arguments[1], arguments[2]);

	return 0;
}


void elementary_cellular_automation(int cell, int gens, int rule)
{
	int i, x = 7, binary[8], binary_reversed[8], *current_gen, *next_gen;
	int  num, y, z;
	int neighbourhood[3];

/* =====Prep==== */

	/* Calculates the binary value */
	for(i = 0; rule > 0; i++)
	{
		binary[i] = rule % 2;
		rule /= 2;
	}

	/* Makes sure it is an 8-bit value */
	for(; i != 8; i++)
		binary[i] = 0;

	/* Revereses the binary list so that it is the correct way around */
	for(i = 0; i != 8; i++)
	{
		binary_reversed[i] = binary[x];
		x--;
	}


/**/


	/* Allocates the correct amount of memory for the array current_gen */
	if(!(current_gen = (int *) calloc(cell, sizeof(int))))
		{
			printf("Memory: NOT ENOUGH MEMORY");
			exit(EXIT_FAILURE);
		}


	/* Allocates the correct amount of memory for the array next_gen */
	if(!(next_gen = (int *) calloc(cell, sizeof(int))))
	{
		printf("Memory: NOT ENOUGH MEMORY");
		exit(EXIT_FAILURE);
	}	
		



/* ====Main==== */
		


	/* Creates generation zero based on the cell value and binary rule */
	i = 0;
	x = 0;
	while(i < cell)
	{
		current_gen[i] = binary_reversed[x];
		i++;
		x++;
		if(x == 8)
			x = 0;
	}
	


	/* Produces output for generation 0 */
	i = 0;
	while(i < cell)
	{
		if(!current_gen[i])
			printf(" ");
		else
			printf("*");
		i++;
	}
	printf("\n");

	next_gen[0] = current_gen[0];
	next_gen[cell - 1] = current_gen[cell - 1];

	/* Loops through each generation */
	for(i = 0; i < gens; i++)
	{
		next_gen[0] = current_gen[0];

		/* Loops through each generation */
		for(x = 1; x < cell - 1; x++)
		{
			/* Works out the neighbourhood for each cell */
			neighbourhood[0] = current_gen[x - 1];
			neighbourhood[1] = current_gen[x];
			neighbourhood[2] = current_gen[x + 1];

			/*printf("neighbourhood[0] = %d\n", neighbourhood[0]);
			printf("neighbourhood[1] = %d\n", neighbourhood[1]);
			printf("neighbourhood[2] = %d\n", neighbourhood[2]);*/


			/* Converts the neighbourhood binary value into decimal */
			num = 0;
			z = 2;
			for(y = 1; y != 8; y *= 2)
			{
				num += neighbourhood[z] * y;				
				z--;
			}
			/*printf("num = %d\n", num);*/


			/* Calculate the next gens cell */
			if(!num)
				next_gen[x] = binary_reversed[7];
			else
				next_gen[x] = binary_reversed[7 - num];
			/*printf("next_gen[x] = %d\n", next_gen[x]);*/

		}

		/* Prints the current line */
		for(y = 0; y < cell; y++)
		{
			if(next_gen[y])
				printf("*");
			else
				printf(" ");
		}
		printf("\n");


		/* Copies next gen to current gen */
		for(y = 0; y < cell; y++)
			current_gen[y] = next_gen[y];
	}


	


	

	/* Relases the Memory from the arrays */
	free(current_gen);
	free(next_gen);
}