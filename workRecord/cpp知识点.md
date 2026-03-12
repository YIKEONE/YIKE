# 闲隙碎笔

## *C*

### 头文件包含顺序

### 全局变量和局部变量

|          | 全局变量                                               | 局部变量                     |
| -------- | ------------------------------------------------------ | ---------------------------- |
| 作用域   | 在整个程序中都可见                                     | 在定义它的代码块中           |
| 生命周期 | 伴随着程序启动到结束                                   | 代码块结束时，局部变量被销毁 |
| 存储位置 | 静态数据区                                             | 存储在栈中                   |
| 默认值   | 未经初始化时，会被赋予默认初始值                       | 不会被自动初始化             |
| 关键字   | 可以使用extern在一个文件中声明另一个文件定义的全局变量 | 无需，除非想定义static       |

### 从代码到可执行的二进制文件

1. 预处理：将宏定义`（#define）`、头文件`#include`等都展开到源文件中，生成`.i`文件。
2. 编译：对预处理后的文件，对其进行语法分析等，将`.i`生成`.s`文件。
3. 汇编：将`.s`文件生成`.o`的二进制代码。
4. 链接：将所有的目标文件链接到一起形成可执行文件，分为动态链接和静态链接
   - 静态链接：将链接库的代码复制到可执行程序中，使得可执行程序体积变大。
   - 动态链接：需要链接的代码放到一个可共享对象中，共享对象映射到进程虚拟地址空间，链接程序记录可执行程序将来需要的代码信息，根据这些信息快速定位相应的代码片段。

### strcpy和memcpy的区别

1. strcpy:专门用于字符串的复制.
2. memcpy:用于复制任意类型的内存块,不仅限于字符串.

~~~c++
int main() {
    char src[] = "i am tobbe";
    char des[20];
    strcpy(des, src);
    memcpy(des, src, sizeof(src));
}
~~~

### 指针数组和数组指针的区别

~~~c++
// 指针数组
int *arr[5]; // 声明一个包含五个指向整数的指针的数组
// 数组指针
int (*arr)[5] = &arr; // 声明一个包含五个整数的数组的指针
~~~

### malloc和calloc的区别

- `malloc` 用于分配指定字节数的内存，内容未初始化。
- `calloc` 用于分配指定数量和大小的元素的内存，内容被初始化为零。
- 在使用 `malloc` 分配内存后，可能需要手动初始化内存内容。
- 在使用 `calloc` 分配内存后，可以确保内存内容为零。
- 在检查内存分配是否成功时，都需要检查返回值是否为 `NULL`。

~~~c++
int main() {
    int *arr = (int*)malloc(5 * sizeof(int)); // 分配地址默认是void *, 所以要转换成int *
    int *arr = (int*)calloc(5, sizeof(int));
}
~~~

### 原码、反码、补码

- 反码是在原码的基础上，负数的表示方式取反。正数的反码和原码相同。
- 补码是在反码的基础上，再加1。
- 补码的性质：
  1. 加法和减法一致： 在计算机中，加法和减法使用相同的硬件电路，无需额外的减法电路。
  2. 唯一的零表示： 补码中只有一个零表示，避免了正零和负零的问题。
  3. 范围表示： 补码表示范围为 −2^(*n*−1),2^(*n*−1)−1，其中 n 是位数。
  4. 溢出处理： 溢出的结果可以被忽略，不会导致错误的计算结果。

### 内联函数和函数的区别

1. 内联函数（Inline Function）：

- 定义： 内联函数是在函数声明前面加上 `inline` 关键字的函数，通常在头文件中定义。编译器会尝试将内联函数的代码插入到每个调用它的地方，而不是通过正常的函数调用机制。
- 特点：
  - 提高代码执行效率，减少函数调用开销。
  - 适用于短小的函数，避免频繁的函数调用带来的开销。

2. 普通函数：

- 定义： 普通函数是一般的函数，不带 `inline` 关键字。函数调用时，会按照正常的函数调用机制执行，包括压栈、跳转、返回等步骤。
- 特点：
  - 函数调用会有一定的开销，包括压栈、跳转、返回等操作。
  - 适用于较大或者复杂的函数，不适合频繁调用。

### 大端对齐与小端对齐

