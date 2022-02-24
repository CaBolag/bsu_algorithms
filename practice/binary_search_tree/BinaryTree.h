#ifndef BINARY_SEARCH_TREE__BINARYTREE_H_
#define BINARY_SEARCH_TREE__BINARYTREE_H_


#include <iostream>
#include <vector>
#include <sstream>
#include <functional>

class Node {
 private:
  Node* left_ = nullptr;
  Node* right_ = nullptr;
  Node* parent_;
  int key_;
  unsigned int height_=0;
  //MaxLengthOfPendantVertexPaths
  unsigned int pendant_paths_max_length_=0;
  unsigned int paths_max_length_=0;

 public:
  Node(int key,Node* parent = nullptr) :key_(key),parent_(parent) {};
  Node* GetLeft();
  Node* GetRight();
  void SetRight(Node* right);
  void SetLeft(Node* left);
  Node* GetParent();
  int GetKey();
  void SetKey(int key);
  unsigned int GetHeight();
  void SetHeight(unsigned int height);
  unsigned int GetPendantMaxLength();
  void SetPendantMaxLength(unsigned int pendant_paths_max_length);
  unsigned int GetPathsMaxLength();
  void SetPathsMaxLength(unsigned int paths_max_length);

};


class BinarySearchTree {
 public:
  BinarySearchTree() = default;
  ~BinarySearchTree();

  void Insert(int key);
  void TreeToVector(std::vector<int> &keys);
  void FindHeights();
  void FindPathsMaxLength();
  void FindMaxKeyOfPathsOfLessLength(unsigned int length,int& max_key);
  void DeleteNode(unsigned int key);


 private:
  //PreOrderTraversal
  void TreeToVector(Node *node, std::vector<int> &keys);
  //PostOrderTraversal
  void FindHeights(Node* node);
  void FindPathsMaxLength(Node* node);
  void FindMaxKeyOfPathsOfLessLength(Node* node,unsigned int length, int& max_key);
  Node *DeleteNode(Node *node, int key);
  void DestroyNode(Node *node);

  Node *root_ = nullptr;
};


Node* Node::GetLeft() {
  return left_;
}

Node* Node::GetRight() {
  return right_;
}

void Node::SetRight(Node* right) {
  right_ = right;
}

void Node::SetLeft(Node* left) {
  left_ = left;
}

Node* Node::GetParent(){
  return parent_;
}

int Node::GetKey() {
  return key_;
}

void Node::SetKey(int key){
  key_=key;
}
unsigned int Node::GetHeight(){
  return height_;
}
void Node::SetHeight(unsigned int height){
  height_=height;
}

unsigned int Node::GetPendantMaxLength(){
  return pendant_paths_max_length_;
}

void Node::SetPendantMaxLength(unsigned int pendant_paths_max_length){
  pendant_paths_max_length_=pendant_paths_max_length;
}

unsigned int Node::GetPathsMaxLength(){
  return paths_max_length_;
}

void Node::SetPathsMaxLength(unsigned int paths_max_length){
  paths_max_length_=paths_max_length;
}


BinarySearchTree::~BinarySearchTree() {
  DestroyNode(root_);
}

void BinarySearchTree::DestroyNode(Node* node) {
  if (node) {
    DestroyNode(node->GetLeft());
    DestroyNode(node->GetRight());
    delete node;
  }
}

void BinarySearchTree::TreeToVector(std::vector<int> &keys) {
  this->TreeToVector(this->root_,keys);
}

void BinarySearchTree::FindHeights() {
  this->FindHeights(this->root_);
}

void BinarySearchTree::FindPathsMaxLength() {
  this->FindPathsMaxLength(root_);
}

void BinarySearchTree::FindMaxKeyOfPathsOfLessLength(unsigned int length, int &max_key) {
  this->FindMaxKeyOfPathsOfLessLength(root_,length,max_key);
}

void BinarySearchTree::DeleteNode(unsigned int key) {
  root_=this->DeleteNode(root_,key);
}



void BinarySearchTree::Insert(int key) {
  if (root_ == nullptr) {
    root_ = new Node(key);
    return;
  }

  Node* current = root_;
  while (1) {
    if(key==current->GetKey()){
      return;
    }

    if (current->GetKey() < key) {
      if (!current->GetRight()) {
        current->SetRight(new Node(key,current));
        return;
      }
      current = current->GetRight();
    }
    else {
      if (!current->GetLeft()) {
        current->SetLeft(new Node(key,current));
        return;
      }
      current = current->GetLeft();
    }
  }
}

void BinarySearchTree::TreeToVector(Node* node, std::vector<int>& keys) {
  if (!node) {
    return;
  }
  keys.push_back(node->GetKey());
  TreeToVector(node->GetLeft(),keys);
  TreeToVector(node->GetRight(),keys);
}

void BinarySearchTree::FindHeights(Node *node) {
  if(!node){
    return;
  }
  FindHeights(node->GetLeft());
  FindHeights(node->GetRight());
  if(node->GetLeft() && node->GetRight()){
    node->SetHeight(std::max(node->GetRight()->GetHeight(),node->GetLeft()->GetHeight())+1);
  } else if (node->GetLeft()) {
    node->SetHeight(node->GetLeft()->GetHeight() + 1);
  } else if(node->GetRight()){
    node->SetHeight(node->GetRight()->GetHeight()+1);
  } else{
    node->SetHeight(0);
  }
}

