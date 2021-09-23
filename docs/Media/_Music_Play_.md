### [[ << 回到上层 ]](README.md)

# Music:Play

> 播放已加载的音乐

```lua

Music:Play(times)

```

## 参数：

+ music [userdata-Music]：音乐数据

+ times [number]：音乐播放的次数，-1为循环播放

## 返回值：

无

## 示例

```lua

Media = UsingModule("EtherMedia")
local music = Media.LoadMusic("test.mp3")
music:Play(-1)

```