- 大端对齐：数据的最高有效字节,存储在最低地址处.
- 小端对齐：数据的最低有效字节,存储在最低地址处

~~~c++
例如0x1234
高地址		低地址
大端对齐
[12][34]
小端对齐
[34][12]
~~~

### 常量指针与指针常量的区别

~~~c++
// 常量指针
const int * ptr; // 修饰的是对象, 所以指针所指向的对象不能修改. 可以改变指向.
// 指针常量
int * const ptr; // 修饰的是指针, 所以指针不能指向别人, 内容可以改变.
// 必须要初始化 int * const ptr = &a;
~~~

### 声明和定义的区别

|          | 声明           | 定义                |
| -------- | -------------- | ------------------- |
| 内存分配 | 不分配实际内存 | 分配内存            |
| 关键字   | extern or not  | int, double, floate |
| 初始化   | 不进行初始化   | 进行初始化          |
| 多次声明 | 可以多次声明   | 只能定义一次        |

### 什么情况会出现野指针

1. 指针释放后未置空:

   ~~~c
   int *ptr = (int*)malloc(sizeof(int));
   free(ptr);
   // 释放后, 未置为NULL
   ~~~

2. 指针未初始化

   ~~~c
   int *ptr;
   // 未初始化, 包含不确定的地址
   ~~~

3. 函数返回局部变量地址

   ~~~c
   int& returnLocal()
   {
       int num = 4;
       return &num;
   }
   ~~~

4. 指针越界访问

   ~~~c
   int *arr = (int*)malloc(5 * sizeof(int));
   arr[5] = 10; // 越界访问
   ~~~

5. 二次释放

   ~~~c
   int *ptr = (int*)malloc(5 * sizeof(int));
   free(ptr);
   free(ptr); // 二次释放
   ~~~

6. 指针拷贝问题

   ~~~c
   // 当两个指针都指向同一个地址, 其中一个指针释放后, 另外一个指针仍在使用, 导致野指针
   int *ptr = (int*)malloc(sizeof(int));
   int *ptr1 = ptr;
   free(ptr);
   *ptr1 = 10; // 使用了已经释放的内存
   ~~~

   ### 浅拷贝与深拷贝

   - 浅拷贝:浅拷贝通常是通过将一个结构体或数组的内容复制到另一个结构体或数组中来实现的。这只涉及到对结构体或数组的直接成员的复制，而不涉及到成员可能指向的动态分配内存的内容。
   - 深拷贝:深拷贝通常涉及到手动管理动态分配内存，并将内容复制到新的内存空间。这需要使用 `malloc` 和 `free` 函数来管理内存。

   ### 静态函数与普通函数的区别

   |                | 静态函数(非成员函数)                                       | 普通函数                       |
   | -------------- | ---------------------------------------------------------- | ------------------------------ |
   | 生命周期       | 整个程序的生命周期                                         | 只有在函数被调用的时候才存在   |
   | 作用域         | 只有在定义的源文件, 在其他源文件无法调用                   | 只要他们的声明可见, 都可以调用 |
   | 编译单元和链接 | 仅在定义它的编译单元中可见, 链接时, 其他笔编译单元无法访问 | 链接时, 对所有编译单元可见     |
   | 函数名的重用   | 不同编译单元可以定义相同名的静态函数                       | 不可以定义相同名的函数         |

   

## *Cpp*

### 关键字

#### static

~~~c++
经过static修饰的变量为静态变量，存在静态区中。存在静态区的数据生命周期与程序相同。在main函数之前初始化，在程序退出时销毁。（无论是全局静态还是局部静态）
~~~

#### using

~~~c++
using 别名 = 主名(更多是用在命名空间的重命名)，typedef(用于类、结构的重命名)。
using Func = std::function<void(int)>;
Func printNum = [&](int num) -> int { std::cout << num << std::endl; };
~~~

#### explicit

~~~c++
explicit 修饰构造函数，表示该构造不能隐式转换，也就是不能 string sName = "tobbe"，只能string sName = string(tobbe)。
防止构造函数，进行类型转换。鼓励构造函数中使用explicit
    
// non-explicit, could apple this constructor
testFuncion(10);
// explicit
testFuncion(Test(10));

// 会报错, 因为explicit禁止了隐式调用拷贝构造函数。
Widget widget = w1;
~~~

