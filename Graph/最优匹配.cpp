struct KM {
    const static int INF = 1e9 + 7;
    const static int maxn = 1e3 + 7;
    int A[maxn], B[maxn];
    int visA[maxn], visB[maxn];
    int match[maxn], slack[maxn], Map[maxn][maxn];
    int M, H;

    void add(int u, int v, int w) {
        Map[u][v] = w;
    }
    bool find_path ( int i ) {
        visA[i] = true;
        for ( int j = 0; j < H; j++ ) {
            if ( !visB[j] && A[i] + B[j] == Map[i][j] ) {
                visB[j] = true;
                if (match[j] == -1 || find_path(match[j])) {
                    match[j] = i;
                    return true;
                }
            } else if ( A[i] + B[j] > Map[i][j] ) //j属于B，且不在交错路径中
                slack[j] = min(slack[j], A[i] + B[j] - Map[i][j]);
        }
        return false;
    }

    int solve (int M, int H) {
        this->M = M; this->H = H;
        int i, j, d;
        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));
        memset(match, -1, sizeof(match));
        for ( i = 0; i < M; i++ )
            for ( j = 0; j < H; j++ )
                A[i] = max (Map[i][j], A[i]);
        for ( i = 0; i < M; i++ ) {
            for ( j = 0; j < H; j++ )
                slack[j] = INF;
            while ( 1 ) {
                memset(visA, 0, sizeof(visA));
                memset(visB, 0, sizeof(visB));
                if ( find_path ( i ) ) break; //从i点出发找到交错路径则跳出循环
                for ( d = INF, j = 0; j < H; j++ ) //取最小的slack[j]
                    if (!visB[j] && d > slack[j]) d = slack[j];
                for ( j = 0; j < M; j++ ) //集合A中位于交错路径上的-d
                    if ( visA[j] ) A[j] -= d;
                for ( j = 0; j < H; j++ ) //集合B中位于交错路径上的+d
                    if ( visB[j] ) B[j] += d;
                    else slack[j] -= d; //注意修改不在交错路径上的slack[j]
            }
        }
        int res = 0;
        for ( j = 0; j < H; j++ )
            res += Map[match[j]][j];
        return res;
    }
};//点从0开始编号
