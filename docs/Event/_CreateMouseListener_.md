### [[ << 回到上层 ]](README.md)

# CreateMouseListener

> 创建监听鼠标的监听者

```lua

listener = CreateMouseListener(name)

```

## 参数：

+ name [string]：监听者名称

## 返回值：

+ listener [userdata-Listener]：监听者对象

## 示例

```lua

Event = UsingModule("EtherEvent")
local listener = Event.CreateMouseListener("十六夜咲夜")

```