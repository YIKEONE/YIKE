在C++中，`const` 是一个关键字，用于声明常量、常量引用、以及常量成员函数。`const` 的作用是指明被修饰的实体是不可修改的，从而提供了一定程度的安全性和约束。以下是 `const` 在不同上下文中的用法和含义：

### 1. 常量变量

cppCopy code

`const int x = 10;`

这里的 `const int x` 表示 `x` 是一个常量，其值不能被修改。一旦 `x` 被赋值，就不能再改变 `x` 的值。

### 2. 常量指针

cppCopy code

`int y = 5; const int* ptr = &y;`

这里的 `const int* ptr` 表示 `ptr` 是一个指向常量整数的指针。通过 `ptr`，不能修改指向的整数的值，但可以通过其他非 `const` 的指针或者直接操作变量 `y` 来修改该值。

### 3. 指向常量的指针

cppCopy code

`int z = 7; int* const p = &z;`

这里的 `int* const p` 表示 `p` 是一个常量指针，它指向整数 `z`，但不能指向其他变量。可以通过 `p` 修改 `z` 的值，但不能修改 `p` 指针指向其他变量。

### 4. 常量成员函数

cppCopy code

```c++
class MyClass { 
public:     
	void doSomething() const; 
};  
void MyClass::doSomething() const {     
	// 在常量成员函数中，不允许修改类的成员变量     
	// 除非成员变量被声明为 mutable 
}
```

在类中，`const` 修饰的成员函数被称为常量成员函数。这些函数不能修改类的非 `mutable` 成员变量，因为编译器会将 `this` 指针视为指向常量对象的指针。

### 5. 常量引用参数

cppCopy code

`void print(const std::string& str) {     // 函数内部不能修改 str 的内容     std::cout << str << std::endl; }`

在函数参数列表中，使用 `const` 引用可以避免不必要的拷贝，同时表示该函数不会修改传入的参数。这种方式既可以传递常量对象，也可以传递非常量对象，但函数内部都无法修改该对象的值。

### 6. 常量对象成员

cppCopy code

```c++
class Point 
{
public:
	int x;
	int y;
	Point(int x, int y) : x(x), y(y) {} 
};  
class Shape { 
public:     
	const Point center;     
	Shape(int centerX, int centerY) : center(centerX, centerY) {} 
};
```

在类中，常量成员变量必须通过构造函数初始化列表进行初始化，因为一旦被初始化，就无法在构造函数或其他地方修改其值。

总之，`const` 在C++中用于指定不可更改的实体，它可以应用于变量、指针、引用、成员函数等多种场景，提高了程序的可读性和安全性。