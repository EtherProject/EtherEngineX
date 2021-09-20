### [[ << 回到主页 ]](README.md)

# Window:GetWindowPosition

> 获取窗口的坐标位置

```lua

point = window:GetWindowPosition()

```

## 参数：

window [userdata-Window]：窗口对象

## 返回值：

point [point]：坐标位置

## 示例
```lua

Window = UsingModule("EtherWindow")
local window = Window.CreateWindow("test1", {x = 100, y = 100, w = 960, h = 640}, {})
local point = window:GetWindowPosition()
print(point.x, point.y)

```