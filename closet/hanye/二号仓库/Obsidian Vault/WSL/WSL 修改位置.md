首先查看所有分发版本 
`wsl -l -v`   
*NAME STATE VERSION  * Ubuntu-20.04 Running 2*
导出分发版为tar文件到d盘 
`wsl --export Ubuntu-20.04 d:\\ubuntu20.04.tar` 
注销当前分发版 
`wsl --unregister Ubuntu-20.04`
重新导入并安装分发版在d:\ubuntu 
```
wsl --import Ubuntu-20.04 c:\\wsl\ubuntu f:\\ubuntu20.04.tar --version 2
``` 
设置默认登陆用户为安装时用户名 
`ubuntu2004 config --default-user Username` 
删除tar文件(可选) 
`del d:\\ubuntu20.04.tar`

```
wsl --import Ubuntu-20.04 d:\\wsl\ubuntu e:\\ubuntu20.04.tar --version 2
```