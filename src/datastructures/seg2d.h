/**
 * Usage:
 * a[0..n-1][0..n-1]
 * build()
 * update(x, y, val): a[x][y] += val
 * query(x1, y1, x2, y2): a[x][y] x1 <= x <= x2, y1 <= y <= y2
*/
const int MAX=1003;

int a[MAX][MAX], seg[2*MAX][2*MAX], n;

void build() {
    for(int x=0;x<n;++x) 
        for(int y=0;y<n;++y)
        seg[x+n][y+n] = a[x][y];
	for (int x = 2*n; x; x--) for (int y = 2*n; y; y--) {
		if (x < n) seg[x][y] = seg[2*x][y] + seg[2*x+1][y];
		if (y < n) seg[x][y] = seg[x][2*y] + seg[x][2*y+1];
	}
}

int query(int x1, int y1, int x2, int y2) {
	int ret = 0, y3 = y1 + n, y4 = y2 + n;
	for (x1 += n, x2 += n; x1 <= x2; ++x1 /= 2, --x2 /= 2)
		for (y1 = y3, y2 = y4; y1 <= y2; ++y1 /= 2, --y2 /= 2) {
			if (x1%2 == 1 and y1%2 == 1) ret += seg[x1][y1];
			if (x1%2 == 1 and y2%2 == 0) ret += seg[x1][y2];
			if (x2%2 == 0 and y1%2 == 1) ret += seg[x2][y1];
			if (x2%2 == 0 and y2%2 == 0) ret += seg[x2][y2];
		}
	
	return ret;
}

void update(int x, int y, int val) {
	int y2 = y += n;
	for (x += n; x; x /= 2, y = y2) {
		if (x >= n) seg[x][y] = val;
		else seg[x][y] = seg[2*x][y] + seg[2*x+1][y];
		
		while (y /= 2) seg[x][y] = seg[x][2*y] + seg[x][2*y+1];
	}
}

