#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int n, k;             // n = 任务数，k = 工人数
vector<int> jobs;     // 各任务的耗时
vector<int> workload; // workload[i] 表示第 i 号工人的当前总工作时长
int bestAnswer;       // 全局最优解

void dfs(int idx, int currentMax)
{
  // 如果当前已经分配完所有任务，则更新全局最优
  if (idx == n)
  {
    bestAnswer = min(bestAnswer, currentMax);
    return;
  }

  int t = jobs[idx];

  // 用来标记：在遍历过程中是否已经遇到过“某个工人 workload[j] == 0”
  // 如果遇到，就只给第一个空闲工人分配，后面的空闲工人都跳过。
  bool assignedToEmpty = false;

  // 尝试将当前任务分配给每个工人
  for (int j = 0; j < k; ++j)
  {
    if (workload[j] == 0)
    {
      workload[j] += t;
      int newMax = max(currentMax, workload[j]);

      // 剪枝：只有当 newMax < bestAnswer 时，才继续深搜
      if (newMax < bestAnswer)
      {
        dfs(idx + 1, newMax);
      }

      // 回溯
      workload[j] -= t;

      // 已经把这个任务分给了一个空闲工人，后续其他空闲工人可跳过
      assignedToEmpty = true;
      break;
    }

    // 如果不是空闲工人，按正常逻辑尝试
    workload[j] += t;
    int newMax = max(currentMax, workload[j]);

    // 剪枝：如果分配后 newMax >= bestAnswer，则不再继续此分支
    if (newMax < bestAnswer)
    {
      dfs(idx + 1, newMax);
    }

    // 回溯
    workload[j] -= t;
  }

  // 如果当前存在空闲工人已被处理，那么就不需要再把任务分给
  // “其他同样空闲”的工人，直接返回即可。
  if (assignedToEmpty)
  {
    return;
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;
  jobs.resize(n);
  for (int i = 0; i < n; ++i)
  {
    cin >> jobs[i];
  }

  sort(jobs.begin(), jobs.end(), greater<int>());

  workload.assign(k, 0);
  bestAnswer = accumulate(jobs.begin(), jobs.end(), 0) + 1;

  dfs(0, 0);
  cout << bestAnswer << "\n";
  return 0;
}
