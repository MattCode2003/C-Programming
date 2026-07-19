#include <stdio.h>
#include <stdlib.h>


long int str_to_int();
int num_check();
void pastri();
int calculate();

int main(int argc, char **argv)
{
	long int num;
	num = str_to_int(argv);


	if(argc != 2)
	{
		printf("Exit Value: 1\n");
		return 1;
	}

	if(num_check(num))
	{
		pastri(num);
	}
	else
	{
		printf("Exit Value: 1\n");
		return 1;
	}
	
	return 0;
}


    /* Converts the number from a char to a long int */
long int str_to_int(char **num)
{
	char *endptr;
	long int converted;
	converted = strtol(num[1], &endptr, 10);

	return converted;
}




    /* Checks that the number is between the values of 1 and 20 */
int num_check(long int n)
{
	if(n >= 1 && n <=20)
		return 1;
	else
		return 0;
}


/*=============================Pascals Triangle======================*/


   /* Calculates and prints pascals triangle */
void pastri(long int size)
{
	/* i = number of rows done
	   j = number of columns
	   space = number of spaces before numbers start */

	int i, j, space, coefficient;
	coefficient = 1;

	/* Loops n rows */
	for(i = 0; i != size; i++)
	{

		/* Creates the spaces on the side of the triangle */
		for(space = 0; space < i; space++)
		{
			printf("   ");
		}

		/* Works out the numbers that go into the triange */
		for(j = 0; j < size - i; j++)
		{	
			coefficient = calculate(i, j, size, coefficient);
			if(coefficient == 1)
				printf("%4d", coefficient);
			else
				printf("%4d ", coefficient);
		}
		/*if(i != size - 1)*/
		printf("\n");
	}	
}

int calculate(int i, int j, long int size, int coefficient)
{
	/* Produces the 1's on the side of the triangle */
	if(!(j))
		coefficient = 1;
	
	/* Calculates the numbers that are inside the triangle */
	else
	coefficient = coefficient * (size - i - j) / j;
	return coefficient;

}