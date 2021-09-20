### [[ << 回到主页 ]](README.md)

# Window:GetWindowTitle

> 获取该窗口对象的标题

```lua

title = window:GetWindowTitle()

```

## 参数：

无

## 返回值：

+ title [string]：窗口标题

## 示例
```lua

Window = UsingModule("EtherWindow")
local window = Window.CreateWindow("test1", {x = 100, y = 100, w = 960, h = 640}, {})
local title = window:GetWindowTitle()

```