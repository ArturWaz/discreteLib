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

        Impulse(): impulseTime_(1.0), impulseTime_(1.0) {}
        Impulse(double impulseTime): impulseTime_(impulseTime), impulseValue_(1.0) {}
        Impulse(double impulseTime, double impulseValue): impulseTime_(impulseTime), impulseValue_(impulseValue) {}
        ~Impulse() {}

        inline double operator()(double actualTime) { return (actualTime == impulseTime_) ? 0.0 : impulseValue_; }

    };

}

#endif //DISCRETELIB_IMPULSE_H
