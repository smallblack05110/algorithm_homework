#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> jobs;
vector<int> workload;
int bestAnswer;

void dfs(int idx)
{
  if (idx == n)
  {
    // 所有任务都已分配，计算当前最大负载
    int currMax = 0;
    for (int j = 0; j < k; ++j)
    {
      currMax = max(currMax, workload[j]);
    }
    bestAnswer = min(bestAnswer, currMax);
    return;
  }
  // 尝试把 jobs[idx] 分配给每位工人
  for (int j = 0; j < k; ++j)
  {
    workload[j] += jobs[idx];
    dfs(idx + 1);
    workload[j] -= jobs[idx];
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // 读取输入格式：
  // 第一行：n k
  // 第二行：jobs 数组（n 个整数）
  cin >> n >> k;
  jobs.resize(n);
  for (int i = 0; i < n; ++i)
  {
    cin >> jobs[i];
  }
  workload.assign(k, 0);
  bestAnswer = INT_MAX;
  dfs(0);
  // 输出最小的“最大工作时间”
  cout << bestAnswer << "\n";
  return 0;
}
