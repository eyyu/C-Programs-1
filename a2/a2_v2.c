/* This program is MODULE 1 : compares only bit by bit*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

#define LINESIZE 1024
#define SWITCHLEN 32 

int comp_by_char(FILE * fp1, FILE *fp2, char f1_name[], char f2_name[], int ignore_caps);
int comp_by_line(FILE * fp1, FILE *fp2, char f1_name[], char f2_name[], int ignore_caps); 
long get_file_size_word(FILE *fp);
int comp_by_word(FILE *fp1, FILE *fp2, char f1_name[], char f2_name[], int ignore_caps);
long get_file_size(FILE *fp);
long max_size(long filesize1, long filesize2);
void init_read(FILE *fp);
int one_empty_file(long file_len1, long file_len2);
int empty_files(long file_len1, long file_len2);
long min_size(long filesize1, long filesize2);
long max_size(long filesize1, long filesize2);

int main(int argc, char *argv[]){
	FILE *fp1,*fp2;
	char f2_name[LINESIZE], f1_name[LINESIZE], current_switch[SWITCHLEN];
	int c,l_switch = 0, w_switch = 0, i_switch = 0, end_switch = 0;
	size_t i;

	if(argc < 3){ /* if there are less than 2 files called*/
		return 2;
	}

	for (i = 1; (int)i < argc; ++i){
		if(*argv[i] == '-'){

			if(end_switch == 1){
				break;
			}
			if(l_switch && w_switch){
				return 2;
			}
			strcpy(current_switch, argv[i]);
			c = current_switch[1];
			switch (c){
				case 'w':
					w_switch = 1;
					break;
				case 'l':
					l_switch = 1;
					break;
				case 'i':
					i_switch = 1;
					break;
				case '-':
					end_switch = 1;
					break;
				default: 
					return 2;/*returns as improper init*/
			}
		}
		else{
			if((argc - i) != 2){ /*if left over arguments are not  two...*/
				return 2;
			}
			break;
		}
	}
	
	strcpy(f1_name, argv[i]);
	strcpy(f2_name,argv[i+1]);

	if((fp1 = fopen(f1_name,"rb")) == 0 
		||(fp2 = fopen(f2_name,"rb")) == 0){ /*if either of the files do not open*/
		return 3;
	}
	

	if(l_switch){
		if(!comp_by_line(fp1, fp2, f1_name, f2_name, i_switch)) /* compare char by char option: default*/	
			return 1; /*not equal*/
	}

	if(w_switch){
		if(!comp_by_word(fp1, fp2, f1_name, f2_name, i_switch)) /* compare char by char option: default*/	
			return 1; /*not equal*/
	}
	
	if(!l_switch && !w_switch){
		if(!comp_by_char(fp1, fp2, f1_name, f2_name,i_switch)) /* compare char by char option: default*/	
			return 1; /*not equal*/
	} 

	printf("%s\n", "files are equal");

	if((fclose(fp1)!=0) 
		&& (fclose(fp2) !=0)){/*if a file does not close*/
		return 3;
	}

	return 0;
}

/**
 * this method is the main method that will be called if the the program is running a 
 * compare character by character. 
 * The methods will iterate through each character and the moment one of the characters are not the same. 
 * the program will return a 0. If both files are the same but one ends before another, the program will also return a 0;
 * 
 * @param  f1 first file pointer
 * @param  f2 second file pointer 
 * @param  f1_name name1 of file as a string literal
 * @param  f2_name name2 of file as a string literal
*  @return  1 if successful (if files comapered are considered equal per character) , 0 if failed;
 */
