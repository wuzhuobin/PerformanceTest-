#ifndef C_PLOT2_H
#define C_PLOT2_H

#include "plot.h"

class CPlot2: public Plot
{
  Q_OBJECT;
public:
  CPlot2(QWidget *pParent = nullptr);

public Q_SLOTS:
  virtual void setSettings(const Settings & rSettings) override;

protected:
  virtual void timerEvent(QTimerEvent *pEvent) override;
  QwtPlotCurve *mpCurve;
};

#endif //!C_PLOT2_H