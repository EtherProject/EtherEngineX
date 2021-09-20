### [[ << 回到上层 ]](README.md)

# Image:GetAlpha

> 获取图像Alpha通道的值

```lua

local alpha = image:GetAlpha()

```

## 参数：

+ image [userdata-Image]：图像对象

## 返回值：

+ alpha [number]：图像Alpha通道的值

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local image = Graphic.LoadImageFromFile("test.png")
local alpha = image:GetAlpha()

```