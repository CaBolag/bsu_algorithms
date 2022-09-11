#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <initializer_list>

long long ModularExponentiation(long long x, long long y, long long n)
{
  if (y == 0) {
    return 1;
  }
  if (y % 2 == 0) {
    long long z = ModularExponentiation(x, y / 2, n);
    return (z * z) % n;
  }
  else {
    return (x * ModularExponentiation(x, y - 1, n)) % n;
  }
}

void FindMaxPathWhileJumping() {
/*  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);*/
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int cells_amount;
  std::cin >> cells_amount;
  int cell_value;
  std::vector<int> values;
  for (int i = 0; i < cells_amount; i++) {
    std::cin >> cell_value;
    values.push_back(cell_value);
  }
  if (cells_amount == 1) {
    std::cout << cell_value << "\n";
    std::cout << 1;
    return;
  }
  std::vector<int> max_sum_by_cells(cells_amount, 0);
  max_sum_by_cells[0] = values[0];
  std::vector<int> idx(cells_amount, 0);
  max_sum_by_cells[1] = -1;
  max_sum_by_cells[2] = max_sum_by_cells[0] + values[2];
  for (int i = 3; i < cells_amount; i++) {
    max_sum_by_cells[i] = std::max(max_sum_by_cells[i - 2], max_sum_by_cells[i - 3]) + values[i];
    if (max_sum_by_cells[i - 2] >= max_sum_by_cells[i - 3]) {
      idx[i] = i - 1;
    } else {
      idx[i] = i - 2;
    }
  }

  std::cout << max_sum_by_cells[cells_amount - 1] << "\n";
  if (max_sum_by_cells[cells_amount - 1] != -1) {
    std::vector<int> result_path;
    result_path.push_back(cells_amount);

    for (int i = cells_amount - 1; i > 0; i = idx[i] - 1) {
      if (idx[i] == 0) {
        result_path.push_back(1);
        break;
      }
      result_path.push_back(idx[i]);
    }
    for (int i = result_path.size(); i > 0; i--) {
      std::cout << result_path[i-1]<<" ";
    }
  }


/*  int max_max_sum_by_cells_by_cells[3];
  max_max_sum_by_cells_by_cells[2]=cell_value;
  std::vector<std::vector<int>> max_max_sum_by_cells_path_of_nearest_cells={{1,3},{-1},{1}};
  std::cin>>cell_value;
  max_max_sum_by_cells_by_cells[1]=-1;
  std::cin>>cell_value;
  max_max_sum_by_cells_by_cells[0]=max_max_sum_by_cells_by_cells[2]+cell_value;
  int prev_cell_to_max_max_sum_by_cells;

  for(int i=3;i<cells_amount;i++) {
    std::cin >> cell_value;

    prev_cell_to_max_max_sum_by_cells = max_max_sum_by_cells_by_cells[1] > max_max_sum_by_cells_by_cells[2] ? 2 : 3;
    int temp_int = max_max_sum_by_cells_by_cells[0];
    max_max_sum_by_cells_by_cells[0] = max_max_sum_by_cells_by_cells[prev_cell_to_max_max_sum_by_cells - 1] + cell_value;
    max_max_sum_by_cells_by_cells[2] = max_max_sum_by_cells_by_cells[1];
    max_max_sum_by_cells_by_cells[1] = temp_int;

    std::vector<int> temp = max_max_sum_by_cells_path_of_nearest_cells[0];
    max_max_sum_by_cells_path_of_nearest_cells[0] = max_max_sum_by_cells_path_of_nearest_cells[prev_cell_to_max_max_sum_by_cells - 1];
    max_max_sum_by_cells_path_of_nearest_cells[0].push_back(i + 1);
    max_max_sum_by_cells_path_of_nearest_cells[2] = max_max_sum_by_cells_path_of_nearest_cells[1];
    max_max_sum_by_cells_path_of_nearest_cells[1] = temp;
  }

  int max_max_sum_by_cells=max_max_sum_by_cells_by_cells[0];

  if(cells_amount==2) {
    std::cout << -1;
    return;
  }
  std::vector<int> path=max_max_sum_by_cells_path_of_nearest_cells[0];
  std::cout<<max_max_sum_by_cells<<"\n";
  int path_size=path.size();
  for(int i=0;i<path_size-1;i++) {
    std::cout << path[i] << " ";
  }
  std::cout<<path[path_size-1];
  return;*/
}

