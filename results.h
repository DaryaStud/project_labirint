#ifndef RESULTS_H
#define RESULTS_H

#include <QDialog>
#include <QLabel>
#include <QWidget>
#include "labstruct.h"
#include "data_elem.h"

class QRadioButton;
class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSpinBox;
class QGridLayout;
class QVBoxLayout;
class QHBoxLayout;
class QComboBox;
class data_elem;


class Results: public QDialog
{
    Q_OBJECT

    int m_start;
    int m_finish;
    int m_lines;
    int m_size;
    QLabel *linesLabel;
    QSpinBox *lines_chooser;
    QPushButton *findButt;
    QPushButton *clearBDButt;
    QPushButton *lButt;
    QPushButton *rButt;

    QHBoxLayout *LRLayout;
    QString file_name;
    QGridLayout *mainLayout;
    QVBoxLayout *menuLayout;
    QVBoxLayout *tabLayout;
    QHBoxLayout *titleLayout;
    QGridLayout *dataLayout;
    QLabel *numTitle;
    QLabel *typeTitle;
    QLabel *sizeTitle;
    QLabel *speedTitle;
    QLabel *randTitle;
    QLabel *timeTitle;
    QPushButton *clearDBButt;
    QVector <data_elem*> DB;
    QVector <data_elem*> DBsorted;

private slots:
    void findButtClicked();
    void lButtClicked();
    void rButtClicked();
    void clearDBButtClicked();

public:
    Results();
    ~Results();
    void Draw();
    void Load();
    void Sort();
};



#endif // RESULTS_H
