### [[ << 回到主页 ]](README.md)

# Window:SetWindowMode

> 设置该窗口的样式

```lua

window:SetWindowMode(mode)

```

## 参数：

+ window [userdata-Window] 窗口对象

+ mode [enum-class]：窗口模式，模式可以为以下值：

    + WINDOW_MODE_WINDOWED：窗口模式
    + WINDOW_MODE_FULLSCREEN：全屏（视频输出模式更改的真全屏）模式
    + WINDOW_MODE_FULLSCREEN_DESKTOP：全屏（将窗口拉伸至屏幕分辨率大小的伪全屏）模式
    + WINDOW_MODE_BORDERLESS：窗口无边框
    + WINDOW_MODE_BORDERED：窗口有边框
    + WINDOW_MODE_RESIZABLE：窗口大小可变
    + WINDOW_MODE_SIZEFIXED：窗口大小固定

## 返回值：

无

## 示例
```lua

Window = UsingModule("EtherWindow")
local window = Window.CreateWindow("test1", {x = 100, y = 100, w = 960, h = 640}, {})
window:SetWindowMode(WINDOW_MODE_WINDOWED)

```