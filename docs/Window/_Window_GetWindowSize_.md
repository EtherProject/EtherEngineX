### [[ << 回到主页 ]](README.md)

# Window:GetWindowSize

> 获取窗口的大小

```lua

width, height = window:GetWindowSize()

```

## 参数：

window [userdata-Window]：窗口对象

## 返回值：

+ width [number]：宽度
+ height [number]：高度

## 示例
```lua

Window = UsingModule("EtherWindow")
local window = Window.CreateWindow("test1", {x = 100, y = 100, w = 960, h = 640}, {})
local width, height = window:GetWindowSize()

```