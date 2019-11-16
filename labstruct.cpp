#include <QtWidgets>
#include "labstruct.h"

Lab::Lab(int n, int m) {
    m_n = n;
    m_m = m;
    m_lab = new dot** [n];
    for (int i = 0; i < n; i++)
        m_lab[i] = new dot*[m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            m_lab[i][j] = new dot;
    m_used = new bool*[n];
    for (int i = 0; i < n; i++)
        m_used[i] = new bool[m];
}

void Lab::gen1(int i, int j) {
    m_used[i][j] = 1;
    for (int k = 0; k != -1;) {
        int path[4];
        k = 0;
        if ((j < m_m - 1) && (m_used[i][j + 1] == 0))
            path[k++] = 1;

        if ((i < m_n - 1) && (m_used[i + 1][j] == 0))
            path[k++] = 2;

        if ((j > 0) && (m_used[i][j - 1] == 0))
            path[k++] = 3;

        if ((i > 0) && (m_used[i - 1][j] == 0))
            path[k++] = 4;
        if (k==0) {
            k=-1;
            continue;
        }

        k = rand() % k;
        if (path[k] == 1) {
            m_lab[i][j]->go_right();
            m_lab[i][j + 1]->go_left();
            //fout<<i<<j<<" --- "<<i<<j+1<<endl;
            gen1(i, j + 1);
        } else if (path[k] == 2) {
            m_lab[i][j]->go_dawn();
            m_lab[i + 1][j]->go_top();
            //fout<<i<<j<<" --- "<<i+1<<j<<endl;
            gen1(i + 1, j);
        } else if (path[k] == 3) {
            m_lab[i][j]->go_left();
            m_lab[i][j - 1]->go_right();
            //fout<<i<<j<<" --- "<<i<<j-1<<endl;
            gen1(i, j - 1);
        } else if (path[k] == 4) {
            m_lab[i][j]->go_top();
            m_lab[i - 1][j]->go_dawn();
            //fout<<i<<j<<" --- "<<i-1<<j<<endl;
            gen1(i - 1, j);
        }
    }
}


