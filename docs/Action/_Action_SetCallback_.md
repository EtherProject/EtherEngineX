### [[ << 回到上层 ]](README.md)

# Action:SetCallback

> 修改该动作对象的回调函数

```lua

action:SetCallback(callback)

```

## 参数：

+ action [userdata-Action]：动作对象

+ callback [function]：回调函数

## 返回值：

无

## 示例

```lua

Action = UsingModule("EtherAction")
local action = Action.CreateMoveTo({x = 200, y = 200}, 4)
action:SetCallback(funciton()
    print("Callback~")
end)

```