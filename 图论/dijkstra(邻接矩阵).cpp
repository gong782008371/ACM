//**************************************************
//��Դ���·����û�б�ʱdisΪINF
//�������и�Ȩ���ڵ��Ŵ�0��ʼ
//**************************************************

void dijkstra(int s)
{
    for(int i=0;i<=N;i++) d[i] = INF;
    d[s] = 0;
    for(int i=0;i<N;i++)
    {
        int m = INF;
        for(int j = 0;j<N;j++)if(!vis[j] && d[j]<m)m=d[s=j];
        vis[s] = 1;
        for(int j=0;j<N;j++)if(d[j] > d[s]+Map[s][j])d[j]=d[s]+Map[s][j];
    }
}