int comp_by_char(FILE * fp1, FILE *fp2, char f1_name[], char f2_name[], int ignore_caps){
	long file_len1, file_len2, file_len_min, file_len_max;
	int c1, c2; /*the chars retrived at each location*/
	size_t count = 1;
	char *eof_on_file;	
	file_len1 = get_file_size(fp1);
	file_len2 = get_file_size(fp2);
	
	if (empty_files(file_len1,file_len2)){
		return 1;
	}

	if(one_empty_file(file_len1,file_len2)){
		printf("files differ: char %d\n",(int)count);
		return 0;
	}
	

	file_len_min = min_size(file_len1, file_len2);
	file_len_max = max_size(file_len1, file_len2); 

	init_read(fp1); /*goes to beginning of file*/
	init_read(fp2);/*goes to beginning of file*/
	while((c1 = (ignore_caps? tolower(fgetc(fp1)):(fgetc(fp1)))) != EOF
	 		&&(c2 = (ignore_caps? tolower(fgetc(fp2)):(fgetc(fp2)))) != EOF){ /*while neither c1 nor c2 are EOF*/
				if(c1 != c2){ /* assigne c1,c2 and compare*/
					printf("files differ: char %ld\n",(long)count);	
					return 0; /*return at not equal*/
				}
				count++; 	
	}
	
	if(file_len_min != file_len_max){
			eof_on_file = (file_len1 == file_len_min)? f1_name: f2_name;
			printf("EOF on %s\n", eof_on_file);	
			return 0; /*return at not equal*/
	} /* get next char, should be EOF*/	
	
	return 1;
}
/**
 * This is the method called when the user requests two files compared word by word 
 * regardless of the number of space between the words, 
 * the program will compare the instance the first word differs 
 * the words between the files must be in order.
 * 
 * @param  fp1 first file for comaprison
 * @param  fp2 second file for comparison
 * @param  f1_name the name of file 1 as a string literal 
 * @param  f2_name the name of file 2 as a string literal 
 * 
 * @return     1 if the files contain the exact same words in the same order, 0 otherwise 
 */
int comp_by_word(FILE *fp1, FILE *fp2, char f1_name/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment2.game.chess;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 *
 * @author Eva
 */
public class ChessBoard extends JFrame {

    final static int BOARD_SIZE = 8;

    public static void main(String args[]) {
        final Color HOTPINK = new Color(251, 12, 138);
        final Color BUBBLEGUM = new Color(35, 210, 254);
        JFrame.setDefaultLookAndFeelDecorated(true);
        JFrame chessFrame;
        GridLayout boardLayout;
        JButton[][] BoardSpace = new JButton[BOARD_SIZE][BOARD_SIZE];

        chessFrame = new JFrame("HOTPINK BUBBLEGUM BUTTON PUSH"); // sets the frame to but the grid layout 
        chessFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        boardLayout = new GridLayout(BOARD_SIZE, BOARD_SIZE);// creates a grid layout 
        chessFrame.setLayout(boardLayout);

        for (int i = 0; i < BOARD_SIZE; i++) { //  creates the botton for each panel 
            for (int j = 0; j < BOARD_SIZE; j++) { //  creates the botton for each panel 
                chessFrame.add(BoardSpace[i][j] = new JButton("I AM: " + (i * BOARD_SIZE + j + 1)));
                BoardSpace[i][j].setPreferredSize(new Dimension(80, 80));
                if ((i + j) % 2 == 0) {
                    BoardSpace[i][j].setBackground(HOTPINK);
                } else {
                    BoardSpace[i][j].setBackground(BUBBLEGUM);
                }
                BoardSpace[i][j].addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent e) {
                        System.out.println("BUTTON PUSHED");
                    }
                });
            }//end inner for 
        }//end out for 
        chessFrame.pack();
        chessFrame.setVisible(true);
    }//end main 
}//end ChessBoard class
[], char f2_name[], int ignore_caps){
	char *eof_on_file;
	char f1_word[LINESIZE], f2_word[LINESIZE];
	long file_len1, file_len2, file_len_min, file_len_max;
	size_t i,j, count = 1;
	
	file_len1 = get_file_size_word(fp1);
	file_len2 = get_file_size_word(fp2);	
	
	file_len_min = min_size(file_len1, file_len2);
	file_len_max = max_size(file_len1, file_len2); 	

	if (empty_files(file_len1,file_len2)){
		return 1;
	}

	if(one_empty_file(file_len1,file_len2)){
		printf("files differ: word %d\n",(int)count);
		return 0;
	}
	
	init_read(fp1);
	init_read(fp2);
	
	while((fscanf(fp1,"%s", f1_word) != EOF)
		&& (fscanf(fp2,"%s", f2_word) != EOF)){

		if (ignore_caps){
			for (i = 0; f1_word[i]; i++){
				f1_word[i] = tolower((unsigned)f1_word[i]);
			}
			for (j = 0; f2_word[j]; j++){
				f2_word[j] = tolower((unsigned)f2_word[j]);
			}
			if(strcmp(f1_word, f2_word) !=0){
				printf("files differ: word %ld\n",(long)count);
				return 0;
			}
			count++;
		}

		if(!ignore_caps){
			if(strcmp(f1_word, f2_word) !=0){
				printf("files differ: word %ld\n",(long)count);
				return 0;
			}
			count++;
		}
	}

	if(file_len_min != file_len_max){
		eof_on_file = (file_len1 == file_len_min)? f1_name: f2_name;
		printf("EOF on %s\n", eof_on_file);	
		return 0; /*return at not equal*/
	}

	return 1;
}

