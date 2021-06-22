// Declare all helper functions for hw1 in this file
#include <stdio.h> 
char checkFlags(char* argv){
   if(argv[0] == '-'){
	if(argv[1] == 'Q'){
	   return argv[1];	
	}
	if(argv[1] == 'N'){
	   return argv[1];	
	}
	if(argv[1] == 'P'){
	   return argv[1];	
	}
	return -1;	
   }
   return 0;
}

int checkPun(const char ch, const char* pun_str){
    int i = 0;
    for(i = 0; pun_str[i]; i++){
        if(ch == pun_str[i]){
            return 1;
        }
    }
    return 0;
}

int compare(int a, int b){	
   if(a > b){
	return a;
   }
   return b; 
}

int countSentences(const char ch, const char previousCh, const char* pun_str){
   if(ch == '\n' && !checkPun(previousCh, pun_str) && previousCh != '\n'){
	        return 1; 	
   }	
   if(checkPun(ch, pun_str) && !checkPun(previousCh, pun_str) 
		&& previousCh != 0 && previousCh != '\n'){
	        return 1;	
   }
   return 0;
}