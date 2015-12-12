//
//  IOManager.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 12/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#ifndef IOManager_hpp
#define IOManager_hpp

#include <stdio.h>
#include <string>
#include <iostream>

#include "Utils.hpp"

using namespace std;

class IOManager {
public:
    static string* extractGenomeFromFile(string genomeFile);
};

#endif /* IOManager_hpp */
