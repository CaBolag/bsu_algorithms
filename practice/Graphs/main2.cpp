/*
#include <iostream>


const int MAX_EDGE = 2000002;
const int MAX_VERTEX =1000001;
const int INF = (int)1e9;

int capacity[MAX_EDGE], end[MAX_EDGE], next_edge[MAX_EDGE],first_edge[MAX_VERTEX], visited[MAX_VERTEX];
int edge_count,destination_vertex;

void AddEdge(int u, int v, int cap) {
  // Прямое ребро
  end[edge_count] = v;                   
  next_edge[edge_count] = first_edge[u];    
  first_edge[u] = edge_count;         
  capacity[edge_count++] = cap; 
  
  // Обратное ребро
  end[edge_count] = u;                   
  next_edge[edge_count] = first_edge[v];     
  first_edge[v] = edge_count;              
  capacity[edge_count++] = 0;           
}

int FindFlow(int u, int flow) {
  if (u == destination_vertex) return flow; 
  visited[u] = true;
  
  for (int edge = first_edge[u]; edge != -1; edge = next_edge[edge]) {
    int to = end[edge];
    if (!visited[to] && capacity[edge] > 0) {
      int min_result = FindFlow(to, std::min(flow, capacity[edge])); 
      
      if (min_result > 0) {                  
        capacity[edge] -= min_result;   
        capacity[edge ^ 1] += min_result;  
        return min_result;
      }
    }
  }
  return 0;
}

int main() {
  std::fill(first_edge, first_edge + MAX_VERTEX, -1);
  int vertex_amount, edge_amount, source_vertex;

  std::cin >> vertex_amount >> edge_amount;
  
  source_vertex = 1;
  destination_vertex = vertex_amount;
  for (int i = 0, u, v, cap; i < edge_amount; i++) {
    std::cin >> u >> v >> cap;
    AddEdge(u, v, cap);
  }
 
  
  int max_flow = 0;
  int result= 0;
  while ((result= FindFlow(source_vertex, INF)) > 0) {
    std::fill(visited, visited + MAX_VERTEX, false);
    max_flow += result;
  }

  std::cout << max_flow << "\n";
  return 0;
}*/


/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <vector>
#include <iterator>
#include <utility>
#include <map>
#include "math.h"
#include <string>
#include <iterator>
#include <iomanip>



unsigned long long NOD(unsigned long long n1, unsigned long long n2)
{
  if (n2 == 0) {
    return n1;
  }
  else {
    return NOD(n2, n1%n2);
  }
}

unsigned long long NOK(unsigned long long n1, unsigned long long n2)
{
  return n1*n2 / NOD(n1, n2);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);


  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> v(n);
  std::vector<std::pair<int,int>> r(m);
  std::vector<std::pair<int,int>> t(m);
  for (int i = 0; i < m; i++) {
    std::cin >> r[i].first >> t[i].first >> r[i].second >> t[i].second;
    v[r[i].first - 1].push_back(i);
    v[r[i].second - 1].push_back(i);
  }
  std::vector<int> anc(n);
  std::vector<int> ind(n);
  std::vector<int> d(n);

  for (int i = 1; i < n; i++) {
    d[i] = INT_MAX;
  }
  std::set <std::pair<int, int> > q;
  q.insert(std::make_pair(d[0], 0));
  std::vector<bool> b(n);
  for (unsigned long long i = 0; i < n; i++) {
    b[i] = false;
  }
  while (!q.empty()) {
    unsigned long long temp = q.begin()->second;
    q.erase(q.begin());
    b[temp] = true;
    for (unsigned long long i=0; i<v[temp].size();i++){
      if (r[v[temp][i]].first-1 == temp && !b[r[v[temp][i]].second-1]) {
        if (d[r[v[temp][i]].second-1] > (int)(d[r[v[temp][i]].first-1] / NOK(t[v[temp][i]].first, t[v[temp][i]].second)+1)*NOK(t[v[temp][i]].first, t[v[temp][i]].second)) {
          q.erase(std::make_pair(d[r[v[temp][i]].second - 1], r[v[temp][i]].second - 1));
          d[r[v[temp][i]].second-1] = ((int)((d[r[v[temp][i]].first - 1])/ NOK(t[v[temp][i]].first, t[v[temp][i]].second) + 1))* NOK(t[v[temp][i]].first, t[v[temp][i]].second);
          anc[r[v[temp][i]].second-1] = r[v[temp][i]].first-1;
          ind[r[v[temp][i]].second-1] = v[temp][i]+1;
          q.insert(std::make_pair(d[r[v[temp][i]].second - 1], r[v[temp][i]].second - 1));
        }
      }
      else if (r[v[temp][i]].second-1 == temp && !b[r[v[temp][i]].first-1]) {
        if (d[r[v[temp][i]].first - 1] > (int)((d[r[v[temp][i]].second - 1]) / NOK(t[v[temp][i]].first, t[v[temp][i]].second)+1)*NOK(t[v[temp][i]].first, t[v[temp][i]].second)) {
          q.erase(std::make_pair(d[r[v[temp][i]].first - 1], r[v[temp][i]].first - 1));
          d[r[v[temp][i]].first - 1] = (int)((d[r[v[temp][i]].second - 1]) /NOK(t[v[temp][i]].first, t[v[temp][i]].second) + 1)* NOK(t[v[temp][i]].first, t[v[temp][i]].second);
          anc[r[v[temp][i]].first - 1] = r[v[temp][i]].second - 1;
          ind[r[v[temp][i]].first - 1] = v[temp][i]+1;
          q.insert(std::make_pair(d[r[v[temp][i]].first - 1], r[v[temp][i]].first - 1));

        }
      }
    }
  }

  std::cout << d[n-1]<<".5" << "\n";
  std::vector<int> y(n);
  int i = 0;
  int x = n - 1;
  while (x > 0) {
    y[i] = ind[x];
    i++;
    x = anc[x];
  }

  for (int j = i-1; j >=0; j--) {
    std::cout << y[j]<<" ";
  }
  return 0;
}
*/



