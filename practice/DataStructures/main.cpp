
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <fstream>

#include "SegmentTree.cpp"
#include "SQRTDecomposition.cpp"

int LowerBound(std::vector<int>& array,int value){
  int middle = 0;
  int left=0;
  int right=array.size();
  while(left<right){
    middle=(left+right)/2;
    if(value<=array[middle]){
      right=middle;
    } else{
      left=middle+1;
    }
  }
  return left;
}

int UpperBound(std::vector<int>& array,int value){
  int middle = 0;
  int left=0;
  int right=array.size();
  while(left<right){
    middle=(left+right)/2;
    if(value<array[middle]){
      right=middle;
    } else{
      left=middle+1;
    }
  }
  return left;
}

bool BinarySearch(std::vector<int>& array,int value){
  int middle = 0;
  int left=0;
  int right=array.size();
  while(left<right){
    middle=(left+right)/2;
    if(value==array[middle]){
      return true;
    } else if(value<array[middle]){
      right=middle;
    } else {
      left=middle+1;
    }
  }
  return false;
}

void IsHeap(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int values_amount;
  std::cin >> values_amount;
  int values[values_amount+1];

  for (int i = 1; i < values_amount+1; i++) {
    int element = 0;
    std::cin >> element;
    values[i]=element;
  }

  values_amount+=1;

  bool is_heap = 0;
  int i = 1;
  for (; i < (values_amount / 2);i++) {
    if (values[i] > values[2 * i] || values[i] > values[2 * i + 1]) {
      is_heap = 1;
      break;
    }
  }
  if (i == (values_amount / 2)) {
    if (values[i] > values[2 * i]) {
      is_heap = 1;
    }
  }
  if (is_heap==0) {
    std::cout << "Yes";
  }
  else {
    std::cout << "No";
  }
}


void SetAllKeys(std::vector<int>& values,int m,int c,int n) {
  int value = 0;
  int index;
  for (int i = 0; i < n; i++) {
    std::cin >> value;
    for (int j = 0; j < m; j++) {
      index = ((value % m) + c * j) % m;
      if (values[index] == -1) {
        values[index] = value;
        break;
      }
      if (values[index] == value) {
        break;
      }
    }
  }
}


long long HuffmanCodingBytesAmount(const std::vector<long long>& frequencies){

  std::priority_queue<long long, std::vector<long long>, std::greater<long long> > frequencies_queue;
  for(int i=0;i<frequencies.size();i++){
    frequencies_queue.push(frequencies[i]);
  }
  long long bytes_amount=0;
  while(frequencies_queue.size()!=1){
    long long current_min_sum=0;
    current_min_sum+=frequencies_queue.top();
    frequencies_queue.pop();
    current_min_sum+=frequencies_queue.top();
    frequencies_queue.pop();
    frequencies_queue.push(current_min_sum);
    bytes_amount+=current_min_sum;
  }

  return bytes_amount;
}


struct Team {
  int x_=0;
  int y_=0;
  int z_=0;

  Team()=default;

  bool operator <(const Team &rhs) const {
    return (x_ < rhs.x_ || (x_ == rhs.x_ && y_ < rhs.y_) ||
        (x_ == rhs.x_ && y_ == rhs.y_ && z_ < rhs.z_));
  }
};


class FenwickTree {
 public:
  FenwickTree(int size) {
    fenwick_tree=std::vector<int>(size,INT_MAX);
  }

  void Update(int index,int value) {
    for (; index < fenwick_tree.size(); index |= (index + 1)) {
      fenwick_tree[index] = std::min(fenwick_tree[index], value);
    }
  }

  int GetMin(int right) {
    int result = INT_MAX;

    for (; right >= 0; right = (right & (right + 1)) - 1) {
      result = std::min(result, fenwick_tree[right]);
    }
    return result;
  }
 private:
  std::vector<int> fenwick_tree;
};




struct Order{
  double extra_fee_;
  double performance_;
  double term_;
  //Order():extra_fee_(INT_MAX),performance_(INT_MAX),term_(0){}
  Order(double extra_fee,double performance,double term):
      extra_fee_(extra_fee),performance_(performance),term_(term){};

/*  bool operator<(const Order order) const
  {
    return extra_fee_>order.extra_fee_;
  }*/
/*  bool operator>(const Order order)
  {
    if(term_ - order.term_ == 0){
      return order.extra_fee_ - extra_fee_;
    }
    return term_ - order.term_;
  }*/
};

struct CompareOrders{
  bool operator()(const Order& order1, const Order& order2) {
/*  if(order1.term_ == order2.term_ ){
    return order2.extra_fee_ < order1.extra_fee_;
  }*/
    return order1.extra_fee_ < order2.extra_fee_;
  }
};

struct CompareOrdersByDeadline {
  bool operator()(const Order& order1, const Order& order2) {
/*  if(order1.term_ == order2.term_ ){
    return order2.extra_fee_ < order1.extra_fee_;
  }*/
    return order1.term_ > order2.term_;
  }
};

