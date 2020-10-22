#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <qmainwindow.h>

class Plot;
class Panel;
class QLabel;
class Settings;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *pParent = nullptr);
  virtual bool eventFilter(QObject *, QEvent *) override;

private Q_SLOTS:
  void applySettings(const Settings &);

private:
  // Plot *d_plot;
  QList<Plot *> mPlots;
  Panel *d_panel;
  QLabel *d_frameCount;
};

#endif
