```
//search无文本内容输入按钮置灰且不可点击
@Entry  
@Component  
struct SearchExample {  
  @State changeValue: string = ''  
  @State submitValue: string = ''  
  
  build() {  
    Column() {  
      Text('onSubmit:' + this.submitValue).fontSize(18).margin(15)  
      Search({ value: this.changeValue, placeholder: 'Type to search...' })  
        .searchButton('SEARCH')  
        .searchIcon({  
          src: $r('app.media.icon')  
        })  
        .cancelButton({  
          style: CancelButtonStyle.CONSTANT,  
          icon: {  
            src: $r('app.media.icon')  
          }  
        })  
        .  
        .width('90%')  
        .height(40)  
        .maxLength(20)  
        .backgroundColor('#F5F5F5')  
        .placeholderColor(Color.Grey)  
        .placeholderFont({ size: 14, weight: 400 })  
        .textFont({ size: 14, weight: 400 })  
        .onSubmit((value: string) => {  
          this.submitValue = value  
        })  
        .onChange((value: string) => {  
          this.changeValue = value  
        })  
        .margin(20)  
    }.width('100%')  
  }  
}
```

```
//colorfilter
import { drawing, common2D } from '@kit.ArkGraphics2D';  
  
@Entry  
@Component  
struct SpanExample {  
  private ColorFilterMatrix: number[] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0]  
  @State DrawingColorFilterFirst: ColorFilter | undefined = new ColorFilter(this.ColorFilterMatrix)  
  private color: common2D.Color = { alpha: 255, red: 255, green: 0, blue: 0 };  
  
  build() {  
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {  
      Text() {  
        ImageSpan($r('app.media.icon'))  
          .width('50px')  
          .height('50px')  
          .colorFilter(this.DrawingColorFilterFirst)  
      }  
      .width('50%')  
      Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {  
        Text() {  
          ImageSpan($r('app.media.icon'))  
            .width('50px')  
            .height('50px')  
            .colorFilter(drawing.ColorFilter.createBlendModeColorFilter({ alpha: 255, red: 0, green: 255, blue: 0 }, drawing.BlendMode.SRC))  
        }  
        .width('50%')  
      }.width('100%').height('10%')  
    }.width('200%').height('100%')  
  }  
}
```