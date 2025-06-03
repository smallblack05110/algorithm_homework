import subprocess
import time

executables = {
    "dfs": "dfs.cpp",
    "dfs_better": "dfs_better.cpp",
    "dp": "dp.cpp"
}

test_cases = [
    # 原有基本测试（保留）
    (4, 2, [3, 2, 3, 4]),
    (6, 3, [2, 2, 3, 7, 4, 1]),
    (5, 2, [5, 5, 5, 5, 5]),
    (8, 4, [1, 1, 1, 1, 1, 1, 1, 20]),
    (10, 5, [1,2,3,4,5,6,7,8,9,10]),

    # 任务数量变多，总和不变，剪枝效果差异大
    (12, 3, [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 20]),

    # 所有人工作时长趋于平均
    (9, 3, [9, 8, 7, 6, 5, 4, 3, 2, 1]),

    # 一个任务特别大，考验贪心排序与分配策略
    (8, 3, [30, 1, 1, 1, 1, 1, 1, 1]),

    # 全为相同任务，考验最均分策略
    (12, 4, [6]*12),  # 总和 = 72，理论最好每人18

    # 大量轻任务 + 少量重任务
    (16, 4, [1]*12 + [8, 9, 10, 11]),

    # 典型“装箱问题”结构，探索最大平衡负载
    (10, 2, [8, 7, 6, 5, 4, 3, 2, 1, 1, 1]),

    # 总任务量特别大，考验 DP 是否能应对
    (14, 4, [9, 8, 6, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1]),

    # 工人少，任务量大（DFS 肯定爆）
    (18, 2, [3]*18),  # 总量=54，最优为27
]


# 编译所有程序
for name, source in executables.items():
    print(f"Compiling {source}...")
    subprocess.run(["g++", "-O2", "-std=c++11", source, "-o", name], check=True)

# 运行测试
for idx, (n, k, jobs) in enumerate(test_cases):
    print(f"\n=== Test Case #{idx + 1}: n = {n}, k = {k}, jobs = {jobs} ===")
    input_data = f"{n} {k}\n{' '.join(map(str, jobs))}\n"

    for name in executables:
        # 调用对应程序
        start_time = time.time()
        result = subprocess.run(
            [f"./{name}"],
            input=input_data.encode(),
            capture_output=True
        )
        elapsed = time.time() - start_time
        output = result.stdout.decode().strip()
        print(f"{name:<12}: Output = {output:<6} | Time = {elapsed:.4f}s")
