//
//  MSingleton.hpp
//  ProxyPlayer
//
//  Created by guowei on 21/08/2017.
//  Copyright © 2017 MOMO. All rights reserved.
//

#ifndef MM_SINGLETON_HPP
#define MM_SINGLETON_HPP

#include <stdio.h>
#include <pthread.h>

namespace mmslog {
    template<typename T>
    class MSingleton {
    public:
        static T *getInstance() {
            pthread_once(&sOnce, init);
            return sIntance;
        }

        // 下面两个方法是用来禁止拷贝的
        MSingleton(const MSingleton<T> &) = delete;

        MSingleton<T> &operator=(const MSingleton<T> &) = delete;

    private:

        MSingleton() {

        }

        ~MSingleton() {

        }

        static void init() {
            sIntance = new T();
        }

        static pthread_once_t sOnce;
        static T *sIntance;
    };

    template<typename T>
    pthread_once_t MSingleton<T>::sOnce = PTHREAD_ONCE_INIT;

    template<typename T>
    T *MSingleton<T>::sIntance = nullptr;
}
#endif /* MM_SINGLETON_HPP */
