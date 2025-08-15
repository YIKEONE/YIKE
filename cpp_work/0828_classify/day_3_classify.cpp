#ifndef CLASSIFY_H
#define CLASSIFY_H
#include "day_3_classify.h"
#include <algorithm>
#include <ostream>
#include <string>
#include <utility>
#endif
#include <iostream>
#include <unordered_map>
#include <vector>

// std::string Classify::FoodClassify(std::unordered_map<std::string, std::unordered_set<std::string>>)
void Classify::FoodClassify()
{
    // std::cout << "hello world!" << std::endl;
    std::string str("goo");
    std::string str2("ood");
    str = std::move(str2);
    std::cout << str << std::endl;
    std::cout << str2 << std::endl;

    std::vector<int> intVec = { 1, 2, 3, 4 };
    std::vector<int> int2Vec = { 1, 2 };
    int2Vec = std::move(intVec);
    std::cout << "intvec" << std::endl;
    for (auto &num : intVec)
    {
    std::cout << num << std::endl;
    }

    std::cout << "int2vec" << std::endl;
    for (auto &num : int2Vec)
    {
    std::cout << num << std::endl;
    }
    std::string tob;
    tob += '0' + 2;
    std::cout << tob << std::endl;
}