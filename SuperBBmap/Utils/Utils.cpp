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
    long keylen = Config::instance()->keylen;
    return pow(2, 2*keylen);
}

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

string matchStringToCigarString(string matchString) {
    char current = matchString[0];
    int number = 1;
    string compressed;
    for(unsigned int i = 1; i < matchString.size(); i++) {
        if(current == matchString[i]) {
            number++;
        }
        else if((current == 'm' && matchString[i] == 's') || (current == 's' && matchString[i] == 'm')) {
            number++;
        }
        else {
            if(current == 's') current = 'm';
            compressed += to_string(number);
            compressed.push_back(current);
            number = 1;
            current = matchString[i];
        }
    }
    if(current == 's') current = 'm';
    compressed += to_string(number);
    compressed.push_back(current);
    return compressed;
}
