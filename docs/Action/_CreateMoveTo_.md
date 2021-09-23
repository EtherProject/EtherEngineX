### [[ << 回到上层 ]](README.md)

# CreateMoveTo

> 创建移动到指定位置的动作对象

```lua

action = CreateMoveTo(point, time)

```

## 参数：

+ point [point]：指定坐标

+ time [time]：持续时间

## 返回值：

+ action [userdata-Action]：动作对象

## 示例

```lua

Action = UsingModule("EtherAction")
local action = Graphic.CreateMoveTo({x = 50, y = 50}, 4)

```

## 作者的话

> 示例的动作可以让任意一个使用他的节点在4秒内移动到坐标值为{x = 50, y = 50}的位置