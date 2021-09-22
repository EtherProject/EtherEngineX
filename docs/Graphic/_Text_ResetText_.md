### [[ << 回到上层 ]](README.md)

# Text:ResetText

> 重新设置该文本图像

```lua

text:ResetText(font, content, [, color], textPattern, codeFormat)

```

## 参数：

+ text [userdata-Font]：文本对象

+ font [userdata-Font]：字体对象

+ content [string]：文本内容

+ color [color]：颜色，根据textPattern和codeFormat的不同，color的含义也不同

+ textPattern [enum-class]：文本模式

    + TEXT_PATTERN_SOLID：使用 `SOLOD模式` 创建文本
    + 此时 `[, color]` 只有一个参数，表示字体的颜色

    + TEXT_PATTERN_SHADED：使用 `SHADED模式` 创建文本
    + 此时 `[, color]` 有两个参数，第一个表示字体的颜色，第二个表示背景的颜色

    + TEXT_PATTERN_BLENDED：使用 `BLENDED模式` 创建文本
    + 此时 `[, color]` 只有一个参数，表示字体的颜色

+ codeFormat [enum-class]：编码格式

    + CODE_FORMAT_NORMAL：默认编码格式(一般是gbk)

    + CODE_FORMAT_UTF8：UTF-8编码格式

## 返回值：

无

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local font = Graphic.LoadFontFromData("msyh.ttf", 50)
local text = Graphic.CreateTextImage(font, "东方Project", {r = 255, g = 0, b = 0}, Graphic.TEXT_PATTERN_BLENDED, Graphic.CODE_FORMAT_UTF8)
text:ResetText(font, "连缘Project", {r = 0, g = 255, b = 0}, Graphic.TEXT_PATTERN_BLENDED, Graphic.CODE_FORMAT_UTF8)

```