### [[ << 回到上层 ]](README.md)

# Image:GetAngle

> 获取图像的旋转角度

```lua

angle = image:GetAngle()

```

## 参数：

+ image [userdata-Image]：图像对象

## 返回值：

+ angle [number]：旋转角度

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local image = Graphic.LoadImageFromFile("test.png")
local angle = image:GetAngle()

```