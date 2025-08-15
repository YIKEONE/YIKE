编译 只编译不上板的用例(不上板用例只可以用linux_unittest这个目标进行编译) 在项目根目录下执行：
比如pr提完门禁过，要放一个对比图：
首先git  还原修改，记住这些命令都是在
![[Pasted image 20240704103157.png]]
这个目录下执行的，首先git branch 查看一下当前的分支：在头指针就可以操作了
![[Pasted image 20240704103239.png]]
```
先git stash 然后git stash pop

```
以下命令执行的目录是 重要重要！！！
![[Pasted image 20240704103335.png]]
```Bash
./build.sh --product-name rk3568 --ccache --build-target linux_unittest
```
  如果出现一些`Ltmp`临时编译符号未定义的错误，这个问题是由`fuzztest`引起的，需要增加一个编译命令
  ```Bash
./build.sh --product-name rk3568 --ccache --build-target linux_unittest --gn-args use_thin_lto=false
```
  **2.执行**

  编译完成后，切换到scripts目录\
  ```Bash
cd foundation/arkui/ace_engine/test/unittest/scripts
```
  执行目录下的run.py脚本InputFilter
  ```Bash
python run.py    #全量执行所有测试用例
python run.py -t xxxx_test_ng    #执行单个测试用例
```
 
  执行全量测试用例最终会输出一个test_result.json文件，文件路径会打印在日志输出的末尾
  ![[Pasted image 20240704134719.png]]
 
  需要分别在**有你代码**和**没有你代码**的情况下各执行一次，得到**两个t**est_result.json文件，对比两个文件的内容，确认没有新增“failed_tests_count”和“unavailable”就可以了，然后在PR上贴上前后对比图，参考https://gitee.com/openharmony/arkui_ace_engine/pulls/28611
 ![[Pasted image 20240814095317.png]]