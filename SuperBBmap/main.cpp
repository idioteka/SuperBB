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
    
    string genomeFilename = "/Users/josipmaric/Projects/SuperBB/SuperBBmap/InputTestsStorage/test_genome.fa";
    string* wholeGenome = IOManager::extractGenomeFromFile(genomeFilename);
    print(*wholeGenome);
    
    GenomeIndex* index = GenomeIndexer::createIndex(wholeGenome);
    
    print(to_string(index->sitesLength));
    
    return 0;
}
