### [[ << 回到上层 ]](README.md)

# Image:SetRendererFlip

> 设置图像的翻转模式

```lua

image:SetRendererFlip(mode)

```

## 参数：

+ image [userdata-Image]：图像对象

+ mode [enum-class]：翻转模式

    + FLIP_HORIZONTAL：水平翻转
    + FLIP_VERTICAL：垂直翻转
    + FLIP_NONE：无翻转

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local image = Graphic.LoadImageFromFile("test.png")
image:SetRendererFlip(Graphic.FLIP_VERTICAL)

```