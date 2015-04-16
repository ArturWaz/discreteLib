//
// Created by artur on 15/04/15.
//

#ifndef DISCRETELIB_DIRECTFORM_I_H
#define DISCRETELIB_DIRECTFORM_I_H


#include <cstdlib>
#include <cstring>
#include "../containers/Buffer.h"


namespace geox {

    class DirectForm_I {

        double *nominator_;
        double *denominator_;

        size_t nominatorOrder_;
        size_t denominatorOrder_;

        geox::Buffer<double> input_;
        geox::Buffer<double> output_;

        double actualValue_;

    public:

        class Exception : public std::exception {
            char const *info;
        public:
            explicit Exception(char const *info) : info(info) {}
            virtual char const *what() const throw() { return info; }
        };

        DirectForm_I(double *nominator, size_t nominatorOrder, double *denominator, size_t denominatorOrder):
                nominatorOrder_(nominatorOrder), denominatorOrder_(denominatorOrder), input_(nominatorOrder,0.0), output_(denominatorOrder-1,0.0) {
            nominator_ = (double*)std::malloc(nominatorOrder*sizeof(double));
            denominator_ = (double*)std::malloc((denominatorOrder-1)*sizeof(double));
            if (nominator == nullptr || denominator == nullptr) throw Exception("Cannot allocate memory, function: TransferFunction::TransferFunction(double*, size_t, double*, size_t)");
            for (size_t i = 0; i < nominatorOrder; ++i) nominator_[i] = nominator[i]/denominator[0];
            for (size_t i = 0; i < denominatorOrder-1; ++i) denominator_[i] = denominator[i+1]/denominator[0];
        }
        ~DirectForm_I() {
            if (nominator_ != nullptr) free(nominator_);
            if (denominator_ != nullptr) free(denominator_);
        }

        double operator()(double const &actualValue) {
            actualValue_ = 0.0;

            for (size_t i = 0; i < nominatorOrder_; ++i)
                actualValue_ += nominator_[i] * input_(i);
            for (size_t i = 0; i < denominatorOrder_-1; ++i)
                actualValue_ -= denominator_[i] * output_(i);

            input_.push(actualValue);
            output_.push(actualValue_);

            return actualValue_;
        }

        inline double actualValue() const { return actualValue_; }

    };

}

#endif //DISCRETELIB_TRANSFERFUNCTION_H
