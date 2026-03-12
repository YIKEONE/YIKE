![[Pasted image 20240514170818.png]]
首先把vscode 全部关掉，然后重新启动wsl

启动成功后，打开里一个linux，进入代码目录下，执行code   .
![[Pasted image 20240514170932.png]]

解决拉取代码报错问题：从开一个终端，执行如下：

![[img_v3_02at_f9c32af9-704e-46fa-bc9c-6743d12309dg.jpg]]

![[Pasted image 20240515094615.png]]

弄好后重新拉取代码：在根目录下执行
repo sync -c
repo forall -c 'git lfs pull'
bash build/prebuilts_download.sh
![[Pasted image 20240515094739.png]]


频繁出现这个问题是因为**内存不够了**：
解决方案就是把内存改小一点：修改一下里面的值如图所示，然后在shutdown一下
![[Pasted image 20240516091848.png]]
![[Pasted image 20240516091824.png]]