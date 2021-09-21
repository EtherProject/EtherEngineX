### [[ << 回到上层 ]](README.md)

# Node:GetDepth

> 获取该节点的深度(值越小越先绘制)

```lua

depth = node:GetDepth()

```

## 参数：

+ node [userdata-Node]：节点对象

## 返回值：

+ depth [number]：绘制深度

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local node = Graphic.CreateNode()
local depth = node:GetDepth()

```