#include "results.h"
#include "data_elem.h"
#include <QWidget>
#include <QtWidgets>
#include <QDebug>

Results::~Results(){
    for (int i = 0; i < DB.size(); i++)
        delete DB[i];
    delete mainLayout;
    delete menuLayout;
    delete tabLayout;
    delete titleLayout;
    delete dataLayout;
    delete typeTitle;
    delete sizeTitle;
    delete speedTitle;
    delete randTitle;
    delete timeTitle;
    delete clearDBButt;
    delete lines_chooser;
    delete findButt;
    delete clearBDButt;
    delete lButt;
    delete rButt;
}

Results::Results()
{
    m_start = 0;
    m_lines = 6;
    mainLayout = new QGridLayout;
    menuLayout = new QVBoxLayout;
    tabLayout = new QVBoxLayout;
    titleLayout = new QHBoxLayout;
    dataLayout = new QGridLayout;

    setLayout(mainLayout);
    mainLayout->addLayout(tabLayout, 0, 0);
    mainLayout->addLayout(menuLayout,0,1);
    tabLayout->addLayout(titleLayout);

    linesLabel = new QLabel("Строк на странице");
    lines_chooser = new QSpinBox;
    lines_chooser->setRange(2, 25);
    lines_chooser->setValue(6);
    findButt = new QPushButton("Показать");
    clearDBButt = new QPushButton("Очистить записи");

    connect(findButt, SIGNAL(clicked()), this, SLOT(findButtClicked()));

    menuLayout->addWidget(linesLabel);
    menuLayout->addWidget(lines_chooser);
    menuLayout->addWidget(findButt);
    menuLayout->addWidget(clearDBButt, Qt::AlignTop);
    QSpacerItem *vS = new QSpacerItem(50, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    menuLayout->addItem(vS);

    LRLayout = new QHBoxLayout;
    lButt = new QPushButton("<");
    rButt = new QPushButton(">");
    menuLayout->addLayout(LRLayout);
    LRLayout->addWidget(lButt);
    LRLayout->addWidget(rButt);
    lButt->setEnabled(0);

    connect(lButt, SIGNAL(clicked()), this, SLOT(lButtClicked()));
    connect(rButt, SIGNAL(clicked()), this, SLOT(rButtClicked()));
    connect(clearDBButt, SIGNAL(clicked()), this, SLOT(clearDBButtClicked()));

    numTitle = new QLabel("#");
    typeTitle = new QLabel("Алгоритм");
    sizeTitle = new QLabel("Размер лабиринта");
    speedTitle = new QLabel("Скорость");
    randTitle = new QLabel("Случ Старт-Финиш");
    timeTitle = new QLabel("Время поиска, мкс");
    {
    numTitle->setMaximumHeight(50);
    typeTitle->setMaximumHeight(50);
    sizeTitle->setMaximumHeight(50);
    speedTitle->setMaximumHeight(50);
    randTitle->setMaximumHeight(50);
    timeTitle->setMaximumHeight(50);

    numTitle->setMinimumWidth(50);
    typeTitle->setMinimumWidth(150);
    sizeTitle->setMinimumWidth(150);
    speedTitle->setMinimumWidth(150);
    randTitle->setMinimumWidth(150);
    timeTitle->setMinimumWidth(150);

    numTitle->setMaximumWidth(50);

    numTitle->setMinimumHeight(50);
    typeTitle->setMinimumHeight(50);
    sizeTitle->setMinimumHeight(50);
    speedTitle->setMinimumHeight(50);
    randTitle->setMinimumHeight(50);
    timeTitle->setMinimumHeight(50);

    numTitle->setStyleSheet("QLabel {"
                                             "border-style: solid;"
                                             "border-width: 2px;"
                                             "background-color:grey;"
                                             "border-color: black; "
                                             "}");
    typeTitle->setStyleSheet("QLabel {"
                                             "border-style: solid;"
                                             "border-width: 2px;"
                                             "background-color:grey;"
                                             "border-color: black; "
                                             "}");
    sizeTitle->setStyleSheet("QLabel {"
                                             "border-style: solid;"
                                             "border-width: 2px;"
                                             "background-color:grey;"
                                             "border-color: black; "
                                             "}");
    speedTitle->setStyleSheet("QLabel {"
                                             "border-style: solid;"
                                             "border-width: 2px;"
                                             "background-color:grey;"
                                             "border-color: black; "
                                             "}");
    randTitle->setStyleSheet("QLabel {"
                                             "border-style: solid;"
                                             "border-width: 2px;"
                                             "background-color:grey;"
                                             "border-color: black; "
                                             "}");
    timeTitle->setStyleSheet("QLabel {"
                                             "border-style: solid;"
                                             "border-width: 2px;"
                                             "background-color:grey;"
                                             "border-color: black; "
                                             "}");
    numTitle->setAlignment(Qt::AlignCenter);
    typeTitle->setAlignment(Qt::AlignCenter);
    sizeTitle->setAlignment(Qt::AlignCenter);
    speedTitle->setAlignment(Qt::AlignCenter);
    randTitle->setAlignment(Qt::AlignCenter);
    timeTitle->setAlignment(Qt::AlignCenter);

    titleLayout->addWidget(numTitle);
    titleLayout->addWidget(typeTitle);
    titleLayout->addWidget(sizeTitle);
    titleLayout->addWidget(speedTitle);
    titleLayout->addWidget(randTitle);
    titleLayout->addWidget(timeTitle);
    }
    tabLayout->addLayout(dataLayout);
    tabLayout->addItem(vS);
    Load();
    Draw();
}

void Results::clearDBButtClicked(){
    QMessageBox::StandardButton answer;
    answer = QMessageBox::question(this, "Вы уверены?",
                         "Удалить все записи?",
                          QMessageBox::Yes | QMessageBox::No);
    if (answer == QMessageBox::Yes)
    {
        for (int i = 0; i<m_size ; i++)
            delete DB[i];
        DB.clear();
        QString file_name = "Tests.txt";
        QFile file(file_name);
        file.open(QIODevice::WriteOnly);
        QTextStream stream(&file);
        stream << "";
    }
    m_size = 0;
    m_start = 0;
    Draw();
}

void Results::findButtClicked(){
    m_lines = lines_chooser->value();
    Draw();
}

void Results::lButtClicked(){
    m_start-=m_lines;
    if (m_start < 0)
        m_start = 0;
    Draw();
}

void Results::rButtClicked(){
    m_start+=m_lines;
    if (m_start > m_size){
        m_start = m_size-1;
    }
    Draw();
}

void Results::Load(){
    QString file_name = "Tests.txt";
    QFile file(file_name);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);

    QString s1; int s2, s3, s4, s5;
    m_size = -1;
    while (!stream.atEnd()){
        s5=0;
        stream >> s1 >> s2 >> s3 >> s4 >> s5;
        if (s1=="")
            break;
        else if (s5==0)
            QMessageBox::critical(this, "Ошибка", "Файл поврежден!");

        DB.push_back(new data_elem);
        m_size++;
        DB[m_size]->m_type = s1;
        DB[m_size]->m_size = s2;
        DB[m_size]->m_speed = s3;
        DB[m_size]->m_rand = s4;
        DB[m_size]->m_time = s5;
    }
}

