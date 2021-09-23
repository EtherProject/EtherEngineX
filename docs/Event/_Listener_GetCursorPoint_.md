### [[ << 回到上层 ]](README.md)

# Listener:GetCursorPoint

> 获取鼠标当前的坐标(鼠标监听者)

```lua

point = listener:GetCursorPoint()

```

## 参数：

+ listener [userdata-Listener]：监听者对象

## 返回值：

+ point [point]：光标坐标

## 示例

```lua

Event = UsingModule("EtherEvent")
local listener = Event.CreateMouseListener("十六夜咲夜")

listener:SetMotion(function()
    local point = listener:GetCursorPoint()
    print(point.x, point.y)
end)

```