#ifndef C_PLOT3_H
#define C_PLOT3_H

#include "plot.h"
// qwt
class QwtPlotDirectPainter;
class CPlot3: public Plot
{
  Q_OBJECT;
public:
  explicit CPlot3(QWidget *pParent = nullptr);


protected:
  virtual void timerEvent(QTimerEvent *pEvent) override;

};

#endif //!C_PLOT3_H