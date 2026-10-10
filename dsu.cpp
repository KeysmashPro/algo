#include <iostream>
#include <vector>

using namespace std;
using u32 = unsigned;
using i32 = int;

template <typename T>
using vec = std::vector<T>;

u32 root_dsu(u32 x, vec<u32> &dsu) {
    return (dsu[x] == x) ? x : dsu[x] = root_dsu(dsu[x], dsu);
}

u32 unite_dsu(u32 x1, u32 x2, vec<u32> &dsu, vec<u32> &mas) {
    u32 r1 = root_dsu(x1, dsu);
    u32 r2 = root_dsu(x2, dsu);
    if (mas[r1] < mas[r2])  swap(r1, r2);
    mas[r1] += mas[r2];
    return dsu[r2] = r1;
}

i32 main() {
    u32 n = 1000000;
    vec<u32> dsu(n, 0);
    vec<u32> mas(n, 1);
    for (u32 i = 0; i < n; ++i) dsu[i] = i;

    for (u32 i = 7; i < n; i+=7) {
        unite_dsu(i, i-7, dsu, mas);
    }

    for (u32 i = 0; i < n; i+=7) {
        cout << root_dsu(i, dsu) << ' ';
    }
    cout << endl;
    return 0;
}
