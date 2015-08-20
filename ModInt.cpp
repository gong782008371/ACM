template<int M>
struct ModInt {
    const static int MOD = M;
    int val;
    ModInt(int _val = 0): val(_val){}
    int show() { return this->val;  }
    bool operator == (const ModInt &A) { return val == A.val; }
    bool operator != (const ModInt &A) { return val != A.val; }
    ModInt operator + (const ModInt &A) { return (val + A.val) % MOD; }
    ModInt operator - (const ModInt &A) { return (val - A.val + MOD) % MOD; }
    ModInt operator * (const ModInt &A) { return (int)( (long long) val * A.val % MOD ); }
    ModInt operator / (const ModInt &A) { return (*this) * ModInt::inv(A.val, MOD); }

    friend ostream& operator<< (ostream &os, ModInt &modInt) { os<<modInt.val; return os; }
    static int inv(int a, int m) { return a==1 ? 1 : (long long)inv(m%a,m)*(m-m/a)%m; }
};
