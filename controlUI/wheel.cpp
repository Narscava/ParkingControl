//
// Created by Seayn on 2019/3/11.
//
#include "wheel.h"

Wheel::Wheel() {type=-1;return ;}

Wheel::Wheel(int type_, double biasLong_, double biasLa_)
{
    type=type_;
    biasLa=biasLa_;
    biasLong=biasLong_;
    return ;
}
Wheel::~Wheel()
{

}
void Wheel::updateLongAndLaWithBiasValueAndDirection(double direction,double lo_,double la_)
{
    longt=0;
    lat=0;
}
