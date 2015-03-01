
/***********************************************************
*                                                          *
*   Edmonds_Karp�㷨������������ڽӾ����ߣ�             *
*                                                          *
***********************************************************/

int src, des;
int cap[MAXN][MAXN], flow[MAXN][MAXN], pre[MAXN], a[MAXN];

int Edmonds_Karp(int n)
{
    queue<int>q;
    mem0(flow);//������ʱ��ʵ������
    int max_flow = 0;//�����
    while(true)
    {
        mem0(a);//ÿ�����������ʼ��Ϊ0
        a[src] = INF;//���Ĳ���ΪINF
        q.push(src);
        while(!q.empty())//BFSѰ������·������¼·��
        {
            int u = q.front(); q.pop();
            for(int v = 1; v <= n; v ++) if(!a[v] && cap[u][v]>flow[u][v])
            {
                pre[v]= u;//��¼·��
                q.push(v);
                a[v] = MIN(a[u], cap[u][v] - flow[u][v]);//����·���ϵ���С����
            }
        }
        if(a[des] == 0) break;    //�Ҳ�����������ʱ�Ѿ��������
        for(int u = des; u != src; u = pre[u])
        {
            flow[pre[u]][u] += a[des];  //���������뷴������
            flow[u][pre[u]] -= a[des];
        }
        max_flow += a[des];//���´�src������������
    }
    return max_flow;
}
