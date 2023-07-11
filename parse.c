#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
#include <ctype.h> 

char* gram[26];
int row = 0;
extern char* yytext;
extern int yylineno;
extern int yylex();
int lookahead;

/* Function prototypes */
void error(const char *msg);
void match(int token);
void prod_list();
void production();
void production_body();
void rule();
void printgram(char* ary[26], int rows);
void init_lenAry(char* ary[26], int rows, int len[]);
int contains(char arr[], int size, char ch);
void remove_hash(char str[]);


// Functions to calculate CFG_Follow 
void CFG_Follow(char c); 
void followfirst(char c, int c1, int c2);

// Function to calculate First 
void Searching_First(char, char* gram[], int end); 
char *follow, *first; 
char *term;
int t;
int n; 
// Stores the final result of the First Sets 
char FirstCalculation[26][100]; 
// Stores the final result of the CFG_Follow Sets 
char calc_CFG_Follow[26][100]; 
int m; 

// Stores the production rules 
int beenhere;
int len_ar[26];
char save, ck;
int hash;
int end;
int k;
int kay;
int e;

int main(int argc, char **argv) {
    int km= 0;
    int jm = 0; 
    int l1 = 0, l2, tmp;
	char done[row]; 
	int ptr = -1; 
    char c,ch;

    // Allocate memory for each character pointer
    for (int i = 0; i < 26; i++) {
        gram[i] = malloc(100 * sizeof(char));
    }
    lookahead = yylex();       
    prod_list();     

    if (lookahead == 0){ // no more input 
        printgram(gram, row);

    // Initializing the FirstCalculation array 
	for(int k = 0; k < row; k++) { 
		for(kay = 0; kay < 100; kay++) { 
			FirstCalculation[k][kay] = '!'; 
		} 
	} 

    init_lenAry(gram, row, len_ar);
    printf("First Sets: \n");
    printf("epsilon is identified with '#' \n");

    for(int i = 0; i < row; i++) {
        end = 0;  
        t =0;
        first = (char*) calloc(100, sizeof(char));
        term = (char*) calloc(100, sizeof(char));
        hash = 0;
        n = 0;
		c = gram[i][0]; 
        beenhere = 0;
		l2 = 0; 
		tmp = 0; 	

		// Checking if First of c has already been calculated 
		for(int j = 0; j <= ptr; j++) 
			if(c == done[j]) 
				tmp = 1; 
				
		if (tmp == 1) 
			continue; 

        // Function call	 
		Searching_First(c, gram,0); 
		ptr += 1; 

        // Adding c to the calculated list 
		done[ptr] = c;       
        printf("\n %c : { ", c);
		FirstCalculation[l1][l2++] = c;

        // Printing the First Sets of the grammar 
		for(int id = 0 + jm; id < n; id++) { 
			int lark = 0, chk = 0; 
			
			for(lark = 0; lark < l2; lark++) { 
				
				if (first[id] == FirstCalculation[l1][lark]) 
				{ 
					chk = 1; 
					break; 
				} 
			} 
			if(chk == 0) 
			{ 
				printf("%c ", first[id]); 
				FirstCalculation[l1][l2++] = first[id]; 
			} 
		} 
		printf("}\n"); 
		l1++; 

        free(first);
        first = NULL;
        free(term);
        term = NULL;
        }
    }
    //    printf("accepted with %d num of rows\n",row);
    printf("\n");
	char donee[row]; 
	ptr = -1; 
	// Initializing the calc_CFG_Follow array 
	for(k = 0; k < row; k++) { 
		for(kay = 0; kay < 100; kay++) { 
			calc_CFG_Follow[k][kay] = '!'; 
		} 
	} 
    l1 = 0;
    int land = 0; 

     printf("Follow Sets: \n");

    for(e = 0; e < row; e++) 
	{ 
        m = 0;
        follow = (char*) calloc(100, sizeof(char));

        ck = gram[e][0];
        l2 = 0;
        tmp = 0;

        // Checking if CFG_Follow of ck 
		// has alredy been calculated 
		for(kay = 0; kay <= ptr; kay++) 
			if(ck == donee[kay]) 
				tmp = 1; 
				
		if (tmp == 1) 
			continue; 
		land += 1; 
		
		// Function call 
		CFG_Follow(ck); 
		ptr += 1; 

        // Adding ck to the calculated list 
		donee[ptr] = ck; 
		printf("%c : { ", ck); 

		calc_CFG_Follow[l1][l2++] = ck; 

        // Printing the CFG_Follow Sets of the grammar 
		for(int i = 0 + km; i < m; i++) { 
			int lark = 0, chk = 0; 
			for(lark = 0; lark < l2; lark++) 
			{ 
				if (follow[i] == calc_CFG_Follow[l1][lark]) 
				{ 
					chk = 1; 
					break; 
				} 
			} 
			if(chk == 0) 
			{ 
				printf("%c ", follow[i]); 
				calc_CFG_Follow[l1][l2++] = follow[i]; 
			} 
		} 
		printf(" }\n\n"); 
		l1++; 

        free(follow);
        follow = NULL;
	} 

    return 0;
}

