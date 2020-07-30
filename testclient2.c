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

	char *strName;
	char *value;
 
	key = 2020;	
	shmid = shmget(key, SHSIZE, 0666);
	if(shmid < 0){
		perror("shmget");
		exit(0);	
	}
		

	shm = shmat(shmid, NULL, 0);
	if(shm == (char *) -1){
		perror("shmat");
		exit(1);
	}

	for(s = shm; *s != 0; s++){
		printf("%c", *s);	
	}
	printf("\n");

	*shm = '*';

	return 0;
}


