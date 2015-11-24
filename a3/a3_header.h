#ifndef A3_HEADER_H
#define A3_HEADER_H

	#include <stdio.h>
	#include <ctype.h>
	#include <string.h>
	#include <stddef.h>
	#include <stdlib.h>

	#define NAMESIZE 20
	#define BLOCK 2
	#define BUFSIZE 512
	
	/*************PREPROCESSING PRECONDITIONS****************/
	/**
	 * THE FOLLOWING ARE PREPROCESSOR PRECONDITIONS FOR DEBUGGING.
	 */
	#ifdef DEBUG 
		static int nalloc_count = 0, list_destroy_count = 0;
		#define DBG_SET() fprintf(stderr, "DEBUG MODE SET: '@' for destroy count, '#' for reallocation count \n");
		#define DBG(y) fprintf(stderr, "%c count: %d\n", y, (y=='#'? ++nalloc_count: ++list_destroy_count));
	#else
		#define DBG_SET()
		#define DBG(y)	
	#endif

	/*************DECLARING STRUCTS****************/
	/*Holds a name*/
	typedef struct 
	{
		char last[NAMESIZE]; 	/*last name; 1 (non-empty) word*/
		char first[NAMESIZE]; 	/*first name; 1 (non-empty) word*/
	}name;

	/*Holds Student record*/
	typedef struct 
	{
		int id; 				/*st id; between 1 000 000 - 9999999, inc*/
		name name; 				/*name of student*/
		int score; 				/*between 0 -100, inc.*/
	}record;

	/*Holds pointer to a dynamically allocated 
	list of records and keeps a dynamic count of the list*/
	typedef struct 
	{
		record *data; 			/* pointer to dynamic array of records*/
		size_t nalloc; 			/* numer of numbers allocated */ 
		size_t nused; 			/* number of records used*/
	}record_list;


	/*****DECLARING ALL METHODS****************/
	void list_init(record_list *list); 
	void list_destroy(record_list *list);
	int list_insert(record_list *list, const record *rec);
	void init_prompt(void); 
	int get_user_req();
	void clear_rec(record *rec);
	int get_name(const int ind, record *rec);
	int get_score(record * rec);
	int get_id(record *rec);
	int is_valid_id(const int id);
	int is_valid_name(const char s[]);
	int is_valid_score(const int score);
	int enter_rec(record_list *list, record *rec);
	void display_rec(int men_no, record_list *list);
	int cmp_name(const void *r1, const void *r2);
	int cmp_id(const void *r1, const void *r2);

#endif 
/*A3_HEADER_H*/