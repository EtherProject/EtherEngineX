### [[ << 回到上层 ]](README.md)

# CreateScaleTo

> 创建放大或缩小到指定尺寸的动作对象

```lua

action = CreateScaleTo(w, h, time)

```

## 参数：

+ w [number]：指定宽度

+ h [number]：指定高度

+ time [time]：持续时间

## 返回值：

+ action [userdata-Action]：动作对象

## 示例

```lua

Action = UsingModule("EtherAction")
local action = Action.CreateScaleTo(200, 200, 4)

```

## 作者的话

> 示例的动作可以让任意一个使用他的节点在4秒内变为宽为200个像素，200个像素的图像