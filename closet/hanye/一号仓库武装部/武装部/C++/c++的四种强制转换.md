作用：四种类型转换用来代替强制类型转换，为了将运行时出现的错误控制在编译时。

## static_cast      
数值的转换，编译时校验

常用 C++中内置基本数据类型之间的相互转换 

2.void*-->指针类型

int main()

{

(1)编译时报错

int a = 10;
int *p = static_cast<int*>(a);//编译错误 int 类型不能转换成 int*

(2)

static_cast 用于将一种数据类型强制转换为另一种数据类型。

int a = 7;

int b = 3;

double result = static_cast<double>(a) / static_cast<double>(b);

cout<<result<<endl;

//(double)a

(3)

double a = 7;

void* p = &a;

double* dp = static_cast<double*>(p);

*dp = 100;

//a = 100;

cout<<a<<endl;

//可以使用 static_cast 找回存在于 void*指针中的值

}

## dynamic_cast
//用于【父子类】之间指针转换，==父类中必须包含虚函数，运行时校验== 非常常用

1.其他三种都是编译时完成的，dynamic_cast 是运行时处理的，运行时要进行类型检查;

2.不能用于内置的基本数据类型的强制转换;

3.dynamic_cast 要求 <> 内所描述的目标类型必须为指针或引用。dynamic_cast 转换如果成功的话返

回的是指向类的指针或引用，转换失败的话则会返回 NULL;

4.使用 dynamic_cast 进行转换的，基类中一定要有虚函数，否则编译不通过;

要求：类中需要有虚函数，为什么？

类中需要检测有虚函数的原因：类中存在虚函数，就说明它有想要让基类指针或引用指向派生类对象的情

况，此时转换才有意义。

这是由于运行时类型检查需要运行时类型信息，而这个信息存储在类的虚函数表。

## const_cast 
//用于【临时】去掉 const 限制，所谓的去掉 const 只是编译器给我们的一个假象 使用率低

## reinterpret_cast
//使用率低 常用于指针类型的转换；