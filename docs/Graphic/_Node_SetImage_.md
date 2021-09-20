### [[ << 回到上层 ]](README.md)

# Node:SetImage

> 设置节点当前的图像

```lua

node.SetImage(image)

```

## 参数：

+ node [userdata-Node]：节点对象

+ image [userdata-Image]：图像对象

## 返回值：

无

## 示例

```lua

Window = UsingModule("EtherWindow“)

Graphic = UsingModule("EtherGraphic")

local window = Window.CreateWindow(
    "test",
    {x = Window.WINDOW_POSITION_DEFAULT,
    y = Window.WINDOW_POSITION_DEFAULT,
    w = 200,
    h = 200},
    {})

local node = Graphic.CreateNode()

window:AddNode(node)

local image = Graphic.LoadImageFromFile("test.png")

node:SetImage(image)

```

## 作者的话

> EtherEngineX负责渲染图像的函数在节点里，而节点想要绘制图像必须获取一个渲染器

> 只有当你把节点加入到某一个窗口中的时候，他才能获取渲染器

> 这之后才能使用SetImage函数来为Node设置图像