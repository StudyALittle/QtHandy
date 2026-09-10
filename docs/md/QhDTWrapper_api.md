# QhCheckBox API

1. [QhDTWrapper()](#QhDTWrapper)
1. [QhDTWrapper(const T &value)](#QhDTWrapper)
1. [QhDTWrapper(T &&value)](#QhDTWrapper)
1. [~QhDTWrapper()](#~QhDTWrapper)
1. [T &value()](#value)
1. [const T &value() const](#value)
1. [bool isValid() const](#isValid)
1. [void setValue(const T &value)](#setValue)
1. [void setValue(T &&value)](#setValue)
1. [void clear()](#clear)
1. [QhDTWrapper &operator = (const T &value)](#operator)
1. [QhDTWrapper &operator = (T &&value)](#operator)
1. [QhDTWrapper &operator = (const QhDTWrapper<T> &that)](#operator)
1. [T &operator()()](#operator)
1. [const T &operator()() const](#operator)

## description 描述
数据包装器；使用场景示例：<br>
**struct QueryParams**<br>
{<br>
    QhDTWrapper<int> age;<br>
    QhDTWrapper<int> sex;<br>
    QhDTWrapper<QString> name;<br>
};<br>
**... set params** <br>
QueryParams params;<br>
params.age = 18;<br>
params.name = "test";<br>
**... get params and set request** <br>
QueryParams params = getQueryParams();<br>
QJsonObject object;<br>
if (params.age.isValid())<br>
    object["age"] = params.age.value();<br>
if (params.sex.isValid())<br>
    object["sex"] = params.age.value();<br>
if (params.name.isValid())<br>
    object["name"] = params.age.value();<br>
... QJsonDocument(object).toJson();

## public functions

<span id="QhDTWrapper"></span>
### QhDTWrapper
构造函数<br>
Access functions:<br>
- QhDTWrapper()<br>
- QhDTWrapper(const T &value) const<br>
- QhDTWrapper(T &&value)

<span id="~QhDTWrapper"></span>
### ~QhDTWrapper()
析构函数

<span id="value"></span>
### value
返回包装数据的值；<br>
如果包装数据是指针，未设置或clear()时，返回值为nullptr<br>
Access functions:<br>
- T &value()<br>
- const T &value() const

<span id="isValid"></span>
### bool isValid() const
返回是否设置包装数据的值；<br>
如果调用setValue，或者创建时使用构造函数QhDTWrapper(const T &value)或QhDTWrapper(T &&value)，返回true;<br>
其他情况或clear()时，返回false;<br>

<span id="setValue"></span>
### setValue
设置包装数据的值；<br>
Access functions:<br>
- void setValue(const T &value)<br>
- void setValue(T &&value)

<span id="clear"></span>
### void clear()
清除设置包装数据的值；<br>
调用该函数后，isValid()返回false;<br>
如果包装数据是指针, value()返回值为nullptr;<br>

<span id="operator"></span>
### operator
运算符重载；<br>
Access functions:<br>
- QhDTWrapper &operator = (const T &value)<br>
- QhDTWrapper &operator = (T &&value)<br>
- QhDTWrapper &operator = (const QhDTWrapper<T> &that)<br>
- T &operator()()<br>
- const T &operator()() const