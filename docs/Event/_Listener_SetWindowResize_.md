### [[ << 回到上层 ]](README.md)

# Listener:SetWindowResize

> 设置窗口尺寸改变时的回调函数(窗口监听者)

```lua

listener:SetWindowResize(callback)

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
listener:SetWindowResize(function()
    print("Ohhhhh, I'm resized")
end)

```