void Searching_First(char c,char* ary[26],int end) 
{ 
	int i;  
    if(strlen(term) == row){
        return;
    }
    if(islower(c)){       
        if(contains(first, strlen(first), c) == 0){ // does not exits in the first array

            if(first[strlen(first)-1]=='#' && hash == 0){
                first[strlen(first)-1] = c;
            }else{
                
                first[n++] = c;
            }    
            return; 
        }    
    }
    if(contains(term, strlen(term), save) == 1){
        return;
    }
	for(i = 0; i < row; i++) 
	{ 
		if(gram[i][0] == c) 
		{ 
            
            for (int loc=4;loc < len_ar[i]; loc++){
                save = gram[i][0]; 
                if(save == gram[i][loc]){// this in the else
                    Searching_First(gram[i][loc+1], ary,end);
                    continue;
                }if(isupper(gram[i][loc])){//
                    if(contains(term, strlen(term), gram[i][loc]) == 0){ // does not exist in the term array
                        Searching_First(gram[i][loc], ary,end); 
                    }else{
                        while(gram[i][loc] != '|' && gram[i][loc] != ';' ){
                            loc++;
                        }
                        if(gram[i][loc] == ';'){
                            return;
                        }else{
                            loc--;
                            continue;
                        }
                    }     
                    continue; 
                }if(islower(gram[i][loc])){
                    Searching_First(gram[i][loc], ary,end);

                    if(contains(first, strlen(first), gram[i][loc]) == 1){

                        while(gram[i][loc] != '|' && gram[i][loc] != ';' ){
                            loc++;
                        }
                        if(gram[i][loc] == ';'){
                            term[t++] = save;
                            return;
                        }else{
                            loc--;
                            continue;
                        }
                    }
                }if((gram[i][loc] == '|') && (gram[i][loc+1] == '\n') ){
                    if(contains(first, strlen(first), '#') == 0 && contains(term, strlen(term), save) == 0){ // does not exist in the term array
                        first[n++] = '#'; // epsilon
                    }
                    continue; 
                } if((gram[i][loc] == '\n') && (gram[i][loc+1] == ';') ){

                    if(contains(term, strlen(term), save) == 0){ // does not exist in the term array
                        term[t++] = save;
                    }  
                   return;//do nothing
                }if((gram[i][loc] == '|') && gram[i][loc+1] == save){
                    Searching_First(gram[i][loc+2], ary,end);
                    continue; 
                }if((gram[i][loc] == '|') && islower(gram[i][loc+1] && hash == 0)){//new
                    Searching_First(gram[i][loc+1], ary,end);
                    continue; 
                }else{
                //do nothing
                }
            }

		} 
       
	} 
    return;
} 

