#ifndef _BST_H_
#define _BST_H_
#include "node.h"
#include <iostream>
#include <vector>
#include <queue>
#include <string>

template <typename T>
class BST {
private:
  Node<T> *root;

  Node<T>* findNode(const T key) const;
  Node<T>* findRightMinNode(Node<T> *cur) const;
  void removeNode(Node<T> *cur);
  void removeAllSibling(Node<T> *cur);
  std::vector<T> _rangeSearch(const T lowKey, const T highKey,  Node<T>* const cur) const;
  void destructTree(Node<T> *cur);
  void printTree(const std::string& prefix, const Node<T>* const node, bool isLeft) const;
public:
  BST(Node<T> *r=nullptr) : root(r) {};

  ~BST() {
    destructTree(root);
  }

  bool insert(const T &d);
  std::vector<T> search(const T key) const;
  std::vector<T> rangeSearch(const T lowKey, const T highKey) const;
  bool modify(const T key, const T& data);
  bool remove(const T key);
  void printTree() const;
};

template <typename T>
Node<T>* BST<T>::findNode(const T key) const {
  Node<T> *cur = root;
  while (cur) {
    const T curKey = cur->getData();
    if (key == curKey) {
      break;
    } else if (key < curKey) {
      cur = cur->getLeftChild();
    } else {
      cur = cur->getRightChild();
    }
  }
  return cur;
}

template <typename T>
Node<T>* BST<T>::findRightMinNode(Node<T> *cur) const {
  while (cur->getLeftChild() != nullptr)
    cur = cur->getLeftChild();
  return cur;
}

template <typename T>
void BST<T>::removeNode(Node<T> *cur) {
  if (cur == nullptr)
    return;

  Node<T> *p = cur->getParent();
  Node<T> *l = cur->getLeftChild();
  Node<T> *r = cur->getRightChild();
  Node<T> *s = cur->getSibling();
  if (s != nullptr) {
    if (cur == root)
      root = s;
    s->setParent(p);
    s->setLeftChild(l);
    s->setRightChild(r);
  } else if (l == nullptr && r == nullptr) {
    if (cur == root)
      root = nullptr;
    else if (p->getLeftChild() == cur)
      p->setLeftChild(nullptr);
    else
      p->setRightChild(nullptr);
  } else if (l != nullptr && r != nullptr) {
    Node<T> *replace = findRightMinNode(cur->getRightChild());
    cur->setData(replace->getData());
    cur->setSibling(replace->getSibling());
    replace->setSibling(nullptr);
    removeNode(replace);
    return;
  } else if (l != nullptr) {
    if (cur == root) {
      root = l;
      l->setParent(nullptr);
    } else if (p->getLeftChild() == cur) {
      p->setLeftChild(l);
      l->setParent(p);
    } else {
      p->setRightChild(l);
      l->setParent(p);
    }
  } else {
    if (cur == root) {
      root = r;
      r->setParent(nullptr);
    }
    else if (p->getLeftChild() == cur) {
      p->setLeftChild(r);
      r->setParent(p);
    } else {
      p->setRightChild(r);
      r->setParent(p);
    }
  }
  delete cur;
  printTree();
}
template <typename T>
void BST<T>::removeAllSibling(Node<T> *cur) {
  Node<T> *sibling = cur->getSibling();
  while (sibling) {
    Node<T> *next = sibling->getSibling();
    delete sibling;
    sibling = next;
  }
  cur->setSibling(nullptr);
  removeNode(cur);
}

template <typename T>
void BST<T>::destructTree(Node<T> *cur) {
  if (cur == nullptr)
    return;
  destructTree(cur->getLeftChild());
  destructTree(cur->getRightChild());
  delete cur;
}

template <typename T>
std::vector<T> BST<T>::_rangeSearch(const T lowKey, const T highKey, Node<T>* const cur) const {
  std::vector<T> vec;
  if (cur == nullptr)
    return vec;
  const T &data = cur->getData();
  if (data < lowKey) {
    std::vector<T> res = _rangeSearch(lowKey, highKey, cur->getRightChild());
    for (int i = 0; i < res.size(); i++)
      vec.push_back(res[i]);
  } else if (data > highKey) {
    std::vector<T> res = _rangeSearch(lowKey, highKey, cur->getLeftChild());
    for (int i = 0; i < res.size(); i++)
      vec.push_back(res[i]);
  } else { // within range
    std::vector<T> res = _rangeSearch(lowKey, highKey, cur->getLeftChild());
    for (int i = 0; i < res.size(); i++)
      vec.push_back(res[i]);
    Node<T> *s = cur;
    while (s) {
      vec.push_back(s->getData());
      s = s->getSibling();
    }
    res = _rangeSearch(lowKey, highKey, cur->getRightChild());
    for (int i = 0; i < res.size(); i++)
      vec.push_back(res[i]);
  }
  return vec;
}

template <typename T>
void BST<T>::printTree(const std::string& prefix, const Node<T>* const node, bool isLeft) const {
  if (node != nullptr)
  {
    std::cout << prefix << (isLeft ? "|--" : "|__" ) << node->getData() << std::endl;

    printTree(prefix + (isLeft ? "|   " : "    "), node->getLeftChild(), true);
    printTree(prefix + (isLeft ? "|   " : "    "), node->getRightChild(), false);
  }
}

template <typename T>
bool BST<T>::insert(const T &d) {
  Node<T> *cur = root;
  Node<T> *new_node = new Node<T>(d);

  if (root == nullptr) {
    root = new_node;
    return true;
  }
  while (true) {
    const T curKey = cur->getData();
    if (d == curKey) {
      new_node->setSibling(cur->getSibling());
      cur->setSibling(new_node);
      break;
    } else if (d < curKey) {
      if (cur->getLeftChild() == nullptr) {
        new_node->setParent(cur);
        cur->setLeftChild(new_node);
        break;
      }
      cur = cur->getLeftChild();
    } else {
      if (cur->getRightChild() == nullptr) {
        new_node->setParent(cur);
        cur->setRightChild(new_node);
        break;
      }
      cur = cur->getRightChild();
    }
  }
  return true;
}

template <typename T>
std::vector<T> BST<T>::search(const T key) const {
  std::vector<T> vec;
  Node<T> *cur = findNode(key);
  if (cur) {
    while (cur) {
      vec.push_back(cur->getData());
      cur = cur->getSibling();
    }
  }
  return vec;
}

template <typename T>
std::vector<T> BST<T>::rangeSearch(const T lowKey, const T highKey) const {
  std::vector<T> vec = _rangeSearch(lowKey, highKey, root);
  return vec;
}

template <typename T>
bool BST<T>::modify(const T key, const T &data) {
  Node<T> *cur = findNode(key);

  if (cur) {
    removeAllSibling(cur);
    insert(data);
    return true;
  }
  return false;
}

template <typename T>
bool BST<T>::remove(const T key) {
  Node<T> *cur = findNode(key);

  if (cur) {
    removeAllSibling(cur);
    return true;
  }
  return false;
}

template <typename T>
void BST<T>::printTree() const {
  printTree("", root, false);
}

#endif
