#pragma once

#include <cstddef>

template <typename Key, typename Value>
class Hash_node {
public:
    Hash_node(const Hash_node &) = delete;      //конструктор копирования запрещен
    Hash_node & operator=(const Hash_node &) = delete; //оператор присваивания запрещен
    Hash_node(const Key &key, const Value &value) :
        _key(key), _value(value), _next(nullptr){}

    Key get_key() const
    {
        return _key;
    }

    Value get_value() const
    {
        return _value;
    }

    void set_value(Value value)
    {
        _value = value;
    }

    Hash_node* get_next() const
    {
        return _next;
    }

    void set_next(Hash_node *next)
    {
        _next = next;
    }

private:
    Key _key;
    Value _value;
    Hash_node* _next;
};