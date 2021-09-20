### [[ << 回到上层 ]](README.md)

# Window:SetWindowOpacity

> 设置窗口的不透明度

```lua

window:SetWindowOpacity(value)

```

## 参数：

+ window [userdata-Window]：窗口对象

+ value [number]：不透明值，取值范围0-1

## 返回值：

无

## 示例

```lua

Window = UsingModule("EtherWindow")
local window = Window.CreateWindow("test1", {x = 100, y = 100, w = 960, h = 640}, {})
window:SetWindowOpacity(0.5)

```