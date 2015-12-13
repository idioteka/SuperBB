//
//  GenomeIndex.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 13/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#ifndef GenomeIndex_hpp
#define GenomeIndex_hpp

#include <stdio.h>
#include <string>
#include <iostream>

#include "Utils.hpp"

using namespace std;

class GenomeIndex {
public:
    long* sizes;
    long sitesLength;
    long* sites;
    GenomeIndex(long* _sizes, long _sitesLength, long* _sites) {
        sizes = _sizes;
        sitesLength = _sitesLength;
        sites = _sites;
    }
};

#endif /* GenomeIndex_hpp */
