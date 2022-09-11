#include <iostream>
#include <vector>
#include <algorithm>

class SegmentTree{
 public:

/*
  us and ue - starting and ending indexes of update query
    diff - which we need to add in the range us to ue
*/
  void UpdateRange(int us, int ue, int diff)
  {
    UpdateRange(0, 0, elements_amount_-1, us, ue, diff);
  }

  void UpdateValue(int index,int new_value){
    long long current_value=FindValue(0,index,0,elements_amount_-1,0);
    UpdateRange(0, 0, elements_amount_-1, index, index,-current_value);
    UpdateRange(0, 0, elements_amount_-1, index, index,new_value);

  }

  long long FindSum(int qs, int qe)
  {
/*    if (qs < 0 || qe > elements_amount_-1 || qs > qe)
    {
      std::cout<<("Invalid input values");
      return -1;
    }*/

    return FindSum(0, elements_amount_-1, qs, qe, 0,0);
  }

  long long FindMin(int qs, int qe)
  {
/*    if (qs < 0 || qe > elements_amount_-1 || qs > qe)
    {
      std::cout<<("Invalid input values");
      return -1;
    }*/

    return FindMin(0, elements_amount_-1, qs, qe, 0);
  }

  long long FindMax(int qs, int qe)
  {
/*    if (qs < 0 || qe > elements_amount_-1 || qs > qe)
    {
      std::cout<<("Invalid input values");
      return -1;
    }*/

    return FindMax(0, elements_amount_-1, qs, qe, 0);
  }

  void Construct(std::vector<int> values)
  {
    elements_amount_=values.size();
    Construct(values, 0, elements_amount_-1, 0);
  }

  void Construct(int elements_amount)
  {
    elements_amount_=elements_amount;
    sum_tree_=std::vector<long long>(4*elements_amount_);
    max_tree_=std::vector<long long>(4*elements_amount_);
    min_tree_=std::vector<long long>(4*elements_amount_);
    lazy_=std::vector<long long>(4*elements_amount_);
  }

 private:

  void Construct(std::vector<int> values, int start_index, int end_index, int current_node)
  {
    if (start_index > end_index)
      return ;
    elements_amount_=values.size();
    sum_tree_=std::vector<long long>(4*values.size());
    max_tree_=std::vector<long long>(4*values.size());
    min_tree_=std::vector<long long>(4*values.size());
    lazy_=std::vector<long long>(4*values.size());


    if (start_index == end_index)
    {
      sum_tree_[current_node] = values[start_index];
      max_tree_[current_node] = values[start_index];
      min_tree_[current_node] = values[start_index];

      return;
    }

    int mid = (start_index + end_index)/2;
    Construct(values, start_index, mid, current_node*2+1);
    Construct(values, mid+1, end_index, current_node*2+2);

    sum_tree_[current_node] = sum_tree_[current_node*2 + 1] + sum_tree_[current_node*2 + 2];
    max_tree_[current_node]= std::max(max_tree_[current_node*2 + 1],max_tree_[current_node*2 + 2]);
    min_tree_[current_node]= std::min(min_tree_[current_node*2 + 1],min_tree_[current_node*2 + 2]);

  }


  long long FindValue(int current_index, int p, int sl, int sr, long long prev_sum) {
    if (p == sl && sr == p) {
      return sum_tree_[current_index] + lazy_[current_index] + prev_sum;

    }
    int middle = (sr + sl) / 2;
    if (p <= middle) {
      long long current_sum = prev_sum + lazy_[current_index];
      return FindValue(2*current_index + 1, p, sl, middle, current_sum);
    }
    else {
      long long current_sum = prev_sum + lazy_[current_index];
      return FindValue(2*current_index + 2, p, middle + 1, sr, current_sum);
    }
  }


/* si - index of current node in segment tree
    ss and se - starting and ending indexes of elements for current nodes.
    us and ue - starting and ending indexes of update query
    diff - which we need to add in the range us to ue */

  void UpdateRange(int si, int ss, int se, int us, int ue, int diff)
  {
    if (us > ue) {
      return;
    }
    if (us == ss && se == ue) {
      max_tree_[si] += diff;
      min_tree_[si] += diff;
      lazy_[si] += diff;
      return;
    }

    int middle = (ss+se) / 2;
    UpdateRange(si * 2 + 1, ss, middle,us, std::min(ue, middle ), diff);
    UpdateRange(si * 2 + 2, middle  + 1, se,std::max(middle  + 1, us), ue, diff);

    sum_tree_[si] += diff * (ue - us + 1);
    min_tree_[si] = std::min(min_tree_[2*si + 1], min_tree_[2*si+ 2]) + lazy_[si];
    max_tree_[si] = std::max(max_tree_[2*si + 1], max_tree_[2*si + 2]) + lazy_[si];

  }



/*
    si - Index of current node in the segment tree.
    ss and se  - Starting and ending indexes of the segment represented by tree[si]
    qs and qe  - Starting and ending indexes of query range
    */

  long long FindSum(int ss, int se, int qs, int qe, int si,long long sum)
  {
    if (qs > qe) {
      return 0;
    }
    if (qs == ss && qe == se) {
      return (lazy_[si] + sum) * (qe - qs + 1) + sum_tree_[si];
    }
    int middle = (se + ss) / 2;
    return FindSum( ss, middle,qs, std::min(qe, middle),si * 2 + 1, lazy_[si]+sum)
        +FindSum( middle + 1, se,  std::max(qs, middle + 1), qe,si * 2 + 2,lazy_[si]+sum);
  }



  long long FindMax(int ss, int se, int qs, int qe, int si)
  {
    if (qs > qe) {
      return INT64_MIN;
    }
    if (qs == ss && qe == se) {
      return max_tree_[si];
    }
    int middle = (ss + se) / 2;
    return std::max(FindMax( ss, middle,qs, std::min(qe, middle),2*si + 1),
                    FindMax(  middle + 1, se,std::max(qs, middle + 1), qe,2*si + 2))
        +lazy_[si];
  }

  long long FindMin(int ss, int se, int qs, int qe, int si)
  {
    if (qs > qe) {
      return INT64_MAX;
    }
    if (ss == qs && qe == se) {
      return min_tree_[si];
    }
    int middle = (ss + se) / 2;
    return std::min(FindMin( ss, middle,qs, std::min(qe, middle),2*si + 1),
                    FindMin(  middle + 1, se,std::max(qs, middle + 1), qe,2*si + 2))
        +lazy_[si];
  }

  std::vector<long long> sum_tree_;
  std::vector<long long> max_tree_;
  std::vector<long long> min_tree_;
  std::vector<long long> lazy_;
  int elements_amount_;
};

