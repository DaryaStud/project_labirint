#ifndef LABSTRUCT_H
#define LABSTRUCT_H

#include <dot.h>
#include <QWidget>
#include <windows.h>
#include <queue>

class QLabel;
class QPixmap;

class Lab {
public:
    int m_n;
    int m_m;
    int m_time;
    int m_res = 0;
    dot*** m_lab;
    int** m_used;
public:
    Lab(int n, int m) ;
    virtual ~Lab();
    void gen1(int i, int j);
    void gen3();
    bool find1(QLabel* lab[][100], int starti, int startj, int finishi, int finishj, int res = 0);
    bool find2(QLabel* lab[][100], int starti, int startj, int finishi, int finishj);
    bool find3(QLabel* lab[][100], int starti, int startj, int finishi, int finishj, int res = 0);
    void operator= (Lab* Lab);
};

//Lab lab(n, m, 1);
#endif // LABSTRUCT_H
