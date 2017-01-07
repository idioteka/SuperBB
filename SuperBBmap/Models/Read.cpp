//
//  Read.cpp
//  SuperBBmap
//
//  Created by Josip Maric on 13/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#include "Read.hpp"

string Read::reverseComplement() {
    string complement;
    for(long i = content.size() - 1; i >= 0; i--) {
        if(toupper(content[i]) == 'A') {
            complement.push_back('T');
        }
        else if(toupper(content[i]) == 'C') {
            complement.push_back('G');
        }
        else if(toupper(content[i]) == 'G') {
            complement.push_back('C');
        }
        else {
            complement.push_back('A');
        }
    }
    return complement;
}

vector<long> Read::makeKeyOffsites() {
    vector<long> keyOffsites;
    Config* config = Config::instance();
    
    long desiredKeysNumber = getDesiredKeyNumber();
    
    double interval = (content.size() - config->keylen) / (double) (max(desiredKeysNumber - 1, (long)1));
    double readPosition = 0;
    
    for(long i=0, j = 0; i < desiredKeysNumber; i++){
        if(((unsigned long) round(readPosition+interval)) > content.size()) {
            break;
        }
        keyOffsites.push_back(j);
        readPosition += interval;
        j = min(((long) content.size() - config->keylen), (max(j+1, (long) round(readPosition))));
    }
    return keyOffsites;
}

vector<int> Read::createReadKeys() {
    vector<int> keys;
    vector<long> keyIndexes = makeKeyOffsites();
    for(unsigned long i = 0; i < keyIndexes.size(); i++) {
        long keyIndex = keyIndexes[i];
        long keylen = Config::instance()->keylen;
        int key = keyFromKmer(&content, keyIndex, keyIndex+keylen);
        keys.push_back(key);
    }
    return  keys;
}

long Read::getDesiredKeyNumber() {
    Config* config = Config::instance();
    long keylen = config->keylen;
    long readlen = content.size();
    long slots = readlen - keylen +1;

    double maxKeyDensity = (( config->desiredKeysNumber * keylen ) / (double) readlen);
    maxKeyDensity = max(config->minKeyDensity, maxKeyDensity);
    maxKeyDensity = min(config->maxKeyDensity, maxKeyDensity);
    long desiredKeyNumber = (long) ceil(( readlen * maxKeyDensity) / keylen);
    desiredKeyNumber = max(config->minDesiredKeysNumber, desiredKeyNumber);
    desiredKeyNumber = min(slots, desiredKeyNumber);
    return desiredKeyNumber;
}

vector<long> Read::reverseComplementKeyOffsites() {
    long readlen = content.size();
    long keylen = Config::instance()->keylen;
    vector<long> keyOffsites = makeKeyOffsites();
    vector<long> reversedKeyOffsites;
    for (long i = keyOffsites.size() - 1; i >= 0; i--) {
        long keyOffsite = keyOffsites[i];
        long reversedKeyOffsite = readlen - (keyOffsite + keylen);
        reversedKeyOffsites.push_back(reversedKeyOffsite);
    }
    return reversedKeyOffsites;
}

vector<int> Read::reverseComplementKeys() {
    long keylen = Config::instance()->keylen;
    vector<int> reversedKeys;
    vector<int> keys = createReadKeys();
    
    for (long i = keys.size() - 1; i >= 0; i--) {
        int key = keys[i];
        int reversedKey = reverseComplementBinary(key, keylen);
        reversedKeys.push_back(reversedKey);
    }
    
    return reversedKeys;
}

