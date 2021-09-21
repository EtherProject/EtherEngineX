### [[ << 回到上层 ]](README.md)

# Node:SetPause

> 设置该节点是否持续更新

```lua

node:SetPause(isRunning)

```

## 参数：

+ node [userdata-Node]：节点对象

+ isRunning [boolean]：是否更新

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
Action = UsingModule("EtherAction")
local node = Graphic.CreateNode()
node:SetPause(true)

```