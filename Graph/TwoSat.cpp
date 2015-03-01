struct TwoSAT{
    int n;
    vector<int>G[MAXN<<1];
    bool mark[MAXN<<1];
    int S[MAXN], c;

    bool dfs(int x) {
        if(mark[x^1]) return false;
        if(mark[x]) return true;
        mark[c++] = true;
        S[c++] = x;
        for(int i = 0; i < G[x].size(); i ++)
            if(!dfs(G[x][i])) return false;
        return true;
    }

    void init(int n) {
        this->n = n;
        for(int i = 0; i < n * 2; i ++) G[i].clear();
        mem0(mark);
    }

    //x = xval, y = yval
    void add_clause(int x, int xval, int y, int yval) {
        x = x * 2 + xval;
        y = y * 2 + yval;
        G[x^1].push_back(y);
        G[y^1].push_back(x);
    }

    bool solve() {
        for(int i = 0; i < n * 2; i += 2) {
            c = 0;
            if(!dfs(i)) {
                while(c > 0) mark[S[--c]] = false;
                if(!dfs(i + 1)) return false;
            }
        }
        return true;
    }
};