long long FindNumberOfCombinationsModularArithmetic(int n,int k){
  long long numerator=1;
  long long denominator=1;
  const long long CONSTANT = (pow(10, 9) + 7);
;
  for(int i=2;i<=k;i++){
    denominator=(denominator*i)%CONSTANT;
  }

  for(int i=n-k+1;i<=n;i++){
    numerator=(numerator*i)%CONSTANT;
  }
  long long number_of_combinations_modular;
  number_of_combinations_modular=(numerator*ModularExponentiation(denominator,CONSTANT-2,CONSTANT))%CONSTANT;
  return number_of_combinations_modular;
}

long long FindNumberOfCombinationsDynamically(int n,int k) {
  //store full table

/*  std::vector<std::vector<long long>> values{{1}};
  const long long CONSTANT = (pow(10, 9) + 7);
  int j = 1;
  if (k > n / 2) {
    k = n - k;
  }
  for (int i = 1; i <= n; i++) {
    values.push_back({1});
    for (int k = 1; k < j; k++) {
      values[i].push_back((values[i - 1][k - 1] % CONSTANT + values[i - 1][k] % CONSTANT) % CONSTANT);
    }
    values[i].insert(values[i].begin() + j, 1);
    j++;
  }

  return values[n][k];*/

//store only needed rows and make only needed operations

  const long long CONSTANT = (pow(10, 9) + 7);
  if (k > n / 2) {
    k = n - k;
  }
  std::vector<long long> previous;
  std::vector<long long> current{1};
  int l = 1;
  int start=1;
  int step=0;
  for (int i = 0; i < n; i++) {
    previous = current;
    for (int j = start; j < l && j <= k; j++) {
      current[j] = (previous[j] % CONSTANT + previous[j - 1] % CONSTANT) % CONSTANT;
    }
    if (l <= k) {
      current.push_back(1);
    }
    l++;
    step++;
    if(step>=n-k+1) {
      start++;
    }
  }
  return current[k];
}

long long FindMinMatrixMultiplicationOperationsAmount(int matrix_dimensions[],int matrix_amount) {
  matrix_amount++;
  std::vector<std::vector<long long>> operations_amount_table(matrix_amount,
                                                              std::vector<long long>(matrix_amount, 0));
  int operations_amount;
  for (int l = 2; l < matrix_amount; l++) {
    for (int i = 1; i < matrix_amount - l + 1; i++) {
      int j = i + l - 1;
      operations_amount_table[i][j] = INT64_MAX;
      for (int k = i; k < j; k++) {
        operations_amount = operations_amount_table[i][k]
            + operations_amount_table[k + 1][j]
            + matrix_dimensions[i - 1]
                * matrix_dimensions[k]
                * matrix_dimensions[j];
        if (operations_amount < operations_amount_table[i][j]) {
          operations_amount_table[i][j] = operations_amount;
        }
      }
    }
  }

  return operations_amount_table[1][matrix_amount - 1];
}