#### const

```c++
const函数，常量和非常量对象都可以调用const函数，但是在const不能修改成员变量，常量对象只能调用常量函数。
```

#### extern

~~~c++
extern，是简单的声明，不分配内存：
// 用法1：在一个.h文件定义int i，在另外一个extern int i，就可以跨文件使用这个变量

// 用法2：在变量很多文件都有涉及，那么在一个头文件中定义extern int i, extern int j,在不同文件中引入该头文件就可以直接使用。

// 用法3：extern "C" {/**/}，就代表代码块中使用C的语法，例如C++支持重载，而extern "C"修饰后，就不能重载了。

// common.h
extern int g_num;
// 如果很多源文件引入该头文件，如果没有extern修饰，就会报错，因为int g_num；是声明
// 说的可以跨文件共享，是指可以在引入该头文件的文件之间共享
~~~

#### define

~~~c++
#define，定义宏，只是单纯的替换：
// 用法1：定义一个宏，#define MAX_VALUE 1000。遇到MAX_VALUE 就会替换成1000。

// 用法2：定义一个函数, #define Add(x, y) x +y。这里只会简单的替换，例如，a * Add(x, y) * b，a * x + y * b, 这里遵循交换律。 

// 用法3：#define ToString(x) #x， #define ToChar(x) #@x，#define Conn(x, y) x##y。##表示连接，#@表给''引上，#给""引上。

// 用法4：条件判断，(#ifdef || #ifndef #else #endif)，取消宏定义#undef。

// 用法5：多行定义，
#define METHOD_MAP(XX)	\
		XX(getId)		\
		XX(getMenu)		\
		XX(getColor)
等价于#define METHOD_MAP(XX) XX(getId) XX(getMenu) XX(getColor)

#define DECLARE_METHOD(methodName) void methodName(void); 
METHOD_MAP(DECLARE_METHOD)  等价于把所有的函数都声明了
这种用于元编程，要批量操作一系列函数时，

// 技巧：当想创立一个自定义变量的数组，那么就得先把自定义类型给定义了，可以使用匿名结构体
struct {
  DeviceinfoMethod id;
  const char *methodName;
} METHOD_NAME[] = {
  /* 这里可以用元编程，使用宏来批量操作*/
}
~~~

#### typename

~~~c++
int main() {
    // 1. typename指明后面是一个类
    template<typename T>  
    typename T::SubType* ptr；
    // 2. typename指模板类
	template<template<typename, typename> class Container, typename Key, typename Value>  
    Container<Key, Value> data;
}
~~~

#### constexpr

   ```c++
// constexpr关键字修饰的，表示该对象在编译时就会确定的值，如果不是那么在编译时就会报错，减少了运行时间

constexpr 函数：可以在编译时计算结果，但要求所有参数都是常量表达式。
    数组大小：必须是常量表达式。
    模板参数：必须是常量表达式。
    常量对象：可以在编译时确定，但非 constexpr 方法仍然在运行时调用。
    编译错误：如果 constexpr 函数的参数不是常量表达式，编译器会报错。
    
    constexpr int size = 10;
    是在编译的时候就确定的值，而不是在运行时确定的值，例如给 arr[size]赋值，这个size是要在编译时就知道的值好分配内存空间，
  
   ```

#### union

~~~c++
union Data {
int i;
float f;
char str[20];
};
// 于struct，不同的时，union的大小为成员中最大的，如char str[]为20字节
Data data;
data.i = 10;
data.f = 10.5; // 此时就没有i值了
~~~

#### volatile
~~~c++

~~~

#### public, private

~~~c++
Base类有纯虚函数, 表示该类无法被实例化(抽象类), 且继承的派生类也必须要重写该函数. 而如果派生类也为抽象类, 则不必重写纯虚函数.
总结则为: 在继承关系下, 如果存在纯虚函数, 则需要实例化的类必须要重写纯虚函数.

在private继承下, 无法多态, 且遮蔽所有的基类方法, 内部仍然可以调用基类的public, protected方法, 而外部则无法调用.
class Base {
public:
    virtual void func1();
};
class Derived : private Base {  
public:
    void callfun1()
    {
        func1();
    }
};
int main()
{
    Derived d;
    d.callfunc(); // 可以, 转交函数
    d.func1(); // 不可以, private继承下func1为private, 无法在外部调用
    Base *b = &d; // private继承下, 无法多态
}
~~~



