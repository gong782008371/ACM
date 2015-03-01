bool Bellman_Ford(int s)//�ж��Ƿ�������·��������ڣ���dֵ�������s�ĵ�Դ���·
{
    for(int i = 1; i <= N; i ++) d[i] = INF;
    d[s] = 0;
    for(int i=1;i<N;i++)//������������ֻ��ҪN-1�ξͿ���ȷ����㵽�������е�����·
    {
        for(int e = 0;e < M; e ++) //ö��ÿ����
        {
            int x = u[e], y = v[e];
            if(d[x] < INF) d[y] = MIN(d[y], d[x] + w[e]);//�ɳ�
        }
    }
    for(int e = 0; e < M; e ++) if(d[u[e]] < INF)//��һ��ö�����б�
    {
        int x = u[e], y = v[e];
        if(d[y] > d[x] + w[e]) return false;//������ж�������ɳڣ����ڸ�Ȩ��·�����������·
    }
    return true;
}
