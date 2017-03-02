#ifndef TOOLBOX1_H
#define TOOLBOX1_H

#include <QToolBox>
#include <QToolButton>
#include <QEvent>
#include <QTcpSocket>

#include "widget.h"

#define CLINETCOUNT 256 //���ͻ�������
#define MSGBODYBUF 1024

//������Ϣ�ṹ
struct msg_t
{
    unsigned char head[4];
    char body[MSGBODYBUF];
};


class toolbox1 : public QToolBox
{
    Q_OBJECT
public:
    explicit toolbox1(QWidget *parent = 0);
    void send_Msg(int d_userid, const char *msgBody);//����server��send��Ϣ

signals:

public slots:
    bool eventFilter(QObject *watched, QEvent *event);
private:
    int userid;
    QString passwd;
    QString hostip;
    int hostport;

    QString username[CLINETCOUNT];
    QToolButton *toolBtn[CLINETCOUNT];
    Widget *child[CLINETCOUNT];


    void init_toolBtn();
    void init_username();

    QTcpSocket *sockClient;
    void login_Msg();

    void recv_send_Msg(int o_userid, const char *msgBody);//����server����Ϣ
    void userStatus_Msg(const char *msgBody);//����server��deliver��Ϣ

    void system_Msg(int msgcode);//����server����Ϣ


private slots:
    void sock_Error(QAbstractSocket::SocketError sockErr);//socket�����ʱ�򴥷��Ĳۺ���
    void read_Msg();//socket���յ���Ϣ�����Ĳۺ���
    void socket_connected();//socket�ɹ����ӵ�����˺󴥷��Ĳۺ���


};

#endif // TOOLBOX1_H
