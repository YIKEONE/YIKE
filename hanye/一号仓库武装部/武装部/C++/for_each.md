`std::for_each` 是 C++ 标准库中的算法函数之一，位于 `<algorithm>` 头文件中，用于对指定范围内的元素应用指定的操作（函数）。`std::for_each` 可以遍历容器或数组中的每个元素，并对每个元素执行指定的操作。

### 基本语法

```c++
template <class InputIterator, class Function>

Function for_each(InputIterator first, InputIterator last, Function f);

```

- `first`：指向要处理的范围的起始位置的迭代器。
- `last`：指向要处理的范围的结束位置的迭代器（不包括在范围内）。
- `f`：表示要应用于范围内每个元素的函数对象或函数指针。

### 示例

#### 1. 使用函数指针作为操作函数

```c++
#include <iostream>
#include <algorithm>
#include <vector>

void printElement(int x) {
    std::cout << x << " ";
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 使用 std::for_each 打印每个元素
    std::for_each(numbers.begin(), numbers.end(), printElement); // 输出: 1 2 3 4 5

    return 0;
}

```

#### 2. 使用 Lambda 表达式作为操作函数

```c++
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 使用 Lambda 表达式打印每个元素
    std::for_each(numbers.begin(), numbers.end(), [](int x) {
        std::cout << x << " ";
    }); // 输出: 1 2 3 4 5

    return 0;
}

```

#### 3. 修改元素值

```c++
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 使用 Lambda 表达式将每个元素加倍
    std::for_each(numbers.begin(), numbers.end(), [](int& x) {
        x *= 2;
    });

    // 打印修改后的元素值
    for (int num : numbers) {
        std::cout << num << " "; // 输出: 2 4 6 8 10
    }

    return 0;
}

```

### 注意事项

- `std::for_each` 并不保证元素的遍历顺序，它只是按照给定的范围顺序依次应用操作。
- `std::for_each` 通常用于对容器中的每个元素执行一些操作，但它不会返回任何结果。
- 可以使用函数指针、函数对象或 Lambda 表达式作为 `std::for_each` 的操作函数，具体取决于需要执行的操作的复杂度和灵活性。

总之，`std::for_each` 是一个便捷的算法函数，用于对容器或数组中的元素应用操作。它是标准库中众多算法函数之一，可以有效地帮助处理数据集合中的元素。