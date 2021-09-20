### [[ << 回到上层 ]](README.md)

# LoadImageFromFile

> 从文件中加载图像

```lua

image = LoadImageFromFile(path)

```

## 参数：

+ path [string]：文件路径及文件名

## 返回值：

+ image [userdata-Image]：图像对象

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local image = Graphic.LoadImageFromFile("test.png")

```