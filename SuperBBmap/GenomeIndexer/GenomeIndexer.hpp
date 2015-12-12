//
//  GenomeIndexer.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 12/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#ifndef GenomeIndexer_hpp
#define GenomeIndexer_hpp

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GenomeIndexer {
public:
    static string* extractGenomeFromFile(string genome_file);
};

#endif /* GenomeIndexer_hpp */
