queue<int>q;
bool inq[MAXN], cnt[MAXN];

//����false��ʾ�и�Ȩ,���������Դ���·
bool SPFA(int s, int t)
{
    for(int i = 0; i < n; i ++) d[i] = (i == s ? 0 : INF);
    memset(inq, 0, sizeof(inq));   //   ���ڶ����С��ı�־
    memset(cnt, 0, sizeof(cnt));   //   ���е���Ӵ���Ϊ0
    q.push(s);
    while(!q.empty())
    {
        int x = q.front(); q.pop();
        inq[x] = false;        //  ������ڶ����С��ı�־
        cnt[x] ++;
        if(cnt[t] > n) return false;
        for(int e = first[x]; e != -1; e = next[e]) if(d[v[e]] > d[x] + w[e])
        {
            d[v[e]] = d[x] +w[e];
            if(!inq[d[e]])   //   ����Ѿ��ڶ����У��Ͳ�Ҫ�ظ������
            {
                inq[v[e]] = true;
                q.push(v[e]);
            }
        }
    }
    return true;
}
