#ifndef _PLOT_H_
#define _PLOT_H_ 1

#include <cmath>
#include <qmath.h>
#include <qwt_plot.h>
#include <qglobal.h>
#include <qwt_system_clock.h>
#include "settings.h"

class QwtPlotGrid;
class QwtPlotCurve;

class Plot: public QwtPlot
{
    Q_OBJECT

public:
    Plot( QWidget* = NULL );

public Q_SLOTS:
    virtual void setSettings( const Settings & );

protected:
    virtual void timerEvent( QTimerEvent *e );

    void alignScales();

    QwtPlotGrid *d_grid;
    QwtPlotCurve *d_curve;

    QwtSystemClock d_clock;
    double d_interval;

    int d_timerId;

    Settings d_settings;
};

static double wave( double x )
{
    const double period = 1.0;
    const double c = 5.0;

    double v = ::fmod( x, period );

    const double amplitude = qAbs( x - qRound( x / c ) * c ) / ( 0.5 * c );
    v = amplitude * qSin( v / period * 2 * M_PI );

    return v;
}

static double noise( double )
{
    return 2.0 * ( qrand() / ( static_cast<double>( RAND_MAX ) + 1 ) ) - 1.0;
}



#endif