/*#include <iostream>
#include <vector>
#include <queue>
#include <set>

long long NOD(long long number1, long long number2)
{
  if (number2 == 0) {
    return number1;
  }
  else {
    return NOD(number2, number1%number2);
  }
}

long long NOK(long long number1,long long number2)
{
  return number1*number2 / NOD(number1, number2);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);


  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<std::pair<long long, long long>>> graph(n);

  int r1,t1,r2,t2;
  for (int i = 0; i < m; i++) {
    std::cin >> r1 >> t1 >> r2>>t2;
    graph[r1 - 1].push_back(std::make_pair(r2 - 1, NOK(t1,t2)));
    graph[r2 - 1].push_back(std::make_pair(r1 - 1, NOK(t1,t2)));
  }

  std::vector<double> dist(n, INT64_MAX);
  std::vector<int> path(n-1, 1);
  dist[0] = 0;
  std::set<std::pair<long long, long long> > queue;
  queue.insert(std::make_pair(dist[0], 0));

  while (!queue.empty()) {
    long long local_min=INT64_MAX;
    int v = queue.begin()->second;
    queue.erase(queue.begin());

    for (int j = 0; j < graph[v].size(); ++j) {
      int next_vertex = graph[v][j].first;
      double length=graph[v][j].second;
      double new_length=graph[v][j].second;//=NOK((unsigned long long)dist[v],(unsigned long long)length)+0.5;
      int i=2;
      //unsigned long long temp=dist[v];

      while(new_length<dist[v]){
        new_length+=length;
      }
      new_length+=0.5;
      if (new_length < dist[next_vertex]) {
        queue.erase(std::make_pair(dist[next_vertex], next_vertex));
        dist[next_vertex] = new_length;
        queue.insert(std::make_pair(dist[next_vertex], next_vertex));

        if(dist[next_vertex]<local_min){
          local_min=dist[next_vertex];
          path[v+1]=next_vertex+1;
        }
      }
    }
  }
  std::cout << dist[n - 1]<<"\n";
  for(int i=0;i<path.size()-1;i++){
    std::cout<<path[i]<<" ";
  }
  std::cout<<path[path.size()-1];

  return 0;

}*/


