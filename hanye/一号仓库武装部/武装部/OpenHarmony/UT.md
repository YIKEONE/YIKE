# TEST UT

### 安装testfwk_xdevice

[testfwk_xdevice: Development self-test and the base library of XTS certification testing | 开发自测试与XTS认证测试基础库 (gitee.com)](https://gitee.com/openharmony/testfwk_xdevice)

运行.\run.bat

### testfwk_developer_test

运行.\start.bat

`run -t UT`

### 编译ut代码
```bash
./build.sh --no-prebuilt-sdk --product-name rk3568 --ccache --build-target foundation/arkui/ace_engine/test/unittest/core/pattern/text:text_test_ng
```

`./build.sh --no-prebuilt-sdk --product-name rk3568 --ccache --build-target foundation/multimedia/histreamer/engine/plugin/plugins/rust_source/test/rtsp_ut:rust_source_plugin_unittest`

`./build.sh --no-prebuilt-sdk --product-name rk3568 --ccache --build-target foundation/multimedia/histreamer/engine/plugin/plugins/rust_source/test/hls_ut:rust_hls_source_plugin_unittest`

拷贝\\wsl.localhost\Ubuntu-20.04\home\xiaolong\xiaolong\ohos-0913\out\rk3568\tests\unittest

到testfwk_developer_test 同级目录unittest

git remote add caiying [](http://xxx.git/)[http://xxx.git](http://xxx.git)

git remote -v

git pull caiying

输入仓库账户、密码

git checkout caiying/DB_rm015/caiying/test1 -b DB_rm015/caiying/test1

git branch -l

git pull

### UT测试Win

UT编译命令>

./build.sh --no-prebuilt-sdk --product-name rk3568 --ccache --build-target foundation/multimedia/histreamer/engine/plugin/plugins/rust_source/test/rtsp_ut:rust_source_plugin_unittest

[https://gitee.com/openharmony/testfwk_xdevice.git](https://gitee.com/openharmony/testfwk_xdevice.git)

.\run.bat

[https://gitee.com/openharmony/testfwk_developer_test.git](https://gitee.com/openharmony/testfwk_developer_test.git)

修改文件testfwk_developer_test\config\user_config.xml以下内容

`<test_cases> <dir>E:\\tools\\test</dir> </test_cases>`

注：`E:\\tools\\test\\`**testfwk_developer_test**

复制ohos-0913\out\rk3568\tests\unittest到`E:\\tools\\test`

运行E:\tools\test\testfwk_developer_test\start.bat

`.\\start.bat`

选择rk3568>1

> run -t UT

开始UT

hdc file recv /data/rtsp.log ./

hdc file recv /data/local/traces/ ./traces/

hdc file send E:\tools\test\libsource_plugin_rust.z.so lib/

hdc file send E:\tools\test\libhistreamer_plugin_RtspSource.z.so lib/

hdc shell power-shell timeout -o 40000000

hdc shell param set debug.media_service.histreamer 1

hdc shell param set persist.init.debug.seccomp.enable 0

hdc shell setenforce 0

hdc shell hilog -b D

hdc shell hilog -D 0xD002B00 | tee ./hilog_http_source_disable_7.log


### TDD

rm -rf out/rk3568/tests/unittest/ && ./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --ccache --build-target=overlay_manager_test_ng

编译完的TDD位置

/home/ying/code/oh0206/out/rk3568/tests/unittest/ace_engine/components/

测试

`运行命令： 
hdc shell mount -o rw,remount / 
hdc shell mkdir temp1 
hdc file send overlay_manager_test_ng /temp1/ 
hdc shell cd temp1/ && hdc shell chmod 777 /temp1/overlay_manager_test_ng 
hdc shell /temp1/overlay_manager_test_ng`