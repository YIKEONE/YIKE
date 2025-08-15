
1.代码在本地整编过后，看一下log是否正常，没问题再提pr！！！！pr门禁过了下门禁镜像和sdk测试l0top0
首先pr分为三种：：①Interface_sdk_js下的，②arkui_ace_enging下的，③doc下的 
一共要fork三个仓！命名方式注意一下
![[Pasted image 20240705144106.png]]
2.区别：Interface_sdk_js提的pr是新增接口，arkui_ace_enging提的pr是业务代码，doc是组件接口功能描述
3.提pr流程：首先fork一个自己的仓，然后创建一个分支，之后在新建pr，过程如下：

->interface的接口pr代码注意项：

①冒号后有空格
②注释对齐，顺序不能错，automicservice支持
③不能用value
④上下各空一行

![[Pasted image 20240703164744.png]]

->新的提交pr流程：
随便点一个pr 进去：点击OpenHarmony

![[Pasted image 20240702104126.png]]

![[Pasted image 20240702104202.png]]
![[Pasted image 20240702104239.png]]
![[Pasted image 20240702104258.png]]
![[Pasted image 20240702104331.png]]
![[Pasted image 20240702104346.png]]
![[Pasted image 20240702104430.png]]
![[Pasted image 20240702104609.png]]

点击master：
![[Pasted image 20240516143224.png]]

新建分支：
![[Pasted image 20240516143128.png]]
然后点击克隆下载：==备注改成克隆SSH下的代码==
![[Pasted image 20240516143403.png]]

```
 git clone https://gitee.com/yangziyong/arkui_ace_engine_cjw_0131.git 
 cd arkui_ace_engine_cjw_0131/
 git branch ---当前分支在master
 git checkout
 git checkout progress_add_tdd ---切到页面建的分支 progress_add_tdd
 git branch ---查看当前所在分支  显示已经切换到 progress_add_tdd
 code .  --打开现在分支上的代码
```
在对应分支上修改完代码然后用git命令提交push一下，
命令具体如下：（具体命令具体实施！不一定按照我这个来）
```
git diff 
git status
git branch  --切到新建的分支
git commit   -s 或者-t   exit 退出  、git commit --amend --覆盖提交记录一般用于后续修改
git add .
git diff
git status
git push origin 分支名字 （progress_add_tdd）
git reset --hard 4f08bcd29ec6f7eca5e110b97cfe896d85387426 //回退提到master分支的错误代码
```
之后就是新建pr，在自己仓下新建，关联自己新建的分支，步骤如下：
![[Pasted image 20240516145209.png]]
![[Pasted image 20240516142808.png]]
![[Pasted image 20240517171904.png]]
![[Pasted image 20240517171937.png]]
之后就是把pr关联一下issue，然后检查一下没问题就可以start build

填写的一个表：把业务代码的pr填到这个表里
![[Pasted image 20240704144058.png]]

自测：门禁通过后，1.接口pr就是interface 那个下面仓的pr合入，就把业务代码的镜像和sdk跑一下：看一下是否支持preview
2.接口pr还未合入，把接口pr的sdk 下载到本地，业务代码pr的镜像下载到本地，然后自测


--替换镜像并烧录的步骤：

![[Pasted image 20240622093457.png]]
![[Pasted image 20240622093726.png]]

--然后就是清空所有项导入所有项，这里D盘images1是之前的镜像。

![[Pasted image 20240622093840.png]]

--业务代码pr的门禁上的dayu_200下到本地，这个就是最新的镜像，烧到板子里测试demo
接口pr的门禁上的ohos_sdk下到本地，这个就是最新的sdk,替换一下。就可以测试demo

![[Pasted image 20240702093501.png]]

![[Pasted image 20240702093520.png]]
![[Pasted image 20240702093538.png]]

--替换sdk步骤：

![[Pasted image 20240705141946.png]]

--把windows下的五个文件拷贝到c盘，然后把devceo关闭，解压到当前位置

![[Pasted image 20240428100213.png]]
![[Pasted image 20240702093743.png]]

--==业务代码pr的门禁上的dayu_200和接口pr的门禁上的ohos_sdk打包成zip，不能是7z==

