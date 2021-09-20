### [[ << 回到主页 ]](README.md)

# Window:SetWindowTitle

> 设置该窗口对象的标题

```lua

window:SetWindowTitle(title)

```

## 参数：

+ title [string]：窗口标题

## 返回值：

无

## 示例
```lua

Window = UsingModule("EtherWindow")
local window = Window.CreateWindow("test1", {x = 100, y = 100, w = 960, h = 640}, {})
window:SetWindowTitle("EtherEngineX")

```