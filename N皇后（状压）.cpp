//DFS(0,0,0)
int ans = 0;
void DFS(int Col,int Fir,int Sec)
{
    if(Col == High){ans++;return;}//���е��ж��Ѿ�������ˣ�˵��û�ֶ�����
    int CanPut = ((~(Col | Fir | Sec)) & High);
    while(CanPut)
    {
        int LowBit = CanPut & (-CanPut);//ȡ�����λ
        DFS((Col|LowBit), ((Fir|LowBit)>>1), (((Sec|LowBit) <<1) & High));
        CanPut &= (~LowBit);//ȥ�����λ
    }
}
