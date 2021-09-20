### [[ << 回到上层 ]](README.md)

# LoadFontFromData

> 从缓冲区中加载字体

```lua

font = LoadFontFromData(data, size)

```

## 参数：

+ data [string]：缓冲区数据

+ size [number]：字体大小

## 返回值：

+ font [userdata-Font]：字体对象

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local font = Graphic.LoadFontFromData("msyh.ttf", 50)

```