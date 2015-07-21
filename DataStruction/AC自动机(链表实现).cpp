/***************************************************************************

����ʵ��AC�Զ����� SIGMA_SIZE�����ַ���Χ(��Ҫ���ַ�ת��Ϊ[0, SIGMA_SIZE - 1]������)
MAX_LEN����ÿ��ģʽ������󳤶�
(����ע���еġ���㡱���Ǳ�ʾ�ֵ���������һ���ڵ㣬 ����ָ����ĳһ��ģʽ����β�ڵ�)

***************************************************************************/
const int SIGMA_SIZE = 26;
const int MAX_LEN = 52;

struct Node {
    int val;
    Node *ch[SIGMA_SIZE];
    Node *f, *last;//ʧ�亯�����׺����
    Node() {//��׺���ӱ�ʾ���Ǵ�����㰴��ʧ������ͷѰ��ʱ����һ�����
        rep (i, 0, SIGMA_SIZE - 1) {
            ch[i] = NULL;
        }
        f = last = NULL;
        val = 0;//val = 0,��ʾ���ǽ�㣬�����ǽ��
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
    int get_idx(char ch) {//������Ŀ��ͬ�޸�
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
        u->val ++;//���������������β��ģʽ���ĸ���
    }
    void getFail() {//�õ�ʧ�亯��ֵ
        q.push(head);
        while(!q.empty()) {
            Node *r = q.front(); q.pop();
            rep (c, 0, SIGMA_SIZE - 1) {
                Node *u = r->ch[c];
                if(u == NULL) {//���潫ʧ��ĵ�ֱ������ʧ�亯��ֵ�ĵ�
                    if(r != head) r->ch[c] = r->f->ch[c];//���Ա������ʱҪ����ʧ����������
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
    int findAns(char *T) {//�ҵ��ж��ٸ�ģʽ��������ƥ�䴮T��
        int n = strlen(T), ans = 0;
        Node *u = head;
        rep (i, 0, n - 1) {
            int c = get_idx(T[i]);
            u = u->ch[c];
            if(!u) u = head;
            Node *v = u;
            while(v != NULL) {//�Ѿ������ڽ����
                if(v->val >= 0) {
                    ans += v->val;
                    v->val = -1;
                }
                else break;
                v = v->last;//ֱ��������һ����㣬v->last==NULL˵��������ʧ������û�����������
            }
        }
        return ans;
    }
}acm;
