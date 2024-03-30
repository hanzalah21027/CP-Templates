
int left(int index) {
	return 2 * index;
}

int right(int index) {
	return 2 * index + 1;
}

ll merge(ll left, ll right) {
	return left + right;
}

void build(int start, int end, int index, vector<ll>&sgt, vector<ll>& arr) {
	if (start == end) {
		sgt[index] = arr[start];
		return;
	}

	int mid = (start + end) / 2;
	build(start, mid, left(index), sgt, arr);
	build(mid + 1, end, right(index), sgt, arr);
	sgt[index] = merge(sgt[left(index)], sgt[right(index)]);
}

void apply(int start, int end, int index, vector<ll>&sgt, vector<ll>&lazy, ll val) {
	sgt[index] += (end - start + 1) * val;
	lazy[index] += val;

}

void pushdown(int start, int end, int index, vector<ll>&sgt, vector<ll>&lazy) {
	if (start == end) {
		lazy[index] = -1;
		return;
	}

	int mid = (start + end) / 2;

	apply(start, mid, left(index), sgt, lazy, lazy[index]);
	apply(mid + 1, end, right(index), sgt, lazy, lazy[index]);
	lazy[index] = -1;
}

void update(int start, int end, int index, vector<ll>&sgt, vector<ll>&lazy, int l, int r, ll val) {
	if (lazy[index] != -1) {
		pushdown(start, end, index, sgt, lazy);
	}

	// Disjoint   [start...end...l...r] or [l...r...start...end]
	if (start > r or l > end)
		return;

	// Complete overlap   [l...start...end...r]
	if (l <= start and end <= r) {
		apply(start, end, index, sgt, lazy, val);
		return;
	}

	int mid = (start + end) / 2;

	update(start, mid, left(index), sgt, lazy, l, r , val);
	update(mid + 1, end, right(index), sgt, lazy, l, r, val);
	sgt[index] = merge(sgt[left(index)], sgt[right(index)]);
}

ll query(int start, int end, int index, vector<ll>&sgt, vector<ll>&lazy, int l, int r) {
	if (lazy[index] != -1) {
		pushdown(start, end, index, sgt, lazy);
	}

	// Disjoint   [start...end...l...r] or [l...r...start...end]
	if (start > r or l > end)
		return 0;

	// Complete overlap   [l...start...end...r]
	if (l <= start and end <= r) {
		return sgt[index];
	}

	int mid = (start + end) / 2;
	ll ans, leftans, rightans;
	leftans = query(start, mid, left(index), sgt, lazy, l, r);
	rightans = query(mid + 1, end, right(index), sgt, lazy, l, r);
	ans = merge(leftans, rightans);
	return ans;
}



void solver() {
	int n, m;
	cin >> n >> m;
	vector<ll> arr(n, 0);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	vector<ll> lazy(4 * n, -1);
	vector<ll> sgt(4 * n);

	build(0, n - 1, 1, sgt, arr);
	while (m--) {
		int op;
		cin >> op;
		if (op == 0) {
			ll l, r, v;
			cin >> l >> r >> v;
			l--; r--;
			update(0, n - 1, 1, sgt, lazy, l, r, v);
		}
		else {
			int l , r;
			cin >> l >> r;
			l--; r--;
			cout << query(0, n - 1, 1, sgt, lazy, l, r) << nline;
		}
	}

}