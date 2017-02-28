#ifndef TOOLBOX1_H
#define TOOLBOX1_H

#include <QToolBox>
#include <QToolButton>
#include <QEvent>
#include <QTcpSocket>

#include "widget.h"

#define CLINETCOUNT 256 //最大客户端数量

class toolbox1 : public QToolBox
{
    Q_OBJECT
public:
    explicit toolbox1(QWidget *parent = 0);

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

private slots:
    void sock_Error(QAbstractSocket::SocketError sockErr);//socket�����ʱ�򴥷��Ĳۺ���
    void read_Msg();//socket���յ���Ϣ�����Ĳۺ���
    void socket_connected();//socket�ɹ����ӵ�����˺󴥷��Ĳۺ���


};

#endif // TOOLBOX1_H
