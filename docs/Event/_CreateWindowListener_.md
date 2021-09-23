### [[ << 回到上层 ]](README.md)

# CreateWindowListener

> 创建监听窗口的监听者

```lua

listener = CreateWindowListener(name)

```

## 参数：

+ name [string]：监听者名称

## 返回值：

+ listener [userdata-Listener]：监听者对象

## 示例

```lua

Event = UsingModule("EtherEvent")
local listener = Event.CreateWindowListener("十六夜咲夜")

```