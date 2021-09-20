### [[ << 回到主页 ]](README.md)

# Window:AddNode

> 向窗口的节点列表里添加节点

```lua

window:AddNode(node)

```

## 参数：

window [userdata-Window]：窗口对象
node [userdata-Node]：节点对象

## 返回值：

无

## 示例
```lua

Graphic = UsingModule("EtherGraphic)
Window = UsingModule("EtherWindow")
local window = Window.CreateWindow("test1", {x = 100, y = 100, w = 960, h = 640}, {})
local node = Graphic.CreateNode()
window:AddNode(node)

```