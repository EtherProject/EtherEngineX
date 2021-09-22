### [[ << 回到主页 ]](../README.md)

# Graphic

> Graphic 模块提供窗口相关操作

## 模块函数列表

+ [LoadImageFromFile(path)](_LoadImageFromFile_.md)：从文件中加载图像

+ [LoadImageFromData(data)](_LoadImageFromData_.md)：从缓冲区中加载图像

+ [CreateNode()](_CreateNode_.md)：创建一个节点对象

+ [LoadFontFromFile(path)](_LoadFontFromFile_.md)：从文件中加载图像

+ [LoadFontFromData(data)](_LoadFontFromData_.md)：从缓冲区中加载图像

+ [CreateTextImage(font, content, [, color], textPattern, codeFormat)](_CreateTextImage_.md)：创建一个文本图像

## 对象成员函数

+ Image 对象成员函数

    + [Image:SetImageDynamic(isDynamic, frameAmount, width, height)](_Image_SetImageDynamic_.md)：设置图像是否为动态

    + [Image:SetRendererFlip(mode)](_Image_SetRendererFlip_.md)：设置图像的翻转模式

    + [Image:GetAnchorPoint()](_Image_GetAnchorPoint_.md)：获取图像的锚点

    + [Image:SetAnchorPoint(x, y)](_Image_SetAnchorPoint_.md)：设置图像的锚点

    + [Image:GetImageRect()](_Image_GetImageRect_.md)：获取图像截取的矩形

    + [Image:SetImageRect(x, y, w, h)](_Image_SetImageRect_.md)：设置图像截取的矩形

    + [Image:GetAlpha()](_Image_GetAlpha_.md)：获取图像的Alpha通道值(不透明度)

    + [Image:SetAlpha(alpha)](_Image_SetAlpha_.md)：设置图像的Alpha通道值(不透明度)
        
    + [Image:GetAngle()](_Image_GetAngle_.md)：获取图像的旋转角度

    + [Image:SetAngle(angle)](_Image_SetAngle_.md)：设置图像的旋转角度

    + 注意事项：以下函数只有属性为动态的图片才可使用

    + [Image:GetPlaySpeed()](_Image_GetPlaySpeed_.md)：获取属性为动态的图像的帧切换速度(speed 帧/次)

    + [Image:SetPlaySpeed(speed = 60)](_Image_SetPlaySpeed_.md)：设置属性为动态的图像的帧切换速度(speed 帧/次)

    + [Image:GetCurrentFrame()](_Image_GetCurrentFrame_.md)：获取属性为动态的图像的当前帧

    + [Image:SetCurrentFrame(frame)](_Image_SetCurrentFrame_.md)：设置属性为动态的图像的当前帧

+ Node 对象成员函数

    + [Node:GetImage()](_Node_GetImage_.md)：获取该节点对应的图像

    + [Node:SetImage(image)](_Node_SetImage_.md)：设置该节点对应的图像

    + [Node:GetCopyRect()](_Node_GetCopyRect_.md)：获取该节点的绘制矩形

    + [Node:SetCopyRect(rect)](_Node_SetCopyRect_.md)：设置该节点的绘制矩形

    + [Node:GetParent()](_Node_GetParent_.md)：获取该节点的父节点

    + [Node:SetParent(parent)](_Node_SetParent_.md)：设置该节点的父节点

    + [Node:GetDepth()](_Node_GetDepth_.md)：获取该节点的深度(值越小越先绘制)

    + [Node:SetDepth()](_Node_SetDepth_.md)：设置该节点的深度

    + [Node:AddChild(child)](_Node_AddChild_.md)：向该节点的子节点列表中添加一个子节点

    + [Node:DeleteChild()](_Node_DeleteChild_.md)：删除该节点的子节点列表中对应索引的节点

    + [Node:RunAction(action1, action2, action3...)](_Node_RunAction_.md)：让该节点运行参数中的动作

    + [Node:SetPause(isRunning)](_Node_SetPause_.md)：设置该节点是否持续更新

+ Font 对象成员函数

    + [Font:GetStyle()](_Font_GetStyle_.md)：获取该字体的风格

    + [Font:SetStyle()](_Font_SetStyle_.md)：设置该字体的风格

    + [Font:GetOutlineWidth()](_Font_GetOutlineWidth_.md)：获取已加载字体的轮框线宽度

    + [Font:SetOutlineWidth(width)](_Font_SetOutlineWidth_.md)：设置已加载字体的轮框线宽度

    + [Font:GetKerning()](_Font_GetKerning_.md)：获取字体间距

    + [Font:SetKerning(kerning)](_Font_SetKerning_.md)：设置字体间距

    + [Font:GetHeight()](_Font_GetHeight_.md)：获取字体高度

    + [Font:GetTextSize()](_Font_GetTextSize_.md)：获取字体大小

    + [Font:GetUTF8TextSize()](_Font_GetUTF8TextSize_.md)：设置UTF-8格式字体大小

+ Text 对象成员函数

    + [Text:ResetText(font, content, [, color], textPattern, codeFormat)](_Text_ResetText_.md)：重新设置文本图像

    + [Text:GetContent()](_Text_GetContent_.md)：获取文本图像的文字内容