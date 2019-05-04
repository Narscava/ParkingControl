#ifndef CONTROLSERIALPORTCOMMUNICATION_H
#define CONTROLSERIALPORTCOMMUNICATION_H
#include "TinyCarCommunication.h"
class OrderCommutication
{
public:
    TinyCarCommunication * tinyCarCommunication;
    OrderCommutication()
    {
        tinyCarCommunication=new TinyCarCommunication();
    }
    ~OrderCommutication()
    {
        delete tinyCarCommunication;
    }
    void sendCommand(char * str)
    {
        tinyCarCommunication->sendMessage(str);
    }

};



#endif // CONTROLSERIALPORTCOMMUNICATION_H
