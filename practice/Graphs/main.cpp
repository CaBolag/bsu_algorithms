
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

struct Edge{
  Edge(int vertex1,int vertex2,int weight):vertex1_(vertex1),vertex2_(vertex2),weight_(weight){}
  int vertex1_=0;
  int vertex2_=0;
  int weight_=0;
/*  bool operator <(const Edge& another_edge){
    return weight_<another_edge.weight_;
  }*/

};
bool CompareEdgeDescendingOrder(Edge edge1, Edge edge2)
{
  return (edge1.weight_>edge2.weight_);
}


struct DSU{

  std::vector<int> parents_;
  std::vector<std::set<int>> neighbours_;
  std::vector<int>  sizes_;
  int sets_amount_;
  DSU(int n){
    parents_=std::vector<int>(n+1,0);
    sizes_=std::vector<int>(n+1,1);
    neighbours_=std::vector<std::set<int>>(n+1,std::set<int>());
    sets_amount_=n;
    for (int i = 0; i < n+1; i++) {
      parents_[i] = i;
      neighbours_[i].insert(i);
    }
  }

  int GetParent(int x) {
    if (x == parents_[x]) {
      return x;
    }
    parents_[x] = GetParent(parents_[x]);
    return parents_[x];
  }

  void Union(int x, int y) {
    x = GetParent(x);
    y = GetParent(y);
    if (x != y) {
      if (sizes_[x] < sizes_[y]) {
        std::swap(x, y);
      }
      parents_[y] = x;
      sizes_[x] += sizes_[y];
      neighbours_[x].merge(neighbours_[y]);
      for(int neighbour:neighbours_[x]){
        neighbours_[neighbour]=neighbours_[x];
      }
      sets_amount_--;
    }
  }

};

std::vector<std::vector<int>> ReadAdjacencyMatrixFromFile(){
  int n,m;
  std::cin>>n>>m;
  std::vector<std::vector<int>> adjacency_matrix(n,std::vector<int>(n,0));
  for(int i=0;i<m;i++){
    int vertex1;
    int vertex2;
    std::cin>>vertex1>>vertex2;
    adjacency_matrix[vertex1-1][vertex2-1]=1;
    adjacency_matrix[vertex2-1][vertex1-1]=1;
  }
  return adjacency_matrix;
}


std::vector<std::vector<int>> ReadAdjacencyListFromFile(){
  int n,m;
  std::cin>>n>>m;
  std::vector<std::vector<int>> adjacency_list(n,std::vector<int>(0,0));
  int vertex1;
  int vertex2;
  for(int i=0;i<m;i++){
    std::cin>>vertex1>>vertex2;
    adjacency_list[vertex1-1].push_back(vertex2);
    adjacency_list[vertex2-1].push_back(vertex1);
  }
  return adjacency_list;
}

std::vector<int> GetCanonicalViewFromAdjacencyMatrix(){
  int n;
  std::cin>>n;
  std::vector<int>canonical_view(n,0);
  int vertex1;
  int vertex2;
  for(int i=0;i<n;i++) {
    for (int j = 0; j < n; j++) {
      int flag;
      std::cin>>flag;
      if(flag){
        canonical_view[j]=i+1;

      }
    }
  }
  return canonical_view;
}

std::vector<int> GetCanonicalViewFromEdgesList(){
  int n;
  std::cin>>n;
  std::vector<int>canonical_view(n,0);
  int vertex1;
  int vertex2;
  for(int i=0;i<n-1;i++){
    std::cin>>vertex1>>vertex2;
    canonical_view[vertex2-1]=vertex1;
  }
  return canonical_view;
}

