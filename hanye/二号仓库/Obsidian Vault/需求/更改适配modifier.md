![[img_v3_02ct_50d16b3a-ed09-4b79-8304-f0cd2619630g.jpg]]【需求描述】:

Search搜索框无文本输入时，支持控件搜索按钮置灰显示，输入内容后，按钮自动恢复

【验收场景和标准】：

1、search搜索框无文本内容，搜索按钮可以置灰，输入内容后，搜索按钮恢复

【是否Rust开发】：否

【涉及接口类型，建议选一】: TS

【是否影响应用兼容性】：否

【外部依赖子系统】:不涉及

【性能功耗指标】:不涉及

【是否支持跨平台】：支持

【是否涉及DFX】:不涉及

【是否涉及一多】：不涉及

【是否涉及工具链】:不涉及

【是否涉及预览】:涉及

【是否涉及无障碍】：不涉及

【是否涉及全球化】：不涉及

**需求1**：给imageSpan添加前景色    提了三个pr：

①interface新加接口的pr：位置在ssh/interface   分支：imageSpan
https://gitee.com/openharmony/interface_sdk-js/pulls/12211
②ace_enging业务代码（给imageSpan添加前景色）pr：位置在/code/ace_engine/arkui_ace_engine_zhangbaoyi$
分支：0621_imageSpan
https://gitee.com/openharmony/arkui_ace_engine/pulls/36188
③doc pr位置：/doc/imagespan_colorfilter/docs_zhangbaoyi

**需求2**：bindmenu pr:
1.ace_enging业务代码 pr：位置/code/ace_engine/arkui_ace_engine_zhangbaoyi
分支20240724



![[Pasted image 20240531154210.png]]

修改为更改背景颜色：![[Pasted image 20240611203643.png]]
---点击输入框触发：

![[Pasted image 20240603154513.png]]
08-05 18:27:43.068   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(OnModifyDone)-(100000:100000:scope)] ###test zby SearchPattern::OnModifyDone  02
08-05 18:27:43.143   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(InitTextFieldValueChangeEvent)-(100000:100000:scope)] ###test zby SearchPattern::InitTextFieldValueChangeEvent  03
08-05 18:27:43.143   1923-1923    C03900/Ace                     com.examp...lication  I  [text_field_event_hub.h(GetOnChange)-(100000:100000:scope)] ###test zby TextFieldEventHub GetOnChange 02


输入文本：
08-05 18:28:08.857   1923-1923    C03900/Ace                     com.examp...lication  I  [text_field_event_hub.h(FireOnChange)-(100000:100000:scope)] ###test zby TextFieldEventHub  FireOnChange  01
08-05 18:28:08.857   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby SearchPattern::UpdateChangeEvent  01
08-05 18:28:08.857   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby textMessage IS NULL
08-05 18:28:08.857   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby textMessage IS NULL END!
08-05 18:28:08.868   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby SearchPattern::UpdateChangeEvent  01
08-05 18:28:08.868   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby textMessage IS NULL
08-05 18:28:08.868   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby textMessage IS NULL END!
08-05 18:28:08.868   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby SearchPattern::UpdateChangeEvent  01
08-05 18:28:08.869   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby textMessage IS NULL
08-05 18:28:08.869   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby textMessage IS NULL END!
08-05 18:28:08.870   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby SearchPattern::UpdateChangeEvent  01
08-05 18:28:08.870   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby textMessage IS NULL
08-05 18:28:08.870   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby textMessage IS NULL END!
08-05 18:28:08.871   1923-1923    C03900/Ace                     com.examp...lication  I  [text_field_event_hub.h(SetOnChange)-(100000:100000:scope)] ###test zby TextFieldEventHub SetOnChange 03
08-05 18:28:08.871   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(OnModifyDone)-(100000:100000:scope)] ###test zby SearchPattern::OnModifyDone  02
08-05 18:28:08.872   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(InitTextFieldValueChangeEvent)-(100000:100000:scope)] ###test zby SearchPattern::InitTextFieldValueChangeEvent  03
08-05 18:28:08.872   1923-1923    C03900/Ace                     com.examp...lication  I  [text_field_event_hub.h(GetOnChange)-(100000:100000:scope)] ###test zby TextFieldEventHub GetOnChange 02

