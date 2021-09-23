### [[ << 回到主页 ]](../README.md)

# Event

> Event 模块提供窗口相关操作

## 模块函数列表

+ [CreateMouseListener(name)](_CreateMouseListener_.md)：创建一个监听鼠标的监听者

+ [CreateKeyboardListener(name)](_CreateKeyboardListener_.md)：创建一个监听键盘的监听者

+ [CreateWindowListener(name)](_CreateWindowListener_.md)：创建一个监听窗口的监听者

+ [RemoveListener(name)](_RemoveListener_.md)：删除指定名称的监听者

## 对象成员函数

+ Listener 对象成员函数

    + [Listener:GetName()](_Listener_GetName_.md)：获取该监听者的名称

    + [Listener:SetButtonDown(function)](_Listener_SetButtonDown_.md)：设置鼠标按键按下时的回调函数(鼠标监听者)

    + [Listener:SetButtonUp(function)](_Listener_SetButtonUp_.md)：设置该鼠标按键弹起时的回调函数(鼠标监听者)

    + [Listener:SetMotion(function)](_Listener_SetMotion_.md)：设置该鼠标移动时的回调函数(鼠标监听者)

    + [Listener:GetButtonType()](_Listener_GetButtonType_.md)：获取鼠标当前按下的键(鼠标监听者)

    + [Listener:GetCursorPoint()](_Listener_GetCursorPoint_.md)：获取鼠标当前在窗口中的坐标值(鼠标监听者)

    + [Listener:GetWheelLength()](_Listener_GetWheelLength_.md)：获取鼠标滚轮滚动的距离(鼠标监听者)

    + [Listener:SetKeyDown(function)](_Listener_SetKeyDown_.md)：设置键盘按键按下时的回调函数(键盘监听者)

    + [Listener:SetKeyUp(function)](_Listener_SetKeyUp_.md)：设置键盘按键弹起时的回调函数(键盘监听者)

    + [Listener:GetKeyType()](_Listener_GetKeyType_.md)：获取键盘当前按下的键(键盘监听者)

    + [Listener:GetKeyMod()](_Listener_GetKeyMod_.md)：获取键盘当前按下的键的修饰键(键盘监听者)

    + [Listener:SetWindowShown(function)](_Listener_SetWindowShown_.md)：设置窗口显示时的回调函数(窗口监听者)

    + [Listener:SetWindowHidden(function)](_Listener_SetWindowHidden_.md)：设置窗口隐藏时的回调函数(窗口监听者)

    + [Listener:SetWindowEnter(function)](_Listener_SetWindowEnter_.md)：设置鼠标进入窗口范围时的回调函数(窗口监听者)

    + [Listener:SetWindowLeave(function)](_Listener_SetWindowLeave_.md)：设置鼠标离开窗口范围时的回调函数(窗口监听者)

    + [Listener:SetWindowFocusGained(function)](_Listener_SetWindowFocusGained_.md)：设置窗口获取焦点时的回调函数(窗口监听者)

    + [Listener:SetWindowFocusLost(function)](_Listener_SetWindowFocusLost_.md)：设置窗口失去焦点时的回调函数(窗口监听者)

    + [Listener:SetWindowMove(function)](_Listener_SetWindowMove_.md)：设置窗口移动时的回调函数(窗口监听者)

    + [Listener:SetWindowResize(function)](_Listener_SetWindowResize_.md)：设置窗口大小改变时的回调函数(窗口监听者)

    + [Listener:SetWindowClose(function)](_Listener_SetWindowClose_.md)：设置窗口关闭时的回调函数(窗口监听者)

    + [Listener:GetEventWindowID()](_Listener_GetEventWindowID_.md)：获取发生事件的窗口的ID(窗口监听者)