std::vector<int> TraversalOrderBFS(int start,std::vector<std::vector<int>> adjacency_matrix) {
  std::queue<int> q;
  std::vector<bool> visited(adjacency_matrix.size(), false);
  int index = 0;
  std::vector<int> traversal_order(adjacency_matrix.size(),-1);
  int current_vertex;

  for(int k=0;k<adjacency_matrix.size();k++) {
    if (!visited[k]) {
      index+=1;
      traversal_order[k] = index;
      visited[k] = true;
      q.push(k);
      while (!q.empty()) {
        current_vertex = q.front();
        q.pop();

        for (int i = 0; i < adjacency_matrix.size(); i++) {
          if (adjacency_matrix[current_vertex][i] == 1 && !visited[i]) {
            visited[i] = true;
            index += 1;
            traversal_order[i] = index;
            q.push(i);
          }
        }
      }
    }
  }
  return traversal_order;
}


void TraversalOrderDFS(int vertex,
                                   std::vector<std::vector<int>> adjacency_matrix,
                                   int n,
                                   std::vector<bool>& visited,
                                   std::vector<int>& indexes,
                                   int& last_index){
  visited[vertex]= true;
  if(indexes[vertex]==0){
    last_index+=1;
    indexes[vertex]=last_index;
  }
  for(int i=0;i<n;i++){
    if(adjacency_matrix[vertex][i] && !visited[i]){
      TraversalOrderDFS(i,adjacency_matrix,n,visited,indexes,last_index);
    }
  }
}




/*

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);


*/
/*  int n;
  std::cin>>n;
  std::vector<std::vector<int>> adjacency_matrix(n,std::vector<int>(n,0));
  int value;
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      std::cin>>value;
      adjacency_matrix[i][j]=value;
    }
  }

  std::vector<int> traversal_order(n,0);
  std::vector<bool> visited(n, false);
  int last_index=0;
  for(int i=0;i<n;i++) {
    TraversalOrderDFS(i, adjacency_matrix, n, visited, traversal_order, last_index);
  }
  for(int index:traversal_order){
    std::cout<<index<<" ";
  }*//*



*/
/*
  int n, q;

  std::cin >> n >> q;
  DSU dsu(n);
*//*

*/
/*  for (int i = 0; i < n; i++) {
    dsu.parents_[i] = i;
    dsu.size[i] = 1;
  }*//*
*/
/*


  int u, v;
  for (int i = 0; i < q; i++) {
    std::cin >> u >> v;
    dsu.Union(u,v);
    std::cout << n - dsu.sets_amount_ << "\n";
  }
*//*




*/
/*  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<std::pair<int, int>>> graph(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    graph[u - 1].push_back(std::make_pair(v - 1, w));
    graph[v - 1].push_back(std::make_pair(u - 1, w));
  }
  std::vector<long long> d(n, INT64_MAX);
  d[0] = 0;
  std::set<std::pair<int, int> > q;
  q.insert(std::make_pair(d[0], 0));
  while (!q.empty()) {
    int v = q.begin()->second;
    q.erase(q.begin());
    for (int j = 0; j < graph[v].size(); ++j) {
      int to = graph[v][j].first;
      int length = graph[v][j].second;
      if (d[v] + length < d[to]) {
        q.erase(std::make_pair(d[to], to));
        d[to] = d[v] + length;
        q.insert(std::make_pair(d[to], to));
      }
    }
  }
  std::cout << d[n - 1];*//*


int vertex_amount,edge_amount;
std::cin>>vertex_amount>>edge_amount;
DSU components(vertex_amount);
std::vector<Edge> edges;
int vertex1,vertex2,weight;
for(int i=0;i<edge_amount;i++){
  std::cin>>vertex1>>vertex2>>weight;
  Edge current_edge(vertex1,vertex2,weight);
  edges.push_back(current_edge);
}


std::sort(edges.begin(),edges.end(),CompareEdgeDescendingOrder);
std::vector<int> answers(vertex_amount,-1);
  for (int i = 0;i <edge_amount ;i++) {
    if( components.neighbours_[edges[i].vertex1_].find(1)!= components.neighbours_[edges[i].vertex1_].end()){
      for(int vertex:components.neighbours_[edges[i].vertex2_]){
        if(answers[vertex-1]==-1){
          answers[vertex-1]=edges[i].weight_;
        }
      }
      components.Union(edges[i].vertex1_,edges[i].vertex2_);
    } else if(components.neighbours_[edges[i].vertex2_].find(1)!= components.neighbours_[edges[i].vertex2_].end()){
      for(int vertex:components.neighbours_[edges[i].vertex2_]){
        if(answers[vertex-1]==-1){
          answers[vertex-1]=edges[i].weight_;
        }
      }
      components.Union(edges[i].vertex1_,edges[i].vertex2_);
    }else{
      components.Union(edges[i].vertex1_,edges[i].vertex2_);
    }
  }

  for(int i=1;i<answers.size()-1;i++){
    std::cout<<answers[i]<<" ";
  }
  std::cout<<answers[answers.size()-1];

  return 0;
}
*/






























