### [[ << 回到上层 ]](README.md)

# Node:AddChild

> 向该节点的子节点列表中添加一个子节点

```lua

nodeParent:AddChild(nodeChild)

```

## 参数：

+ nodeParent [userdata-Node]：节点对象

+ nodeChild [userdata-Node]：节点对象

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local nodeParent = Graphic.CreateNode()
local nodeChild = Graphic.CreateNode()
nodeParent:AddChild(nodeChild)

```