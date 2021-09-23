### [[ << 回到上层 ]](README.md)

# Music:PlayWithFadeIn

> 使用淡入效果播放已加载的音乐

```lua

Music:PlayWithFadeIn(times, delay)

```

## 参数：

+ music [userdata-Music]：音乐数据

+ times [number]：音乐播放的次数，-1为循环播放

+ delay [number]：淡入音效持续时间，单位为毫秒

## 返回值：

无

## 示例

```lua

Media = UsingModule("EtherMedia")
local music = Media.LoadMusic("test.mp3")
music:PlayWithFadeIn(-1)

```