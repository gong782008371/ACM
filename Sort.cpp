
/***************************Bubble Sort***************************/

void BubbleSort(int *arr, int n)
{
    for(int i = 0; i < n; i ++ )
    {
        for(int j = n-1; j > i; j -- )
        {
            if(arr[j] < arr[j-1])
                Swap(arr[j], arr[j-1]);
        }
    }
}


/**************************Selection Sort**************************/
void SelectionSort(int *arr, int n)
{
    for(int i = 0; i < n; i ++)
    {
        int k = i;
        for(int j = i + 1 ; j < n ; j ++ )
        {
            if(arr[j] < arr[k]) k = j;
        }
        if( k != i )
            Swap(arr[i], arr[k]);
    }
}


/**************************Insertion Sort**************************/
void InsertionSort(int *arr, int n)
{
    for(int i = 1 ; i < n ; i ++ )
    {
        for(int j = i ; j > 0; j -- )
        {
            if ( arr[j] < arr[j-1] )
                Swap(arr[j], arr[j-1]);
        }
    }
}


/****************************Shell Sort****************************/
int m = 5, d[5] = {1, 2, 3, 5, 7};
void ShellPass(int *arr, int d)
{
    for(int i = d; i < n ; j ++ )
    {
        int k = d, temp = arr[k];
        while(temp < arr[k-d])
        {
            arr[k] = arr[k-d];
            k -= d;
        }
        arr[k] = temp;
    }
}
void ShellSort(int *arr, int n)
{
    for(int i=m-1;i>=0;i--)
        ShellPass(arr, d[i]);
}


/****************************Merge Sort****************************/
void mergeSort(int *arr, int *temp, int low, int high)//[low, high)
{
    if(high - low <= 1) return ;
    int mid = (low + high) >> 1;
    MergeSort(arr, low, m);
    mergeSort(arr, m, high);
    int x = low, y = mid, p = x;
    while(x < mid || y < high)
    {
        if ( y == high || (x < mid && arr[x] <= arr[y]) )
            temp[p++] = arr[x++];
        else
            temp[p++] = arr[y++];
    }
    for(int i = low; i < high; i ++ )
    {
        arr[i] = temp[i];
    }
}


/****************************Quick Sort****************************/
void QuickSort(int *arr, int low, int high)// [low, high]
{
    if(low >= high) return ;
    int x = low, y = high, mid = (x+y)>>1;
    int key = arr[mid];
    Swap(arr[x], arr[mid]);
    while(x != y)
    {
        while(x <= y &&　arr[y] >= key) y --;
        arr[x] = arr[y];
        while(x <= y &&　arr[x] <= key) x ++;
        arr[y] = arr[x];
    }
    arr[x] = key;
    QuickSort(arr, low, x - 1);
    QuickSort(arr, x + 1, high);
}


/****************************Heap Sort*****************************/
void HeapAdjust(int *arr, int i, int nLength)
{
    int nChild;
    for(; i * 2 + 1 < nLength; i = nChild)
    {
        nChild = i * 2 + 1;
        if(nChild < nLength - 1 && arr[nChild] < arr[nChild + 1]) nChild ++;
        if(arr[i] < arr[nChild])
            swap(arr[i], arr[nChild]);
        else break;
    }
}

void HeapSort(int *arr, int length)//[0, length)
{
    for(int i = length / 2 - 1; i >= 0; i --)
        heapAdjust(arr, i, length);
    for(int i = length - 1; i >= 0; i --)
    {
        swap(arr[i], arr[0]);
        heapAdjust(arr, 0, i);
    }
}


/***************************Bucket Sort********************************/
const double EPS = 1e-9;
const int BUCKETSIZE = 20;//桶的个数
const int ARRAYSIZE  =100;//数组的大小
const int MAXELEMENT = 100000;//数组中最大的数不超过此数

int bucket[BUCKETSIZE], next[ARRAYSIZE], arr[ARRAYSIZE], ans[ARRAYSIZE];

void insertIntoBucket(int idx, int s)//将数组arr的第s个元素插入到第idx个桶中
{
    int u = bucket[idx], p = -1;
    while(u != -1 && arr[u] < arr[s]) {
        p = u;
        u = next[u];
    }
    next[s] = u;
    (p == -1 ? bucket[idx] : next[p]) = s;
}

void BucketSort(int n)
{
    memset(bucket, -1, sizeof(bucket));
    for(int i = 0; i < n; i ++) {
        int idx = (int)((double)arr[i] / MAXELEMENT * BUCKETSIZE + EPS);//计算所属桶号
        insertIntoBucket(idx, i);//插入到桶中
    }
    int cnt = 0;
    for(int i = 0; i < BUCKETSIZE; i ++) {
        for(int p = bucket[i]; p != -1; p = next[p])
            ans[cnt++] = arr[p];  //从桶中一次拿出每一个元素
    }
    memcpy(arr, ans, sizeof(ans));//重新保存在arr数组中（可以不要此语句，将答案保存在ans中）
}

