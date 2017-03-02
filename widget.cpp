#include "widget.h"
#include "toolbox1.h"

#include <QHBoxLayout>
#include <QDateTime>
#include <QScrollBar>
#include <QMessageBox>
#include <QColorDialog>

Widget::Widget(const QIcon icon, int ID, QString name, toolbox1 *w, QWidget *parent)
    : QWidget(parent)
{
    userID = ID;
    username = name;
    main_w = w;
    setWindowTitle(name);
    setWindowIcon(icon);
    //���������С����ť��Ч
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint & ~Qt::WindowMinimizeButtonHint);

    //���ñ�����ɫ
    setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(Qt::darkCyan));
    setPalette(palette);
    init_widget();//��ʼ����صĿؼ�
}

Widget::~Widget()
{

}

void Widget::init_widget()
{
    textBrowser = new QTextBrowser;
        //����textBrowser������ɫ��ͼƬ
        textBrowser->setStyleSheet("background-image: url(:/images/2.jpg);");//��������Ϊ2.jpg
        //textBrowser->setStyleSheet("border-image: url(:/images/2.jpg);");//��������Ϊ2.jpg

        QHBoxLayout *layout1 = new QHBoxLayout;
        layout1->addWidget(textBrowser);

        fontComboBox = new QFontComboBox;
        fontComboBox->setToolTip(tr("����"));

        comboBox = new QComboBox;
        comboBox->setToolTip(tr("�ֺ�"));
        comboBox->setEditable(true);
        comboBox->addItem(QString::number(8));
        comboBox->addItem(QString::number(9));
        comboBox->addItem(QString::number(10));
        comboBox->addItem(QString::number(11));
        comboBox->addItem(QString::number(12));
        comboBox->addItem(QString::number(13));
        comboBox->addItem(QString::number(14));
        comboBox->addItem(QString::number(15));
        comboBox->addItem(QString::number(16));
        comboBox->addItem(QString::number(17));
        comboBox->addItem(QString::number(18));
        comboBox->addItem(QString::number(19));
        comboBox->addItem(QString::number(20));
        comboBox->addItem(QString::number(21));
        comboBox->addItem(QString::number(22));
        comboBox->setCurrentIndex(4);//���õ�ǰ������

        toolButton_1 = new QToolButton;
        toolButton_1->setToolTip(tr("�Ӵ�"));
        toolButton_1->setText(tr("�Ӵ�"));
        toolButton_1->setCheckable(true);
        toolButton_1->setAutoRaise(true);
        toolButton_1->setIcon(QPixmap(":/images/bold.png"));

        toolButton_2 = new QToolButton;
        toolButton_2->setToolTip(tr("��б"));
        toolButton_2->setText(tr("��б"));
        toolButton_2->setCheckable(true);
        toolButton_2->setAutoRaise(true);
        toolButton_2->setIcon(QPixmap(":/images/italic.png"));

        toolButton_3 = new QToolButton;
        toolButton_3->setToolTip(tr("�»���"));
        toolButton_3->setText(tr("�»���"));
        toolButton_3->setCheckable(true);
        toolButton_3->setAutoRaise(true);
        toolButton_3->setIcon(QPixmap(":/images/under.png"));

        toolButton_4 = new QToolButton;
        toolButton_4->setToolTip(tr("��ɫ"));
        toolButton_4->setText(tr("��ɫ"));
        toolButton_4->setAutoRaise(true);
        toolButton_4->setIcon(QPixmap(":/images/color.png"));

        toolButton = new QToolButton;
        toolButton->setText(tr("��ʾ������"));
        toolButton->setAutoRaise(true);

        QHBoxLayout *layout2 = new QHBoxLayout;
        layout2->addWidget(fontComboBox);
        layout2->addWidget(comboBox);
        layout2->addWidget(toolButton_1);
        layout2->addWidget(toolButton_2);
        layout2->addWidget(toolButton_3);
        layout2->addWidget(toolButton_4);
        layout2->addWidget(toolButton);

        lineEdit = new QLineEdit;

        pushButton = new QPushButton;
        pushButton->setText(tr("����"));

        QHBoxLayout *layout3 = new QHBoxLayout;
        layout3->addWidget(lineEdit);
        layout3->addWidget(pushButton);

        QVBoxLayout *mainlayout = new QVBoxLayout;

        mainlayout->addLayout(layout1);
        mainlayout->addLayout(layout2);
        mainlayout->addLayout(layout3);
        //mainlayout->setSizeConstraint(QLayout::SetFixedSize);//���ô��ڴ�С���ܸı�
        setLayout(mainlayout);

        textBrowser->setCurrentFont(fontComboBox->font());//����textBrowser��Ĭ������
        textBrowser->setFontPointSize(comboBox->currentText().toDouble());//����textBrowser��Ĭ���ֺ�
        lineEdit->setFocus();
}

