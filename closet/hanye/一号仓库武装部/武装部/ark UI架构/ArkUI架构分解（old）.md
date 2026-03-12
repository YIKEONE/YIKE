## 框架图
### 1、参考文档
     https://gitee.com/yan-shuifeng/arkui_docs/blob/master/design/NewStructureDesign/ng-overview-ArkUI%E7%BB%84%E4%BB%B6%E6%96%B0%E6%9E%B6%E6%9E%84%E4%BB%8B%E7%BB%8D.md
###   2、上下文结构 / Context structure

![[Pasted image 20240510133437.png]]
- JSView：引擎对接层，提供js引擎数据解析能力，将前端的UI描述对接到后端C++函数调用；（在代码中主要命名为JSXXX（如JSStack），路径在foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/jsview目录下）
    
- View：C++组件对外提供的接口类，包括组件的创建、属性设置、事件设置等；（在代码中主要命名为XXXView（如StackView），路径在foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/组件名/的目录下）
    
- FrameNode：C++组件类（路径在foundation/arkui/ace_engine/frameworks/core/components_ng/base目录下），内部包括：
    
    - GeometryNode：存储大小位置信息；
    - PaintProperty：内容区绘制类属性集合，不同组件可以创建子类，保存相关渲染属性，比如进度条的滑轨颜色；
    - LayoutProperty：布局类属性集合，不同组件可以创建子类，保存相关布局属性，比如Flex容器的Flex属性；
    - Pattern：组件模板类，不同组件会对应不同的Pattern模板类，用于提供不同组件差异化RenderProperty、LayoutProperty、布局算法、绘制方法的能力；
    - RenderContext：绘制上下文，对接不同后端，提供统一的canvas接口、渲染属性（转换矩阵、背景色等）接口。
    - AnimationOption：动画配置相关属性集合，设置给后端RenderContext进行动画配置。
    - Inspector：调测相关能力，如获取组件大小位置信息，获取组件属性信息等；
- LayoutWrapper：工具类，承载布局任务，在组件需要重新布局时，会生成相应的LayoutWrapper对象，LayoutWrapper对象输入为LayoutProperty、LayoutAlgorithm，输出为GeometryNode。（路径在foundation/arkui/ace_engine/frameworks/core/components_ng/layout目录下）
    
    - LayoutWrapper布局包装器设计目的主要有以下几点考虑：
        - 布局过程中不可避免的会出现变量需要在不同阶段不同函数内调用，从而需要将该变量按照成员变量保存，而布局任务作为瞬时任务按需触发，不应该将布局过程中产生的变量保存在FrameNode，而LayoutWrapper作为临时对象，也是在布局时创建，过程中的变量保存在该临时变量中，不影响FrameNode；
        - LayoutWrapper在创建时会拷贝FrameNode中布局任务相关的布局属性以及布局算法，在布局过程中不再依赖FrameNode，可以实现布局任务的独立运行，为后续布局任务的并行并发提供基础。
        - FrameNode不再具体处理布局任务，实现属性更新和布局过程的解耦，方便代码维护以及TDD用例设计执行。
- RenderWrapper：工具类，承载绘制任务，在组件需要重新布局时，会生成相应的RenderWrapper对象，RenderWrapper对象输入为PaintProperty、绘制任务实现，RenderContext绘制上下文，输出为Canvas的绘制指令。（路径在foundation/arkui/ace_engine/frameworks/core/components_ng/render目录下）；
    
    - RenderWrapper绘制包装器的设计目的同LayoutWrapper，主要用于和FrameNode解耦，提供并行并发任务基础。
- EventHub：事件管理类，提供事件回调设置统一入口，针对设置的事件回调类型，创建不同的事件管理器进行事件处理，比如手势事件创建GestureEventHub进行统一处理。（foundation/arkui/ace_engine/frameworks/core/components_ng/event目录下）
    
