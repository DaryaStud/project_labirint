#ifndef LABIRINT_H
#define LABIRINT_H

#include <QDialog>
#include <QWidget>
#include <labstruct.h>

class QRadioButton;
class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSpinBox;
class QGridLayout;

class Labirint : public QDialog
{
    Q_OBJECT

public:
    Labirint(QWidget *parent = 0);
    void Draw(Lab *Lab, QLabel *lab[41][41], QGridLayout* labLayout, int k);
signals:


private slots:
    void GenerateClicked();
    //void StartClicked();
    //void CheckBoxClicked();

private:
    int size = 20;
    QLabel *sizeLabel;
    QSpinBox *sizeChoser;
    QRadioButton *gen1Radio;
    QRadioButton *gen2Radio;
    QRadioButton *gen3Radio;
    QCheckBox *find1Box;
    QCheckBox *find2Box;
    QCheckBox *find3Box;
    QPushButton *genButt;
    QPushButton *findButt;
    QLine *Line;
    QLabel* lab2[41][41];
    QLabel* lab1[41][41];
    QLabel *lab1Title;
    QLabel *lab2Title;
    QLabel *lab1Info;
    QLabel *lab2Info;
    Lab *Lab1;
    Lab *Lab2;
};
#endif
