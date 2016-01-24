//
//  Read.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 13/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#ifndef Read_hpp
#define Read_hpp

#include "Utils.hpp"
#include "CorrectAlignment.hpp"

// represents one read with possible correct alignment
class Read {
public:
    int id;
    string content;
    string name;
    CorrectAlignment* correctAlignment;
    Read(int _id, string _content, string _name, CorrectAlignment* _correctAlignment) {
        id = _id;
        content = _content;
        name = _name;
        correctAlignment = _correctAlignment;
    }
    ~Read() {
        delete correctAlignment;
    }
    string reverseComplement();
    vector<int> readKeys();
private:
    vector<long> makeKeyIndexes();
    long getDesiredKeyNumber();
};

#endif /* Read_hpp */
