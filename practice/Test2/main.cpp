/*
#include <iostream>
#include <vector>
#include <algorithm>

class SegmentTree{
 public:

*/
/*
  us and ue - starting and ending indexes of update query
    diff - which we need to add in the range us to ue
*//*

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
*/
/*    if (qs < 0 || qe > elements_amount_-1 || qs > qe)
    {
      std::cout<<("Invalid input values");
      return -1;
    }*//*


    return FindSum(0, elements_amount_-1, qs, qe, 0,0);
  }

  long long FindMin(int qs, int qe)
  {
*/
/*    if (qs < 0 || qe > elements_amount_-1 || qs > qe)
    {
      std::cout<<("Invalid input values");
      return -1;
    }*//*


    return FindMin(0, elements_amount_-1, qs, qe, 0);
  }

  long long FindMax(int qs, int qe)
  {
*/
/*    if (qs < 0 || qe > elements_amount_-1 || qs > qe)
    {
      std::cout<<("Invalid input values");
      return -1;
    }*//*


    return FindMax(0, elements_amount_-1, qs, qe, 0);
  }

  long long FindSecondMin(int qs, int qe,long long first_min)
  {
*/
/*    if (qs < 0 || qe > elements_amount_-1 || qs > qe)
    {
      std::cout<<("Invalid input values");
      return -1;
    }*//*


    return FindSecondMin(0, elements_amount_-1, qs, qe, 0,first_min);
  }

  long long FindSecondMax(int qs, int qe,long long second_max)
  {
*/
/*    if (qs < 0 || qe > elements_amount_-1 || qs > qe)
    {
      std::cout<<("Invalid input values");
      return -1;
    }*//*


    return FindSecondMax(0, elements_amount_-1, qs, qe, 0,second_max);
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


*/
/* si - index of current node in segment tree
    ss and se - starting and ending indexes of elements for current nodes.
    us and ue - starting and ending indexes of update query
    diff - which we need to add in the range us to ue *//*


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



*/
/*
    si - Index of current node in the segment tree.
    ss and se  - Starting and ending indexes of the segment represented by tree[si]
    qs and qe  - Starting and ending indexes of query range
    *//*


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



  long long FindMax(int ss, int se, int qs, int qe, int si,int index)
  {
    if (qs > qe) {
      return INT64_MIN;
    }if
    if (qs == ss && qe == se) {
      if(max_tree_[si]>index){
        index=
      }
      return max_tree_[si];
    }
    int middle = (ss + se) / 2;
    return std::max(FindMax( ss, middle,qs, std::min(qe, middle),2*si + 1,index),
                    FindMax(  middle + 1, se,std::max(qs, middle + 1), qe,2*si + 2,index))
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

int main() {

  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n,q;
  std::cin>>n>>q;
  std::vector<int> values;
  int value;

  SegmentTree tree;
  tree.Construct(n);
  for(int i=0;i<n;i++) {
    std::cin>>value;
    tree.UpdateValue(i,value);
  }
  char request;
  int x,y;
  for(int i=0;i<q;i++){
    std::cin>>request;
    switch (request) {
      case '?': {
        std::cin >>x>>y;
        long long first_min=tree.FindMin(x,y-1);
        long long first_max=tree.FindMax(x,y-1);
        long long second_max=tree.FindSecondMax(x,y-1,first_max);
        long long second_min=tree.FindSecondMin(x,y-1,first_min);
        std::cout<<std::max(second_min*first_min,second_max*first_max)<<"\n";
        break;
      }
      case '=': {
        std::cin>>x>>y;
        tree.UpdateValue(x,y);
        break;
      }
    }
  }
  return 0;
}


*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

int main() {

  //task 1
/*  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);*//*


  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n,q;
  std::cin>>n>>q;
  std::vector<long long> values;
  long long value;
  for(int i=0;i<n;i++){
    std::cin>>value;
    values.push_back(value);
  }

  char request;
  int x,y;
  for(int i=0;i<q;i++){
    std::cin>>request;
    switch (request) {
      case '?': {
        long long max=INT64_MIN;
        std::cin >>x>>y;
        for(int i=x-1;i<y;i++){
          for(int j=i+1;j<y;j++){
            if(values[i]*values[j]>max){
              max=values[i]*values[j];
            }
          }
        }
        std::cout<<max<<"\n";
        break;
      }
      case '=': {
        std::cin >>x>>y;

        values[x-1]=y;
        break;
      }
    }
  }
*/


  //task 2
  int const VALUE = 100000;

  std::ios_base::sync_with_stdio(false);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  std::cin.tie(nullptr);
  int l, r, q;
  std::cin >> l >> r >> q;
  std::string request;
  int a, b;
  std::map<std::string, int> teams_results;