/*
int CompareOrders(const void * x1, const void * x2)
{
  if((*(Order*)x1).term_ - (*(Order*)x2).term_ == 0){
    return (*(Order*)x2).extra_fee_ - (*(Order*)x1).extra_fee_;
  }
  return(*(Order*)x1).term_ - (*(Order*)x2).term_;
}
*/

/*
int main() {

  //task 40
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //Random();
  std::ifstream in("lazy.in");
  std::ofstream out("lazy.out");
  int orders_amount;
  in >> orders_amount;
  std::priority_queue<Order, std::vector<Order>, CompareOrdersByDeadline> orders_by_deadline;
  std::priority_queue<Order, std::vector<Order>, CompareOrders> queue;

  //std::vector<Order>orders;
  // Order new_order;
  for (int i = 0; i < orders_amount; i++) {
    double extra_fee, performance, term;
    in >> extra_fee >> performance >> term;
    orders_by_deadline.push(Order(extra_fee, performance, term));
    //orders.push_back(new_order);
  }

  //int size=orders.size();
  // Order temp=orders[orders_amount-1];
  //std::qsort(orders,orders_amount,sizeof(Order),CompareOrders);
  // std::sort(orders,orders+orders_amount,CompareOrders);
  */
/*std::sort(orders,orders+orders_amount-1,[](const Order& order1, const Order& order2){
    if(order1.term_ ==order2.term_ ){
      return order2.extra_fee_ < order1.extra_fee_;
    }
    return order1.term_ < order2.term_;
  });*//*




  // Order* order=new Order;

  double total_time = 0.;
  double extra_time = 0.;
  double money = 0.;
  //std::priority_queue<Order, std::vector<Order>,std::less<std::vector<Order>::value_type> > queue;

  //first element
  //Order curr_order;
  Order curr_order = orders_by_deadline.top();
  orders_by_deadline.pop();
  extra_time = curr_order.performance_ - curr_order.term_;
  if (curr_order.performance_ > curr_order.term_) {
    money += (double)extra_time / curr_order.extra_fee_;
    double performance=curr_order.performance_;
    curr_order.performance_ = curr_order.performance_ - extra_time;
  }
  total_time += std::min(curr_order.performance_, curr_order.term_);
  if (curr_order.performance_ > 0) {
    queue.push(curr_order);
  }

  //other elements
  for (int i = 1; i < orders_amount; i++) {
    curr_order = orders_by_deadline.top();
    orders_by_deadline.pop();
    double extra_fee=curr_order.extra_fee_;
    double performance=curr_order.performance_;
    double term=curr_order.term_;

    extra_time = total_time + performance - term;
    if (extra_time <= 0) {
      total_time += performance;
      if (curr_order.performance_ > 0) {
        queue.push(curr_order);
      }
      continue;
    }

    bool is_performed = false;
    total_time = term;
    while (extra_time > 0 && !queue.empty() && !is_performed && extra_fee < queue.top().extra_fee_) {
      Order order = queue.top();
      queue.pop();
      double curr_money = 0.;
      if (extra_time < order.performance_) {
        curr_money = extra_time / order.extra_fee_;
        order.performance_ =order.performance_ - extra_time;
        is_performed = true;
        queue.push(order);
      } else {
        curr_money = order.performance_ / order.extra_fee_;
        extra_time -= order.performance_;;
      }
      money += curr_money;
    }

    if (!is_performed) {
      curr_order.performance_ = curr_order.performance_ - extra_time;
      money += extra_time / curr_order.extra_fee_;
    }

    if (curr_order.performance_ > 0) {
      queue.push(curr_order);
    }

  }
  out << std::fixed << std::setprecision(2) << money;
  return 0;
}*/












#include <iostream>
#include <vector>
#include <cfloat>


int main() {

  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);


  int n,m;

  std::cin >> n >> m;
  std::vector<double> jobs(n);
  std::vector<double> workers(m);

  double value;
  for (int i = 0; i < n; ++i) {
    std::cin >> value;
    jobs[i]=value;
  }

  for (int i = 0; i < m; ++i) {
    std::cin >> workers[i];
  }
  std::sort(jobs.rbegin(), jobs.rend());

  std::vector<int> workers_answer(n);
  std::vector<int> amount(m, 0);
  std::vector<double> jobs_time(m, 0);

  int k = n / m;
  int count = n % m;
  double min;
  int job_index;


  for (int i = 0; i < n; ++i) {
    min = DBL_MAX;
    for (int j = 0; j < m; ++j) {
      if (min > jobs_time[j]+jobs[i]/workers[j] && amount[j] <= k) {
        min = jobs_time[j]+jobs[i]/workers[j];
        job_index = j;
      }
    }
    amount[job_index]++;

    if (amount[job_index] == k+1) {
      count--;
    }

    if (count == 0) {
      k--;
      count--;
    }
    workers_answer[i] = job_index+1;
    jobs_time[job_index] = min;
  }

  std::cout << *std::max_element(jobs_time.begin(),jobs_time.end()) << '\n';
  for (int i = 0; i < n; ++i) {
    std::cout << workers_answer[i] << '\n';
  }

  return 0;
}
