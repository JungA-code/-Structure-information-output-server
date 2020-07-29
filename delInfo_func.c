void delInfo( int client_sock )
{
    int n, i, idx;
    char idxbuf[16];
    StCiMap *g_ciMap_temp;
    CiMember *g_member_temp;

    printf("delInfo func :) \n");

    printf("wait read.......\n");
    if( ( n = read(client_sock, idxbuf, sizeof( idxbuf ) ) ) < 0 ){
        printf("cannot rcv err \n");
    }
    else{
        idx = *(int*)idxbuf;

        printf("g_ciMapMax(1) : %d\n", g_ciMapMax);
        g_ciMap_temp  = realloc( NULL, sizeof( StCiMap ) * (g_ciMapMax)  );
        g_member_temp = realloc( NULL, sizeof( CiMember ) * (g_ciMapMax) );

        printf("**test**\n");
        printf("delete idx :  %d\n", idx);

        printf("copy 0~%d\n",idx-1 );
        for(i=0; i<idx; i++){
            memcpy(&g_ciMap_temp[i], &g_ciMap[i], sizeof( StCiMap ) );
        }

        printf("copy %d~%d\n",idx,g_ciMapMax-2 );
        for(i = idx; i<g_ciMapMax-1; i++){
            memcpy(&g_ciMap_temp[i], &g_ciMap[i+1], sizeof( StCiMap ) ); //해당 인덱스 다음을 해당 >인덱스로 복사
        }

        g_ciMap  = realloc( g_ciMap , sizeof( StCiMap ) * (g_ciMapMax - 1) );
        g_member = realloc( g_member, sizeof( CiMember ) * (g_ciMapMax - 1) );

        g_ciMap = g_ciMap_temp;
        g_member = g_member_temp;

        /*
           for(i = 0; i<g_ciMapMax-1; i++){
           printf("g_ciMap[%d]name: %s,  val : %d, index : %d \n",i, g_ciMap[i].nodeName,g_ciMap[i].value, g_ciMap[i].list[i].index);
           }*/
        printf("delete complete !\n");
    }
}
