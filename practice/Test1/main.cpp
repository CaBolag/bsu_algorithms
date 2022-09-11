/*#include <iostream>
using namespace std;

int main() {
  const int pow_N = 7;
  const int N = 39;
  int dp[pow_N][N];

  // для всех `n` используя только 2^0, всего один способ суммы
  for (int j = 0; j < N; ++j)
    dp[0][j] = 1;

  // динамика
  for (int i = 1; i < pow_N; ++i){
    for (int j = 0; j < N; ++j){
      int p = 1 << i;
      if (j < p){
        dp[i][j] = dp[i-1][j];
        continue;
      }
      dp[i][j] = 0;
      if (i > 0)
        dp[i][j] += dp[i-1][j];
      if (j-p >= 0)
        dp[i][j] += dp[i][j-p];
    }
  }
for(int i=0;i<pow_N;i++){
  for(int j=0;j<N;j++){
    cout<<dp[i][j]<<" ";
  }
  cout<<endl;
}

  int n;
  cin >> n;
  cout << dp[6][n];
  return 0;
}*/

/*
#include <iostream>
const long long MOD = 1000000007;


long long CountPaths(int n, int k) {
  long long* dp = new long long[n];
  dp[0] = 1;
  dp[1] = 1;
  for (int i = 2; i <= k; i++) {
    dp[i] = ((2 * dp[i - 1]) % MOD+MOD)%MOD;
  }
  for (int i = k + 1; i < n; i++) {
    dp[i] = ((2 * dp[i - 1] % MOD - dp[i - k - 1] % MOD)+MOD) % MOD;
  }
  return dp[n-1] %MOD;
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int requests_amount;
  int n,k;
  std::cin >> requests_amount;
  for (int i = 0; i < requests_amount; i++) {
    std::cin>> n;
    std::cin >> k;
    std::cout << CountPaths(n, k) << "\n";
  }
}*/



/*#include <iostream>
#include <vector>
long long penalties[202][1002];
long long  dp[202][1002];

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nulong longptr);

  int rows_amount;
  int columns_amount;
  std::cin>>rows_amount>>columns_amount;

  //std::vector<std::vector<long long>> penalties(202,std::vector<long long>(1002));
  int penalty;
  for(int i=0;i<rows_amount;i++){
    for(int j=0;j<columns_amount;j++){
      std::cin>>penalty;
      penalties[i][j]=penalty;
    }
  }

  //std::vector<std::vector<long long>> dp(202,std::vector<long long>(2002));
  for (int i = 0; i <= rows_amount; i++) {
    for (int j = 0; j <= columns_amount; j++) {
      dp[i][j] = INT32_MAX;
    }
  }
  dp[0][0] = penalties[0][0];
  for(int i=0;i<=rows_amount;i++) {
    for (int j = 0; j <= columns_amount; j++) {
      if(dp[i][j] + penalties[i + 1][j]<dp[i + 1][j]){
        dp[i + 1][j]=dp[i][j] + penalties[i + 1][j];
      }

      if(dp[i][j] + penalties[i + 1][j - 1]<dp[i + 1][j - 1]){
        dp[i + 1][j - 1]=dp[i][j] + penalties[i + 1][j - 1];
      }

      if(dp[i][j] + penalties[i + 1][j + 1]<dp[i + 1][j + 1]){
        dp[i + 1][j + 1]=dp[i][j] + penalties[i + 1][j + 1];
      }
    }
  }

  if (dp[rows_amount-1][columns_amount-1] >= INT32_MAX) {
    std::cout <<-1;
  } else {
    std::cout<<dp[rows_amount-1][columns_amount-1];

  }
  return 0;
}*/




/*

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
typedef long long  long long;
const int MAX = INT32_MAX;
long long a[202][1002];
long long dp[202][1002];
*/
/*
Задана матрица A натуральных чисел размера n × m.
За каждый проход через элемент (i, j) взимается штраф ai, j.
Необходимо минимизировать штраф и пройти из элемента (1, 1) в (n, m),
при этом из текущего элемента можно перейти в любой из трёх соседних, стоящих в строке с номером, на 1 большим.
*//*

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nulong longptr);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n, m;
  cin >> n >> m;
  */
/*long long** a = new long long* [n+1];
  for (int i = 0; i < n+1; i++) {
   a[i] = new long long[m + 1]{};
  }
  long long** dp = new long long* [n+1];
  for (int i = 0; i < n+2; i++) {
   dp[i] = new long long[m + 2]{};
  }*//*

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      dp[i][j] = MAX;
    }
  }
  dp[1][1] = a[1][1];
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      dp[i + 1][j - 1] = min(dp[i + 1][j - 1], dp[i][j] + a[i + 1][j - 1]);
      dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + a[i + 1][j]);
      dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + a[i + 1][j + 1]);
    }
  }
  if (dp[n][m] >= MAX) {
    cout << -1 << endl;
  }
  else {
    cout << dp[n][m] << endl;
  }
}*/



#include <iostream>
#include <string>


int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n, k,d;
  std::cin >> n >> k >> d;
  std::string value;
  std::cin >> value;
  std::string extended_value(n-k,'0');
/*  for (int i =0; i < n-k; i++) {
    extended_value.push_back(0);
  }*/
  for (int i = 0;i<value.size() ; i++) {
    extended_value.push_back(value[i]);
  }

  int ones_amount;
  int zeroes_amount;
  if (extended_value[n - 1] == '1')
  {
    ones_amount = 1;
    zeroes_amount = 1;
  } else {
    ones_amount = 0;
    zeroes_amount = 1;
  }
  for (int i = n - 2; i >= 0; i--)
  {
    if (extended_value[i] == '1')
    {
      ones_amount = (ones_amount+ zeroes_amount)%d;

    }
    else {
      zeroes_amount = (ones_amount + zeroes_amount) % d;
    }
  }
  std::cout << zeroes_amount % d << "\n";
  return 0;
}