### 语法类

#### 虚继承

~~~c++
虚继承，当出现菱形继承时，23分别是1的子类，4同时继承2，3。把2.3改为virtual public 1；是为了防止2.3和1有相同名字的成员变量，而4继承后不知道是用谁的值，导致二义性。此时4的成员变量值为最右侧继承基类的值。
~~~

#### 代码块

~~~c++
代码块{}，就是块内的代码，块外访问不到。搭配一些例如lock_guard，出代码块的作用域，会自动释放资源。
~~~

#### 在头文件定义的inline和模板函数

~~~c++
//.h
void fun();
//.cpp
#include ".h"
void fun() {};
//main.cpp
#include ".h"
int main() {
    func();
}

//预处理
//编译，分别编译.cpp和main.cpp,生成.o和main.o文件
.cpp，编译器看到函数的声明和定义，对于普通函数，只需要知道声明，不用需要知道实现，但是需要有
.main，编译器看到了声明，
//链接
.main对于func()的调用，找到.o文件中的实现，把他们链接起来

/*内联函数：需要在头文件中定义，因为编译器需要在每个调用点处看到内联函数的完整定义。
静态成员函数：可以在类内定义，以提高代码的可读性和模块化。
构造函数和析构函数：可以在类内定义，以提高代码的可读性和模块化。
简单的成员函数：可以在类内定义，以提高代码的可读性和模块化。
常量表达式函数：需要在头文件中定义，因为编译器需要在每个调用点处看到函数的完整定义
*/

而对于内联、模板和常量表达式函数需要在头文件定义，因为这些函数都是在编译时必须知道的。所以不能像普通函数，在编译时不用知道，在链接时知道即可。
如果没在头文件中定义，那么main.cpp在预处理把头文件展开，编译时就可以知道他的定义。
~~~

#### 左值、右值引用

~~~c++
//左值和右值引用实际都为引用
//右值引用，右值不可以取x + y的地址，但是可以取a的地址&a，
int &&a = x + y;
//并且右值不能被左值赋值，如果需要左值赋值，使用std::move()
int &&a = x; //×
int &&a = std::move(x); //√

//左值引用
//而左值也只能被左值所赋值
int &a = x;//√
int &a = 1;//×
//但是const修饰后的左值，都可以被赋值
const int &x = 1;//√

//拷贝构造函数和移动构造函数都是对构造函数的重载，不同的是，拷贝构造函数接受的参数是const左值，左值和右值，而移动构造函数接受的参数是右值和被move的左值。


//完美转发，用于万能引用，等同于模板右值引用。std::forward<>,正常来说，传左值或右值给函数时，会以左值或右值引用进行传递，而forword是用于传参时，右值被强制转换为左值。万能引用是和T模板相结合，T&& a, 为万能引用。而Test&& a为右值引用，const T&& a也为右值引用。
std::forward<T> (x);//只要是右值引用，由当前函数再传递给其它函数调用，要保持右值属性，必须实现完美转发。

//不能返回局部变量的引用，并且不能返回由new创建的对象。第一条，因为局部变量离开作用域就被析构了，而局部变量的引用就变成“无所指”的情况。第二条，虽然不会出现没有指向的情况，但是new出来的对象，如果没有赋值给一个实际变量，从而delete不了，造成内存泄漏。
~~~

#### 左右折叠，template，typename...

~~~c++
//左折叠
//属于c++17的新特性，g++ -std=c++1z main.cpp -o main才可以编译
template<typename... Args>
void print(Args... agrs) {//args op ...
    (std::cout << ... << agrs) << std::endl;
    return (... && args);//所有参数为真
    return (... || args);//至少有一个参数为真
    return (args + ... + 0);//求和
    return (args * ... * 1);//求积
    return (... > args ? ... : agrs);//求最大值
    return (... + (args > 0 ? args : 0));//大于0的数相加
}
//右折叠
template<typename... Args>
void func(Args... args) {
    std::cout << (args * ... * 1) << std::endl;
}
int main() {
    print("hello", " world!");//hello world!
}

