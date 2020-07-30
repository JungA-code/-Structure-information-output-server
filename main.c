#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>

char rcvbuff[BUFSIZ];
char sndbuff[BUFSIZ];

pthread_t thread; 
pthread_mutex_t mutex;

char greeting[ ] = "hello clinet , I'm server";

void *sendMsg(void *);

int main(int argc, char *argv[ ])
{
	int c_socket, s_socket;
    struct sockaddr_in s_addr, c_addr;
    int    len;
    int    i, j, n;
    int    res;

if(pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Can not create mutex\n");
        return -1;
    }

    s_socket = socket(PF_INET, SOCK_STREAM, 0);
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);

    if(bind(s_socket, (struct sockaddr *)&s_addr, sizeof(s_addr)) == -1) {
        printf("Can not Bind\n");
        return -1;
    }

    if(listen(s_socket, MAX_CLIENT) == -1) {
        printf("listen Fail\n");
        return -1;
    }
 while(1) {
        len = sizeof(c_addr);
        c_socket = accept(s_socket, (struct sockaddr *) &c_addr, &len); // 클라이언트 접속 허용 
      //  res = pushClient(c_socket); //접속한 클라이언트를 list_c에 추가
        //if(res < 0) { //MAX_CLIENT만큼 이미 클라이언트가 접속해 있다면,
          //  write(c_socket, CODE200, strlen(CODE200)); // 에러코드 보내주기 
           // close(c_socket);
        //} else { // 클라이언트가 접속했다면  
            write(c_socket, greeting, strlen(greeting));
            //pthread_create with do_chat function.
            pthread_mutex_lock(&mutex); // 락걸기 
            pthread_create(&thread, NULL, sendMsg, (void*)&c_socket); // 스레드 만들기
		    pthread_mutex_unlock(&mutex); // 락 풀기 
        //}
    }

}



void *sendMsg(void *arg)
{
	 int c_socket = *((int *)arg);
	 
	
}