void CFG_Follow(char c) {
    int i, j; 
    // Adding "$" to the CFG_Follow, set of the start symbol 
	if(gram[0][0] == c) { 
		follow[m++] = '$'; 
	} 
    for(i = 0; i < row; i++) {
        for(j = 4;j < len_ar[i]; j++) {

            if(gram[i][j] == c){

                if(gram[i][j+1] != '|' && gram[i][j+1] != ';'){
                    // Calculate the first of the next 
					// Variable (Non-Terminal ) in the production 
                    followfirst( gram[i][j+1], i , (j+2));
                }if(gram[i][j+1]==';' && c!=gram[i][0]){
                    // Calculate the CFG_Follow of the Variable (Non-Terminal )                                                      │
                    // in the L.H.S. of the production                                                                               │
                    CFG_Follow(gram[i][0]); 
                }              
            }
        } 
    } 
}

void followfirst(char c, int c1, int c2){
    int k;
 
    // The case where we encounter
    // a Terminal
    if (islower(c)){
        follow[m++] = c;
    }else {
        int i = 0, j = 1;
        for (i = 0; i < row; i++) {
            if(FirstCalculation[i][0] == c) 
				break; 
        }
        //Including the First set of the 
		// Variable (Non-Terminal ) in the CFG_Follow of 
		// the original query 
        while(FirstCalculation[i][j] != '!' && FirstCalculation[i][j] != '\000'){ 
            if(FirstCalculation[i][j] != '#'){ 
				follow[m++] = FirstCalculation[i][j]; 
			}else{
                if(gram[c1][c2] == '|' || gram[c1][c2] == ';' ){
                    // Case where we reach the 
					// end of a production 
					CFG_Follow(gram[c1][0]); 
                } else{ 
					// Recursion to the next symbol in case we encounter a "#" 
					followfirst(gram[c1][c2], c1, c2+1); 
				} 
            }
            j++;
        }
    }
    
}

void error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

void match(int token) {
    
    if (lookahead == token) {
        lookahead = yylex();
    } else {
        error("Syntax error: unexpected match token");
    }
}

void prod_list() {
    
    production();
    while (lookahead == NT) {
        production();
    }
    
}

void production() {  

    strcpy(gram[row],yytext);

    match(NT);

    strcat(gram[row],yytext);

    match(GOES);
    
    production_body();

    strcat(gram[row],yytext);

    match(SEMI);

    strcat(gram[row],yytext);

    match(EOL);  

    row++;   
}

void production_body() {
    rule();
    while (lookahead == OR) {
        strcat(gram[row],yytext);

        match(OR);
        rule();
    }
}

void rule() {
    if (lookahead == NT) {

        strcat(gram[row],yytext);

        match(NT);
        rule();
    } else if (lookahead == T) {

        strcat(gram[row],yytext);

        match(T);
        rule();
    } else if (lookahead == EOL) {
        /* Empty production */
        strcat(gram[row],yytext);
        match(EOL);
    } else {
        error("Syntax error: unexpected rule token");
    }
}

void init_lenAry(char* ary[26], int rows, int len[]){
    for (int i = 0; i < rows; i++) {
        len[i] = strlen(ary[i]);
    }
}

void printgram(char* ary[26], int rows) {
    
    // Print each string in the array
    for (int i = 0; i < rows; i++) {
        printf("%s \n", gram[i]);
    }
}

int contains(char arr[], int size, char ch) {
    int i;
    for (i = 0; i < size; i++) {
        if (arr[i] == ch) {
            return 1; // the character is found in the array
        }
    }
    return 0; // the character is not found in the array
}

void remove_hash(char* str) {
    int len = strlen(str);
    if (len > 1) {  // check if string has more than one character
        if (str[0] == '#' || str[len-1] == '#') {
            //do nothing
        }
        
            for (int i = 1; i < len-1; i++) {
                if (str[i] == '#') {
                    memmove(&str[i], &str[i+1], len-i);
                }
            }
        
    }
}