//template
//不能共享，每一个函数都得独立声明；且只能在声明的模板内有效；
template<typename... N>//也可以定义一个固定类型的参数包
template<int... N>//也可以定义一个固定类型的参数包

template<typename N>//typename可以使任何一个类，也可以指定固定类，例如int
void test() {}
test<int/5>();
~~~

#### static局部变量

~~~c++
void func()
{
    static int num = 10;
}
// 只要是静态变量，其的声明周期都是全局的
// 与全局静态不同的是，局部静态是在第一次访问时分配值i，并且其的作用域只是在对应的代码块中
~~~

#### 虚析构函数

如果类可能被继承，并且可能被基类指针删除，析构函数应该声明为 `virtual`。

- 没有定义虚析构函数时，有可能执行子类的析构后不会执行父类的析构函数

#### 构造函数

~~~c++
Widget w1; // default constructor
Widget w2(w1); // copy constructor
// 区分拷贝构造和拷贝赋值
// 当有新对象创建的时候, 肯定会有构造
// 因为 explicit禁止了隐式调用拷贝构造函数。
Widget widget = w1; // copy constructor
// 反之, 当没有的时候, 则就是赋值
w1 = w2; // assignment operator
~~~

#### 类型转换

~~~c++
//1. static_cast, 用于在编译时就知道的类型, 不进行运行时类型检查, 不能去除const, volatile限定符
int i = 10;
double d = static_cast<double>(i);
Base *b = new Derived();
Derived *d = static_cast<Derived*>(b); // 不安全

//2. dynamic_cast, 用于多态中向下类型转换
Base *b = new Derived();
Derived *d = static_cast<Derived*>(b); // 安全
if d() {} // 如果转换成功

// 3. const_cast, 用于添加或移除const, volatile限定符
// 唯一合法的场景, 变量本身就不是const, 可以使用const_cast给const修饰符移除
int y = 10;
const int& cref = y;
int& ref = const_cast<int&>(cref);
ref = 20; // OK, 因为y本身就不是const的

// 4. reinterpret_cast, 最危险, 用于不同类型的互相转换
~~~



### 接口类

#### std::move

~~~c++
//std::move
string ch = "tobbe";
string&& str = std::move(ch);//左值不能赋值给右值，通过move来转换 
str.push_back();//通过传入引用,将左值引用转换成右值引用，提高内存操作效率
~~~

#### std::ref

#### std::advance

#### std::tuple、std::tie，std::get\<N\>

~~~c++
std:tuple<bool, int> getPath() {
    return make_tuple(true, 10);
}
int main {
    auto[succ, num] = getPath();//c++17之后才允许的，结构化绑定，用来赋值，succ和num都是临时变量
}
//而tie用来更新值
class Person {
    int age;
    string name;
}
int main() {
    Person p;
    std::tie(p.age, p.name) = make_tuple(1, "yike");

    std::tuple<int, std::string> myTuple = {42, "Hello, World!"};  

    int firstElement = std::get<0>(myTuple);
}
~~~

#### std::make_index_sequence<>

~~~c++
//std::make_index_sequence<5>，为一个模板类，为sequence<0,1,2,3,4>
template<size_t... N>
void test(std::index_sequence<N...>) {
    (std::cout << ... << N) << std::endl;
}
int main() {
    // execute("hello ", "world!");
    // execute(1, 2, 3, 4, 5);
    // execute1(1, 2, 3, "tobbe");
    // std::cout << "right fold" << std::endl;
    // execute2(1, 2, 3, "tobbe");
    test(std::make_index_sequence<5>{});
}
~~~



### 多线程

#### 多线程-操作

~~~c++
int task(int num) {
    std::cout << "thread Id: " << std::this_thread::get_id() << std::endl;
    return num * num;
}
void task1(int num, std::promise<int> &promise) {
    promise.set_value(num * num);
}
void task2(shared_future<int> f) {
    int num = f.get();
}
int main()
{
    // 1.1 抛线程-没有返回值
    std::thread t(task, 5);
    t.join();

    // 1.2 抛线程-有返回值
    std::promise<int> promise;
    auto futures = promise.get_future();
    std::thread t(task1, 5, std::ref(promise));
    std::cout << futures.get() << std::endl;
    t.join();
    
    // 2.1 抛异步任务
    auto res1 = std::async(std::launch::async, task, 5); //直接在后台执行
    auto res = std::async(std::launch::deferred, task, 5); //等get后才开始执行
    
    // 2.2 抛异步任务
    shared_future<int> f = res1.share();
    std::thread t1(task2, f);//把一个异步的结果，传给另外一个线程
	auto res2 = std::async(std::launch::async, task2, f);
    
    t1.join();
    res2.get();
}

