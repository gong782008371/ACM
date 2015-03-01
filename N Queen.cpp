//DFS(0,0,0)
int ans = 0;
void DFS(int Col,int Fir,int Sec)
{
    if(Col == High){ans++;return;}//所有的列都已经被标记了，说明没咧都放了
    int CanPut = ((~(Col | Fir | Sec)) & High);
    while(CanPut)
    {
        int LowBit = CanPut & (-CanPut);//取出最低位
        DFS((Col|LowBit), ((Fir|LowBit)>>1), (((Sec|LowBit) <<1) & High));
        CanPut &= (~LowBit);//去掉最低位
    }
}
