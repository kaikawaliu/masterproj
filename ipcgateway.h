#ifndef IPCGATEWAY_H
#define IPCGATEWAY_H

#include <QObject>

class IPCGateway : public QObject
{
    Q_OBJECT
public:
    explicit IPCGateway(QObject *parent = nullptr);

signals:

public slots:
};

#endif // IPCGATEWAY_H