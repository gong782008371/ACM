#define root 1, 1, n
#define lson dep+1, L, mid
#define rson dep + 1, mid+1, R
struct Tree {
    int n;
    int sorted[MAXN], val[16][MAXN], to_left[16][MAXN];
    void build(int *arr, int n) {
        this->n = n;
        rep (i, 1, n) {
            val[1][i] = sorted[i] = arr[i];
        }
        sort(sorted + 1, sorted + n + 1);
        build(1, 1, n);
    }
    void build(int dep, int L, int R) {
        if(L == R) return ;

        int mid = (L + R) >> 1;
        int middle_val = sorted[mid], same_with_middle = mid - L + 1;
        for(int i = L; i <= mid; i ++) {
            if(sorted[i] < middle_val) {
                same_with_middle --;
            }
        }
        int left_point = L, right_point = mid + 1;
        for(int i = L; i <= R; i ++) {
            to_left[dep][i] =  L == i ? 0 : to_left[dep][i - 1];
            if(val[dep][i] < middle_val) {
                to_left[dep][i] += 1;
            }

            if(val[dep][i] < middle_val) {
                val[dep + 1][left_point++] = val[dep][i];
            }
            else if(val[dep][i] > middle_val) {
                val[dep + 1][right_point++] = val[dep][i];
            }
            else {
                if(same_with_middle) {
                    val[dep + 1][left_point++] = val[dep][i];
                    --same_with_middle;
                    ++to_left[dep][i];
                }
                else val[dep + 1][right_point++] = val[dep][i];
            }
        }
        build(lson); build(rson);
    }
    int query(int dep, int L, int R, int l, int r, int k) {
        if(l == r) return val[dep][l];
        int mid = (L + R) >> 1;
        int cnt_sm_left  = l == L ? 0 : to_left[dep][l - 1];
        int cnt_sm_right = to_left[dep][r];
        int cnt_to_left = cnt_sm_right - cnt_sm_left;
        if(cnt_to_left >= k) {
            return query(lson, L + cnt_sm_left, L + cnt_sm_right - 1, k);
        }
        return query(rson, mid + 1 + l - L - cnt_sm_left, mid + 1 + r - L - cnt_sm_right, k - cnt_to_left);
    }
}T;