- Adapter：后端渲染抽象层，主要用于获取抽象的Canvas绘制接口，创建后端渲染节点树，执行显式隐式动画等；
### 3、组件树的构建
![[Pasted image 20240510133735.png]]
- 当应用启动时，ArkUI框架会初始化应用UI根节点，应用UI根节点使用StagePattern用于实现页面切换等特殊操作；
- 初始化完成后，ArkUI框架会开始加载页面文件，在加载页面文件时会创建页面根节点CustomNode（@Entry标识的自定义组件）；
- 页面根节点组件会在路由管理类中挂载到页面包装节点上（PagePattern）；页面包装节点会挂载到根节点下；
- 页面根节点在布局测试过程中，会调用内部的build方法，生成子树结构挂载到页面根节点下。
### 4、组件diff 和脏区任务

![[Pasted image 20240510133955.png]]
- 页面在首次创建时，会给每个UINode节点生成唯一的标识id；
- 当页面状态变量发生变化时，前端框架会标记持有该状态变量的自定义组件为更新脏区，并保存在渲染管线对象中，并请求下一个vsync信号；
- 当下一个vsync信号到来时，渲染管线会调用该脏区节点进行更新任务执行；
- 自定义组件在执行更新任务会，会通过前端框架识别build函数内部子节点的更新条件，重新执行依赖状态变量（发生改变）的子节点的UI描述方法，更新新的UI属性和条件变量；
- 当UI更新设置新的UI属性和条件变量时，会与老的UI属性和条件变量进行对比，针对产生差异的UI组件标记为布局脏区；此外，针对if语法节点，会基于当前的条件值，动态删除其子节点，实现if语法的更新；
- 由于布局任务大部分场景依赖父子关系，标记为布局脏区的子节点通常情况下会标记父节点为布局脏区；
- 上述布局脏区节点会保存到渲染管线中，由渲染管线在刷新布局阶段执行这些脏区节点的重新布局；
- 布局脏区节点完成布局后，会更新组件相应的大小位置等信息并生成渲染脏区节点；
- 渲染脏区节点同样会保存在渲染管线中，由渲染管线在属性绘制阶段执行这些脏区节点的重新绘制。
### 5、渲染管线
![[Pasted image 20240510134132.png]]
- 当渲染管线内加入脏区节点时，会请求下一帧vsync；
    
- FlushAnimation：当下一帧vsync过来后，会首先执行动画，动画处理过程中会生成额外的DirtyNode保存在渲染管线中；
    
- FlushDirtyNodeUpdate：处理更新脏区节点，此时会刷新待更新的UI节点属性和参数，并生成额外的DirtyNode保存在渲染管线中；
    
- FlushTouchEvents：集中处理手势事件，在该阶段可能会修改UI节点的属性并标记布局或者渲染脏区（比如列表滑动）；
    
- FlushLayoutTask：集中处理布局脏区节点，生成并执行布局任务；
    
- FlushRenderTask：集中处理渲染脏区节点，生成并执行渲染任务；
    
- FlushMessage：驱动后端进行渲染刷新


### 6、关键类和数据结构说明
   
   ####  1、Framenode结构说明
     ![[Pasted image 20240510134542.png]]
     - 成员变量说明：
    
    - children_：子节点信息，可能为语法节点（SyntaxNode）（如if，foreach）和组件节点（FrameNode）；
    - parent_：父节点信息，可能为语法节点（SyntaxNode）（如if，foreach）和组件节点（FrameNode）；
    - context_：渲染管线对象；
    - geometryNode_：组件大小位置信息；
    - layoutProperty_：布局属性集合信息，比如长宽信息；
    - paintProperty_：内容区绘制属性集合信息，比如进度条轨道颜色；
    - renderContext_：后端绘制上下文，比如设置背景色，获取Canvas等；
    - eventHub_：事件回调集合，保存事件信息，比如点击，进度条变更通知等；
    - pattern_：组件模板类，提供不同类型组件对应的LayoutProperty子类，PaintProperty子类，EventHub子类，布局方法和绘制方法等；
