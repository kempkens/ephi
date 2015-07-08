#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include "mandelbrot.h"

double ols_slope(std::vector< std::pair< double, double > > &data) {
    double xmean = 0;
    double ymean = 0;
    for (auto it = data.begin(); it != data.end(); ++it) {
        xmean += it->first;
        ymean += it->second;
    }
    xmean /= (double)data.size();
    ymean /= (double)data.size();

    double p = 0;
    double q = 0;
    for (auto it = data.begin(); it != data.end(); ++it) {
        p += (it->first - xmean) * (it->second - ymean);
        q += (it->first - xmean) * (it->first - xmean);
    }
    return p / q;
}

int main(int argc, char * argv[]) {
    const double xm = -0.7;
    const double ym = 0;
    const double d = 3.0769;
    const int max_iteration = 100;
    const double threshold = 2E-3;

    const int xsize = 2000;
    const int ysize = 1500;

    const double res = (double)xsize / d;

    const double xmin = xm - d / 2.0;
    const double ymin = -ym - d / 2.0 * ysize / xsize;

    std::vector<int> steps = {1, 2, 4, 5};
    std::vector< std::pair<double, double> > dim_data;

    for (auto it = steps.begin(); it != steps.end(); ++it) {
        long long count = 0;
        for (int Px = 0; Px < xsize; Px += *it) {
            for (int Py = 0; Py < ysize; Py += *it) {
                double x0 = (double)Px / res + xmin;
                double y0 = (double)Py / res + ymin;

                double b = mandelbrot::distance_estimator(x0, y0, max_iteration);
                if (fabs(b) < threshold) {
                    ++count;
                }
            }
        }

        // calc box dimension
        std::pair<double, double> dim_data_point = std::make_pair(-log(*it), log(count));
        dim_data.push_back(dim_data_point);
        printf("%.3f %.3f\n", dim_data_point.first, dim_data_point.second);
    }
    printf("box dimension = %.6f\n", ols_slope(dim_data));

    return 0;
}