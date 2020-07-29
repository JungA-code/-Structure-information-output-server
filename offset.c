#include <stdio.h>
#include <string.h>
#include "msdsim.h"

#define CODEFILE "./offset_print.c"

char rcvbuff[BUFSIZ];
char sndbuff[BUFSIZ];

int findParent( int );

static char *head =
"#include <stdio.h>\n"
"#include <stddef.h>\n"
"#include \"msdsim.h\"\n"
"#include \"Measure.h\"\n"
"#include \"test.i\"\n"

"#define OFFSETFILE \"./offset.txt\"\n"
"\n"
"int main( void )\n"
"{\n"
"    FILE *fp = fopen(OFFSETFILE, \"w\");\n"
"\n"
"    if ( fp == NULL )\n"
"    {\n"
"        printf( \"File Open Fail\\n\" );\n"
"        return 1;\n"
"    }\n"
"\n";

static char *tail =
"\n"
"    fclose( fp );\n"
"    return 0;\n"
"}";


int main( void )
{
    FILE *fp = fopen( FILENAME, "r" );
    FILE *code = fopen( CODEFILE, "w" );
    int i, j;

    int n1=0, n2=0;
    // 파일 읽어서 전역 변수에 저장 (parse.c)
    readFile( fp );
    fclose( fp );

    // 문자열 분석함수 3종 세트 호출 (parse.c)
    removePreprocessor();
    removeNeedlessSpace();
    initStMap();
    int k =0;
    int p = 0;

    // output to file
  fprintf( code, head );
    for ( i = 0; i < g_stMapMax; i++ )
    {
        if(g_stMap[i].isChild == true){
                p = i+1;

                do{
                        if(g_stMap[p].isChild == false){

                            n1 = i;

                                for(j=0;j<g_stMap[i].com;j++){
                                    fprintf(code , "    fprintf( fp, \"%s %s.%s %%d\\n\", offsetof(%s, %s.%s) );\n",g_stMap[p].type, g_stMap[i].type, g_stMap[i].list[j].name, g_stMap[p].type, g_stMap[i].type, g_stMap[i].list[j].name);
                                    printf( "   offsetof(%s, %s.%s);\n",g_stMap[p].type, g_stMap[i].type, g_stMap[i].list[j].name);
                            }//end for
                            break;
                        }else{ p++;}


                n2++;
                }while(g_stMap[i].isChild == true);

        }else{
            for(j=0; j<g_stMap[i].com; j++){
                  k = n1+n2;
                  int cnt;

             //  다중구조체 타입 지우기!
              for(cnt = 0; cnt < g_stMap[i].com; cnt ++){

               if(strstr(g_stMap[cnt].type, g_stMap[k].list[j].type)){
                            if(g_stMap[cnt].isChild == true){
                               // printf( " delete>> offsetof(%s, %s);\n",g_stMap[k].type,  g_stMap[k].list[j].type);
                                j++;
                            }
                        }
                }


                    fprintf(code , "    fprintf( fp, \"%s %s %%d\\n\", offsetof(%s, %s) );\n", g_stMap[i].type, g_stMap[i].list[j].name, g_stMap[i].type, g_stMap[i].list[j].name );
                    printf( " offsetof(%s, %s);\n",g_stMap[i].type,  g_stMap[i].list[j].name);

        } //end else
    } //end i for
    }
    fprintf( code, tail );
    fclose( code );

    return 0;
}
