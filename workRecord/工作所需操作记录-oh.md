# 烧镜像

## 烧镜像/推So包

1. 将A中的root和log文件夹复制到B中
2. 将root中BINs所有的.img文件都复制到log的fastboot_basepkg中
3. log/ALN_AL00_all_cn/update_allpkg.bat
4. 执行跳开机的脚本
5. 执行推So包的脚本
6. 安装HAP 
7. 修改common.d.ts 有两个：ets/component 还有 build-tools/../declarations



## 拉代码

1. 将A中的manifest.xml复制到B中
2. 使用xshell在远程服务器中创建自己的文件夹，并且创建与AB相同的文件夹
3. 开始拉代码
4. 在第一次编译的时候，使用第一条编译指令，在之后修改代码的时候，使用第二条的快编指令即可，都是使用下面的代码

xshell: 右键 ->ftp -> 登陆：号：服务器号：mwx390290，密码：huawei1234



# 提蓝区PR

1. 先需要知道提交的开源仓例如ace_engine（开源仓），fork该仓（fork仓）

2. 克隆fork仓

   ~~~bash
   git clone + fork仓地址
   ~~~

3. 设置fork仓的上游，更新代码

   ~~~bash
   git remote add upstream git@gitee.com:openharmony/arkui_ace_engine.git # 若不删除仓，设置一次即可
   # 查看是否添加上游成功
   git remote -v
   #  从开源仓拉代码到fork仓
   git fetch upstream
   ~~~

4. 选择要提交的仓，以此为基础创建分支

   ~~~bash
   git branch -a
   git checkout upstream/要提交到的分支名 -b branch_name / dev # 例如master，或者对应的特性分支
   ~~~
   
5. 提交代码

   ~~~bash
   git add .
   # 第一次
   git commit -s
   # 之后
   git commit --amend
   git push origin 分支名 -f
   ~~~

6. 提交pr，创建pull，创建issue



# fork仓和开源仓保持同步

~~~bash
使得fork仓和开源仓保持同步
git remote add upstream git@gitee.com:openharmony/arkui_ace_engine.git # 若不删除仓，设置一次即可
# 更新上游
git fetch upstream
# master为对应的分支，test自己取的名
git checkou upstream/master -b test
~~~



# 蓝区解冲突

~~~bash
## 解决冲突
# 设置fork仓的上游，为了保持fork仓和开源仓同步
git remote add upstream git@gitee.com:openharmony/arkui_ace_engine.git # 若不删除仓，设置一次即可
# 查看是否添加上游成功
git remote -v
#  从开源仓拉代码到fork仓
git fetch upstream
# 变基
git rebase upstream/master # 对应要提交的分支
# 解决冲突后
git rebase --continue

# 若有新的提交 
git add .
git commit --ament
git push ...
~~~



# Git

~~~bash
# git添加到暂存区
git add .

# git删除文件
git rm test/\*.log 			# 删除test/目录下，所有的.log文件
git rm --cached test.txt 	# 删除暂存区中的文件

# git提交到本地仓库
git commit -m "first commit"
git commit --amend

# git移动文件
git mv file_form file_to

# 暂存，例如在分支a修改了代码，但是实际要提到b分支
git stash
git stash -l
git stash pop
git stash pop @编号
git stash drop

# 查看某一笔提交的差异
git show hash --stat
    
# 拉远程代码
git fetch upstream

# 显示远程仓和本地仓之间的差异
git log master...upstream/master

# 操作失误，想回退
git relog
git reset <hash> --hard # hash为想要回退位置的hash

# 提交多合一
git rebase -i HEAD~`n` # 将除第一个提交外的其他提交的开头的 `pick` 关键字改为 `squash`

# cherry-pick
git cherry-pick <对应的hash>
git cherry-pick --continue	# 继续

git cherry-pick --abort 	# 取消本次cherry-pick
~~~



# 编TDD

```shell
1.     ./build.sh -p rk3568 -T ace_engine_unittest    #这会在out中生成 /home/hanye/work/code/out/rk3568/tests/unittest/这个文件夹
2.     /home/hanye/work/code/out/rk3568/tests/unittest/ 内容 替换到  E:\Test\testcase\unittest
3.    编译SDK 将下面位置生成的toolchain拷贝到本地 注意：windows 版本   /home/hanye/work/code/out/sdk/packages/ohos-sdk/windows/  将本地路径复制添加到环境变量，这样才能识别板子
4.    
```



# build指令

1. 单独编蓝区的ace_engine仓

   ~~~bash
   # cd 到根目录
   ./build.sh --product-name rk3568 --ccache -T ace_engine --fast-rebuild
   ./build.sh --product-name rk3568 --ccache --no-prebuilt-sdk --fast-rebuild
   
   # 门禁codeCheck检查
   static-check
   
   # tdd
   run -UT -ts accessiibility_adapter_test_ng
   ~~~



# 需求交付流程

1. 编写需求代码，提蓝区

2. 蓝区找人加分，填合入详情表，最好是在交付前的半个月，时间比较充足

   ~~~
   合入详情表：
   tdd: 和华为确定无障碍的tdd +  accessibility_property_test_ng
   autoui: accessibilitydev
   xts: XTS run -I ActsActionExtension AbilityTest;ActsUIExtension Test;AActsUlExtForResultAsCallerTest;ActsShareExtension Ability Test;ActsuiExtensionForResult Test
   ~~~

3. 合黄区dev，填合入详情表

4. 与测试对其测试用例，同步完善交付件



# HDC相关指令

1. 开启DEBUG模式

   ~~~bash
   
   ~~~





