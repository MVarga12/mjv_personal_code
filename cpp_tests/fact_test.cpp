#include <iostream>
#include <cmath>
#include <chrono>


    long double factorial(unsigned n)
    {
        return (n == 0) ? 1 : n * factorial(n - 1);
    }

    // Following from Numerical Recipes, ch. 6
    double gammln(double n) {
        double x { 0 };
        double y { 0 };
        double tmp { 0 };
        double ser { 0 };
        static double cof[6]={76.18009172947146,-86.50532032941677,24.01409824083091,-1.231739572450155,
                              0.1208650973866179e-2,-0.5395239384953e-5};
        int j {0};
        y=x=n;
        tmp=x+5.5;
        tmp -= (x+0.5)*log(tmp);
        ser=1.000000000190015;
        for (j=0;j<=5;j++) ser += cof[j]/++y;
        return -tmp+log(2.5066282746310005*ser/x);
    }

    double gammFactorial(int n) {
        static int ntop=4;
        static float a[33] = {1.0, 1.0, 2.0, 6.0, 24.0 };
        int j {0};

        if (n < 0) {
            std::cerr << "Error, computing factorial for negative number.\n";
            exit(1);
        }

        if (n > 32)
            return exp(gammln(n+1.0));

        while (ntop < n) {
            j = ntop++;
            a[ntop] = a[j] * ntop;
        }

        return a[n];
    }

using Timer = std::chrono::steady_clock;
int main() {
    Timer::time_point start = Timer::now();

    int itr { 0 };
    while (++itr < 32) {
        std::cout << factorial(itr) << '\n';
    }
    std::cout << "Recursive: " << std::chrono::duration<double>(Timer::now() - start).count() << '\n';

    Timer::time_point start2 = Timer::now();
    itr = 0;
    while (++itr < 32) {
        std::cout << gammFactorial(itr) << '\n';
    }
    std::cout << "Recursive: " << std::chrono::duration<double>(Timer::now() - start2).count() << '\n';
}
