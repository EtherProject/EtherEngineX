### [[ << 回到上层 ]](README.md)

# LoadMusic

> 加载音乐文件

```lua

music = LoadMusic(path)

```

## 参数：

+ path [string]：音乐文件路径

## 返回值：

+ music [userdata-Music]：成功则返回音乐数据

## 示例

```lua

Media = UsingModule("EtherMedia")
local music = Media.LoadMusic("test.mp3")
music:Play(-1)

```