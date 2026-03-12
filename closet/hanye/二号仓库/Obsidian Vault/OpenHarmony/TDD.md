##   ArkUI黄蓝区不依赖真机环境用例执行

  华为wiki原文链接在红WeLink 陈佳锋30043950 的个人签名中

####   1.编译

  只编译不上板的用例(不上板用例只可以用linux_unittest这个目标进行编译)

  在项目根目录下执行：

```Bash
./build.sh --product-name rk3568 --ccache --build-target linux_unittest
```

  如果出现一些`Ltmp`临时编译符号未定义的错误，这个问题是由`fuzztest`引起的，需要增加一个编译命令

```Bash
./build.sh --product-name rk3568 --ccache --build-target linux_unittest --gn-args use_thin_lto=false
```

####   2.执行

  编译完成后，切换到scripts目录

```Bash
cd foundation/arkui/ace_engine/test/unittest/scripts
```

  执行目录下的run.py脚本

```Bash
python run.py    #全量执行所有测试用例
python run.py -t xxxx_test_ng    #执行单个测试用例
```

  执行全量测试用例最终会输出一个test_result.json文件，文件路径会打印在日志输出的末尾

![](https://neusoft.feishu.cn/space/api/box/stream/download/asynccode/?code=YTg2N2IyODk5OTU3OTExYjU5YWUwZTFjMzI4NDZkNTlfa2lDZXBuZlYwVGtqRUUwYW5LYkdrWGdnOG81Z3JiSlBfVG9rZW46SlROQWJuNGYxb3FtRk94djgyYWNrV29qbndLXzE3MTEwODk0OTM6MTcxMTA5MzA5M19WNA)

  需要分别在有你TDD代码和没有你TDD代码的情况下各执行一次，得到两个test_result.json文件，对比两个文件的内容，确认没有新增“failed_tests_count”和“unavailable”就可以了，然后在PR上贴上前后对比图，参考https://gitee.com/openharmony/arkui_ace_engine/pulls/28611

  

  其他注意事项：

  1.现在蓝区只执行不上板的用例就可以了，不用执行**[tdd编译](https://neusoft.feishu.cn/docx/UUQNdXz1soyg8wx3A09cPltJnvh#part-CfBudMaO2olcHbxF3WqcR7bunx4)**这里的操作得到网页版的reports了，也不用改bundle.json和BUILD.gn这两个文件

  2.如果你的TDD文件在unavailable中，只要两个test_result.json中没有新增“failed_tests_count”和“unavailable”就可以（证明不是自己的代码问题）