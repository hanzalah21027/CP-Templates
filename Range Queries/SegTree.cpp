int left(int index)
{
    return 2 * index;
}

int right(int index)
{
    return 2 * index + 1;
}

ll merge(ll left, ll right)
{
    return left + right;
}

ll default_value()
{
    return 0;
}

// O(n)
void build(int start, int end, int index, vector<ll> &arr, vector<ll> &SGT)
{
    if (start == end)
    {
        SGT[index] = arr[start];
        return;
    }

    int mid = (start + end) / 2;
    build(start, mid, left(index), arr, SGT);                // built left part
    build(mid + 1, end, right(index), arr, SGT);             // build right part
    SGT[index] = merge(SGT[left(index)], SGT[right(index)]); // merge two answer
}

// O(logn)
void update(int start, int end, int index, vector<ll> &SGT, int pos, ll val)
{
    if (start == end)
    { // reached your destination
        SGT[index] = val;
        return;
    }

    int mid = (start + end) / 2;

    if (pos <= mid)
        update(start, mid, left(index), SGT, pos, val); // Update Left
    else
        update(mid + 1, end, right(index), SGT, pos, val); // Update Right

    SGT[index] = merge(SGT[left(index)], SGT[right(index)]); // Merge two answers
}

// O(logn)
ll query(int start, int end, int index, vector<ll> &SGT, int L, int R)
{
    // Complete Overlap
    // [L....start....end....R]
    if (L <= start and R >= end)
    {
        return SGT[index];
    }

    // Disjoin
    // [start...end...L...R] or [L...R...start...end]
    if (end < L or R < start)
    {
        return default_value();
    }

    // Partial
    int mid = (start + end) / 2;
    ll leftAns = query(start, mid, left(index), SGT, L, R);
    ll rightAns = query(mid + 1, end, right(index), SGT, L, R);
    return merge(leftAns, rightAns);
}

void solver()
{
    int n;
    cin >> n;
    vector<ll> a(n + 1), SGT(4 * n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    build(1, n, 1, a, SGT); // built the segment tree
}
