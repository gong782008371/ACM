template<int M>
struct Matrix {
    static const int siz = M;
    int mat[55][55];
    Matrix() { mem0(mat); }
    Matrix operator * (const Matrix &another) {
        Matrix ans;
        rep (i, 1, siz) rep (j, 1, siz) rep (k, 1, siz) {
            ans.mat[i][j] += mat[i][k] * another.mat[k][j];
        }
        return ans;
    }
    static Matrix getUnit() {
        Matrix ans; rep (i, 1, siz) ans.mat[i][i] = 1;
        return ans;
    }
};
