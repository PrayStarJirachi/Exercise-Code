#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

const long long MAXB = 1001;

long long size, c[MAXB][2];
char buff[MAXB], d[MAXB];
std::string exp;
bool hX[MAXB];

long long gcd(long long a, long long b) {return b ? gcd(b, a % b) : a;}

struct Factor{
	long long p, q;
	Factor() {}
	Factor(long long p) : p(p), q(1) {}
	Factor(long long p, long long q) : p(p), q(q) {
		simplify();
	}
	void simplify() {
		long long g = gcd(p, q);
		if (g == 0) {
			p = 0;
			q = 0;
		}
		else{
			p /= g; q /= g;
			if (q < 0) {
				p = -p;
				q = -q;
			}
		}
	}
	Factor operator +(const Factor &rhs)const {
		Factor ret;
		ret.p = p * rhs.q + q * rhs.p;
		ret.q = q * rhs.q;
		ret.simplify();
		return ret;
	}
	Factor operator -(const Factor &rhs)const {
		Factor ret;
		ret.p = p * rhs.q - q * rhs.p;
		ret.q = q * rhs.q;
		ret.simplify();
		return ret;
	}
	Factor operator *(const Factor &rhs)const {
		Factor ret;
		ret.p = p * rhs.p;
		ret.q = q * rhs.q;
		ret.simplify();
		return ret;
	}
	Factor operator /(const Factor &rhs)const {
		if (rhs.q == 0) {
			return rhs;
		}
		Factor ret;
		ret.p = p * rhs.q;
		ret.q = q * rhs.p;
		ret.simplify();
		return ret;
	}
	void print()const {
		if (q == 0) {
			if (p == 0) puts("MULTIPLE");
			else puts("NONE");
		}
		else{
			cout << "X = " << p << "/" << q << "\n";
		}
	}
};

bool isoperator(const char &c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}

Factor getres(const Factor &a, const Factor &b, const char &c) {
	if (c == '+') return a + b;
	if (c == '-') return a - b;
	if (c == '*') return a * b;
	if (c == '/') return a / b;
	return Factor(0, 1);
}
char getopp(const char &c) {
	if (c == '+') return '-';
	if (c == '-') return '+';
	if (c == '*') return '/';
	if (c == '/') return '*';
	return ' ';
}

Factor calc(long long x) {
	if (!isoperator(d[x])) return Factor(d[x] - '0');
	return getres(calc(c[x][0]), calc(c[x][1]), d[x]);
}

Factor check(long long x, const Factor &answer) {
	if (!isoperator(d[x])) {
		//return Factor(d[x] - '0');
		if (isdigit(d[x])) return Factor(d[x] - '0');
		else return answer;
	}
	return getres(check(c[x][0], answer), check(c[x][1], answer), d[x]);
}

bool predfs(long long x) {
	if (d[x] == 'X') return hX[x] = true;
	if (isoperator(d[x])) {
		hX[x] |= predfs(c[x][0]);
		hX[x] |= predfs(c[x][1]);
	}
	return hX[x];
}

long long construct(long long l, long long r) {
	if (isoperator(d[l])) {
		if (hX[c[l][1]] && (d[l] == '+' || d[l] == '*')) {
			std::swap(c[l][1], c[l][0]);
		}
		if (hX[c[l][0]]) {
			size++; hX[size] = false;
			c[size][0] = r;
			c[size][1] = c[l][1];
			d[size] = getopp(d[l]);
			return construct(c[l][0], size);
		}
		else{
			long long tmp = c[l][1];
			c[l][1] = r;
			return construct(tmp, l);
		}
	}
	else return r;
}

void solve(const std::string &e) {
	static long long stack[MAXB];
	size = 0;
	long long top = 0;
	for (long long i = 0; i < (int)e.length(); i++) {
		if (e[i] == ' ') continue;
		size++; hX[size] = false;
		c[size][1] = c[size][0] = 0;
		if (isoperator(e[i])) {
			c[size][1] = stack[top--];
			c[size][0] = stack[top--];
		}
		d[size] = e[i];
		stack[++top] = size;
	}
	if (size == 0) {
		return;
	}
	std::fill(hX + 1, hX + size + 1, false);
	predfs(size);
	if (!hX[size]) {
		Factor tmp = calc(size) / Factor(0);
		tmp.print();
		return;
	}
	long long rt = size;
	size++; hX[size] = false;
	c[size][0] = c[size][1] = 0;
	d[size] = '0';
	Factor ans = calc(construct(rt, size));
	
	size = 0; top = 0;
	for (long long i = 0; i < (int)e.length(); i++) {
		if (e[i] == ' ') continue;
		size++; hX[size] = false;
		c[size][1] = c[size][0] = 0;
		if (isoperator(e[i])) {
			c[size][1] = stack[top--];
			c[size][0] = stack[top--];
		}
		d[size] = e[i];
		stack[++top] = size;
	}
	Factor now = check(size, ans);
	if (now.q == 0) {
		now = check(size, Factor(18231));
		if (now.p == 0) puts("MULTIPLE");
		else puts("NONE");
		return;
	}
	ans.print();
}

int main() {
	freopen("E.in", "r", stdin);
	while (gets(buff)) {
		exp = buff;
		if ((int)exp.length() == 0) {
			continue;
		}
		solve(exp);
	}
	return 0;
}