/*  auto cmp = [](const std::pair<std::string,long long>& team1, const std::pair<std::string,long long>& team2) {
    return (team1.second<team2.second);
  };*/

  struct cmp {
    bool operator()(const std::pair<std::string, int> &team1,
                    const std::pair<std::string, int> &team2) const {
      return (team1.second < team2.second);
    }
  };

  std::set<std::pair<std::string, int>, cmp> best_teams_r;

  for (int i = 0; i < q; i++) {
    std::cin >> request;
    if (request == "show") {
      if (best_teams_r.empty()) {
        std::cout << 0 << "\n";
        continue;
      }
      std::vector<std::string> result;
      for (auto team : best_teams_r) {
        if (r - l + 1 == result.size() || best_teams_r.size()<l ||best_teams_r.size()-l<result.size() ) {
          break;
        }
        result.push_back(team.first);
      }

      std::cout << result.size() << "\n";
      for (int i = result.size() - 1; i >= 0; i--) {
        std::cout << result[i] << "\n";
      }

    } else {

/*      // request is a team name
      std::cin>>a>>b;
      teams_results.erase(request);
      teams_results.insert(std::make_pair(request,a*VALUE-b));
      best_teams.erase(request);
      best_teams.insert(request);

      if(best_teams.size()==r+1){
        best_teams.erase(--best_teams.end());
      }*/

      std::cin >> a >> b;

        auto it = teams_results.find(request);
        if (it != teams_results.end()) {
          int team_result = it->second;
          auto find_team_r = best_teams_r.find(std::pair<std::string, int>(request, team_result));
          if (find_team_r != best_teams_r.end()) {
            best_teams_r.erase(find_team_r);
          }
        }

        //operator [] will insert new pair, if there is no request key
        teams_results[request] = a * VALUE - b;
        best_teams_r.insert(std::make_pair(request, teams_results[request]));
        if (best_teams_r.size() == r+1) {
          best_teams_r.erase((best_teams_r.begin()));
        }
      }
    }

  return 0;
}







/*

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;
struct classcomp {
  bool operator() (const pair<string, long long>& a, const pair<string, long long>& b) const
  {
    return (a.second < b.second);
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int l, r, q;
  cin >> l >> r >> q;
  set<pair<string,long long>,classcomp> teams_set;
  map<string, long long> teams_map;
  vector<string> result;
  for (int i = 0; i < q; i++) {
    string str;
    cin >> str;
    if (str == "show") {
      if (teams_set.empty()) {
        cout << 0 << endl;
      }
      else {
        int count = 0;
        string result = "";
        string temp = "";
        for (auto team : teams_set) {
          if (teams_set.size() < l) break;
          if (teams_set.size() - l < count) break;
          if (count == r - l + 1) break;
          temp = team.first + "\n";
          temp += result;
          result = temp;
          count++;
        }
        cout << count << endl;
        cout << result;
      }
    }
    else {
      int tasks, fine;
      cin >> tasks >> fine;
      if (tasks > 0) {
        auto it = teams_map.find(str);
        if (it != teams_map.end()) {
          long long res = it->second;
          auto find_ = teams_set.find(pair<string, long long>(str, res));
          if (find_ != teams_set.end()) {
            teams_set.erase(find_);
          }
        }
        teams_map [str] = tasks * pow(10, 5) - fine;
        teams_set.insert(make_pair(str, tasks * pow(10, 5) - fine));
        if (teams_set.size() > (r)) {
          teams_set.erase((teams_set.begin()));
        }
      }
    }
  }

}*/
