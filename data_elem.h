#ifndef DATA_ELEM_H
#define DATA_ELEM_H

#include <QWidget>

class data_elem
{

public:
    QString m_type;
    int m_size;
    int m_speed;
    bool m_rand;
    int m_time;

    data_elem();
};


#endif // DATA_ELEM_H
