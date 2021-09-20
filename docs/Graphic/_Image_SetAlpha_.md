### [[ << 回到上层 ]](README.md)

# Image:SetAlpha

> 设置图像Alpha通道的值

```lua

image:SetAlpha(alpha)

```

## 参数：

+ image [userdata-Image]：图像对象

+ alpha [number]：图像Alpha通道的值，取值范围0-255

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local image = Graphic.LoadImageFromFile("test.png")
image:SetAlpha(114)

```