### [[ << 回到主页 ]](README.md)

# Window:SetWindowPosition

> 设置窗口的坐标位置

```lua

window:GetWindowPosition(point)

```

## 参数：

window [userdata-Window]：窗口对象
point [point]：坐标位置

## 返回值：

无

## 示例
```lua

Window = UsingModule("EtherWindow")
local window = Window.CreateWindow("test1", {x = 100, y = 100, w = 960, h = 640}, {})
window:SetWindowPosition(200, 200)

```