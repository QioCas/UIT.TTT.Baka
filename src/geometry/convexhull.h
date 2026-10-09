vector<Point> convexHull(vector<Point> dots) {
    sort(dots.begin(), dots.end());
    vector<Point> A(1, dots[0]);
    const int sz = dots.size();
    for(int c = 0; c < 2; reverse(all(dots)), c++)
    for(int i = 1, t = A.size(); i < sz; A.emplace_back(dots[i++]))
      while (A.size() > t and ccw(A[A.size()-2], A.back(), dots[i]) < 0)
        A.pop_back();
    A.pop_back(); return A; 
} 