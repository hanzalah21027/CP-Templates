
struct Node {
	ll val, idx; // may change

	Node(){	// Default value of segtree nodes
		val = -1; // may change
		idx = -1; // may change
	}

	Node(ll i, ll x){	// Actual Node
		val = x; // may change
		idx = i;
	}

	void merge(Node &l, Node &r){	// Merge two child nodes
		if (l.val >= r.val) {
			val = l.val;
			idx = l.idx;
		}
		else {
			val = r.val;
			idx = r.idx;
		}
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
		if (start == end){
			tree[index] = Node(start, arr[start]);
			return;
		}

		int mid = (start + end) / 2;
		build(start, mid, left(index));                           // built left part
		build(mid + 1, end, right(index));                        // build right part
		tree[index].merge(tree[left(index)], tree[right(index)]); // merge two answer
	}

	// O(logn)
	void set(int start, int end, int index, int pos, ll val) {	// Never change this
		if (start == end){	// reached your destination
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
	Node query(int start, int end, int index, ll x) {	// Never change this
		if (start == end) {
			if (tree[index].val >= x)
				return tree[index];
			else
				return Node();
		}

		int mid = (start + end) / 2;

		if (tree[left(index)].val >= x) {
			return query(start, mid, left(index), x);
		}
		else {
			return query(mid + 1, end, right(index), x);
		}
	}

	void make_update(int pos, ll val) {	// pass in as many parameters as required
		set(0, n - 1, 1, pos, val);
	}

	Node make_query(ll x) {
		return query(0, n - 1, 1, x);
	}
};

