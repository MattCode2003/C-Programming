#include <stdio.h>
#include "convert_integer.h"


int ordinal();
int day_1_jan();
int wday();
int week();

int main(int argc, char **argv)
{
	/* Variable declaration */
	int day, month, year, iso_day, first_day, iso_week;
	unsigned int ordinal_day;

	/* Inputs */
	day = get_integer();
	month = get_integer();
	year = get_integer();

	/* Prints calender date */
	printf("%d-%02d-%02d\n", year, month, day);

	/* Converts into Ordinal and prints it */
	ordinal_day = ordinal(day, month, year);
	printf("%d-%03d\n", year, ordinal_day);
	
	/* Converts into Week date */
	first_day = day_1_jan(year);
	iso_day = wday(ordinal_day, first_day);
	iso_week = week(ordinal_day, iso_day, year);
	if(iso_week == 1 && month == 12)
		year += 1;
	if(iso_week == 53 && month == 1)
		year -= 1;

	printf("%d-W%02d-%d\n", year, iso_week, iso_day); /* ISO */

	/* Exits the Program */
	return 0;
}


/*===========================Leap Year========================*/


int leap_year(int year)
{
	if (!(year % 400))
		return 1;
	if (!(year % 100))
		return 0;
	if (!(year % 4))
		return 1;

	return 0;
}


/*============================Rounding========================*/


int rounding(float ordinal_day)
{
	int rounded;

	if(ordinal_day < 0)
		rounded = ordinal_day - 0.5;
	else
		rounded = ordinal_day + 0.5;
	
	return rounded;
}


/*============================Ordinal=========================*/


int ordinal(int day, int month, int year)
{
	int ordinal_day, i;
	int month_add[11] = {31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

	if(month == 1 || month == 2)
	{

		if(month == 1)
		{
			ordinal_day = day;
			return ordinal_day;
		}

		else
		{
			ordinal_day = day + month_add[0];
			return ordinal_day;
		}


	}

	for(i = 3; i < 13; i++)
	{
		if(month == i)
		{
			ordinal_day = day + month_add[i - 2] + leap_year(year);
			return ordinal_day;
		}
		
	}


	return 0;


}


/*=============================ISO============================*/


/* Works out the first day of any given year */
int day_1_jan(int year)
{
	int d, iso_day;

	/* Gauss' Algorithm - Works out the first day of year */
	d = (1 + 5 * ((year - 1)%4) + 4 * ((year - 1)%100) + 6 *((year - 1)%400))%7;
	
	/* Converts the day from Gregorian Calender to ISO Calender */
	if (d == 0)
		iso_day = 7;
	else
		iso_day = d;

	return iso_day;
}


/* Works out the correct day of the week */
int wday(int ordinal_day, int first_day)
{	
	int week_nbr, i;

	/* Decides wheather the day is the same as 1st jan and if not
	   calculates the offset */
	week_nbr = ordinal_day % 7;

	/* If same as 1st jan returns the same day */
	if(week_nbr == 0)
	{
		first_day = first_day - 1;
		if(first_day == 0)
			first_day = 7;
		return first_day;
	}

	/* If not works out the day based from offset and day of 1st jan*/
	for(i = 1; i != week_nbr; i++)
	{
		if(first_day == 7)
			first_day = 1;
		else
			first_day++;


	}

	return first_day;
}


/* The formula for weeks_in_year function */
int p(int year)
{
	return (year + year / 4 - year / 100 + year / 400) % 7;
}


/* Calculates the amount of weeks in the calender year */
int weeks_in_year(int year)
{
	int weeks_in_year;

	if(p(year) == 4 || p(year - 1) == 3)
		weeks_in_year = 53;
	else
		weeks_in_year = 52;

	return weeks_in_year;
}


/* Calculates what week of the year the date it in */
int week(int ordinal_day, int week_day, int year)
{
	int week;

	/* Calculates the current week in the year */
	week = rounding((ordinal_day - week_day + 10) / 7);
	
	/* Checks if the week is in the new year or not */
	if(!(week))
	{
		week = weeks_in_year(year - 1);
		return week;
	}
	if(week > weeks_in_year(year))
	{	
		if(week_day < 4)
		{
			week = 1;
			return week;
		}
	}

	return week;
}

/*  */