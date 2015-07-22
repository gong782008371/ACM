
/************************************************************

AC�Զ���ģ�壬ʹ�þ�̬���鹹��

************************************************************/
const int SIGMA_SIZE = 27;//�Զ��壬�����ַ��ļ��ϴ�С
const int MAX_LEN = 52;//ģʽ������󳤶�

struct ACMachine {
    int ch[MAXN * MAX_LEN][SIGMA_SIZE];//����
    int val[MAXN * MAX_LEN];//��Ǵ˽ڵ��ǲ��ǽ��
    int fail[MAXN * MAX_LEN];//ʧ�亯��
    int last[MAXN * MAX_LEN];//��׺����

    int node_cnt;
    queue<int>q;

    //�����������Զ������

    void init() {
        node_cnt = 0;
        mem0(ch); mem0(val);
        mem0(fail); mem0(last);
        while(!q.empty()) q.pop();
    }
    int get_idx(char ch) {
        //��Ҫ�Զ���˺�������Ҫ��chת��Ϊ[0, SIGMA_SIZE)��ֵ
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
    void get_fail() {//����ʧ�亯��
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
            u = ch[u][c];//ʧ����ݵĵ�
            int v = u;
            while(v) {
                if(val[v]) ;//�������ҵ��˵��ʽ�㣬����Զ������
                v = last[v];
            }
        }

    }
}acm;