删除文本：
08-05 18:26:53.806   1923-1923    C03900/Ace                     com.examp...lication  I  [text_field_event_hub.h(FireOnChange)-(100000:100000:scope)] ###test zby TextFieldEventHub  FireOnChange  01
08-05 18:26:53.806   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby SearchPattern::UpdateChangeEvent  01
08-05 18:26:53.806   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby textMessage IS NULL
08-05 18:26:53.817   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby SearchPattern::UpdateChangeEvent  01
08-05 18:26:53.817   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby textMessage IS NULL
08-05 18:26:53.818   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby SearchPattern::UpdateChangeEvent  01
08-05 18:26:53.818   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby textMessage IS NULL
08-05 18:26:53.819   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby SearchPattern::UpdateChangeEvent  01
08-05 18:26:53.819   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby textMessage IS NULL
08-05 18:26:53.819   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(UpdateChangeEvent)-(100000:100000:scope)] ###test zby textMessage IS NULL END!
08-05 18:26:53.821   1923-1923    C03900/Ace                     com.examp...lication  I  [text_field_event_hub.h(SetOnChange)-(100000:100000:scope)] ###test zby TextFieldEventHub SetOnChange 03
08-05 18:26:53.821   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(OnModifyDone)-(100000:100000:scope)] ###test zby SearchPattern::OnModifyDone  02
08-05 18:26:53.822   1923-1923    C03900/Ace                     com.examp...lication  I  [search_pattern.cpp(InitTextFieldValueChangeEvent)-(100000:100000:scope)] ###test zby SearchPattern::InitTextFieldValueChangeEvent  03
08-05 18:26:53.822   1923-1923    C03900/Ace                     com.examp...lication  I  [text_field_event_hub.h(GetOnChange)-(100000:100000:scope)] ###test zby TextFieldEventHub GetOnChange 02


**---时序图：**
sequenceDiagram
Participant 框架
Participant SearchModelNG
Participant FrameNode
Participant SearchPattern
Participant TextFieldEventHub
Participant RenderContext
Participant EventHub

activate SearchModelNG
SearchModelNG->>FrameNode:GetOrCreateFrameNode()
activate FrameNode
FrameNode-->>SearchModelNG:GetFrameNode()
SearchModelNG->>SearchPattern:SetButtonNode()
activate SearchPattern
activate 框架
框架->>FrameNode:MarkModifyDone()
FrameNode->>SearchPattern:MarkModifyDone()
SearchPattern->>SearchPattern:OnModifyDone()
SearchPattern->>SearchPattern:InitTextFieldValueChangeEvent()

SearchPattern-->>FrameNode:host->GetChildren()
FrameNode->>SearchPattern:GetEventHub()
SearchPattern->>TextFieldEventHub:GetOnChange()
activate TextFieldEventHub
TextFieldEventHub-->>SearchPattern:isOnChange() 布尔类型
deactivate TextFieldEventHub

SearchPattern->>SearchPattern:UpdateChangeEvent()
SearchPattern-->>FrameNode:host->GetOrCreateFrameNode()
FrameNode->>SearchPattern:GetRenderContext()
SearchPattern->>RenderContext:UpdateBackgroundColor()
activate RenderContext
RenderContext-->>SearchPattern:void()
deactivate RenderContext

SearchPattern-->>FrameNode:host->GetOrCreateFrameNode()
FrameNode->>SearchPattern:GetEventHub()
SearchPattern->>EventHub:SetEnabLed()
activate EventHub
EventHub-->>SearchPattern:isEnabLed()布尔类型
deactivate EventHub
deactivate SearchModelNG
deactivate SearchPattern
deactivate FrameNode
deactivate 框架
![[Pasted image 20240612151427.png]]



需求二：
【需求描述】: Search子icon支持提供InspectorID

