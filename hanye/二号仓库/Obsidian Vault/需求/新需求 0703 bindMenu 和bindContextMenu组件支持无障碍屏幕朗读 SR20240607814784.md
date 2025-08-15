
1.bindmenu 有三种方式：

①数组， 需要找调setaccessibility 方法

```
@Entry
@Component
struct MenuExample {
  build() {
    Column() {
      Text('click for Menu')
        .bindMenu([
          {
            value: 'Menu1',
            action: () => {
              console.info('handle Menu1 select')
            }
          },
          {
            value: 'Menu2',
            action: () => {
              console.info('handle Menu2 select')
            }
          },
        ])
    }
    .width('100%')
    .margin({ top: 5 })
  }
}
```

②builder 可以直接 . accessibility

```
@Entry
@Component
struct MenuExample {
  @State listData: number[] = [0, 0, 0]
  @Builder MenuBuilder() {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      ForEach(this.listData, (item:number, index) => {
        Column() {
          Row() {
            Image($r("app.media.icon")).width(20).height(20).margin({ right: 5 })
            Text(`Menu${index as number + 1}`).fontSize(20)
          }
          .width('100%')
          .height(30)
          .justifyContent(FlexAlign.Center)
          .align(Alignment.Center)
          .onClick(() => {
            console.info(`Menu${index as number + 1} Clicked!`)
          })
          if (index != this.listData.length - 1) {
            Divider().height(10).width('80%').color('#ccc')
          }
        }.padding(5).height(40)
      })
    }.width(100)
  }
  build() {
    Column() {
      Text('click for menu')
        .fontSize(20)
        .margin({ top: 20 })
        .bindMenu(this.MenuBuilder)
    }
    .height('100%')
    .width('100%')
    .backgroundColor('#f0f0f0')
  }
}
```

③bindmenu menuitem 可能要加一个接口，starticonaccessbilitytext

```
@Entry
@Component
struct Index {
  @State select: boolean = true
  private iconStr: ResourceStr = $r("app.media.view_list_filled")
  private iconStr2: ResourceStr = $r("app.media.arrow_right_filled")
  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: "复制", labelInfo: "Ctrl+C" })
      MenuItem({ content: "粘贴", labelInfo: "Ctrl+V" })
    }
  }
  @Builder
  MyMenu(){
    Menu() {
      MenuItem({ startIcon: $r("app.media.icon"), content: "菜单选项" })
      MenuItem({ startIcon: $r("app.media.icon"), content: "菜单选项" })
        .enabled(false)
      MenuItem({
        startIcon: this.iconStr,
        content: "菜单选项",
        endIcon: this.iconStr2,
        builder: ():void=>this.SubMenu()
      })
      MenuItemGroup({ header: '小标题' }) {
        MenuItem({
          startIcon: this.iconStr,
          content: "菜单选项",
          endIcon: this.iconStr2,
          builder: ():void=>this.SubMenu()
        })
        MenuItem({
          startIcon: $r("app.media.app_icon"),
          content: "菜单选项",
          endIcon: this.iconStr2,
          builder: ():void=>this.SubMenu()
        })
      }
      MenuItem({
        startIcon: this.iconStr,
        content: "菜单选项",
      })
    }
  }
  build() {
    Row() {
      Column() {
        Text('click to show menu')
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
      }
      .bindMenu(this.MyMenu)
      .width('100%')
    }
    .height('100%')
  }
}
```

2.bindmenu、bindContextMenu 要找到出现和关闭的地方

出现menu的地方：


关闭menu的地方：
![[Pasted image 20240708101044.png]]


串讲问题清单：
1.上报弹出/退出状态信息给无障碍框架。 请问那这个焦点是否要进行无障碍处理？
2.menu里不是有很多选项吗，是所有选项都要读吗？
3.menu里有文字还有图片，请问accessibility读的是图片还是文字呢？如果读图片文字是不是就不做处理
4.text是要加在哪里？
5.别的模块我略了解，但是对于这个模块的异常值我不太了解，请您说一下


【需求来源】: 无障碍

【需求描述】: bindMenu/bindContextMenu组件支持屏幕朗读，上报弹出/退出状态信息给无障碍框架。

