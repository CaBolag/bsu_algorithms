/*
#include <iostream>
#include <vector>

std::vector<std::vector<int>> GetMatrixPower(std::vector<std::vector<int>> matrix, int power){
  if(power==1){
    return matrix;
  }

}


std::vector<std::vector<int>> Multiply(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2)
{
  if (matrix1[0].size()!=matrix2.size())
  {
    throw std::invalid_argument("Invalid matrix size");
  }
  std::vector<std::vector<int>> result_matrix = std::vector<std::vector<int>>(matrix1.size(), std::vector<int>(matrix2[0].size(),0));

  for (int i = 0; i < result_matrix.size(); i++)
  {
    for (int j = 0; j < result_matrix[0].size(); j++)
    {
      for (int k = 0; k < result_matrix[0].size(); k++)
      {
        int result_element= matrix1[i][k] * matrix2[k][j];
        result_matrix[i][j]=result_element;
      }
    }
  }
  return result_matrix;
}






*/




#include <iostream>
#include <vector>

void dfs (int v,std::vector<bool>& visited,const std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& components) {
  visited[v] = true;
  components[components.size()-1].push_back(v);
  for (size_t i=0; i<graph[v].size(); ++i) {
    int to = graph[v][i];
    if (! visited[to])
      dfs (to,visited,graph,components);
  }
}

void find_comps(std::vector<bool>& visited,const std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& components) {
  for (int i=0; i<graph.size(); ++i)
    visited[i] = false;
  for (int i=0; i<graph.size(); ++i)
    if (! visited[i]) {
      components.push_back(std::vector<int>(0));
      dfs(i,visited,graph,components);
    }
}


inline char invert(int c) {
  return c == 1 ? 2 : 1;
}

/*void dfs(int v, char color,std::vector<char> colors,const std::vector<std::vector<int>>& graph) {   //c - цвет текущей вершины
  colors[v] = color;

  for (int u: graph[v]) {
    if (colors[u] == 0) {    //непосещённая вершина
      dfs(u, invert(color),colors,graph);
    } else if (colors[u] == color) {
      std::cout << "Graph is not bipartite." << endl;
      exit(0);
    }
  }
}*/

/*
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);


  int vertex_amount,edge_amount;
  std::cin>>vertex_amount>>edge_amount;
  std::vector<std::vector<int>> graph(vertex_amount,std::vector<int>(0));
  std::vector<bool> visited(vertex_amount);
  std::vector<std::vector<int>> components;

  int vertex1,vertex2;
  int default_value=-1;
  for(int i=0;i<edge_amount;i++){
    std::cin>>vertex1>>vertex2;
    graph[vertex1].push_back(vertex2);
    graph[vertex2].push_back(vertex1);
    components.clear();
    find_comps(visited,graph,components);

*/
/*
    for(int i=0;i<components.size();i++){
      std::vector<std::vector<int>> sub_graph;
      for(int i=0;i<sub_graph.size();i++){
        for(int j=0;j<//j++)
        sub_graph.push_back(components[i])
      }
      std::vector<char> colors;     //Цвет будем представлять типом char
//0 - вершина ещё не покрашена; 1, 2 - различные цвета.

    }*//*

    std::cout<<components.size();
    for(int i=0;i<3;i++){
      std::cout<<" "<<default_value;
    }
    std::cout<<"\n";
  }

  return 0;
}
*/

/*#include <iostream>

int main() {
  int n;
  double a, b, c, d;
  std::cin >> n >> a >> b >> c >> d;
  double** dp=new double*[n];
  for (int i = 0; i < n; i++) {
    dp[i] = new double[n + 2];
  }
  dp[0][0] = c - d;
  dp[0][1] = 1 - a - b - c + d;
  dp[0][2] = a + b;

  for (int i = 1; i < n; i++)
  {
    for (int j = 0; j < i + 3; j++)
    {
      if (j == 0)
      {
        dp[i][j] = dp[i - 1][j] + dp[i - 1][j + 1] * (c - d);
      }
      else if (j == 1)
      {
        dp[i][j] = dp[i - 1][j] * (1 - a - b - c + d) + dp[i - 1][j + 1] * (c - d / 2);
      }
      else if (j == i + 1)
      {
        dp[i][j] = dp[i - 1][j] * (1 - (a + b / j) - (c - d / j)) + dp[i - 1][j - 1] * (a + b / i);
      }
      else if (j == i + 2)
      {
        dp[i][j] = dp[i - 1][j - 1] * (a + b / (j-1));
      }
      else {
        dp[i][j] = dp[i - 1][j - 1] * (a + b / (j - 1)) + dp[i - 1][j] * (1 - (a + b / j) - (c - d / j)) + dp[i - 1][j + 1] * (c - d / (j + 1));
      }
    }
  }

  for (int i = 0; i < n; i++)
  {
    std::cout << dp[i][0] << "\n";
  }
  return 0;
}*/


#include <iostream>

#include <vector>


void MultiplyMatrices(std::vector<std::vector<long long>>& matrix, std::vector<std::vector<long long>>& new_matrix, long long m)
{
  int size = matrix.size();
  std::vector<std::vector<long long>> result(size,std::vector<long long>(size));

  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      result[i][j] = 0;
      for (int k = 0; k < size; k++){
        long long product = ((matrix[i][k] % m) * (new_matrix[k][j] % m)) % m;
        result[i][j] = (result[i][j] % m + (product % m)) % m;
      }
    }
  }

  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      matrix[i][j] = result[i][j];
    }
  }
}

std::vector<std::vector<long long>> GetMatrixPower(std::vector<std::vector<long long>> &matrix, long long power, long long m){
  int n = matrix.size();
  std::vector<std::vector<long long>> result(n,std::vector<long long>(n));

  for (int i = 0; i < n; ++i){
    result[i][i] = 1;
  }

  while (power > 0){
    if (power & 1){
      MultiplyMatrices(result, matrix, m);
    }

    MultiplyMatrices(matrix, matrix, m);
   power >>= 1;
  }
  return result;
}


int main()
{
  int n;
  long long m,power;
  std::cin >> n >> m >>power;

  std::vector<std::vector<long long>> matrix(n,std::vector<long long>(n));
  long long value;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      std::cin >> value;
      matrix[i][j] = value;
    }
  }

  std::vector<std::vector<long long>> result = GetMatrixPower(matrix,power, m);
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      std::cout << matrix[i][j] << " ";
    }
    std::cout << "\n";
  }
  return 0;
}

