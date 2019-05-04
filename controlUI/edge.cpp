//
// Created by Seayn on 2019/3/17.
//

#include "edge.h"
Edge::Edge()
{
    type=-1;
}
Edge::Edge(int type_, double biasLong_, double biasLa_)
{
    type=type_;
    biasLa=biasLa_;
    biasLong=biasLong_;
}

Edge::~Edge()
{

}

void Edge::updateLongAndLaWithBiasValueAndDirection(double direction, double lo_, double la_)
{

}