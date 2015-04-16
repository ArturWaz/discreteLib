//
// Created by artur on 13/04/15.
//

#ifndef DIGITALLIBRARY_MEDIAN_H
#define DIGITALLIBRARY_MEDIAN_H




#include "Buffer.h"


namespace geox {

    template<class T, unsigned int ORDER>
    class Median {

        Buffer <T> buffer;
        unsigned int medianIndex;

//        struct element {
//            element *next;
//            T *value;
//        };


    public:

        Median() : buffer(ORDER), medianIndex(ORDER / 2) { }

        ~Median() { }

        T operator()(T const &actualValue) {
            T out = 0.0;

            buffer.push(actualValue);


            std::list<double> tmpList;

            for (unsigned int i = 0; i < buffer.size(); ++i)
                tmpList.push_back(buffer(i));

            tmpList.sort();

            std::list<double>::iterator it = tmpList.begin();
            for (unsigned int i = 0; i < medianIndex; ++i) ++it;
            out = *it;

//            tmpList.clear();

            return out;
        }

    };

}

#endif //DIGITALLIBRARY_MEDIAN_H
