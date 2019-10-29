//
// Created by chenwangwang on 2018/8/23.
//

#ifndef MMLOG_MMLOGBASE_H
#define MMLOG_MMLOGBASE_H

#include <string>
#include <list>
#include <map>
#include "ILogManager.h"

namespace mmslog {

    void registerLogManager(const std::string &name, ILogManager *logManager);

}

#endif //MMLOG_MMLOGBASE_H
