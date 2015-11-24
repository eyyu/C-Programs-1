
/*****************************************
 *COMP 2510 Assignment 1
 *Eva Yu 
 *A00942918
 *
 * This program retrieves and appends records from a file.
 * The user is pompted to make an action of either 0, nth record, or -nth record. 
 * The following describe the instances:
 * 0 : append new record
 * -n: retrieve records from |n|th record 
 * n : retireive nth record only
 * 
 * The records are stored as Student number, Name, and Score. 
 * The user can request to see the records and will output to stderr.
 * 
 * @author Eva Yu
 * @version 1.0
 * 
******************************************/

/************INCLUDE****************/
#include <stdio.h> 
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>

/************DEFINE**************/
#define LINESIZE    512
#define RECORDSIZE	54
#define MINARGUMENT 2
#define MINSCORE    0
#define MAXSCORE    100
#define IDSIZE      10
#define MINNAMESIZE 2
#define MAXNAMESIZE 20
#define SCORESIZE   4


/*****DECLARING ALL METHODS****************/
/**prompt**/
int prompt_input(int* input, FILE *fp);
int no_record_err(void);
/**display**/
int display_record(const int record, FILE* fp);
int display_multi_record(const int record, FILE* fp);
/**gets**/
int get_id(char id_record[]);
int get_name( char firstname[], char lastname[]);
int get_score(int *score);
/**checks**/
int is_valid_input(const int record_no, FILE* fp);
int is_valid_id(char id_let, char id_num[]);
int is_valid_name(const char s[]);
int is_valid_score(int score);
/**append*/
int append_record(FILE *fp, char id[], char first[], char last[], int score);
/******************************************/


/*
 * This is the the main method where the program begins to execute. 
 * The program will open an existing or new text file in binary to append or read 
 * if the file is created or opened succesfully, the program will loop and 
 * repeatedly ask the user for input from stdinn until the user
 * indicates EOF or enters empty spaces. 
 * 
 * @param   argc      argument count 
 * @param   argv      argument values
 * @return            returns 0 in successful termination of program
 *                    returnsn -1 if program exits
 *                    returns  -2 if file does not clsoe properly 
 */
int main(int argc, char* argv[] ){
	FILE* fp;
	int input;
	char id[IDSIZE], first[MAXNAMESIZE], last[MAXNAMESIZE];
	int score = -1;
	if(argc != MINARGUMENT){ /* checks there are 2 arguments when program runs*/
		char usage[] = "Program needs one file to run";
		printf("%s", usage); /* prints usage of program*/
		return -1; /* returns -1to terminate program;*/
	}

	if((fp = fopen(argv[1], "a+b")) == 0){ /*if file does not exist*/ 
		perror("fopen");	/*create new file*/
		return -1;
	}
 /* close file*/
	
	while(prompt_input(&input, fp))
	{  /* if input is not valid */
			if(input == 0) 
			{
				if(get_id(id) && get_name(first, last) && get_score(&score))
				{
					append_record(fp,id,first,last,score);
										
				} 
			}else if(input > 0){
				display_record(input, fp);
								
			} else if(input < 0){
				display_multi_record(input, fp);
								
			}	
	}

	if(fclose(fp) != 0){
		perror("fclose");
		return -1;
	}
	return 0;
}

/**
 * Checks a string to see if it 
 * contains only spaces but is 
 * not onyl null or newspace character
 * 
 * @param  string checks any string of n length 
 * @return        returns 1 if string is only spaces
 */
int is_empty_string(char string[]){
	size_t i;
	if(strlen(string) != 1){
		for (i = 0; string[i] != '\0'; ++i)
		{
			if(!isspace((unsigned int)string[i])){
				return 0;
			}
		}
	return 1;
	}
	return 0;
}

/**
 *This method appends a formatted string to represent a record to a file.
 *
 * 
 * @param  fp    the file destination to append to 
 * @param  id    string that indicates the student id 
 * @param  first String that indicates a first name 
 * @param  last  a string that indicates the last name 
 * @param  score int that indcates a score
 * @return       0 upon successful termination of method
 */
