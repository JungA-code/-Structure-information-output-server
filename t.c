#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>

#define SIZE 1000
#define PORT 9000
#define SHSIZE 300   

void do_send(int);
void Msg(int);
void SHM_Create();
void SHM_Update(int);

char sendBuf[SIZE];
char readBuf[SIZE];

typedef struct tag_st { 
	int num;
    char ch; 
} basic;
    
typedef struct {
    basic st;   int *p; 
	long double ldar[128];
} contain;  


int shmid; // 공유메모리 아이디 
key_t key; // 공유메모리 접근 키 
void* addr;
            
contain data;

void EraseSpace(char str[]){
	char temp[64];
	int i, index = 0;

	for(i=0; str[i] != 0; i++){
		if(str[i] == '\n'){
			str[i] = '\t';
		}
	}

	for(i = 0; str[i] != 0; i++){
		if(str[i] != '\t'){
			temp[index] = str[i];
			index++;
		}
	}
	
	
	temp[index] = 0; 
	
	index = 0;
	for(i = 0; temp[i] != 0; i++){
		str[index] = temp[i];
		index++;	
	}	
	
	str[index] = 0;
}

char *toknizer(char *dest, const char *tok, char **next)
{
   char *ret = NULL;

   if (dest == NULL)
   {
      dest = *next;
   }

   ret = strstr(dest, tok);
   if (ret)
   {
      *ret = '\0';
      *next = ret + strlen(tok);
   }

   return dest;
}
 
int ret = 1; // SHMcreate  T/F T=0 F=1

int main(int argc, char *argv[ ]){

	int c_socket, s_socket;
    struct sockaddr_in s_addr, c_addr;
    int    len;
    int    i, j, n;
    int    res;
	
    s_socket = socket(PF_INET, SOCK_STREAM, 0);
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);

    if(bind(s_socket, (struct sockaddr *)&s_addr, sizeof(s_addr)) == -1) {
        printf("Can not Bind\n");
        return -1;
    }

    if(listen(s_socket, 5) == -1) {
        printf("listen Fail\n");
        return -1;
    }

	while(1){	
		len = sizeof(c_addr);
		c_socket = accept(s_socket, (struct sockaddr *) &c_addr, &len); // 클라이언트 접속 허용 
	
		printf("... server ... \n");	

		if(ret == 1){
			Msg(c_socket);
			SHM_Create();
		}

		printf("main3\n");
		SHM_Update(c_socket);
	
	}

	ret = 0;
	close(c_socket);
	close(s_socket);
	return 0;	
}

void SHM_Create(){

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
      }else{
			printf("ShardMemory Create Done..!\n");
			ret = 0;
		}   

}

void SHM_Update(int c){

	int c_socket = c;

	while(1){
	int n = 0;
	
	char name[30];
		name[0] = '\0';
		n  = read(c_socket, name, sizeof(name));

	char value[30];
		value[0] = '\0';
	char basic_name[30];
		basic_name[0] = '\0';
	char basic_value[30];	
		basic_value[0] = '\0';	

		if(strstr(name, "st")){
			printf("client select st\n");

			n  = read(c_socket, basic_name, sizeof(basic_name));
			printf("basic name : %s\n", basic_name);
    
		
			n = read(c_socket, basic_value, sizeof(basic_value));
			printf("basic value : %s\n", basic_value);

		
				if(strstr(basic_name, "num")){
					int val; 
					val = atoi(basic_value);
					(*(contain*)addr).st.num = val;
				}else if(strstr(basic_name, "ch")){
					char ch;
					ch = *basic_value;
					printf("client input val = %c\n", ch);
					(*(contain*)addr).st.ch = ch;
				}
				
		}else if(strstr(name, "p")){
			printf("client select p\n");

           n = read(c_socket, value, sizeof(value));
           value[n] = 0;
           printf("client put value : %s\n", value);         

			int k;
			k = atoi(value);
	
			printf("P value : %d\n", k);
			(*(contain*)addr).p = k;
			
		}else if(strstr(name, "ldar")){
				char idx[10]; 
				n = read(c_socket, idx, sizeof(idx));
				idx[n] = 0;
				printf("idx : %s\n", idx);				

			  n = read(c_socket, value, sizeof(value));
              value[n] = 0;
              printf("client put value : %s\n", value);  

				int index;
				long double val;
				val = atof(value);
				index = atoi(idx);
			(*(contain*)addr).ldar[index] = val;	
		}
	} //end while
}


