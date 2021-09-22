### [[ << 回到上层 ]](README.md)

# Font:GetTextSize

> 获取已加载字体的大小

```lua

width, height = font:GetTextSize()

```

## 参数：

+ font [userdata-Font]：字体对象

## 返回值：

+ width [number]：字体宽度

+ height [number]：字体高度

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local font = Graphic.LoadFontFromFile("simhei.ttf")
local width, height = font:GetTextSize()

```