#### 2、Pattern 及其相关类结构说明
![[Pasted image 20240510134844.png]]

- `virtual bool IsAtomicNode() const`

当前组件是否为原子节点，原子节点的组件不包含子节点，比如Image，基类默认值为true。如果是容器组件，Pattern子类必须重写上述方法返回false。

Whether the current component is an atomic node, the component of the atomic node does not contain child nodes, such as Image, the default value of the base class is true. If it is a container component, the Pattern subclass must rewrite the above method to return false.

- `virtual RefPtr<LayoutProperty> CreateLayoutProperty()`
    
    创建组件布局的布局属性集合（子类LayoutProperty），比如Row和Column的CrossAxisAlign属性。布局属性设计开发时必须遵循下列要求：
    
    - 同类别的属性需要统一到struct结构体中，使用`ACE_DEFINE_PROPERTY_GROUP_ITEM`宏（第一个参数为属性名称，第二个参数为属性类型）定义相应的数据，可以参考foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/linear_layout/linear_layout_styles.h。
    - LayoutProperty子类使用`ACE_DEFINE_PROPERTY_GROUP`宏（第一个参数为属性组名称，第二个参数为属性组类型）将上述的struct结构体声明为自己的成员变量，可以参考foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/linear_layout/linear_layout_property.h。
    - 属性值的设置接口需要通过LayoutProperty子类暴露给前端（XXXView层），属性设置接口在完成上述两个步骤后，使用`ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP`宏（第一个参数为属性组名称，第二个参数为当前需要设置的属性值名称，第三个参数为当前属性值的类型，第四个参数为当属性值发生变化时需要标记的脏区类型（PROPERTY_UPDATE_MEASURE：改变自身大小尺寸，PROPERTY_UPDATE_LAYOUT：改变子节点在自身内部区域的放置方式）），可以参考foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/linear_layout/linear_layout_property.h。
    - 如果该属性值非常独立，不需要相应的属性组，则在LayoutProperty子类中使用`ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP`宏（第一次参数为属性名称，第二个参数为属性类型，第三个参数为属性变化时需要标记的脏区类型），可以参考foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/list/list_layout_property.h。
    - 完成上述步骤后，属性值在前端（XXXView层）层可以通过`ACE_UPDATE_LAYOUT_PROPERTY`宏（第一个参数为子类LayoutProperty类型，第二个参数为属性名称，第三个参数为设置的属性值），可以参考foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/list/list_view.cpp或者foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/linear_layout/column_view.cpp。
    - - `virtual RefPtr<PaintProperty> CreatePaintProperty()`
    
    创建组件绘制的绘制属性集合（子类PaintProperty），比如进度条的滑块颜色属性。绘制属性设计开发时同样遵循布局属性的要求，使用相同的宏（前端（XXXView层）层可以通过`ACE_UPDATE_PAINT_PROPERTY`宏）简化开发。
    
-   virtual RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm()`
    
    创建组件大小测算和布局的算法。该方法会在框架创建对应的布局包装器进行布局前调用，组件需要在该函数中返回自身大小测算和布局的算法。返回的布局算法后，框架会额外使用`LayoutAlgorithmWrapper`对象封装一层，`LayoutAlgorithmWrapper`对象主要基于组件更新场景的脏区类型设置`skipMeasure`和`skipLayout`来略过特定布局，比如脏区类型只是重新布局子节点位置而不涉及大小变化，则`skipMeasure`会被设置为true，在LayoutWrapper在布局过程中会忽略测算阶段，具体布局基类参考LayoutAlgorithm类说明。
    
     virtual RefPtr<PaintProperty> CreatePaintProperty()`
     创建组件绘制的绘制属性集合（子类PaintProperty），比如进度条的滑块颜色属性。绘制属性设计开发时同样遵循布局属性的要求，使用相同的宏（前端（XXXView层）层可以通过`ACE_UPDATE_PAINT_PROPERTY`宏）简化开发。

     `virtual RefPtr<NodePaintMethod> CreateNodePaintMethod()`

