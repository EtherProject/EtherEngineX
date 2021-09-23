### [[ << 回到上层 ]](README.md)

# Listener:SetWindowMove

> 设置窗口移动时的回调函数(窗口监听者)

```lua

listener:SetWindowMove(callback)

```

## 参数：

+ listener [userdata-Listener]：监听者对象

+ callback [function]：回调函数

## 返回值：

无

## 示例

```lua

Event = UsingModule("EtherEvent")
local listener = Event.CreateWindowListener("十六夜咲夜")
listener:SetWindowMove(function()
    print("Ohhhhh, I'm moving!")
end)

```