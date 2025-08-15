
tdd首先看一下原生的build.gn是否好使，不好使就逐行试，看哪个tdd是好使的，自己编写tdd也是这样，按照断言来逐行注释编译，这里编译用的是真机编译指令
```
./build.sh --product-name rk3568 --ccache --build-target progress_test_ng
```
首先用真机跑一下现有的tdd，流程***进行单编tdd需要板子***
真机跑tdd遇到build.gn文件不存在，需要往上层寻找：发现他被注释掉了
![[Pasted image 20240801141346.png]]

1.编写tdd：路径如下
![[Pasted image 20240801140331.png]]
![[Pasted image 20240801140401.png]]

2.进行单编tdd需要板子：

①首先把代码保存好在根目录下**单编**：

```
./build.sh --product-name rk3568 --ccache --build-target overlay_manager_test_ng

```

②然后把ubuntu生成的文件拷贝到e盘：操作如下
![[Pasted image 20240802091923.png]]
![[Pasted image 20240802091941.png]]
③拷贝到E盘这个位置然后，打开POWERSHELL:
![[Pasted image 20240802092003.png]]

```
cd E:\Test\developer_test

```

```
 .\start.bat

```

```
run -t UT -ts progress_test_ng
```

![[Pasted image 20240802092049.png]]

![[img_v3_02dc_c2a26291-0070-451e-9c2c-5cd82232991g.jpg]]
3.然后进行无真机跑tdd 对比截图