//抛线程与抛异步任务
//线程：适用于比较长的计算，且无法返回值，需要搭配promise
//异步任务：更加轻量级，可以返回值
//通过shared，可以把一个异步任务的结果，传给另外一个线程，或者任务
~~~

#### 多线程-锁

```c++
//1.锁
std::mutex mtx;
int count = 0;

void func() {
    for (size_t i = 0; i < 1000; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        count++;
    }
}
int main() {
    std::vector<std::thread> threads(5);
    while(int i < 5) {
        threads.emplace_back(func);
    }
    for(auto &t : threads) {
        if(!t.joinable()) continue;
        t.join();
    }
}
//2.信号量 c++20
std::counting_semaphore<1000> sem(1);//1000代表最高并发量，1表示许可的个数
void func() {
    sem.acquire();
    ++counter;
    sem.release();
}
//3.条件变量
std::mutex mtx;
std::condition_variable cv;
bool ready = false;
void producer() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        ++count;
        ready = true;
    }
    cv.notify_one();//唤醒另外一个线程
}
void consumer() {
    std::lock_guard<std::mutex> lock(mtx);
    cv.wait(lock, []() { return ready; })//等待ready为true
}
//原子操作
std::atomic<int> count(0);
void func() {
    for (size_t i = 0; i < 1000; ++i) {
        count++;
    }
}
//
```

#### std::thread_local

```c++
/*线程隔离：每个线程都有自己的变量副本，因此访问和修改这些变量时不会影响到其他线程。
  避免同步：由于每个线程操作的是自己的变量副本，因此无需使用锁或其他同步机制来避免数据竞争。
  空间换时间：通过为每个线程分配独立的变量副本，ThreadLocal以空间换时间的方式解决了线程安全问题。*/
thread NClass nclass;
//每个线程的都存在的各自的局部变量
```

#### std::thread

~~~c++
std::vector<std::thread> ts;

ts.emplace_back(arg1, arg2);//arg1是线程函数（如拿糖果），arg2是传给线程函数的参数

ts.emplace_back();//是在容器的尾部直接创建新的对象，而不是创建一个再移动或复制

ts.emplace_back(func, std::ref(jar));//ts.emplace_back里面是值传递，而不是引用，到需要引用传递时，std::ref()可以将其转换为引用
~~~

#### std::async

~~~c++
 //
 std::future = std::async(std:launch::async, callback, arg...);
 auto res = future.get();
~~~

#### std::promise

~~~c++
 std::promise<int> promise;
 auto future = promise.get_future();
 
 std::thread t1([](std::promise<int> promise, int num) {
     promise.set_value(num * num);
 }, std::move(promise), 7);
 
 auto res = future.get();
~~~

### STL容器

#### 迭代器

~~~c++
//list,set,map的迭代器不支持+，-操作
std::unordered_set<int>::const_iterator it = hash.begin();
it++;
it--; //不支持
it += 5;//不支持
std::advance(it, 5);//可以对所有类型的迭代器，进行+操作
~~~

#### 容器存放指针

~~~c++
//STL的容器是自动管理内存的，但如果存放的是指针，例如
std::vector<int *> intVec(5);
for(size_t i = 0; i < 5; ++i) intVec.emplace_back(new int(5));
~~~

#### 容器的定义和初始化

~~~c++
//容器的定义
//1.另外一个容器的拷贝，2.另外一个容器的迭代器范围
//1.
vector<int> ivec;
list<int> ilist(ivec);//容器拷贝，数据类型必须一致，
//2.只有array和string容器不支持
vector<string> svec;
list<const char *> chlist(svec,begin(), svec,end());//只要数据类型可以互相转换即可

//容器的初始化
//1.同定义，拷贝必须类型相同，迭代器数据类型必须可以转换
std::list<char *> chlist;
std::vector<std::string> strvec;
strvec.assign(chlist.begin(), chlist.end());
~~~

