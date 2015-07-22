
/************************************************************

AC自动机模板，使用静态数组构树

************************************************************/
const int SIGMA_SIZE = 27;//自定义，输入字符的集合大小
const int MAX_LEN = 52;//模式串的最大长度

struct ACMachine {
    int ch[MAXN * MAX_LEN][SIGMA_SIZE];//树边
    int val[MAXN * MAX_LEN];//标记此节点是不是结点
    int fail[MAXN * MAX_LEN];//失配函数
    int last[MAXN * MAX_LEN];//后缀链接

    int node_cnt;
    queue<int>q;

    //这里可以添加自定义变量

    void init() {
        node_cnt = 0;
        mem0(ch); mem0(val);
        mem0(fail); mem0(last);
        while(!q.empty()) q.pop();
    }
    int get_idx(char ch) {
        //需要自定义此函数，需要将ch转化为[0, SIGMA_SIZE)的值
    }
    void insert_to_tree(char *str) {
        int u = 0, len = strlen(str);
        rep (i, 0, len - 1) {
            int c = get_idx(str[i]);
            if(!ch[u][c]) {
                ch[u][c] = ++node_cnt;
            }
            u = ch[u][c];
        }
        val[u] ++;
    }
    void get_fail() {//计算失配函数
        rep (c, 0, SIGMA_SIZE - 1) {
            int u = ch[0][c];
            if(u) q.push(u);
        }
        while(!q.empty()) {
            int r = q.front(); q.pop();
            rep (c, 0, SIGMA_SIZE - 1) {
                int u = ch[r][c];
                if(!u) {
                    ch[r][c] = ch[fail[r]][c];
                    continue;
                }
                q.push(u);
                int v = fail[r];
                while(v && !ch[v][c]) v = fail[v];
                fail[u] = ch[v][c];
                last[u] = val[fail[u]] ? fail[u] : last[fail[u]];
            }
        }
    }
    void find_ans(char *str) {
        int len = strlen(str), u = 0;
        rep(i, 0, len - 1) {
            int c = get_idx(str[i]);
            u = ch[u][c];//失配回溯的点
            int v = u;
            while(v) {
                if(val[v]) ;//在这里找到了单词结点，添加自定义操作
                v = last[v];
            }
        }

    }
}acm;
