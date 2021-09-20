### [[ << 回到上层 ]](README.md)

# LoadFontFromFile

> 从文件中加载字体

```lua

font = LoadFontFromFile(path)

```

## 参数：

+ path [string]：文件路径及文件名

## 返回值：

+ font [userdata-Font]：字体对象

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local font = Graphic.LoadFontFromFile("msyh.ttf")

```