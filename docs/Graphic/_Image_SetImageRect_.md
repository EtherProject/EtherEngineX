### [[ << 回到上层 ]](README.md)

# Image:SetImageRect

> 设置图像截取的矩形

```lua

image:SetImageRect(rect)

```

## 参数：

+ image [userdata-Image]：图像对象

+ rect [rect]：截取原图片的矩形

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local image = Graphic.LoadImageFromFile("test.png")
image:SetImageRect({x = 0, y = 0, w = 300, h = 300})

```