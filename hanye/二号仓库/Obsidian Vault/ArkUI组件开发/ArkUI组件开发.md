一·UI组件的树形结构说明

1.UI组件的属性结构包括：

```
1)前端UI描述结构
2）FrameNode节点树
3）后端渲染树
```
![[Pasted image 20240619100026.png]]

2.后端基于前端UI描述结构创建相应的UINode节点树：

```
UINode节点树包括：
1）自定义组件节点==CustomNod==e
2）语法节点SyntaxNode类似==LazyForEach==
3）控件节点==FrameNode==
```

3==.FrameNode节点树==：主要==处理UI组件属性更新，布局测算，事件处理等业务逻辑==
4==.CustomNode==作为FrameNode的子类，用于==处理自定义组件相关业务逻辑，比如执行build函数；==
5.==RenderNode==渲染节点树用于渲染展示。

二·上下文结构

1.JS层：==将前端的UI描述对接到后端C++函数调用 .==
路径如下:

```
foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/jsview目录下
```

2.View层：==C++组件对外提供的接口类，包括组件的创建、属性设置、事件设置等==.
路径如下:

```
foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/组件名/的目录下
```

3.FrameNode层：C++组件类

```
1)==GeometryNode：存储大小位置信息==；
2)==PaintProperty==：内容区绘制类属性集合==,不同组件可以创建子类，保存相关渲染属性，比如进度条的滑轨颜色
3)==LayoutProperty:==布局类属性集合,不同组件可以创建子类，保存相关==布局属性==，比如Flex容器的Flex属性
4)==Pattern==:组件模板类，不同组件会对应不同的Pattern模板类，==用于提供不同组件差异化RenderProperty、LayoutProperty、布局算法、绘制方法的能力；==
5)==RenderContext==：绘制上下文，对接不同后端，==提供统一的canvas接口、渲染属性（转换矩阵、背景色等）接口。==
6)==AnimationOption==：==动画配置==相关属性集合，==设置给后端RenderContext进行动画配置==。
7)Inspector：无障碍，预览能力等；
8)EventHub:事件管理
```

1)==GeometryNode：存储大小位置信息==；
2)==PaintProperty==：==内容区绘制类属性集合==，不同组件可以创建子类，保存相关渲染属性，比如进度条的滑轨颜色
3)==LayoutProperty:==布局类属性集合,不同组件可以创建子类，保存相关==布局属性==，比如Flex容器的Flex属性
4)==Pattern==:组件模板类，不同组件会对应不同的Pattern模板类，==用于提供不同组件差异化RenderProperty、LayoutProperty、布局算法、绘制方法的能力；==
5)==RenderContext==：绘制上下文，对接不同后端，==提供统一的canvas接口、渲染属性（转换矩阵、背景色等）接口。==
6)==AnimationOption==：==动画配置==相关属性集合，==设置给后端RenderContext进行动画配置==。
7)Inspector：无障碍，预览能力等；
8)EventHub:事件管理
![[Pasted image 20240619110334.png]]

4.LayoutWrapper层：工具类，承载布局任务， 在组件需要布局时，会生成相应的LayoutWrapper对象

```
输入为LayoutProperty、LayoutAlgorithm，
输出为GeometryNode,
路径在foundation/arkui/ace_engine/frameworks/core/components_ng/layout目录下
```

```
- LayoutWrapper布局包装器设计目的主要有以下几点考虑：
    - 1.布局过程中不可避免的会出现变量需要在不同阶段不同函数内调用，从而需要将该变量按照成员变量保存，而布局任务作为瞬时任务按需触发，不应该将布局过程中产生的变量保存在FrameNode，而LayoutWrapper作为临时对象，也是在布局时创建，过程中的变量保存在该临时变量中，不影响FrameNode；
    - 2.LayoutWrapper在创建时会拷贝FrameNode中布局任务相关的布局属性以及布局算法，在布局过程中不再依赖FrameNode，可以实现布局任务的独立运行，为后续布局任务的并行并发提供基础。
    - 3.FrameNode不再具体处理布局任务，实现属性更新和布局过程的解耦，方便代码维护以及TDD用例设计执行。
```

5.RenderWrapper层：工具类，承载绘制任务，在组件需要重新布局时，会生成相应RenderWrapper对象

```
输入为PaintProperty，绘制任务实现,RenderContext绘制上下文，
输出为Canvas的绘制指令。
路径在foundation/arkui/ace_engine/frameworks/core/components_ng/render目录下；
```

```
- RenderWrapper绘制包装器的设计目的同LayoutWrapper，主要用于和FrameNode解耦，提供并行并发任务基础。
```

6.EventHub：事件管理类，提供事件回调设置统一入口，针对设置的事件回调类型，创建不同的事件管理器进行事件处理，比如手势事件创建GestureEventHub，KeyEventHub焦点按键事件管理进行统一处理。

```
目录为foundation/arkui/ace_engine/frameworks/core/components_ng/event
```

7.Adapterhi后端渲染抽象层，主要用于获取抽象的Canvas绘制接口，创建后端渲染节点树，执行显式隐式动画等；

三，组件树创建：

