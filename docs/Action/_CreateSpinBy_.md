### [[ << 回到上层 ]](README.md)

# CreateSpinBy

> 创建旋转一定角度的动作对象

```lua

action = CreateSpinBy(angle, time)

```

## 参数：

+ angle [number]：指定角度

+ time [time]：持续时间

## 返回值：

+ action [userdata-Action]：动作对象

## 示例

```lua

Graphic = UsingModule("EtherGraphic")
local action = Graphic.CreateSpinBy(720, 4)

```

## 作者的话

> 示例的动作可以让任意一个使用他的节点在4秒内旋转720°
> 如果旋转角度值为负数则逆时针旋转