std::string FindLongestPalindromicSubstring(std::string str){
  int n=str.length();
  std::vector<std::vector<long long>> palindromic_substring_length_table(n,std::vector<long long>(n, 0));
  for(int i=0;i<n;i++){
    palindromic_substring_length_table[i][i]=1;
  }
  for(int i=0;i<n-1;i++){
    if(str[i]==str[i+1]){
      palindromic_substring_length_table[i][i+1]=2;
    } else{
      palindromic_substring_length_table[i][i+1]=1;
    }
  }

  int cell_to_start_move_up=0;
  for(int j=2;j<n;j++){
    for(int i=cell_to_start_move_up;i>=0;i--){
      if(str[i]==str[j]){
        palindromic_substring_length_table[i][j]=palindromic_substring_length_table[i+1][j-1]+2;
      }else{
        palindromic_substring_length_table[i][j]=std::max
            (palindromic_substring_length_table[i+1][j],
             palindromic_substring_length_table[i][j-1]);
      }
    }
    cell_to_start_move_up++;
  }

  int palindromic_substring_length=palindromic_substring_length_table[0][n-1];
  std::string palindromic_substring;
  for(int i=0;i<palindromic_substring_length;i++){
    palindromic_substring.append(" ");
  }
  int current_row=0;
  int current_column=n-1;
  int start_to_insert=0;
  int end_to_insert=palindromic_substring_length-1;
  while(palindromic_substring_length>=palindromic_substring_length/2){
    if(str[current_row]==str[current_column]){
      palindromic_substring[start_to_insert]=str[current_row];
      palindromic_substring[end_to_insert]=str[current_row];
      start_to_insert++;
      end_to_insert--;
      current_row++;
      current_column--;
      palindromic_substring_length-=2;
    } else if(palindromic_substring_length_table[current_row][current_column]==palindromic_substring_length_table[current_row+1][current_column]){
      current_row++;
    }else{
      current_column--;
    }
  }
  return palindromic_substring;
}


long long FindMinStringConversionPenalty(std::string str1,
                                         std::string str2,
                                         long long delete_penalty,
                                         long long insert_penalty,
                                         long long replace_penalty) {
  int rows_amount = str1.length() + 1;
  int columns_amount = str2.length() + 1;
  std::vector<std::vector<long long>> penalty_table(rows_amount, std::vector<long long>(columns_amount, 0));

  for (int i = 0; i < columns_amount; i++) {
    penalty_table[0][i] = i * insert_penalty;
  }
  for (int i = 1; i < rows_amount; i++) {
    penalty_table[i][0] = i * delete_penalty;
  }
  long long min_cost_replace_or_delete_and_insert = std::min(replace_penalty, delete_penalty + insert_penalty);

  for (int i = 1; i < rows_amount; i++) {
    for (int j = 1; j < columns_amount; j++) {
      int is_identical_elements;
      if (str2[j - 1] == str1[i - 1]) {
        is_identical_elements = 0;
      } else {
        is_identical_elements = 1;
      }

      penalty_table[i][j] = (std::min({
                                          penalty_table[i - 1][j] + delete_penalty,
                                          penalty_table[i][j - 1] + insert_penalty,
                                          penalty_table[i - 1][j - 1]
                                              + is_identical_elements * min_cost_replace_or_delete_and_insert}));
    }
  }
  return penalty_table[rows_amount - 1][columns_amount - 1];
}

int FindIndexForValue(std::vector<int>& sequence, int left, int right,int value){
  int middle = 0;
  int index = 0;
  bool is_index_found = 0;

  for (middle = (left + right) / 2; left <= right && is_index_found!=1; middle = (left + right) / 2) {
    if (sequence[middle] > value) {
      right = middle - 1;
    }
    else if (sequence[middle] == value) {
      index = middle;
      is_index_found = 1;
    }
    else if (middle + 1 <= right && sequence[middle + 1] >= value) {
      sequence[middle + 1] = value;
      index = middle + 1;
      is_index_found = 1;
    } else {
      left = middle + 1;
    }
  }

  if (!is_index_found) {
    if (middle == left) {
      sequence[middle] = value;
      index = middle;
    }
    else {
      sequence[middle + 1] = value;
      index = middle + 1;
    }
  }

  return index;
}

