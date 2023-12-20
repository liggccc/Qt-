#include "examdialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QApplication>
#include <QButtonGroup>
#include <QPushButton>

ExamDialog::ExamDialog(QWidget* parent):QDialog(parent)
{
    //设置字体大小
    QFont font;
    font.setPointSize(12);
    setFont(font);

    //设置窗体背景颜色
    setPalette(QPalette(QColor(209, 215, 255)));
    setWindowTitle("考试已用时: 0分0秒");
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    resize(800, 900);

    initTimer();
    initLayout();
    if(!initTextEdit()){
        QMessageBox::information(this, "提示", "初始化题库数据文件失败！");
        QTimer::singleShot(0, qApp, SLOT(quit()));//间隔0秒当前的应用程序退出操作
    }
    initButtons();
    show();
}

void ExamDialog::initTimer()
{
    m_timeGo = 0;
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    m_timer->start();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(freshTime()));//连接信号与槽
}

void ExamDialog::initLayout()
{
    m_layout = new QGridLayout(this);
    m_layout->setSpacing(10);//设置控件间的间距
    m_layout->setMargin(10); //设置窗体和控件间的间隙
}

bool ExamDialog::initTextEdit()//初始化文本编译器
{
    QString strLine;//保存文件中读取到的一行数据
    QStringList strList; //保存读取到的答案行
    QString fileName("exam.txt");
    QFile file(fileName);
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    if( file.open(QIODevice::ReadOnly | QIODevice::Text ))
    {
        m_textEdit = new QTextEdit(this);
        m_textEdit->setReadOnly(true);
        QString strText;
        int nlines = 0;
        while(!stream.atEnd()){
            //过滤首行
            if(nlines == 0){
                stream.readLine();
                nlines ++ ;
                continue;
            }
            //过滤答案行
            if( (nlines >= 6 && nlines <= 6 * 9 && nlines % 6 == 0) || nlines == 6 * 9 + 4){
                strLine = stream.readLine();
                strList = strLine.split(" ");
                m_answerList.append(strList.at(1));
                strText += "\n";
                nlines ++ ;
                continue;
            }
            strText += stream.readLine();
            strText += "\n";
            nlines ++ ;
        }
        m_textEdit->setText(strText);
        m_layout->addWidget(m_textEdit, 0, 0, 1, 10);
        file.close();
        return true;
    }else{
        return false;
    }
}

void ExamDialog::initButtons()
{
    QStringList strList = {"A","B","C","D"};
    for (int i = 0; i < 10; i ++ ){
        //题目标签
        m_titleLabels[i] = new QLabel(this);
        m_titleLabels[i]->setText("第" + QString::number(i + 1) + "题");
        m_layout->addWidget(m_titleLabels[i], 1, i);//文本标签是第1行第i列开始，占据一行一列（最小值可以不写）

        //判断题
        if(i == 9){
            m_radioA = new QRadioButton(this);//考试窗口作为他的父窗口
            m_radioB = new QRadioButton(this);

            m_radioA->setText("正确");
            m_radioB->setText("错误");

            m_layout->addWidget(m_radioA, 2, 9);
            m_layout->addWidget(m_radioB, 3, 9);

            m_btnGroups[8] = new QButtonGroup(this);
            m_btnGroups[8]->addButton(m_radioA);
            m_btnGroups[8]->addButton(m_radioB);
            break;
        }
        if (i < 8) m_btnGroups[i] = new QButtonGroup(this);
        //选择题
        for (int j = 0; j < 4; j ++ ){
            //多选题
            if (i == 8){
                m_checkBtns[j] = new QCheckBox(this);
                m_checkBtns[j]->setText(strList.at(j));
                m_layout->addWidget(m_checkBtns[j], 2 + j, 8);
            }else{
                //单选题
                m_radioBtns[4 * i + j] = new QRadioButton(this);
                m_radioBtns[4 * i + j]->setText(strList.at(j));
                m_layout->addWidget(m_radioBtns[4 * i + j], 2+j,i);
                m_btnGroups[i]->addButton(m_radioBtns[4 * i + j]);
            }
        }
    }
    QPushButton *submitBtn = new QPushButton(this);
    submitBtn->setText("提交");
    submitBtn->setFixedSize(100, 35);
    connect(submitBtn, SIGNAL(clicked(bool)),this,SLOT(getScore()));//信号与槽连接
    m_layout->addWidget(submitBtn, 6, 9);
}

bool ExamDialog::hasNoSelect()
{
    int radioSelects = 0;
    for (int i = 0; i < 8; i ++ )
        if( m_btnGroups[i]->checkedButton() )
            radioSelects ++ ;
    if(radioSelects < 8)
        return true;

    int checkSelects = 0;
    for (int i = 0; i < 4; i ++ )
        if( m_checkBtns[i]->isChecked())
            checkSelects ++ ;
    if (checkSelects < 2)
        return true;

    if (m_radioA->isChecked() || m_radioB->isChecked())
        return false;
    else return true;

    return false;
}

void ExamDialog::freshTime()
{
    //刷新考试用时
    m_timeGo++;
    QString min = QString::number(m_timeGo / 60);
    QString sec = QString::number(m_timeGo % 60);
    setWindowTitle("考试已用时: " + min + "分" + sec + "秒");
}

void ExamDialog::getScore()
{
    if (hasNoSelect()){
        QMessageBox::information(this, "提示","您有未完成的题目，请完成");
        return;
    }

    int scores = 0;
    for (int i = 0 ; i < 10; i ++ ){
        //单选题计分
        if (i < 8)
            if (m_btnGroups[i]->checkedButton()->text() == m_answerList.at(i))
                scores += 10;
         //多选题计分
        if (i == 8){
            QString answer = m_answerList.at(i);
            bool hasA = false;
            bool hasB = false;
            bool hasC = false;
            bool hasD = false;

            if ( answer.contains("A") ) hasA = true;
            if ( answer.contains("B") ) hasB = true;
            if ( answer.contains("C") ) hasC = true;
            if ( answer.contains("D") ) hasD = true;

            bool checkA = m_checkBtns[0]->checkState();
            bool checkB = m_checkBtns[1]->checkState();
            bool checkC = m_checkBtns[2]->checkState();
            bool checkD = m_checkBtns[3]->checkState();

            if ( hasA != checkA) continue;
            if ( hasB != checkB) continue;
            if ( hasC != checkC) continue;
            if ( hasD != checkD) continue;

            scores += 10;
        }
        //判断题计分
        if (i == 9){
            if (m_btnGroups[8]->checkedButton()->text() == m_answerList.at(i))
                scores += 10;
        }
    }
    int res = QMessageBox::information(this, "提示", "您的分数是：" + QString::number(scores) + "分，是否重新考试？", QMessageBox::Yes | QMessageBox::No);
    if (res == QMessageBox::Yes)
        return;
    else
        close();
}
