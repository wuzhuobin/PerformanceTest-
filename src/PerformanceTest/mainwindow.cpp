#include <qstatusbar.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qevent.h>
#include <qdatetime.h>
#include <qwt_plot_canvas.h>
#include "panel.h"
#include "mainwindow.h"
#include "CPlot2.h"
#include "CPlot1.h"
#include "CPlot3.h"

static const int NUM_OF_WAVE = 24;
MainWindow::MainWindow( QWidget *parent ):
    QMainWindow( parent )
{
    QWidget *w = new QWidget( this );

    d_panel = new Panel( w );

    // d_plot = new Plot( w );
    for (int i = 0; i < NUM_OF_WAVE; ++i)
    {
        // (i % 2 == 0) ? this->mPlots << new Plot(w) : this->mPlots << new CPlot2(w);
        this->mPlots << new CPlot2(w);
        // this->mPlots << new CPlot3(w);
        // this->mPlots << new CPlot1(w);
    }

    QHBoxLayout *hLayout = new QHBoxLayout( w );
    hLayout->addWidget( d_panel );
    QGridLayout *pGridLayout = new QGridLayout();
    pGridLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->addLayout(pGridLayout, 2);
    for(int i = 0; i < this->mPlots.size(); ++i)
    {
      this->mPlots[i]->setMaximumHeight(this->height() / this->mPlots.size() * 2);
      pGridLayout->addWidget(this->mPlots[i], i / 2, i % 2);
    }

    setCentralWidget( w );

    d_frameCount = new QLabel( this );
    statusBar()->addWidget( d_frameCount, 10 );

    applySettings( d_panel->settings() );

    connect( d_panel, SIGNAL( settingsChanged( const Settings & ) ),
        this, SLOT( applySettings( const Settings & ) ) );
}

bool MainWindow::eventFilter( QObject *object, QEvent *event )
{
    if ( object == this->mPlots.first()->canvas() && event->type() == QEvent::Paint )
    {
        static int counter;
        static QTime timeStamp;

        if ( !timeStamp.isValid() )
        {
            timeStamp.start();
            counter = 0;
        }
        else
        {
            counter++;

            const double elapsed = timeStamp.elapsed() / 1000.0;
            if ( elapsed >= 1 )
            {
                QString fps;
                fps.setNum( qRound( counter / elapsed ) );
                fps += " Fps";

                d_frameCount->setText( fps );

                counter = 0;
                timeStamp.start();
            }
        }
    }

    return QMainWindow::eventFilter( object, event );
}

void MainWindow::applySettings( const Settings &settings )
{
    for(Plot *pPlot: this->mPlots)
    {
        pPlot->setSettings(settings);

        // the canvas might have been recreated
        pPlot->canvas()->removeEventFilter(this);
        pPlot->canvas()->installEventFilter(this);
    }
}
