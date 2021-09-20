### [[ << 回到上层 ]](README.md)

# Image:SetPlaySpeed

> 设置属性为动态的图像的帧切换速度

```lua

image:SetPlaySpeed(speed)

```

## 参数：

+ image [userdata-Image]：图像对象

+ speed [number]：帧切换速度

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local image = Graphic.LoadImageFromFile("test.png")
image:SetPlaySpeed(5)

```

## 作者的话
> 帧切换速度的默认值为60
> 所以如果不设置的话，引擎就会每过60帧的时间把动图切换到下一帧