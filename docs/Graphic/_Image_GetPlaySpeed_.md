### [[ << 回到上层 ]](README.md)

# Image:GetPlaySpeed

> 获取属性为动态的图像的帧切换速度(speed 帧/次)

```lua

speed = image:GetPlaySpeed()

```

## 参数：

+ image [userdata-Image]：图像对象

## 返回值：

+ speed [number]：帧切换速度

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local image = Graphic.LoadImageFromFile("test.png")
local speed = image:GetPlaySpeed()

```