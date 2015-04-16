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

        void init(double *nominator, size_t nominatorOrder, double *denominator, size_t denominatorOrder) {
            nominator_ = (double*) std::calloc(history_.length()+1, sizeof(double));
            denominator_ = (double*) std::calloc(history_.length()+1, sizeof(double));
            if (nominator == nullptr || denominator == nullptr) throw Exception("Cannot allocate memory, function: TransferFunction::TransferFunction(double*, size_t, double*, size_t)");
            std::memcpy(&(nominator_[nominatorOrder < denominatorOrder ? denominatorOrder-nominatorOrder : 0]),nominator,nominatorOrder*sizeof(double));
            std::memcpy(&(denominator_[denominatorOrder < nominatorOrder ? nominatorOrder-denominatorOrder : 0]),denominator,denominatorOrder*sizeof(double));
            for (size_t i = 0; i < history_.length() + 1; ++i) {
                nominator_[i] /= denominator[0];
                denominator_[i] /= denominator[0];
            }
        }

    public:

        class Exception : public std::exception {
            char const *info;
        public:
            explicit Exception(char const *info) : info(info) {}
            virtual char const *what() const throw() { return info; }
        };

        DirectForm_II(double *nominator, size_t nominatorOrder, double *denominator, size_t denominatorOrder):
                history_((denominatorOrder-1 < nominatorOrder) ? nominatorOrder : denominatorOrder-1,0.0) {
            init(nominator, nominatorOrder, denominator, denominatorOrder);
        }
        ~DirectForm_II() {
            if (nominator_ != nullptr) free(nominator_);
            if (denominator_ != nullptr) free(denominator_);
        }

        double operator()(double actualValue) {
            double n = 0.0;

            for (size_t i = 1, j = 0; j < history_.length(); ++i, ++j) {
                actualValue -= denominator_[i] * history_(j);
                n += nominator_[i] * history_(j);
            }

            history_.push(actualValue);

            return actualValue * nominator_[0] + n;
        }

    };

}

#endif //DISCRETELIB_DIRECTFORM_II_H
