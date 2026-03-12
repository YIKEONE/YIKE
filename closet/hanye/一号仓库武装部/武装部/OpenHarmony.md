
 # 一、Event
  #文件名称含义:
 1. "==click_event.cpp==" - 可能包含了处理点击事件的代码。 
2. "==drag_event.cpp==" - 可能包含了处理拖动事件的代码。
3. "==event_hub.cpp==" - 可能是一个中心类，用于管理各种事件的分发和处理。
4. "==focus_hub.cpp==" - 可能是处理焦点事件的代码，比如当用户在不同组件间移动焦点时。
5. "==gesture_event_hub.cpp==" - 可能包含了处理手势事件的代码，比如双击、滑动等手势识别。
6. "==input_event.cpp==" - 可能包含了处理一般输入事件的代码，比如键盘或鼠标输入。
7. "==input_event_hub.cpp==" - 可能是输入事件的中心管理类。
8. "l==ong_press_event.cpp==" - 可能包含了处理长按事件的代码。
9. "==pan_event.cpp==" - 可能包含了处理平移（pan）事件的代码，即用户在屏幕上滑动。
10. "==response_ctrl.cpp==" - 可能是用于控制响应机制的代码。
11. "==scrollable_event.cpp==" - 可能包含了处理可滚动区域滚动事件的代码。
12. "==state_style_manager.cpp==" - 可能是用于管理组件在不同状态下的样式的代码。
13. "==target_component.cpp==" - 可能是用于定义目标组件的代码，这些组件会响应特定事件。
14. "==touch_event.cpp==" - 可能包含了处理触摸事件的代码，适用于触屏设备。

## 1、event_hub.cpp

    1、GestureEventHub-----手势事件{  create、get、set、}
    2、inputHub-------{create、get}
    3、FocusHub-------{ GetOrCreateFocusHub }
    4、FireInnerOnAreaChanged
[![[Pasted image 20240424154321.png]]
这是一个名为 FireInnerOnAreaChanged 的函数，它接受四个参数：两个 RectF 类型的变量 oldRect 和 rect，以及两个 OffsetF 类型的变量 oldOrigin 和 origin。函数内部，它遍历一个名为 onAreaChangedInnerCallbacks_ 的数据结构，该数据结构看起来是一个包含有关回调信息的容器（可能是std::map或std::unordered_map等）。对于容器中的每一项，它检查对应的值（innerCallbackInfo.second ）是否不为空，如果非空，则执行存储在其中的回调函数（innerOnAreaCallback），传递四个参数。

总结来说，这个函数的作用是：

1. 遍历存储在 onAreaChangedInnerCallbacks_ 中的回调信息。

2. 对于每个有效的回调（即，innerCallbackInfo.second 不为空），执行该回调。

3. 在执行回调时，将 oldRect, oldOrigin, rect, 和 origin 四个参数传递给回调函数。

    5、





        