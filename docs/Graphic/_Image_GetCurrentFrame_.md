### [[ << 回到上层 ]](README.md)

# Image:GetCurrentFrame

> 获取属性为动态的图像的当前帧

```lua

frame = image:GetCurrentFrame()

```

## 参数：

+ image [userdata-Image]：图像对象

## 返回值：

+ frame [number]：当前帧

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local image = Graphic.LoadImageFromFile("test.png")
local frame = image:GetCurrentFrame()

```