### [[ << 回到上层 ]](README.md)

# CreateSpinTo

> 创建旋转到指定角度的动作对象

```lua

action = CreateSpinTo(angle, time, direction)

```

## 参数：

+ angle [number]：指定角度

+ time [time]：持续时间

+ direction [enum-class]：旋转方向

    + ROTATION_CLOCKWISE：顺时针方向
    + RORATION_ANTI_CLOCKWISE：逆时针方向

## 返回值：

+ action [userdata-Action]：动作对象

## 示例

```lua

Action = UsingModule("EtherAction")
local action = Action.CreateSpinTo(60, 4, ROTATION_ANTI_CLOCKWISE)

```

## 作者的话

> 示例的动作可以让任意一个使用他的节点在4秒内逆时针移动到60°