### [[ << 回到上层 ]](README.md)

# Listener:SetButtonDown

> 设置鼠标按键按下时的回调函数(鼠标监听者)

```lua

listener:SetButtonDown(callback)

```

## 参数：

+ listener [userdata-Listener]：监听者对象

+ callback [function]：回调函数

## 返回值：

无

## 示例

```lua

Event = UsingModule("EtherEvent")
local listener = Event.CreateMouseListener("十六夜咲夜")
listener:SetButtonDown(function()
    print("Hello~ Mouse button down!")
end)

```