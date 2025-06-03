#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<int> jobs(n);
  for (int i = 0; i < n; i++)
  {
    cin >> jobs[i];
  }

  int N = 1 << n; // 掩码范围 [0, 2^n)
  vector<int> sum(N, 0);
  for (int mask = 0; mask < N; mask++)
  {
    int total = 0;
    // 枚举 mask 中哪些位为 1
    for (int i = 0; i < n; i++)
    {
      if ((mask >> i) & 1)
      {
        total += jobs[i];
      }
    }
    sum[mask] = total;
  }

  const int INF = sum[N - 1] + 1;
  vector<vector<int>> f(k, vector<int>(N, INF));

  for (int mask = 0; mask < N; mask++)
  {
    f[0][mask] = sum[mask];
  }

  for (int i = 1; i < k; i++)
  {
    for (int mask = 0; mask < N; mask++)
    {

      int sub = mask;
      while (true)
      {
        int other = mask ^ sub;
        int cost_i = sum[sub];           // 第 i 号工人完成 sub 子集的耗时
        int cost_prev = f[i - 1][other]; // 前 i-1 号工人完成其余的最优峰值
        int candidate = max(cost_i, cost_prev);
        if (candidate < f[i][mask])
        {
          f[i][mask] = candidate;
        }

        if (sub == 0)
        {
          break;
        }
        sub = (sub - 1) & mask; // 枚举下一个子集
      }
    }
  }

  cout << f[k - 1][N - 1] << "\n";
  return 0;
}
