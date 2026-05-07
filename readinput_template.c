#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  while(1){

    //read input line
    char* line = (char*) calloc(50,sizeof(char));
    fgets(line,50,stdin);
      
    // remove '\n'
    line[strcspn(line, "\n")] = '\0';

    //loop's break condition
    if(line[0] == '*'){
      break;
    }

    //command's space split
    char* cmd = strtok(line," ");
    char* cmd2 = strtok(NULL," ");

    // algorithm
    if(strcmp(cmd, "insert") == 0){
      // xử lý insert
    }
    else if(strcmp(cmd, "delete") == 0){
      // xử lý delete
    }
    else if(strcmp(cmd, "print") == 0){
      // xử lý print
    }

    free(line);

  }
}
