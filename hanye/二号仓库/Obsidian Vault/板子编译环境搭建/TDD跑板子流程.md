ch


首先把代码保存好在根目录下**单编**：
```
./build.sh --product-name rk3568 --ccache --build-target progress_test_ng

```


![[Pasted image 20240522153638.png]]
然后把生成的文件拷贝到e盘：操作如下
![[Pasted image 20240522154026.png]]
![[Pasted image 20240522154102.png]]拷贝到E盘这个位置然后，打开POWERSHELL:

```
cd E:\Test\developer_test

```

```
 .\start.bat

```

```
 run -t UT -ts overlay_manager_test_ng

```

![[Pasted image 20240522154411.png]]

![[Pasted image 20240522154440.png]]

然后就是拷贝这个路径，找到比对文件：
![[Pasted image 20240522154532.png]]

	![[Pasted image 20240522155533.png]]跑板子就成功了！
	
linux测试TDD
```
./build.sh --product-name rk3568 --ccache --build-target linux_unittest --gn-argsuse_thin_lto=false
```
```
cd foundation/arkui/ace_engine/test/unittest/scripts
```
```
python run.py #
```




全量执行所有测试用例
```
python run.py -t xxxx_test_ng #
```

执行单个测试用例