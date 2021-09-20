### [[ << 回到上层 ]](README.md)

# Image:SetAnchorPoint

> 设置图像对象的锚点(即旋转绕着的点)

```lua

image:SetAnchorPoint(point)

```

## 参数：

+ image [userdata-Image]：图像对象

+ point [point]：坐标位置

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local image = Graphic.LoadImageFromFile("test.png")
image:SetAnchorPoint({x = 114, y = 514})

```