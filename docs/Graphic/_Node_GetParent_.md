### [[ << 回到上层 ]](README.md)

# Node:GetParent

> 获取节点的父节点

```lua

nodeParent = nodeChild.GetParent()

```

## 参数：

+ nodeChild [userdata-Node]：节点对象

## 返回值：

+ nodeParent [userdata-Node]：节点对象

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local nodeChild = Graphic.CreateNode()
local testParent = Graphic.CreateNode()
local nodeChild.SetParent(testParent)
local nodeParent = Graphic.GetParent()

```