#ifndef LABSTRUCT_H
#define LABSTRUCT_H

#include <dot.h>

class Lab {
public:
    int m_n;
    int m_m;
    dot*** m_lab;
    bool** m_used;

public:
    Lab(int n, int m) ;
    void gen1(int i, int j);

};

//Lab lab(n, m, 1);
#endif // LABSTRUCT_H
