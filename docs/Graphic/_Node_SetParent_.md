### [[ << 回到上层 ]](README.md)

# Node:SetParent

> 设置该节点的父节点

```lua

nodeChild.SetParent(nodeParent)

```

## 参数：

+ nodeChild [userdata-Node]：节点对象

+ nodeParent [userdata-Node]：节点对象

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local nodeChild = Graphic.CreateNode()
local nodeParent = Graphic.CreateNode()
nodeChild.SetParent(nodeParent)

```