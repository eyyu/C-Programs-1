
#include "a3_header.h"


/**
 * COMP 2510 C
 * A3  
 * Q sort function 
 */

/**
 * this method uses q sort to sort the array in two ways 
 * and then displaying the records to stdout
 * 
 * @param men_no [the sorting depends on the menu num chosen]
 * @param list   [the dynamically allocated list of records to be sorted]
 */
 void display_rec(int men_no, record_list *list){
 	size_t i;
 	if (men_no == 2){	
 		qsort(list->data, list->nused, sizeof(record), cmp_id);
 	}
 	else if(men_no == 3){
 		qsort(list->data, list->nused, sizeof(record), cmp_name);
 	}
 	else{
 		fprintf(stderr, "%s\n", "Error occurred while attempting to display records." );
 	}
	for (i = 0; i < list->nused; i++) {				
		printf("%d %s, %s: %d\n",				
			list->data[i].id,						
			list->data[i].name.last, 				
			list->data[i].name.first, 				
			list->data[i].score);					
	} 
 }

/**
 * This method compares the id values 
 * for ASCENDING order 
 * the method will return a positive number 
 * if the 1st record should go after the second
 * and negative if the 1st number should  go prior 
 *a zero is returned if there is not 
 *  
 * @param  r1 [description]
 * @param  r2 [description]
 * @return    [description]
 */
 int cmp_id(const void *r1, const void *r2){
 	const record *rec_1 = r1;
 	const record *rec_2 = r2;
 	return rec_1->id - rec_2->id;
 }

/**
 * This method is takes in two parameters 
 * to compare the names of the students in each record.
 *  if the names are the same, then the student id is compared
 * 
 * @param  r1 [description]
 * @param  r2 [description]
 * @return    [description]
 */
 int cmp_name(const void *r1, const void *r2){
 	const record *rec_1 = r1;
 	const record *rec_2 = r2;
 	int l, f;
 	l = strcmp(rec_1->name.last, rec_2->name.last);
 	if (l != 0){
 		return l;
 	}

 	f =  strcmp(rec_1->name.first, rec_2->name.first);
 	if(f != 0)
 		return f;
 	else
 		return cmp_id(r1, r2);
 }
