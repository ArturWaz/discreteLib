//
// Created by artur on 13/04/15.
//

#ifndef DIGITALLIBRARY_IIR_DIRECTFORM_II_H
#define DIGITALLIBRARY_IIR_DIRECTFORM_II_H




namespace geox {

    template<class T, unsigned int NUMBER_OF_SECTIONS>
    class IIR_DirectFormII {

        unsigned int numberOfSections;
        Buffer <T> *buffer;

//        T **numerator;
//        T **denominator;

    public:

        IIR_DirectFormII() : numberOfSections(NUMBER_OF_SECTIONS) {
            buffer = new Buffer <T>[numberOfSections](2);
        }

        ~IIR_DirectFormII() { delete[]buffer; }

        T filterMatlabCoeffs(T const &actualValue) {
            T out = actualValue;

            for (int i = 0; i < numberOfSections; ++i) {

                T actual =
                        filterFromMatlab2::NUM[i * 2][0] * out - filterFromMatlab2::DEN[i * 2 + 1][1] * buffer[i](0) -
                        filterFromMatlab2::DEN[i * 2 + 1][2] * buffer[i](1);
                out = filterFromMatlab2::NUM[i * 2 + 1][0] * actual +
                      filterFromMatlab2::NUM[i * 2 + 1][1] * buffer[i](0) +
                      filterFromMatlab2::NUM[i * 2 + 1][2] * buffer[i](1);

                buffer[i].push(actual);
            }

            return out;
        }

    };

}

#endif //DIGITALLIBRARY_IIR_DIRECTFORM_II_H