创建组件内容的绘制方法。该方法会在框架创建对应的绘制包装器进行内容绘制前调用，组件需要在该函数中返回自身内容绘制的方法实现，具体可以参考foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/text/text_paint_method.h，foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/image/image_paint_method.h。具体查看NodePaintMethod基类说明

`virtual RefPtr<EventHub> CreateEventHub()`

创建组件事件集合。该方法会在前端设置事件时调用，UI组件的事件归类到EventHub的子类中，当后端触发事件场景时，调用EventHub子类触发前端事件。

`virtual bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)`

当布局完成后，框架会调用FrameNode的SwapDirtyLayoutWrapperOnMainThread方法，在该方法中会调用上述pattern方法来告诉框架是否需要启动内容区的绘制流程。第一个参数为布局完成后的包装器，可以通过该参数获取布局完成后的组件大小，内容区大小等信息，同时LayoutWrapper类中还提供了`SkipMeasureContent`方法会来获取当次布局内容区的大小是否不变。第二个参数则是说明当次布局计算是否略过了大小测算，第三个参数说明当次布局计算是否略过了内容区和子节点的布局。一般情况下如果布局内容区不变或者布局计算忽略了大小测算，可以认为内容不变，不需要重新绘制，返回false即可。由于父子节点绘制独立，从而容器组件一般也返回false（不涉及容器组件本身内容，例外情况比如列表的分割线场景需要返回true）。

`RefPtr<FrameNode> GetHost() const`

获取宿主FrameNode对象。

`virtual void ()`和`virtual void OnActive()`

在布局完成后，有可能组件的可见性发生了变化，如果组件从可见变为不可见区域时，会回调OnInActive事件，反之会回调OnActive事件。

`virtual void OnModifyDone()`

通过前端(XXXView)执行完完当前UI组件的属性方法时会回调该函数，在该函数中，可以获取组件最新的属性设置值。

#### 3、LayoutAlgorithm类

`virtual std::optional<SizeF> MeasureContent(const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)`

组件涉及内容区大小测算时，子类LayoutAlgorithm需要重写上述方法，返回内容区大小，比如文本大小。contentConstraint限制为内容区大小限制（去掉了Padding，Margin）。具体可以参考foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/text/text_layout_algorithm.h。

`virtual void Measure(LayoutWrapper* layoutWrapper)`

测算组件自身大小和子组件大小（容器组件）。组件自身大小逻辑：

- 如果显式设置了width和height属性，则组件自身大小为width和height属性设置的大小；（flex容器能在上述大小基础上进行额外的拉伸或者压缩）
- 如果未显示设置width和height属性，则组件自身大小为内容区大小（非容器组件）加上Padding内边距值，针对容器组件，则按照容器组件具体的布局规范来，比如Row和Column组件，自身大小为子组件大小总和加上Padding内边距值。

大部分非容器组件，可以直接继承**BoxLayoutAlgorithm**类，自身大小测算逻辑已经在BoxLayoutAlgorithm类中实现。

`virtual void Layout(LayoutWrapper* layoutWrapper)`

设置组件内容（比如文本）或者子组件的布局位置。组件内容的位置定位逻辑：

- 当组件内容大小小于组件本身大小时，会生效align属性，通过align属性设置组件内容在组件区域的对齐方式（比如左上，居中对齐等）。

大部分非容器组件，可以直接继承**BoxLayoutAlgorithm**类，内容区对齐方式已经在BoxLayoutAlgorithm类中实现，容器类组件按照各容器自身的布局规范对子节点进行布局。

####  4、NodePaintMethod类

