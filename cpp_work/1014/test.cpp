#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <string>
#include "dirent.h"
#include <sys/stat.h>

#include <thread>
#include <unordered_set>
#include <vector>
#include <future>

void test(int num, std::promise<int> &promise)
{
    std::cout << "hello\n";
    promise.set_value(num * num);
}

int main()
{
    // const std::string filePath = "test.txt";

    // FILE *file = fopen(filePath.c_str(), "r+"); //r, w, a

    // if (!file) std::cout << "file not exist\n";

    // int fd = fileno(file); //return fd

    // // std::cout << "fd: " << fd << std::endl;
    
    // fclose(file); //close file

    std::string sen = "im 1234 tobbe 3 w4";
    auto it = sen.find("w4");
    std::cout << sizeof(std::unordered_set<int>::iterator) << std::endl;
}