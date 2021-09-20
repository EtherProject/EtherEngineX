### [[ << 回到上层 ]](README.md)

# Image:SetImageDynamic

> 设置图片是否为动态

```lua

image:SetImageDynamic(isDynamic, frameAmount, width, height)

```

## 参数：

+ image [userdata-Image]：图像数据

+ isDynamic [boolean]：是否为动态

+ frameAmount [number]：帧总数量

+ width [number]：图像宽度

+ height [number]：图像高度

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local image = Graphic.LoadImageFromFile("test.png")
image:SetImageDynamic(true, 4, 100, 100)

```

## 作者的话
> EtherEngineX还没有播放GIF图片的功能，该动图的原理是从一张图片中读取出每帧的图片
> 该动图的每帧大小应该相同，且以从左往右，从上往下的顺序排列，最后一行可留空
> 设置一张图片为动图时你应该告诉EtherEngineX一共有多少帧(第二个参数)，以及每帧图片的大小(第三第四个参数)