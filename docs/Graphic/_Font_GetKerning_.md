### [[ << 回到上层 ]](README.md)

# Font:GetKerning

> 获取已加载字体的间距

```lua

kerning = font:GetKerning()

```

## 参数：

+ font [userdata-Font]：字体对象

## 返回值：

+ kerning [number]：字体间距

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local font = Graphic.LoadFontFromFile("simhei.ttf")
local kerning = font:GetKerning()

```