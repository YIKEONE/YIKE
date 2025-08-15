

问题一：如何查看指定日期的GIT提交？
#查看指定日期git提交记录
```
 git log --since="2023-03-07" --until="2023-03-08"
```




问题二：如何将某个分支的提交应用到另一个分支？

分支提交切换 方式一：
#切换到你想要应用提交的分支
```
git checkout main 
```
#应用来自feature-branch分支的单个提交 
```
git cherry-pick 1234abcd
```
#或者应用一系列的提交 
```
git cherry-pick 1234abcd..5678efgh
```
#中途出现冲突需要手动接触冲突然后执行
```
git add  
```
#进行标记已解决的文件然后执行
```
git cherry-pick --continue
```


分支提交切换 方式二：

#首先保证你在正确的分支上工作使用命令来查看分支
```
git branch
```

#切换分支使用命令
```
 git checkout <your-branch>
```
#执行命令将当前分支的提交应用到另一个分支base-branch
```
git rebase <base-branch>
```
#确保rebase成功后，将更改合并回base-branch分支
```
git checkout <base-branch>
```

```
git merge <your-branch>
```

问题三：如何修改我的feature分支上的某个提交历史

#切换到feature分支 
```
git checkout feature 
```
#开始交互式rebase
```
git rebase -i <commit-hash> 
```
#弹出的编辑器中，修改你想要更改的提交前的命令（如 pick 改为 edit）
#保存并关闭编辑器，Git将停止在第一个需要修改的提交处 # 进行必要的修改后，执行
```
git commit --amend
```
#来更新提交 
#继续rebase过程
```
git rebase --continue
```

问题四：如何撤销一次rebase操作?
#查看rebase之前的状态 
```
git reflog 
```
#找到你要回退到的提交哈希值 
#回退到那个提交 
```
git reset --hard <commit-hash>
```

问题五：拉取代码git fetch 和git pull的区别

`git fetch`命令会从远程仓库获取最新的历史记录，但不会改变你本地的工作副本。具体来说，`git fetch`执行以下操作：

- 从远程仓库获取所有分支的最新历史记录。
- 将这些历史记录存储在你的本地仓库中，但不自动合并到你的当前分支。
- 不会改变你的工作目录中的文件。

这意味着，使用``` git fetch ```后，你可以检查远程仓库的最新更改，而不会影响你当前的工作。

`git pull`命令组合操作，它相当于执行了`git fetch`和`git merge`。具体来说，`git pull`执行以下操作：
- 从远程仓库获取最新的历史记录（相当于`git fetch`）。
- 将远程仓库的最新更改自动合并到你的当前分支（相当于`git merge`）。
- 如果远程仓库的更改与你本地的工作副本不冲突，那么`git pull`将会顺利地合并这些更改。
- 如果有冲突，你需要手动解决这些冲突，然后完成合并。

在处理远程仓库的更新时，如果你想要先查看远程更改而不立即合并它们，应该使用`git fetch`。如果你想要立即将远程更改合并到本地分支，应该使用`git pull`。

问题四 ：如何利用diff转换代码

#1、将diff文件放在git同级目录下

#2、应用diff文件
```
git apply 38877.diff --reject
```  

#3、多笔提交提成一笔(比如前6笔提交合成一笔)
```
git rebase -i 0bde81db5e(第七笔提交哈希值)
```
