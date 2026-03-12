```
### colorFilter<sup>12+</sup>

  

colorFilter(value: ColorFilter | DrawingColorFilter)

  

为图像设置颜色滤镜效果。

  

**原子化服务API：** 从API version 12开始，该接口支持在原子化服务中使用。

  

**系统能力：** SystemCapability.ArkUI.ArkUI.Full

  

**参数：**

  

| 参数名 | 类型                                    | 必填 | 说明                                                         |

| ------ | --------------------------------------- | ---- | ------------------------------------------------------------ |

| value  | [ColorFilter](ts-types.md#colorfilter9) \| [DrawingColorFilter](../../apis-arkgraphics2d/js-apis-graphics-drawing.md#colorfilter) | 是   | 1. 给图像设置颜色滤镜效果，入参为一个的4x5的RGBA转换矩阵。<br/>矩阵第一行表示R（红色）的向量值，第二行表示G（绿色）的向量值，第三行表示B（蓝色）的向量值，第四行表示A（透明度）的向量值，4行分别代表不同的RGBA的向量值。<br/>当矩阵对角线值为1，其余值为0时，保持图片原有色彩。<br/> **计算规则：**<br/>如果输入的滤镜矩阵为：<br/>![image-matrix-1](figures/image-matrix-1.jpg)<br/>像素点为[R, G, B, A]<br/>则过滤后的颜色为 [R’, G’, B’, A’]<br/>![image-matrix-2](figures/image-matrix-2.jpg)<br/>2. 支持@ohos.graphics.drawing的ColorFilter类型作为入参。<br/>**说明：** <br/>该接口中的DrawingColorfilter类型支持在原子化服务中使用。其中，svg类型的图源需具有stroke属性。|

@Entry

@Component

struct SpanExample {

  private ColorFilterMatrix: number[] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0]

  @State DrawingColorFilterFirst: ColorFilter | undefined = new ColorFilter(this.ColorFilterMatrix)

  

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

```

```