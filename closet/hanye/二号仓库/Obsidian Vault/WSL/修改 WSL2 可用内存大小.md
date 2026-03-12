WSL2默认可以使用的内存大小为主机的80%,对于Linux而言即使装了桌面,一般的开发也没必要给这么多内存,分多了,反而有可能卡主机的Windows

打开Windows资源管理器,地址栏输入 `%UserProfile%` 回车,在该目录下创建一个文件, 名字为 `.wslconfig` ,写入内容示例如下 (我电脑8GB内存,分给WSL内存2GB,另外设置交换分区4GB)

[wsl2] 
memory=2GB 
swap=4GB 
localhostForwarding=true

cmd执行
**wsl --shutdown** 
关闭WSL,再重新打开即可

文件位置

C:\Users\Administrator\AppData\Local\Packages\CanonicalGroupLimited.Ubuntu22.04LTS_79rhkp1fndgsc\LocalState

注销

wsl --unregister Ubuntu-22.04