int FindLongestIncreasingSequenceLength(std::vector<int>& sequence) {
  int sequence_size = sequence.size();
  std::vector<int> dp(sequence_size + 1, INT_MAX);
  int length = 0;
  dp[0] = INT_MIN;
  for (int i = 0; i < sequence_size; i++) {
    int index = int(std::upper_bound(dp.begin(), dp.end(), sequence[i]) - dp.begin());
    if (dp[index - 1] < sequence[i] && sequence[i] < dp[index]) {
      dp[index] = sequence[i];
      //length=std::max(length,index);
    }
  }
  for (int i = sequence_size; i >= 0; i--) {
    if (dp[i] != INT_MAX) {
      length = i;
      break;
    }
  }
  return length;
}

void FindMaxPolygonExpressionValue() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<long long> values;
  std::vector<char> arithmetic_symbols;
  int elements_amount;
  std::cin >> elements_amount;
  long long value;
  char symbol;
  for (int i = 0; i < elements_amount; i++) {
    std::cin >> symbol;
    std::cin >> value;
    arithmetic_symbols.push_back(symbol);
    values.push_back(value);
  }
  std::rotate(arithmetic_symbols.begin(), arithmetic_symbols.begin() + 1, arithmetic_symbols.end());
  for (int i = 0; i < elements_amount - 1; i++) {
    values.push_back(values[i]);
    arithmetic_symbols.push_back(arithmetic_symbols[i]);
  }

  std::vector<std::vector<long long>> max_table(elements_amount, std::vector<long long>(elements_amount, INT64_MIN));
  std::vector<std::vector<long long>> min_table(elements_amount, std::vector<long long>(elements_amount, INT64_MAX));

  for (int i = 0; i < elements_amount; i++) {
    max_table[i][0] = values[i];
    min_table[i][0] = values[i];

  }

  //i - index of a starting element
  //j - amount of elements after starting elements
  for (int j = 1; j < elements_amount; j++) {
    for (int i = 0; i < elements_amount; i++) {
      //find min and max value of expression starting from the i-th element of length j
      long long current_max = INT64_MIN;
      long long current_min = INT64_MAX;

      //l+1 - length of prefix in the current expression after inserting the parenthesis
      for (int l = 0; l < j; l++) {
        //shifted_i - variable to get correct value from table for elements with index > elements_amount
        int shifted_i = i;
        if (i + l + 1 >= elements_amount) {
          shifted_i -= elements_amount;
        }

        if (arithmetic_symbols[i + l] == 't') {
          current_max = std::max({current_max, max_table[i][l] + max_table[shifted_i + l + 1][j - l - 1]});

          if(min_table[i][l]!=INT64_MAX && min_table[shifted_i + l + 1][j - l - 1]!=INT64_MAX){
            current_min = std::min({current_min,
                                    current_max,
                                    min_table[i][l] + min_table[shifted_i + l + 1][j - l - 1]});
          }else if(min_table[i][l]!=INT64_MAX) {
            current_min = std::min({current_min,
                                    current_max,
                                    min_table[i][l] + max_table[shifted_i + l + 1][j - l - 1]});
          } else if( min_table[shifted_i + l + 1][j - l - 1]!=INT64_MAX){
            current_min = std::min({current_min,
                                    current_max,
                                    min_table[shifted_i + l + 1][j - l - 1] + max_table[i][l]});
          }
          else{
            current_min = std::min({current_min,current_max});
          }

          //'x'
        } else {

          std::vector<long long> all_possible_values;
          if(min_table[i][l]!=INT64_MAX && min_table[shifted_i + l + 1][j - l - 1]!=INT64_MAX){
            all_possible_values.push_back(max_table[i][l] * max_table[shifted_i + l + 1][j - l - 1]);
            all_possible_values.push_back(min_table[i][l] * min_table[shifted_i + l + 1][j - l - 1]);
            all_possible_values.push_back(max_table[i][l] * min_table[shifted_i + l + 1][j - l - 1]);
            all_possible_values.push_back(min_table[i][l] * max_table[shifted_i + l + 1][j - l - 1]);
            std::sort(all_possible_values.begin(),all_possible_values.end());
            current_min=std::min({current_min,all_possible_values[0],all_possible_values[1],current_min,all_possible_values[2],all_possible_values[3]});
            current_max=std::max({current_max,all_possible_values[0],all_possible_values[1],current_min,all_possible_values[2],all_possible_values[3]});
          } else if(min_table[i][l]!=INT64_MAX){
            all_possible_values.push_back(max_table[i][l] * max_table[shifted_i + l + 1][j - l - 1]);
            all_possible_values.push_back(min_table[i][l] * max_table[shifted_i + l + 1][j - l - 1]);
            std::sort(all_possible_values.begin(),all_possible_values.end());
            current_min=std::min({current_min,all_possible_values[0],all_possible_values[1]});
            current_max=std::max({current_max,all_possible_values[0],all_possible_values[1]});
          } else{
            all_possible_values.push_back(max_table[i][l] * max_table[shifted_i + l + 1][j - l - 1]);
            all_possible_values.push_back(max_table[i][l] * min_table[shifted_i + l + 1][j - l - 1]);
            std::sort(all_possible_values.begin(),all_possible_values.end());
            current_min=std::min({current_min,all_possible_values[0],all_possible_values[1]});
            current_max=std::max({current_max,all_possible_values[0],all_possible_values[1]});
          }








/*
            if(min_table[i][l]<0 && min_table[shifted_i + l + 1][j - l - 1]<0) {
              current_max = std::max({current_min,
                                      current_max,
                                      max_table[i][l] * max_table[shifted_i + l + 1][j - l - 1],
                                      min_table[i][l] * min_table[shifted_i + l + 1][j - l - 1],
                                      max_table[i][l] * min_table[shifted_i + l + 1][j - l - 1],
                                      min_table[i][l] * max_table[shifted_i + l + 1][j - l - 1]});
            }else if(min_table[i][l]<0){
              current_max = std::max({current_min,
                                      current_max,
                                      max_table[i][l] * max_table[shifted_i + l + 1][j - l - 1],
                                      min_table[i][l] * max_table[shifted_i + l + 1][j - l - 1]});
            }else if(min_table[shifted_i + l + 1][j - l - 1]<0){
              current_max = std::max({current_min,
                                      current_max,
                                      max_table[i][l] * max_table[shifted_i + l + 1][j - l - 1],
                                      max_table[i][l] * min_table[shifted_i + l + 1][j - l - 1]});
            } else {
              current_max = std::max({current_min,
                                      current_max,
                                      max_table[i][l] * max_table[shifted_i + l + 1][j - l - 1]});
            }

          if(min_table[i][l]!=INT64_MAX && min_table[shifted_i + l + 1][j - l - 1]!=INT64_MAX){
            current_min = std::min({current_min,
                                    current_max,
                                    max_table[i][l] * max_table[shifted_i + l + 1][j - l - 1],
                                    min_table[i][l] * min_table[shifted_i + l + 1][j - l - 1]});
          } else{
            current_min = std::min({current_min,
                                    current_max,
                                    max_table[i][l] * max_table[shifted_i + l + 1][j - l - 1]});
          };*/
        }
      }
      max_table[i][j] = std::max(current_max, max_table[i][j]);
      min_table[i][j] = std::min(current_min, min_table[i][j]);
    }
  }

  std::vector<int> elements_to_delete;
  long long max_expression_value = INT64_MIN;
  for (int i = 0; i < elements_amount; i++) {
    if (max_table[i][elements_amount - 1] > max_expression_value) {
      elements_to_delete = std::vector<int>();
      elements_to_delete.push_back(i+1);
      max_expression_value = max_table[i][elements_amount - 1] ;
    } else if (max_table[i][elements_amount - 1] == max_expression_value) {
      elements_to_delete.push_back(i + 1);
    }
  }

  std::cout<<max_expression_value<<"\n";
  std::sort(elements_to_delete.begin(),elements_to_delete.end());
  int elements_to_delete_size=elements_to_delete.size();
  for(int i=0;i<elements_to_delete_size-1;i++){
    std::cout<<elements_to_delete[i]<<" ";
  }
  std::cout<<elements_to_delete[elements_to_delete_size-1];



