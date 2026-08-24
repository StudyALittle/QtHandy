# QhCheckBox API

1. [void setLockState(bool b)](#lockState)
1. [void setSelectOutsideText(int b)](#selectOutsideText)
1. [bool isLockState() const](#lockState)
1. [bool isSelectOutsideText() const](#selectOutsideText)

## description 描述
复选框控件

## public functions

<span id="setLockState"></span>
### void lockState(bool b)
Is the current status locked; If true, the status cannot be modified by clicking with the mouse; Default false.<br>
是否锁定当前状态；如果为true，不能通过鼠标点击修改状态；默认为false<br>
Access functions:<br>
- void setLockState(bool b)<br>
- bool isLockState() const

<span id="selectOutsideText"></span>
### selectOutsideText(int b);
Can it be selected outside the text; If it is true, it can be selected; Default to false.<br>
Warring: The mouse is still inside the control, just outside the text of the control<br>
在文本外是否能选中；如果为true，则能选中；默认为false<br>
警告：鼠标还是处于控件中，只是在控件中的文本外<br>
Access functions:<br>
- void setSelectOutsideText(bool b)<br>
- bool isSelectOutsideText() const