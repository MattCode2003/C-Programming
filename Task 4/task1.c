/*==================================Includes=================================*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINE 256

/*===========================Function Declarations===========================*/


int count_lines(char*);
int absent_students(int, int);
float meanf(int*, int, int);
float standard_deviation(int*, float, int, int);


/*====================================Main===================================*/


/* Performs sanity checks and Program Outputs*/
int main(int argc, char **argv)
{
	int activity_lines, *grades, i, grade;
	FILE *fp;
	char line[MAX_LINE], *token, *endptr;

	typedef struct Output{
		int students;
		int absent;
		float grade_average;
		double grade_sd;
	} Output;
	Output record;

	/* Correct number of arguments given */
	if(argc != 3)
	{
		fprintf(stderr, "Usage: Incorrect Number of Arguments\n");
		return 1;
	}
	

	/* Checks excel file 1 is readable */
	if(access(argv[1], F_OK))
	{
		fprintf(stderr, "Error: file %s not found\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	/* Checks excel file 2 is readable */
	if(access(argv[2], F_OK))
	{
		fprintf(stderr, "Error: file %s not found\n", argv[2]);
		exit(EXIT_FAILURE);
	}


	/* Checks if file 1 is students file */
	if(!(strstr(argv[1], "student")))
	{
		fprintf(stderr, "Error: Incorrect file entered\n");
		exit(EXIT_FAILURE);
	}

	/* Checks if file 2 is activity file */
	if(!(strstr(argv[2], "activity")))
	{
		fprintf(stderr, "Error: Incorrect file entered\n");
		exit(EXIT_FAILURE);
	}



	/* Calculates number of students in student file */
	record.students = count_lines(argv[1]) - 1;

	/* Calculates the number of lines in activity file */
	activity_lines = count_lines(argv[2]);




	/* Allocates the correct amount of memory for the array current_gen */
	if(!(grades = (int *) calloc(activity_lines - 1, sizeof(int))))
	{
		fprintf(stderr, "Memory: NOT ENOUGH MEMORY");
		exit(EXIT_FAILURE);
	}

	/* gets the grades and stores them in the grades array */
	fp = fopen(argv[2], "r");
	i = 0;
	while(fgets(line, MAX_LINE, fp))
	{
		if(i)
		{
			/* Strip any carriage returns */
			line[strcspn(line, "\n\r")] = '\0';

			/* parse string */
			token = strtok(line, ",");
			token = strtok(NULL, ",");
		
			/* Converts the grade from char to int */
			grade = strtol(token, &endptr, 10);
			
			/* Stores it in the array */
			grades[i - 1] = grade;

			i++;
		}
		else
			i++;
	}
	
	fclose(fp);

	/* Calculates the number of absent students */
	record.absent = absent_students(record.students, activity_lines - 1);

	/* Calculates the mean */
	record.grade_average = meanf(grades, activity_lines -1, record.students);

	/* Calculates the standard deviation */
	record.grade_sd = standard_deviation(grades, record.grade_average, \
		record.students, activity_lines - 1);

	
	free(grades);

	/* Prints Output */
	printf("total students = %d\n", record.students);
	printf("absent students = %d\n", record.absent);
	printf("grade mean = %0.2f\n", record.grade_average);
	printf("grade sd = %0.2f\n", record.grade_sd);

	return 0;
}


/*============================Counts Lines of File===========================*/


int count_lines(char *file)
{
	FILE *fp;
	char line[MAX_LINE];
	int line_num = 0;
	
	fp = fopen(file, "r");

	/* Calculates the number of lines in the file */
	while(fgets(line, MAX_LINE, fp))
		line_num++;

	fclose(fp);
	return line_num;
}


/*==============================Absent Students==============================*/


int absent_students(int students, int activity_lines)
{
	return students - activity_lines;
}


/*====================================Mean===================================*/


float meanf(int *grades, int lines, int students)
{
	int i; 
	float mean = 0;

	for(i = 0; i < lines; i++)
		mean += grades[i];
	mean /= students;


	return mean;
}


/*=============================Standard Diviation============================*/


float standard_deviation(int *grades, float mean, int students, int lines)
{
	int i;
	float sum = 0, sd = 0;

	for(i = 0; i < lines; i++)
		sum += pow(grades[i] - mean, 2);

	while(i != students)
	{
		sum += pow(0 - mean, 2);
		i++;
	}

	sd = sqrt(sum / students);
	

	return sd;
}