#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

const long double eps = 1e-4;
const int MAXN = 2222;
const int MAXF = 2222;
const int INF = ~0u >> 2;

int dcmp(const long double &x) {
	return fabs(x) < eps ? 0 : (x > 0 ? 1 : -1);
}

namespace Geometry_2D{
	struct Point{
		long double x, y;
		Point() {}
		Point(long double x, long double y) : x(x), y(y) {}
		Point operator +(const Point &p)const {
			return Point(x + p.x, y + p.y);
		}
		Point operator -(const Point &p)const {
			return Point(x - p.x, y - p.y);
		}
		Point operator *(const long double &p)const {
			return Point(x * p, y * p);
		}
		Point operator /(const long double &p)const {
			return Point(x / p, y / p);
		}
	};
	long double det(const Point &a, const Point &b) {
		return a.x * b.y - b.x * a.y;
	}
	
	bool Pair_Comp(const Point &a, const Point &b) {
		if (dcmp(a.x - b.x) < 0) return true;
		if (dcmp(a.x - b.x) > 0) return false;
		return dcmp(a.y - b.y) < 0;
	}
	
	int Convex_Hull(int n, Point *P, Point *C) {
		std::sort(P, P + n, Pair_Comp);
		int top = 0;
		for (int i = 0; i < n; i++) {
			while (top >= 2 && dcmp(det(C[top - 1] - C[top - 2], P[i] - C[top - 2])) <= 0) top--;
			C[top++] = P[i];
		}
		int lasttop = top;
		for (int i = n - 1; i >= 0; i--) {
			while (top > lasttop && dcmp(det(C[top - 1] - C[top - 2], P[i] - C[top - 2])) <= 0) top--;
			C[top++] = P[i];
		}
		return top;
	}
	
	long double getArea(int n, Point *p) {
		long double ret = 0;
		for (int i = 0; i < n; i++)
			ret += det(p[i], p[(i + 1) % n]);
		return fabs(ret) / 2.0;
	}
};

namespace Geometry_3D{
	struct TPoint{
		long double x, y, z;
		TPoint() {}
		TPoint(long double x, long double y, long double z) : x(x), y(y), z(z) {}
		TPoint operator +(const TPoint &p)const {
			return TPoint(x + p.x, y + p.y, z + p.z);
		}
		TPoint operator -(const TPoint &p)const {
			return TPoint(x - p.x, y - p.y, z - p.z);
		}
		TPoint operator *(const long double &p)const {
			return TPoint(x * p, y * p, z * p);
		}
		TPoint operator /(const long double &p)const {
			return TPoint(x / p, y / p, z / p);
		}
		void read() {
			double X, Y, Z;
			scanf("%lf%lf%lf", &X, &Y, &Z);
			x = X;
			y = Y;
			z = Z;
		}
	};
	struct Triangle{
		TPoint a, b, c;
		Triangle() {}
		Triangle(TPoint a, TPoint b, TPoint c) : a(a), b(b), c(c) {}
	};
	long double sqrdist(const TPoint &a) {
		long double ret = 0;
		ret += a.x * a.x;
		ret += a.y * a.y;
		ret += a.z * a.z;
		return ret;
	}
	long double sqrdist(const TPoint &a, const TPoint &b) {
		long double ret = 0;
		ret += (a.x - b.x) * (a.x - b.x);
		ret += (a.y - b.y) * (a.y - b.y);
		ret += (a.z - b.z) * (a.z - b.z);
		return ret;
	}
	long double dist(const TPoint &a) {
		return sqrt(sqrdist(a));
	}
	TPoint det(const TPoint &a, const TPoint &b) {
		TPoint ret;
		ret.x = a.y * b.z - b.y * a.z;
		ret.y = a.z * b.x - b.z * a.x;
		ret.z = a.x * b.y - b.x * a.y;
		return ret;
	}
	long double dot(const TPoint &a, const TPoint &b) {
		long double ret = 0;
		ret += a.x * b.x;
		ret += a.y * b.y;
		ret += a.z * b.z;
		return ret;
	}
	long double detdot(const TPoint &a, const TPoint &b, const TPoint &c, const TPoint &d) {
		return dot(det(b - a, c - a), d - a);
	}
	namespace Convex_Hull{
		struct Face{
			int a, b, c;
			bool isOnConvex;
			Face() {}
			Face(int a, int b, int c) : a(a), b(b), c(c) {}
		};
		
		int nFace, left, right, whe[MAXN][MAXN];
		Face queue[MAXF], tmp[MAXF];
		
		bool isVisible(const std::vector<TPoint> &p, const Face &f, const TPoint &a) {
			return dcmp(detdot(p[f.a], p[f.b], p[f.c], a)) > 0;
		}
		
		bool init(std::vector<TPoint> &p) {
			bool check = false;
			for (int i = 1; i < (int)p.size(); i++) {
				if (dcmp(sqrdist(p[0], p[i]))) {
					std::swap(p[1], p[i]);
					check = true;
					break;
				}
			}
			if (!check) return false;
			check = false;
			for (int i = 2; i < (int)p.size(); i++) {
				if (dcmp(sqrdist(det(p[i] - p[0], p[1] - p[0])))) {
					std::swap(p[2], p[i]);
					check = true;
					break;
				}
			}
			if (!check) return false;
			check = false;
			for (int i = 3; i < (int)p.size(); i++) {
				if (dcmp(detdot(p[0], p[1], p[2], p[i]))) {
					std::swap(p[3], p[i]);
					check = true;
					break;
				}
			}
			if (!check) return false;
			for (int i = 0; i < (int)p.size(); i++)
				for (int j = 0; j < (int)p.size(); j++)
					whe[i][j] = -1;
			return true;
		}
		
