### [[ << 回到上层 ]](README.md)

# Listener:GetKeyMod

> 获取键盘上按下键的修饰键

```lua

type = listener:GetKeyMod()

```

## 参数：

+ listener [userdata-Listener]：监听者对象

## 返回值：

+ type [enum-class]：按键类型

    + KEY_MOD_NONE：无状态

    + KEY_MOD_NUM：数字键修饰

    + KEY_MOD_CAPS：大写锁定修饰

    + KEY_MOD_RESERVED：RESERVED键修饰

    + KEY_MOD_SHIFT：SHIFT键修饰

        + KEY_MOD_LSHIFT：左SHIFT键

        + KEY_MOD_RSHIFT：右SHIFT键

    + KEY_MOD_CTRL：CTRL键修饰

        + KEY_MOD_LCTRL：左CTRL键

        + KEY_MOD_RCTRL：右CTRL键

    + KEY_MOD_ALT：ALT键修饰

        + KEY_MOD_LALT：左ALT键

        + KEY_MOD_RALT：右ALT键

    + KEY_MOD_GUI：GUI键修饰

        + KEY_MOD_LGUI：左GUI键

        + KEY_MOD_RGUI：右GUI键

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