#### insert和emplace的区别

~~~c++
class Two
{
    Two(int n1, int n2);
};
vector<Two> vec;
//insert是先创建对象在拷贝到容器中
Two t(1, 2);
vec.insert(vec.begin(), t);
//emplace是直接在容器调用构造函数
vec.insert(vec.begin(), 1, 2);//错
vec.emplace(vec.begin(), 1, 2);//对
~~~

#### 适配器stack，queue，priority_queue

~~~c++
//适配器，用来修饰容器
vector<int> vec;
stack<int, vector<int>> stk(vec);

//queue，priority_queue，可以修饰deque和list
deque<int> deq；
list<int> ls;

~~~

#### 关联容器

~~~C++
/*
	<key, value>
	set/map
	multiset/map
	unorderedset/map
*/ 
1.只有重载了"<"操作符，才可以作为关键字的类型
2.通过begin等返回的迭代器为 pair<const key, value>，所以不能修改值，
auto it = map.begin();
it->fist = "new kek";//错
it->second = 15//可以
~~~

### 泛型算法

泛型算法不依赖容器，但是依赖元素类型。
例如，std::find()，需要元素类型支持==，其他算法需要元素类型支持<操作符
算法大多数都是，func(iter, iter, init);都是传入一个迭代器的范围

#### std::find

~~~C++
/*
	in	: 迭代器范围
	out	: 找到的迭代器
*/
//std::find
auto it = std::find(vec.begin(), vec.end(), 5);//查找范围，返回的是迭代器

//std::find_if，传入谓词，lambda表达式
auto it = std::find_if(vec.begin(), vec.end(), [](int num) {
    return num > 10;
});

//对于以下有成员方法find，用自己的。要求通用性，使用泛型算法，所有容器都能使用
sting s;
size_t index = s.find("1");//返回的是下标
~~~

#### std::all_of

~~~c++
/*
	in	: 迭代器范围，谓词
	out	: 元素对谓词的结果 
*/
//all_of
auto status = std::all_of(vec.begin(), vec.end(), [](int num) {
    return num > 0;//all_of所有元素都得满足条件，为true
});

//none_of
status = std::none_of(vec.begin(), vec.end(), [](int num) {
    return num > 0;//none_of，所有元素都不满足条件，为true
});

//any_of
status = std::any_of(vec.begin(), vec.end(), [](int num) {
    return num > 0;//any_of，有一个元素满足条件，为true
});
~~~

#### std::count

~~~c++
/*
	in	：迭代器范围
	out	：出现次数
*/
//std::count
auto count = std::count(vec.begin(), vec.end(), 3);//返回出现次数

//std::count_if
auto count = std::count_if(vec.begin(), vec.end(), [](int num) {
    return num >= 3;
});
~~~

#### std::copy

~~~c++
/*
	in	: 迭代器范围，拷贝的容器的迭代器
	out	: 指向ivec的指针
*/
auto it = std::copy(vec.begin(), vec.end(), ivec.begin());

std::replace(ivec.begin(), ivec.end(), 5, 6);

auto it1 = std::replace_copy(vec.begin(), vec.end(), ivec.begin(), 5, 1);//vec的内容不变，把vec的5换成1给到ivec

//给需要拷贝的容器为空时，传入begin()为报错，需要使用back_inserter(vec)
~~~



#### 计算算法

```c++
//std::accumulate，计算和
#include <numeric>
int main()
{
    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    std::accumulate(vec.begin(), vec.end(), 0);//传入范围，初始值为0
}
```

#### std::fill

~~~c++
/*
	in	: 迭代器范围，需要填充的值
	out	: 
*/
std::fill(vec.begin(), vec.end(), 5); // 传入一个迭代器范围

std::fill_n(vec.begin(), 5, 1); // 传入一个开始的指针，和要替代的个数，这里个数一定不能越界
~~~

#### 排序算法

~~~c++
std::sort(vec.begin(), vec.end()); // 排序, 对于自定义的数据类, 需要重载<或==

std::stable_sort(vec.begin(), vec.end()); // 当元素相同时, 会保持排序前的顺序

auto it = std::unique(vec.begin(), vec.end()); // 只把相邻相同的元素放到末尾, 返回末尾的迭代器, 所以要排序