int append_record(FILE *fp, char id[], char first[], char last[], int score){
	fprintf(fp, "%-10s%-20s%-20s%-4d",id, first, last, score);
	return 0;
}

/**
 * This is a function that prints to stderr to indicate there is no record found at the indcated value
 * 
 * @param  record int record number
 * @return        0 upon successful termination of method
 */
int no_record_err(void){
	fprintf(stderr, "no matching record\n");
	return 0;
}

/**
 * This method makes sure that the value input is avalid input of either : 0, n, or -n 
 * where n and |-n| are both values that are less than or equal to the number of records there are.  
 * 
 * @param  record_no [description]
 * @param  fp        [description]
 * @return           [description]
 */
int is_valid_input(const int record_no, FILE* fp){
 	
	int c;
	int count= 0;
	int records = 0;

	fseek(fp, 0, SEEK_SET);/* sets the file to the beginning*/
	 while((c = fgetc(fp)) != EOF) /* counts number of lines (aka: records) */
	 {
	 		count++;
	 }
	 records = count / RECORDSIZE;

	 if (abs(record_no) > records)
	 {
	 	no_record_err();
		return 0; /* not a valid input*/	
	 }


	 return 1;
  
}
 
/**
 * This method will prompt the user for an input of 3 possibilieties: 
 * 0 : append new record
 * -(int): retrieve from nth record 
 * int : retireive nth record
 * 
 * @param  input the address of the input to change the value retireved
 * @param  fp    the file destination
 * @return   0 if the use enters empty string or EOF     
 */
int prompt_input(int* input, FILE *fp)
{
	
	char line[LINESIZE], extra[LINESIZE];
	int num;

	do
	{
		printf("%s\n", "Please indicate desired input:" );
		if(!fgets(line, LINESIZE, stdin) || is_empty_string(line)) /* if there is no input*/ 
		{ 
			clearerr(stdin);/* exits progroam at EOF*/
			return 0;
		}

	}while(sscanf(line, "%d%s", &num, extra) == 0
		|| line[0] == '\n'
		|| !is_valid_input(num, fp)

		);/* while there is more than one*/ 
	
	*input = num;	
	return 1;	
}

/**
 * Displays the Nth record requested if it a valid value to stderr.
 *
 * 
 * @param  record int representing the nth record
 * @param  fp     the file destionation
 * @return        0 upon successful termination of the method
 */
int display_record(const int record, FILE* fp)
{
	int score;
	char id[IDSIZE], first[MAXNAMESIZE], last[MAXNAMESIZE];
	fseek(fp, (abs(record-1))*RECORDSIZE, SEEK_SET); 
	if(fscanf(fp, "%s%s%s%d",id, first, last, &score) == 4)
	{
		fprintf(stderr,"%s : %s, %s : %d\n",id, last, first, score);
	}

	return 0;
}

/**
 * Function runs if user inputs a valid value to retrive multiple records
 * and prints to stderr. Records will be retirved from the n-th value to the last. 
 * 
 * @param  record a negative int to represent the nth value of record to begin at
 * @param  fp     the file to read from 
 * @return        returns 0 upon succesful termination of method
 */
int display_multi_record(const int record, FILE* fp)
{
	int  score;
	char id[IDSIZE], first[MAXNAMESIZE], last[MAXNAMESIZE];

	fseek(fp, abs((record+1)*RECORDSIZE), SEEK_SET); 
	
	while(fscanf(fp, "%s%s%s%d",id, first, last, &score) == 4)
	{
		fprintf(stderr,"%s : %s, %s : %d\n",id, last, first, score);
	}

	return 0;
}


/**
 * Method checks that the id is a valid student id 
 * 
 * @param  id_let first character on id should be letter 'a' only 
 * @param  id_num the string of numbers ( only digits ) that follow that make up the id
 * @return        0 if the id is not valid 
 */
int is_valid_id(char id_let, char id_num[])
{
	size_t i;
	int count = 0;

	if(id_let != 'a'){
		return 0;
	}
	
	for(i=0;id_num[i] != '\0';i++){
		if(!isdigit((unsigned int)id_num[i])){
			return 0;	 
		}
		count++;
	}

	if(count!=8){
		return 0;
	}

	return 1;
}

