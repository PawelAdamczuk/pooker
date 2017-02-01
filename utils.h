//
// Created by Janusz Grzesik on 01.02.2017.
//

#ifndef POOKER_CONSTANTS_H
#define POOKER_CONSTANTS_H

#include <vector>

using namespace std;

enum RoundPhase {
    preflop = 0, flop, turn, river
};

template<class T>
class CyclicIterator{
private:
    vector<T> vec;
    typename vector<T>::iterator it;

public:
    CyclicIterator(vector<T> vec) : vec(vec), it(vec.begin()) {}

    CyclicIterator& operator++() {
        it++;
        if (isEnd()) {
            it = vec.begin();
        }
        return *this;
    }

    CyclicIterator& operator--() {
        it++;
        if (isEnd()) {
            it = vec.begin();
        }
        return *this;
    }

    bool isEnd() {
        return it == vec.end();
    }

    T &operator*() {
        return *it;
    }
};

#endif //POOKER_CONSTANTS_H
