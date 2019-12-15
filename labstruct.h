#ifndef LABSTRUCT_H
#define LABSTRUCT_H

#include <dot.h>
#include <QWidget>

class QLabel;
class QPixmap;

class Lab {
public:
    int m_n;
    int m_m;
    int m_time;
    int m_res = 0;
    dot*** m_lab;
    bool** m_used;
public:
    Lab(int n, int m) ;
    ~Lab(){
        for (int i = 0; i < m_n; i++)
            for (int j = 0; j < m_m; j++)
                delete m_lab[i][j];
        for (int i = 0; i < m_n; i++)
            delete[] m_lab[i];
        delete[] m_lab;
        for (int i = 0; i < m_n; i++)
            delete[] m_used[i];
        delete[] m_used;
    }
    void gen1(int i, int j);
    void gen2();
    void gen3();
    bool find1(QLabel* lab[][100], int starti, int startj, int finishi, int finishj, int res = 0);
    bool find2(QLabel* lab[][100], int starti, int startj, int finishi, int finishj);
    bool find3(QLabel* lab[][100], int starti, int startj, int finishi, int finishj, int res = 0);

};

//Lab lab(n, m, 1);
#endif // LABSTRUCT_H
