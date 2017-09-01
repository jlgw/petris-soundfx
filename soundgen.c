#include <stdint.h>
#include <stdio.h>
#include <math.h>

double pitch = 440 * 2*3.14159;

double y(double t, double amp, double freq, double peak, double exp, 
        double min, double dec) {
    double fade = pow(2.718, -t/pitch*dec);
    double pulse = (peak==0) + (peak!=0)/(pow(fabs((t/pitch-peak)/
                    ((peak==0)+peak)), exp) + min);
    return amp*fade*pulse*sin(freq*t);
}


int main(int argc, char* argv[]) {
    int16_t v;
    char* p = (char*) (&v);

    double t    = 0;
    double amp  = 1;
    double freq = 1;
    double peak = 0.1;
    double exp  = 2;
    double min  = 0.3;
    double dec  = 1;
    double dur  = 1;

    switch(argc){
        case 7:
            sscanf(argv[6], "%lf", &dec);
        case 6:
            sscanf(argv[5], "%lf", &min);
        case 5:
            sscanf(argv[4], "%lf", &exp);
        case 4:
            sscanf(argv[3], "%lf", &peak);
        case 3:
            sscanf(argv[2], "%lf", &freq);
        case 2:
            sscanf(argv[1], "%lf", &amp);
        default:
            break;
    }
    while (t<dur) {
        t += 1./44100;
        v  = (int16_t) ( y(t*pitch, amp, freq, peak, exp, min, dec)  
                * (2<<12) );
        putchar(p[0]);putchar(p[1]);
        putchar(p[0]);putchar(p[1]);
    }
    return 0;
}
