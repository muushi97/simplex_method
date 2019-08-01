#include <iostream>
#include <vector>

template <class T>
class simplex_method {
private:
    int N, M;
    std::vector<T> mc(N);
    std::vector<T> mx(N);
    std::vector<std::vector<T>> mA(M);
    std::vector<T> mb(M);

public:
    simplex_method(int N, int M) : N(N), M(M), c(N), x(N), A(M), b(M) {
        for (int i = 0; i < A.size(); i++) A[i].resize(N);
    }

    void hoge() {
        /*
 basis variable | basis value |  z    x1        x2       ...  x(n+m)        | limit of increase
 ---------------------------------------------------------------------------------------
       bv[0]    |     bvv[0]  | p[0] p[1]      p[2]      ...  p[n+m]        | loi[0]
       bv[1]    |     bvv[1]  |  -   t[0][0]   t[0][1]   ...  t[0][n+m-1]   | loi[1]
       bv[2]    |     bvv[2]  |  -   t[1][0]   t[1][1]   ...  t[1][n+m-1]   | loi[2]
       ...      |     ...     | ...  ...       ...       ...  ...           | ...
       bv[M]    |     bvv[M]  |  -   t[M-1][0] t[M-1][1] ...  t[M-1][n+m-1] | loi[M]
         */
        // 基底変数 (0 : z, 1:x(N+1), 2:x(N+2), ..., M:x(N+M))
        std::vector<int> bv(1 + M);                 // 基底変数 (pのインデックスと対応)
        bv[0] = 0;
        for (int i = 1; i < M + 1; i++) bv[i] = M + i;

        std::vector<T> bvv(1 + M);                  // 基底変数の値
        bvv[0] = 0;
        for (int i = 1; i < M + 1; i++) bvv[i] = b[i - 1];

        std::vector<T> loi(1 + M);                  // 増加限界
        for (int i = 0; i < M + 1; i++) loi[i] = 0;

        std::vector<T> p(N + M + 1);                // シンプレックス基準
        std::vector<std::vector<T>> t(M);           // たブロー
        for (int i = 0; i < A.size(); i++) {
            t[i].resize(N + M);
            for (int j = 0; j < N + M; j++) t[i][j] = (N == N - j) ? 1 : 0;
        }
    }


    T z() const {
        T r = 0;
        for (int i = 0; i < N; i++) r += mc[i] * mx[i];
        return r;
    }
    std::vector<T> b() {
        std::vector<T> r(b.size());
        for (int i = 0; i < M; i++) r[i] = b(i);
        return r;
    }
    T b(int i) {
        T r = 0;
        for (int j = 0; j < N; j++) r += mA[i][j] * mx[j];
        return r;
    }
};

int main() {
    return 0;
}

