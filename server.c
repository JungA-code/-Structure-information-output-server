#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHSIZE 100

int main(int argc, char *argv[]){
	int shmid; //쉐어메모리 아이디
	key_t key;
	char *shm;
	char *s;

	key = 2020;	
	shmid = shmget(key, SHSIZE, IPC_CREAT | 0666);
	if(shmid < 0){
		perror("shmget");
		exit(0);	
	}
		

	shm = shmat(shmid, NULL, 0);
	if(shm == (char *) -1){
		perror("shmat");
		exit(1);
	}

	memcpy(shm, "Hello World", 11); //메모리에 복사 
	s = shm;
	s += 11;

	*s = 0;

	while(*shm != '*'){
		sleep(10);
		
	}
	
	
	
	return 0;
}


