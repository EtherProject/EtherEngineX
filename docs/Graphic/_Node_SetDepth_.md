### [[ << 回到上层 ]](README.md)

# Node:SetDepth

> 设置该节点的深度(值越小越先绘制)

```lua

node:SetDepth(depth)

```

## 参数：

+ node [userdata-Node]：节点对象

+ depth [number]：绘制深度

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local nodeAbove = Graphic.CreateNode()
local nodeBeneath = Graphic.CreateNode()
nodeAbove:SetDepth(1)
nodeBeneath:SetDepth(2)

```

## 作者的话
> 节点深度越小，该节点的位置接近用户
> 所以深度小的节点会将深度大的节点覆盖