### [[ << 回到上层 ]](README.md)

# RemoveListener

> 删除指定名称的监听者

```lua

RemoveListener(name)

```

## 参数：

+ name [string]：监听者名称

## 返回值：

无

## 示例

```lua

Event = UsingModule("EtherEvent")
local listener = Event.CreateMouseListener("十六夜咲夜")
Event.RemoveListener("十六夜咲夜")

```