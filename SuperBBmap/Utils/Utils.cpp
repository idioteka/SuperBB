//
//  Utils.cpp
//  SuperBBmap
//
//  Created by Josip Maric on 13/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#include "Utils.hpp"

void print(string content) {
    cout << "[SuperBB]: " << content << endl;
}

void debugPrint(string content) {
    if (debug) {
        print(content);
    }
}

int baseToCode(char base) {
    char lowerBase = tolower(base);
    
    switch (lowerBase) {
        case 'a':
            return 0;
        case 'c':
            return 1;
        case 'g':
            return 2;
        case 't':
            return 3;
        default:
            return -1;
    }
}

int keyspace() {
    int keylen = Config::instance()->keylen;
    return pow(2, 2*keylen);
}