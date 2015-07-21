/***************************************************************************

链表实现AC自动机， SIGMA_SIZE代表字符范围(需要将字符转化为[0, SIGMA_SIZE - 1]的区间)
MAX_LEN代表每个模式串的最大长度
(下面注释中的“结点”不是表示字典树上任意一个节点， 而是指的是某一个模式串的尾节点)

***************************************************************************/
const int SIGMA_SIZE = 26;
const int MAX_LEN = 52;

struct Node {
    int val;
    Node *ch[SIGMA_SIZE];
    Node *f, *last;//失配函数与后缀链接
    Node() {//后缀链接表示的是从这个点按照失配链往头寻找时的上一个结点
        rep (i, 0, SIGMA_SIZE - 1) {
            ch[i] = NULL;
        }
        f = last = NULL;
        val = 0;//val = 0,表示不是结点，否则是结点
    }
};

struct ACMachine {
    int node_cnt;
    Node *head;
    queue<Node*>q;

    void init() {
        node_cnt = 0;
        head = new Node();
    }
    int get_idx(char ch) {//根据题目不同修改
        return ch - 'a';
    }
    void insert_to_tree(char *str) {
        Node *u = head;
        for(int i = 0; str[i]; i ++) {
            int c = get_idx(str[i]);
            if(!u->ch[c]) {
                u->ch[c] = new Node();
            }
            u = u->ch[c];
        }
        u->val ++;//保存的是以这个点结尾的模式串的个数
    }
    void getFail() {//拿到失配函数值
        q.push(head);
        while(!q.empty()) {
            Node *r = q.front(); q.pop();
            rep (c, 0, SIGMA_SIZE - 1) {
                Node *u = r->ch[c];
                if(u == NULL) {//下面将失配的点直接连向失配函数值的点
                    if(r != head) r->ch[c] = r->f->ch[c];//可以避免查找时要按照失配链往回找
                    continue;
                }
                q.push(u);
                if(r == head) { u->f = head; continue; }
                Node *v = r->f;
                while(v && v->ch[c] == NULL) v = v->f;
                u->f = v == NULL ? head : v->ch[c];
                u->last = u->f->val ? u->f : u->f->last;
            }
        }
    }
    int findAns(char *T) {//找到有多少个模式串出现在匹配串T种
        int n = strlen(T), ans = 0;
        Node *u = head;
        rep (i, 0, n - 1) {
            int c = get_idx(T[i]);
            u = u->ch[c];
            if(!u) u = head;
            Node *v = u;
            while(v != NULL) {//已经不存在结点了
                if(v->val >= 0) {
                    ans += v->val;
                    v->val = -1;
                }
                else break;
                v = v->last;//直接跳到上一个结点，v->last==NULL说明这个点的失配链上没有其他结点了
            }
        }
        return ans;
    }
}acm;
