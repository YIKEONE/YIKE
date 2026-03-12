1.解决报错：错误码9568393
![[Pasted image 20240730095810.png]]

下载sdk替换一下：目录如下

C:\Program Files\Huawei\DevEco Studio\sdk\HarmonyOS-NEXT-DB1\openharmony
C:\Users\Administrator\AppData\Local\OpenHarmony\Sdk\12

2.安装hap包报错：

![[img_v3_02d9_da29b674-4a75-4cb4-8569-3bf2f36ae9bg.jpg]]

这个报错是要安装build下面的hap包，然后在安装自己工程的hap包，缺一不可！

3.安装huap包流程：
首先打包这个工程，然后远程黄区电脑，通过邮件发送，新建自己的文件夹，然后用deveco打开，之后就是执行build
![[Pasted image 20240730195019.png]]
![[Pasted image 20240730195147.png]]

然后进行编译：李琦老师执行后续流程。

3.deveco 报这个问题如何解决：
![[Pasted image 20240807153203.png]]
4.deveco 执行preview 用最简单的helloworld demo 测试效果，显示一片白，这个问题是要修改文件配置：
![[Pasted image 20240807155140.png]]
![[Pasted image 20240807155207.png]]

5但改完报错
![[img_v3_02dh_5489416f-0c5d-4d44-9a49-e87a3757ccdg.jpg]]

解决方法：

错误码9568389
![[Pasted image 20240823154355.png]]

