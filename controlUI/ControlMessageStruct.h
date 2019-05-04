#ifndef CONTROLMESSAGESTRUCT_H
#define CONTROLMESSAGESTRUCT_H
#define MESSAGETYPE_GPS 1
#define MESSAGETYPE_CV 2
struct ControlMessageStruct
{
    unsigned char id;
    double distance;
    double time;
    ControlMessageStruct(unsigned char id,double distance,double time):
        id(id),distance(distance),time(time) {}
};
#endif // CONTROLMESSAGESTRUCT_H
