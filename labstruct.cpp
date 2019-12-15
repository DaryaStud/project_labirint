#include <QtWidgets>
#include "labstruct.h"
#include <windows.h>
#include <queue>

using namespace std;

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
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            m_used[i][j] = 0;
}

void Lab::gen1(int i, int j) {
    //for (int i = 0; i < m_n; i++)
    //    for (int j = 0; j < m_m; j++)
    //        delete m_lab[i][j];

    //for (int i = 0; i < m_n; i++)
    //    for (int j = 0; j < m_m; j++)
    //        m_lab[i][j] = new dot;

    m_used[i][j] = 1;
    for (int k = 0; k != -1;) {
        int path[4];
        for (int p = 0; p<4; p++)
            path[p]=0;
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

void Lab::gen2(){
    //Алгоритм Эллера
    /*for (int i = 0; i < m_n; i++)
        for (int j = 0; j < m_m; j++)
            delete m_lab[i][j];

    for (int i = 0; i < m_n; i++)
        for (int j = 0; j < m_m; j++)
            m_lab[i][j] = new dot;

    int n = m_n;
    int m = m_m;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){

        }
    }*/
}

void Lab::gen3(){

}

bool Lab::find1(QLabel* lab[][100], int i, int j, int finishi, int finishj, int res) {
    Sleep(m_time);
    if (i == finishi && j == finishj){
        m_res = res;
        return 1;
    }
    else
    {
    if (res == 0){
        for (int i = 0; i < m_n; i++)
            for (int j = 0; j < m_m; j++)
                m_used[i][j] = 0;
        m_res = 0;
    }
    else{
        lab[(i+1)*2-1][(j+1)*2-1]->setStyleSheet("background-color: blue");
        lab[(i+1)*2-1][(j+1)*2-1]->repaint();
    }
    m_used[i][j] = 1;
    Sleep(m_time);
    if (m_lab[i][j]->get_dawn() && m_used[i+1][j] == 0 && m_res == 0){
        lab[(i+1)*2][(j+1)*2-1]->setStyleSheet("background-color: blue");
        lab[(i+1)*2][(j+1)*2-1]->repaint();
        if (find1(lab, i+1, j, finishi, finishj, res+1)){
            lab[(i+1)*2-1][(j+1)*2-1]->setStyleSheet("background-color: yellow");
            lab[(i+1)*2][(j+1)*2-1]->setStyleSheet("background-color: yellow");
            if (res == 0){
               lab[(i+1)*2-1][(j+1)*2-1]->setStyleSheet("background-color: red");
            }
            return 1;
        }
    }
    if (m_lab[i][j]->get_right() && m_used[i][j+1] == 0 && m_res == 0){
        lab[(i+1)*2-1][(j+1)*2]->setStyleSheet("background-color: blue");
        lab[(i+1)*2-1][(j+1)*2]->repaint();
        if (find1(lab, i, j+1, finishi, finishj, res+1)){
            lab[(i+1)*2-1][(j+1)*2-1]->setStyleSheet("background-color: yellow");
            lab[(i+1)*2-1][(j+1)*2]->setStyleSheet("background-color: yellow");
            if (res == 0){
               lab[(i+1)*2-1][(j+1)*2-1]->setStyleSheet("background-color: red");
            }
            return 1;
        }
       }
    }
    if (m_lab[i][j]->get_top() && m_used[i-1][j] == 0 && m_res == 0){
        lab[(i+1)*2-2][(j+1)*2-1]->setStyleSheet("background-color: blue");
        lab[(i+1)*2-2][(j+1)*2-1]->repaint();
        if (find1(lab, i-1, j, finishi, finishj, res+1)){
            lab[(i+1)*2-1][(j+1)*2-1]->setStyleSheet("background-color: yellow");
            lab[(i+1)*2-2][(j+1)*2-1]->setStyleSheet("background-color: yellow");
            if (res == 0){
               lab[(i+1)*2-1][(j+1)*2-1]->setStyleSheet("background-color: red");
            }
            return 1;
        }
    }
    if (m_lab[i][j]->get_left() && m_used[i][j-1] == 0 && m_res == 0){
        lab[(i+1)*2-1][(j+1)*2-2]->setStyleSheet("background-color: blue");
        lab[(i+1)*2-1][(j+1)*2-2]->repaint();
        if (find1(lab, i, j-1, finishi, finishj, res+1)){
            lab[(i+1)*2-1][(j+1)*2-1]->setStyleSheet("background-color: yellow");
            lab[(i+1)*2-1][(j+1)*2-2]->setStyleSheet("background-color: yellow");
            if (res == 0){
               lab[(i+1)*2-1][(j+1)*2-1]->setStyleSheet("background-color: red");
            }
            return 1;
        }
    }
    return 0;
}

bool Lab::find2(QLabel* lab[][100], int i, int j, int finishi, int finishj) {
    for (int i = 0; i < m_n; i++)
        for (int j = 0; j < m_m; j++)
            m_used[i][j] = 0;
    int starti = i;
    int startj = j;
    int p[1000];
    p[i*m_n+j] = -1;
    queue <pair<int, int>> q;
    q.push(make_pair(i, j));
    while (!q.empty()){
        int i = q.front().first;
        int j = q.front().second;
        q.pop();
        if (i == finishi && j == finishj){
            break;
        }
        if (i != starti || j != startj)
        lab[(i+1)*2-1][(j+1)*2-1]->setStyleSheet("background-color: blue");
        lab[(i+1)*2-1][(j+1)*2-1]->repaint();
        Sleep(m_time);
        if (m_lab[i][j]->get_top() && m_used[i-1][j] == 0){
            lab[(i+1)*2-2][(j+1)*2-1]->setStyleSheet("background-color: blue");
            lab[(i+1)*2-2][(j+1)*2-1]->repaint();
            Sleep(m_time);
            q.push(make_pair(i-1, j));
            m_used[i-1][j] = 1;
            p[(i-1)*m_n+j]=i*m_n+j;

        }
        if (m_lab[i][j]->get_dawn() && m_used[i+1][j] == 0){
            lab[(i+1)*2][(j+1)*2-1]->setStyleSheet("background-color: blue");
            lab[(i+1)*2][(j+1)*2-1]->repaint();
            Sleep(m_time);
            q.push(make_pair(i+1, j));
            m_used[i+1][j] = 1;
            p[(i+1)*m_n+j]=i*m_n+j;
        }
        if (m_lab[i][j]->get_right() && m_used[i][j+1] == 0){
            lab[(i+1)*2-1][(j+1)*2]->setStyleSheet("background-color: blue");
            lab[(i+1)*2-1][(j+1)*2]->repaint();
            Sleep(m_time);
            q.push(make_pair(i, j+1));
            m_used[i][j+1] = 1;
            p[i*m_n+j+1]=i*m_n+j;
        }
        if (m_lab[i][j]->get_left() && m_used[i][j-1] == 0){
            lab[(i+1)*2-1][(j+1)*2-2]->setStyleSheet("background-color: blue");
            lab[(i+1)*2-1][(j+1)*2-2]->repaint();
            Sleep(m_time);
            q.push(make_pair(i, j-1));
            m_used[i][j-1] = 1;
            p[i*m_n+j-1]=i*m_n+j;
        }
    }
    for (int v = finishi*m_n+finishj; v!=-1;){
        int j = v % m_n;
        int i = v / m_n;
        if (i == starti && j == startj){
            lab[(finishi+1)*2-1][(finishj+1)*2-1]->setStyleSheet("background-color: green");
            lab[(finishi+1)*2-1][(finishj+1)*2-1]->repaint();
            break;
        }
        lab[(i+1)*2-1][(j+1)*2-1]->setStyleSheet("background-color: yellow");
        lab[(i+1)*2-1][(j+1)*2-1]->repaint();
        v = p[v];
        if (v % m_n < j){
            lab[(i+1)*2-1][(j+1)*2-2]->setStyleSheet("background-color: yellow");
            lab[(i+1)*2-1][(j+1)*2-2]->repaint();
        } else
            if (v % m_n > j){
                lab[(i+1)*2-1][(j+1)*2]->setStyleSheet("background-color: yellow");
                lab[(i+1)*2-1][(j+1)*2]->repaint();
            } else
                if (v / m_n < i){
                    lab[(i+1)*2-2][(j+1)*2-1]->setStyleSheet("background-color: yellow");
                    lab[(i+1)*2-2][(j+1)*2-1]->repaint();
                } else
                    if (v / m_n > i){
                        lab[(i+1)*2][(j+1)*2-1]->setStyleSheet("background-color: yellow");
                        lab[(i+1)*2][(j+1)*2-1]->repaint();
                    }
    }
    return 1;
}

bool Lab::find3(QLabel* lab[][100], int i, int j, int finishi, int finishj, int res) {

}
