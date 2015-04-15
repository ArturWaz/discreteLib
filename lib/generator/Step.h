//
// Created by artur on 15/04/15.
//

#ifndef DISCRETELIB_STEP_H
#define DISCRETELIB_STEP_H




namespace geox {

    class Step {

        double stepTime_;
        double stepValue_;

    public:

        Step(): stepTime_(1.0), stepValue_(1.0) {}
        Step(double const &stepTime): stepTime_(stepTime), stepValue_(1.0) {}
        Step(double const &stepTime, double const &stepValue): stepTime_(stepTime), stepValue_(stepValue) {}
        ~Step() {}

        inline double operator()(double const &actualTime) const { return (actualTime < stepTime_) ? 0.0 : stepValue_; }

    };

}

#endif //DISCRETELIB_STEP_H
