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
                QMessageBox::information(this, tr("错误"), tr("无效用户ID号"));
                exit(0);
            }else
            {
                setWindowTitle(username[login.userid]);
                userid = login.userid;
                passwd = login.passwd;
                hostip = login.hostip;
                hostport = login.hostport;

                //根据登录对话框中用户输入的服务器IP和端口号连接到服务器
                sockClient = new QTcpSocket(this);

                connect(sockClient, SIGNAL(error(QAbstractSocket::SocketError)), this,
                               SLOT(sock_Error(QAbstractSocket::SocketError)));//设置socket出错时的槽函数


                connect(sockClient, SIGNAL(readyRead()), this, SLOT(read_Msg()));//设置socket读消息的槽函数
                connect(sockClient, SIGNAL(connected()), this, SLOT(socket_connected()));//设置socket完成连接消息的槽函数


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
        toolBtn[i] = new QToolButton();//new 256个toolbutton
        toolBtn[i]->setObjectName(QString::number(i));//为每个toolbtn设置objectname属性
        toolBtn[i]->installEventFilter(this);//toolbtn的点击事件有toolbox1来处理
        toolBtn[i]->setText(username[i]);//设置toolbttn用户名
        imagename.sprintf(":/images/%d.png", i);
        toolBtn[i]->setIcon(QPixmap(imagename));//设置toolbtn图像
        toolBtn[i]->setIconSize(QPixmap(imagename).size());//设置toolbtn大小和图像一致
        toolBtn[i]->setAutoRaise(true);//设置toolbtn自动浮起界面风格
        toolBtn[i]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置toolbtn文字在图像的旁边
        toolBtn[i]->setToolTip(tr("未知"));//设置toolbtn鼠标提示为未知
        child[i] = new Widget(toolBtn[i]->icon(), i, toolBtn[i]->text(), this);
    }
    QGroupBox *groupBox[8];
    QVBoxLayout *layout[8];
    static int index = 0;
    for(int i = 0; i < 8; i++)
    {
        groupBox[i] = new QGroupBox;
        layout[i] = new QVBoxLayout(groupBox[i]);
        layout[i]->setMargin(10);//设置布局中个窗体的显示间距
        layout[i]->setAlignment(Qt::AlignHCenter);//设置布局中古窗体的位置
        for(int j = 0; j < 32; j++)
        {
            layout[i]->addWidget(toolBtn[index++]);//代表一个layout中加入32个toolbox
        }
        layout[i]->addStretch();//插入一个占位符
    }
    addItem((QWidget *)groupBox[0], tr("好友"));
    addItem((QWidget *)groupBox[1], tr("陌生人"));
    addItem((QWidget *)groupBox[2], tr("家人"));
    addItem((QWidget *)groupBox[3], tr("同学"));
    addItem((QWidget *)groupBox[4], tr("同事"));
    addItem((QWidget *)groupBox[5], tr("网友"));
    addItem((QWidget *)groupBox[6], tr("驴友"));
    addItem((QWidget *)groupBox[7], tr("社区"));

}

void toolbox1::init_username()
{
    for(int i = 0; i < CLINETCOUNT; i++)//将username数组中所有的成员初始化
    {
        username[i] = tr("用户") + QString::number(i);
    }
}

bool toolbox1::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)//如果是鼠标按键信号
        {
            int i = watched->objectName().toInt();
            child[i]->showNormal();//将toolbtn下对应的child显示到屏幕
        }
        return QToolBox::eventFilter(watched, event);//其他信号交给父类进行默认处理
}

void toolbox1::sock_Error(QAbstractSocket::SocketError sockErr)
{
    switch (sockErr)
    {
    case QAbstractSocket::RemoteHostClosedError://如果是远程服务器正常关闭了socket，就直接break
        break;
    default:
        QMessageBox::information(this, tr("错误"), sockClient->errorString());
    }
}

void toolbox1::read_Msg()
{

}

void toolbox1::socket_connected()
{

}
