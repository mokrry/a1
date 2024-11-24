#include <iostream>
#include <cstdlib>
#include <ctime>
#include "helping_functions.h"
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <cmath>

using namespace std;

class Circle {
public:
    double x, y, r;
    Circle(double a, double b, double c){
        x=a;
        y=b;
        r=c;
    }
};

bool isInside(const Circle &circle, double px, double py) {
    return (px - circle.x) * (px - circle.x) + (py - circle.y) * (py - circle.y) <= circle.r * circle.r;
}

int main() {
    vector<vector<double>> data;
    vector<double>aprox_area;
    vector<double>n;
    vector<double>scale;
    vector<double>dif;

    vector<Circle> circles;
    circles.push_back(Circle(1,1,1));
    circles.push_back(Circle(1.5,2,sqrt(5)/2));
    circles.push_back(Circle(2,1.5,sqrt(5)/2));

    double min_x = min(circles[0].x - circles[0].r, min(circles[1].x - circles[1].r,circles[2].x - circles[2].r));
    double max_x = max(circles[0].x + circles[0].r, max(circles[1].x + circles[1].r,circles[2].x + circles[2].r));
    double min_y = min(circles[0].y - circles[0].r, min(circles[1].y - circles[1].r,circles[2].y - circles[2].r));
    double max_y = max(circles[0].y + circles[0].r, max(circles[1].y + circles[1].r,circles[2].y + circles[2].r)) ;

    double realArea = static_cast<double>(0.25*M_PI+1.25*std::asin(0.8) - 1);
    // Monte Carlo simulation
    srand(time(0));
    for(int s = 1; s < 6; s++){
        for(int k = 100; k <= 100000; k+=500){
            int totalPoints = k;
            int insidePoints = 0;
            for (int i = 0; i < totalPoints; ++i) {
                double px = min_x + (max_x - min_x) * (double(rand()) / RAND_MAX);
                double py = min_y + (max_y - min_y) * (double(rand()) / RAND_MAX);

                bool inside = true;
                for (const Circle &circle : circles) {
                    if (!isInside(circle, px, py)) {
                        inside = false;
                        break;
                    }
                }

                if (inside) {
                    ++insidePoints;
                }
            }
            double boundingBoxArea = (max_x - min_x) * (max_y - min_y);
            double estimatedArea = boundingBoxArea * static_cast<double>(insidePoints) / static_cast<double>(totalPoints);
            aprox_area.push_back(estimatedArea);
            n.push_back(k);
            scale.push_back(s);
            dif.push_back(realArea-estimatedArea);
            cout.precision(8);
            cout << estimatedArea << endl;
        }
        data.push_back(aprox_area);
        data.push_back(n);
        data.push_back(scale);
        data.push_back(dif);
        writeCSV(data, "output.csv");
        aprox_area.clear();
        n.clear();
        scale.clear();
        dif.clear();
        data.clear();
    }

    return 0;
}