const int INF = 100000;
int N, M, K;
int map[105][105];
int dist[105];
// 1 ~ N: origianl
// 0 : S, N + 1 T
bool BFS() {
	memset(dist, -1, sizeof(dist));
	dist[0] = 0;
	std::queue< int > Q;
	Q.push(0);
	while (!Q.empty()) {
		int now = Q.front();
		Q.pop();
		for (int i = 0;i <= N + 1; ++i)
			if (dist[i] == -1 && map[now][i]) {
				Q.push(i);
				dist[i] = dist[now] + 1;
			}
	}
	return dist[N + 1] != -1;
}
int DFS(int node, int flow) {
	if (node == N + 1) {
		return flow;
	}
	int ret = 0;
	for (int i = 0;i <= N + 1; ++i)
		if(map[node][i] && dist[i] == dist[node] + 1) {
			int bneck = min(flow, map[node][i]);
			int tmp = DFS(i, bneck);
			map[node][i] -= tmp;
			map[i][node] += tmp;
			flow -= tmp;
			ret += tmp;
		}
	return ret;
}
int maxFlow() {
	int totalFlow = 0;
	while (BFS()) {
		totalFlow += DFS(0, INF);
	}
	return totalFlow;
}
