#ifndef LABSTRUCT_H
#define LABSTRUCT_H

#include <dot.h>
#include <QWidget>
#include <windows.h>
#include <queue>
#include <QQueue>

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
    QQueue <int*> draw_queue;
public:
    Lab(int n, int m) ;
    virtual ~Lab();
    void gen1(int i, int j);
    void gen3();
    void mySleep();
    void push_to_draw_queue(int i, int j, int k);
    bool find1(int starti, int startj,
               int finishi, int finishj, int res = 0);
    bool find2(int starti, int startj,
               int finishi, int finishj);
    bool find3(int starti, int startj,
               int finishi, int finishj);
    void operator= (Lab* Lab);
};

//Lab lab(n, m, 1);
#endif // LABSTRUCT_H
