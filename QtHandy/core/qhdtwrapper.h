#ifndef QHDTWRAPPER_H
#define QHDTWRAPPER_H

/**
 * @file       qhdtwrapper.h
 * @brief 数据类型包装器（Data type wrapper）
 *  包装数据类型，用于判断数据类型是否初始化（设置值）；
 *  使用场景：
 *      判断非指针数据是否初始化;
 *      例如 int n; 的语句，不太好判断n是否初始化值，如果全部使用指针又不太好管理；
 *      使用 QhDTWrapper<int> n, 的isValid()可以判断是否初始化值；
 *
 *  Packaging data type, used to determine whether the data type has been initialized (set value)
 *  Usage scenario:
 *      Determine whether non-pointer data is initialized;
 *      For example, in the statement "int n;", it is difficult to determine whether n has been initialized with a value.
 *      If pointers are used exclusively, it becomes unwieldy to manage;
 *      The isValid() method of QhDTWrapper<int> n can be used to determine whether the value has been initialized;
 * @author     wmz
 * @date       2026/03/09
 * @history
 */

#include <type_traits>

template<typename T>
class QhDTWrapper
{
public:
    /// @brief Constructor, isValid() return false
    inline QhDTWrapper();
    /// @brief Constructor, set default value, isValid() return true
    inline QhDTWrapper(const T &value);
    /// @brief Constructor, set default value, isValid() return true
    inline QhDTWrapper(T &&value);
    /// @brief Destructor
    inline ~QhDTWrapper();

    /// @brief return value
    inline T &value() { return _value; }
    inline const T &value() const { return _value; }

    /// @brief Is the data valid;
    /// setValue() returns true
    inline bool isValid() const { return _bValid; }

    /// @brief set value
    inline void setValue(const T &value) { _value = value; _bValid = true; }
    inline void setValue(T &&value) { _value = value; _bValid = true; }

    /// @brief Clear data, isValid() return false.
    /// if it is a pointer, value() return nullptr
    inline void clear();

    /// @brief Overloaded
    QhDTWrapper &operator = (const T &value) { setValue(value); return *this; }
    QhDTWrapper &operator = (T &&value) { setValue(value); return *this; }

    /// @brief Overloaded
    QhDTWrapper &operator = (const QhDTWrapper<T> &that);

    /// @brief Overloaded, example: QhDTWrapper<int> n; n();
    T &operator()() { return _value; }
    const T &operator()() const { return _value; }

private:
    // ptr
    template<typename U = T>
    typename std::enable_if<std::is_pointer<U>::value>::type
    initValue(U& val) { val = nullptr; }

    // not ptr
    template<typename U = T>
    typename std::enable_if<!std::is_pointer<U>::value>::type
    initValue(U&) { }

    // ptr
    template<typename U = T>
    typename std::enable_if<std::is_pointer<U>::value>::type
    delValue(U& val) { if (val) { delete val; val = nullptr; } }

    // not ptr
    template<typename U = T>
    typename std::enable_if<!std::is_pointer<U>::value>::type
    delValue(U&) { }

    // ptr
    template<typename U = T>
    typename std::enable_if<std::is_pointer<U>::value>::type
    copyValue(U& thatValue);

    // not nullptr
    template<typename U = T>
    typename std::enable_if<!std::is_pointer<U>::value>::type
    copyValue(U& thatValue) { _value = thatValue; }

    bool _bValid;
    T _value;
};

template <typename T>
inline QhDTWrapper<T>::QhDTWrapper(): _bValid(false)
{
    initValue(_value);
}

template <typename T>
inline QhDTWrapper<T>::QhDTWrapper(const T &value)
{
    setValue(value);
}

template <typename T>
inline QhDTWrapper<T>::QhDTWrapper(T &&value)
{
    setValue(value);
}

template <typename T>
inline QhDTWrapper<T>::~QhDTWrapper()
{
    clear();
}

template <typename T>
inline void QhDTWrapper<T>::clear()
{
    _bValid = false;
    delValue(_value);
}

template <typename T>
QhDTWrapper<T> &QhDTWrapper<T>::operator = (const QhDTWrapper<T> &that)
{
    if (&that == this)
        return *this;

    _bValid = that._bValid;
    copyValue(that._value);
    return *this;
}

template <typename T>
template <typename U>
typename std::enable_if<std::is_pointer<U>::value>::type
QhDTWrapper<T>::copyValue(U& thatValue)
{
    delValue(_value);
    if (thatValue) {
        _value = new typename std::remove_pointer<U>::type();
        *_value = *thatValue;
    }
}

#endif // QHDTWRAPPER_H
