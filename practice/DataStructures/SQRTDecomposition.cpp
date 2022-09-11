#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct SQRTDecomposition{
  std::vector<long long> a_;
  std::vector<long long> b_;
  int n_;
  int k_;

  void Build(){
    std::cin >> n_;
    a_=std::vector<long long>(n_);
    k_ = std::floor(std::sqrt(n_));
    b_=std::vector<long long>(n_/k_+1);

    for (int i = 0; i < n_; i++) {
      int value = 0;
      std::cin >> value;
      a_[i]=value;
    }
    for (int i = 0; i < n_; i++) {
      b_[i / k_] += a_[i];
    }
  }

  void Insert(int index, int x)
  {
    a_[index] += x;
    b_[index / k_] += x;
  }

  long long FindSum(int l, int r) {
    long long sum = 0;
    int jl = l / k_;
    int jr = r / k_;
    if (jl == jr) {
      for (int i = l; i < r; ++i)
      {
        sum += a_[i];
      }
    }
    else {
      int end_index = (jl + 1) * k_ - 1;
      for (int i = l; i <= end_index; ++i)
      {
        sum += a_[i];
      }

      for (int i = jl + 1; i < jr; ++i)
      {
        sum += b_[i];
      }

      for (int i = jr * k_; i < r; ++i)
      {
        sum += a_[i];
      }
    }
    return sum;
  }

};