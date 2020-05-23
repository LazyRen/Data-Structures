#ifndef _NODE_H_
#define _NODE_H_
#include <string>

template <typename T>
class Node {
private:
  T data;
  Node *parent;
  Node *leftChild;
  Node *rightChild;
  Node *sibling; //Nodes with same Data key
public:
  Node(T d=T(), Node *p=nullptr, Node *l=nullptr, Node *r=nullptr, Node *s=nullptr);
  Node(const Node&) = default;
  Node(Node&&) = default;

  ~Node() = default;

  const T& getData() const;
  Node* getParent() const;
  Node* getLeftChild() const;
  Node* getRightChild() const;
  Node* getSibling() const;

  void setData(const T &d);
  void setParent(Node* const n);
  void setLeftChild(Node* const n);
  void setRightChild(Node* const n);
  void setSibling(Node* const n);

  Node& operator=(const Node&) = default;
  Node& operator=(Node&&) = default;

};

template <typename T>
Node<T>::Node(T d, Node *p, Node *l, Node *r, Node *s) : data(d), parent(p), leftChild(l), rightChild(r), sibling(s) {};

template <typename T>
const T& Node<T>::getData() const {
  return data;
}

template <typename T>
Node<T>* Node<T>::getParent() const {
  return parent;
}

template <typename T>
Node<T>* Node<T>::getLeftChild() const {
  return leftChild;
}

template <typename T>
Node<T>* Node<T>::getRightChild() const {
  return rightChild;
}

template <typename T>
Node<T>* Node<T>::getSibling() const {
  return sibling;
}

template <typename T>
void Node<T>::setData(const T &d) {
  data = d;
}

template <typename T>
void Node<T>::setParent(Node<T>* const n) {
  parent = n;
}

template <typename T>
void Node<T>::setLeftChild(Node<T>* const n) {
  leftChild = n;
}

template <typename T>
void Node<T>::setRightChild(Node<T>* const n) {
  rightChild = n;
}

template <typename T>
void Node<T>::setSibling(Node<T>* const n) {
  sibling = n;
}

#endif
