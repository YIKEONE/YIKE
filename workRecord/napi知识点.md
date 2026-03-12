# 闲隙碎笔

## *JNI*

~~~c++
jniEnv->FindClass(CLASS_NAME); // 用过CLASS_NAME也就是路径找到Java类 
~~~

## *NAPI*

### napi注册过程

~~~tex
napi_defined_class() -> napi_get_prototype() -> napi_create_function() -> napi_set_named_property() -> 注册类 -> 注册模块
    
1.先写好完整的c++的类，包括构造，属性，方法...，通过napi一系列方法，将c++的类注册到js中
2.napi_defined_class():传入c++构造回调，获得js对象
3.napi_get_prototype():传入js对象，获取js对象的属性列表
4.创建js方法，并加入到js对象的属性列表中，napi_create_function():传入c++函数回调，获取该函数对应的js函数。napi_set_named_property()：把该js函数设置到对应的js对象的属性列表中，传入js对象的属性列表prototype和js函数method，静态方法传入的就是js对象和js函数
5.把整个Myclass类到入到js中，napi_set_named_property()
6.最后模块的注册
~~~

#### napi_define_class

~~~c++
napi_status napi_define_class(napi_env env,// 操作的句柄
                              const char* utf8name,// 类名
                              size_t length,// 类名的长度
                              napi_callback constructor,// c++类的构造函数的指针
                              void* data,// 传入构造函数的参数
                              size_t property_count,// 类属性的个数
                              const napi_property_descriptor* properties,//
                              napi_value* result);// 如果函数成功，返回类的js对象
~~~


#### napi_get_prototype

```c++
napi_get_prototype(env, constructor, &prototype);// 获取原型对象
// constructor通过napi_define_class获取的js对象
// prototype获取的也就是js对象的属性
napi_value prototype;
status = napi_get_prototype(env, constructor, &prototype);
```

#### napi_create_function

```c++
napi_status napi_create_function(napi_env env,//创建js函数，与c++函数所映射
                                 const char* utf8name,//函数名字
                                 size_t length,//函数长度
                                 napi_callback cb,//对应的c++函数的回调
                                 void* data,//
                                 napi_value* result)//所创建的js函数
napi_value method;
napi_status status = napi_create_function(env, nullptr, 0, MyMethod, nullptr, &method);
```

#### napi_set_named_property

~~~c++
napi_status napi_set_named_property(napi_env env, //设置js对象的属性
                                    napi_value object, //js对象的属性
                                    const char* utf8name, //属性名字，
                                    napi_value value)//c++回调函数，
//通过napi_get_prototype获取对象的属性
status = napi_set_named_property(env, prototype, "printValue", method);
//设置静态方法，js对象的属性直接传js对象
status = napi_set_named_property(env, constructor, "staticMethod", staticMethod);
//将MyClass类导出到js中
status = napi_set_named_property(env, exports, "MyClass", constructor);
~~~

### NAPI数据类型

```tex
napi_env: 	表示指向环境的指针，可以想象为作用域
napi_status:表示NAPI接口执行的结果，napi_ok，napi_invalid_arg，napi_generic_failure
napi_value:	表示任何JavaScript值，不能直接访问，需要通过NAPI函数来操作
napi_info:	表示调用回调时的上下文参数
```

### NAPI接口

#### napi_get_cb_info

~~~c++
//thisVar表示指针，例如demo.add()，在add的napi函数声明时，thisVar为demo
napi_status napi_get_cb_info(napi_env env,
                             napi_callback_info cbinfo,
                             size_t* argc,
                             napi_value* argv,
                             napi_value* thisArg,//out:this，如果obj.fun()，那么this为obj
                             void** data)//附加数据
~~~

#### napi_get_value_string_utf8

```c++
//thisVar表示指针，例如demo.add()，在add的napi函数声明时，thisVar为demo
NAPI_EXTERN napi_status napi_get_value_string_utf8(napi_env env,//napi string 转 c++ string
                                                   napi_value value, //napi string
                                                   char* buf, // c++ string
                                                   size_t bufsize, // 设置c++ string的缓存区大小
                                                   size_t* result) // napi string的长度
```
#### napi_new_instance

```c++
napi_status napi_new_instance(napi_env env,//创建js类的实例
                              napi_value constructor,//类的构造器
                              size_t argc,//参数个数
                              const napi_value* argv,//参数列表
                              napi_value* result);//成功后的类的实例
```

### NAPI异步调用

##### napi_create_async_work

```c++
napi_status napi_create_async_work(napi_env env,
                                   napi_value async_resource,
                                   napi_value async_resource_name,//为字符串，用于测试和调试
//typedef void (*napi_async_execute_callback)(napi_env env, void *data);
                                   napi_async_execute_callback execute,//执行耗时操作的回调，在worker线程
//typedef void (*napi_async_complete_callback)(napi_env env, napi_status status, void *data);
                                   napi_async_complete_callback complete,//执行完成的回调，在js主线程，用于返回，回收资源
                                   void* data,//用于传给两个回调的参数
                                   napi_async_work* result);//返回的napi_async_work异步工作项
```

#### napi_queue_async_work

```c++
napi_status napi_queue_async_work(node_api_basic_env env,
                                  napi_async_work work);//使用napi_create_async_work获得的async_work
```

### js和c++数据的绑定和解绑

#### napi_wrap & napi_unwrap 

~~~c
napi_status napi_wrap(napi_env env,
                      napi_value js_object,//js对象
                      void* native_object,//c++对象
//void finalize_cb(napi_env env, void* finalize_data, void* finalize_hint);data为绑定到js的c++数据指针
                      napi_finalize finalize_cb,//在js的gc时调用
                      void* finalize_hint,//传给finalize_cb的参数，也就是finalize_hint
                      napi_ref* result);//返回的绑定的js对象的指针，不需要时，传入null，需要时传入&napi_value

napi_status napi_unwrap(napi_env env,
                        napi_value js_object,//js对象
                        void** result);//c++对象
~~~

