#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  while(1){

    //read input line
    char* line = (char*) calloc(50,sizeof(char));
    fgets(line,50,stdin);
    line[strlen(line)-1] = '\0';

    //command's space split
    char* cmd = strtok(line," ");
    char* cmd2 = strtok(NULL," ");

    //loop's break condition
    if(line[0] == '*'){
      break;
    }

    //algorithm....
    if(strcmp(cmd,"") == 0){

    }

    free(line);

  }
}