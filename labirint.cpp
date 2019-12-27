#include <QtWidgets>
#include "labirint.h"
#include <labstruct.h>
#include "results.h"

Labirint::Labirint(QWidget *parent)
    : QDialog(parent)
{

    sizeLabel = new QLabel("Размер:");
    sizeLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    sizeChoser = new QSpinBox;
    sizeChoser->setMinimum(5);
    sizeChoser->setSingleStep(2);
    sizeChoser->setMaximum(53);
    sizeChoser->setValue(11);
    gen1Radio = new QRadioButton("Глубинный Алгоритм");
    gen3Radio = new QRadioButton("Алгоритм Дерево");
    randCheck = new QCheckBox("Случайные Старт-Финиш");
    randCheck -> setCheckState(Qt::CheckState::Checked);
    genButt = new QPushButton("&Сгенерировать");
    RandomButt = new QPushButton("С&лучайные Старт-Финиш");
    genError = new QLabel;
    genError->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    sizeLabel->setMaximumWidth(200);
    sizeChoser->setMaximumWidth(200);
    gen1Radio->setMaximumWidth(200);
    gen3Radio->setMaximumWidth(200);
    genButt->setMaximumWidth(200);
    RandomButt->setMaximumWidth(200);
    genError->setMaximumWidth(200);
    genError->setStyleSheet("color: rgb(250, 0, 0)");


    connect(RandomButt, SIGNAL(clicked()),
            this, SLOT(RandomButtClicked()));
    connect(genButt, SIGNAL(clicked()),
            this, SLOT(GenerateClicked()));
    connect(sizeChoser, SIGNAL(valueChanged(int)),
            this, SLOT(FixsizeChanger(int)));

    QVBoxLayout *GenLayout = new QVBoxLayout;
    GenLayout->addWidget(sizeLabel);
    GenLayout->addWidget(sizeChoser);
    GenLayout->addWidget(gen1Radio);
    GenLayout->addWidget(gen3Radio);
    GenLayout->addWidget(randCheck);
    GenLayout->addWidget(genButt);
    GenLayout->addWidget(genError);

    speedLabel = new QLabel("Задержка, мс:");
    speedChoser = new QSpinBox;
    speedChoser->setMinimum(0);
    speedChoser->setSingleStep(25);
    speedChoser->setMaximum(1000);
    speedChoser->setValue(200);
    find1Box = new QCheckBox("DFS");
    find2Box = new QCheckBox("BFS");
    find3Box = new QCheckBox("rand-find");
    findButt = new QPushButton("&Start");
    cleanButt = new QPushButton("&Очистить");
    cleanButt->setEnabled(0);
    findButt->setEnabled(0);
    findError = new QLabel;
    speedLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    findError->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    findError->setStyleSheet("color: rgb(250, 0, 0)");

    speedLabel->setMinimumWidth(200);
    speedLabel->setMaximumWidth(200);
    speedChoser->setMaximumWidth(200);
    find1Box->setMaximumWidth(200);
    find2Box->setMaximumWidth(200);
    find3Box->setMaximumWidth(200);
    findButt->setMaximumWidth(200);
    cleanButt->setMaximumWidth(200);
    findError->setMaximumWidth(200);

    connect(cleanButt, SIGNAL(clicked()),
            this, SLOT(cleanButtClicked()));
    connect(find1Box, SIGNAL(clicked()),
            this, SLOT(findBoxChanged()));
    connect(find2Box, SIGNAL(clicked()),
            this, SLOT(findBoxChanged()));
    connect(find3Box, SIGNAL(clicked()),
            this, SLOT(findBoxChanged()));
    connect(findButt, SIGNAL(clicked()),
            this, SLOT(FindClicked()));

    QVBoxLayout *FindLayout = new QVBoxLayout;
    //FindLayout->set
    FindLayout->addWidget(speedLabel);
    FindLayout->addWidget(speedChoser);
    FindLayout->addWidget(find1Box);
    FindLayout->addWidget(find2Box);
    FindLayout->addWidget(find3Box);
    //FindLayout->addWidget(find3Box);
    FindLayout->addWidget(findButt);
    FindLayout->addWidget(RandomButt);
    FindLayout->addWidget(cleanButt);
    FindLayout->addWidget(findError);

    QVBoxLayout *menuLayout = new QVBoxLayout;
    loadButt = new QPushButton("Загрузить");
    saveButt = new QPushButton("Сохранить");
    resultsButt = new QPushButton("Результаты");
    saveButt->setEnabled(0);
    exitButt = new QPushButton("Выход");
    menuLayout->addWidget(resultsButt);
    menuLayout->addWidget(loadButt);
    menuLayout->addWidget(saveButt);
    menuLayout->addWidget(exitButt);
    saveButt->setMaximumWidth(200);
    loadButt->setMaximumWidth(200);
    exitButt->setMaximumWidth(200);

    connect(resultsButt, SIGNAL(clicked()), this, SLOT(resultButtClicked()));
    connect(exitButt, SIGNAL(clicked()), this, SLOT(close()));
    connect(saveButt, SIGNAL(clicked()), this, SLOT(save()));
    connect(loadButt, SIGNAL(clicked()), this, SLOT(load()));

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addLayout(GenLayout, Qt::AlignTop);
    rightLayout->addSpacing(30);
    rightLayout->addLayout(FindLayout, Qt::AlignTop);
    QSpacerItem *vS = new QSpacerItem(50, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    rightLayout->addSpacing(30);
    rightLayout->addLayout(menuLayout);
    rightLayout->addItem(vS);

    lab1Layout = new QGridLayout;
    lab2Layout = new QGridLayout;

    lab1Layout->setHorizontalSpacing(0);
    lab1Layout->setVerticalSpacing(0);
    lab2Layout->setHorizontalSpacing(0);
    lab2Layout->setVerticalSpacing(0);

    Lab1 = new Lab(0, 0);
    Lab2 = new Lab(0, 0);
    Draw(0);

    lab1Title = new QLabel("<font size=24>Лабиринт 1</font>");
    lab2Title = new QLabel("<font size=24>Лабиринт 2</font>");
    lab1Title->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    lab2Title->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    lab2Info = new QLabel("");
    lab1Info = new QLabel("");
    lab1Info->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    lab2Info->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    QVBoxLayout *LleftLayout = new QVBoxLayout;
    LleftLayout->addWidget(lab1Title);
    LleftLayout->addLayout(lab1Layout);
    LleftLayout->addWidget(lab1Info);

    QVBoxLayout *RleftLayout = new QVBoxLayout;
    RleftLayout->addWidget(lab2Title);
    RleftLayout->addLayout(lab2Layout);
    RleftLayout->addWidget(lab2Info);

    QHBoxLayout *leftLayout = new QHBoxLayout;
    leftLayout->addLayout(LleftLayout);
    leftLayout->addSpacing(50);
    leftLayout->addLayout(RleftLayout);
    
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addSpacing(10);
    mainLayout->addLayout(leftLayout);
    mainLayout->addSpacing(30);
    mainLayout->addLayout(rightLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Лабиринт"));
    //setFixedHeight(600);
    //setFixedWidth(1300);
    resize(1300, 600);
    connect(this, SIGNAL(press(QMouseEvent*)), this, SLOT(WindowPress(QMouseEvent*)));
    connect(this, SIGNAL(move(QMouseEvent*)), this, SLOT(WindowMove(QMouseEvent*)));
    connect(this, SIGNAL(release(QMouseEvent*)), this, SLOT(WindowRelease()));
}

void Labirint::resultButtClicked(){
    Results *result_window = new Results;
    result_window->show();
}

void Labirint::RandomButtClicked(){
    lab1[finishi][finishj]->setStyleSheet("background-color: white");
    lab2[finishi][finishj]->setStyleSheet("background-color: white");
    lab1[starti][startj]->setStyleSheet("background-color: white");
    lab2[starti][startj]->setStyleSheet("background-color: white");
    starti=(rand()%(size/2))*2+1;
    startj=(rand()%(size/2))*2+1;
    finishi=(rand()%(size/2))*2+1;
    finishj=(rand()%(size/2))*2+1;
    while (finishi==starti && finishj==startj){
        finishi=(rand()%(size/2))*2+1;
        finishj=(rand()%(size/2))*2+1;
    }
    lab1[finishi][finishj]->setStyleSheet("background-color: green");
    lab2[finishi][finishj]->setStyleSheet("background-color: green");
    lab1[starti][startj]->setStyleSheet("background-color: red");
    lab2[starti][startj]->setStyleSheet("background-color: red");
}

void Labirint::cleanButtClicked(){
    cleanButt->setEnabled(0);
    Redraw();
}

void Labirint::Redraw(){
    for (int i = 1; i<size-1; i++)
        for (int j = 1; j<size-1; j++){
            lab1[i][j]->setStyleSheet("background-color: white");
            lab2[i][j]->setStyleSheet("background-color: white");
        }

    for (int i = 2; i<size-1; i+=2)
        for (int j = 2; j<size-1; j+=2){
            lab1[i][j]->setStyleSheet("background-color: black");
            lab2[i][j]->setStyleSheet("background-color: black");
        }
    lab1[starti][startj]->setStyleSheet("background-color: red");
    lab2[starti][startj]->setStyleSheet("background-color: red");
    lab1[finishi][finishj]->setStyleSheet("background-color: green");
    lab2[finishi][finishj]->setStyleSheet("background-color: green");
    for (int i = 0; i<size/2; i++)
        for (int j = 0; j<size/2; j++){
            if (!Lab1->m_lab[i][j]->get_right()){
                lab1[(i+1)*2-1][(j+1)*2]->setStyleSheet("background-color: black");
                lab2[(i+1)*2-1][(j+1)*2]->setStyleSheet("background-color: black");
            }
            if (!Lab1->m_lab[i][j]->get_dawn()){
                lab1[(i+1)*2][(j+1)*2-1]->setStyleSheet("background-color: black");
                lab2[(i+1)*2][(j+1)*2-1]->setStyleSheet("background-color: black");
            }
        }
}

void Labirint::Draw(int k)
{
    while (QLayoutItem* item = lab1Layout->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    while (QLayoutItem* item = lab2Layout->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    if (k != -1){
        delete Lab1;
        delete Lab2;
        Lab1 = new Lab(size/2, size/2);
        Lab2 = new Lab(0, 0);
        if (k == 1){
            Lab1->gen1(0, 0);
        }
        if (k == 3){
            Lab1->gen3();
        }

        *Lab2 = Lab1;
        starti = 1;
        startj = 1;
        finishi = size - 2;
        finishj = size - 2;
    }
    for (int i = 0; i<size; i++)
        for (int j = 0; j<size; j++){
            lab1[i][j] = new QLabel;
            lab2[i][j] = new QLabel;

            if (i == 0 || i == size-1 || j == 0 || j == size-1){
                lab1[i][j]->setStyleSheet("background-color: black");
                lab2[i][j]->setStyleSheet("background-color: black");
            }
            else{
                lab1[i][j]->setStyleSheet("background-color: white");
                lab2[i][j]->setStyleSheet("background-color: white");
            }
            lab1Layout->addWidget(lab1[i][j],i,j);
            lab2Layout->addWidget(lab2[i][j],i,j);
        }

    for (int i = 2; i<size-1; i+=2)
        for (int j = 2; j<size-1; j+=2){
            lab1[i][j]->setStyleSheet("background-color: black");
            lab2[i][j]->setStyleSheet("background-color: black");
        }
    lab1[starti][startj]->setStyleSheet("background-color: red");
    lab2[starti][startj]->setStyleSheet("background-color: red");
    lab1[finishi][finishj]->setStyleSheet("background-color: green");
    lab2[finishi][finishj]->setStyleSheet("background-color: green");
    for (int i = 0; i<size/2; i++)
        for (int j = 0; j<size/2; j++){
            if (!Lab1->m_lab[i][j]->get_right()){
                lab1[(i+1)*2-1][(j+1)*2]->setStyleSheet("background-color: black");
                lab2[(i+1)*2-1][(j+1)*2]->setStyleSheet("background-color: black");
            }
            if (!Lab1->m_lab[i][j]->get_dawn()){
                lab1[(i+1)*2][(j+1)*2-1]->setStyleSheet("background-color: black");
                lab2[(i+1)*2][(j+1)*2-1]->setStyleSheet("background-color: black");
            }
        }
}

void Labirint::GenerateClicked(){
    genButt->setEnabled(0);
    genButt->repaint();
    genError->setText("");
    size = sizeChoser->value();
    if (gen1Radio->isChecked()){
        Draw(1);
        if (randCheck->checkState())
            RandomButt->click();
    }
    else if (gen3Radio->isChecked()){
        Draw(3);
        if (randCheck->checkState())
            RandomButt->click();
    }
    else genError->setText("Выберите алгоритм");
    genButt->setEnabled(1);
    genButt->repaint();
    saveButt->setEnabled(1);
    findButt->setEnabled(1);
}

void Labirint::findBoxChanged(){
    if (find1Box->checkState() + find2Box->checkState() + find3Box->checkState()<4){
        find3Box->setEnabled(1);
        find2Box->setEnabled(1);
        find1Box->setEnabled(1);
    }
    if (find1Box->checkState()==2 && find2Box->checkState()==2)
        find3Box->setEnabled(0);
    if (find1Box->checkState()==2 && find3Box->checkState()==2)
        find2Box->setEnabled(0);
    if (find3Box->checkState()==2 && find2Box->checkState()==2)
        find1Box->setEnabled(0);
}

void Labirint::FixsizeChanger(int a){
    if (a%2==0)
        sizeChoser->setValue(sizeChoser->value()-1);
}

void Labirint::mousePressEvent(QMouseEvent* event)
{
    emit press(event);
}
void Labirint::mouseReleaseEvent(QMouseEvent* event)
{
    emit release(event);
}
void Labirint::mouseMoveEvent(QMouseEvent* event)
{
    emit move(event);
}

void Labirint::WindowPress(QMouseEvent* event){
    if ( (event->x() > lab1[starti][startj]->x()) && (event->x() < lab1[starti+1][startj+1]->x()-1) )
        if ( (event->y() > lab1[starti][startj]->y()) && (event->y() < lab1[starti+1][startj+1]->y()-1) ){
            StartPressedOnLab1 = 1;
        }
    if ( (event->x() > lab2[starti][startj]->x()) && (event->x() < lab2[starti+1][startj+1]->x()-1) )
        if ( (event->y() > lab2[starti][startj]->y()) && (event->y() < lab2[starti+1][startj+1]->y()-1) ){
            StartPressedOnLab2 = 1;
        }
    if ( (event->x() > lab1[finishi][finishj]->x()) && (event->x() < lab1[finishi+1][finishj+1]->x()-1) )
        if ( (event->y() > lab1[finishi][finishj]->y()) && (event->y() < lab1[finishi+1][finishj+1]->y()-1) ){
            FinishPressedOnLab1 = 1;
        }
    if ( (event->x() > lab2[finishi][finishj]->x()) && (event->x() < lab2[finishi+1][finishj+1]->x()-1) )
        if ( (event->y() > lab2[finishi][finishj]->y()) && (event->y() < lab2[finishi+1][finishj+1]->y()-1) ){
            FinishPressedOnLab2 = 1;
        }
}

int Labirint::mouseLabj(QMouseEvent* event, QLabel* lab[][100]){
    return (event->x()-lab[0][0]->x()) / (lab[0][1]->x() - lab[0][0]->x());
}
int Labirint::mouseLabi(QMouseEvent* event, QLabel* lab[][100]){
    return (event->y()-lab[0][0]->y()) / (lab[1][0]->y() - lab[0][0]->y());
}
bool Labirint::mouseOutOfStart(QMouseEvent* event, QLabel* lab[][100]){
    return (mouseLabi(event, lab)/2*2+1 != starti || mouseLabj(event, lab)/2*2+1 !=startj);
}
bool Labirint::mouseOutOfFinish(QMouseEvent* event, QLabel* lab[][100]){
    return (mouseLabi(event, lab)/2*2+1 != finishi || mouseLabj(event, lab)/2*2+1 !=finishj);
}
bool Labirint::insideLab(int i, int j){
    return (i < size - 1 && j < size - 1 && i > 0 && j > 0);
}

void Labirint::WindowMove(QMouseEvent* event){
    int i, j;
    if (StartPressedOnLab1){
        i=mouseLabi(event, lab1);
        j=mouseLabj(event, lab1);
        if (insideLab(i, j))
            if (mouseOutOfStart(event, lab1))
                if (mouseOutOfFinish(event, lab1)){
                    lab1[starti][startj]->setStyleSheet("background-color: white");
                    lab2[starti][startj]->setStyleSheet("background-color: white");
                    startj=mouseLabj(event, lab1)/2*2+1;
                    starti=mouseLabi(event, lab1)/2*2+1;
                    lab1[starti][startj]->setStyleSheet("background-color: red");
                    lab2[starti][startj]->setStyleSheet("background-color: red");
                }
    }

    if (StartPressedOnLab2){
        i=mouseLabi(event, lab2);
        j=mouseLabj(event, lab2);
        if (insideLab(i, j))
            if (mouseOutOfStart(event, lab2))
                if (mouseOutOfFinish(event, lab2)){
                    lab1[starti][startj]->setStyleSheet("background-color: white");
                    lab2[starti][startj]->setStyleSheet("background-color: white");
                    starti=mouseLabi(event, lab2)/2*2+1;
                    startj=mouseLabj(event, lab2)/2*2+1;
                    lab1[starti][startj]->setStyleSheet("background-color: red");
                    lab2[starti][startj]->setStyleSheet("background-color: red");
                }
    }

    if (FinishPressedOnLab1){
        i=mouseLabi(event, lab1);
        j=mouseLabj(event, lab1);
        if (insideLab(i, j))
        if (mouseOutOfStart(event, lab1))
            if (mouseOutOfFinish(event, lab1)){
                    lab1[finishi][finishj]->setStyleSheet("background-color: white");
                    lab2[finishi][finishj]->setStyleSheet("background-color: white");
                    finishi=mouseLabi(event, lab1)/2*2+1;
                    finishj=mouseLabj(event, lab1)/2*2+1;
                    lab1[finishi][finishj]->setStyleSheet("background-color: green");
                    lab2[finishi][finishj]->setStyleSheet("background-color: green");
            }
    }

    if (FinishPressedOnLab2){
        i=mouseLabi(event, lab2);
        j=mouseLabj(event, lab2);
        if (insideLab(i, j))
        if (mouseOutOfStart(event, lab2))
            if (mouseOutOfFinish(event, lab2)){
                    lab1[finishi][finishj]->setStyleSheet("background-color: white");
                    lab2[finishi][finishj]->setStyleSheet("background-color: white");
                    finishi=mouseLabi(event, lab2)/2*2+1;
                    finishj=mouseLabj(event, lab2)/2*2+1;
                    lab1[finishi][finishj]->setStyleSheet("background-color: green");
                    lab2[finishi][finishj]->setStyleSheet("background-color: green");
              }
    }
}

void Labirint::WindowRelease(){
    if (FinishPressedOnLab1) FinishPressedOnLab1 = 0;
    if (StartPressedOnLab1) StartPressedOnLab1 = 0;
    if (FinishPressedOnLab2) FinishPressedOnLab2 = 0;
    if (StartPressedOnLab2) StartPressedOnLab2 = 0;
}

void Labirint::FindClicked(){
    disconnect(this, SIGNAL(press(QMouseEvent*)), this, SLOT(WindowPress(QMouseEvent*)));
    disconnect(this, SIGNAL(move(QMouseEvent*)), this, SLOT(WindowMove(QMouseEvent*)));
    disconnect(this, SIGNAL(release(QMouseEvent*)), this, SLOT(WindowRelease()));
    cleanButt->setEnabled(0);
    Redraw();
    cleanButt->setEnabled(0);
    RandomButt->setEnabled(0);
    RandomButt->repaint();
    cleanButt->repaint();
    genButt->setEnabled(0);
    findButt->setEnabled(0);
    genButt->repaint();
    findButt->repaint();
    Lab1->m_time = speedChoser->value();
    Lab2->m_time = speedChoser->value();
    findError->setText("");
    if (find1Box->checkState() + find2Box->checkState() + find3Box->checkState()<4){
        findError->setText("Выберите два алгоритма");
    }else{
        QString file_name = "Tests.txt";
        QFile file(file_name);
        file.open(QIODevice::Append | QIODevice::Text);
        QTextStream stream(&file);

        QElapsedTimer timer;
        if (find1Box->checkState() == 2){
            lab1Title->setText("<font size=24>Лабиринт 1 - DFS</font>");
            timer.start();
            Lab1->find1(lab1, (starti-1)/2, (startj-1)/2, (finishi-1)/2, (finishj-1)/2, 0);
            lab1Info->setText("Путь найден за " + QString::number(timer.nsecsElapsed()/1000000000)+ ":"
                                                + QString::number(timer.nsecsElapsed()%1000000000/1000000)+ ":"
                                                + QString::number(timer.nsecsElapsed()%1000000/1000) + "");
            stream << "DFS ";
            stream << size << " " << speedChoser->value() << " "<< bool(randCheck->checkState()) << " " << timer.nsecsElapsed()/1000 << endl;
            if (find2Box->checkState() == 2){
                lab2Title->setText("<font size=24>Лабиринт 2 - BFS</font>");
                timer.start();
                Lab2->find2(lab2, (starti-1)/2, (startj-1)/2, (finishi-1)/2, (finishj-1)/2);
                lab2Info->setText("Путь найден за " + QString::number(timer.nsecsElapsed()/1000000000)+ ":"
                                                    + QString::number(timer.nsecsElapsed()%1000000000/1000000)+ ":"
                                                    + QString::number(timer.nsecsElapsed()%1000000/1000) + "");
                stream << "BFS ";
                stream << size << " " << speedChoser->value() << " " << bool(randCheck->checkState())<< " " << timer.nsecsElapsed()/1000 << endl;
            } else
            if (find3Box->checkState() == 2){
                lab2Title->setText("<font size=24>Лабиринт 2 - rand-find</font>");
                timer.start();
                Lab2->find3(lab2, (starti-1)/2, (startj-1)/2, (finishi-1)/2, (finishj-1)/2);
                lab2Info->setText("Путь найден за " + QString::number(timer.nsecsElapsed()/1000000000)+ ":"
                                                    + QString::number(timer.nsecsElapsed()%1000000000/1000000)+ ":"
                                                    + QString::number(timer.nsecsElapsed()%1000000/1000) + "");
                stream << "rand-find ";
                stream << size << " " << speedChoser->value() << " " << bool(randCheck->checkState())<< " " << timer.nsecsElapsed()/1000 << endl;
            }
        }
        else{
            if (find2Box->checkState() == 2){
                lab1Title->setText("<font size=24>Лабиринт 2 - BFS</font>");
                timer.start();
                Lab1->find2(lab1, (starti-1)/2, (startj-1)/2, (finishi-1)/2, (finishj-1)/2);
                lab1Info->setText("Путь найден за " + QString::number(timer.nsecsElapsed()/1000000000)+ ":"
                                                    + QString::number(timer.nsecsElapsed()%1000000000/1000000)+ ":"
                                                    + QString::number(timer.nsecsElapsed()%1000000/1000) + "");
                stream << "BFS ";
                stream << size << " " << speedChoser->value() << " " << bool(randCheck->checkState())<< " " << timer.nsecsElapsed()/1000 << endl;
            }
            if (find3Box->checkState() == 2){
                lab2Title->setText("<font size=24>Лабиринт 2 - rand-find</font>");
                timer.start();
                Lab2->find3(lab2, (starti-1)/2, (startj-1)/2, (finishi-1)/2, (finishj-1)/2);
                lab2Info->setText("Путь найден за " + QString::number(timer.nsecsElapsed()/1000000000)+ ":"
                                                    + QString::number(timer.nsecsElapsed()%1000000000/1000000)+ ":"
                                                    + QString::number(timer.nsecsElapsed()%1000000/1000) + "");
                stream << "rand-find ";
                stream << size << " " << speedChoser->value() << " " << bool(randCheck->checkState())<< " " << timer.nsecsElapsed()/1000 << endl;
            }
        }
    }
    cleanButt->setEnabled(1);
    cleanButt->repaint();
    genButt->setEnabled(1);
    findButt->setEnabled(1);
    genButt->repaint();
    findButt->repaint();
    RandomButt->setEnabled(1);
    RandomButt->repaint();
    connect(this, SIGNAL(press(QMouseEvent*)), this, SLOT(WindowPress(QMouseEvent*)));
    connect(this, SIGNAL(move(QMouseEvent*)), this, SLOT(WindowMove(QMouseEvent*)));
    connect(this, SIGNAL(release(QMouseEvent*)), this, SLOT(WindowRelease()));
}

bool Labirint::save(){
    QString file_name = QFileDialog::getSaveFileName(this, "Сохранить лабиринт", "", "*.txt");
    if (file_name!=""){
        QFile file(file_name);
        file.open(QIODevice::WriteOnly);
        QTextStream stream(&file);
        stream << "ThisIsLabirintSave" << endl;
        stream << size << endl;
        for (int i = 0; i<size/2; i++)
            for (int j = 0; j<size/2; j++){
                stream << Lab1->m_lab[i][j]->get_top() << " "
                       << Lab1->m_lab[i][j]->get_right() << " "
                       << Lab1->m_lab[i][j]->get_dawn() << " "
                       << Lab1->m_lab[i][j]->get_left() << endl;
            }
       stream << starti << " " << startj << endl;
       stream << finishi << " " << finishj << endl;
       return 0;
    }
    return 1;
}

bool Labirint::load(){
    cleanButt->setEnabled(0);
    saveButt->setEnabled(0);
    saveButt->repaint();
    cleanButt->repaint();
    genButt->setEnabled(0);
    findButt->setEnabled(0);
    genButt->repaint();
    findButt->repaint();
    QString file_name = QFileDialog::getOpenFileName(this, "Загрузить лабиринт", "", "*.txt");
    if (file_name!=""){
        QFile file(file_name);
        file.open(QIODevice::ReadOnly);
        QTextStream stream(&file);
        QString s;
        int a;
        stream >> s;
        if (s != "ThisIsLabirintSave"){
            QMessageBox::critical(this, "Ошибка", "Файл поврежден!");
            saveButt->setEnabled(1);
            saveButt->repaint();
            cleanButt->setEnabled(1);
            cleanButt->repaint();
            genButt->setEnabled(1);
            findButt->setEnabled(1);
            genButt->repaint();
            findButt->repaint();
            return 1;
        }
        delete Lab1;
        delete Lab2;
        stream >> a;
        size = a;
        Lab1 = new Lab(size/2, size/2);
        Lab2 = new Lab(0,0);
        sizeChoser->setValue(size);
        for (int i = 0; i<size/2; i++)
            for (int j = 0; j<size/2; j++){
                stream >> a;
                if (a) Lab1->m_lab[i][j]->go_top();
                stream >> a;
                if (a) Lab1->m_lab[i][j]->go_right();
                stream >> a;
                if (a) Lab1->m_lab[i][j]->go_dawn();
                stream >> a;
                if (a) Lab1->m_lab[i][j]->go_left();
            }
        stream >> starti >> startj >> finishi >> finishj;
        *Lab2 = Lab1;
        Draw(-1);
        saveButt->setEnabled(1);
        saveButt->repaint();
        cleanButt->setEnabled(1);
        cleanButt->repaint();
        genButt->setEnabled(1);
        findButt->setEnabled(1);
        genButt->repaint();
        findButt->repaint();
        return 0;
    }
    saveButt->setEnabled(1);
    saveButt->repaint();
    cleanButt->setEnabled(1);
    cleanButt->repaint();
    genButt->setEnabled(1);
    findButt->setEnabled(1);
    genButt->repaint();
    findButt->repaint();
    return 1;
}

Labirint::~Labirint(){
    delete sizeLabel;
    delete sizeChoser;
    delete gen1Radio;
    delete gen3Radio;
    delete genButt;
    delete genError;
    delete speedChoser;
    delete speedLabel;
    delete find1Box;
    delete find2Box;
    delete find3Box;
    delete findButt;
    delete cleanButt;
    delete findError;
    delete Line;
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++){
            delete lab1[i][j];
            delete lab2[i][j];
        }
    delete lab1Title;
    delete lab2Title;
    delete lab1Info;
    delete lab2Info;
    delete Lab1;
    delete Lab2;
    delete lab1Layout;
    delete lab2Layout;
}
