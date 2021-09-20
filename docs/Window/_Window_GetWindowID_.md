### [[ << 回到主页 ]](README.md)

# Window:GetWindowID

> 获取窗口的ID

```lua

ID = window:GetWindowID()

```

## 参数：

window [userdata-Window]：窗口对象

## 返回值：

id [number]：窗口ID

## 示例
```lua

Window = UsingModule("EtherWindow")
local window = Window.CreateWindow("test1", {x = 100, y = 100, w = 960, h = 640}, {})
local id = window:GetWindowID()

```