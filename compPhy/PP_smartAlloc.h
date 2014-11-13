#ifndef PP_SMARTALLOC_H
#define PP_SMARTALLOC_H

#include <stdlib.h>

class PP_smartAlloc
{
public:
    PP_smartAlloc();
    double * allocateDouble(unsigned long N);
    void dealocate(double* X);

    double ** allocateDouble(unsigned long _Nt, unsigned long _Nz);
    void dealocate(double** X, unsigned long _Nt);
};

#endif // PP_SMARTALLOC_H
