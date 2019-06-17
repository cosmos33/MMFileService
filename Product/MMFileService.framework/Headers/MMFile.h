//
// Created by chenwangwang on 2018/9/18.
//

#ifndef MMLOG_MMFILE_H
#define MMLOG_MMFILE_H

#include <string>
#include "ILogManager.h"

namespace mmslog {

    ILogManager* getLogManager(const std::string &name);

}



#endif //MMLOG_MMFILE_H
