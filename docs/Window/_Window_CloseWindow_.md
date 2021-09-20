### [[ << 回到上层 ]](README.md)

# Window:CloseWindow

> 关闭并删除该窗口对象

```lua

window:CloseWindow()

```

## 参数

+ window [userdata-Window]：窗口对象

## 返回值

+ 无

## 示例
```lua

Window = UsingModule("EtherWindow")
local window = Window.CreateWindow("test1", {x = 100, y = 100, w = 960, h = 640}, {})
window:CloseWindow()

```