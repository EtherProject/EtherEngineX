### [[ << 回到上层 ]](README.md)

# Sprite:AddImage

> 向精灵的图像队列中添加图像

```lua

sprite:AddImage(image)

```

## 参数：

+ sprite [userdata-Sprite]：精灵对象

+ image [userdata-Image]：图像对象

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local sprite = Graphic.CreateSprite()
local image = Graphic.LoadImageFromFile("test.png")
sprite:AddImage(image)

```