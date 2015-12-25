//
//  Config.cpp
//  SuperBBmap
//
//  Created by Josip Maric on 13/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#include "Config.hpp"

Config* Config::pInstance = NULL;

Config* Config::instance() {
    if (!pInstance) {
        pInstance = new Config();
    }
    return pInstance;
}

Config::Config() {
    keylen = 13;
    indexId = "0";
    rootDirPath = "/Users/josipmaric/Projects/SuperBB/SuperBBmap/";
    inRootDir = rootDirPath + "InputTestsStorage/";
    outRootDir = rootDirPath + "OutputTestStorage/";
}