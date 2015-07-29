#include <cstdio>
typedef long long LL;
int N, K,deq[1005], hd, ed;
LL pos[1005], val[1005]; 
LL dp[1005][1005];
LL sumVal[1005],sumPV[1005];
LL gSumVal(int i, int j) {
	if (j < i) return 0;
	return sumVal[j + 1] - sumVal[i];
}
LL gSumPV(int i, int j) {
	if (j < i) return 0;
	return sumPV[j + 1] - sumPV[i]; 
}
LL calc(int j, int i, int k) {
	return dp[j][k] + pos[i] * gSumVal(j + 1, i - 1) - gSumPV(j + 1, i - 1);
}
double slope(int i, int j, int k) {
	return ((double)(dp[i][k] - dp[j][k]) + (double)gSumPV(j + 1, i)) / (double)(gSumVal(j + 1, i));
}
int main() {
	while (~scanf("%d%d", &N, &K)) {
		for (int i = 0; i < N; ++i) {
			scanf("%lld%lld", &pos[i], &val[i]);
			if (i) {
				sumVal[i + 1] = sumVal[i] + val[i];
				sumPV[i + 1] = sumPV[i] + val[i] * pos[i];
			} else {
				sumVal[i + 1] = val[i];
				sumPV[i + 1] = val[i] * pos[i]; 
			}
		}
		dp[0][1] = 0;
		for (int i = 1; i < N; ++i) 
			dp[i][1] = dp[i - 1][1] + gSumVal(0, i - 1) * (pos[i] - pos[i - 1]); 
		for (int k = 2; k <= K; ++k) {
			dp[k - 1][k] = 0;
			hd = ed = 0;
			deq[ed++] = k - 2;
			deq[ed++] = k - 1;
			for (int i = k; i < N; ++i) {
				while (hd + 1 < ed && calc(deq[hd], i, k - 1) > calc(deq[hd + 1], i, k - 1))
					++hd;
				dp[i][k] = calc(deq[hd], i, k - 1);
                while (hd + 1 < ed && slope(i, deq[ed - 2], k - 1) > slope(i, deq[ed - 1], k - 1))
                    --ed;
				deq[ed++] = i;
			}
		}
		printf("%lld\n", dp[N - 1][K]);
	}
}