void BinarySearchTree::FindPathsMaxLength(Node* node) {
  if (!node) {
    return;
  }
/*
  find length of the following paths:
  - through the vertex and the left subtree
  - through the vertex and the right subtree
  - path for which the vertex is pendant
*/

  std::vector<unsigned int> paths_length = {0, 0, 0};
  unsigned int length_with_other_parent_subtree = 0;
  Node *parent = node->GetParent();
  if (parent != nullptr) {
    if (node == parent->GetRight() && parent->GetLeft()) {
      length_with_other_parent_subtree = parent->GetLeft()->GetHeight() + 2;
    } else if (node == parent->GetLeft() && parent->GetRight()) {
      length_with_other_parent_subtree = parent->GetRight()->GetHeight() + 2;
    }
    node->SetPendantMaxLength(std::max(parent->GetPendantMaxLength() + 1, length_with_other_parent_subtree));
    paths_length[0] = node->GetPendantMaxLength();
  }

  if (node->GetLeft() && node->GetRight()) {
    paths_length[1] = node->GetLeft()->GetHeight() + 1;
    paths_length[2] = node->GetRight()->GetHeight() + 1;
  } else if (node->GetRight()) {
    paths_length[2] = node->GetRight()->GetHeight() + 1;
  } else if (node->GetLeft()) {
    paths_length[1] = node->GetLeft()->GetHeight() + 1;
  }

  // path of max length passing through the vertex is a max sum of the length of this paths
  std::sort(paths_length.begin(), paths_length.end());
  node->SetPathsMaxLength(paths_length[1] + paths_length[2]);

/*  unsigned int length_with_max_height_subtree = 0;
  unsigned int length_with_subtrees = 0;
  //
  if (node->GetLeft() && node->GetRight()) {
    length_with_max_height_subtree = std::max(node->GetLeft()->GetHeight(), node->GetRight()->GetHeight()) + 1;
    length_with_subtrees += node->GetLeft()->GetHeight() + node->GetRight()->GetHeight() + 2;
  } else if (node->GetRight()) {
    length_with_max_height_subtree = node->GetRight()->GetHeight() + 1;
    length_with_subtrees += node->GetRight()->GetHeight() + 1;
  } else if (node->GetLeft()) {
    length_with_max_height_subtree = node->GetLeft()->GetHeight() + 1;
    length_with_subtrees += node->GetLeft()->GetHeight() + 1;

  }
  // for root PendantMaxLength=0
  if (node == root_) {
    if (node->GetLeft() && node->GetRight()) {
      node->SetPathsMaxLength(node->GetRight()->GetHeight() + node->GetLeft()->GetHeight() + 2);
    } else {
      node->SetPathsMaxLength(node->GetHeight());
    }

  } else {

    node->SetPathsMaxLength(std::max(length_with_max_height_subtree + node->GetPendantMaxLength(),
                                     length_with_subtrees));
    //node->SetPathsMaxLength(subtrees_max_height+node->GetPendantMaxLength()+1);

//}*/

  FindPathsMaxLength(node->GetLeft());
  FindPathsMaxLength(node->GetRight());
}

void BinarySearchTree::FindMaxKeyOfPathsOfLessLength(Node *node, unsigned int max_length, int &max_key)
{
  if (!node) {
    return;
  }
  FindMaxKeyOfPathsOfLessLength(node->GetLeft(), max_length, max_key);
  FindMaxKeyOfPathsOfLessLength(node->GetRight(), max_length, max_key);
  if (node->GetPathsMaxLength() < max_length && node->GetKey() >= max_key) {
    max_key = node->GetKey();
  }
}

Node *BinarySearchTree::DeleteNode(Node *node, int key) {
  if (node == nullptr) {
    return nullptr;
  }

  if (key == node->GetKey()) {
    if (node == root_ && node->GetLeft() && !node->GetRight()) {
      root_ = node->GetLeft();
      return node->GetLeft();
    } else if (node == root_ && node->GetRight() && !node->GetLeft()) {
      root_ = node->GetRight();
      return node->GetRight();
    }
    if (node->GetLeft() && node->GetRight()) {
      //find node with smallest key in the right subtree
      Node *smallestNode = node->GetRight();
      while (smallestNode && smallestNode->GetLeft() != nullptr) {
        smallestNode = smallestNode->GetLeft();
      }

      node->SetKey(smallestNode->GetKey());
      node->SetRight(DeleteNode(node->GetRight(), smallestNode->GetKey()));

    } else if (node->GetLeft()) {
      Node *temp = node->GetLeft();
      delete node;
      return temp;
    } else if (node->GetRight()) {
      Node *temp = node->GetRight();
      delete node;
      return temp;
    } else {
      delete node;
      return nullptr;
    }

  } else if (key < node->GetKey()) {
    node->SetLeft(DeleteNode(node->GetLeft(), key));
  } else {
    node->SetRight(DeleteNode(node->GetRight(), key));
  }

  return node;
}


#endif //BINARY_SEARCH_TREE__BINARYTREE_H_
