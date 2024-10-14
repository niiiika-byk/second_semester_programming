#pragma once

#include <cstddef>

template <typename Key>
class Set_node {
public:
    Key _key;
    Set_node* _next;
    
    Set_node(const Set_node &) = delete;      //конструктор копирования запрещен
    Set_node & operator=(const Set_node &) = delete; //оператор присваивания запрещен
    Set_node(const Key &key) :
        _key(key), _next(nullptr) {}

    Key get_key() const
    {
        return _key;
    }

    Set_node* get_next() const
    {
        return _next;
    }

    void set_next(Set_node *next)
    {
        _next = next;
    }

};