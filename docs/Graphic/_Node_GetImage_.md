### [[ << 回到上层 ]](README.md)

# Node:GetImage

> 获取节点当前的图像

```lua

image = node.GetImage()

```

## 参数：

+ image [userdata-Image]：图像对象

## 返回值：

+ node [userdata-Node]：节点对象

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local node = Graphic.CreateNode()
local image = node.GetImage()

```