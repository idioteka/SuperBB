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

using namespace std;

class IOManager {
public:
    static string* extractGenomeFromFile(string genome_file);
};

#endif /* IOManager_hpp */