/**
 * Mehtod repeatedly prompts user for a student number that is valid.
 * It will parse the input with the first character and the folowing string of digits 
 * and pass it into is_valid_id to validate the string. 
 * If it is validated, the string will copy into the value at the address of the id
 *  
 * Program Exits function at EOF or if there are only spaces.
 * 
 * @param  id_record A string that should represent a student number
 * @return           0 if the use enters empty string or EOF 
 */
int get_id(char id_record[])
{
 	char id_num[IDSIZE];
 	char extra[LINESIZE];
	char line[LINESIZE];
	char id_start;
	size_t i;

	do{
		printf("%s\n", "Please print a valid student ID: " );
		if(!fgets(line, LINESIZE, stdin)){
			return 0;
		}
		if(is_empty_string(line)){ 
			return 0;
		}

	}while(sscanf(line, "%c%s%s",&id_start, id_num, extra) == 0
		||!is_valid_id(id_start,id_num)
		);

	id_record[0] = id_start;
	for(i=0; id_num[i] != '\0'; i++){
		id_record[i+1] = id_num[i]; 
	}
	id_record[i+1] = id_num[i];

	return 1;
}

/**
 * THis method checks the validity of a first and last name input
 * Each name cannot begin or end with a dash and must be between 2-20 characters long
 * 
 * @param  s String that is the name
 * @return   0 if the name is not valid 
 */
int is_valid_name(const char s[]){
	size_t i, length = 0;
	
	for ( i=0; s[i]; i++){
		if(!isalpha((unsigned char)s[i]) && s[i] != '-'){
			return 0;
		}
		length++;
	}

	if(s[0] == '-' ){
		return 0;
	}

	if (s[length - 1] == '-'){
		return 0;
	}

	if(length < MINNAMESIZE){
		return 0;
	}
	
	if(length >= MAXNAMESIZE){
		return 0; 
	}

	return 1;
}

/**
 * [get_name description]
 * @param  firstname [description]
 * @param  lastname  [description]
 * @return           0 if the use enters empty string or EOF 
 */
int get_name( char firstname[], char lastname[]){
 	char first[LINESIZE];
	char last[LINESIZE];
	char extra[LINESIZE];
	char line[LINESIZE];

	size_t i;

	do{
		printf("%s\n", "Please print a valid name: " );
		if(!fgets(line, LINESIZE, stdin)){
			return 0;
		}
		if(is_empty_string(line)){ 
			return 0;
		}
		
	}while(sscanf(line, "%s%s%s", first, last, extra) == 1
		||!is_valid_name(first)
		||!is_valid_name(last)
		);

	for(i=0; first[i]; i++){
		firstname[i] = tolower((unsigned int)first[i]); 
	}
	firstname[i] = first[i]; 
	
	for(i=0; last[i]; i++){
		lastname[i] = tolower((unsigned int)last[i]); 
	}	
	lastname[i] = last[i]; 

	return 1;

}

/**
 * checks  the validity of the int score to make sure it is between 0 -100 , inclusive 
 * 
 * @param  score int 
 * @return       0 if the score is not a valid score 
 */
int is_valid_score(int score){
	if(score > MAXSCORE || score < MINSCORE){
		return 0; 
	}
	return 1;
}

/**
 * Method prompts user to enter an int as a score
 * and checks the scores validity
 * and then the score is passed into the address if the int variable using it 
 *  
 * @param  *score address to the score of the individual 
 * @return       0 if the use enters empty string or EOF 
 */
int get_score(int *score){
 	int grade;
 	char line[LINESIZE];
	do{
		printf("%s\n", "Please print a score from 0-100: " );
		if(!fgets(line, LINESIZE, stdin)){
			return 0;
		}
		if(is_empty_string(line)){ 
			return 0;
		}
		
	}while(sscanf(line, "%d", &grade) != 1
		||!is_valid_score(grade)
		);

	*score = grade;
	return 1;

}


