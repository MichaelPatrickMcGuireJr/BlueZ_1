#include <stdio.h>
#include <unistd.h>
#include <QBluetoothServer>


#include <QtBluetooth/qbluetoothhostinfo.h>
#include <QtBluetooth/qbluetoothlocaldevice.h>
#include <QtBluetooth/qbluetoothserver.h>
#include <QtBluetooth/qbluetoothsocket.h>
#include <QtBluetooth/qbluetoothaddress.h>
#include <QtBluetooth/qbluetoothserviceinfo.h>




const QBluetoothAddress &localAdapter = QBluetoothAddress();
static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c8");

#include <QObject>
#include <QtCore/qobject.h>


void clientConnected()
{

}



int main()
{

    //QObject *sender();

    QList<QBluetoothHostInfo> localAdapters;

    localAdapters = QBluetoothLocalDevice::allDevices();

    //QBluetoothServer *rfcommServer = nullptr;

    if (localAdapters.count() > 0)
    {
        localAdapters.at(0).address().toString();
        QBluetoothLocalDevice adapter(localAdapters.at(0).address());
        adapter.setHostMode(QBluetoothLocalDevice::HostDiscoverable);

        //bool result1 = rfcommServer->listen(localAdapter);

        //if (!result1) {
        //    qWarning() << "Cannot bind chat server to" << localAdapter.toString();
        //    return 0;
        //}



        QBluetoothServer *rfcommServer = nullptr;

        bool result2 = rfcommServer->listen(localAdapter);
        if (!result2) {
            qWarning() << "Cannot bind chat server to" << localAdapter.toString();
            return 0;
        }



        QBluetoothServiceInfo::Sequence profileSequence;
        QBluetoothServiceInfo::Sequence classId;
        classId << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::SerialPort));
        classId << QVariant::fromValue(quint16(0x100));
        profileSequence.append(QVariant::fromValue(classId));

        QBluetoothServiceInfo serviceInfo;

        serviceInfo.setAttribute(QBluetoothServiceInfo::BluetoothProfileDescriptorList,
                                 profileSequence);

        classId.clear();
        classId << QVariant::fromValue(QBluetoothUuid(serviceUuid));
        classId << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::SerialPort));

        serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceClassIds, classId);

        //! [Service name, description and provider]
        serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceName, QObject::tr("Bt Chat Server"));
        serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceDescription, QObject::tr("Example bluetooth chat server"));
        serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceProvider, QObject::tr("qt-project.org"));
        //! [Service name, description and provider]

        //! [Service UUID set]
        serviceInfo.setServiceUuid(QBluetoothUuid(serviceUuid));
        //! [Service UUID set]

        //! [Service Discoverability]
        QBluetoothServiceInfo::Sequence publicBrowse;
        publicBrowse << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::PublicBrowseGroup));
        serviceInfo.setAttribute(QBluetoothServiceInfo::BrowseGroupList, publicBrowse);
        //! [Service Discoverability]

        //! [Protocol descriptor list]
        QBluetoothServiceInfo::Sequence protocolDescriptorList;
        QBluetoothServiceInfo::Sequence protocol;
        protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::L2cap));
        protocolDescriptorList.append(QVariant::fromValue(protocol));
        protocol.clear();
        protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::Rfcomm)) << QVariant::fromValue(quint8(rfcommServer->serverPort()));
        protocolDescriptorList.append(QVariant::fromValue(protocol));
        serviceInfo.setAttribute(QBluetoothServiceInfo::ProtocolDescriptorList, protocolDescriptorList);
        //! [Protocol descriptor list]

        //! [Register service]
        serviceInfo.registerService(localAdapter);
        //! [Register service]











    }


    while(1)
    {

        printf("Hello World \n");


        QBluetoothSocket *socket = qobject_cast<QBluetoothSocket *>(QObjecT::sender());
        if (socket)
        {
            while (socket->canReadLine())
            {
                QByteArray line = socket->readLine().trimmed();
                //emit messageReceived(socket->peerName(), QString::fromUtf8(line.constData(), line.length()));
            }
        }


        sleep(1);
    }




    return 0;
}
