### [[ << 回到上层 ]](README.md)

# GetMusicVolume

> 获取当前音乐播放的音量

```lua

volume = GetMusicVolume()

```

## 参数：

无

## 返回值：

+ volume [number]：音量大小，取值范围为0-128

## 示例

```lua

Media = UsingModule("EtherMedia")
local music = Media.LoadMusic("test.mp3")
music:Play(-1)
local volume = Media.GetMusicVolume()

```