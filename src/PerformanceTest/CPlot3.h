#ifndef C_PLOT3_H
#define C_PLOT3_H

#include "plot.h"
class CPlot3: public Plot
{
  Q_OBJECT;
public:
  explicit CPlot3(QWidget *pParent = nullptr);

public Q_SLOTS:
  virtual void setSettings(const Settings & rSettings);

protected:
  virtual void timerEvent(QTimerEvent *pEvent) override;
};

#endif //!C_PLOT3_H