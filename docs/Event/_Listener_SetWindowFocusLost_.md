### [[ << 回到上层 ]](README.md)

# Listener:SetWindowFocusLost

> 设置鼠标离开窗口范围时的回调函数(窗口监听者)

```lua

listener:SetWindowFocusLost(callback)

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
listener:SetWindowFocusLost(function()
    print("Oh, I lost your attention!")
end)

```