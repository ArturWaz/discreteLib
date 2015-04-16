//
// Created by artur on 16/04/15.
//

#ifndef DISCRETELIB_DIRECTFORM_II_H
#define DISCRETELIB_DIRECTFORM_II_H


#include <cstdlib>
#include <cstring>
#include "../containers/Buffer.h"


namespace geox {

    class DirectForm_II {

        double *nominator_;
        double *denominator_;

        geox::Buffer<double> history_;

    public:

        class Exception : public std::exception {
            char const *info;
        public:
            explicit Exception(char const *info) : info(info) {}
            virtual char const *what() const throw() { return info; }
        };

        DirectForm_II(double *nominator, size_t nominatorOrder, double *denominator, size_t denominatorOrder):
                history_((denominatorOrder-1 < nominatorOrder) ? nominatorOrder : denominatorOrder-1,0.0) {
            nominator_ = (double*) std::calloc(history_.length(), sizeof(double));
            denominator_ = (double*) std::calloc(history_.length(), sizeof(double));
            if (nominator == nullptr || denominator == nullptr) throw Exception("Cannot allocate memory, function: TransferFunction::TransferFunction(double*, size_t, double*, size_t)");
            for (size_t i = 0; i < nominatorOrder; ++i) nominator_[i] = nominator[i]/denominator[0];
            for (size_t i = 0; i < denominatorOrder-1; ++i) denominator_[i] = denominator[i+1]/denominator[0];
        }
        ~DirectForm_II() {
            if (nominator_ != nullptr) free(nominator_);
            if (denominator_ != nullptr) free(denominator_);
        }

        double operator()(double const &actualValue) {
            double outValue = actualValue;

            for (int i = 0; i < history_.length(); ++i) outValue -= denominator_[i] * history_(i);

            double tmp = outValue;

            outValue *= nominator_[0];
            for (int i = 0; i < history_.length(); ++i) outValue += nominator_[i+1] * history_(i);

            history_.push(tmp);

            return outValue;
        }

    };

}

#endif //DISCRETELIB_DIRECTFORM_II_H
