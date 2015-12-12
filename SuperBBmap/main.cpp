//
//  main.cpp
//  SuperBBmap
//
//  Created by Josip Maric on 30/11/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#include "IOManager.hpp"

int main(int argc, const char * argv[]) {
    
    std::string genome_filename = "/Users/josipmaric/Projects/SuperBB/SuperBBmap/InputTestsStorage/test_genome.fa";
    std::string* whole_genome = IOManager::extractGenomeFromFile(genome_filename);
    std::cout << *whole_genome << std::endl;
    
    return 0;
}
