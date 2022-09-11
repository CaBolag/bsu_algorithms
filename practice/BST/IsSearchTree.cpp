#include <iostream>
#include <vector>


struct TNode{

  TNode(long long key):key_(key){
    min_=INT64_MIN;
    max_=INT64_MAX;
  }

  long long key_;
  long long min_;
  long long max_;

};


void IsBinaryTree() {

  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  freopen("bst.in", "r", stdin);
  freopen("bst.out", "w", stdout);
  int vertex_amount;
  std::cin >> vertex_amount;
  std::vector<TNode*> nodes;
  int key,parent_number;
  char insert_direction;

  std::cin >> key;
  nodes.push_back(new TNode(key));


  bool is_search_tree = 1;

  for (int i = 1; i < vertex_amount; i++) {
    std::cin >> key;
    std::cin >> parent_number;
    parent_number--;
    TNode* new_node=new TNode(key);
    std::cin >> insert_direction;

    if (insert_direction == 'R') {
      new_node->min_ = nodes[parent_number]->key_ - 1;
      new_node->max_ =nodes[parent_number]->max_;
    } else {
      new_node->min_ =nodes[parent_number]->min_;
      new_node->max_  = nodes[parent_number]->key_;
    }

    if (key <= new_node->min_ || key >= new_node->max_) {
      is_search_tree = 0;
      break;
    }
    nodes.push_back(new_node);
  }

  if (is_search_tree) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}