```
1.页面启动：初始化应用UI根节点，使用StagePattern，实现页面切换。
2.初始化完成，框架会加载页面文件，创建页面根节点CustomNode。
3.页面根节点会挂载到页面包装节点，页面包装节点会挂载到根节点下。
```

![[Pasted image 20240619150707.png]]

四，组件Diff和脏区任务

```
1)页面创建
2）UINode节点会生成唯一标识id
3）页面变化，前端框架会标记持有该状态变量的自定义组件为更新脏区，保存在渲染管线对象中，并请求下一个Vsync信号
4）下一个信号来时，渲染管线会调用该脏区节点进行更新
5）更新时会通过前端框架识别build函数内部子节点的更新条件，重新执行发生改变的子节点的UI描述方法。更新新的UI属性和条件变量
6）更新后会比对旧的UI属性和条件变量
①针对产生差异的UI组件标记布局脏区
②会针对if语法节点，动态删除其子节点，实现if语法更新
7）标记为脏区的子节点的父节点也标记为布局脏区
8）布局脏区节点存储在渲染管线，由渲染管线在刷新布局阶段执行这些脏区节点的重新布局
9）完成布局后，更新组件相应的大小位置等信息，生成渲染脏区节点
10）渲染脏区节点同样保存在渲染管线中，由渲染管线在属性绘制阶段执行这些脏区节点的重新绘制。
```

五.结合代码LayoutWrapper

①怎么在刷新时候把脏区节点dirty回传，在FrameNode文件中进行如下操作:
==取出dirty往本身Geometry赋值==

```
1.FrameNode::SwapDirtyLayoutWrapperOnMainThread  
这个函数的作用是将一个`LayoutWrapper`对象与当前`FrameNode`的`LayoutWrapper`对象进行交换，同时更新布局属性、位置属性等，并确保`FrameNode`的渲染状态保持正确。

---auto needRerender = pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
2.SearchPattern::OnDirtyLayoutWrapperSwap 所有更新布局属性都是在这个函数里做：
这个函数的作用是处理一个名为`dirty`的`LayoutWrapper`对象，并更新一些变量，以便在后续的布局过程中使用。把所有的位置和大小全部取出
```


②怎么测量？
答：都在Algorithm里做，怎么测量大小位置  eg：SearchLayoutAlgorithm

==子类重写就是适应新组件，不重写就会调默认的BoxLayoutAlgorithm类==

```
①void BoxLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
`Measure`函数使用了递归。

1）首先，它创建一个子约束`layoutConstraint`，这个约束将用于限制子元素的尺寸。
    
2）然后，它遍历布局包装器`layoutWrapper`的所有子元素（通过`GetAllChildrenWithBuild()`方法获取），并对每个子元素调用`Measure()`函数。这个调用是一个递归的过程，因为`Measure()`函数也调用了`Measure`函数。
    
3）接下来，它调用`PerformMeasureSelf()`函数，这个函数可能是用于计算布局包装器自己的尺寸。
==总结==：`Measure`函数使用了递归来对布局包装器及其所有子元素进行测量，从而实现了布局算法
```


```
②void BoxLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
`Layout`函数确实使用了递归来对布局包装器`layoutWrapper`的所有子元素进行布局。

1）首先，它调用了一个名为`PerformLayout`的函数，这个函数可能是用于实现布局算法的具体逻辑。这个函数的调用是一个递归的过程，因为`PerformLayout`函数自身也调用了`Layout`函数。
    
2）然后，它遍历布局包装器`layoutWrapper`的所有子元素（通过`GetAllChildrenWithBuild()`方法获取），并对每个子元素调用`Layout()`函数。这个调用也是一个递归的过程，因为`Layout`函数也调用了`PerformLayout`函数。
==总结==：`Layout`函数使用了递归来对布局包装器及其所有子元素进行布局，从而实现了布局算法.
```

```
③std::optional<SizeF> BoxLayoutAlgorithm::MeasureContent(
const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)

代码中的`MeasureContent`函数没有直接使用递归，但是它使用了`do-while`循环，这个循环的执行条件是`false`，这意味着它将无限循环，直到找到一个有效的更新方法。然而，这个循环并不是真正的递归，而是通过循环来模拟递归的过程。

在循环中，`contentSize`的值被多次更新，每次更新都可能调用`UpdateSizeWithCheck`、`UpdateIllegalSizeWithCheck`等函数。（这两函数都是通过使用条件判断和赋值操作来模拟递归）这些函数的实现可能涉及到递归调用，但是由于循环的执行条件是`false`，因此这些递归调用不会真正执行，而是被循环replace。

==总结==：`MeasureContent`函数没有直接使用递归，但是它通过循环模拟了递归的过程，从而实现了布局算法。
```

子类重写这三个函数：
```
virtual std::optional<SizeF> MeasureContent(const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)

contentConstraint布局约束 layoutWrapper 布局包装器
```

```
virtual void Measure(LayoutWrapper* layoutWrapper)

```

```
virtual void Layout(LayoutWrapper* layoutWrapper)
```
```
```

```
==背景色：RenderContext 前景色：PaintProrerty 位置：Algorithm 图片有问题：paintmethod==

GeometryNode:node大小和frame信息，位置大小。

==时序图：线上的函数是后面的成员函数。==