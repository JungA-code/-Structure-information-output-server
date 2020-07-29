int keepalive(int client_sock){
    int c_sock = client_sock;
    int n;
    char rcvbuf[100];
    char CODE200[ ] = "OK";

    memset(rcvbuf, 0, sizeof(rcvbuf));
    n = read(c_sock, rcvbuf, strlen(rcvbuf));
    if(n<0){
        printf("client dead :(\n");
        c_sock = -1;
    }

    write(c_sock, CODE200, strlen(CODE200));

    return c_sock;
}
