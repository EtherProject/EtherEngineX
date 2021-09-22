### [[ << 回到上层 ]](README.md)

# Action:ModifyTime

> 修改该动作对象的持续时间

```lua

action:ModifyTime(5)

```

## 参数：

+ action [userdata-Action]：动作对象

+ time [time]：持续时间

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local action = Graphic.CreateMoveTo({x = 200, y = 200}, 4)
action:ModifyTime(6)

```