/**
 * This method read files line by line to compare .
 * it tokenizes a line to represent each word and compares the words to make sure
 *  they are the same. The moment it is not the same, the progarm will exit.
 *  this progarm will return a 0 under the following circumstances:
 *  -  both files are equal except one file ends before another
 *  -  the moment one file differs from another
 *  the progarm also counts the number of lines read   
 * 
 * @param  fp1 this is a file pointer to the first file
 * @param  fp2 this is a file pointer to the second file
 * @param  f1_name name of file 1 as a string literal
 * @param  f2_name name of file 2 a string literal
 * @return     returns a 1 upon a successful comparison of a file(files are considered equal line by line), 0 otherwise.

 */
int comp_by_line(FILE * fp1, FILE *fp2, char f1_name[], char f2_name[], int ignore_caps){ 
	
	char f1_line[LINESIZE], f2_line[LINESIZE];
	long file_len1, file_len2, file_len_min, file_len_max;
	size_t count = 1, i ,j;
	char f1_word[LINESIZE], f2_word[LINESIZE];
	char *token_l1,*token_l2, *delim = " ", *eof_on_file; 
	
	file_len1 = get_file_size_word(fp1);
	file_len2 = get_file_size_word(fp2);
	
	file_len_min = min_size(file_len1, file_len2);
	file_len_max = max_size(file_len1, file_len2); 	

	if (empty_files(file_len1,file_len2)){
		return 1;
	}

	if(one_empty_file(file_len1,file_len2)){
		printf("files differ: line %d\n", (int)count);
		return 0;
	}

	init_read(fp1);
	init_read(fp2);
	 
	while(fgets(f1_line, LINESIZE, fp1) 
		  && fgets(f2_line, LINESIZE, fp2)){

		token_l1 = strtok(f1_line, delim);/*tokens the line from file 1*/
		token_l2 = strtok(f2_line, delim);/*tokens the line from file 2*/

		while(token_l1 && token_l2){
				
			strcpy(f1_word, token_l1);
			strcpy(f2_word, token_l2);
			for(i=0; f1_word[i]; i++){
				if(isspace((unsigned)f1_word[i]))
					break;							
			}
			f1_word[i] = '\0';

			for(j=0; f2_word[j]; j++){
				if(isspace((unsigned)f2_word[j]))
					break;							
			}
			f2_word[j] = '\0';

			if(f1_word[0] == '\0' || f2_word[0] == '\0'){
				break;
			}
			
			if(ignore_caps){
				if(strcasecmp(f1_word, f2_word) != 0){
					printf("files differ: line %ld\n",(long)count);	
					return 0;
				}
			}else{
				if(strcmp(f1_word, f2_word) != 0){
					printf("files differ: line %ld\n",(long)count);	
					return 0;
				}
			}
		
			token_l1 += strlen(token_l1) + 1;
    		token_l2 += strlen(token_l2) + 1;

			token_l1 = strtok(token_l1, delim);
    		token_l2 = strtok(token_l2, delim);
		}
		
		count++;
	}

	if((fgets(f1_line, LINESIZE, fp1) || fgets(f2_line, LINESIZE, fp2))
		&&(strcmp(f1_word, f2_word))){
			printf("files differ: line %ld\n",(long)--count);	
			return 0;
	}	

	if(fgets(f1_line, LINESIZE, fp1) || fgets(f2_line, LINESIZE, fp2)){ 
		eof_on_file = (file_len1 == file_len_min)? f1_name: f2_name;
		printf("EOF on %s\n", eof_on_file);	
		return 0;		
	}
	/*the following if statement is totally a hack.. I dont know why it works*/
	if((file_len_min != file_len_max) && (count == 2)){
			printf("files differ: line %ld\n",(long)--count);	
			return 0;
	}

	if((file_len_min != file_len_max)){
		eof_on_file = (file_len1 == file_len_min)? f1_name: f2_name;
		printf("EOF on %s\n", eof_on_file);	
		return 0;
	}

	return 1;
}
/**
 * Method comapres the sizes of the file accoridng to the length of chars they have 
 * If the file is a different size, the program terminates. 
 * @param  f1 [description]
 * @param  f2 [description]
 * @return    1 if the files are the same size ( length of chars)
 */
