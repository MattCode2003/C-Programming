/*==================================Includes=================================*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define MAX_LINE 256


/*===========================Function Declarations===========================*/


int count_lines(char *);
void student_information(char *, char ***, int);
void student_grade(char *, char ***, int, int);


/*====================================Main===================================*/
int main(int argc, char **argv)
{
	int i = 0, num_students = 0, activity_lines = 0, x = 0;
	char ***student_info;

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


	num_students = count_lines(argv[1]) - 1;
	activity_lines = count_lines(argv[2]) - 1;
	

	/* Allocates memory to student_info string 2D-array */
	if(!(student_info = calloc(num_students, sizeof(char**))))
	{
		fprintf(stderr, "Memory: Not Enough Memory\n");
		exit(EXIT_FAILURE);
	}
	for(i = 0; i < num_students; i++)
	{
		if(!(student_info[i] = calloc(3, sizeof(char*))))
		{
			fprintf(stderr, "Memory: Not Enough Memory\n");
			exit(EXIT_FAILURE);
		}
		
		for(x = 0; x < 3; x++)
			if(!(student_info[i][x] = calloc(MAX_LINE, sizeof(char))))
			{
				fprintf(stderr, "Memory: Not Enough Memory\n");
				exit(EXIT_FAILURE);
			}
	}


	student_information(argv[1], &*student_info, num_students);
	student_grade(argv[2], &*student_info, num_students, activity_lines);



	/* Frees Memeory from 2D array */
	for(i = 0; i < num_students; i++)
	{
		for(x = 0; x < 3 ; x++)
			free(student_info[i][x]);
		free(student_info[i]);
	}
	free(student_info);
	

	/* Ends Program */
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

/*==========================Get Student name and ID==========================*/


void student_information(char *file, char ***student_info, int num_students)
{
	FILE *fp;
	char line[MAX_LINE], *token;
	int i = 0, x;

	fp = fopen(file, "r");



	while(fgets(line, MAX_LINE, fp))
	{	
		/* skips the header line */
		if(i)
		{
			/* strips any carrage returns */
			line[strcspn(line, "\n\r")] = '\0';

			/* Populates the 2D Array */
			token = strtok(line, ",");
			strcpy(student_info[i - 1][0], token);

			for(x = 1; x < 3; x++)
			{
				token = strtok(NULL, ",");
				strcpy(student_info[i - 1][x], token);

			}

			i++;
		}
		else
			i++;
	}

	fclose(fp);

}

/*===============================Student Grades==============================*/


void student_grade(char *file, char ***student_info, int num_students, \
	int activity_lines)
{
	FILE *fp;
	char line[MAX_LINE], *token, *endptr;
	int i, x, id1, id2;


	/* Loops thorugh each student */
	for(i = 0; i < num_students; i++)
	{
		fp = fopen(file, "r");
		x = 0;
		/* Loops through each line in activity file */
		while(fgets(line, MAX_LINE, fp))
		{
			/* strips any carrage returns */
			line[strcspn(line, "\n\r")] = '\0';

			/* Checks if ID matches student */
			token = strtok(line, ",");

			/* Converts ID to integer */
			id1 = strtol(token, &endptr, 10);
			id2 = strtol(student_info[i][0], &endptr, 10);

			if(id1 == id2)
			{
				token = strtok(NULL, ",");
				printf("%s %s %s\n", student_info[i][2], student_info[i][1], \
					token);
				break;
			}
			x++;
		}

		if(x == activity_lines + 1)
			printf("%s %s %d\n", student_info[i][2], student_info[i][1], 0);
		fclose(fp);
	}

	
}