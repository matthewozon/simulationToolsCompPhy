#ifndef PP_EL_HAHN_H
#define PP_EL_HAHN_H

#include "PP_sigRMN.h"


class PP_el_hahn : public PP_sigRMN
{
public:
    PP_el_hahn();

    //simulation of the monochrmatic momentum during a two pi/2-pulse sequence with a constant phase shift induced by the field inhomogeneities
    void monochromatic(double mx0, double my0, double mz0, double dw, bool rotFrame=true);
    void biChromatic(double mx0, double my0, double mz0, double dw, bool rotFrame=true);
    void multiChrome(double mx0, double my0, double mz0, int N, bool rotFrame=true);

    void monochromaticDiffusion(double mx0, double my0, double mz0, double dw, bool rotFrame=true);
    void multiChromeDiffusion(double mx0, double my0, double mz0, int N, bool rotFrame=true);

};

#endif // PP_EL_HAHN_H
