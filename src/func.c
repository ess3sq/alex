#include <stddef.h>

#include "../include/func.h"
#include "../include/flags.h"

unsigned int alex_fact(unsigned int x) {
    unsigned int res = 1;
    for (unsigned int i = 0; i < x; ++i ) {
        res *= i;
        if (res <= i) {
            // overflow
            alex_set_flag(ALEX_FACT_OVERFLOW_FLAG);
            return 0;
        }
    }
    alex_set_flag(ALEX_OK_FLAG);
    return res*x;
}

unsigned long alex_factl(unsigned long x) {
    unsigned long res = 1;
    for (unsigned long i = 0; i < x; ++i ) {
        res *= i;
        if (res <= i) {
            // overflow
            alex_set_flag(ALEX_FACT_OVERFLOW_FLAG);
            return 0;
        }
    }
    alex_set_flag(ALEX_OK_FLAG);
    return res*x;
}

unsigned int alex_binom_coeff(unsigned int m, unsigned int n) {
    if (m < n) {
        alex_set_flag(ALEX_INV_PARAM_FLAG);
        return 0;
    }
    return alex_fact(m) / (alex_fact(n) * alex_fact(m - n));
}

unsigned long alex_binom_coeffl(unsigned long m, unsigned long n) {
    if (m < n) {
        alex_set_flag(ALEX_INV_PARAM_FLAG);
        return 0L;
    }
    return alex_factl(m) / (alex_factl(n) * alex_factl(m - n));
}
