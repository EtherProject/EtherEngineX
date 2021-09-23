### [[ << 回到上层 ]](README.md)

# CreateKeyboardListener

> 创建监听键盘的监听者

```lua

listener = CreateKeyboardListener(name)

```

## 参数：

+ name [string]：监听者名称

## 返回值：

+ listener [userdata-Listener]：监听者对象

## 示例

```lua

Event = UsingModule("EtherEvent")
local listener = Event.CreateKeyboardListener("十六夜咲夜")

```