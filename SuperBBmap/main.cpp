//
//  main.cpp
//  SuperBBmap
//
//  Created by Josip Maric on 30/11/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#include "IOManager.hpp"
#include "GenomeIndexer.hpp"

int main(int argc, const char * argv[]) {
    
    string genomeFilename = Config::instance()->inRootDir + "test_genome.fa";
    string* wholeGenome = IOManager::extractGenomeFromFile(genomeFilename);
    print(*wholeGenome);
    
    GenomeIndex* index = GenomeIndexer::createIndex(wholeGenome);
    
    delete wholeGenome;
    
    print(to_string(index->sitesLength));
    
    IOManager::writeIndexToFile(index);
    
    delete index;
    
    return 0;
}