vec.erase(it, vec.end()); // 删除重复元素
~~~

#### std::partition

~~~c++
// partition, 接受一个谓词, 分为两个部分, 前面为谓词为true. 返回最后一个谓词为true的迭代器.
auto it = std::partition(vec.begin(), vec.end(), [](int num) {
    return !(num & 1);
});
~~~

#### std::unique

~~~c++
auto it = std::unique(beg, end); // 相邻元素如果相同，给他放到容器尾部。返回重复的头迭代器

auto it = std::unique_copy(beg, end, vecbak.begin()); // 把不同的元素，copy给别的容器
~~~

### 迭代器的适配器

~~~c++
auto it = std::back_inserter(vec); // 返回一个插入迭代器

std::fill_n(it, 5, 1); // 如果传入的是begin()，会报越界错误

// back_inserter对于可扩容的容器，不用考虑越界的问题

// 1.back_inserter，容器必须支持push_back
std::copy(beg, end, std::back_inserter(vecbak));

// 2.front_inserter，容器必须支持push_front
std::copy(beg, end, std::front_inserter(vecbak));

// 3.inserter,容器支持insert
std::copy(beg, end, std::inserter(vecbak, vecbak.begin()));
~~~

### lambda表达式

~~~c++
// 基本格式
[]() -> return {};

// mutable 修饰值传递
[=]() mutable {}; // 捕获的值，在lambda内不能修改，使用mutable修饰后，可以修改。

// 什么时候需要显示 -> return
// 1.多行表达式时
std::transform(vec.begin(), vec.end(), vec.begin(), [](int i) -> int {
	i = i *10;
    return i;
});
// 2.当有多个返回值时
std::transform(vec.begin(), vec.end(), vec.begin(), [](int i) -> int {
    if (i > 0) {
        return i;
    } else {
        return i;
    }
});
// 3.返回值不显而易见时
auto createVector = []() -> std::vector<int> {
    std::vector<int> ivec(10, 5);
    return ivec;
}
// 4.返回值是模板时
auto identity(T value) -> T {
    return value;
}
~~~

### 智能指针

#### unique_ptr

~~~c++
// 初始化
std::unique_ptr<int>(new int(10));
auto ptr = std::make_unique<int>(10);
// 禁止复制，可以移动
int main (int argc, char *agrv) {// 此时ptr1为空，ptr2指向原来的对象
    auto ptr1 = std::make_unique<int>(10);
    std::unique_ptr<int> ptr2 = std::move(ptr1);
}
// 自定义删除器
void customDeleter(int* ptr) {   
    delete ptr;  
}  
int main() {// 接受一个删除器，当离开作用域时自动调用
    // void(*)(int*)，表示返回值为void，void(*)表示是函数指针，而void*则是一个返回指针的函数
    std::unique_ptr<int, void(*)(int*)> ptr(new int(10), customDeleter);  
}
// 支持数组
std::unique_ptr<int[]> arr(new int[5]{1, 2, 3, 4, 5});
// 释放所有权
int* rawPtr = ptr.release(); //需要手动，delete rawPtr
// 重置指针
std::unique_ptr<int, deleter> ptr = std::make_unique<int>(10);  
ptr.reset(new int(20)); // 指向新对象  
ptr.reset(); // 变为空 

make_unique<T[]>(5);//接受一个数组时，是非法的，要求是定长的，不能是动态创建大小，因为是在编译时
// 就和指针一样，也就是ptr=arr数组的名字arr[5] = ptr[5];
// argPath为unique_ptr，而捕获列表有= &,而unique_ptr禁止复制，传&argPath，lambda可以会超出指针的声明周期，所以使用move来操作
lambda：[arg, argPath = move(argPath), argMode = move(argMode)];
// 接受一个删除器，在离开生命周期时会调用删除器，且把持有的资源自动传给删除器，如果资源类型和删除器传参类型不一致，会报错
std::unique_ptr<T, Deleter> ;
~~~

#### std::shared_ptr

~~~c++
当一个类Sale需要共享一个vector，两个对象saleA，saleB都持有vector
当数据需要共享时，使用shared_ptr来修饰，这样动态创建在堆区，创建对象时，就传shared_ptr，直到最后一个持有的对象析构时，才会释放
~~~

### 线程池
