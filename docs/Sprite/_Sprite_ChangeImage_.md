### [[ << 回到上层 ]](README.md)

# Sprite:ChangeImage

> 切换精灵当前图像为图像列表中指定索引处图像

```lua

sprite:ChangeImage(index)

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
sprite:ChangeImage(1)

```