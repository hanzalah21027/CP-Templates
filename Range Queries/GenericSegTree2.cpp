struct Node {
	ll val; // may change

	Node() {	// Default value of segtree nodes
		val = 0; // may change
	}

	Node(ll x) {	// Actual Node
		val = x; // may change
	}

	void merge(Node &l, Node &r) {	// Merge two child nodes
		val = l.val + r.val;
	}

	void update(ll x) {	// apply update to given node
		val = x; // may change
	}
};

template <typename Node>
struct SegTree {
	vector<Node> tree;
	vector<ll> arr; // type may change
	int size;
	int n;

	SegTree(int a_len, vector<ll> &a) {	// change if type updated
		arr = a;
		n = a_len;
		size = 1;
		while (size < 2 * n)
		{
			size = size << 1;
		}
		tree.resize(size, Node());
		build(0, n - 1, 1);
	}

	int left(int index) {
		return 2 * index;
	}

	int right(int index) {
		return 2 * index + 1;
	}

	// O(n)
	void build(int start, int end, int index) {	// Never change this
		if (start == end) {
			tree[index] = Node(arr[start]);
			return;
		}

		int mid = (start + end) / 2;
		build(start, mid, left(index));                           // built left part
		build(mid + 1, end, right(index));                        // build right part
		tree[index].merge(tree[left(index)], tree[right(index)]); // merge two answer
	}

	// O(logn)
	void set(int start, int end, int index, int pos, ll val) {	// Never change this
		if (start == end) {	// reached your destination
			tree[index].update(val);
			return;
		}

		int mid = (start + end) / 2;
		if (pos <= mid)
			set(start, mid, left(index), pos, val); // Update Left
		else
			set(mid + 1, end, right(index), pos, val); // Update Right

		tree[index].merge(tree[left(index)], tree[right(index)]); // Merge two answers
	}

	// O(logn)
	Node query(int start, int end, int index, int l, int r) {	// Never change this
		if (start >= l and end <= r)
			return tree[index];

		// Disjoint -> [start... end...l...r] or [l...r...start...end]
		if (end < l or r < start) {
			return Node();
		}

		Node ans;
		int mid = (start + end) / 2;
		Node leftAns = query(start, mid, left(index), l, r);
		Node rightAns = query(mid + 1, end, right(index), l, r);
		ans.merge(leftAns, rightAns);
		return ans;
	}

	void make_update(int pos, ll val) {	// pass in as many parameters as required
		set(0, n - 1, 1, pos, val);
	}

	Node make_query(int l, int r) {
		return query(0, n - 1, 1, l, r);
	}
};