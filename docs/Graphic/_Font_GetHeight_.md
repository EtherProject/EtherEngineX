### [[ << 回到上层 ]](README.md)

# Font:GetHeight

> 获取已加载字体的高度

```lua

height = font:GetHeight()

```

## 参数：

+ font [userdata-Font]：字体对象

## 返回值：

+ height [number]：字体高度

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local font = Graphic.LoadFontFromFile("simhei.ttf")
local height = font:GetHeight()

```