/*
  //int values_amount = values.size() + 1;
  std::vector<int> elements_to_delete;
  long long max_expression_value=INT64_MIN;
  for(int m=0;m<arithmetic_symbols.size();m++) {
    std::vector<char> current_symbols=arithmetic_symbols;
    std::vector<long long> current_values=values;
    std::rotate(current_values.begin(),current_values.begin()+m,current_values.end());
    std::rotate(current_symbols.begin(),current_symbols.begin()+m,current_symbols.end());
    current_symbols.erase(current_symbols.begin());

    std::vector<std::vector<long long>> dp(elements_amount);
    for (int i = 0; i < elements_amount; i++) {
      for (int j = 0; j < i; j++) {
        dp[i].push_back(INT64_MAX);
      }
      for (int k = i; k < elements_amount; k++) {
        dp[i].push_back(INT64_MIN);
      }
    }
    for(int i=0;i<elements_amount;i++){
      dp[i][i]=current_values[i];
    }
    long long expression_value;
    for (int j = 1; j <elements_amount ; j++) {
     // for (int i = 0; i < elements_amount - l + 1; i++) {
        for (int i = j-1; i >= 0; i--) {
          for (int k = i; k < j; k++) {

            if (current_symbols[k] == 't') {
              expression_value = dp[i][k] + dp[k + 1][j];
              if (expression_value > dp[i][j]) {
                dp[i][j] = expression_value;
              }
              if (expression_value < dp[j][i]) {
                dp[j][i] = expression_value;
              }

            } else if (current_symbols[k] == 'x') {
              dp[i][j] =std::max({dp[i][j],dp[i][k]*dp[k + 1][j],dp[i][k]*dp[j][k+1],dp[k][i]*dp[k + 1][j],dp[k][i]*dp[j][k+1]});
                  *//*    if( dp[k + 1][j]<0 && dp[k][i]<0) {
                expression_value = std::min(dp[i][k],dp[k][i])*std::min(dp[k + 1][j],dp[j][k+1]);
              } else{
                expression_value = dp[i][k] * dp[k + 1][j];
              }*//*
              dp[j][i]=std::min({dp[j][i],dp[i][k]*dp[k + 1][j],dp[i][k]*dp[j][k+1],dp[k][i]*dp[k + 1][j],dp[k][i]*dp[j][k+1]});
               // dp[j][i] = std::min({dp[j][i],dp[k][i] * dp[k + 1][j], dp[i][k] * dp[k + 1][j]});
            }

          }
        }
      }
   // }
    if(dp[0][elements_amount - 1]>max_expression_value){
      elements_to_delete=std::vector<int>();
      elements_to_delete.push_back(m+1);
      max_expression_value=dp[0][elements_amount - 1];
    } else if(dp[0][elements_amount - 1]==max_expression_value){
      elements_to_delete.push_back(m+1);
    }
  }
  std::cout<<max_expression_value<<"\n";
  std::sort(elements_to_delete.begin(),elements_to_delete.end());
  int elements_to_delete_size=elements_to_delete.size();
  for(int i=0;i<elements_to_delete_size-1;i++){
    std::cout<<elements_to_delete[i]<<" ";
  }
  std::cout<<elements_to_delete[elements_to_delete_size-1];*/

}

