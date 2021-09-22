### [[ << 回到上层 ]](README.md)

# Font:SetKerning

> 设置已加载字体的间距

```lua

font:GetKerning(kerning)

```

## 参数：

+ font [userdata-Font]：字体对象

+ kerning [number]：字体间距

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local font = Graphic.LoadFontFromFile("simhei.ttf")
font:GetKerning(20)

```