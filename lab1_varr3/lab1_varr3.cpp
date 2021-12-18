#include <iostream>
#include <string>
#include <string.h>
using namespace std;

int is_vector(int arg) {
	for (int temp; arg != 0;) {
		temp = arg % 10;
		if ((temp != 0) && (temp != 1)) {
			cin.clear();
			cin.ignore(10000, '\n');
			return 1;
		}
		arg /= 10;
	}
	return 2;
}
int degree_counter(int number) {
	int i = 0;
	while (number != 0) {
		number /= 2;
		i++;
	}
	i--;
	return i;
}
int poly_counter(int number) {
	int i = 0;
	while (number != 0) {
		if (number % 2 == 1) i++;
		number /= 2;
	}
	return i;
}
int to_decimal(int number) {
	int res = 0, i = 0;
	while (number != 0) {
		if (number % 10 == 1) res = res + pow(2, i);
		i++;
		number /= 10;
	}
	return res;
}
int fact(int A)
{
	if (A <= 1) {
		return 1;
	}
	return A * fact(A - 1);
}
int poly_div(int m, int gx) {
	for (int gx_temp; (degree_counter(m) >= degree_counter(gx));) {
		gx_temp = gx << (degree_counter(m) - degree_counter(gx));
		m = m ^ gx_temp;
	}
	return m;
}

int* A_counter(int gx, int d, int m) {
	int count = pow(2, (degree_counter(m) + 1)) - 1;
	int* res = new int[count];
	int cx, ax, mx;
	int newm = 1;
	for (int i = 0; i != count; i++, newm++) {
		mx = newm * pow(2, degree_counter(gx));
		cx = poly_div(mx, gx);
		ax = mx + cx;
		res[i] = ax;
	}
	return res;
}

int weight(int* A, int d, int size) {
	int icount = 0;
	for (int i = 0, temp; i != size; i++) {
		temp = poly_counter(A[i]);
		if (temp >= d)icount++;
	}
	return icount;
}
double higher_border(double p, int d, int ax) {
	int c;
	double p_degree, p_bracket, res = 0;
	d--;
	while ((d + 1) != 0)
	{
		c = fact(ax) / (fact(d) * fact(ax - d));
		p_degree = pow(p, d);
		p_bracket = pow(1 - p, ax - d);
		d--;
		res = res + c * p_degree * p_bracket;
	}
	return (1 - res);
}
int fact_plus(int rowlen) {
	int res = 0;
	rowlen--;
	while (rowlen != 0) {
		res = res + rowlen;
		rowlen--;
	}
	return res;
}

double exact_val(double p, int d, int* A, int n, int size) {
	double p_degree, p_bracket, res = 0;
	int Ai;
	while ((d) != n + 1)
	{
		Ai = weight(A, d, size);
		p_degree = pow(p, d);
		p_bracket = pow(1 - p, n - d);
		d++;
		res = res + (Ai * p_degree * p_bracket);
	}
	return res;
}

int main()
{
	int gx;
	int p;
	int l;
	cout << "Input g(x) in a vector format (Example: x^3 + x + 1 = 1010) \n";
	while ((!(cin >> gx)) || (is_vector(gx) != 2)) {
		cout << "Wrong format\n";
		cin.clear();
		cin.ignore(10000, '\n');
	}
	cout << "Input l in a vector format (Example: x^3 + x + 1 = 1010) \n";
	while ((!(cin >> l)) || (is_vector(l) != 2)) {
		cout << "Wrong format\n";
		cin.clear();
		cin.ignore(10000, '\n');
	}
	cout << "Input p (from 0 to percent) \n";
	while (!(cin >> p) || ((p < 0) || (p > 100))) {
		cout << "Wrong format\n";
		cin.clear();
		cin.ignore(10000, '\n');
	}
	double pp = p * 0.01;
	int gx1 = to_decimal(gx);
	int l1 = to_decimal(l);
	int gx_l = degree_counter(gx1);
	int d = degree_counter(gx1);
	int m = l1 * pow(2, gx_l);
	int* A = new int[degree_counter(m)];
	A = A_counter(gx1, d, l1);
	int n = degree_counter(m) + 1;
	int size = pow(2, degree_counter(l1) + 1) - 1;
	double res1 = higher_border(pp, d, n);
	double res2 = exact_val(pp, d, A, n, size);
	string s = to_string(res1);
	string s1 = to_string(res2);
	cout << "\n Upper decode error estimate: " << s << " %\n";
	cout << "\n Exact decode error value: " << s1 << " %";
	return 0;
}
