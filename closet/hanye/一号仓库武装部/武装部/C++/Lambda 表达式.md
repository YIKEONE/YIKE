在 C++ 中，Lambda 表达式是 C++11 引入的重要特性，用于创建匿名函数对象。Lambda 表达式提供了一种简洁、方便的方式来编写临时函数对象，通常用于函数式编程、STL 算法、以及简化回调函数的编写。

### Lambda 表达式的基本语法

Lambda 表达式的基本语法如下：

cppCopy code

```c++
[capture clause](parameters) -> return_type {     
	// 函数体     
	return expression; // 或者空，表示返回类型推断 
}
```

其中各部分含义如下：

- **Capture Clause (捕获列表)**：用于捕获外部变量，控制 Lambda 函数对外部变量的访问方式。
    
    - `[ ]`：不捕获任何外部变量。
    - `[var]`：捕获名为 `var` 的外部变量。
    - `[var1, var2]`：捕获多个外部变量。
    - `[&]`：按引用捕获所有外部变量。
    - `[=]`：按值捕获所有外部变量。
    - `[&, var]`：按引用捕获所有外部变量，但是 `var` 按值捕获。
- **Parameters (参数列表)**：Lambda 函数的参数列表，与普通函数类似。
    
- **Return Type (返回类型)**：Lambda 函数的返回类型，可以省略（由编译器推断）。
    
- **Function Body (函数体)**：Lambda 函数的实际执行代码。
    
- **Return Expression (返回表达式)**：Lambda 函数的返回值。
    

### 示例

#### 1. Lambda 表达式示例：
```c++
// Lambda 表达式：计算两个整数的和
auto sum = [](int a, int b) { return a + b; };

// 使用 Lambda 表达式
int result = sum(3, 4); // result = 7

```

#### 2. 捕获外部变量的 Lambda 表达式示例：

```c++
int x = 10;
int y = 20;

// Lambda 表达式：捕获外部变量并求和
auto add = [x, y]() { return x + y; };

// 使用 Lambda 表达式
int sum = add(); // sum = 30

```

#### 3. 按引用捕获外部变量的 Lambda 表达式示例：

```c++
int total = 0;
std::vector<int> numbers = {1, 2, 3, 4, 5};

// Lambda 表达式：按引用捕获外部变量并累加
std::for_each(numbers.begin(), numbers.end(), [&total](int x) { total += x; });

// 使用 Lambda 表达式后，total 变为所有元素的和：total = 15

```

Lambda 表达式常用于函数对象的定义，例如作为 STL 算法的谓词、排序比较函数、以及事件处理的回调函数等。它简化了函数对象的书写和使用，使得代码更加清晰、简洁。