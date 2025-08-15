
首先代码修改好之后就是进入git：
首先创建文件和ohos同级：
![[Pasted image 20240516142345.png]]

之后就是点击git随便进一个：
[feat: Progress支持通过样式Builder定制内容区 · Pull Request !29053 · OpenHarmony/arkui_ace_engine - Gitee.com](https://gitee.com/openharmony/arkui_ace_engine/pulls/29053/files)

gitee.com

gitee.com

feat: Progress支持通过样式Builder定制内容区 · Pull Request !29053 · OpenHarmony/arkui_ace_engine - Gitee.com

https://gitee.com/openharmony/arkui_ace_engine/issues/I9EIU0输入图片说明https://foruda.gitee.com/images...
然后进入yangziyong账号：选择我的仓库：
![[Pasted image 20240516142514.png]]
然后随便进入一个仓库：



点击master：
![[Pasted image 20240516143224.png]]
新建分支：
![[Pasted image 20240516143128.png]]

然后点击克隆下载：==备注改成克隆SSH下的代码==
![[Pasted image 20240516143403.png]]

终端执行如下：进入刚才新建的文件夹中执行如下命令：重点重点！！！！！！
git clone https://gitee.com/yangziyong/arkui_ace_engine_cjw_0131.git 
 cd arkui_ace_engine_cjw_0131/
 git branch ---当前分支在master
 git checkout
 git checkout progress_add_tdd ---切到页面建的分支 progress_add_tdd
 git branch ---查看当前所在分支  显示已经切换到 progress_add_tdd
 code .  --打开现在分支上的代码
 git status ----查看是否新增代码 文件路径
 git diff   ----查看差异
 git add    .  ---- 将当前本地文件添加到远程仓
 git commit -m 'test: add tdd to progress' --signoff     ----提交并生成一个commit
 git push   --- 提交代码
 git status 
git add    ./
git status
git commit --amend   ---覆盖提交
git push origin progress_add_tdd   -----提交代码
git push origin progress_add_tdd   -f   -----提交代码失败后用这个命令

git status
git diff
git add   ./
git commit -s
git branch
git push origin progress_add_tdd
如果提交两个commit：用两次：git commit -s
git log
git rebase -i ed6564be78a243a4cf4cc2b500ffae30c76cf40a
git push origin progress_add_tdd   -f   -----提交代码
git log ---只有一个commit

==git push 报错可能是密钥权限的问题修改一下权限==：

```
chmod 600 id_rsa
chmod 600 id_rsa.pub

```



git diff 查看错误
git status 查看修改文件路径
git  branch 查看当前所在分支
git checkout  progress_add_tdd 切换到 在git上新建的分支
code . 打开文件


![[Pasted image 20240516144041.png]]

之后拷贝修改的文件到分支上，之后就是提到pr上具体操作如下：

![[Pasted image 20240516144550.png]]

然后打开git：点击pr
![[Pasted image 20240516145209.png]]

![[Pasted image 20240516142808.png]]


代码拷贝到分支上然后
git status
之后  就会出现差异，然后在
git add    ./ 
存在暂存区

git commit   -s 或者-t   exit 退出
git commit --amend 覆盖上一次提交记

git commit -s/-t 是新增一个commit，如果想把两个合成一个：执行如下命令

git log
![[Pasted image 20240520104915.png]]
**合并：两个commit：git rebase -i** ed6564be78a243a4cf4cc2b500ffae30c76cf40a
会有两个pick，把不要的改成s，回车
ctrl+k 返回删除 
--把pick改成s
![[Pasted image 20240520105007.png]]
合并成功后重提：git push origin progress_add_tdd  -f
![[Pasted image 20240520105039.png]]
![[Pasted image 20240520105122.png]]




git push  origin  progress_add_tdd  -f

![[Pasted image 20240517171603.png]] 这就是提完代码了：

![[Pasted image 20240517171757.png]]start build 失败：需要关联一个issue


![[Pasted image 20240517171904.png]]

![[Pasted image 20240517171937.png]]

![[Pasted image 20240517172058.png]]


新建完，返回到pr，关联：
![[Pasted image 20240517172157.png]]

然后重新start build！！

拷贝文件之前先初始化build 文件：
初始化一下build文件，防止出错
 cat foundation/arkui/ace_engine/test/unittest/core/pattern/progress/BUILD.gn | prebuilts/build-tools/linux-x86/bin/gn format --stdin > FORMAT_RESULT.gn;cp -f FORMAT_RESULT.gn foundation/arkui/ace_engine/test/unittest/core/pattern/progress/BUILD.gn;rm FORMAT_RESULT.gn

**./build.sh --product-name rk3568 --ccache --build-target  progress_test_ng 先编这个** ！！！！！！这个过了在提交代码



代码差异：
![[Pasted image 20240521112400.png]]

git push zby_inter  imageSpan

等门禁过了之后就可以下载门禁上的镜像和sdk ，在本地进行自验证L0Top0