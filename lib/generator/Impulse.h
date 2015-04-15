//
// Created by artur on 15/04/15.
//

#ifndef DISCRETELIB_IMPULSE_H
#define DISCRETELIB_IMPULSE_H




namespace geox {

    class Impulse {

        double impulseTime_;
        double impulseValue_;

    public:

        Impulse(): impulseTime_(0.0), impulseValue_(1.0) {}
        Impulse(double const &impulseTime): impulseTime_(impulseTime), impulseValue_(1.0) {}
        Impulse(double const &impulseTime, double const &impulseValue): impulseTime_(impulseTime), impulseValue_(impulseValue) {}
        ~Impulse() {}

        inline double operator()(double const &actualTime) const { return (actualTime != impulseTime_) ? 0.0 : impulseValue_; }

    };

}

#endif //DISCRETELIB_IMPULSE_H
