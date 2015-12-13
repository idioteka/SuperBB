//
//  GenomeIndex.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 13/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#ifndef GenomeIndex_hpp
#define GenomeIndex_hpp

#include "Utils.hpp"

using namespace std;

class GenomeIndex {
public:
    static const string sizesArrayName;
    static const string sitesArrayName;
    long* sizes;
    long sitesLength;
    long* sites;
    GenomeIndex(long* _sizes, long _sitesLength, long* _sites) {
        sizes = _sizes;
        sitesLength = _sitesLength;
        sites = _sites;
    }
    ~GenomeIndex() {
        delete sizes;
        delete sites;
    }
};

#endif /* GenomeIndex_hpp */