std::vector<int> FindPositionsForPokemons(const std::vector<int>& pokemons_height,const std::vector<int>& blocks_height){
  int m=pokemons_height.size();
  int n=blocks_height.size();
  std::vector<std::vector<int>> dp(m+1,std::vector<int>(n+1));
  for(int i=1;i<m+1;i++){
    dp[i][0]=pokemons_height[i-1];
  }
  for(int i=1;i<n+1;i++){
    dp[0][i]=blocks_height[i-1];
  }
/*  for(int i=1;i<m+1;i++){
    dp[i][1]=dp[i][0]+dp[0][1];
  }*/
  int sum;
  for(int i=1;i<m+1;i++){
    for(int j=i;j<n-m+1+i;j++) {
      sum=dp[i][0]+dp[0][j];
      if((sum>dp[i-1][j-1] && dp[i-1][j-1]!=0)|| i==1){
        if(j-1==0 || dp[i][j-1]==0){
          dp[i][j]=sum;
          continue;
        }
        if(sum<dp[i][j-1]){
          dp[i][j]=sum;
        } else{
          dp[i][j]=dp[i][j-1];
        }
        //dp[i][j]=std::min(sum,dp[i][j-1]);
      } else {
        dp[i][j]=dp[i][j-1];
      }
    }
  }
  int j=n;
  std::vector<int> positions;
  for(int i=m;i>0;i--){
    //int j=n-m+i;
    int current_sum=dp[i][j];
    while(current_sum==0 && j!=0){
      j--;
      current_sum=dp[i][j];
    }

    while(dp[i][j]==current_sum && j!=0){
      j--;
    }

    if(dp[i][j+1]!=0){
      positions.push_back(j+1);
    }
  }
  return positions;

}

