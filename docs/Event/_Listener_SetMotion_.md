### [[ << 回到上层 ]](README.md)

# Listener:SetMotion

> 设置鼠标移动的回调函数(鼠标监听者)

```lua

listener:SetMotion(callback)

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
listener:SetMotion(function()
    print("Oh, it seems that the cursor is moving!")
end)

```