--代码门禁通过==本地自测成功==就可以把sdk和镜像打包zip发给对应的测试，之后就是在业务代码的pr放对比截图：具体步骤如下：
```
./build.sh --product-name rk3568 --ccache --build-target linux_unittest --gn-args use_thin_lto=false
```
\
```
cd foundation/arkui/ace_engine/test/unittest/scripts
```

```
python run.py
```

![[Pasted image 20240704134719.png]]

--需要分别在**有你代码**和**没有你代码**的情况下各执行一次，得到**两个t**est_result.json文件，对比两个文件的内容，确认没有新增“failed_tests_count”和“unavailable”就可以了，然后在PR上贴上前后对比图，参考https://gitee.com/openharmony/arkui_ace_engine/pulls/28611

--然后就填写这个表：
![[Pasted image 20240704143831.png]]
![[Pasted image 20240704172123.png]]
![[Pasted image 20240704172012.png]]

--提示没问题就可以填下下面三个表

![[Pasted image 20240704171909.png]]
![[Pasted image 20240706164231.png]]
![[Pasted image 20240704172243.png]]

之后就是写doc文档，提pr。
--写doc步骤：首先在doc下fork一个自己的仓 命名方式doc_名字拼音

![[Pasted image 20240705101219.png]]

![[Pasted image 20240705101414.png]]

![[Pasted image 20240705101600.png]]
![[Pasted image 20240705101655.png]]
![[Pasted image 20240705101803.png]]

```
git checkout -b 0705_colorfilter origin/0705_colorfilter
```
![[Pasted image 20240705110649.png]]

然后打开分支上的doc：
![[Pasted image 20240705110817.png]]

![[Pasted image 20240705110733.png]]

有几点要注意：
①属性
②版本号是12
③示例 最简单的那个colorfilter 不包含modifier
④截图，比例一致， 一比一截图清晰

[[AR-1] 【ArkUI开发框架_组件】【SR20240418679149】【内部单】Previewer显示失败 - Jira](https://10.0.77.88/jira/browse/AR-1)
收到测试并解完bug后邮件就点击处理中，经办人转给测试人员，并给测试人员发zip包，包名命名规则：SRxxxbase2024xxxx==01==,01根据日期决定，比如你在一天中发了三次包给测试就是01 02 03  如果第二天也发了，就从01 开始

![[Pasted image 20240705125239.png]]

在开发过程中要及时更新这个表，自己项目的状态要把控好：实时更新

![[Pasted image 20240705143447.png]]

写doc时候遇到的问题：
①是否支持卡片能力，取决于新加的接口是否有@form,原子化服务API对应的就是@atomicservice
②value是否修改为filter，跑门禁之后看是否有问题在修改
③示例代码太单一，因为我这个接口可以有两种方式调，要写在一起，然后截图不能太糊且不能有毛刺。
修改代码然后提交注意事项：
要在pr上放一个刚进devceo的截图，代表demo编译成功，之后就是start build，然后填写合入检视表
![[img_v3_02ch_e357788e-853c-4978-b873-ce7545c3c96g.jpg]]
![[Pasted image 20240706165352.png]]

这个表内部过了之后就填写PR推进表。
门禁通过后，填写PR推进表

录制的视频要传到svn路径如下：
```
svn://10.0.77.88/ArkUI_Enhance202404/1.ManagementDocLibrary/06.MeetingRecord/3.需求澄清&串讲会议纪要
```


后续提pr 就在对应的仓建一个分支，然后在新分支上改代码。
![[Pasted image 20240712150239.png]]
这个是本地仓，然后在本地自己的仓建一个分支，push的时候，分支才会到远程仓内


![[Pasted image 20240807205148.png]]

新加一个业务代码的分支change_open_changge

![[Pasted image 20240807205536.png]]



```
git pull origin 0816_bindmenu //更新本地分支

首先在远程仓新建一个分支0816_bindmenu,然后本地也新建一个分支0816_bindmenu
命令如下：git checkout -b 0816_bindmenu origin/0816_bindmenu
```

特殊情况：要先找责任田人加分，pass过后在执行start build。。。。哎

正常流程是先跑门禁start build，然后门禁通过在找人加分
![[Pasted image 20240816205220.png]]


后续在提交pr直接，远程端更新按钮点击，然后打开linux，首先切到master分支，之后在git pull origin
然后新建一个分支，编写代码
![[Pasted image 20240817163306.png]]


编译生成的镜像路径：![[Pasted image 20240923153107.png]]