#ifndef TOOLBOX1_H
#define TOOLBOX1_H

#include <QToolBox>
#include <QToolButton>
#include <QEvent>
#include <QTcpSocket>

#include "widget.h"

#define CLINETCOUNT 256 //鏈�澶у鎴风鏁伴噺

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
    void sock_Error(QAbstractSocket::SocketError sockErr);//socket出错的时候触发的槽函数
    void read_Msg();//socket接收到消息触发的槽函数
    void socket_connected();//socket成功连接到服务端后触发的槽函数


};

#endif // TOOLBOX1_H