- UI组件的绘制层级从下到上为：
    
    - 背景层：绘制背景色，背景图等，该层由后端渲染节点完成，UI组件在NodePaintMethod类中不需要额外处理；
        
    - 内容层：UI组件内容区绘制，比如进度条等；
        
    - 前景层：前景颜色，边框属性；
        
    - 遮罩层：比如调测的边框绘制，同时父容器在该层的绘制内容会遮盖子组件的绘制内容。

      - `virtual CanvasDrawFunction GetContentPaintImpl(PaintWrapper* paintWrapper)`
    
    创建内容区绘制方法。 Create a content area drawing method.
    
     - `virtual CanvasDrawFunction GetForegroundPaintImpl(PaintWrapper* paintWrapper)`
    
    创建前景层绘制方法。 Create a foreground layer drawing method.
    
     - `virtual CanvasDrawFunction GetOverlayPaintImpl(PaintWrapper* paintWrapper)`
    
    创建overLay层绘制方法。 Create an overLay layer drawing method.








文件说明：

在OpenHarmony（开源鸿蒙操作系统）中，这些文件和目录是项目结构的一部分，各自承担着不同的功能和作用，彼此之间构成了整个操作系统的开发、编译和运行框架。 以下是对每个提到的文件和目录的简要说明及其在OpenHarmony中的作用：
1. **applications**: 这个目录包含了OpenHarmony的各种应用程序，包括系统应用程序和第三方应用程序。 

2. **build**: 这是一个脚本和配置文件目录，包含了构建OpenHarmony系统所需的脚本和配置，例如`build.py`是一个重要的构建脚本。

3. **commonlibrary**: 包含OpenHarmony共享库的代码，这些库通常被系统中的应用程序和组件所使用。

4. **device**: 包含与设备硬件相关的代码，如驱动程序、硬件抽象层（HAL）等。 

5. **drivers**: 这个目录包含了各种设备驱动程序，它们使得操作系统可以与硬件设备进行通信。 

6. **interface**: 定义了系统提供的各种接口，包括API和系统服务接口。

7. **out**: 构建输出目录，所有编译后的文件都会放到这里。

8. **qemu-run**: 可能包含用于在QEMU模拟器上运行OpenHarmony的脚本和配置文件。

9. **vendor**: 这个目录包含了来自不同硬件制造商的硬件适配代码。

10. **arkcompiler**: 阿克编译器相关代码和配置，用于将应用程序代码编译为可以在OpenHarmony上运行的格式。 

11. **build.py**: 这是一个Python脚本，它是启动OpenHarmony构建过程的入口点。

12. **data**: 包含系统初始数据文件，如系统设置、默认应用程序数据等。

13. **docs**: 文档目录，包含了OpenHarmony的开发者文档、用户指南等。

14. **foundation**: 包含OpenHarmony的基础组件，如系统框架、核心库和基础服务。

15. **kernel**: 操作系统的核心部分，通常包括调度器、内存管理、设备管理等。

16. **prebuilts**: 包含预编译的工具和库，这些工具和库通常不参与编译过程。

17. **test**: 包含测试代码和测试用例，用于验证系统的稳定性和性能。 

18. **build.sh**: 可能是Linux下的shell脚本，用于编译OpenHarmony。

19. **developtools**: 开发工具目录，包含了开发OpenHarmony所需的工具链。

20. **domains**: 可能包含不同应用领域的特定代码，如通信、多媒体等。

21. **ide**: 集成开发环境配置和插件，可能用于OpenHarmony应用程序的开发。 

22. **napi_generator**: 可能是用于生成Native API的代码生成工具。 

23. **productdefine**: 包含产品定义的配置文件，定义了不同产品的硬件配置和特性。 

24. **third_party**: 第三方依赖库和代码，这些代码不是OpenHarmony项目直接开发的，但是项目需要它们。 



这些组件之间的联系在于它们共同组成了OpenHarmony的开发、构建、测试和部署流程。开发者在`commonlibrary`、`foundation`、`drivers`等目录下开发代码，通过`build.py`或`build.sh`脚本进行编译，在`test`目录下进行测试，最后在`out`目录中生成可用于部署的镜像文件。而`arkcompiler`则是将开发者编写的高级语言代码编译为可在OpenHarmony上运行的机器码。整个系统的硬件适配和特定领域的功能则由`device`、`domains`等目录下的代码来支持。