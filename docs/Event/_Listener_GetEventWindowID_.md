### [[ << 回到上层 ]](README.md)

# Listener:GetEventWindowID

> 获取事件发生的窗口的ID(窗口监听者)

```lua

id = listener:GetEventWindowID()

```

## 参数：

+ listener [userdata-Listener]：监听者对象

## 返回值：

+ id [number]：窗口ID

## 示例

```lua

Event = UsingModule("EtherEvent")
local listener = Event.CreateWindowListener("十六夜咲夜")
local id = listener:GetEventWindowID()

```