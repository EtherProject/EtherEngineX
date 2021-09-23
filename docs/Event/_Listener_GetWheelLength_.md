### [[ << 回到上层 ]](README.md)

# Listener:GetWheelLength

> 获取鼠标滚轮滚动的距离(鼠标监听者)

```lua

wheelLength = listener:GetWheelLength()

```

## 参数：

+ listener [userdata-Listener]：监听者对象

## 返回值：

+ wheelLength [table]：滚轮状态信息，包含以下成员

    + x [number]：鼠标滚轮在x轴上滚动的距离

    + y [number]：鼠标滚轮在y轴上滚动的距离

    + direction [number]：鼠标滚轮滚动的方向

        + MOUSE_WHEEL_NORMAL：正方向，x轴上是向右，y轴上是向下
        + MOUSE_WHEEL_FLIPPED：反方向，x轴上是向左，y轴上是向上

## 示例

```lua

Event = UsingModule("EtherEvent")
local listener = Event.CreateMouseListener("十六夜咲夜")
listener:SetMotion(function()
    local wheelLength = listener:GetWheelLength()
    if wheelLength.direction == MOUSE_WHEEL_NORMAL then
        print(wheelLength.x, wheelLength.y)
    end
end)

```