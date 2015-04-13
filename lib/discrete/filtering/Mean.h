//
// Created by artur on 13/04/15.
//

#ifndef DIGITALLIBRARY_AVERAGE_H
#define DIGITALLIBRARY_AVERAGE_H



namespace geox {

    template<class T, unsigned int ORDER>
    class Mean {

        Buffer <T> buffer;

        T sum; // temporary average use to improve speed of calculations

    public:

        Average() : buffer(ORDER), sum(0) { }

        ~Average() { }

        T filter(T const &actualValue) {
            sum -= buffer(buffer.size() - 1);
            buffer.push(actualValue);
            sum += buffer(0);
            return sum / buffer.size();
        }

        inline T actual() const { return sum / buffer.size(); }

    };

}

#endif //DIGITALLIBRARY_AVERAGE_H
