### [[ << 回到上层 ]](README.md)

# Listener:GetName

> 获取该监听者的名称

```lua

name = listener:GetName()

```

## 参数：

+ listener [userdata-Listener]：监听者对象

## 返回值：

+ name [string]：监听者名称

## 示例

```lua

Event = UsingModule("EtherEvent")
local listener = Event.CreateMouseListener("十六夜咲夜")
local name = listener:GetName()

```