// Natcha Jengjirapas 
// Njengjir 

#include "hw1.h"
#include "helpers1.h"
#include <stdio.h> 
#include <stdlib.h>
// You may define any helper functions you want. Place them in helpers.c/.h

// Main program
int main(int argc, char *argv[]) {
    // Insert your hw1 code here
    return manager(argc, argv);
}

int manager(int argc, char **argv){
    char* pun_str = malloc(sizeof(char) * 10);
    int Q = 0;
    int i = 0;
    int j = 0;
    int length = 140;
    char flag;
    
    // default pun_str
    pun_str[0] = '.';
    pun_str[1] = '!';
    pun_str[2] = '?';
    pun_str[3] = '\0';
    
    for(i = 1; i < argc; i++){
        flag = checkFlags(argv[i]);
        if(flag == 'Q'){
            Q = 1;
        }
        if(flag == 'N'){
            i++;
            length = atoi(argv[i]);
            if(length <= 0){
                fprintf(stderr, USAGE);
                return 1;
            }
        }
        if(flag == 'P'){
            i++;
            for(j = 0; argv[i][j]; j++){
                pun_str[j] = argv[i][j];
            }
	    pun_str[j] = '\0';
        }
        if(flag == -1){
            fprintf(stderr, USAGE);
            return 1;
        }
    }
    if(Q){
        for(j = 0; pun_str[j]; j++){
            if(pun_str[j] == 34){
                fprintf(stderr, USAGE);
                return 1;
            }
        }
    }
    //return 0;
    return run(Q, length, pun_str);
}

int run (const int Q, const int length, const char* pun_str){
    char* string = malloc(sizeof(char) * length);
    long fileSize;
    int i = 0;
    int count = 0; 
    int longestCh = 0;
    int sentences = 0; 
    int endSentence = 1; // bool 
    char ch; 
    char previousCh = 0;
    while((ch = getchar()) != EOF){
	if(Q){
	   if(ch == 34 && i == 0){
		//printf("{%c}",ch);
	    	string[i++] = ch; 
		endSentence = 0;
	    }	
	    //printf("%d",string[0] == 34);
	    if(i > 0 && i < length && string[0] == 34 && ch != 34){
		//printf("(%c)",ch);
		string[i++] = ch; 
	    }
	    //printf("%d", (i > 1));
	    if(ch == 34 && (i > 0 && i < length) && endSentence){
		//printf("[%c]",ch);
		if(string[0] != 0){
			string[i++] = ch; 
	        	printf("%s\n", string);
		}
	        string = realloc(NULL, sizeof(char) * length);
		i = 0;
	    }
   	    if(i >= length ){
		//printf("%d %c",i, previousCh);
		string = realloc(NULL, sizeof(char) * length);
		i = 1;
		if(ch == 34){
		  	i = 0;		
		}
		//count = 1;
	    }
	    //printf("<%c>",ch);
	    endSentence = 1;
	}
	if(!Q){
	    if((ch != '\n' && !checkPun(ch, pun_str)) 
		&& (i <= length) 
		&& (i != 0 || (ch != 32 && ch != 9))){
		string[i++] = ch; 
            }
	    if(ch == '\n' && i != 0){
		if(!checkPun(previousCh, pun_str) 
		   && i <= length && previousCh != '\n'){
			string[i++] = ch;
			printf("%s", string);
			string = realloc(NULL, sizeof(char) * length);
	 	}
		i = 0; 
	    }
	    if(checkPun(ch, pun_str)){
		if(!checkPun(previousCh, pun_str) 
		   && i <= length && i != 0){
			string[i++] = ch;
			printf("%s\n", string);
			string = realloc(NULL, sizeof(char) * length);
		}
		i = 0;
	    }
	    if(i > length){
	    	string = realloc(NULL, sizeof(char) * length);
	    }

	    // counting sentences and longest characters 
	    if(countSentences(ch, previousCh, pun_str)){
		if(ch == '\n'){
		    longestCh = compare(count, longestCh);
	    	    count = 0;
	            endSentence = 1; // True 
		}
		if(checkPun(ch, pun_str)){
		    count++;
		    longestCh = compare(count, longestCh);
	    	    count = 0;
	            endSentence = 1; // True 
		}
	    }else{
	    	if(ch != 32 && ch != 9 && ch != '\n' 
		   && !checkPun(ch, pun_str) || !endSentence ){
	    	    count++;
		    endSentence = 0; // False
	    	}
	    }
	    sentences += countSentences(ch, previousCh, pun_str);
        }
	if(ch != 9 && ch != 32){
	    previousCh = ch; 
	}
    }
    
    if(!Q){
	if(i <= length && count != 0 && string[i-1] != '\n'){
	    printf("%s\n",string);
	}
	if(previousCh != '\n' && !checkPun(previousCh, pun_str)){
	    sentences++;
	}
	longestCh = compare(count, longestCh);
    	fprintf(stderr, "%d %d\n", sentences, longestCh); 
    }
    free(string);
    if((fileSize = ftell(stdin)) == 0){
        return 2;
    }
    return 0;
}