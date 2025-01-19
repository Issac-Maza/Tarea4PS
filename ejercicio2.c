#include <stdio.h>
#include <stddef.h>
#define MAX 4 
pid_t mas(int i, int execute){ 
pid_t t = fork(); 
if(t == 0){ 
     if(i != 0){ 
         printf("pid %d ppid %d\n",getpid(),getppid()); 
         printf("mas %d\n", i); 
         while(1); 
     } 
     else{  
        if(execute){ 
              execl("./a.out","./a.out", "0", NULL);           
         } 
 } 
} 
else 
     return t; 
return -1; 
} 
  
int main(int argc, char** argv){ 
 pid_t d = getpid(); 
 printf("pid %d\n",d);  
 pid_t back[4] = {-1}; 
  
 for(int j = MAX-1; j >= 0; j--){ 
  if(d == getpid()){ 
   back[j] = mas(j, atoi(argv[1])); 
  } 
 } 
 for(int i = 0; i < MAX; i++) 
  waitpid(back[i], NULL,0); 
  return 0; 
}
