//
// Created by artur on 13/04/15.
//

#ifndef DIGITALLIBRARY_FIR_DIRECTFORM_I_H
#define DIGITALLIBRARY_FIR_DIRECTFORM_I_H






namespace geox {

    template<class T, unsigned int ORDER>
    class FIR_DirectFormI {

        Buffer <T> buffer;
        unsigned int order;

//        T *numerator;

    public:

        FIR_DirectFormI() : buffer(ORDER), order(ORDER) { }

        ~FIR_DirectFormI() { }

        T filterMatlabCoeffs(T const &actualValue) {
            T out = 0.0;

            buffer.push(actualValue);

            for (unsigned int i = 0; i < order; ++i)
                out += buffer(i) * FIRfilter1::B[i];

            return out;
        }

    };

}

#endif //DIGITALLIBRARY_FIR_DIRECTFORM_I_H
