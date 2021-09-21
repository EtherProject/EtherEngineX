### [[ << 回到上层 ]](README.md)

# Node:DeleteChild

> 删除该节点的子节点列表中对应索引的节点

```lua

nodeParent:DeleteChild(nodeChild)

```

## 参数：

+ nodeParent [userdata-Node]：节点对象

+ index [number]：索引

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local nodeParent = Graphic.CreateNode()
local nodeChild = Graphic.CreateNode()
nodeParent:AddChild(nodeChild)
nodeParent:DeleteChild(1)

```