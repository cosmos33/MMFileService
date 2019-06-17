//
// Created by chenwangwang on 2018/9/18.
//

#ifndef MMLOG_IMMLOGINFO_H
#define MMLOG_IMMLOGINFO_H

#include <string>
#include <list>

namespace mmslog {

    typedef struct MMFileInfo_t {
        std::list<std::string> heads;
        std::string body;
    } MMLogInfo;

}

#endif //MMLOG_IMMLOGINFO_H
