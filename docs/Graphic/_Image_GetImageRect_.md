### [[ << 回到上层 ]](README.md)

# Image:GetImageRect

> 获取图像截取的矩形

```lua

rect = image:GetImageRect()

```

## 参数：

+ image [userdata-Image]：图像对象

## 返回值：

+ rect [rect]：截取原图片的矩形

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local image = Graphic.LoadImageFromFile("test.png")
local rect = image:GetImageRect()

```