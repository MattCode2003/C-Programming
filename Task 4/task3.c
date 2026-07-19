/*==================================Includes=================================*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 256


/*===========================Function Declarations===========================*/


void file_is_student(char *, char *, char *);
void file_is_results(char *, char *, char *);
int count_lines(char *);
void student_information(char *, char ***);
void results_information(char *, char ***, int);


/*====================================Main===================================*/


int main(int argc, char **argv)
{

	/* Sanity check */
	if(argc != 4)
	{
		fprintf(stderr, "Usage: Incorrect number of arguments\n");
		exit(EXIT_FAILURE);
	}

	if(access(argv[1], F_OK))
	{
		fprintf(stderr, "Error: file %s not found\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	if(access(argv[2], F_OK))
	{
		fprintf(stderr, "Error: file %s not found\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	if(!(strstr(argv[1], "student") || strstr(argv[1], "results")))
	{
		fprintf(stderr, "Error: Incorrect file entered\n");
		exit(EXIT_FAILURE);
	}

	if(!(strstr(argv[2], "activity")))
	{
		fprintf(stderr, "Error: Incorrect file entered\n");
		exit(EXIT_FAILURE);
	}

	if(!(strstr(argv[3], ".csv")))
	{
		fprintf(stderr, "Error: arg3 must be of .csv file type\n");
		exit(EXIT_FAILURE);
	}



	/* Decides what path to take */
	if(strstr(argv[1], "student"))
		file_is_student(argv[1], argv[2], argv[3]);
	else
		file_is_results(argv[1], argv[2], argv[3]);


	return 0;
}


/*===============================Student File================================*/


void file_is_student(char *student_file, char *activity_file, \
	char *output_file)
{
	FILE *fp1, *fp2;
	char line[MAX_LINE], *token, *endptr;
	int num_students, i, x, id1, id2, activity_lines;
	char *** student_info;

	num_students = count_lines(student_file) - 1;
	activity_lines = count_lines(activity_file) - 1;


	/* Allocates memory to 2D String array */
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


	/* Gets Student Information */
	student_information(student_file, &*student_info);

	fp2 = fopen(output_file, "w");
	fprintf(fp2, "id,last_name,first_name,average,grade01\n");

	/* Gets student Grades */
	for(i = 0; i < num_students; i++)
	{
		fp1 = fopen(activity_file, "r");
		x = 0;
		/* Loops through each line in activity file */
		while(fgets(line, MAX_LINE, fp1))
		{
			/* strips any carrage returns */
			line[strcspn(line, "\n\r")] = '\0';

			/* Checks if ID matches student */
			token = strtok(line, ",");

			/* Converts ID to integer */
			id1 = strtol(token, &endptr, 10);
			id2 = strtol(student_info[i][0], &endptr, 10);

			/* If id's match add to results file */
			if(id1 == id2)
			{
				token = strtok(NULL, ",");
				fprintf(fp2, "%s,%s,%s,%s.00,%s\n", student_info[i][0], \
					student_info[i][1], student_info[i][2], token, token);
				break;
			}
			x++;
		}

		/* makes grade 0 if student is absent */
		if(x == activity_lines + 1)
			fprintf(fp2, "%s,%s,%s,0.00,0\n", student_info[i][0], \
				student_info[i][1], student_info[i][2]);

		fclose(fp1);

	}

	fclose(fp2);



	/* Frees Memeory from 2D array */
	for(i = 0; i < num_students; i++)
	{
		for(x = 0; x < 3 ; x++)
			free(student_info[i][x]);
		free(student_info[i]);
	}
	free(student_info);
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


void student_information(char *file, char ***student_info)
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


/*===============================Results File================================*/


void file_is_results(char *results_file, char *activity_file, \
	char *output_file)
{
	FILE *fp, *fp2;
	char ***current_info, line[MAX_LINE], *token, *endptr, *current_student;
	char **grades;
	int i, num_grades, x, num_students, num_header = 0, id1, id2;
	int y;
	float mean;


	/* works out the current number of grades in file and items in header*/	
	fp = fopen(results_file, "r");
	if(fgets(line, MAX_LINE, fp))
	{
		/* strips any carrage returns */
		line[strcspn(line, "\n\r")] = '\0';

		token = strtok(line, ",");

		while(token)
		{
			token = strtok(NULL, ",");
			num_header++;
		}
	}
	fclose(fp);

	num_grades = num_header - 4;
	num_students = count_lines(results_file) - 1;




	/* Allocates memory to 2D string array */
	if(!(current_info = calloc(num_students, sizeof(char**))))
	{
		fprintf(stderr, "Memory: Not Enough Memory\n");
		exit(EXIT_FAILURE);
	}
	for(i = 0; i < num_students; i++)
	{
		if(!(current_info[i] = calloc(num_header, sizeof(char*))))
		{
			fprintf(stderr, "Memory: Not Enough Memory\n");
			exit(EXIT_FAILURE);
		}
		
		for(x = 0; x < num_header; x++)
			if(!(current_info[i][x] = calloc(MAX_LINE, sizeof(char))))
			{
				fprintf(stderr, "Memory: Not Enough Memory\n");
				exit(EXIT_FAILURE);
			}
	}

	

	/* Allocates grades memory */
	if(!(grades = calloc(num_grades + 1, sizeof(char*))))
	{
		fprintf(stderr, "Memory: Not Enough Memory\n");
		exit(EXIT_FAILURE);
	}
	for(i = 0; i < num_students + 1; i++)
	{
		if(!(grades = calloc(MAX_LINE, sizeof(char))))
		{
			fprintf(stderr, "Memory: Not Enough Memory\n");
			exit(EXIT_FAILURE);
		}
	}

	/* Allocates current student memory */
	if(!(current_student = calloc(1, sizeof(char*))))
	{
		fprintf(stderr, "Memory: Not Enough Memory\n");
		exit(EXIT_FAILURE);
	}


	/* reads results file and populate 2D array */
	results_information(results_file, &*current_info, num_header);

	/*for(i = 0; i < num_students; i++)
	{
		for (x = 0; x < num_header; x++)
			printf("current_info[%d][%d] = %s\n", i, x, current_info[i][x]);
	}*/

	/* Gets the grade for each person in new activity and calculates means */
	fp2 = fopen(output_file, "w");
	x = 0;
	for(i = 0; i < num_students; i++)
	{
		fp = fopen(activity_file, "r");
		while(fgets(line, MAX_LINE, fp))
		{
			/* strips any carrage returns */
			line[strcspn(line, "\n\r")] = '\0';

			token = strtok(line, ",");
			strcpy(current_student, token);

			/* Converts ID to integer */
			id1 = strtol(token, &endptr, 10);
			id2 = strtol(current_info[i][0], &endptr, 10);

			if(id1 == id2)
			{
				token = strtok(NULL, ",");
				break;
			}
			else
				x++;
		}
		rewind(fp);

		/* If name not in activity file then token is 0 */
		if(x == count_lines(activity_file) + 1)
			token = "0";



		/* Populates the grades array */
		mean = 0;
		for(y = 0; y < num_grades; y++)
		{
			grades[y] = current_info[i][y + 4];
			mean += strtol(current_info[i][y + 4], &endptr, 10);
		}
		grades[y + 1] = token;
		mean += strtol(token, &endptr, 10);



	




		/* Calculates new mean */
		mean /= y + 1;







		/* Writes info to new results file */

		/* If its the first student then creates header as well */
		if(!i)
		{

			/* Creates header */
			fprintf(fp2, "id,last_name,first_name,average");
			for(x = 0; x < num_grades + 1; x++)
				fprintf(fp2, ",grade%02d", x + 1);
			fprintf(fp2, "\n");
		}


		fprintf(fp2, "%s,%s,%s,%0.2f", current_info[i][0], \
			current_info[i][1], current_info[i][2], mean);

		for(x = 0; x < num_grades; x++)
		{
			fprintf(fp2, ",%s", grades[x]);
		}
		fprintf(fp2, ",%s", grades[x+1]);

		if(!(x + 1 == num_students))
			fprintf(fp2, "\n");
			
	}
	fclose(fp);
	fclose(fp2);




	/* Frees Memeory from 2D array */
	for(i = 0; i < num_students; i++)
	{
		for(x = 0; x < num_header; x++)
			free(current_info[i][x]);
		free(current_info[i]);
	}
	free(current_info);


	/* Frees memory from grades array */
	free(grades);
}


/*==========================Gets Results Infomation==========================*/


void results_information(char *file, char ***results_info, int num_header)
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
			strcpy(results_info[i - 1][0], token);

			for(x = 1; x < num_header; x++)
			{
				token = strtok(NULL, ",");
				strcpy(results_info[i - 1][x], token);

			}

			i++;
		}
		else
			i++;
	}

	fclose(fp);
}