输入:开发者配置Search的icon

处理：

1. Search控件创建的时候，给对应的icon生成inspector id。

输出：开发者可基于getInspectorById的方式获取Search控件的icon节点

【验收场景和标准】：开发者可基于getInspectorById的方式获取Search控件的icon节点

【是否Rust开发】：否

【涉及接口类型】: 不涉及

【是否影响应用兼容性】:否

【外部依赖】: 无

【性能功耗指标】: 不涉及

【是否支持跨平台】：支持

【是否涉及DFX】:可增加Dump信息

【是否涉及一多】：不涉及

【是否涉及工具链】:不涉及

【是否涉及预览】:涉及

【是否涉及无障碍】：不涉及

【是否涉及全球化】：不涉及

![[Pasted image 20240613142902.png]]

![[Pasted image 20240613164245.png]]

==添加枚举不成功不生效原因是这个文件/home/zby/zwork/foundation/arkui/ace_engine/frameworks/bridge/declarative_frontend/engine/jsEnumStyle.js里也要添加东西：==
```
var UpdateIconId;

(function (UpdateIconId) {

  UpdateIconId["SEARCHICON"] = "SEARCHICON";

  UpdateIconId["CANCELICON"] = "CANCELICON";

  UpdateIconId["LAOXU"] = "LAOXU";

})(UpdateIconId || (UpdateIconId = {}));

```

![[Pasted image 20240618104926.png]]
==打印枚举：==
LOGE("TEST b JSSearch::SetIconId 1 type = %{public}d",static_cast<int32_t>(iconType));


![[Pasted image 20240620145817.png]]

![[img_v3_02c1_6a98f44f-7599-4daf-a0e5-3931aee8727g.jpg]]


第二个需求：【基础能力】ImageSpan支持前景色设置

流程：
先Fork一个仓，在interface下建一个属于自己的仓，然后新建一个分支：在zwork同级目录下新建一个文件夹步骤如下：

![[Pasted image 20240620193926.png]]
在这个目录下提的接口pr，下面是执行的命令
![[Pasted image 20240629164831.png]]
![[Pasted image 20240629165013.png]]
![[Pasted image 20240629165055.png]]
![[Pasted image 20240629165133.png]]

提交新增接口的PR,然后更改API文档，完成就调试编写代码，代码PR提交，改设计文档。

下载最新的镜像：提交pr后有一个最新的镜像，更新到本地
![[Pasted image 20240622093457.png]]

![[Pasted image 20240622093726.png]]
然后就是清空所有项导入所有项，这里D盘images1是之前的镜像。

![[Pasted image 20240622093840.png]]



更改适配modifier：
1.ArkImageSpan.ts
![[Pasted image 20240701092600.png]]

![[Pasted image 20240701092634.png]]

2.arkComponent.js

![[Pasted image 20240701093457.png]]
![[Pasted image 20240701093552.png]]


3.arkts_native_api_impl_bridge.cpp
![[Pasted image 20240701093756.png]]

4.arkts_native_image_span_bridge.cpp
![[Pasted image 20240701093955.png]]

![[Pasted image 20240701094055.png]]

![[Pasted image 20240701094117.png]]

![[Pasted image 20240701094136.png]]
5.arkts_native_image_span_bridge.h
![[Pasted image 20240701094227.png]]

6.node_image_span_modifier.cpp

![[Pasted image 20240701094322.png]]
![[Pasted image 20240701094405.png]]
![[Pasted image 20240701094431.png]]
顺序不能写错
![[Pasted image 20240701094514.png]]

7.arkoala_api.h
![[Pasted image 20240701094617.png]]


重新更新一下业务代码pr
git diff
git status
git add .
git status
git commit --amend
git push origin 0621_imageSpan -f

然后填写review表：
![[Pasted image 20240702093404.png]]

代码门禁通过==本地自测成功==就可以把sdk和镜像打包zip发给佳丽哥：
==本地自测:把门禁上的dayu_200下到本地，最新的镜像烧到板子里测试demo
![[Pasted image 20240702141848.png]]
![[Pasted image 20240702093501.png]]

