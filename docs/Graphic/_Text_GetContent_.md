### [[ << 回到上层 ]](README.md)

# Text:GetContent

> 获取文本图像的文本内容

```lua

content = text:GetContent()

```

## 参数：

+ text [userdata-Text]：文本对象

## 返回值：

+ content [string]：文本内容

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local font = Graphic.LoadFontFromFile("simhei.ttf")
local text = Graphic.CreateTextImage(font, "东方Project", {r = 255, g = 0, b = 0}, Graphic.TEXT_PATTERN_BLENDED, Graphic.CODE_FORMAT_UTF8)
local content = text:GetContent()

```