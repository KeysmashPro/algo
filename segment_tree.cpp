#include <iostream>
#include <vector>

template <typename T>
using vec = std::vector<T>;

using namespace std;
using usize = size_t;
using u64 = unsigned long long;
using i64 = long long;
using u32 = unsigned;
using i32 = int;


class segment_tree {
    vec<i64> tree;
    i64 (*fun)(i64, i64);
    i64 neutral;
    u64 size;

public:
    explicit segment_tree(vec<i64> &arr, i64 (*f)(i64, i64), i64 t)
        : tree(arr), fun(f), neutral(t), size(arr.size() / 2) {
            for (usize i = size - 1; i > 0; --i) {
                tree[i] = fun(tree[i<<1], tree[i<<1|1]);
            }
    };

    void modify(usize i, i64 val) {
        for (tree[i += size] = val; i > 1; i >>= 1) {
            tree[i>>1] = tree[i] + tree[i^1];
        }
    }

    void update(usize l, usize r, i64 val) {
        for (l += size, r += size; l < r; l >>= 1, r >>= 1) {
            if (l&1) tree[l++] += val;
            if (r&1) tree[--r] += val;
        }
    }

    void assign(usize l, usize r, i64 val) {
        //
    }

    i64 range(i64 l, i64 r) const {
        i64 res = neutral;
        for (l += size, r += size; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = fun(res, tree[l++]);
            if (r&1) res = fun(tree[--r], res);
        }
        return res;
    }
};

i32 main() {
    vec<i64> init = {0,0,0,0,0,8,9,4,2,-7};
    auto fun = [](i64 i0, i64 i1){
        return min(i0, i1);
    };

    segment_tree tree(init, fun, ((i64)1<<60));
    cout << tree.range(0, 6) << endl;
    return 0;
}
