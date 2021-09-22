### [[ << 回到上层 ]](README.md)

# CreateMoveBy

> 创建移动到一定距离的动作对象

```lua

action = CreateMoveBy(distance, time)

```

## 参数：

+ distance [point]：指定距离

+ time [time]：持续时间

## 返回值：

+ action [userdata-Action]：动作对象

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local action = Graphic.CreateMoveBy({x = 100, y = 100}, 4)

```

## 作者的话

> 示例的动作可以让任意一个使用他的节点在4秒内在x轴上移动100个像素，在y轴上移动100个像素