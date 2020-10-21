#ifndef C_PLOT1_H
#define C_PLOT1_H

#include "plot.h"
class CPlot1: public Plot
{
  Q_OBJECT;
public:
  explicit CPlot1(QWidget *pParent = nullptr);
}; 

#endif //!C_PLOT1_H