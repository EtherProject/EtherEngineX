### [[ << 回到上层 ]](README.md)

# Node:RunAction

> 让该节点运行参数中的动作(接受任意数量的动作参数)

```lua

node:RunAction(action1, action2, action3...)

```

## 参数：

+ node [userdata-Node]：节点对象

+ action, action2, action3.... [userdata-Node]：动作对象

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
Action = UsingModule("EtherAction")
local node = Graphic.CreateNode()
local action1 = Action.CreateMoveTo({x = 50, y = 50}, 3)
local action2 = Action.CreateMoveBy({x = 100, y = 100}, 3)
node:RunAction(action1, action2)

```