void Results::Draw(){
    m_finish = m_start + m_lines;
    if (m_start >= m_size - m_lines)
        rButt->setEnabled(0);
    else
        rButt->setEnabled(1);
    if (m_start == 0)
        lButt->setEnabled(0);
    else
        lButt->setEnabled(1);
    while (QLayoutItem* item = dataLayout->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    int i = 0;
    QLabel* labels[6];
    while (i < DB.size()){
        if (i>=m_start && i<m_finish){
            labels[0] = new QLabel;
            labels[1] = new QLabel(DB[i]->m_type);
            labels[2] = new QLabel;
            labels[3] = new QLabel;
            labels[4] = new QLabel;
            labels[5] = new QLabel;

            labels[0]->setNum(i+1);
            labels[2]->setNum(DB[i]->m_size);
            labels[3]->setNum(DB[i]->m_speed);
            labels[4]->setNum(DB[i]->m_rand);
            labels[5]->setNum(DB[i]->m_time);

            labels[0]->setAlignment(Qt::AlignCenter);
            if (i % 2 == 1)
                labels[0]->setStyleSheet("QLabel {"
                                     "border-style: solid;"
                                     "border-width: 1px;"
                                     "background-color: silver;"
                                     "border-color: black; "
                                     "}");
            else
                labels[0]->setStyleSheet("QLabel {"
                                     "border-style: solid;"
                                     "border-width: 1px;"
                                     "background-color: white;"
                                     "border-color: black; "
                                     "}");
            labels[0]->setMinimumHeight(30);
            labels[0]->setMaximumHeight(30);
            labels[0]->setMinimumWidth(50);
            labels[0]->setMaximumWidth(50);
            dataLayout->addWidget(labels[0],i-m_start,0);

            for (int p = 1; p < 6; p++){
                labels[p]->setAlignment(Qt::AlignCenter);
                if (i % 2 == 1)
                    labels[p]->setStyleSheet("QLabel {"
                                             "border-style: solid;"
                                             "border-width: 1px;"
                                             "background-color: silver;"
                                             "border-color: black; "
                                             "}");
                else
                    labels[p]->setStyleSheet("QLabel {"
                                             "border-style: solid;"
                                             "border-width: 1px;"
                                             "background-color: white;"
                                             "border-color: black; "
                                             "}");
                labels[p]->setMinimumHeight(30);
                labels[p]->setMaximumHeight(30);
                dataLayout->addWidget(labels[p],i-m_start,p);
            }
        }
        i++;
    }
    //resize(600, 500);
}
