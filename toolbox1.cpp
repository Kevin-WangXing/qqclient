#include "toolbox1.h"
#include "logindlg.h"
#include <QIcon>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QTextCodec>
#include <QHostAddress>
#include <QMessageBox>

toolbox1::toolbox1(QWidget *parent) :
    QToolBox(parent)
{
    QTextCodec *codec = QTextCodec::codecForName("system");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

    setWindowIcon(QPixmap(":/images/3.png"));
    init_username();
    init_toolBtn();

    loginDlg login;
    login.exec();

    if (login.islogin)
        {
            if ((login.userid < 0) || (login.userid > 255))
            {
                QMessageBox::information(this, tr("����"), tr("��Ч�û�ID��"));
                exit(0);
            }else
            {
                setWindowTitle(username[login.userid]);
                userid = login.userid;
                passwd = login.passwd;
                hostip = login.hostip;
                hostport = login.hostport;

                //���ݵ�¼�Ի������û�����ķ�����IP�Ͷ˿ں����ӵ�������
                sockClient = new QTcpSocket(this);

                connect(sockClient, SIGNAL(error(QAbstractSocket::SocketError)), this,
                               SLOT(sock_Error(QAbstractSocket::SocketError)));//����socket����ʱ�Ĳۺ���


                connect(sockClient, SIGNAL(readyRead()), this, SLOT(read_Msg()));//����socket����Ϣ�Ĳۺ���
                connect(sockClient, SIGNAL(connected()), this, SLOT(socket_connected()));//����socket���������Ϣ�Ĳۺ���


                QHostAddress hostAddr(hostip);
                sockClient->connectToHost(hostAddr, hostport);
            }
        }else
        {
            exit(0);
        }
}

void toolbox1::init_toolBtn()
{
    QString imagename;
    for(int i = 0; i < CLINETCOUNT; i++)
    {
        toolBtn[i] = new QToolButton();//new 256��toolbutton
        toolBtn[i]->setObjectName(QString::number(i));//Ϊÿ��toolbtn����objectname����
        toolBtn[i]->installEventFilter(this);//toolbtn�ĵ���¼���toolbox1������
        toolBtn[i]->setText(username[i]);//����toolbttn�û���
        imagename.sprintf(":/images/%d.png", i);
        toolBtn[i]->setIcon(QPixmap(imagename));//����toolbtnͼ��
        toolBtn[i]->setIconSize(QPixmap(imagename).size());//����toolbtn��С��ͼ��һ��
        toolBtn[i]->setAutoRaise(true);//����toolbtn�Զ����������
        toolBtn[i]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//����toolbtn������ͼ����Ա�
        toolBtn[i]->setToolTip(tr("δ֪"));//����toolbtn�����ʾΪδ֪
        child[i] = new Widget(toolBtn[i]->icon(), i, toolBtn[i]->text(), this);
    }
    QGroupBox *groupBox[8];
    QVBoxLayout *layout[8];
    static int index = 0;
    for(int i = 0; i < 8; i++)
    {
        groupBox[i] = new QGroupBox;
        layout[i] = new QVBoxLayout(groupBox[i]);
        layout[i]->setMargin(10);//���ò����и��������ʾ���
        layout[i]->setAlignment(Qt::AlignHCenter);//���ò����йŴ����λ��
        for(int j = 0; j < 32; j++)
        {
            layout[i]->addWidget(toolBtn[index++]);//����һ��layout�м���32��toolbox
        }
        layout[i]->addStretch();//����һ��ռλ��
    }
    addItem((QWidget *)groupBox[0], tr("����"));
    addItem((QWidget *)groupBox[1], tr("İ����"));
    addItem((QWidget *)groupBox[2], tr("����"));
    addItem((QWidget *)groupBox[3], tr("ͬѧ"));
    addItem((QWidget *)groupBox[4], tr("ͬ��"));
    addItem((QWidget *)groupBox[5], tr("����"));
    addItem((QWidget *)groupBox[6], tr("¿��"));
    addItem((QWidget *)groupBox[7], tr("����"));

}

void toolbox1::init_username()
{
    for(int i = 0; i < CLINETCOUNT; i++)//��username���������еĳ�Ա��ʼ��
    {
        username[i] = tr("�û�") + QString::number(i);
    }
}

bool toolbox1::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)//�������갴���ź�
        {
            int i = watched->objectName().toInt();
            child[i]->showNormal();//��toolbtn�¶�Ӧ��child��ʾ����Ļ
        }
        return QToolBox::eventFilter(watched, event);//�����źŽ����������Ĭ�ϴ���
}

void toolbox1::sock_Error(QAbstractSocket::SocketError sockErr)
{
    switch (sockErr)
    {
    case QAbstractSocket::RemoteHostClosedError://�����Զ�̷����������ر���socket����ֱ��break
        break;
    default:
        QMessageBox::information(this, tr("����"), sockClient->errorString());
    }
}

void toolbox1::read_Msg()
{

}

void toolbox1::socket_connected()
{

}
