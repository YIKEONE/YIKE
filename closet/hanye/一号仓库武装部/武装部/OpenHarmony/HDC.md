## 简介

hdc（HarmonyOS Device Connector）是HarmonyOS为开发人员提供的用于调试的命令行工具，通过该工具可以在windows/linux/mac系统上与真实设备或者模拟器进行交互。

[](http://zhuoqun.info/article/451/#top)

## 环境准备

hdc工具通过HarmonyOS SDK获取，存放于SDK的toolchains目录下，使用时将SDK的toolchains目录（C:\Users\{用户名}\AppData\Local\Huawei\Sdk\hmscore\3.1.0\toolchains）添加到环境变量。

- Windows环境变量设置方法：
    
    在**此电脑 > 属性 > 高级系统设置 > 高级 > 环境变量**中，添加HDC端口变量名为：OHOS_HDC_SERVER_PORT，变量值可设置为任意未被占用的端口，如7035。
    
    ![](https://alliance-communityfile-drcn.dbankcdn.com/FileServer/getFile/cmtyPub/011/111/111/0000000000011111111.20231117162302.87254931269241703703303922026277:50001231000000:2800:E70FA50DE3E6DA9464FA3779AAD24C72E643A9544FB26242A252AF917FAF2790.png?needInitFileName=true?needInitFileName=true)
    
    环境变量配置完成后，关闭并重启DevEco Studio。
    
- macOS环境变量设置方法：
    1. 打开终端工具，执行以下命令，根据输出结果分别执行不同命令。
        
        ```bash
        echo $SHELL
        ```
        
        复制
        
        - 如果输出结果为/bin/bash，则执行以下命令，打开.bash_profile文件。
            
            ```bash
            vi ~/.bash_profile
            ```
            
            复制
            
        - 如果输出结果为/bin/zsh，则执行以下命令，打开.zshrc文件。
            
            ```bash
            vi ~/.zshrc
            ```
            
            复制
            
    2. 单击字母“i”，进入**Insert**模式。
    3. 输入以下内容，添加HDC_SERVER_PORT端口信息。
        
        ```bash
        export HDC_SERVER_PORT=7035
        ```
        
        复制
        
    4. 编辑完成后，单击**Esc**键，退出编辑模式，然后输入“:wq”，单击**Ente****r**键保存。
    5. 执行以下命令，使配置的环境变量生效。
        
        ```bash
        source ~/.bash_profile
        ```
        
        复制
        
    6. 环境变量配置完成后，关闭并重启DevEco Studio。

## 注意事项

- 使用hdc，如果出现异常，可以尝试通过hdc kill -r命令杀掉并重启hdc服务。
- 如果出现hdc list targets获取不到设备信息的情况，可以通过任务管理器查看是否有hdc进程存在。若进程存在，则通过hdc kill -r命令杀掉该进程。

说明

- 命令行中被[]修饰的参数表示可选参数。
- 命令行中的参数若是斜体，表示在使用时该参数需替换为具体的信息，例如：file send _local remote_命令中的local和remote，使用时需替换为本地待发送和远端待接收的文件路径。
## 开发指导
# shell 命令
$ hdc shell am force-stop net.xieboke.helloword
# 查询已连接的所有目标设备，添加-v选项，则会打印设备详细信息
$hdc list targets
2KE0220103009100        device
# shell 命令
$ hdc shell bm uninstall net.xieboke.helloword
# 从本地发送文件至远端设备
$ hdc file send E:\DevEcoStudioProjects\helloword\entry\build\default\outputs\default\entry-default-
signed.hap /sdcard/1ed1f3218e3843ecbb52f0d2458bb511/entry-default-signed.hap
# 从远端设备发送文件至本地
hdc file recv remote local
# 安装指定的应用package文件
$ hdc shell bm install -p /sdcard/1ed1f3218e3843ecbb52f0d2458bb511/
# 卸载指定的应用包package包名
hdc uninstall packageName
# 删除文件夹
$ hdc shell rm -rf /sdcard/1ed1f3218e3843ecbb52f0d2458bb511
# 启动 APP
$ hdc shell aa start -a EntryAbility -b net.xieboke.helloword


https://developer.harmonyos.com/cn/docs/documentation/doc-guides-V3/ide-command-line-hdc-0000001237908229-V3