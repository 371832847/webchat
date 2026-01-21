#include<iostream>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include"epoller.h"


int main(){

    epoller e;

    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd < 0){
        std::cout << "socket init error" << std::endl;
        return -1;
    }

    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8900);
    addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(fd,(sockaddr*)&addr,sizeof(addr)) != 0){
        std::cout << "bind error" << std::endl;
        return -1;
    }

    if(listen(fd,5) != 0){
        std::cout << "listen error" << std::endl;
        return -1;
    }

    if(!e.add_fd(fd,EPOLLIN)){
        std::cout << "add epoll error" << std::endl;
        return -1;
    }

    while(1){
        int num = e.wait();
        for(int i = 0;i < num;i++){
            int server = e.get_event_fd(i);
            int client = accept(server,NULL,0);
            const char* str = "hello";
        send(client,str,5,0);
        std::cout << "fd : " << client << std::endl;
        close(client);
        }
    }

    return 0;
}