void Msg(int n){
	int c_socket = n;
	FILE* rFILE = fopen("struct.h", "r");  
	FILE* wFILE = fopen("struct.log", "w");

	char strline[100]; 
	char cpline[1000];
	char *cutline;

	char str_read[SIZE];
	char *a = "struct";
	char *b = "}";
	char *c = ";";
 
	char *token = NULL;
	char *context = NULL;
	char *ptr = NULL;

	const char* arr[3];
	const char* arr2[3];
	const char* word = NULL;
	char tmp[100];

	char buf1[1000];	
	char buf2[1000];
	char buf3[1000];
	char buf4[1000];
	char buf5[1000];
	char sndBuf[1000];

	int cnt = 0;
	int sumcnt = 0;
	char TagName[ ] = "\\";
	char TypeName[20]; 
	char cntStr[5];
	char Msg[300];
	char Check[300];

	char structName[100]; // 구조체 멤버 체크 
	char *d = "basic";
 
	cpline[0] = '\0';
	strline[0] = '\0';

	while(fgets(strline, sizeof(strline), rFILE)){

		if(strstr(strline, ";")){
			strcat(cpline, strline);
		}
		
		if(strstr(strline, a))
	    {
			// struct name
			token = strtok(strline, "{");
			ptr = strstr(strline, a);
			token = strtok_r(ptr, " ", &context);
			context[strlen(context)-1] = '\0';
	
			strcpy(TypeName, context);
			
			buf1[0] = '\0';
			buf3[0] = '\0';
			buf2[0] = '\0';
			buf4[0] = '\0';
			buf5[0] = '\0';
		}


		if(strncmp(strline, b, strlen(b) ) == 0)
        {
			// struct tag_name			
			token = strtok(strline, "}");
			token[strlen(token)-2] = '\0';

			if(token[0] == '\0'){
				 //strcat(buf1, "없음\n");
			}else{   
				strcpy(structName, token);
			}

			strcat(buf1, "@");
			sprintf(cntStr, "%d", sumcnt);
			strcat(buf1, cntStr);
			cnt=0;
			sumcnt=0;

			EraseSpace(buf1);
			EraseSpace(buf2);
			EraseSpace(buf3);
			EraseSpace(buf4);
			
			strcat(buf5, buf1);
			strcat(buf5, buf2);
			strcat(buf5, buf3);

			EraseSpace(buf5);
			strcat(sendBuf, buf5);
		}
				
		if(strstr(strline, c)){
				Msg[0] = '\0';	
				sumcnt++;
			
				strline[strlen(strline) - 2] = '\0';
				if(strstr(strline, structName)){
				strline[strlen(strline)-1] = '\0';
				}
				arr[0] = strtok(strline," ");
				
				int i=1;
				for(i = 1; i<3; i++){
					arr[i] = strtok(NULL, " ");	
				}	


				Msg[0] = '\0';
				if(strstr(arr[0], structName)){
					sprintf(Msg,"@/%s",TypeName);
					strcat(buf2, Msg);				
						}
					
						 if(arr[2] == NULL){
                            
								word = arr[1];
							       strcpy(tmp, arr[1]);
									
									  if(strstr(arr[1], "]")){
                                       token = strtok(arr[1], "[");
                                         arr[1] = token;
                                     }
									
									if(strstr(arr[1], "*")){
										token = strtok(arr[1], "*");
										arr[1] = token;
									}
	
                                     // 멤버변수 변수명
                                     sprintf(Msg,"@%s",arr[0]);
                                     strcat(buf3, Msg);
                                     sprintf(Msg, "@%s",arr[1]);
                                     strcat(buf3, Msg);
									 strcpy(word, tmp);
                             }else{
								word = arr[2];
								strcpy(tmp, arr[2]);		
                                       
									if(strstr(arr[2], "]")){
                                         token = strtok(arr[2], "[");
                                           arr[2] = token;
                                       }

									  if(strstr(arr[2], "*")){
                                         token = strtok(arr[2], "*");
                                           arr[2] = token;
                                       }
										
                                    sprintf(Msg,"@%s %s",arr[0], arr[1]);
                                     strcat(buf3, Msg);
                                     sprintf(Msg,"@%s",arr[2]);
                                      strcat(buf3, Msg);                        
									strcpy(word, tmp);
							 }			
				
				//array check
				if(strstr(word, "[")){
					token = strtok_r(word,"[", &word);
					token = strtok(word, "]");
					sprintf(Check,"@%s", word);
				}else{
					sprintf(Check,"@0");
				}
				strcat(buf3, Check);
							
				//pointer check
				if(strstr(word, "*")){
						sprintf(Check,"@YES");
				}
				else{
					sprintf(Check,"@NO");	
				}
				strcat(buf3, Check);
				
				word = NULL;
				tmp[0] = '\0';
		   }
	
	}	

	fclose(wFILE);
	fclose(rFILE);

	do_send(c_socket);
	//sendBuf[0] = '\0';
}


void do_send(int arg){
	int c_socket = arg;
	int n = strlen(sendBuf);

	printf("%d\n", n);
	printf("WRITE MSG : %s\n", sendBuf);
  	write(c_socket, &n, sizeof(n));
	 write(c_socket, sendBuf, n);	
}
