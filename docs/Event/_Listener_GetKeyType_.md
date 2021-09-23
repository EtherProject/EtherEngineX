### [[ << 回到上层 ]](README.md)

# Listener:GetKeyType

> 获取键盘上当前按下的按键

```lua

type = listener:GetKeyType()

```

## 参数：

+ listener [userdata-Listener]：监听者对象

## 返回值：

+ type [enum-class]：按键类型

    + [附录(所有按键类型)](_Key_Type_.md)

## 示例

```lua

Event = UsingModule("EtherEvent")
local listener = Event.CreateKeyboardListener("十六夜咲夜")
listener:SetKeyDown(function()
    if listener:GetKeyType() == Event.KEY_X then
        print("封魔阵!")
    end
end)

```