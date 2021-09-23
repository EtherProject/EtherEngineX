### [[ << 回到上层 ]](README.md)

# CheckMusicPlaying

> 判断当前音乐是否正在播放

```lua

flag = CheckMusicPlaying()

```

## 参数：

无

## 返回值：

+ flag [boolean]：是否正在播放

## 示例

```lua

Media = UsingModule("EtherMedia")
local music = Media.LoadMusic("test.mp3")
music:Play(-1)
local isPlaying = Media.CheckMusicPlaying()

```