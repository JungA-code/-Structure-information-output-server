  #include <stdio.h>                                                           
   #include <stdlib.h>
   #include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHSIZE 100

typedef struct tag_st { 
           int num;
           char ch; 
          }basic;
      
typedef struct {
             basic st;   int *p; 
             long double ldar[128];
         }contain;   
   

int main(int argc, char *argv[]){
	int shmid; //쉐어메모리 아이디
	key_t key;
	void *addr;

    contain data;

	char *strName;
	char *value;
 
	key = 2020;	

	// 공유메모리 생성
	shmid = shmget(key, SHSIZE, 0666);
	if(shmid < 0){
		perror("shmget");
		exit(0);	
	}
		
	
	addr = shmat(shmid, NULL, 0);
	if(addr == (void *) -1){
		perror("shmat");
		exit(1);
	}

	printf("\n----------------------struct info----------------------\n");
	
	printf("st.num : %d\n", (*(contain*)addr).st.num);
	printf("st.ch : %c\n",(*(contain*)addr).st.ch);
	printf("*p : %d\n", (*(contain*)addr).p);
	printf("ldar[n] : null is skip\n");
	int i = 0;
	for(i=0; i<128; i++){

	if((*(contain*)addr).ldar[i] == 0.0) continue;

	printf("ldar[%d] : %.2Lf\n",i ,(*(contain*)addr).ldar[i]);
	
	}
	printf("-------------------------------------------------------\n");
	

	return 0;
}



