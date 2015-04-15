//
// Created by artur on 15/04/15.
//

#ifndef DISCRETELIB_TRANSFERFUNCTION_H
#define DISCRETELIB_TRANSFERFUNCTION_H


#include <cstdlib>
#include <cstring>
#include "../../containers/Buffer.h"


namespace geox {

    class TransferFunction { // ZOH (zero-order hold)

        double *nominator_;
        double *denominator_;

        size_t nominatorOrder_;
        size_t denominatorOrder_;

        geox::Buffer<double> input_;
        geox::Buffer<double> output_;

    public:

        class Exception : public std::exception {
            char const *info;
        public:
            explicit Exception(char const *info) : info(info) {}
            virtual char const *what() const throw() { return info; }
        };

        TransferFunction(double *nominator, size_t nominatorOrder, double *denominator, size_t denominatorOrder):
                nominatorOrder_(nominatorOrder), denominatorOrder_(denominatorOrder), input_(nominatorOrder,0.0), output_(denominatorOrder,0.0) {
            nominator_ = (double*)std::malloc(nominatorOrder*sizeof(double));
            denominator_ = (double*)std::malloc(denominatorOrder*sizeof(double));
            if (nominator == nullptr ||denominator == nullptr) throw Exception("Cannot allocate memory, function: TransferFunction::TransferFunction(double*, size_t, double*, size_t)");
            std::memcpy(nominator_, nominator, nominatorOrder * sizeof(double));
            std::memcpy(denominator_, denominator, denominatorOrder * sizeof(double));
        }
        ~TransferFunction() {
            if (nominator_ != nullptr) free(nominator_);
            if (denominator_ != nullptr) free(denominator_);
        }

        double operator()(double const &actualValue) {
            double outValue = 0.0;

            input_.push(actualValue);

            for (size_t i = 0; i < nominatorOrder_; ++i)
                outValue += nominator_[i] * input_(i);
            for (int i = 0; i < denominatorOrder_; ++i)
                outValue -= denominator_[i] * output_(i);

            output_.push(outValue);

            return outValue;
        }

    };

}

#endif //DISCRETELIB_TRANSFERFUNCTION_H
