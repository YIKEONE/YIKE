
1、编译库 ace_engine 并将其保存
    ```
```
 ./build.sh --product-name rk3568 --ccache -T ace_engine --fast-rebuild
```
     并将编译出的ace_engine（/home/hanye/work/code/out/rk3568/arkui/ace_engine/）放到本地         D:\netshare 中

```
git log --since="2023-03-07" --until="2023-03-08"
```

```
./build.sh --product-name rk3568 --ccache
```

```
run -l ActsAceCArkUITest  -ta class:RefreshOffsetEventTest
```
2、  将下述命令存放到文件中命名为.bat格式
     hdc  shell mount -o rw,remount /
     hdc  shell setenforce 0
     hdc  file send D:\netshare\ace_engine\libace_compatible.z.so               /system/lib/libace_compatible.z.so
     hdc file send D:\netshare\ace_engine\libace.z.so
     /system/lib/libace.z.so
     hdc file send D:\netshare\ace_engine\libplugincomponent.z.so
     /system/lib/libplugincomponent.z.so
     hdc shell reboot


新需求：[feat: visible speaking for radio selection · Pull Request !60111 · OpenHarmony/arkui_ace_engine - Gitee.com](https://gitee.com/openharmony/arkui_ace_engine/pulls/60111)




MenuParam 结构

### **与蒙层自定义相关的参数**

1. **`backgroundColor`**
    
    - **类型**：`std::optional<Color>`
    - **功能**：设置蒙层的背景颜色。
    - **用途**：开发者可以通过此参数自定义蒙层的颜色，例如设置为半透明黑色或其他颜色。
2. **`backgroundBlurStyle`**
    
    - **类型**：`std::optional<int32_t>`
    - **功能**：设置蒙层的模糊样式。
    - **用途**：用于定义蒙层的模糊效果，例如高斯模糊的强度。
3. **`backgroundBlurStyleOption`**
    
    - **类型**：`std::optional<BlurStyleOption>`
    - **功能**：进一步细化模糊样式的选项。
    - **用途**：允许开发者选择更复杂的模糊效果配置。
4. **`backgroundEffectOption`**
    
    - **类型**：`std::optional<EffectOption>`
    - **功能**：设置蒙层的视觉效果选项。
    - **用途**：可以用于定义蒙层的特殊效果，例如透明度渐变或其他视觉效果。
5. **`effectOption`**
    
    - **类型**：`std::optional<EffectOption>`
    - **功能**：设置额外的视觉效果。
    - **用途**：可以与 `backgroundEffectOption` 配合使用，进一步增强蒙层的视觉表现。
6. **`borderRadius`**
    
    - **类型**：`std::optional<NG::BorderRadiusProperty>`
    - **功能**：设置蒙层的圆角半径。
    - **用途**：允许开发者为蒙层设置圆角效果，使其更符合设计需求。
7. **`layoutRegionMargin`**
    
    - **类型**：`std::optional<NG::MarginProperty>`
    - **功能**：设置蒙层的布局边距。
    - **用途**：用于调整蒙层与菜单内容之间的间距。

---

### **可能的扩展参数**

1. **`blurStyleOption`**
    
    - **类型**：`std::optional<BlurStyleOption>`
    - **功能**：与 `backgroundBlurStyleOption` 类似，用于设置模糊样式。
    - **用途**：可以进一步细化模糊效果的配置。
2. **`outlineWidth`**
    
    - **类型**：`std::optional<NG::BorderWidthProperty>`
    - **功能**：设置蒙层的边框宽度。
    - **用途**：如果蒙层需要边框，可以通过此参数设置边框的宽度。
3. **`outlineColor`**
    
    - **类型**：`std::optional<NG::BorderColorProperty>`
    - **功能**：设置蒙层的边框颜色。
    - **用途**：与 `outlineWidth` 配合使用，为蒙层添加边框效果。

---

### **总结**

#### **核心参数**

- **颜色相关**：
    - `backgroundColor`
- **模糊相关**：
    - `backgroundBlurStyle`
    - `backgroundBlurStyleOption`
    - `blurStyleOption`
- **视觉效果相关**：
    - `backgroundEffectOption`
    - `effectOption`
- **布局相关**：
    - `borderRadius`
    - `layoutRegionMargin`

#### **扩展参数**

- **边框相关**：
    - `outlineWidth`
    - `outlineColor`

这些参数为开发者提供了丰富的自定义选项，可以满足多样化的蒙层样式需求。如果需要实现具体的功能，可以基于这些参数进行逻辑开发。