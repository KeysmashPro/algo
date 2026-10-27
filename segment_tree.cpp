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

template <class func, class type>
class segment_tree {
    func monoid;
    type neutral;
    vec<type> tree;
    usize size;

public:
    explicit segment_tree(func f, type n, const vec<type> &val)
        : monoid(f), neutral(n), tree(val), size(val.size() / 2) {
            for (usize i = size - 1; i > 0; --i) {
                tree[i] = monoid(tree[i<<1], tree[i<<1|1]);
            }
    };

    void modify(usize i, type val) {
        for (tree[i += size] = val; i > 1; i >>= 1) {
            if (i&1) { tree[i>>1] = monoid(tree[i^1], tree[i]); }
            else     { tree[i>>1] = monoid(tree[i], tree[i^1]); }
        }
    }

    type range(usize l, usize r) const {
        type l_res = neutral;
        type r_res = neutral;
        for (l += size, r += size; l < r; l >>= 1, r >>= 1) {
            if (l&1) l_res = monoid(l_res, tree[l++]);
            if (r&1) r_res = monoid(tree[--r], r_res);
        }
        return monoid(l_res, r_res);
    }
};

i32 main() {
    vec<i64> init = {0,0,0,0,0,8,9,4,2,0};
    auto fun = [](i64 i0, i64 i1){
        return i0 +i1;
    };

    segment_tree<decltype(fun), i64> tree(fun, 0, init);
    tree.modify(4,-7);
    cout << tree.range(0, 5) << endl;
    return 0;
}
