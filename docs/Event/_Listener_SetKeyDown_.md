### [[ << 回到上层 ]](README.md)

# Listener:SetKeyDown

> 设置键盘按键按下时的回调函数(鼠标监听者)

```lua

listener:SetKeyDown(callback)

```

## 参数：

+ listener [userdata-Listener]：监听者对象

+ callback [function]：回调函数

## 返回值：

无

## 示例

```lua

Event = UsingModule("EtherEvent")
local listener = Event.CreateKeyboardListener("十六夜咲夜")
listener:SetKeyDown(function()
    print("Wow! I got a keyboard's event!It's down")
end)

```