int main() {


/*  //task 69.2
  FindMaxPathWhileJumping();*/


/*  //task 0.2
  int n,k;
  std::cin>>n>>k;
  long long number_of_combinations=FindNumberOfCombinationsModularArithmetic(n,k);
  std::cout<<number_of_combinations<<"\n";*/


/*
//task 20
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  std::string str;
  std::cin>>str;
  std::string palindromic_substring=FindLongestPalindromicSubstring(str);
  std::cout<<palindromic_substring.length()<<"\n";
  std::cout<<palindromic_substring;
*/


  /*//task 0.1
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int matrix_amount;
  std::cin>>matrix_amount;
  int matrix_dimensions[matrix_amount+1];
  int dimension;
  std::cin>>dimension;
  matrix_dimensions[0]=dimension;
  std::cin>>dimension;
  matrix_dimensions[1]=dimension;
  for(int i=1;i<matrix_amount;i++){
    std::cin>>dimension;
    std::cin>>dimension;
    matrix_dimensions[i+1]=dimension;
  }
  int operations_amount=FindMinMatrixMultiplicationOperationsAmount(matrix_dimensions,matrix_amount);
  std::cout<<operations_amount;
*/

/*  //task 25
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
  long long delete_penalty;
  long long insert_penalty;
  long long replace_penalty;
  std::cin>>delete_penalty>>insert_penalty>>replace_penalty;
  std::string str1;
  std::string str2;
  std::cin>>str1>>str2;

  std::cout<<FindMinStringConversionPenalty(str1,str2,delete_penalty,insert_penalty,replace_penalty);*/


/*//task 6
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int sequence_length;
  std::cin>>sequence_length;
  std::vector<int> sequence;
  int value;
  for(int i=0;i<sequence_length;i++){
    std::cin>>value;
    sequence.push_back(value);
  }
  std::cout<<FindLongestIncreasingSequenceLength(sequence);*/

//Polygon task
FindMaxPolygonExpressionValue();

/*//Pokemons task
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
*//*  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);*//*
int pokemons_amount;
int blocks_amount;

std::cin>>pokemons_amount;
std::cin>>blocks_amount;
std::vector<int> pokemons_height;
std::vector<int> blocks_height;
int pokemon_height;

for(int i=0;i<pokemons_amount;i++){
  std::cin>>pokemon_height;
  pokemons_height.push_back(pokemon_height);
}

int block_height;
for(int i=0;i<blocks_amount;i++){
  std::cin>>block_height;
  blocks_height.push_back(block_height);
}

std::vector<int> positions=FindPositionsForPokemons(pokemons_height,blocks_height);
if(positions.size()<pokemons_amount){
  std::cout<<-1;
  return 0;
}
  for(int i=positions.size()-1;i>0;i--){
    std::cout<<positions[i]<<" ";
  }
  std::cout<<positions[0];*/


  return 0;

}