/*
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <float.h>
#include <limits>


long long gcd(long long a, long long b)
{
  return b == 0 ? a : gcd(b, a % b);
}

long long lcm(long long a, long long b)
{
  return (a / gcd(a, b)) * b;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);


*//*
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<std::pair<long long, long long>>> graph(n);

  int r1,t1,r2,t2;
  for (int i = 0; i < m; i++) {
    std::cin >> r1 >> t1 >> r2>>t2;
    graph[r1 - 1].push_back(std::make_pair(r2 - 1, lcm(t1,t2)));
    graph[r2 - 1].push_back(std::make_pair(r1 - 1, lcm(t1,t2)));
  }

  std::vector<double> d (n, INF),  p (n);
  d[0] = 0.5;

  std::vector<char> u (n);
  for (int i=0; i<n; i++) {
    int v = -1;
    for (int j=0; j<n; j++)
      if (!u[j] && (v == -1 || d[j] < d[v]))
        v = j;
    if (d[v] == INF)
      break;
    u[v] = true;

    for (size_t j=0; j<graph[v].size(); ++j) {
      int to = graph[v][j].first;
      //len = graph[v][j].second;
      double default_length=graph[v][j].second;
      double length=graph[v][j].second;//=NOK((unsigned long long)dist[v],(unsigned long long)length)+0.5;
      int i=2;
      //unsigned long long temp=dist[v];
      while(length<d[v]){
        length+=default_length;
      }
      length+=0.5;
      if (length < d[to]) {
        d[to] = length;
        p[to] = v;
      }
    }
  }

    std::cout << d[n-1]<<"\n";







  std::vector<int> path;
  for (int v=n-1; v!=0; v=p[v]){
    path.push_back (v);
  }
  path.push_back (0);
  std::reverse(path.begin(), path.end());
  for(int i=1;i<path.size()-1;i++){
    std::cout<<path[i]<<" ";
  }
  std::cout<<path[path.size()-1];
  return 0;
*//*





  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<std::pair<int, long long>>> graph(n);
  std::vector<std::vector<int>> edges(n);

  for (int i = 0; i < m; i++) {
    int r1, r2;
    long long t1,t2;
    std::cin >> r1 >> t1 >> r2 >> t2;
    graph[r1 - 1].push_back(std::make_pair(r2 - 1, lcm(t1, t2)));
    graph[r2 - 1].push_back(std::make_pair(r1 - 1, lcm(t1, t2)));
    edges[r1-1].push_back(i+1);
    edges[r2-1].push_back(i+1);
  }

  std::vector<long double> dist(n, std::numeric_limits<long double>::max());
  std::vector<int> parents(n, 0);
  std::vector<int> ans_edges(n,0);
  std::set<std::pair<long double, int>> queue;

  dist[0] = 0.;
  queue.insert(std::make_pair(dist[0], 0));

  //Dijkstra's algorithm
  while (!queue.empty()) {

    // long long local_min = INT64_MAX;
    int v = queue.begin()->second;
    long double current_dist=queue.begin()->first;

    queue.erase(queue.begin());
    if(dist[v]<current_dist) continue;

    for (int j = 0; j < graph[v].size(); ++j) {
      int next_vertex = graph[v][j].first;
      long long length = graph[v][j].second;
      int edge=edges[v][j];
      long double length_to_use_edge = (long double)0.5+(long double)length+(long double)std::floor(current_dist/length)*length;//=NOK((unsigned long long)dist[v],(unsigned long long)length)+0.5;

      if (length_to_use_edge < dist[next_vertex]) {
        //queue.erase(std::make_pair(dist[next_vertex], next_vertex));
        queue.insert(std::make_pair(length_to_use_edge, next_vertex));
        dist[next_vertex] = length_to_use_edge;
        parents[next_vertex] = v;
        ans_edges[next_vertex]=edge;
      }
    }
  }

  std::cout.precision(std::numeric_limits<double>::max_digits10);
    std::cout << dist[n - 1] << "\n";

    std::vector<int> path;
 *//*   for (int v = n - 1; v != 0; v = parents[v]) {
      path.push_back(ans_edges[v]);
    }*//*
 int current_vert = n - 1;
 while (current_vert != 0) {
   path.push_back(ans_edges[current_vert]);
   current_vert = parents[current_vert];
 }
    //path.push_back (0);
    std::reverse(path.begin(), path.end());
 for(int i=0;i<path.size()-1;i++){
   std::cout<<path[i]<<" ";
 }
 std::cout<<path[path.size()-1];

  return 0;
}*/















#include <iostream>
#include <vector>
#include <queue>


//Prim’s Algorithm
std::vector<std::vector<std::pair<int, int>>> FindMST(const std::vector<std::vector<std::pair<int,int>>>& graph) {

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

    for (int i=0;i<graph[not_marked_vertex].size();i++) {
      if (!marked[graph[not_marked_vertex][i].first]) {
        queue.push(std::make_pair(graph[not_marked_vertex][i].second,
                                  std::make_pair(not_marked_vertex, graph[not_marked_vertex][i].first)));
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

    for (int i=0;i<MST[current_vertex].size();i++) {
      int to = MST[current_vertex][i].first;
      int weight = MST[current_vertex][i].second;

      if (!visited[to]) {
        queue.push(std::make_pair(to, std::min(current_edge, weight)));
        result[to] = std::min(current_edge, weight);
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






