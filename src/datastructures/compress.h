template<class Tp> struct Compress : vector<Tp> {
    Compress() = default;
    template<class Data, class = decltype(*declval<Data>().begin())>
    Compress(const Data& data) : Compress(data.begin(), data.end()) {}
    template<class Iterator, class = decltype(*declval<Iterator>())>
    Compress(Iterator first, Iterator last) {
        for(auto it = first; it != last; ++it) (*this).push_back(*it);
        build();
    }
    void build() {
        sort(begin(*this), end(*this));
        (*this).erase(unique(begin(*this), end(*this)), end(*this));
    }
    int prod(const Tp& x, int default_value = -1) {
        auto it = lower_bound(begin(*this), end(*this), x);
        return it != end(*this) && *it == x ? it - begin(*this) : default_value;
    }
};

