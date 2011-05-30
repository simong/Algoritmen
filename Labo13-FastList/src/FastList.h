//
//  FastList.h
//  Labo13-FastList
//
//  Created by Simon on 29/05/2011.
//  Copyright 2011 CARET. All rights reserved.
//

#ifndef FASTLIST_H_
#define FASTLIST_H_

#include<vector>

typedef unsigned int uint;

template<typename T>
struct Hasher {
    virtual uint operator()(T x)=0;
};


template<typename T>
class FastList {
  
public:
    FastList(Hasher<T>& hasher_, uint n);
    
    
    void add(T x);
    bool contains(T x);
    
    typedef typename std::vector<T>::const_iterator const_iterator;
    
    const_iterator begin() {
        //return data.begin();
    }
    const_iterator end() {
        //return data.end();
    }
    
private:
    T* data;
    uint size;
    uint *hashed;
    uint n;
    Hasher<T>& hasher;
    
    
};

template<typename T>
FastList<T>::FastList(Hasher<T>& hasher_, uint n_) : hasher(hasher_), n(n_), size(0) {
    hashed = new uint[n];
    data = new T[n];
}

template<typename T>
void FastList<T>::add(T x) {
    uint pos = hasher(x) % n;
    data[size] = x;
    hashed[pos] = size;
    size++;
}

template<typename T>
bool FastList<T>::contains(T x) {
    uint pos = hasher(x) % n;
    uint p = hashed[pos];
    return (data[p] == x);
}

#endif
