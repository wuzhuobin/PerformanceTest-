#include "CPlot1.h"

CPlot1::CPlot1(QWidget *pParent): Plot(pParent)
{
  this->setTitle(QString());
  this->setFooter(QString());
  this->enableAxis(xTop, false);
  this->enableAxis(xBottom, false);
  this->enableAxis(yLeft, false);
  this->enableAxis(yRight, false);
}