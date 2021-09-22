### [[ << 回到上层 ]](README.md)

# Sprite:DeleteImage

> 删除精灵的图像队列中指定索引处的图像

```lua

sprite:DeleteImage(index)

```

## 参数：

+ sprite [userdata-Sprite]：精灵对象

+ index [number]：索引

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local sprite = Graphic.CreateSprite()
local image = Graphic.LoadImageFromFile("test.png")
sprite:AddImage(image)
sprite:DeleteImage(1)

```