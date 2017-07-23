// 数代码.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

FILE * intput_filename();
int the_number_of_line(FILE * fp, int * pointer_of_number_of_note, int * pointer_of_number_of_blank);

int main()
{
	FILE * fp;
	int number_of_lines, number_of_notes,number_of_blank_lines;
	fp = intput_filename();
	number_of_lines = the_number_of_line(fp, &number_of_notes,&number_of_blank_lines);
	printf("The number of lines are %d\n", number_of_lines);
	printf("The number of notes are %d\n", number_of_notes);
	printf("The number of blank lines are %d\n", number_of_blank_lines);
	return 0;
}

FILE * intput_filename()
{
	char filename[100] = { 0 };
	FILE * fp;
	puts("Please intput filename:");
	//fgets(filename, 100, stdin);
	//filename[strlen(filename) - 1] = 0;//Delete enter(from fgets)
	strcat(filename, "ReadMe.txt");//Debug
	if (0 == (fp = fopen(filename, "r")))
	{
		puts("Can't open this file");
		system("pause");
		exit(-1);
	}
	return fp;
}

int the_number_of_line(FILE * fp, int * pointer_of_number_of_notes, int * pointer_of_number_of_blank_lines)
{
	char one_line[1000] = { 0 };//The longest byte of one list is 1000
	int number_of_lines, number_of_notes, number_of_blank_lines;
	bool blank_line;
	for (number_of_lines = 0, number_of_notes = 0, number_of_blank_lines = 0;0 == feof(fp) ; number_of_lines++)
	{
		fgets(one_line, 1000, fp);
		if (0 == *one_line)
		{
			number_of_lines = 0;
			number_of_notes = 0;
			number_of_blank_lines = 0;
			break;
		}
		if (strstr(one_line, "//") == one_line)//Delete note//
		{
			number_of_lines--;
			number_of_notes++;
		}
		else if (0)//Delete note/**/
		{
			;
		}
		else
		{
			char * cp = one_line;
			for (blank_line = 1; *cp; cp++)
			{
				if (*cp != '\n' && *cp != ' ' && *cp != '\t')
				{
					blank_line = 0;
					break;
				}
			}
			number_of_blank_lines += blank_line;
			number_of_lines -= blank_line;
		}
	}
	if (strstr(one_line, "//") == one_line)//Delete note//
	{
		number_of_notes--;
	}
	else if (0)//Delete note/**/
	{
		;
	}
	else if (1 == blank_line)
	{
		number_of_blank_lines--;
	}
	else
	{
		number_of_lines--;
	}
	puts(one_line);//Debug
	*pointer_of_number_of_notes = number_of_notes;
	*pointer_of_number_of_blank_lines = number_of_blank_lines;
	return number_of_lines;
}