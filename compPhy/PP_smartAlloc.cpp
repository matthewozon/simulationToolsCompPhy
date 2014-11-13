#include <PP_smartAlloc.h>

PP_smartAlloc::PP_smartAlloc()
{
}


double * PP_smartAlloc::allocateDouble(unsigned long N)
{
    return new double[N];
}

void PP_smartAlloc::dealocate(double* X)
{
    if(X!=NULL)
    {
        delete X;
    }
    X = NULL;
}

double ** PP_smartAlloc::allocateDouble(unsigned long _Nt, unsigned long _Nz)
{
    double** _M = new double*[_Nt];
    if(_M!=NULL)
    {
        unsigned long I = _Nt+1;
        for(unsigned long i=0 ; i<_Nt ; i++)
        {
            _M[i] = new double[_Nz];
            if(_M[i]==NULL)
            {
                I=i;
                i=_Nt;
            }
        }
        if(I!=(_Nt+1))
        {
            for(unsigned long i=0 ; i<I ; i++)
            {
                delete _M[i];
            }
            delete _M;
            _M = NULL;
        }
    }
    return _M;
}

void PP_smartAlloc::dealocate(double** X, unsigned long N)
{
    if(X!=NULL)
    {
        for(unsigned long i=0 ; i<N ; i++)
        {
            if(X[i]!=NULL) delete X[i];
        }
        delete X;
        X = NULL;
    }
    return;
}
