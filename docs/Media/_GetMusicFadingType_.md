### [[ << 回到上层 ]](README.md)

# GetMusicFadingType

> 获取当前正在播放的音乐的淡化效果类型

```lua

type = GetMusicFadingType()

```

## 参数：

无

## 返回值：

+ type [MACRO number]：淡化效果类型，可能的类型如下：

    + FADING_TYPE_NONE：无淡化效果
    + FADING_TYPE_IN：正在淡入
    + FADING_TYPE_OUT：正在淡出
    
## 示例

```lua

Media = UsingModule("EtherMedia")
local music = Media.LoadMusic("test.mp3")
music:Play(-1)
if Media.GetMusicFadingType() == FADING_TYPE_NONE then
    print("No fading type!")
end

```