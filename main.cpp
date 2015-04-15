#include <iostream>


#include "lib/discrete/object/TransferFunction.h"





using namespace std;

int main() {


    geox::TransferFunction tf({0.0, 0.3, 0.4});

    cout << tf.nominator_[0] << " " << tf.nominator_[1] << " " << tf.nominator_[2];

    return 0;
}