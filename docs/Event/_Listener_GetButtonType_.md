### [[ << 回到上层 ]](README.md)

# Listener:GetButtonType

> 获取鼠标当前按下的键(鼠标监听者)

```lua

type = listener:GetButtonType()

```

## 参数：

+ listener [userdata-Listener]：监听者对象

## 返回值：

+ type [enum-class]：按键类型

    + MOUSE_LEFTBUTTON：鼠标左键
    + MOUSE_MIDDLEBUTTON：鼠标中键
    + MOUSE_RIGHTBUTTON：鼠标右键

## 示例

```lua

Event = UsingModule("EtherEvent")
local listener = Event.CreateMouseListener("十六夜咲夜")

listener:SetCallDown(function()
    if listener:GetButtonType() == MOUSE_LEFTBUTTON then
        print("What? Left button down!?")
    end
end)

```