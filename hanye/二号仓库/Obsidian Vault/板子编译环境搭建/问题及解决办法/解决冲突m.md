1.==先进pr==
![[Pasted image 20240522105218.png]]
```
cd /node_add/arkui_ace_engine_cjw_0131

```
```
git branch --查看当前分支

```
```
git checkout master    ---切到master分支

```
```
git pull  ---更新一下 master 分支

```
```
git pull https://gitee.com/openharmony/arkui_ace_engine.git ---把网页上的master 分支拷贝下来

```
```
git checkout progress_add_tdd

```
```
git rebase master

```
```
code .

```
把build.gn文件更改一下，或者拷贝分支上的build.gn 然后拷贝到本地代码，执行一下初始化操作：
在ohos下执行：

```
cat foundation/arkui/ace_engine/test/unittest/core/pattern/progress/BUILD.gn | prebuilts/build-tools/linux-x86/bin/gn format --stdin > FORMAT_RESULT.gn;cp -f FORMAT_RESULT.gn foundation/arkui/ace_engine/test/unittest/core/pattern/progress/BUILD.gn;rm FORMAT_RESULT.gn

```
执行完把初始化后的build.gn内容拷贝到分支代码的BUILD.gn：解冲突
![[Pasted image 20240522101322.png]]
https://gitee.com/openharmony/arkui_ace_engine.git 克隆来源如图所示：

![[Pasted image 20240522095748.png]]

![[Pasted image 20240522095808.png]]

2.更改完build.gn 继续执行命令：
```
git status   ----查看是否新增代码 文件路径

```
```
git diff    ----查看差异 看是否有空格

```
```
git rebase --continue

```

```
git log    ---这个时候正常是可以看到我建的commit 

```
```
git commit --amend --signoff

```
```
git push origin progress_add_tdd -f  ---重提代码

```

然后回到PR，重新start build