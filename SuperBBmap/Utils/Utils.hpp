//
//  Utils.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 13/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>

#include "Config.hpp"

using namespace std;

static bool debug = true;

void print(string content);
void debugPrint(string content);

int baseToCode(char base);

int keyspace();

#endif /* Utils_hpp */
