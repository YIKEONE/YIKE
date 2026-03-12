# 闲隙碎笔


## *Linux*

1. Linux查看进程指令，ps -aux第二列是什么，和ps -elf区别。

~~~bash
ps -aux	# 更适合普通用户查看进程的基本信息，比如 CPU 和内存占用。
ps -elf	# 提供了更底层的细节，适合系统管理员进行深入分析
~~~

### ubuntu 给apt配置代理

~~~bash
sudo nano /etc/apt/apt.conf.d/95proxy

# 修改具体的ip和端口
nslookup proxy.neusoft.com # 查询对应ip

Acquire::http::Proxy "http://192.168.2.78:8080";
Acquire::https::Proxy "http://192.168.2.78:8080";
~~~



### github通过https协议推送

~~~bash
git config user.name "YIKEONE"

# settings -> developer settings -> Persion access tokens -> 勾选repo
git remote set-url origin https://YIKEONE:{换成对应token}@github.com/YIKEONE/YIKE.git
~~~



### 生成ssh秘钥对

~~~bash
ssh-keygen -t ed25519

cat ~/.ssh/id_ed25519.pub
~~~



### 增加bash显示分支

~~~bash
if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[33m\]$(__git_ps1 " (%s)")\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w$(__git_ps1 " (%s)")\$ '
fi
~~~



## *Vim*

### vim基本指令

```cpp
// 移动光标
h	左移，j	下移，k	上移，l	右移

// 删除光标的字符
x

// 替换字符
r	替换当前光标的字符
R	替换多个字符

// 撤销
ctrl r， 或者u

// 复制
yy
    
// 粘贴
p
```

### vim插入

```
i	光标前键入插入模式
I	行头进入插入模式
a	光标后键入插入模式
A	行尾进入插入模式
o	本行后添加一行，并进入插入模式
O	本行前添加一行，并进入插入模式
```

### vim搜索

```c++
:set hls	// 搜索高亮
:set is		// 搜索部分匹配
:set ic		// 搜索忽略大小写

/test 是从前后往后搜索test, ?test 是从后往前搜索test
/test\C /b \C是不忽略大小写，\b是全字匹配

*# 表示搜索光标所在单词

:%s/test/demo 文本中的所有test换成demo

q/ 表示搜索记录
```

### vim删除

~~~shell
# 所有的d换成c，就是删除后进入插入模式
dw	删除单词
d$	删除光标到末尾
dd	是删除整行
3dd	删除三行，类似ctrl x，会到放到寄存器中，p可以粘贴
:%d	删除所有

# 删除块级别
di+对应的符号	删除[],(),{},'',""中的元素
例如, [test] 
di[ -> []
若是想连""也一起删除,就是da
~~~

###  vim跳转

~~~
f + 字符	跳转光标后的第一个该字符的位置
^		行首
$		行首
0		行头
e/w		后移一个单词
b		前移一个单词
gg		移动到文件第一行
G		移动到文件最后一行
gg486	移动到486行，ctrl g是显示行号
%		匹配对应(),[]
*		跳转光标对应字符的下一个位置
#		跳转光标对应字符的上一个位置
~~~

### Vim执行外部命令

```shell
# Vim执行外部命令
:!ls	执行ls的命令
:!rm	执行rm的命令
```

### Vim文件相关操作

~~~shell
# 把文本中一些字段保存到另一文件中
v/V		进入可视模式
移动光标选择需要保存的字段
w TEST	保存为TEST文件

# 在文件中，插入别的文件的内容
:r TEST		可以搭配上面那个用
~~~

## *Git*

~~~bash
# 和对应仓添加关联
git remote add <upstream> <url> # upstream 可以取任意名字, url为对应仓的git地址
git remote rm <upstream>

# 提交代码
git add .
git commit -m "first commit"
git commit --amend
git push origin <branchName> -f

# git rm 删除文件
git rm test/\*.log 			# 删除test/目录下，所有的.log文件
git rm --cached test.txt 	# 删除暂存区中的文件

# git移动文件
git mv <file_form> <file_to>

# git stash
# 暂存，例如在分支a修改了代码，但是实际要提到b分支
git stash
git stash list
git stash pop
git stash pop <@编号>
git stash apply
git stash drop

# 查看某一笔提交的差异
git show <hash> --stat		# 看对应hash提交中有哪些文件修改
git show <HEAD> --shortstat	# 看git log最近一笔的修改的代码行数

# 显示远程仓和本地仓之间的差异
git log <master>..<origin/master>
git diff <branch1>..<branch2>	# 查看两个分支的代码差异
git diff <branch1>...<branch2>	# 比较从共同祖先到branch2的差异

# 查看历史操作记录, 配合reset达成代码回退
git reflog
git reset --hard <hash>


# 新提交一笔pr
git checkout <puec_0701> -b <puec_test>
# HEAD为git log的最新一笔提交, HEAD~1表示最新一笔的前一笔提交, --soft会把HEAD与HEAD~1之间的差异放到暂存, --hard则会直接删除
git reset --soft <HEAD~1>
git commit -s
git push origin <puec_test>

~~~



### push

~~~bash
# 给别人提交代码
git remote add <urlName> <url>
git fetch urlName
git add .
git commit
git push origin curBranch:targetBranch
~~~



### cherry-pick

~~~bash
# 快速提交
git fetch origin kexin # 获取到需要cherry-pick的commit
git cherry-pick <hash>
git cherry-pick --continue	# 继续
git cherry-pick --abort 	# 取消本次cherry-pic
~~~



### rebase

~~~bash
# 多合一
# 在 ABCDE中提交其中的一笔pr
git rebase -i B的commitId^
把pick 修改为 drop # 多合一 咋把pick修改为 s
~~~

~~~bash
# 变基or解冲突
git fetch <upstream> <master>
git rebase <upstream/master>
git rebase --continue
~~~



### submodule

~~~bash
# 创建子仓
git init 
# 使用github等平台，创建仓库url
git submodule add url path

git add .gitmodules 子仓/
git push...

# 主仓存子仓的快照，当子仓push后，主仓也要push
~~~

