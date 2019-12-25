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
    Labirint(QWidget *parent = nullptr);
    void Redraw();
    void Draw(int k);
    ~Labirint();
signals:
    void press(QMouseEvent *event);
    void move(QMouseEvent *event);
    void release(QMouseEvent *event);
protected:
    void mouseReleaseEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void resultButtClicked();
    void RandomButtClicked();
    void cleanButtClicked();
    void GenerateClicked();
    void FindClicked();
    void findBoxChanged();
    void FixsizeChanger(int a);
    void WindowPress(QMouseEvent* event);
    void WindowMove(QMouseEvent* event);
    void WindowRelease();
    int mouseLabi(QMouseEvent* event, QLabel* lab1[][100]);
    int mouseLabj(QMouseEvent* event, QLabel* lab1[][100]);
    bool mouseOutOfStart(QMouseEvent* event, QLabel* lab[][100]);
    bool mouseOutOfFinish(QMouseEvent* event, QLabel* lab[][100]);
    bool insideLab(int i, int j);
    bool save();
    bool load();
    //void StartClicked();
    //void CheckBoxClicked();

private:
    int w, h;
    int size = 21;
    QLabel *sizeLabel;
    QSpinBox *sizeChoser;
    QRadioButton *gen1Radio;
    QRadioButton *gen3Radio;
    QCheckBox *randCheck;
    QPushButton *genButt;
    QPushButton *RandomButt;
    QLabel *genError;
    QSpinBox *speedChoser;
    QLabel *speedLabel;
    QCheckBox *find1Box;
    QCheckBox *find2Box;
    QCheckBox *find3Box;
    QPushButton *findButt;
    QPushButton *cleanButt;
    QLabel *findError;
    QLine *Line;
    QLabel* lab2[100][100];
    QLabel* lab1[100][100];
    QLabel *lab1Title;
    QLabel *lab2Title;
    QLabel *lab1Info;
    QLabel *lab2Info;
    Lab *Lab1 = nullptr;
    Lab *Lab2 = nullptr;
    QGridLayout *lab1Layout;
    QGridLayout *lab2Layout;
    int starti;
    int startj;
    int finishi;
    int finishj;
    bool StartPressedOnLab1 = 0;
    bool FinishPressedOnLab1 = 0;
    bool StartPressedOnLab2 = 0;
    bool FinishPressedOnLab2 = 0;
    int labPSizeX;
    int labPSizeY;
    QPushButton* loadButt;
    QPushButton* saveButt;
    QPushButton *resultsButt;
    QPushButton* exitButt;
};
#endif
