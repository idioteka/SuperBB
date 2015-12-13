//
//  IOManager.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 12/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#ifndef IOManager_hpp
#define IOManager_hpp

#include "Utils.hpp"
#include "GenomeIndex.hpp"

using namespace std;

class IOManager {
public:
    static string* extractGenomeFromFile(string genomeFile);
    static void writeIndexToFile(GenomeIndex* index);
private:
    static void writeLongArray(long* array, long length, string location, string name);
};

#endif /* IOManager_hpp */
