#pragma once

template <typename Data>
class tree_node {
public: 
    Data data; 
    tree_node<Data>* left;
    tree_node<Data>* right;
    unsigned char height;

    tree_node(Data _data) { data = _data; left = right = 0; height = 1; }

    ~tree_node() { delete left; delete right; }
    unsigned char get_height(tree_node* _node) {
        return (_node == nullptr) ? 0 : _node->height;
    }

    int balance_factor(tree_node<Data>* _node) {
        return get_height(_node->right) - get_height(_node->left);
    }

    void fix_height(tree_node<Data>* _node) {
        unsigned char height_left = get_height(_node->left);
        unsigned char height_right = get_height(_node->right);
        _node->height = (height_left > height_right ? height_left : height_right) + 1;
    }
    tree_node<Data>* rotate_right(tree_node<Data>* _node){ // правый поворот
        tree_node<Data>* node_left = _node->left;
        _node->left = node_left->right;
        node_left->right = _node;
        fix_height(_node);
        fix_height(node_left);
        return node_left;
    }
    tree_node<Data>* rotate_left(tree_node<Data>* _node){ // левый поворот
        tree_node<Data>* node_right = _node->right;
        _node->right = node_right->left;
        node_right->left = _node;
        fix_height(_node);
        fix_height(node_right);
        return node_right;
    }
    tree_node<Data>* balance(tree_node<Data>* _node){ // балансировка узла
        fix_height(_node);
        if( balance_factor(_node) == 2 ) {      //правый больше левого
            if( balance_factor( _node->right ) < 0 )
                _node->right = rotate_right( _node->right );
            return rotate_left(_node);
        }
        if( balance_factor(_node) == -2 ) {
            if( balance_factor(_node->left) > 0 )
                _node->left = rotate_left(_node->left);
            return rotate_right(_node);
        }
        return _node; // балансировка не нужна
    }
};
