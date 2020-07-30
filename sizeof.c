#include <stdio.h>

typedef struct st_CiMember
{
    int choice;
    int index;  // array index
    int keyidx;
} CiMember;

typedef struct
{
    CiMember *list;
    int max_choice;
    int value;
    char nodeName[256];
} StCiMap;
CiMember *g_member = NULL;
StCiMap *g_ciMap;

main(){
		
	printf("1 : %d\n", sizeof(g_ciMap));      	
	g_ciMap[0].list[0].choice = 1;
	
	printf("2 : %d\n", sizeof(g_ciMap));
}
