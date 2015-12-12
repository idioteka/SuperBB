//
//  Utils.cpp
//  SuperBBmap
//
//  Created by Josip Maric on 13/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#include "Utils.hpp"

static void print(string content) {
    cout << "[SuperBB]: " << endl;
}

static void debugPrint(string content) {
    if (debug) {
        print(content);
    }
}
