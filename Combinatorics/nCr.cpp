ll fact[1000001], ifact[1000001];
 
ll nCr(int n, int r) {
	return mod_mul(fact[n], mod_mul(ifact[r], ifact[n - r], mod), mod);
}

int main(){
    fact[0] = 1;
	for (int i = 1; i <= 1000000; i++)
		fact[i] = mod_mul(fact[i - 1], i, mod);
 
	ifact[1000000] = mminvprime(fact[1000000], mod);
 
	for (int i = 999999; i >= 0; i--)
		ifact[i] = mod_mul(i + 1, ifact[i + 1], mod);
}