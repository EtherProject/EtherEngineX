# EtherEngineX开发者文档(版本：1.0.0 Beta)

+ 由于引擎自身原因(内存管理功能欠缺及其他原因)，开发者在使用中请留意每个模块的注意事项

## 模块索引

+ [Window](Window/README.md)：窗口相关操作

+ [Graphic](Graphic/README.md)：图形相关操作

+ [Sprite](Sprite/README.md)：精灵相关操作

+ [Action](Action/README.md)：动作相关操作

+ [Event](Graphic/README.md)：交互相关操作

+ [Media](Media/README.md)：媒体相关操作

## 全局函数

+ UsingModule(name)

    + 注意事项：使用UsingModule(name)加载的模块访问内部对象应使用 `.`，例如：Window.CreateWindow(...)
    + 而使用模块内部的函数对象创建返回的对象成员的成员函数应使用 `:`，例如：window:AddNode(sprite1)

    + 功能：启用指定内置模块或加载外部模块
    + 参数：模块名（`string`）
    + 返回值：模块内容（`table`）

+ GetVersion()

    + 功能：获取当前引擎版本号
    + 参数：无
    + 返回值：当前引擎版本号（`string`）

## 启动配置

引擎启动时将默认加载同一目录下的 `config.json` 作为配置文件

文档中测试示例的配置文件如下

```json
{
    "entry": "Main.lua",
    "scene": [
        {"name" : "Main.lua", "nextScene" : ["test.lua"]},
        {"name" : "test.lua", "nextScene" : []}
    ]
}
```

+ `entry` 入口文件，支持相对于.exe文件的目录
+ `scene` 场景关系，指定某个场景可以前往的下一个场景

## 附录

> 常用结构体内部成员简介

+ 矩形：

    + x [number]：矩形左上角顶点x坐标
    + y [number]：矩形左上角顶点y坐标
    + w [number]：矩形宽度
    + h [number]：矩形高度

+ 点：

    + x [number]：点x坐标
    + y [number]：点y坐标

+ 颜色：

    + r [number]：颜色的红色分量
    + g [number]：颜色的绿色分量
    + b [number]：颜色的蓝色分量
    + a [number]：颜色的透明度