#include <QtWidgets>
#include "labirint.h"
#include <labstruct.h>

Labirint::Labirint(QWidget *parent)
    : QDialog(parent)
{

    sizeLabel = new QLabel("Размер:");
    sizeLabel->setMaximumSize(1000, 14);
    sizeChoser = new QSpinBox;
    sizeLabel->setBuddy(sizeChoser);
    sizeChoser->setMinimum(4);
    sizeChoser->setMaximum(35);
    sizeChoser->setValue(size);
    gen1Radio = new QRadioButton("1 Gen");
    gen2Radio = new QRadioButton("2 Gen");
    gen3Radio = new QRadioButton("3 Gen");
    genButt = new QPushButton("Сгенерировать");


    QVBoxLayout *GenLayout = new QVBoxLayout;
    GenLayout->addWidget(sizeLabel, Qt::AlignTop);
    GenLayout->addWidget(sizeChoser);
    GenLayout->addWidget(gen1Radio);
    GenLayout->addWidget(gen2Radio);
    GenLayout->addWidget(gen3Radio);
    GenLayout->addWidget(genButt);


    find1Box = new QCheckBox("1 Poisk");
    find2Box = new QCheckBox("2 Poisk");
    find3Box = new QCheckBox("3 Poisk");
    findButt = new QPushButton("Start");

    QVBoxLayout *FindLayout = new QVBoxLayout;
    FindLayout->addWidget(find1Box);
    FindLayout->addWidget(find2Box);
    FindLayout->addWidget(find3Box);
    FindLayout->addWidget(findButt);

    Line = new QLine;
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addSpacing(36);
    rightLayout->addLayout(GenLayout, Qt::AlignTop);
    rightLayout->addSpacing(50);
    rightLayout->addLayout(FindLayout, Qt::AlignTop);

    //Это нашел в интернете для решения проблемсы выравнивания в лояуте
    QWidget* myWidget = new QWidget;
    rightLayout->insertWidget(-1, myWidget, 0, Qt::AlignTop);

    QGridLayout *lab1Layout = new QGridLayout;
    QGridLayout *lab2Layout = new QGridLayout;

    Draw(Lab1, lab1, lab1Layout, 0);
    Draw(Lab2, lab2, lab2Layout, 0);

    //lab2[2][2]->setPixmap(Wall);

    lab1Title = new QLabel("<font size=24>Лабиринт 1</font>");
    lab2Title = new QLabel("<font size=24>Лабиринт 2</font>");
    lab2Info = new QLabel;
    lab1Info = new QLabel;
    //lab1Title->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    //lab2Title->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    //lab2Title->setMaximumSize(1000, 30);
    //lab1Title->setMaximumSize(1000, 30);

    QVBoxLayout *LleftLayout = new QVBoxLayout;
    LleftLayout->addWidget(lab1Title);
    LleftLayout->addLayout(lab1Layout);
    LleftLayout->addWidget(lab2Info);

    QVBoxLayout *RleftLayout = new QVBoxLayout;
    RleftLayout->addWidget(lab2Title);
    RleftLayout->addLayout(lab2Layout);
    RleftLayout->addWidget(lab2Info);

    //Опять для выравнивания
    //LleftLayout->insertWidget(-1, myWidget, 0, Qt::AlignTop);
    //RleftLayout->insertWidget(-1, myWidget, 0, Qt::AlignTop);

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
    //setFixedHeight(sizeHint().height());
    setFixedWidth(sizeHint().width());
}


void Labirint::Draw(Lab *Labo, QLabel *lab[41][41], QGridLayout *labLayout, int k)
{
    delete Labo;
    Labo = new Lab(size, size);

    if (k == 1){
        Labo->gen1(size/2, size/2);
    }
    if (k == 2){

    }
    if (k == 3){

    }
    if (k == 0){

    }

    QPixmap Wall("Wall.png");
    QPixmap Empty("Empty.png");
    for (int i = 0; i<size; i++)
        for (int j = 0; j<size; j++){
            lab[i][j] = new QLabel;
            if (i == 0 || i == size-1 || j == 0 || j == size-1)
                lab[i][j]->setPixmap(Wall);
            else
                lab[i][j]->setPixmap(Empty);
            labLayout->addWidget(lab[i][j],i,j);
        }


}

void Labirint::GenerateClicked(){

}