/*

#include <iostream>
#include <vector>
#include <queue>


//Prim’s Algorithm
std::vector<std::vector<std::pair<int, int>>> FindMST(const std::vector<std::vector<std::pair<int, int>>>& graph) {

  std::priority_queue<std::pair<int, std::pair<int, int>>,std::vector<std::pair<int, std::pair<int, int>>>,std::less<>> queue;
  std::vector<std::vector<std::pair<int, int>>> MST(graph.size() + 1);

  for (int i=0;i<graph[1].size();++i) {
    queue.push(std::make_pair(graph[1][i].second, std::make_pair(1, graph[1][i].first)));
  }
  std::vector<bool> marked(graph.size()+1, false);
  marked[1] = true;
  int weight;
  int marked_vertex;
  int not_marked_vertex;

  while (!queue.empty()) {
    weight = queue.top().first;
    marked_vertex = queue.top().second.first;
    not_marked_vertex = queue.top().second.second;
    queue.pop();

    if (marked[not_marked_vertex]) {
      continue;
    }

    MST[not_marked_vertex].emplace_back(marked_vertex, weight);
    MST[marked_vertex].emplace_back(not_marked_vertex, weight);
    marked[not_marked_vertex] = true;

    for (auto pair: graph[not_marked_vertex]) {
      if (!marked[pair.first]) {
        queue.push(std::make_pair(pair.second, std::make_pair(not_marked_vertex, pair.first)));
      }
    }
  }
  return MST;
}

std::vector<int> bfs(std::vector<std::vector<std::pair<int, int>>>& MST) {
  int n=MST.size();
  std::vector<int> result(n+1,-1);

  std::queue<std::pair<int, int>> queue;
  std::vector<bool> visited(n+1,false);

  queue.push(std::make_pair(1, INT32_MAX));
  visited[1] = true;

  int current_vertex,current_edge;

  while (!queue.empty()) {
    current_vertex = queue.front().first;
    current_edge = queue.front().second;
    queue.pop();

    for (auto &node: MST[current_vertex]) {
      int to = node.first;
      int weight = node.second;

      if (!visited[to]) {
        result[to] = std::min(current_edge, weight);
        queue.push(std::make_pair(to, std::min(current_edge, weight)));
        visited[to] = true;
      }
    }
  }
  return result;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int vertex_amount,edge_amount;
  std::cin>>vertex_amount>>edge_amount;
  std::vector<std::vector<std::pair<int, int>>> graph(vertex_amount + 1);

  int vertex1,vertex2,weight;
  for(int i=0;i<edge_amount;i++){
    std::cin>>vertex1>>vertex2>>weight;
    graph[vertex1].emplace_back(vertex2, weight);
    graph[vertex2].emplace_back(vertex1, weight);
  }

  std::vector<int> result(vertex_amount+1,-1);
  std::vector<std::vector<std::pair<int, int>>> MST;
  MST=FindMST(graph);
  result=bfs(MST);

  for(int i = 2; i < vertex_amount; i++) {
    std::cout << result[i] << "\n";
  }
  std::cout << result[vertex_amount];
  return 0;
}
*/


