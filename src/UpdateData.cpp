#include "UpdateData.h"

UpdateData::UpdateData()
{

}

UpdateData::~UpdateData()
{
    //dtor
}

void UpdateData::setPlayer(Player* p) const
{
    this->player = p;
}
