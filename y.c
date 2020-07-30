#include <stdio.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

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

int main(){

    //CiMember *g_member;
    struct StCiMap *g_ciMap = malloc(sizeof(struct StCiMap));

    int g_ciMapMax;
    int i =0;
    char str[256] = "testququ";

    printf("1\n");
    for(i =0; i<10; i++){
        printf("2\n");
        g_ciMap->list.choice = i+3;
        g_ciMap->list.index = i-1;
        g_ciMap->list.keyidx = i+10;
        g_ciMap->max_choice = i;
        g_ciMap->value = i + 3 * 4;
             //strcpy(str, g_ciMap->nodeName);
        printf("3\n");;
       // printf("g_ciMap[%d] >> choice : %d | index : %d | keyidx : %d | max_choice : %d | value : %d | nodeName : %s\n",i, g_ciMap[i].list[i].choice,
         //       g_ciMap[i].list[i].index, g_ciMap[i].list[i].keyidx, g_ciMap[i].max_choice, g_ciMap[i].value, g_ciMap[i].nodeName);
    }

}