void Widget::add_msg(QString delivername, QString msg)
{
    //�õ���ǰʱ�䣬����ʱ���ʽ��Ϊ"yyy-MM-dd hh:ss:ss"��ʽ���ַ���
    QString sTime = QDateTime::currentDateTime().toString("yyy-MM-dd hh:ss:ss");
    textBrowser->append("[" + delivername + "]" + sTime);
    textBrowser->append(msg);

    //����Ϣtextbrowser����Ϣ������ֹ��������Զ����������·�
    textBrowser->verticalScrollBar()->setValue(textBrowser->verticalScrollBar()->maximum());
}

void Widget::on_pushButton_clicked()
{
    if(lineEdit->text().isEmpty())//���lineEdit�ؼ�����Ϊ�գ���ʾ�û����ܷ��Ϳ���Ϣ
    {
        QMessageBox::information(this, tr("ע��"), tr("���ܷ��Ϳ���Ϣ"));
    }else
    {
        add_msg(tr("�ҵ���Ϣ"), lineEdit->text());
         main_w->send_Msg(userID, lineEdit->text().toStdString().data());//���������ڵ�send_Msg��������������ύsend��Ϣ
         lineEdit->clear();//������ɺ󣬽�lineEdit�ؼ��������
    }
    lineEdit->setFocus();
}

void Widget::on_fontComboxBox_currentFontChanged(const QFont &f)//�޸�textBrowser����
{
    textBrowser->setCurrentFont(f);
    textBrowser->setFontPointSize(comboBox->currentText().toDouble());
    if(toolButton_1->isChecked())
    {
        textBrowser->setFontWeight(QFont::Bold);
    }
    else
        {
            textBrowser->setFontWeight(QFont::Normal);
        }

        if(toolButton_2->isChecked())
        {
            textBrowser->setFontItalic(true);
        }
        else
        {
            textBrowser->setFontItalic(false);
        }

        if(toolButton_3->isChecked())
        {
            textBrowser->setFontUnderline(true);
        }
        else
        {
            textBrowser->setFontUnderline(false);
        }

        textBrowser->setTextColor(color);
        lineEdit->setFocus();
}

void Widget::on_comboBox_currentIndexChanged(const QString &arg1)//�޸�textBrowser�ֺ�
{
    textBrowser->setFontPointSize(arg1.toDouble());
    lineEdit->setFocus();
}

void Widget::on_toolButton_1_clicked(bool checked)//�޸�textBroer���Ƿ�Ӵ�
{
    if(checked)
    {
        textBrowser->setFontWeight(QFont::Bold);
    }
    else
    {
        textBrowser->setFontWeight(QFont::Normal);
    }
    lineEdit->setFocus();
}

void Widget::on_toolButton_2_clicked(bool checked)//�޸�textBroer���Ƿ�б��
{
    textBrowser->setFontItalic(checked);
    lineEdit->setFocus();
}

void Widget::on_toolButton_3_clicked(bool checked)//�޸�textBroer���Ƿ��»���
{
    textBrowser->setFontUnderline(checked);
    lineEdit->setFocus();
}

void Widget::on_toolButton_4_clicked()//�޸�textBroer������ɫ
{
    color = QColorDialog::getColor(color,this);
    if(color.isValid())
    {
        textBrowser->setTextColor(color);
        lineEdit->setFocus();
    }
}

void Widget::on_toolButton_clicked()//
{
    main_w->hide();
    main_w->showNormal();
}

void Widget::on_lineEdit_returnPressed()
{
    if (pushButton->isEnabled())//���pushButtonû�б�ң���ô�Ϳ��Ե���on_pushButton_clicked()����
        on_pushButton_clicked();
}
