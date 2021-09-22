### [[ << 回到主页 ]](../README.md)

# Action

> Action 模块提供窗口相关操作

## 模块函数列表

+ [CreateMoveTo(point, time)](_CreateMoveTo_.md)：创建移动到指定位置的动作对象

+ [CreateMoveBy(distance, time)](_CreateMoveBy_.md)：创建移动一定距离的动作对象

+ [CreateSpinTo(angle, time, direction)](_CreateSpinTo_.md)：创建旋转到指定角度的动作对象

+ [CreateSpinBy(angle, time)](_CreateSpinBy_.md)：创建旋转一定角度的动作对象

+ [CreateScaleTo(w, h, time)](_CreateScaleTo_.md)：创建放大或缩小到指定尺寸的动作对象

## 对象成员函数

+ Action 对象成员函数

    + [Action:ModifyTime(time)](_Action_ModifyTime_.md)：修改该动作对象的持续时间

    + [Action:SetCallback(callback)](_Action_SetCallback_.md)：设置该动作对象的回调函数

## 作者的话

> 还有很多测试失败的动作呢...
> 之后慢慢加慢慢测试()
> 顺带一提，添加一个动作在源码中需要改7个位置QAQ