【验收场景和标准】：bindMenu/bindContextMenu组件弹出时，无障碍焦点框架能显示在菜单上；退出时无障碍焦点框架显示在下层页面上；涉及组件：NavitationMenu/SelectOverlayExtensionMenu/SelectOverlayCustomMenu/SelectOverlaySubMenu/SelectOverlayRightClickMenu

【是否Rust开发】：否

【涉及接口类型，建议选一】: 不涉及

【是否影响应用兼容性】:否

【验收平台，可多选】：手机工程机/开发板/ArkUI-X

【外部依赖子系统】:不涉及

【性能功耗指标】:不涉及

【是否支持跨平台】：不涉及

【是否涉及DFX】:不涉及

【是否涉及一多】：不涉及

【是否涉及工具链】:不涉及

【是否涉及预览】: 不涉及

【是否涉及无障碍】：不涉及

【是否涉及全球化】不涉及


![](https://chatgai.lovepor.cn/images/head_cquestion@3x.png)


```cpp
auto pipelineContext = NG::PipelineContext::GetCurrentContext();
CHECK_NULL_VOID(pipelineContext);
auto overlayManager = pipelineContext->GetOverlayManager();
CHECK_NULL_VOID(overlayManager);
auto menuNode = overlayManager->GetMenuNode(targetId);
if (menuNode) {
LOGI("@@@@TEST BY ViewAbstractModelNG::BindMenu 02");
auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
wrapperPattern->SetHasTransitionEffect(menuParam.hasTransitionEffect);
if (menuParam.hasTransitionEffect) {
LOGI("@@@@TEST BY ViewAbstractModelNG:BindMenu 03");
auto renderContext = menuNode->GetRenderContext();
CHECK_NULL_VOID(renderContext);
renderContext->UpdateChainedTransition(menuParam.transition);
}
if (wrapperPattern->IsShow() && menuParam.setShow && !menuParam.isShow) {
LOGI("@@@@TEST BY ViewAbstractModel:BindMenu 04");
overlayManager->HideMenu(menuNode, targetId, false);
}
} else if (menuParam.isShow) {
LOGI("@@@@TEST BY ViewAbstractModelNG::BindMenu 05");
if (!params.empty()) {
LOGI("@@@@TEST BY ViewAbstractModelNG::BindMenu 06");
NG::ViewAbstract::BindMenuWithItems(std::move(params), targetNode, menuParam.positionOffset, menuParam);
} else if (buildFunc) {
LOGI("@@@@TEST BY ViewAbstractModelNG::BindMenu 07");
std::function<void()> previewBuildFunc;
NG::ViewAbstract::BindMenuWithCustomNode(
std::move(buildFunc), targetNode, menuParam.positionOffset, menuParam, std::move(previewBuildFunc));
}
}
if (!menuParam.setShow) {
LOGI("@@@@TEST BY ViewAbstractModelNG::BindMenu 08");
BindMenuGesture(std::move(params), std::move(buildFunc), menuParam);
}
// delete menu when target node destroy
auto pipeline = PipelineBase::GetCurrentContext();
CHECK_NULL_VOID(pipeline);
auto theme = pipeline->GetTheme<SelectTheme>();
CHECK_NULL_VOID(theme);
auto expandDisplay = theme->GetExpandDisplay();
if (!menuParam.isShowInSubWindow && expandDisplay) {
expandDisplay = false;
}
if (!expandDisplay) {
LOGI("@@@@TEST BY ViewAbstractModelNG::BindMenu 09");
auto destructor = [id = targetNode->GetId(), params]() mutable {
params.clear();
auto pipeline = NG::PipelineContext::GetCurrentContext();
CHECK_NULL_VOID(pipeline);
auto overlayManager = pipeline->GetOverlayManager();
CHECK_NULL_VOID(overlayManager);
overlayManager->DeleteMenu(id);
};
targetNode->PushDestroyCallback(destructor);
} else {
LOGI("@@@@TEST BY ViewAbstractModelNG::BindMenu 10");
}
```

bindmenu show menu
![[Pasted image 20240709104524.png]]


```
打印枚举值
auto pipeline = PipelineBase::GetCurrentContext(); CHECK_NULL_VOID(pipeline);  
AccessibilityEvent event; event.type = AccessibilityEventType::PAGE_CHANGE;  
pipeline->SendEventToAccessibility(event); 
TAG_LOGI(AceLogTag::ACE_OVERLAY, “Send event to accessibility %{public}d”, static_cast<int32_t>(event.type)); }
```


提pr首先在本地新建一个分支：
![[Pasted image 20240712150239.png]]
然后修改完代码，就push一下，分支就会推到远程仓
![[Pasted image 20240712165336.png]]

然后就可以提交pr，进入自己的仓，下面新建一个pr，选自己的分支，然后提交，关联issue就完成了！
然后填写这个表格：位置在四大神奇
![[Pasted image 20240712165736.png]]
![[Pasted image 20240712165544.png]]

```
封装函数解决超50行
void OverlayManager::SendToAccessibility(const RefPtr<FrameNode>& node, AccessibilityEventType eventType, WindowsContentChangeTypes contentChangeType)

{

    auto menuWrapper = node.Upgrade();

    CHECK_NULL_VOID(menuWrapper);

    menuWrapper->OnAccessibilityEvent(eventType, contentChangeType);

        TAG_LOGI(AceLogTag::ACE_OVERLAY, "Send event to %{public}d",

        static_cast<int32_t>(eventType));

}

void OverlayManager::ShowMenuAnimation(const RefPtr<FrameNode>& menu)

{

    LOGI("@@@@TEST BY  OverlayManager::ShowMenuAnimation 0");

    BlurLowerNode(menu);

    auto wrapperPattern = menu->GetPattern<MenuWrapperPattern>();

    CHECK_NULL_VOID(wrapperPattern);

    wrapperPattern->CallMenuAboutToAppearCallback();

    wrapperPattern->SetMenuStatus(MenuStatus::ON_SHOW_ANIMATION);

    SetIsMenuShow(true);

    if (wrapperPattern->HasTransitionEffect()) {

        UpdateMenuVisibility(menu);

        auto renderContext = menu->GetRenderContext();

        CHECK_NULL_VOID(renderContext);

        renderContext->SetTransitionInCallback(

            [weak = WeakClaim(this), menuWK = WeakClaim(RawPtr(menu)), id = Container::CurrentId()] {

                auto overlayManager = weak.Upgrade();

                CHECK_NULL_VOID(overlayManager);

                overlayManager->OnShowMenuAnimationFinished(menuWK, weak, id);

            });

        return;

    }

    AnimationOption option;

    option.SetCurve(Curves::FAST_OUT_SLOW_IN);

    option.SetDuration(MENU_ANIMATION_DURATION);

    option.SetFillMode(FillMode::FORWARDS);

    option.SetOnFinishEvent(

        [weak = WeakClaim(this), menuWK = WeakClaim(RawPtr(menu)), id = Container::CurrentId()] {

            auto overlayManager = weak.Upgrade();

            CHECK_NULL_VOID(overlayManager);

            overlayManager->OnShowMenuAnimationFinished(menuWK, weak, id);

            overlayManager->SendToAccessibility(menuWK, AccessibilityEventType::PAGE_CHANGE, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);

        });

  

    if (wrapperPattern->GetPreviewMode() == MenuPreviewMode::CUSTOM) {

        auto pipelineContext = PipelineContext::GetCurrentContext();

        CHECK_NULL_VOID(pipelineContext);

        auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();

        CHECK_NULL_VOID(menuTheme);

        option.SetDuration(menuTheme->GetContextMenuAppearDuration());

        auto previewChild = wrapperPattern->GetPreview();

        if (previewChild) {

            auto previewPattern = AceType::DynamicCast<MenuPreviewPattern>(previewChild->GetPattern());

            if (previewPattern) {

                previewPattern->SetFirstShow();

            }

        }

    }

    wrapperPattern->SetAniamtinOption(option);

    SetPatternFirstShow(menu);

    LOGI("@@@@TEST BY  OverlayManager::ShowMenuAnimation 1");

}
```
![[Pasted image 20240724105117.png]]

![[Pasted image 20240724105211.png]]