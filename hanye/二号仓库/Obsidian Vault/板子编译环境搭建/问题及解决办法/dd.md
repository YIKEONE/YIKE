编译代码及测试环境搭建
一、SDK
SDK编译命令:
```
./build.sh --product-name ohos-sdk --ccache 

```
SDK路径：
```
out/sdk/packages/ohos-sdk/

```
二、编译源码
```
 ./build.sh --product-name rk3568 --ccache.
```
 快速差分编译：
 
```
./build.sh --product-name rk3568 --gn-args enable_notice_collection=false --gnargs load_test_config=false --gn-args enable_lto_O0=true --fast-rebuild --ccache

``` 
并行下载代码并强行合并
```
repo： repo sync -c -j16 --force-sync 
```

同步代码：
```
repo sync -c 

```
```
repo forall -c 'git lfs pull'

```

三、DevEcoStudio
```
 安装：照下面链接步骤执行 -------飞书打开链接 https://neusoft.feishu.cn/docx/KDULdiC1CoAF6kxpGsGcXcNbnch log位置： C:\Users\Administrator\AppData\Local\Huawei\DevEcoStudio4.1\log 

```

四、TDD
1、不需要真机 只编译不上板的用例(不上板用例只可以用linux_unittest这个目标进行编译) 在项目根目录下执行：
```
 ./build.sh --product-name rk3568 --ccache --build-target linux_unittest 

```

如果出现一些`Ltmp`临时编译符号未定义的错误，这个问题是由`fuzztest`引起的，需要增加一个编译命令
```
Bash./build.sh --product-name rk3568 --ccache --build-target linux_unittestgn-args use_thin_lto=false 

```

执行编译完成后，切换到scripts目录 
```
cd foundation/arkui/ace_engine/test/unittest/scripts

```
 
 执行目录下的run.py脚本 
```
 python run.py 

```

#全量执行所有测试用例
```
python run.py -t xxxx_test_ng

```

 #执行单个测试用例
  执行全量测试用例最终会输出一个test_result.json文件，文件路径会打印在日志输出的末尾
  
   2、真机测试 
   1)、Linux下运行命令：
```
 ./build.sh -p rk3568 -T ace_engine_unittest

```
  
  1）/home/hanye/work/code/out/rk3568/tests/unittest/ace_engine/components/ ![[Pasted image 20240522162432.png]]
   然后将此处的生成的测试文件例如：overlay_manager_test_ng 放到windows里相同的位置里。真机环境搭建如下: 
   
   2）代码中更改build 将foundation/arkui/ace_engine/test/unittest下的build.gn unittest 改成ace_engine_unittest 
   ![[Pasted image 20240521145658.png]] 
   将foundation/arkui/ace_engine/bundle.json 文件改成 "//foundation/arkui/ace_engine/test/unittest:ace_engine_unittest" ![[Pasted image 20240521160819.png]] ![[img_v3_02av_0435c92a-132b-469c-adb4-4e2cce07d60g.jpg]] ![[img_v3_02av_229e6808-1179-4361-bd38-e57c5dd8e88g.jpg]
2）、代码根目录下编译代码： ./build.sh -p rk3568 -T ace_engine_unittest 这会在out中生成 /home/hanye/work/code/out/rk3568/tests/unittest/这个文件夹
   
3)下载test.zip压缩文件并解压 ![[Pasted image 20240521163125.png]] 将上述2）生成的文件夹替换 /home/hanye/work/code/out/rk3568/tests/unittest/ 内容 替换到 E:\Test\testcase\unittest 4）、编译SDK 将下面位置生成的toolchain拷贝到本地 注意：windows 版本 /home/hanye/work/code/out/sdk/packages/ohos-sdk/windows/ ![[Pasted image 20240522100117.png]] 将本地路径复制添加到环境变量，这样才能识别板子 ![[Pasted image 20240522154843.png]] 5）、打开windows power shell ![[Pasted image 20240522155300.png]]6)、切换到 E:\Test\developer_test 路径下 ![[Pasted image 20240522155610.png]] ![[Pasted image 20240522160307.png]] 运行命令： run -t UT -ts overlay_manager_test_ng ----此处文件是第一步拷贝下来的。 7）、生成的文件位置在E:\Test\developer_test\reports ![[Pasted image 20240522163251.png]] ![[Pasted image 20240522163451.png]]