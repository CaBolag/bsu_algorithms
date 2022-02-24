#include "BinaryTree.h"

int main() {

  freopen("tst.in", "r", stdin);
  freopen("tst.out", "w", stdout);

  BinarySearchTree bts;
  unsigned int max_length;
  std::cin>>max_length;
  unsigned int value;
  while (std::cin >> value) {
    bts.Insert(value);
  }

  bts.FindHeights();
  bts.FindPathsMaxLength();
  int max_key = -1;
  bts.FindMaxKeyOfPathsOfLessLength(max_length, max_key);
  if (max_key>=0) {
    bts.DeleteNode(max_key);
  }

  std::vector<int> tree;
  bts.TreeToVector(tree);
  int index=0;
  int size= tree.size();
  if(!tree.empty()){
    while (index<size-1) {
      std::cout << tree[index] << "\n";
      index++;
    }
    std::cout << tree[index];
  } else {
    std::cout<<"Empty";
  }

  fclose(stdin);
  fclose(stdout);

  return 0;
}