![[Pasted image 20240702093520.png]]
![[Pasted image 20240702093538.png]]

![[Pasted image 20240702093743.png]]

==打包成zip，不能是7z==

interface的接口pr：
新的提交pr流程：
随便点一个pr 进去：点击OpenHarmony
![[Pasted image 20240702104126.png]]

![[Pasted image 20240702104202.png]]
![[Pasted image 20240702104239.png]]
![[Pasted image 20240702104258.png]]

![[Pasted image 20240702104331.png]]![[Pasted image 20240702104346.png]]
![[Pasted image 20240702104430.png]]
![[Pasted image 20240702104609.png]]


项目构成：
1.镜像 dayu200
2.ohos_sdk 替换5个文件，并把12修改为11
3.文件更改


searchbutton 无文本内容按钮置灰：
会议纪要参考模板： 
1、支持自动大小写模式添加个接口autoCap传一个枚举类型包含:none(默认规格不主动触发）、worlds（按词语大写）、sentences(按句子大写)、allcharacters （全大写）。
2、实现让输入法应用感知到空格后输入的类型做出相应的处理（功能由小E输入法实现）。
3、我们这边负责传递四个属性，通过输入法框架传给输入法应用做处理（实现个传输协议）。
4、依赖输入法应用、输入法框架（后续需要拉齐会议、有个风险点）。 
5、涉及 API接口 dfx modifier tdd preview xts。 6、验收需要小E配合、接口我们开，输入法框架用。


会议纪要：
1.搜索框无文本内容时候不可以有点击动效

2.按钮置灰是背景颜色置灰还是字体置灰，需要华为SE和ux对一下

3.空格特殊符号换行，其他文字算有文本，没有其他特殊输入需要注意

4.涉及DFX,XTS,TDD

5.需要华为SE提供新的接口，新增一个search控件是否开启这个功能（有风险）

6支不支持modifier和preview（再议）

7.是否设计UX?

```
doc文档示例：
import { drawing, common2D } from '@kit.ArkGraphics2D';

  

@Entry

@Component

struct SpanExample {

  private ColorFilterMatrix: number[] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0]

  @State DrawingColorFilterFirst: ColorFilter | undefined = new ColorFilter(this.ColorFilterMatrix)

  private color: common2D.Color = { alpha: 255, red: 255, green: 0, blue: 0 };

  @State DrawingColorFilterSecond: ColorFilter | undefined = undefined

  

  build() {

    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {

      Text() {

        ImageSpan($r('app.media.icon'))

          .width('50px')

          .height('50px')

          .colorFilter(this.DrawingColorFilterFirst)

          .onClick(()=>{

            this.DrawingColorFilterFirst = drawing.ColorFilter.createBlendModeColorFilter(this.color, drawing.BlendMode.SRC_IN);

          })

      }

      .width('50%')

      Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {

        Text() {

          ImageSpan($r('app.media.icon'))

            .width('50px')

            .height('50px')

            .colorFilter(this.DrawingColorFilterSecond)

            .onClick(()=>{

              this.DrawingColorFilterSecond = drawing.ColorFilter.createBlendModeColorFilter({ alpha: 255, red: 255, green: 255, blue: 0 }, drawing.BlendMode.SRC);

            })

        }

      .width('50%')

      }.width('100%').height('10%')

    }.width('200%').height('100%')

  }

}
```

![[image_span_colorfilter.gif]]



1.search在无文本内容输入的时候按钮置灰且不可点击
新加接口：autoEnableSearchButton
```
/**

   * If there is no text, the search button is grayed out and cannot be clicked.

   *

   * @param { boolean } value

   * @returns { SearchAttribute } returns the instance of the SearchAttribute.

   * @syscap SystemCapability.ArkUI.ArkUI.Full

   * @crossplatform

   * @atomicservice

   * @since 13

   */

    autoEnableSearchButton(value: boolean): SearchAttribute;

}
```
