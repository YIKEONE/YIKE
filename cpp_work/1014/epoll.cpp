#include <iostream>
#include <sys/epoll.h>
#include <string>

int main()
{
    // epoll_create(0);
    // epoll_event
    std::cout << 0x01 << std::endl;
    epoll_create(5);
}