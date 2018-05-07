#ifndef CubicSplineH
#define CubicSplineH

#include <cstdlib>
#include <cmath>
#include <limits>

class CubicSpline {
private:
	struct splineTuple {
		double a, b, c, d, x;
	};

	splineTuple *splines;
	int n;

	void freeMem();

public:
	CubicSpline();

	~CubicSpline();

	void buildSpline(const int16_t *x, const int16_t *y, int n);

	double f(double x) const;
};
#endif