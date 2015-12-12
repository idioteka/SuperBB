//
//  IOManager.cpp
//  SuperBBmap
//
//  Created by Josip Maric on 12/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#include "IOManager.hpp"

string* IOManager::extractGenomeFromFile(string genome_file) {
    
    string* whole_genome = new string();
    FILE *inGenome = fopen(genome_file.c_str(), "r");
    if (inGenome == NULL) {
        print("Reference file does not exist: " + genome_file);
        exit(-1);
    }
    char buff[256];
    
    while (fgets(buff, 255, inGenome)) {
        // ignore lines that start with genome desc, they start with '>'
        if (buff[0] != '>') {
            string tmp = buff;
            tmp.resize(tmp.size() - 1);  // remove endl
            *whole_genome += tmp;
        }
    }
    return whole_genome;
}
