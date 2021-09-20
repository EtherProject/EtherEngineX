### [[ << 回到主页 ]](README.md)

# Window:DeleteNode

> 删除节点列表中指定索引的节点

```lua

window:DeleteNode(index)

```

## 参数：

window [userdata-Window]：窗口对象
index [number]：数字索引

## 返回值：

无

## 示例
```lua

Graphic = UsingModule("EtherGraphic)
Window = UsingModule("EtherWindow")
local window = Window.CreateWindow("test1", {x = 100, y = 100, w = 960, h = 640}, {})
local node = Graphic.CreateNode()
window:AddNode(node)
window:DeleteNode(1)

```