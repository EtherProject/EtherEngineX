### [[ << 回到上层 ]](README.md)

# Image:SetAngle

> 设置图像的旋转角度

```lua

image:SetAngle(angle)

```

## 参数：

+ image [userdata-Image]：图像对象

+ angle [number]：旋转角度

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local image = Graphic.LoadImageFromFile("test.png")
image:SetAngle(angle)

```