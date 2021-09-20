### [[ << 回到上层 ]](README.md)

# Image:SetCurrentFrame

> 设置属性为动态的图像的当前帧

```lua

image:SetCurrentFrame(frame)

```

## 参数：

+ image [userdata-Image]：图像对象

+ frame [number]：当前帧

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local image = Graphic.LoadImageFromFile("test.png")
image:SetCurrentFrame(3)

```