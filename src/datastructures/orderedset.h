#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template<class T>
using OrderedTree = tree<T, null_type, less<T>, rb_tree_tag,
    tree_order_statistics_node_update>;
template<class T>
using OrderedMultiTree = tree<T, null_type, less_equal<T>, rb_tree_tag,
    tree_order_statistics_node_update>;

// [void] s.insert(x): insert x into s
// [itr ] s.find_by_order(id): s[id]
// [int ] s.order_of_key(x): min_id; s[min_id] >= x or number val < x
// [int ] s.order_of_key(x): min_id; s[min_id] >= x or number val < x
// [int ] s.order_of_key(r + 1) - s.order_of_key(l): number val in range [l, r]
// [void] s.erase(x): erase x in s
// [itr ] s.find(x): find x in s. if not exist, return s.end()
// [itr ] s.lower_bound(x): s[min_id]; s[min_id] >= x
// [itr ] s.upper_bound(x): s[min_id]; s[min_id] > x