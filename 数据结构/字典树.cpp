int tree[100010][12], s;
bool val[100010];//val[i] = 1表示是某个字符串的尾节点

void insert_to_tree(char* str)
{
    int u = 0;
    for(int i = 0; str[i]; i ++)
    {
        int c = get_val(str[i]);
        if(!tree[u][c])
        {
            tree[u][c] = ++s;
            val[s] = 0;
        }
        u = tree[u][c];
    }
    val[u] = 1;
}
