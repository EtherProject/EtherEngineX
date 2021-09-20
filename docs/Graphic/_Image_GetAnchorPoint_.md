### [[ << 回到上层 ]](README.md)

# Image:GetAnchorPoint

> 获取图像对象的锚点

```lua

image:GetAnchorPoint()

```

## 参数：

+ image [userdata-Image]：图像对象

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local image = Graphic.LoadImageFromFile("test.png")
local point = image:GetAnchorPoint()
print(point.x, point.y)

```