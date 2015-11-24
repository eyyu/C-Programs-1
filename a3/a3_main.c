#include "a3_header.h"
/**
 * This is the main method of the program that will call the
 * functions necessary to:
 *  -display a menu
 *  -enter records
 *  -sort (and display) records
 *  -initsilaize the record list 
 *  -destory the records list 
 *  
 * @return  [int that indicated successful execution of main]
 */
int main(void){
	record rec;
	record_list list;
 	int men_no;
 	list_init(&list);
 	DBG_SET();
	do{
		if(!(men_no = get_user_req())){			/*if user quits menu*/
			list_destroy(&list);
			fprintf(stderr, "%s\n", "Quit Program" );
			return 0;
		}
		switch(men_no){
			case 1:
				while(enter_rec(&list, &rec));	/*keep reading records*/
				break;
			case 2:
			case 3:
				display_rec(men_no, &list);
				break;
		}
	}while(men_no);	/**loop out or end program*/
	list_destroy(&list);
	return 1;
}

/**
 * That will return the users menu item request 
 * @return [int representing the value of the request
 *              any move to exit the program the use makes, 
 *              the function will return a 0]
 */
int get_user_req(void){
	int men_no;					 /*menu number*/
 	char line[BUFSIZE];
	char extra[BUFSIZE]; 
	do{
		init_prompt();
		if(!fgets(line, BUFSIZE, stdin)){
			fprintf(stderr, "%s\n", "No Input Detected for Menu Choice");
			clearerr(stdin);
			return 0; 			/*program exit*/
		}
	}while(sscanf(line, "%d%s", &men_no, extra) == 0
		|| men_no < 0
		|| men_no > 4);
	if (men_no == 4){
		return 0;
	}
	return men_no;
}

/**
 * This method is the initial menu of the program
 * indicate the action the user wants to take 
 */
void init_prompt(void){
	size_t i;
	char *prompt[4] = {
		"Enter Records",
		"Display record sorted by ID",
		"Display record sorted by name",
		"Quit"};
	for (i = 0; i < 4; i++){
		fprintf(stderr, "%d. %s\n", (int)i+1 ,prompt[i]);
		/*printed to stderr according to instruction of assignment 3*/
	}
}

void list_init(record_list *list){
	list->nalloc = 0;
	list->nused = 0; /* num of lines allocated, num of pointers used*/
	list->data = malloc(sizeof(list->data));
}

/**
 * Method allows for insertion of records
 * @param  list [the record list struct to be allocated to ]
 * @param  rec  [the record struct that is allocated into the list]
 * @return      [1 if the allocation was successful, 0 if not]
 */
int list_insert(record_list *list, const record *rec){
	record_list temp;
	int new_size = (int)list->nalloc + BLOCK;
	
	if((int)list->nused == (int)list->nalloc){
		fprintf(stderr, "%s\n", "Attempting to reallocate");/*tester*/
		temp.data = realloc(list->data, (new_size)*sizeof(record)); /*resizing the array*/
		if(temp.data == '\0'){
			fprintf(stderr,"Cannot reallocate memory to resize dynamic array");
			return 0;
		}
	DBG('#'); /*DEBUG MACRO*/
	list->data = temp.data;
	list->nalloc += BLOCK;
	}
	list->data[list->nused] = *rec;
	list->nused++;
	return 1;
}
/**
 * destroy a record list 
 * make sure that the dynamically allocated memory is free!
 * Notes: why does this need to be in the 
 * @param list [the ]
 */
void list_destroy(record_list *list){
    list->nalloc = 0;
    list->nused = 0;
    free(list->data); 
    DBG('@'); /*DEBUG MACRO*/
	fprintf(stderr, "%s\n", "List Destroyed.");/*tester*/
}
