#define root 1, 1, n
#define lson dep+1, L, mid
#define rson dep + 1, mid+1, R
struct Tree {
    int n;//val记录每一层的实际值，而to_left记录当前区间[l, r]的[l, i]有多少个数是要被放在它的左子树的
    int sorted[MAXN], val[16][MAXN], to_left[16][MAXN];
    void build(int *arr, int n) { //传入一个数组和这个数组的大小，来建树
        this->n = n;
        rep (i, 1, n) {
            val[1][i] = sorted[i] = arr[i];
        }
        sort(sorted + 1, sorted + n + 1); //sorted需要排序
        build(1, 1, n);
    }
    void build(int dep, int L, int R) {
        if(L == R) return ;

        int mid = (L + R) >> 1;
        int middle_val = sorted[mid], same_with_middle = mid - L + 1;//middle_val记录中位数
        for(int i = L; i <= mid; i ++) {//same_with_middle记录有多少个与中位数一样的数是要被放在左子树的
            if(sorted[i] < middle_val) {
                same_with_middle --;
            }
        }
        int left_point = L, right_point = mid + 1;
        for(int i = L; i <= R; i ++) {
            to_left[dep][i] =  L == i ? 0 : to_left[dep][i - 1];
            if(val[dep][i] < middle_val) {//上下这两行用于计算to_left数组
                to_left[dep][i] += 1;
            }

            if(val[dep][i] < middle_val) {//如果比中位数要小，放在左区间
                val[dep + 1][left_point++] = val[dep][i];
            }
            else if(val[dep][i] > middle_val) {//比中位数大，放在右区间
                val[dep + 1][right_point++] = val[dep][i];
            }
            else {//表示与中位数相同
                if(same_with_middle) {//如果左侧还能放入数，就放左边
                    val[dep + 1][left_point++] = val[dep][i];
                    --same_with_middle;//放左边的容量减一
                    ++to_left[dep][i];//更新放左边的数量
                }
                else val[dep + 1][right_point++] = val[dep][i];//否则放右边
            }
        }
        build(lson); build(rson);//递归
    }
    int query(int dep, int L, int R, int l, int r, int k) {//查询区间[l, r]的第k小的数(区间从小到大排序，排在第k的数)
        if(l == r) return val[dep][l]; //找到了
        int mid = (L + R) >> 1;
        int cnt_sm_left  = l == L ? 0 : to_left[dep][l - 1]; //l左侧有多少进入左子树
        int cnt_sm_right = to_left[dep][r];//r左侧有多少进入左子树
        int cnt_to_left = cnt_sm_right - cnt_sm_left; //[l, r]有多少进入左子树
        if(cnt_to_left >= k) {
            return query(lson, L + cnt_sm_left, L + cnt_sm_right - 1, k);//条件判断+递归
        }
        return query(rson, mid + 1 + l - L - cnt_sm_left, mid + 1 + r - L - cnt_sm_right, k - cnt_to_left);
    }
}T;