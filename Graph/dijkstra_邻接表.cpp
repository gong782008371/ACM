struct cmp//�������ȶ��е����ȼ��Ƚ�
{
    bool operator() (Pair a, Pair b)
    {
        return a.first < b.first;
    }
};

bool done[MAXN];
typedef pair<int, int> Pair;//��������dֵ����Ŷ������
void dijkstra(int s)
{
    mem(done);
    for(int i=0;i<=N;i++) d[i] = INF;//��ʼʱ��suoyoudֵ����Ϊ+��
    priority_queue<Pair, vector<Pair>, cmp>q;//����һ�����ȶ���
    q.push(make_pair(d[s]=0, s));//������������У���ֻ������dֵΪ0
    while(!q.empty())//���δ����ȶ�����ȡ�����ȼ�����Ԫ�أ�Ҳ����dֵ��С�ĵ㣩ֱ��Ϊ��
    {
        Pair top = q.top();  q.pop();
        int x = top.second;
        if(done[x]) continue;//����˶����Ѿ�����ˣ���������
        done[x] = true;
        for(int e = first[x]; e != -1; e = next[e])//ö�ٴ˸���������б�
        {
            if(d[v[e]] > d[x] + w[e])
            {
                d[v[e]] = d[x] + w[e];
                q.push(make_pair(d[v[e]], v[e]));//���µ�dֵ��С�ĵ�Ž����ȶ���
            }
        }
    }
}
