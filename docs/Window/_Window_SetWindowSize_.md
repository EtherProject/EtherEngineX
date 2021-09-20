### [[ << 回到主页 ]](README.md)

# Window:SetWindowSize

> 设置该窗口的大小

```lua

window:SetWindowSize(width, height)

```

## 参数：

+ window [userdata-Window]：窗口对象
+ width [number]：宽度
+ height [number]：高度

## 返回值：

无

## 示例
```lua

Window = UsingModule("EtherWindow")
local window = Window.CreateWindow("test1", {x = 100, y = 100, w = 960, h = 640}, {})
window:SetWindowSize(200, 200)

```