### [[ << 回到主页 ]](../README.md)

# Window

> Window 模块提供窗口相关操作

## 模块函数列表

+ [CreateWindow(title, rect, attributes)](_CreateWindow_.md)：创建并返回窗口对象，可创建多个窗口

## 对象成员函数

+ Window 对象成员函数

    + [Window:CloseWindow()](_Window_CloseWindow_.md)：关闭并删除该窗口对象

    + [Window:GetWindowTitle()](_Window_GetWindowTitle_.md)：获取该窗口对象的标题

    + [Window:SetWindowTitle(title)](_Window_SetWindowTitle_.md)：设置该窗口对象的标题

    + [Window:SetWindowMode(mode)](_Window_SetWindowMode_.md)：设置窗口样式

    + [Window:SetWindowOpacity(value)](_Window_SetWindowOpacity_.md)：设置窗口不透明度

    + [Window:GetWindowSize(width, height)](_Window_GetWindowSize_.md)：获取窗口大小

    + [Window:SetWindowSize()](_Window_SetWindowSize_.md)：设置窗口大小

    + [Window:GetWindowMaxSize()](_Window_GetWindowMaxSize_.md)：获取窗口最大尺寸的大小

    + [Window:SetWindowMaxSize(width, height)](_Window_SetWindowMaxSize_.md)：设置窗口最大尺寸的大小

    + [Window:GetWindowMinSize()](_Window_GetWindowMinSize_.md)：获取窗口最小尺寸的大小

    + [Window:SetWindowMinSize(width, height)](_Window_SetWindowMinSize_.md)：设置窗口最小尺寸的大小

    + [Window:GetWindowPosition()](_Window_GetWindowPosition_.md)：获取窗口的坐标位置

    + [Window:SetWindowPosition(width, height)](_Window_SetWindowPosition_.md)：设置窗口的坐标位置

    + [Window:GetWindowID()](_Window_GetWindowID_.md)：获取窗口的ID

    + [Window:AddNode(node)](_Window_AddNode_.md)：为窗口的节点列表添加节点

    + [Window:DeleteNode(node)](_Window_DeleteNode_.md)：删除窗口节点列表中指定索引的节点

## 作者的话

> 由于SDL2支持多窗口，想来挺有意思的，就把EtherEngineX中的窗口设计为了一个对象
> 本来窗口下应该是图层类，但因为我还没搞的太清楚，所以干脆就在某个版本删除掉了