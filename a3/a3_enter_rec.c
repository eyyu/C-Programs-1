#include "a3_header.h"
/**
 * this function will clear the preexisting record if the
 * user exits the records updating halfway through. 
 * @param rec [the struct record to be cleared ]
 */
void clear_rec(record *rec){
	rec->id = 0;	
	rec->name.last[0]  = '\0';
	rec->name.first[0] = '\0';
	rec->score = 0;
}

/**
 * [this method enters a record to the list,
 *  given that a record is successfully entered fully ]
 * @param  list [a record list struct]
 * @param  rec  [a record to be entered into the list]
 * @return      [1 to indicate successful entering of a record
 *                  0 to indicate the user exited the record entering mode]
 */
int enter_rec(record_list *list, record *rec){ 
	/*for when the user is entering data*/
	while(get_id(rec) 
		&& get_name(1 , rec) /*last name*/  
		&& get_name(0 , rec) /*first name*/
		&& get_score(rec)){ 
			list_insert(list, rec);	
			return 1;
	}
	clear_rec(rec);
	return 0;
}

/**
 * [this method gets the id of the user
 * the id must be valid and not be a a space
 * 
 * @param  rec [this is the struct record to put the id into]
 * @return     [1 to indicate that the input is successful, 0 to indicate
 *               	exiting]
 */
int get_id(record *rec){
	int id;
	char line[BUFSIZE];
	char *p = "Exited Record Input";
	do{
		fprintf(stderr, "%s\n", "Please print a valid student ID: " );
		if(!fgets(line, BUFSIZE, stdin)){
			fprintf(stderr, "%s\n", p);
			return 0;
		}
	}while(sscanf(line, "%d",&id) == 0
		||(!is_valid_id(id) && (id != 0)) 
		);
	if(id == 0){
		fprintf(stderr, "%s\n",p);
		return 0;
	}
	rec->id =  id;
	return 1;
}
/**
 * this method retrieves the first and last name of the user 
 * 0 will indicate first name, 
 * 1 will indicate last name.
 *
 *the name is then copied into the appropriate space in the record 
 * 
 * @param  ind [ 0 or 1 to indicate first or last name]
 * @param  rec [the struct record to copy the information into]
 * @return     [1 if successful, 0 otherwise]
 */
int get_name(const int ind, record *rec){
	/* ind means indicator*/
	size_t i;
	char line[BUFSIZE], name[NAMESIZE], extra[BUFSIZE];
	char *n_str[2] = {"first","last"};
	do{
		fprintf(stderr, "%s %s %s \n", "Please print a valid",n_str[ind],"name:" );
		if(!fgets(line, BUFSIZE, stdin)){
			fprintf(stderr, "%s\n", "Exited record input" );
			return 0;
		}
	}while((sscanf(line, "%s%s", name, extra) == 0)
		||line[0] == '\n'
		||!is_valid_name(name)
		);
	for (i = 1; i < strlen(name); i++){
		name[i] = tolower((unsigned)name[i]);
	}
	name[0] = toupper((unsigned)name[0]);
	if(ind){
		strcpy(rec->name.last, name);
	}else{
		strcpy(rec->name.first, name);
	}
	return 1;
}
/**
 * this method checks for a score from the users input. 
 * the score must be valid, or the program will continue the prompt 
 * until the user exits with EOF 
 * 
 * @param  rec [a struct record to put the information into]
 * @return     [1 is successful, 0 otherwise]
 */
int get_score(record *rec){
 	int grade;
 	char line[BUFSIZE];
	do{
		fprintf(stderr, "%s\n", "Please print a score from 0-100: " );
		if(!fgets(line, BUFSIZE, stdin)){
			return 0;
		}
	}while(sscanf(line, "%d", &grade) != 1
		||!is_valid_score(grade)
		);
	rec->score = grade;
	return 1;
}
/**
 * this method checks for a valid score 
 * the score must be between 0 - 100, inclusive
 * 
 * @param  score [int representing the score]
 * @return       [1 if the score is valid, 0 if not]
 */
int is_valid_score(const int score){
	if(score <= 100 
		&& score >= 0)
		return 1;
	return 0;
}
/**
 * Checks to see if the name is valid. 
 * A name is valid if it a string of any characters 
 * 
 * @param  s [the string that a name]
 * @return   [0 is invalid, 1 if valid ]
 */
int is_valid_name(const char s[]){
	if(strlen(s) < 1 
		|| strlen(s) >= NAMESIZE)
		return 0; 	
	return 1;
}
/**
 * checks for valid id
 * an id is valid if it is between 1000000 and 99999999, inclusive
 *  
 * @param  id [the int that represents ID]
 * @return    [a 1 indicates a valid ID, 0 otherwise ]
 */
int is_valid_id(const int id){
	if(id <= 9999999
		&& id >= 1000000){
		return 1;
	}
	return 0;
}