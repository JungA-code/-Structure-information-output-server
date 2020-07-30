#include <stdio.h>  
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHSIZE 300

       typedef struct tag_st { 
        int num;
        char ch; 
       }basic;
   
       typedef struct {
          basic st;   int *p; 
          long double ldar[128];
      } contain;  
 
int main(int argc, char *argv[]){
	int shmid; // 공유메모리 아이디 
	key_t key; // 공유메모리 접근 키 
	void* addr;
	
	contain data;

	
	key = 2020; 

	//공유 메모리생성
     shmid = shmget(key, SHSIZE, IPC_CREAT | 0666);
     if(shmid < 0){ //error = -1
         perror("shmget");
         exit(0);    
     }

	// 공유 메모리를 사용하기 위해 프로세스 메모리에 붙인다. 
	addr = shmat(shmid, NULL, 0);
     if(addr == (char *) -1){
         perror("shmat");
         exit(1);
     }
	
	(*(contain*)addr).ldar[0] = 2.3;

	printf("%.2Lf \n", (*(contain*)addr).ldar[0]);
	
	return 0;
}
