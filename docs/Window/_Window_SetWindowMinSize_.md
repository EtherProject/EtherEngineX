### [[ << 回到主页 ]](README.md)

# Window:SetWindowMinSize

> 设置该窗口最小尺寸的大小

```lua

window:SetWindowMinSize(width, height)

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
window:SetWindowMinSize(200, 200)

```