vector<ll> sieve(int n) {
    vector<ll> lpf(n + 1);
    for (int i = 0; i <= n; i++)    lpf[i] = i; 
    for (int i = 2; i * i <= n; i++) {
        if (lpf[i] != i) {
            continue;
        } 
        for (int j = i * i; j <= n; j += i)     lpf[j] = i;
    } 
    return lpf;
}
