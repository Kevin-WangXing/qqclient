#include "logindlg.h"

#include <QGridLayout>
#include <QMessageBox>

loginDlg::loginDlg(QWidget *parent) :
    QDialog(parent)
{
    lable0 = new QLabel;
        lable0->setText(tr("�û�ID"));
        lineEditUserID = new QLineEdit;

        lable1 = new QLabel;
        lable1->setText(tr("����"));
        lineEditPasswd = new QLineEdit;
        lineEditPasswd->setEchoMode(QLineEdit::Password);//����Ϊ�����

        lable2 = new QLabel;
        lable2->setText(tr("������IP"));
        lineEditHostIP = new QLineEdit;

        lable3 = new QLabel;
        lable3->setText(tr("�������˿ں�"));
        lineEditHostport = new QLineEdit;


        loginBtn = new QPushButton;
        loginBtn->setText(tr("��¼"));
        logoutBtn = new QPushButton;
        logoutBtn->setText(tr("ȡ��"));


        QGridLayout *layout1 = new QGridLayout(this);
        layout1->addWidget(lable0, 0, 0);
        layout1->addWidget(lineEditUserID, 0, 1);

        layout1->addWidget(lable1, 1, 0);
        layout1->addWidget(lineEditPasswd, 1, 1);

        layout1->addWidget(lable2, 2, 0);
        layout1->addWidget(lineEditHostIP, 2, 1);

        layout1->addWidget(lable3, 3, 0);
        layout1->addWidget(lineEditHostport, 3, 1);

        layout1->addWidget(loginBtn, 4, 0);
        layout1->addWidget(logoutBtn, 4, 1);

        layout1->setColumnStretch(0, 1);
        layout1->setColumnStretch(1, 1);

        layout1->setMargin(15);
        layout1->setSpacing(10);
        layout1->setSizeConstraint(QLayout::SetFixedSize);

        connect(loginBtn,SIGNAL(clicked()), this, SLOT(loginBtnOnclick()));
        connect(logoutBtn,SIGNAL(clicked()), this, SLOT(logoutBtnOnclick()));

        islogin = false;

        setWindowIcon(QPixmap(":/images/3.png"));//���ô���ͼ��

        lineEditUserID->setFocus();//����lineEditUserID�ؼ��������뽹��

        //���ô���û�б߿�
        setWindowFlags(Qt::FramelessWindowHint);

        //���öԻ��򱳾���ɫ��ͼƬ
        setAutoFillBackground(true);
        QPalette palette;
        //palette.setColor(QPalette::Background, QColor(Qt::blue));
        palette.setBrush(QPalette::Background, QBrush(QPixmap(":/images/1.jpg")));
        setPalette(palette);
}
void loginDlg::loginBtnOnclick()
{
    if (lineEditUserID->text().isEmpty())
    {
        QMessageBox::information(this, tr("����"), tr("�û�ID����Ϊ��"));
        lineEditUserID->setFocus();
    }else
    {
        bool ok;
        userid = lineEditUserID->text().toInt(&ok);
        if (!ok)
        {
            QMessageBox::information(this, tr("����"), tr("�û�ID�����Ǵ�0��255������"));
            lineEditUserID->setFocus();
        }else
        {
            islogin = true;
            passwd = lineEditPasswd->text();
            hostip = lineEditHostIP->text();
            hostport = lineEditHostport->text().toInt();
            close();
        }
    }
}

void loginDlg::logoutBtnOnclick()
{
    close();
}
