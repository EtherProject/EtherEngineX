### [[ << 回到上层 ]](README.md)

# ResumeMusic

> 恢复当前暂停状态的音乐

```lua

ResumeMusic()

```

## 参数：

无

## 返回值：

无

## 示例

```lua

Media = UsingModule("EtherMedia")
local music = Media.LoadMusic("test.mp3")
music:Play(-1)
Media.ResumeMusic()

```