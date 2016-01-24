//
//  Config.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 13/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#ifndef Config_hpp
#define Config_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>
#include <pthread.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Class containing config data of current running instance of program
class Config {
public:
    static Config* instance();
    // length of key
    long keylen;
    // id of genome index
    string indexId;
    // root directory path where input and output data is stored
    string rootDirPath;
    // directory where input data is stored
    string inRootDir;
    // directory where output data is stored
    string outRootDir;
    
    long desiredKeysNumber;
    long minDesiredKeysNumber;
    double minKeyDensity;
    double maxKeyDensity;
private:
    Config();
    Config(Config const&);
    void operator=(Config const&);
    static Config* pInstance;
};

#endif /* Config_hpp */