long get_file_size(FILE *fp){
	long pos_fp;
	fseek(fp,-1,SEEK_END);
	pos_fp = ftell(fp);
	return pos_fp;
}

/**
 * This method counts the number of words or string literals sererated by spaces in a file.
 * @param  fp this file to be counted
 * @return    the number of words found in the file.
 */
long get_file_size_word(FILE *fp){
	long word_count = 0;
	int flag = 0; /*keeps a flag to indicate a new word*/
	int c;
	while((c=fgetc(fp)) != EOF){
		if(!flag && (!isspace((unsigned)c))){
			word_count++;
			flag = 1;
		}
		if (flag && isspace((unsigned)c))
			flag = 0;
	}
	return word_count;
}
/**
 * This method checks if the length of both files are zero, inidcating that they are both empty
 * 
 * @param  file_len1 long that signifies length of measurement of firstfile
 * @param  file_len2 long that signifies length of measurement of second file
 * @return           0 if the fiels are no empty, 1 if the files are both empty
 */
int empty_files(long file_len1, long file_len2){
	if(!file_len2 && !file_len1){
		return 1;
	}
	return 0;
}
/**
 * This method checks if there is one file empty, excluisvely. 
 * 
 * @param  file_len1 long indicating length of first file
 * @param  file_len2 long indicating length of second file
 * @return           1 if there is one empty file amongst the two, 0 otherwise
 */
int one_empty_file(long file_len1, long file_len2){
	if((!file_len2 && (file_len1 > 0)) 
		|| (!file_len1 && (file_len2 > 0))){
		return 1;
	}
	return 0;
}
/**
 * This method returns the shorter of the length of two long numbers
 ***this method will prevent overflowing while reading the files 
 *  
 * @param  filesize1 long that represents the size of the first file
 * @param  filesize2 long the represent the size of the second file
 * @return           returns the smaller value 
 */
long min_size(long filesize1, long filesize2){
	return (filesize1 > filesize2)? filesize2: filesize1; 
}
/**
 * This method returns the longer of the length of two long numbers 
 *  
 * @param  filesize1 long that represents the size of the first file
 * @param  filesize2 long the represent the size of the second file
 * @return           returns the larger value
 */
long max_size(long filesize1, long filesize2){
	return (filesize1 < filesize2)? filesize2: filesize1; 
}
/**
 * Method that makes sure the reading of the file beigns at the begiining 
 * @param fp [description]
 */
void init_read(FILE *fp){
	fseek(fp,0,SEEK_SET);
}
