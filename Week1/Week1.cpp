#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int p, a, b, c, d;
typedef unsigned long int uLong;

double f(uLong i)
{
    return p * (sin(a*i+b) + cos(c*i+d) + 2);
}

double max_fall(uLong n)
{
    double max_fall = 0.0;
    double max_func_val = 0;

    for(uLong i = 1; i <= n; i++)
    {
        double current_func_val = f(i);

        if(max_func_val - current_func_val > max_fall)
            max_fall = max_func_val - current_func_val;

        if(current_func_val > max_func_val)
            max_func_val = current_func_val;
    }

    return max_fall;

}

int main()
{

    uLong n;
    cin >> p >> a >> b >> c >> d >> n;

    cout << setprecision(6) << fixed << max_fall(n) << endl;
}