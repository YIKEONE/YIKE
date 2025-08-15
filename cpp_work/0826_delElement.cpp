#include <iostream>
#include <vector>
#include <unordered_set>

void delElement(std::vector<int>& vt) {
    std::unordered_set<int> hashset;
    for (auto iter = vt.begin(); iter != vt.end(); iter++) {
        auto num = *iter;
        if (!hashset.count(num)) {
            hashset.insert(num);
            continue;
        }
        iter = vt.erase(iter);
        iter--;
    }
}

int main() {
    std::vector<int> vec;
    vec.emplace_back(10);
    vec.emplace_back(20);
    vec.emplace_back(20);
    vec.emplace_back(30);
    vec.emplace_back(40);
    vec.emplace_back(40);
    delElement(vec);
    for (auto num : vec) {
        std::cout << num << std::endl;
    }
}