		void pushface(const int &a, const int &b, const int &c) {
			nFace++;
			tmp[nFace] = Face(a, b, c);
			tmp[nFace].isOnConvex = true;
			whe[a][b] = nFace;
			whe[b][c] = nFace;
			whe[c][a] = nFace;
		}
		
		bool deal(const std::vector<TPoint> &p, const std::pair<int, int> &now, const TPoint &base) {
			int id = whe[now.second][now.first];
			if (!tmp[id].isOnConvex) return true;
			if (isVisible(p, tmp[id], base)) {
				queue[++right] = tmp[id];
				tmp[id].isOnConvex = false;
				return true;
			}
			return false;
		}
		
		std::vector<Triangle> getConvex(std::vector<TPoint> &p) {
			static std::vector<Triangle> ret;
			ret.clear();
			nFace = 0;
			if(!init(p)) return ret;
			if (!isVisible(p, Face(0, 1, 2), p[3])) pushface(0, 1, 2); else pushface(0, 2, 1);
			if (!isVisible(p, Face(0, 1, 3), p[2])) pushface(0, 1, 3); else pushface(0, 3, 1);
			if (!isVisible(p, Face(0, 2, 3), p[1])) pushface(0, 2, 3); else pushface(0, 3, 2);
			if (!isVisible(p, Face(1, 2, 3), p[0])) pushface(1, 2, 3); else pushface(1, 3, 2);
			for (int a = 4; a < (int)p.size(); a++)	{
				TPoint base = p[a];
				for (int i = 1; i <= nFace; i++) {
					if (tmp[i].isOnConvex && isVisible(p, tmp[i], base)) {
						left = 0, right = 0;
						queue[++right] = tmp[i];
						tmp[i].isOnConvex = false;
						while (left < right) {
							Face now = queue[++left];
							if (!deal(p, std::make_pair(now.a, now.b), base)) pushface(now.a, now.b, a);
							if (!deal(p, std::make_pair(now.b, now.c), base)) pushface(now.b, now.c, a);
							if (!deal(p, std::make_pair(now.c, now.a), base)) pushface(now.c, now.a, a);
						}
						break;
					}
				}
			}
			for (int i = 1; i <= nFace; i++) {
				Face now = tmp[i];
				if (now.isOnConvex) {
					ret.push_back(Triangle(p[now.a], p[now.b], p[now.c]));
				}
			}
			return ret;
		}
	}
}

int n;
std::vector<Geometry_3D::TPoint> data;
std::vector<Geometry_3D::Triangle> convex;

long double getDist(const Geometry_3D::TPoint &a, const Geometry_3D::Triangle &p) {
	long double ret = fabs(Geometry_3D::detdot(p.a, p.b, p.c, a));
	ret /= Geometry_3D::dist(det(p.b - p.a, p.c - p.b));
	return ret;
}

long double getArea(const std::vector<Geometry_3D::TPoint> &data, const Geometry_3D::Triangle &face) {
	static Geometry_2D::Point p[MAXN], c[MAXN];
	Geometry_3D::TPoint xAxis = face.b - face.a;
	Geometry_3D::TPoint yAxis = det(det(xAxis, face.c - face.a), xAxis);
	int tot = 0;
	for (int i = 0; i < (int)data.size(); i++) {
		p[tot].x = Geometry_3D::dot(data[i], xAxis) / Geometry_3D::dist(xAxis);
		p[tot].y = Geometry_3D::dot(data[i], yAxis) / Geometry_3D::dist(yAxis);
		tot++;
	}
	tot = Geometry_2D::Convex_Hull(tot, p, c) - 1;
	return Geometry_2D::getArea(tot, c);
}

int main() {
	freopen("H.in", "r", stdin);
	while (scanf("%d", &n) == 1) {
		if (n == 0) break;
		data.clear();
		for (int i = 1; i <= n; i++) {
			Geometry_3D::TPoint now;
			now.read();
			data.push_back(now);
		}
		convex = Geometry_3D::Convex_Hull::getConvex(data);
		std::pair<long double, long double> answer = std::make_pair(0, INF);
		for (int i = 0; i < (int)convex.size(); i++) {
			long double maxdist = 0;
			for (int j = 0; j < (int)data.size(); j++) {
				maxdist = std::max(maxdist, getDist(data[j], convex[i]));
			}
			if (dcmp(answer.first - maxdist) == 0) {
				answer.second = std::min(answer.second, getArea(data, convex[i]));
			}
			else if (dcmp(answer.first - maxdist) < 0) {
				answer.first = maxdist;
				answer.second = getArea(data, convex[i]);
			}
		}
		std::pair<double, double> out = std::make_pair(answer.first, answer.second);
		printf("%.3f %.3f\n", out.first, out.second);
	}
	return 0;
}
