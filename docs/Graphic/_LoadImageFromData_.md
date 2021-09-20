### [[ << 回到上层 ]](README.md)

# LoadImageFromData

> 从缓冲区中加载图像

```lua

image = LoadImageFromData(data)

```

## 参数：

+ data [string]：缓冲区数据

## 返回值：

+ image [userdata-Image]：图像对象

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local image = Graphic.LoadImageFromFile("test.png")

```