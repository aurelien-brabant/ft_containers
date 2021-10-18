#pragma once

namespace ft {

template<typename T1, typename T2>
class pair
{
  public:
    typedef T1 first_type;
    typedef T2 second_type;

    T1 first;
    T2 second;

    pair(void)
      : first()
      , second()
    {}

    pair(const T1& x, const T2& y)
      : first(x)
      , second(y)
    {}

    pair(const pair& other) { *this = other; }

    template<typename U1, typename U2>
    pair(const pair<U1, U2>& other)
      : first(other.first)
      , second(other.second)
    {}

    pair& operator=(const pair& rhs)
    {
        if (this != &rhs) {
            first = rhs.first;
            second = rhs.second;
        }

        return *this;
    }
};

template<typename T1, typename T2>
pair<T1, T2>
make_pair(T1 t, T2 u)
{
    return pair<T1, T2>(t, u);
}

template<typename T1, typename T2>
bool
operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template<typename T1, typename T2>
bool
operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(lhs == rhs);
}

template<typename T1, typename T2>
bool
operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    if (lhs.first < rhs.first)
        return true;
    if (rhs.first < lhs.first)
        return false;
    return (lhs.second < rhs.second);
}

template<typename T1, typename T2>
bool
operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(rhs < lhs);
}

template<typename T1, typename T2>
bool
operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return rhs < lhs;
}

template<typename T1, typename T2>
bool
operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(lhs < rhs);
}

} // namespace ft
