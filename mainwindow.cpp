/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011-2018 Emanuel Eichhammer                            **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.qcustomplot.com/                          **
**             Date: 25.06.18                                             **
**          Version: 2.0.1                                                **
****************************************************************************/

/************************************************************************************************************
**                                                                                                         **
**  This is the example code for QCustomPlot.                                                              **
**                                                                                                         **
**  It demonstrates basic and some advanced capabilities of the widget. The interesting code is inside     **
**  the "setup(...)Demo" functions of MainWindow.                                                          **
**                                                                                                         **
**  In order to see a demo in action, call the respective "setup(...)Demo" function inside the             **
**  MainWindow constructor. Alternatively you may call setupDemo(i) where i is the index of the demo       **
**  you want (for those, see MainWindow constructor comments). All other functions here are merely a       **
**  way to easily create screenshots of all demos for the website. I.e. a timer is set to successively     **
**  setup all the demos and make a screenshot of the window area and save it in the ./screenshots          **
**  directory.                                                                                             **
**                                                                                                         **
*************************************************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QRandomGenerator>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <bitset>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(200, 200, 800, 600);

    _loGrid = new QGridLayout;

    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollAreaWidgetContents->setLayout(_loGrid);

    setupDemo(false);
}

void MainWindow::setupDemo(bool openGl)
{
    setupQuadraticDemo(0,0, openGl);
    setupSimpleDemo(0,1, openGl);
    setupSincScatterDemo(1,0, openGl);
    setupScatterStyleDemo(1,1, openGl);
    setupScatterPixmapDemo(2,0, openGl);
    setupLineStyleDemo(2,1, openGl);
    setupDateDemo(3,0, openGl);
    setupTextureBrushDemo(3,1, openGl);
    setupMultiAxisDemo(4,0, openGl);
    setupLogarithmicDemo(4,1, openGl);
    setupParametricCurveDemo(5,0, openGl);
    setupBarChartDemo(5,1, openGl);
    setupStatisticalDemo(6,0, openGl);
    setupSimpleItemDemo(6,1, openGl);
    setupStyledDemo(7,0, openGl);
    setupAdvancedAxesDemo(7,1, openGl);
    setupColorMapDemo(8,0, openGl);
    setupFinancialDemo(8,1, openGl);
    setupRealtimeDataDemo(9,0, openGl);
    setupRealtimeBrushDemo(9,1, openGl);
    setupRealtimeThresholdDemo(10,0, openGl);
    setupRealtimeEcgDemo(10,1, openGl);
    setupItemDemo(11,0, openGl);
    setupHistoryDemo(11,1, openGl);
    setupAxisTagDemo(12,0, openGl);
    setupBitFieldDemo(12,1, openGl);

    setWindowTitle("QCustomPlot Examples");
}

void MainWindow::setupQuadraticDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Quadratic Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
        x[i] = i/50.0 - 1; // x goes from -1 to 1
        y[i] = x[i]*x[i];  // let's plot a quadratic function
    }
    // create graph and assign data to it:
    plot->addGraph();
    plot->graph(0)->setData(x, y);
    // give the axes some labels:
    plot->xAxis->setLabel("x");
    plot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    plot->xAxis->setRange(-1, 1);
    plot->yAxis->setRange(0, 1);

    plot->replot();
}

void MainWindow::setupSimpleDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Simple Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);

    // add two new graphs and set their look:
    plot->addGraph();
    plot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    QLinearGradient gradient(1000, 0, 0, 0);
    gradient.setColorAt(0, QColor::fromRgbF(0, 1, 0, 1));
    gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));

    QBrush brush(gradient);
    plot->graph(0)->setBrush(brush); // first graph will be filled with translucent blue
    plot->addGraph();
    plot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    // generate some points of data (y0 for first, y1 for second graph):
    QVector<double> x(251), y0(251), y1(251);
    for (int i=0; i<251; ++i)
    {
        x[i] = i;
        y0[i] = qExp(i/150.0)*qCos(i/10.0); // exponentially decaying cosine
        y1[i] = qExp(i/150.0);              // exponential envelope
    }
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    plot->xAxis2->setVisible(true);
    plot->xAxis2->setTickLabels(false);
    plot->yAxis2->setVisible(true);
    plot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    plot->graph(0)->setData(x, y0);
    plot->graph(1)->setData(x, y1);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    plot->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    plot->graph(1)->rescaleAxes(true);
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    plot->replot();
}

void MainWindow::setupSincScatterDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Sinc Scatter Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);

    plot->legend->setVisible(true);
    plot->legend->setFont(QFont("Helvetica",9));
    // set locale to english, so we get english decimal separator:
    plot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    // add confidence band graphs:
    plot->addGraph();
    QPen pen;
    pen.setStyle(Qt::DotLine);
    pen.setWidth(1);
    pen.setColor(QColor(180,180,180));
    plot->graph(0)->setName("Confidence Band 68%");
    plot->graph(0)->setPen(pen);
    plot->graph(0)->setBrush(QBrush(QColor(255,50,30,20)));
    plot->addGraph();
    plot->legend->removeItem(plot->legend->itemCount()-1); // don't show two confidence band graphs in legend
    plot->graph(1)->setPen(pen);
    plot->graph(0)->setChannelFillGraph(plot->graph(1));
    // add theory curve graph:
    plot->addGraph();
    pen.setStyle(Qt::DashLine);
    pen.setWidth(2);
    pen.setColor(Qt::red);
    plot->graph(2)->setPen(pen);
    plot->graph(2)->setName("Theory Curve");
    // add data point graph:
    plot->addGraph();
    plot->graph(3)->setPen(QPen(Qt::blue));
    plot->graph(3)->setLineStyle(QCPGraph::lsNone);
    plot->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
    // add error bars:
    QCPErrorBars *errorBars = new QCPErrorBars(plot->xAxis, plot->yAxis);
    errorBars->removeFromLegend();
    errorBars->setAntialiased(false);
    errorBars->setDataPlottable(plot->graph(3));
    errorBars->setPen(QPen(QColor(180,180,180)));
    plot->graph(3)->setName("Measurement");

    // generate ideal sinc curve data and some randomly perturbed data for scatter plot:
    QVector<double> x0(250), y0(250);
    QVector<double> yConfUpper(250), yConfLower(250);
    for (int i=0; i<250; ++i)
    {
        x0[i] = (i/249.0-0.5)*30+0.01; // by adding a small offset we make sure not do divide by zero in next code line
        y0[i] = qSin(x0[i])/x0[i]; // sinc function
        yConfUpper[i] = y0[i]+0.15;
        yConfLower[i] = y0[i]-0.15;
        x0[i] *= 1000;
    }
    QVector<double> x1(50), y1(50), y1err(50);
    for (int i=0; i<50; ++i)
    {
        // generate a gaussian distributed random number:
        double tmp1 = rand()/(double)RAND_MAX;
        double tmp2 = rand()/(double)RAND_MAX;
        double r = qSqrt(-2*qLn(tmp1))*qCos(2*M_PI*tmp2); // box-muller transform for gaussian distribution
        // set y1 to value of y0 plus a random gaussian pertubation:
        x1[i] = (i/50.0-0.5)*30+0.25;
        y1[i] = qSin(x1[i])/x1[i]+r*0.15;
        x1[i] *= 1000;
        y1err[i] = 0.15;
    }
    // pass data to graphs and let QCustomPlot determine the axes ranges so the whole thing is visible:
    plot->graph(0)->setData(x0, yConfUpper);
    plot->graph(1)->setData(x0, yConfLower);
    plot->graph(2)->setData(x0, y0);
    plot->graph(3)->setData(x1, y1);
    errorBars->setData(y1err);
    plot->graph(2)->rescaleAxes();
    plot->graph(3)->rescaleAxes(true);
    // setup look of bottom tick labels:
    plot->xAxis->setTickLabelRotation(30);
    plot->xAxis->ticker()->setTickCount(9);
    plot->xAxis->setNumberFormat("ebc");
    plot->xAxis->setNumberPrecision(1);
    plot->xAxis->moveRange(-10);
    // make top right axes clones of bottom left axes. Looks prettier:
    plot->axisRect()->setupFullAxesBox();

    plot->replot();
}

void MainWindow::setupScatterStyleDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Scatter Style Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);

    plot->legend->setVisible(true);
    plot->legend->setFont(QFont("Helvetica", 9));
    plot->legend->setRowSpacing(-3);
    QVector<QCPScatterStyle::ScatterShape> shapes;
    shapes << QCPScatterStyle::ssCross;
    shapes << QCPScatterStyle::ssPlus;
    shapes << QCPScatterStyle::ssCircle;
    shapes << QCPScatterStyle::ssDisc;
    shapes << QCPScatterStyle::ssSquare;
    shapes << QCPScatterStyle::ssDiamond;
    shapes << QCPScatterStyle::ssStar;
    shapes << QCPScatterStyle::ssTriangle;
    shapes << QCPScatterStyle::ssTriangleInverted;
    shapes << QCPScatterStyle::ssCrossSquare;
    shapes << QCPScatterStyle::ssPlusSquare;
    shapes << QCPScatterStyle::ssCrossCircle;
    shapes << QCPScatterStyle::ssPlusCircle;
    shapes << QCPScatterStyle::ssPeace;
    shapes << QCPScatterStyle::ssCustom;

    QPen pen;
    // add graphs with different scatter styles:
    for (int i=0; i<shapes.size(); ++i)
    {
        plot->addGraph();
        pen.setColor(QColor(qSin(i*0.3)*100+100, qSin(i*0.6+0.7)*100+100, qSin(i*0.4+0.6)*100+100));
        // generate data:
        QVector<double> x(10), y(10);
        for (int k=0; k<10; ++k)
        {
            x[k] = k/10.0 * 4*3.14 + 0.01;
            y[k] = 7*qSin(x[k])/x[k] + (shapes.size()-i)*5;
        }
        plot->graph()->setData(x, y);
        plot->graph()->rescaleAxes(true);
        plot->graph()->setPen(pen);
        plot->graph()->setName(QCPScatterStyle::staticMetaObject.enumerator(QCPScatterStyle::staticMetaObject.indexOfEnumerator("ScatterShape")).valueToKey(shapes.at(i)));
        plot->graph()->setLineStyle(QCPGraph::lsLine);
        // set scatter style:
        if (shapes.at(i) != QCPScatterStyle::ssCustom)
        {
            plot->graph()->setScatterStyle(QCPScatterStyle(shapes.at(i), 10));
        }
        else
        {
            QPainterPath customScatterPath;
            for (int i=0; i<3; ++i)
                customScatterPath.cubicTo(qCos(2*M_PI*i/3.0)*9, qSin(2*M_PI*i/3.0)*9, qCos(2*M_PI*(i+0.9)/3.0)*9, qSin(2*M_PI*(i+0.9)/3.0)*9, 0, 0);
            plot->graph()->setScatterStyle(QCPScatterStyle(customScatterPath, QPen(Qt::black, 0), QColor(40, 70, 255, 50), 10));
        }
    }
    // set blank axis lines:
    plot->rescaleAxes();
    plot->xAxis->setTicks(false);
    plot->yAxis->setTicks(false);
    plot->xAxis->setTickLabels(false);
    plot->yAxis->setTickLabels(false);
    // make top right axes clones of bottom left axes:
    plot->axisRect()->setupFullAxesBox();

    plot->replot();
}

void MainWindow::setupLineStyleDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Line Style Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);

    plot->legend->setVisible(true);
    plot->legend->setFont(QFont("Helvetica", 9));
    QPen pen;
    QStringList lineNames;
    lineNames << "lsNone" << "lsLine" << "lsStepLeft" << "lsStepRight" << "lsStepCenter" << "lsImpulse";
    // add graphs with different line styles:
    for (int i=QCPGraph::lsNone; i<=QCPGraph::lsImpulse; ++i)
    {
        plot->addGraph();
        pen.setColor(QColor(qSin(i*1+1.2)*80+80, qSin(i*0.3+0)*80+80, qSin(i*0.3+1.5)*80+80));
        plot->graph()->setPen(pen);
        plot->graph()->setName(lineNames.at(i-QCPGraph::lsNone));
        plot->graph()->setLineStyle((QCPGraph::LineStyle)i);
        plot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
        // generate data:
        QVector<double> x(15), y(15);
        for (int j=0; j<15; ++j)
        {
            x[j] = j/15.0 * 5*3.14 + 0.01;
            y[j] = 7*qSin(x[j])/x[j] - (i-QCPGraph::lsNone)*5 + (QCPGraph::lsImpulse)*5 + 2;
        }
        plot->graph()->setData(x, y);
        plot->graph()->rescaleAxes(true);
    }
    // zoom out a bit:
    plot->yAxis->scaleRange(1.1, plot->yAxis->range().center());
    plot->xAxis->scaleRange(1.1, plot->xAxis->range().center());
    // set blank axis lines:
    plot->xAxis->setTicks(false);
    plot->yAxis->setTicks(true);
    plot->xAxis->setTickLabels(false);
    plot->yAxis->setTickLabels(true);
    // make top right axes clones of bottom left axes:
    plot->axisRect()->setupFullAxesBox();

    plot->replot();
}

void MainWindow::setupScatterPixmapDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Scatter Pixmap Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);

    plot->axisRect()->setBackground(QPixmap(":/solarpanels.jpg"));
    plot->addGraph();
    plot->graph()->setLineStyle(QCPGraph::lsLine);
    QPen pen;
    pen.setColor(QColor(255, 200, 20, 200));
    pen.setStyle(Qt::DashLine);
    pen.setWidthF(2.5);
    plot->graph()->setPen(pen);
    plot->graph()->setBrush(QBrush(QColor(255,200,20,70)));
    plot->graph()->setScatterStyle(QCPScatterStyle(QPixmap(":/sun.png")));
    // set graph name, will show up in legend next to icon:
    plot->graph()->setName("Data from Photovoltaic\nenergy barometer 2011");
    // set data:
    QVector<double> year, value;
    year  << 2005 << 2006 << 2007 << 2008  << 2009  << 2010 << 2011;
    value << 2.17 << 3.42 << 4.94 << 10.38 << 15.86 << 29.33 << 52.1;
    plot->graph()->setData(year, value);

    // set title of plot:
    plot->plotLayout()->insertRow(0);
    plot->plotLayout()->addElement(0, 0, new QCPTextElement(plot, "Regenerative Energies", QFont("sans", 12, QFont::Bold)));
    // axis configurations:
    plot->xAxis->setLabel("Year");
    plot->yAxis->setLabel("Installed Gigawatts of\nphotovoltaic in the European Union");
    plot->xAxis2->setVisible(true);
    plot->yAxis2->setVisible(true);
    plot->xAxis2->setTickLabels(false);
    plot->yAxis2->setTickLabels(false);
    plot->xAxis2->setTicks(false);
    plot->yAxis2->setTicks(false);
    plot->xAxis2->setSubTicks(false);
    plot->yAxis2->setSubTicks(false);
    plot->xAxis->setRange(2004.5, 2011.5);
    plot->yAxis->setRange(0, 52);
    // setup legend:
    plot->legend->setFont(QFont(font().family(), 7));
    plot->legend->setIconSize(50, 20);
    plot->legend->setVisible(true);
    plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);
    plot->replot();
}

void MainWindow::setupDateDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Date Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);

    // set locale to english, so we get english month names:
    plot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    // seconds of current time, we'll use it as starting point in time for data:
    double now = QDateTime::currentDateTime().toTime_t();
    srand(8); // set the random seed, so we always get the same random data
    // create multiple graphs:
    for (int gi=0; gi<5; ++gi)
    {
        plot->addGraph();
        QColor color(20+200/4.0*gi,70*(1.6-gi/4.0), 150, 150);
        plot->graph()->setLineStyle(QCPGraph::lsLine);
        plot->graph()->setPen(QPen(color.lighter(200)));
        plot->graph()->setBrush(QBrush(color));
        // generate random walk data:
        QVector<QCPGraphData> timeData(250);
        for (int i=0; i<250; ++i)
        {
            timeData[i].key = now + 24*3600*i;
            if (i == 0)
                timeData[i].value = (i/50.0+1)*(rand()/(double)RAND_MAX-0.5);
            else
                timeData[i].value = qFabs(timeData[i-1].value)*(1+0.02/4.0*(4-gi)) + (i/50.0+1)*(rand()/(double)RAND_MAX-0.5);
        }
        plot->graph()->data()->set(timeData);
    }
    // configure bottom axis to show date instead of number:
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("d. MMMM\nyyyy");
    plot->xAxis->setTicker(dateTicker);
    // configure left axis text labels:
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTick(10, "a bit\nlow");
    textTicker->addTick(50, "quite\nhigh");
    plot->yAxis->setTicker(textTicker);
    // set a more compact font size for bottom and left axis tick labels:
    plot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    plot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    // set axis labels:
    plot->xAxis->setLabel("Date");
    plot->yAxis->setLabel("Random wobbly lines value");
    // make top and right axes visible but without ticks and labels:
    plot->xAxis2->setVisible(true);
    plot->yAxis2->setVisible(true);
    plot->xAxis2->setTicks(false);
    plot->yAxis2->setTicks(false);
    plot->xAxis2->setTickLabels(false);
    plot->yAxis2->setTickLabels(false);
    // set axis ranges to show all data:
    plot->xAxis->setRange(now, now+24*3600*249);
    plot->yAxis->setRange(0, 60);
    // show legend with slightly transparent background brush:
    plot->legend->setVisible(true);
    plot->legend->setBrush(QColor(255, 255, 255, 150));

    plot->replot();
}

void MainWindow::setupTextureBrushDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Texture Brush Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);

    // add two graphs with a textured fill:
    plot->addGraph();
    QPen redDotPen;
    redDotPen.setStyle(Qt::DotLine);
    redDotPen.setColor(QColor(170, 100, 100, 180));
    redDotPen.setWidthF(2);
    plot->graph(0)->setPen(redDotPen);
    plot->graph(0)->setBrush(QBrush(QPixmap(":/balboa.jpg"))); // fill with texture of specified image

    plot->addGraph();
    plot->graph(1)->setPen(QPen(Qt::red));

    // activate channel fill for graph 0 towards graph 1:
    plot->graph(0)->setChannelFillGraph(plot->graph(1));

    // generate data:
    QVector<double> x(250);
    QVector<double> y0(250), y1(250);
    for (int i=0; i<250; ++i)
    {
        // just playing with numbers, not much to learn here
        x[i] = 3*i/250.0;
        y0[i] = 1+qExp(-x[i]*x[i]*0.8)*(x[i]*x[i]+x[i]);
        y1[i] = 1-qExp(-x[i]*x[i]*0.4)*(x[i]*x[i])*0.1;
    }

    // pass data points to graphs:
    plot->graph(0)->setData(x, y0);
    plot->graph(1)->setData(x, y1);
    // activate top and right axes, which are invisible by default:
    plot->xAxis2->setVisible(true);
    plot->yAxis2->setVisible(true);
    // make tick labels invisible on top and right axis:
    plot->xAxis2->setTickLabels(false);
    plot->yAxis2->setTickLabels(false);
    // set ranges:
    plot->xAxis->setRange(0, 2.5);
    plot->yAxis->setRange(0.9, 1.6);
    // assign top/right axes same properties as bottom/left:
    plot->axisRect()->setupFullAxesBox();
}

void MainWindow::setupMultiAxisDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Multi Axis Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    plot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom)); // period as decimal separator and comma as thousand separator
    plot->legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    plot->legend->setFont(legendFont);
    plot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
    plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);

    // setup for graph 0: key axis left, value axis bottom
    // will contain left maxwell-like function
    plot->addGraph(plot->yAxis, plot->xAxis);
    plot->graph(0)->setPen(QPen(QColor(255, 100, 0)));
    plot->graph(0)->setBrush(QBrush(QPixmap(":/balboa.jpg"))); // fill with texture of specified image
    plot->graph(0)->setLineStyle(QCPGraph::lsLine);
    plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    plot->graph(0)->setName("Left maxwell function");

    // setup for graph 1: key axis bottom, value axis left (those are the default axes)
    // will contain bottom maxwell-like function with error bars
    plot->addGraph();
    plot->graph(1)->setPen(QPen(Qt::red));
    plot->graph(1)->setBrush(QBrush(QPixmap("./balboa.jpg"))); // same fill as we used for graph 0
    plot->graph(1)->setLineStyle(QCPGraph::lsStepCenter);
    plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, Qt::white, 7));
    plot->graph(1)->setName("Bottom maxwell function");
    QCPErrorBars *errorBars = new QCPErrorBars(plot->xAxis, plot->yAxis);
    errorBars->removeFromLegend();
    errorBars->setDataPlottable(plot->graph(1));

    // setup for graph 2: key axis top, value axis right
    // will contain high frequency sine with low frequency beating:
    plot->addGraph(plot->xAxis2, plot->yAxis2);
    plot->graph(2)->setPen(QPen(Qt::blue));
    plot->graph(2)->setName("High frequency sine");

    // setup for graph 3: same axes as graph 2
    // will contain low frequency beating envelope of graph 2
    plot->addGraph(plot->xAxis2, plot->yAxis2);
    QPen blueDotPen;
    blueDotPen.setColor(QColor(30, 40, 255, 150));
    blueDotPen.setStyle(Qt::DotLine);
    blueDotPen.setWidthF(4);
    plot->graph(3)->setPen(blueDotPen);
    plot->graph(3)->setName("Sine envelope");

    // setup for graph 4: key axis right, value axis top
    // will contain parabolically distributed data points with some random perturbance
    plot->addGraph(plot->yAxis2, plot->xAxis2);
    plot->graph(4)->setPen(QColor(50, 50, 50, 255));
    plot->graph(4)->setLineStyle(QCPGraph::lsNone);
    plot->graph(4)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    plot->graph(4)->setName("Some random data around\na quadratic function");

    // generate data, just playing with numbers, not much to learn here:
    QVector<double> x0(25), y0(25);
    QVector<double> x1(15), y1(15), y1err(15);
    QVector<double> x2(250), y2(250);
    QVector<double> x3(250), y3(250);
    QVector<double> x4(250), y4(250);
    for (int i=0; i<25; ++i) // data for graph 0
    {
        x0[i] = 3*i/25.0;
        y0[i] = qExp(-x0[i]*x0[i]*0.8)*(x0[i]*x0[i]+x0[i]);
    }
    for (int i=0; i<15; ++i) // data for graph 1
    {
        x1[i] = 3*i/15.0;;
        y1[i] = qExp(-x1[i]*x1[i])*(x1[i]*x1[i])*2.6;
        y1err[i] = y1[i]*0.25;
    }
    for (int i=0; i<250; ++i) // data for graphs 2, 3 and 4
    {
        x2[i] = i/250.0*3*M_PI;
        x3[i] = x2[i];
        x4[i] = i/250.0*100-50;
        y2[i] = qSin(x2[i]*12)*qCos(x2[i])*10;
        y3[i] = qCos(x3[i])*10;
        y4[i] = 0.01*x4[i]*x4[i] + 1.5*(rand()/(double)RAND_MAX-0.5) + 1.5*M_PI;
    }

    // pass data points to graphs:
    plot->graph(0)->setData(x0, y0);
    plot->graph(1)->setData(x1, y1);
    errorBars->setData(y1err);
    plot->graph(2)->setData(x2, y2);
    plot->graph(3)->setData(x3, y3);
    plot->graph(4)->setData(x4, y4);
    // activate top and right axes, which are invisible by default:
    plot->xAxis2->setVisible(true);
    plot->yAxis2->setVisible(true);
    // set ranges appropriate to show data:
    plot->xAxis->setRange(0, 2.7);
    plot->yAxis->setRange(0, 2.6);
    plot->xAxis2->setRange(0, 3.0*M_PI);
    plot->yAxis2->setRange(-70, 35);
    // set pi ticks on top axis:
    plot->xAxis2->setTicker(QSharedPointer<QCPAxisTickerPi>(new QCPAxisTickerPi));
    // add title layout element:
    //    plot->plotLayout()->insertRow(0);
    //    plot->plotLayout()->addElement(0, 0, new QCPTextElement(plot, "Way too many graphs in one plot", QFont("sans", 12, QFont::Bold)));

    // set labels:
    plot->xAxis->setLabel("Bottom axis with outward ticks");
    plot->yAxis->setLabel("Left axis label");
    plot->xAxis2->setLabel("Top axis label");
    plot->yAxis2->setLabel("Right axis label");
    // make ticks on bottom axis go outward:
    plot->xAxis->setTickLength(0, 5);
    plot->xAxis->setSubTickLength(0, 3);
    // make ticks on right axis go inward and outward:
    plot->yAxis2->setTickLength(3, 3);
    plot->yAxis2->setSubTickLength(1, 1);
    //    plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);

    plot->replot();
}

void MainWindow::setupLogarithmicDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Logarithmic Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);

    plot->setNoAntialiasingOnDrag(true); // more performance/responsiveness during dragging
    plot->addGraph();
    QPen pen;
    pen.setColor(QColor(255,170,100));
    pen.setWidth(2);
    pen.setStyle(Qt::DotLine);
    plot->graph(0)->setPen(pen);
    plot->graph(0)->setName("x");

    plot->addGraph();
    plot->graph(1)->setPen(QPen(Qt::red));
    plot->graph(1)->setBrush(QBrush(QColor(255, 0, 0, 20)));
    plot->graph(1)->setName("-sin(x)exp(x)");

    plot->addGraph();
    plot->graph(2)->setPen(QPen(Qt::blue));
    plot->graph(2)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    plot->graph(2)->setName(" sin(x)exp(x)");

    plot->addGraph();
    pen.setColor(QColor(0,0,0));
    pen.setWidth(1);
    pen.setStyle(Qt::DashLine);
    plot->graph(3)->setPen(pen);
    plot->graph(3)->setBrush(QBrush(QColor(0,0,0,15)));
    plot->graph(3)->setLineStyle(QCPGraph::lsStepCenter);
    plot->graph(3)->setName("x!");

    const int dataCount = 200;
    const int dataFactorialCount = 21;
    QVector<QCPGraphData> dataLinear(dataCount), dataMinusSinExp(dataCount), dataPlusSinExp(dataCount), dataFactorial(dataFactorialCount);
    for (int i=0; i<dataCount; ++i)
    {
        dataLinear[i].key = i/10.0;
        dataLinear[i].value = dataLinear[i].key;
        dataMinusSinExp[i].key = i/10.0;
        dataMinusSinExp[i].value = -qSin(dataMinusSinExp[i].key)*qExp(dataMinusSinExp[i].key);
        dataPlusSinExp[i].key = i/10.0;
        dataPlusSinExp[i].value = qSin(dataPlusSinExp[i].key)*qExp(dataPlusSinExp[i].key);
    }
    for (int i=0; i<dataFactorialCount; ++i)
    {
        dataFactorial[i].key = i;
        dataFactorial[i].value = 1.0;
        for (int k=1; k<=i; ++k) dataFactorial[i].value *= k; // factorial
    }
    plot->graph(0)->data()->set(dataLinear);
    plot->graph(1)->data()->set(dataMinusSinExp);
    plot->graph(2)->data()->set(dataPlusSinExp);
    plot->graph(3)->data()->set(dataFactorial);

    plot->yAxis->grid()->setSubGridVisible(true);
    plot->xAxis->grid()->setSubGridVisible(true);
    plot->yAxis->setScaleType(QCPAxis::stLogarithmic);
    plot->yAxis2->setScaleType(QCPAxis::stLogarithmic);
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    plot->yAxis->setTicker(logTicker);
    plot->yAxis2->setTicker(logTicker);
    plot->yAxis->setNumberFormat("eb"); // e = exponential, b = beautiful decimal powers
    plot->yAxis->setNumberPrecision(0); // makes sure "1*10^4" is displayed only as "10^4"
    plot->xAxis->setRange(0, 19.9);
    plot->yAxis->setRange(1e-2, 1e10);
    // make range draggable and zoomable:
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // make top right axes clones of bottom left axes:
    plot->axisRect()->setupFullAxesBox();
    // connect signals so top and right axes move in sync with bottom and left axes:
    connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));

    plot->legend->setVisible(true);
    plot->legend->setBrush(QBrush(QColor(255,255,255,150)));
    // make legend align in top left corner or axis rect
    plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    plot->replot();
}

void MainWindow::setupRealtimeDataDemo(int row, int col, bool openGl)
{
    QTimer *timer = new QTimer();
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Real Time Data Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);

    plot->addGraph(); // blue line
    plot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    plot->addGraph(); // red line
    plot->graph(1)->setPen(QPen(QColor(255, 110, 40)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    plot->xAxis->setTicker(timeTicker);
    plot->axisRect()->setupFullAxesBox();
    plot->yAxis->setRange(-1.2, 1.2);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));

    connect(timer, &QTimer::timeout,
            [=]() {
        static QTime timeData(QTime::currentTime());
        // calculate two new data points:
        double key = timeData.elapsed()/1000.0; // time elapsed since start of demo, in seconds
        static double lastPointKeyData = 0;
        if (key-lastPointKeyData > 0.002) // at most add point every 2 ms
        {
            // add data to lines:
            plot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
            plot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
            // rescale value (vertical) axis to fit the current data:
            //ui->customPlot->graph(0)->rescaleValueAxis();
            //ui->customPlot->graph(1)->rescaleValueAxis(true);
            lastPointKeyData = key;
        }
        // make key axis range scroll with the data (at a constant range size of 8):
        plot->xAxis->setRange(key, 10, Qt::AlignRight);
        plot->replot();


        plot->graph(0)->data()->removeBefore(key-11);
        plot->graph(1)->data()->removeBefore(key-11);

        // calculate frames per second:
        static double lastFpsKeyData;
        static int frameCountData;
        ++frameCountData;
        if (key-lastFpsKeyData > 2) // average fps over 2 seconds
        {
            bar->showMessage(
                        QString("%1 FPS, Total Data points: %2")
                        .arg(frameCountData/(key-lastFpsKeyData), 0, 'f', 0)
                        .arg(plot->graph(0)->data()->size()+plot->graph(1)->data()->size())
                        , 0);
            lastFpsKeyData = key;
            frameCountData = 0;
        }
    }
    );
    timer->start(0); // Interval 0 means to refresh as fast as possible

}

void MainWindow::setupRealtimeThresholdDemo(int row, int col, bool openGl)
{

    QTimer *timer = new QTimer();
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Real Time Threshold Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);

    plot->legend->setVisible(false);
    plot->addGraph(); // blue line
    plot->graph(0)->setPen(QPen(Qt::blue));
    plot->addGraph(); // blue line
    plot->graph(1)->setPen(QPen(Qt::green));
    plot->addGraph(); // blue line
    plot->graph(2)->setPen(QPen(Qt::red));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    plot->xAxis->setTicker(timeTicker);
    plot->axisRect()->setupFullAxesBox();
    plot->yAxis->setRange(-1.5, 1.5);

    QCPItemLine *lineBottom = new QCPItemLine(plot);
    lineBottom->setPen(QPen(Qt::green, 1, Qt::DashLine));
    lineBottom->start->setTypeX(QCPItemPosition::ptAxisRectRatio);
    lineBottom->start->setTypeY(QCPItemPosition::ptPlotCoords);
    lineBottom->start->setAxisRect(plot->axisRect());
    lineBottom->start->setAxes(0, plot->yAxis);
    lineBottom->start->setCoords(0, -1.0);
    lineBottom->end->setTypeX(QCPItemPosition::ptAxisRectRatio);
    lineBottom->end->setTypeY(QCPItemPosition::ptPlotCoords);
    lineBottom->end->setAxisRect(plot->axisRect());
    lineBottom->end->setAxes(0, plot->yAxis);
    lineBottom->end->setCoords(1, -1.0);

    QCPItemLine *lineTop = new QCPItemLine(plot);
    lineTop->setPen(QPen(Qt::red, 1, Qt::DashLine));
    lineTop->start->setTypeX(QCPItemPosition::ptAxisRectRatio);
    lineTop->start->setTypeY(QCPItemPosition::ptPlotCoords);
    lineTop->start->setAxisRect(plot->axisRect());
    lineTop->start->setAxes(0, plot->yAxis);
    lineTop->start->setCoords(0, 1.0);
    lineTop->end->setTypeX(QCPItemPosition::ptAxisRectRatio);
    lineTop->end->setTypeY(QCPItemPosition::ptPlotCoords);
    lineTop->end->setAxisRect(plot->axisRect());
    lineTop->end->setAxes(0, plot->yAxis);
    lineTop->end->setCoords(1, 1.0);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    //    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));

    connect(timer, &QTimer::timeout,
            [=]() {
        static QTime time(QTime::currentTime());
        // calculate two new data points:
        double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
        static double lastPointKey = 0;
        static double lastPointValue = 0;
        if (key-lastPointKey > 0.002) // at most add point every 2 ms
        {

            // add data to lines:
            double val = qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843);
            if(val < -1.0) {
                if(lastPointValue < -1.0)
                    plot->graph(1)->addData(key, val);
                else if (lastPointValue > 1.0) {
                    double interv = (key - lastPointKey)/3;
                    plot->graph(2)->addData(lastPointKey + interv, 1.0);
                    plot->graph(0)->addData(lastPointKey + interv, 1.0);
                    plot->graph(0)->addData(lastPointKey + 2*interv, -1.0);
                    plot->graph(1)->addData(lastPointKey + 2*interv, -1.0);
                    plot->graph(1)->addData(key, val);
                } else {
                    double interv = (key - lastPointKey)/2;
                    plot->graph(0)->addData(lastPointKey + interv, -1.0);
                    plot->graph(1)->addData(lastPointKey + interv, -1.0);
                    plot->graph(1)->addData(key, val);
                }
                plot->graph(0)->addData(key, qQNaN());
                plot->graph(2)->addData(key, qQNaN());
            }
            else if( val > 1.0) {
                if(lastPointValue < -1.0) {
                    double interv = (key - lastPointKey)/3;
                    plot->graph(0)->addData(lastPointKey + interv, -1.0);
                    plot->graph(0)->addData(lastPointKey + 2*interv, 1.0);
                    plot->graph(1)->addData(lastPointKey + interv, -1.0);
                    plot->graph(2)->addData(lastPointKey + 2*interv, 1.0);
                    plot->graph(2)->addData(key, val);
                }
                else if (lastPointValue > 1.0) {
                    plot->graph(2)->addData(key, val);

                } else
                {
                    double interv = (key - lastPointKey)/2;
                    plot->graph(0)->addData(lastPointKey + interv, 1.0);
                    plot->graph(2)->addData(lastPointKey + interv, 1.0);
                    plot->graph(2)->addData(key, val);
                }

                plot->graph(0)->addData(key, qQNaN());
                plot->graph(1)->addData(key, qQNaN());
            } else {
                if(lastPointValue < -1.0) {
                    double interv = (key - lastPointKey)/2;
                    plot->graph(1)->addData(lastPointKey + interv, -1.0);
                    plot->graph(0)->addData(lastPointKey + interv, -1.0);
                    plot->graph(0)->addData(key, val);
                }else if (lastPointValue > 1.0) {
                    double interv = (key - lastPointKey)/2;
                    plot->graph(2)->addData(lastPointKey + interv, 1.0);
                    plot->graph(0)->addData(lastPointKey + interv, 1.0);
                    plot->graph(0)->addData(key, val);
                } else
                {
                    plot->graph(0)->addData(key, val);
                }

                plot->graph(1)->addData(key, qQNaN());
                plot->graph(2)->addData(key, qQNaN());

            }
            lastPointKey = key;
            lastPointValue = val;
        }
        // make key axis range scroll with the data (at a constant range size of 8):

        //        lineBottom->start->setCoords(0,-1.0);
        //        lineBottom->end->setCoords(1,-1.0);
        plot->graph(0)->data()->removeBefore(key-10);
        plot->graph(1)->data()->removeBefore(key-10);
        plot->graph(2)->data()->removeBefore(key-10);
        plot->xAxis->rescale();
        plot->yAxis->rescale();
        plot->replot();

        // calculate frames per second:
        static double lastFpsKey;
        static int frameCount;
        ++frameCount;
        if (key-lastFpsKey > 2) // average fps over 2 seconds
        {
            bar->showMessage(
                        QString("%1 FPS, Total Data points: %2")
                        .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                        .arg(plot->graph(0)->data()->size()+plot->graph(1)->data()->size())
                        , 0);
            lastFpsKey = key;
            frameCount = 0;
        }
    }
    );
    timer->start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::setupRealtimeBrushDemo(int row, int col, bool openGl)
{
    QTimer *timer = new QTimer();
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Real Time Brush Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);
    //    demoName = "Real Time Data Demo";

    // include this section to fully disable antialiasing for higher performance:
    /*
  customPlot->setNotAntialiasedElements(QCP::aeAll);
  QFont font;
  font.setStyleStrategy(QFont::NoAntialias);
  customPlot->xAxis->setTickLabelFont(font);
  customPlot->yAxis->setTickLabelFont(font);
  customPlot->legend->setFont(font);
  */

    plot->addGraph(); // red line
    plot->graph(0)->setPen(Qt::NoPen);
    QLinearGradient gradient0(0, 0, 0, 1);
    gradient0.setCoordinateMode(QGradient::ObjectBoundingMode);
    gradient0.setColorAt(1, QColor(40, 110, 255, 255));
    gradient0.setColorAt(0.95, QColor(40, 110, 255, 200));
    gradient0.setColorAt(0, QColor::fromRgbF(0, 0, 0, 0));
    QBrush brush0(gradient0);
    plot->graph(0)->setBrush(brush0);

    plot->addGraph(); // red line
    plot->graph(1)->setPen(Qt::NoPen);

    QLinearGradient gradient1(0, 0, 0, 1);
    gradient1.setCoordinateMode(QGradient::ObjectBoundingMode);
    gradient1.setColorAt(1, QColor(255, 110, 40, 255));
    gradient1.setColorAt(0.95, QColor(255, 110, 40, 200));
    gradient1.setColorAt(0, QColor::fromRgbF(0, 0, 0, 0));
    QBrush brush1(gradient1);
    plot->graph(1)->setBrush(brush1);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    plot->xAxis->setTicker(timeTicker);
    plot->axisRect()->setupFullAxesBox();
    plot->yAxis->setRange(-1.5, 1.5);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    //    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));

    connect(timer, &QTimer::timeout,
            [=]() {
        static QTime timeBrush(QTime::currentTime());
        // calculate two new data points:
        double key = timeBrush.elapsed()/1000.0; // time elapsed since start of demo, in seconds
        static double lastPointKeyBrush = 0;
        if (key-lastPointKeyBrush > 0.002) // at most add point every 2 ms
        {

            // add data to lines:
            plot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
            plot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
            // rescale value (vertical) axis to fit the current data:
            //ui->customPlot->graph(0)->rescaleValueAxis();
            //ui->customPlot->graph(1)->rescaleValueAxis(true);
            lastPointKeyBrush = key;
        }
        // make key axis range scroll with the data (at a constant range size of 8):

        plot->graph(0)->data()->removeBefore(key-10);
        plot->graph(1)->data()->removeBefore(key-10);
        plot->xAxis->rescale();
        plot->yAxis->rescale();
        plot->replot();

        // calculate frames per second:
        static double lastFpsKeyBrush;
        static int frameCountBrush;
        ++frameCountBrush;
        if (key-lastFpsKeyBrush > 2) // average fps over 2 seconds
        {
            bar->showMessage(
                        QString("%1 FPS, Total Data points: %2")
                        .arg(frameCountBrush/(key-lastFpsKeyBrush), 0, 'f', 0)
                        .arg(plot->graph(0)->data()->size()+plot->graph(1)->data()->size())
                        , 0);
            lastFpsKeyBrush = key;
            frameCountBrush = 0;
        }
    }
    );
    timer->start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::setupRealtimeEcgDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Real Time ECG Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);

    plot->addGraph(plot->xAxis, plot->yAxis); // blue line
    plot->graph(0)->setPen(QPen(Qt::blue));
    plot->addGraph(plot->xAxis2, plot->yAxis); // red line
    plot->graph(1)->setPen(QPen(Qt::red));

    plot->xAxis->setRange(0, 10);
    plot->xAxis2->setRange(10, 20);

    QTimer *timer =new QTimer();
    connect(timer, &QTimer::timeout,
            [=]() {

        static QTime timeEcg(QTime::currentTime());
        // calculate two new data points:
        double keyTime = timeEcg.elapsed()/1000.0; // time elapsed since start of demo, in seconds

        double key = std::fmod(keyTime,20);

        static bool plottingBlue = true;

        // add data to lines:
        double val = qSin(keyTime)+qrand()/(double)RAND_MAX*1*qSin(keyTime/0.3843);
        plot->graph(0)->addData(key, val);
        plot->graph(1)->addData(key, val);

        if(key <10.0)
        {
            if(!plottingBlue)
            {
                plottingBlue = true;
                plot->graph(0)->data()->clear();
            }
            plot->graph(1)->data()->removeBefore(10+key);
        }
        else
        {
            if(plottingBlue)
            {
                plottingBlue = false;
                plot->graph(1)->data()->clear();
            }
            plot->graph(0)->data()->removeBefore(key-10);
        }

        // make key axis range scroll with the data (at a constant range size of 8):
        plot->yAxis->rescale();
        plot->replot();
    }
    );
    timer->start(0);

}

void MainWindow::setupParametricCurveDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Parametric Curves Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);
    //    demoName = "Parametric Curves Demo";

    // create empty curve objects:
    QCPCurve *fermatSpiral1 = new QCPCurve(plot->xAxis, plot->yAxis);
    QCPCurve *fermatSpiral2 = new QCPCurve(plot->xAxis, plot->yAxis);
    QCPCurve *deltoidRadial = new QCPCurve(plot->xAxis, plot->yAxis);
    // generate the curve data points:
    const int pointCount = 500;
    QVector<QCPCurveData> dataSpiral1(pointCount), dataSpiral2(pointCount), dataDeltoid(pointCount);
    for (int i=0; i<pointCount; ++i)
    {
        double phi = i/(double)(pointCount-1)*8*M_PI;
        double theta = i/(double)(pointCount-1)*2*M_PI;
        dataSpiral1[i] = QCPCurveData(i, qSqrt(phi)*qCos(phi), qSqrt(phi)*qSin(phi));
        dataSpiral2[i] = QCPCurveData(i, -dataSpiral1[i].key, -dataSpiral1[i].value);
        dataDeltoid[i] = QCPCurveData(i, 2*qCos(2*theta)+qCos(1*theta)+2*qSin(theta), 2*qSin(2*theta)-qSin(1*theta));
    }
    // pass the data to the curves; we know t (i in loop above) is ascending, so set alreadySorted=true (saves an extra internal sort):
    fermatSpiral1->data()->set(dataSpiral1, true);
    fermatSpiral2->data()->set(dataSpiral2, true);
    deltoidRadial->data()->set(dataDeltoid, true);
    // color the curves:
    fermatSpiral1->setPen(QPen(Qt::blue));
    fermatSpiral1->setBrush(QBrush(QColor(0, 0, 255, 20)));
    fermatSpiral2->setPen(QPen(QColor(255, 120, 0)));
    fermatSpiral2->setBrush(QBrush(QColor(255, 120, 0, 30)));
    QRadialGradient radialGrad(QPointF(310, 180), 200);
    radialGrad.setColorAt(0, QColor(170, 20, 240, 100));
    radialGrad.setColorAt(0.5, QColor(20, 10, 255, 40));
    radialGrad.setColorAt(1,QColor(120, 20, 240, 10));
    deltoidRadial->setPen(QPen(QColor(170, 20, 240)));
    deltoidRadial->setBrush(QBrush(radialGrad));
    // set some basic customPlot config:
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plot->axisRect()->setupFullAxesBox();
    plot->rescaleAxes();

    plot->replot();
}

void MainWindow::setupBarChartDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Bar Chart Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);
    //    demoName = "Bar Chart Demo";
    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    plot->setBackground(QBrush(gradient));

    // create empty bar chart objects:
    QCPBars *regen = new QCPBars(plot->xAxis, plot->yAxis);
    QCPBars *nuclear = new QCPBars(plot->xAxis, plot->yAxis);
    QCPBars *fossil = new QCPBars(plot->xAxis, plot->yAxis);
    regen->setAntialiased(false); // gives more crisp, pixel aligned bar borders
    nuclear->setAntialiased(false);
    fossil->setAntialiased(false);
    regen->setStackingGap(1);
    nuclear->setStackingGap(1);
    fossil->setStackingGap(1);
    // set names and colors:
    fossil->setName("Fossil fuels");
    fossil->setPen(QPen(QColor(111, 9, 176).lighter(170)));
    fossil->setBrush(QColor(111, 9, 176));
    nuclear->setName("Nuclear");
    nuclear->setPen(QPen(QColor(250, 170, 20).lighter(150)));
    nuclear->setBrush(QColor(250, 170, 20));
    regen->setName("Regenerative");
    regen->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    regen->setBrush(QColor(0, 168, 140));
    // stack bars on top of each other:
    nuclear->moveAbove(fossil);
    regen->moveAbove(nuclear);

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7;
    labels << "USA" << "Japan" << "Germany" << "France" << "UK" << "Italy" << "Canada";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    plot->xAxis->setTicker(textTicker);
    plot->xAxis->setTickLabelRotation(60);
    plot->xAxis->setSubTicks(false);
    plot->xAxis->setTickLength(0, 4);
    plot->xAxis->setRange(0, 8);
    plot->xAxis->setBasePen(QPen(Qt::white));
    plot->xAxis->setTickPen(QPen(Qt::white));
    plot->xAxis->grid()->setVisible(true);
    plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    plot->xAxis->setTickLabelColor(Qt::white);
    plot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    plot->yAxis->setRange(0, 12.1);
    plot->yAxis->setPadding(5); // a bit more space to the left border
    plot->yAxis->setLabel("Power Consumption in\nKilowatts per Capita (2007)");
    plot->yAxis->setBasePen(QPen(Qt::white));
    plot->yAxis->setTickPen(QPen(Qt::white));
    plot->yAxis->setSubTickPen(QPen(Qt::white));
    plot->yAxis->grid()->setSubGridVisible(true);
    plot->yAxis->setTickLabelColor(Qt::white);
    plot->yAxis->setLabelColor(Qt::white);
    plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    QVector<double> fossilData, nuclearData, regenData;
    fossilData  << 0.86*10.5 << 0.83*5.5 << 0.84*5.5 << 0.52*5.8 << 0.89*5.2 << 0.90*4.2 << 0.67*11.2;
    nuclearData << 0.08*10.5 << 0.12*5.5 << 0.12*5.5 << 0.40*5.8 << 0.09*5.2 << 0.00*4.2 << 0.07*11.2;
    regenData   << 0.06*10.5 << 0.05*5.5 << 0.04*5.5 << 0.06*5.8 << 0.02*5.2 << 0.07*4.2 << 0.25*11.2;
    fossil->setData(ticks, fossilData);
    nuclear->setData(ticks, nuclearData);
    regen->setData(ticks, regenData);

    // setup legend:
    plot->legend->setVisible(true);
    plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    plot->legend->setBrush(QColor(255, 255, 255, 100));
    plot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    plot->legend->setFont(legendFont);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    plot->replot();
}

void MainWindow::setupStatisticalDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Statistical Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);
    //    demoName = "Statistical Demo";
    QCPStatisticalBox *statistical = new QCPStatisticalBox(plot->xAxis, plot->yAxis);
    QBrush boxBrush(QColor(60, 60, 255, 100));
    boxBrush.setStyle(Qt::Dense6Pattern); // make it look oldschool
    statistical->setBrush(boxBrush);

    // specify data:
    statistical->addData(1, 1.1, 1.9, 2.25, 2.7, 4.2);
    statistical->addData(2, 0.8, 1.6, 2.2, 3.2, 4.9, QVector<double>() << 0.7 << 0.34 << 0.45 << 6.2 << 5.84); // provide some outliers as QVector
    statistical->addData(3, 0.2, 0.7, 1.1, 1.6, 2.9);

    // prepare manual x axis labels:
    plot->xAxis->setSubTicks(false);
    plot->xAxis->setTickLength(0, 4);
    plot->xAxis->setTickLabelRotation(20);
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTick(1, "Sample 1");
    textTicker->addTick(2, "Sample 2");
    textTicker->addTick(3, "Control Group");
    plot->xAxis->setTicker(textTicker);

    // prepare axes:
    plot->yAxis->setLabel(QString::fromUtf8("O₂ Absorption [mg]"));
    plot->rescaleAxes();
    plot->xAxis->scaleRange(1.7, plot->xAxis->range().center());
    plot->yAxis->setRange(0, 7);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    plot->replot();
}

void MainWindow::setupSimpleItemDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Simple Item Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);
    //    demoName = "Simple Item Demo";
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // add the text label at the top:
    QCPItemText *textLabel = new QCPItemText(plot);
    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
    textLabel->setText("Text Item Demo");
    textLabel->setFont(QFont(font().family(), 16)); // make font a bit larger
    textLabel->setPen(QPen(Qt::black)); // show black border around text

    // add the arrow:
    QCPItemLine *arrow = new QCPItemLine(plot);
    arrow->start->setParentAnchor(textLabel->bottom);
    arrow->end->setCoords(4, 1.6); // point to (4, 1.6) in x-y-plot coordinates
    arrow->setHead(QCPLineEnding::esSpikeArrow);

    plot->replot();
}

void MainWindow::setupItemDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Item Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);

    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    QCPGraph *graph = plot->addGraph();
    int n = 500;
    double phase = 0;
    double k = 3;
    QVector<double> x(n), y(n);
    for (int i=0; i<n; ++i)
    {
        x[i] = i/(double)(n-1)*34 - 17;
        y[i] = qExp(-x[i]*x[i]/20.0)*qSin(k*x[i]+phase);
    }
    graph->setData(x, y);
    graph->setPen(QPen(Qt::blue));
    graph->rescaleKeyAxis();
    plot->yAxis->setRange(-1.45, 1.65);
    plot->xAxis->grid()->setZeroLinePen(Qt::NoPen);

    // add the bracket at the top:
    QCPItemBracket *bracket = new QCPItemBracket(plot);
    bracket->left->setCoords(-8, 1.1);
    bracket->right->setCoords(8, 1.1);
    bracket->setLength(13);

    // add the text label at the top:
    QCPItemText *wavePacketText = new QCPItemText(plot);
    wavePacketText->position->setParentAnchor(bracket->center);
    wavePacketText->position->setCoords(0, -10); // move 10 pixels to the top from bracket center anchor
    wavePacketText->setPositionAlignment(Qt::AlignBottom|Qt::AlignHCenter);
    wavePacketText->setText("Wavepacket");
    wavePacketText->setFont(QFont(font().family(), 10));

    // add the phase tracer (red circle) which sticks to the graph data (and gets updated in bracketDataSlot by timer event):
    QCPItemTracer *phaseTracer = new QCPItemTracer(plot);
    phaseTracer->setGraph(graph);
    phaseTracer->setGraphKey((M_PI*1.5-phase)/k);
    phaseTracer->setInterpolating(true);
    phaseTracer->setStyle(QCPItemTracer::tsCircle);
    phaseTracer->setPen(QPen(Qt::red));
    phaseTracer->setBrush(Qt::red);
    phaseTracer->setSize(7);

    // add label for phase tracer:
    QCPItemText *phaseTracerText = new QCPItemText(plot);
    phaseTracerText->position->setType(QCPItemPosition::ptAxisRectRatio);
    phaseTracerText->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
    phaseTracerText->position->setCoords(1.0, 0.95); // lower right corner of axis rect
    phaseTracerText->setText("Points of fixed\nphase define\nphase velocity vp");
    phaseTracerText->setTextAlignment(Qt::AlignLeft);
    phaseTracerText->setFont(QFont(font().family(), 9));
    phaseTracerText->setPadding(QMargins(8, 0, 0, 0));

    // add arrow pointing at phase tracer, coming from label:
    QCPItemCurve *phaseTracerArrow = new QCPItemCurve(plot);
    phaseTracerArrow->start->setParentAnchor(phaseTracerText->left);
    phaseTracerArrow->startDir->setParentAnchor(phaseTracerArrow->start);
    phaseTracerArrow->startDir->setCoords(-40, 0); // direction 30 pixels to the left of parent anchor (tracerArrow->start)
    phaseTracerArrow->end->setParentAnchor(phaseTracer->position);
    phaseTracerArrow->end->setCoords(10, 10);
    phaseTracerArrow->endDir->setParentAnchor(phaseTracerArrow->end);
    phaseTracerArrow->endDir->setCoords(30, 30);
    phaseTracerArrow->setHead(QCPLineEnding::esSpikeArrow);
    phaseTracerArrow->setTail(QCPLineEnding(QCPLineEnding::esBar, (phaseTracerText->bottom->pixelPosition().y()-phaseTracerText->top->pixelPosition().y())*0.85));

    // add the group velocity tracer (green circle):
    QCPItemTracer *groupTracer = new QCPItemTracer(plot);
    groupTracer->setGraph(graph);
    groupTracer->setGraphKey(5.5);
    groupTracer->setInterpolating(true);
    groupTracer->setStyle(QCPItemTracer::tsCircle);
    groupTracer->setPen(QPen(Qt::green));
    groupTracer->setBrush(Qt::green);
    groupTracer->setSize(7);

    // add label for group tracer:
    QCPItemText *groupTracerText = new QCPItemText(plot);
    groupTracerText->position->setType(QCPItemPosition::ptAxisRectRatio);
    groupTracerText->setPositionAlignment(Qt::AlignRight|Qt::AlignTop);
    groupTracerText->position->setCoords(1.0, 0.20); // lower right corner of axis rect
    groupTracerText->setText("Fixed positions in\nwave packet define\ngroup velocity vg");
    groupTracerText->setTextAlignment(Qt::AlignLeft);
    groupTracerText->setFont(QFont(font().family(), 9));
    groupTracerText->setPadding(QMargins(8, 0, 0, 0));

    // add arrow pointing at group tracer, coming from label:
    QCPItemCurve *groupTracerArrow = new QCPItemCurve(plot);
    groupTracerArrow->start->setParentAnchor(groupTracerText->left);
    groupTracerArrow->startDir->setParentAnchor(groupTracerArrow->start);
    groupTracerArrow->startDir->setCoords(-40, 0); // direction 30 pixels to the left of parent anchor (tracerArrow->start)
    groupTracerArrow->end->setCoords(5.5, 0.4);
    groupTracerArrow->endDir->setParentAnchor(groupTracerArrow->end);
    groupTracerArrow->endDir->setCoords(0, -40);
    groupTracerArrow->setHead(QCPLineEnding::esSpikeArrow);
    groupTracerArrow->setTail(QCPLineEnding(QCPLineEnding::esBar, (groupTracerText->bottom->pixelPosition().y()-groupTracerText->top->pixelPosition().y())*0.85));

    // add dispersion arrow:
    QCPItemCurve *arrow = new QCPItemCurve(plot);
    arrow->start->setCoords(1, -1.1);
    arrow->startDir->setCoords(-1, -1.3);
    arrow->endDir->setCoords(-5, -0.3);
    arrow->end->setCoords(-10, -0.2);
    arrow->setHead(QCPLineEnding::esSpikeArrow);

    // add the dispersion arrow label:
    QCPItemText *dispersionText = new QCPItemText(plot);
    dispersionText->position->setCoords(-6, -0.9);
    dispersionText->setRotation(40);
    dispersionText->setText("Dispersion with\nvp < vg");
    dispersionText->setFont(QFont(font().family(), 10));

    // setup a timer that repeatedly calls MainWindow::bracketDataSlot:
    //    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(bracketDataSlot()));

    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout,
            [=]() {
        double secs = QCPAxisTickerDateTime::dateTimeToKey(QDateTime::currentDateTime());

        // update data to make phase move:
        int n = 500;
        double phase = secs*5;
        double k = 3;
        QVector<double> x(n), y(n);
        for (int i=0; i<n; ++i)
        {
            x[i] = i/(double)(n-1)*34 - 17;
            y[i] = qExp(-x[i]*x[i]/20.0)*qSin(k*x[i]+phase);
        }
        plot->graph()->setData(x, y);

        phaseTracer->setGraphKey((8*M_PI+fmod(M_PI*1.5-phase, 6*M_PI))/k);

        plot->replot();

        // calculate frames per second:
        double key = secs;
        static double lastFpsKeyItem;
        static int frameCountItem;
        ++frameCountItem;
        if (key-lastFpsKeyItem > 2) // average fps over 2 seconds
        {
            bar->showMessage(
                        QString("%1 FPS, Total Data points: %2")
                        .arg(frameCountItem/(key-lastFpsKeyItem), 0, 'f', 0)
                        .arg(plot->graph(0)->data()->size())
                        , 0);
            lastFpsKeyItem = key;
            frameCountItem = 0;
        }
    }
    );
    timer->start(0); // Interval 0 means to refresh as fast as possible
    //    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::setupStyledDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Styled Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);
    //    demoName = "Styled Demo";

    // prepare data:
    QVector<double> x1(20), y1(20);
    QVector<double> x2(100), y2(100);
    QVector<double> x3(20), y3(20);
    QVector<double> x4(20), y4(20);
    for (int i=0; i<x1.size(); ++i)
    {
        x1[i] = i/(double)(x1.size()-1)*10;
        y1[i] = qCos(x1[i]*0.8+qSin(x1[i]*0.16+1.0))*qSin(x1[i]*0.54)+1.4;
    }
    for (int i=0; i<x2.size(); ++i)
    {
        x2[i] = i/(double)(x2.size()-1)*10;
        y2[i] = qCos(x2[i]*0.85+qSin(x2[i]*0.165+1.1))*qSin(x2[i]*0.50)+1.7;
    }
    for (int i=0; i<x3.size(); ++i)
    {
        x3[i] = i/(double)(x3.size()-1)*10;
        y3[i] = 0.05+3*(0.5+qCos(x3[i]*x3[i]*0.2+2)*0.5)/(double)(x3[i]+0.7)+qrand()/(double)RAND_MAX*0.01;
    }
    for (int i=0; i<x4.size(); ++i)
    {
        x4[i] = x3[i];
        y4[i] = (0.5-y3[i])+((x4[i]-2)*(x4[i]-2)*0.02);
    }

    // create and configure plottables:
    QCPGraph *graph1 = plot->addGraph();
    graph1->setData(x1, y1);
    graph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
    graph1->setPen(QPen(QColor(120, 120, 120), 2));

    QCPGraph *graph2 = plot->addGraph();
    graph2->setData(x2, y2);
    graph2->setPen(Qt::NoPen);
    graph2->setBrush(QColor(200, 200, 200, 20));
    graph2->setChannelFillGraph(graph1);

    QCPBars *bars1 = new QCPBars(plot->xAxis, plot->yAxis);
    bars1->setWidth(9/(double)x3.size());
    bars1->setData(x3, y3);
    bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(10, 140, 70, 160));

    QCPBars *bars2 = new QCPBars(plot->xAxis, plot->yAxis);
    bars2->setWidth(9/(double)x4.size());
    bars2->setData(x4, y4);
    bars2->setPen(Qt::NoPen);
    bars2->setBrush(QColor(10, 100, 50, 70));
    bars2->moveAbove(bars1);

    // move bars above graphs and grid below bars:
    plot->addLayer("abovemain", plot->layer("main"), QCustomPlot::limAbove);
    plot->addLayer("belowmain", plot->layer("main"), QCustomPlot::limBelow);
    graph1->setLayer("abovemain");
    plot->xAxis->grid()->setLayer("belowmain");
    plot->yAxis->grid()->setLayer("belowmain");

    // set some pens, brushes and backgrounds:
    plot->xAxis->setBasePen(QPen(Qt::white, 1));
    plot->yAxis->setBasePen(QPen(Qt::white, 1));
    plot->xAxis->setTickPen(QPen(Qt::white, 1));
    plot->yAxis->setTickPen(QPen(Qt::white, 1));
    plot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    plot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    plot->xAxis->setTickLabelColor(Qt::white);
    plot->yAxis->setTickLabelColor(Qt::white);
    plot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    plot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    plot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    plot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    plot->xAxis->grid()->setSubGridVisible(true);
    plot->yAxis->grid()->setSubGridVisible(true);
    plot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    plot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    plot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    plot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    plot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    plot->axisRect()->setBackground(axisRectGradient);

    plot->rescaleAxes();
    plot->yAxis->setRange(0, 2);

    plot->replot();
}

void MainWindow::setupAdvancedAxesDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Advanced Axes Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);
    //    demoName = "Advanced Axes Demo";
    // configure axis rect:
    plot->plotLayout()->clear(); // clear default axis rect so we can start from scratch
    QCPAxisRect *wideAxisRect = new QCPAxisRect(plot);
    wideAxisRect->setupFullAxesBox(true);
    wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    plot->plotLayout()->addElement(0, 0, wideAxisRect); // insert axis rect in first row
    plot->plotLayout()->addElement(1, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
    //customPlot->plotLayout()->setRowStretchFactor(1, 2);
    // prepare axis rects that will be placed in the sublayout:
    QCPAxisRect *subRectLeft = new QCPAxisRect(plot, false); // false means to not setup default axes
    QCPAxisRect *subRectRight = new QCPAxisRect(plot, false);
    subLayout->addElement(0, 0, subRectLeft);
    subLayout->addElement(0, 1, subRectRight);
    subRectRight->setMaximumSize(150, 150); // make bottom right axis rect size fixed 150x150
    subRectRight->setMinimumSize(150, 150); // make bottom right axis rect size fixed 150x150
    // setup axes in sub layout axis rects:
    subRectLeft->addAxes(QCPAxis::atBottom | QCPAxis::atLeft);
    subRectRight->addAxes(QCPAxis::atBottom | QCPAxis::atRight);
    subRectLeft->axis(QCPAxis::atLeft)->ticker()->setTickCount(2);
    subRectRight->axis(QCPAxis::atRight)->ticker()->setTickCount(2);
    subRectRight->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
    subRectLeft->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    // synchronize the left and right margins of the top and bottom axis rects:
    QCPMarginGroup *marginGroup = new QCPMarginGroup(plot);
    subRectLeft->setMarginGroup(QCP::msLeft, marginGroup);
    subRectRight->setMarginGroup(QCP::msRight, marginGroup);
    wideAxisRect->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);
    // move newly created axes on "axes" layer and grids on "grid" layer:
    foreach (QCPAxisRect *rect, plot->axisRects())
    {
        foreach (QCPAxis *axis, rect->axes())
        {
            axis->setLayer("axes");
            axis->grid()->setLayer("grid");
        }
    }

    // prepare data:
    QVector<QCPGraphData> dataCos(21), dataGauss(50), dataRandom(100);
    QVector<double> x3, y3;
    qsrand(3);
    for (int i=0; i<dataCos.size(); ++i)
    {
        dataCos[i].key = i/(double)(dataCos.size()-1)*10-5.0;
        dataCos[i].value = qCos(dataCos[i].key);
    }
    for (int i=0; i<dataGauss.size(); ++i)
    {
        dataGauss[i].key = i/(double)dataGauss.size()*10-5.0;
        dataGauss[i].value = qExp(-dataGauss[i].key*dataGauss[i].key*0.2)*1000;
    }
    for (int i=0; i<dataRandom.size(); ++i)
    {
        dataRandom[i].key = i/(double)dataRandom.size()*10;
        dataRandom[i].value = qrand()/(double)RAND_MAX-0.5+dataRandom[qMax(0, i-1)].value;
    }
    x3 << 1 << 2 << 3 << 4;
    y3 << 2 << 2.5 << 4 << 1.5;

    // create and configure plottables:
    QCPGraph *mainGraphCos = plot->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));
    mainGraphCos->data()->set(dataCos);
    mainGraphCos->valueAxis()->setRange(-1, 1);
    mainGraphCos->rescaleKeyAxis();
    mainGraphCos->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black), QBrush(Qt::white), 6));
    mainGraphCos->setPen(QPen(QColor(120, 120, 120), 2));
    QCPGraph *mainGraphGauss = plot->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft, 1));
    mainGraphGauss->data()->set(dataGauss);
    mainGraphGauss->setPen(QPen(QColor("#8070B8"), 2));
    mainGraphGauss->setBrush(QColor(110, 170, 110, 30));
    mainGraphCos->setChannelFillGraph(mainGraphGauss);
    mainGraphCos->setBrush(QColor(255, 161, 0, 50));
    mainGraphGauss->valueAxis()->setRange(0, 1000);
    mainGraphGauss->rescaleKeyAxis();

    QCPGraph *subGraphRandom = plot->addGraph(subRectLeft->axis(QCPAxis::atBottom), subRectLeft->axis(QCPAxis::atLeft));
    subGraphRandom->data()->set(dataRandom);
    subGraphRandom->setLineStyle(QCPGraph::lsImpulse);
    subGraphRandom->setPen(QPen(QColor("#FFA100"), 1.5));
    subGraphRandom->rescaleAxes();

    QCPBars *subBars = new QCPBars(subRectRight->axis(QCPAxis::atBottom), subRectRight->axis(QCPAxis::atRight));
    subBars->setWidth(3/(double)x3.size());
    subBars->setData(x3, y3);
    subBars->setPen(QPen(Qt::black));
    subBars->setAntialiased(false);
    subBars->setAntialiasedFill(false);
    subBars->setBrush(QColor("#705BE8"));
    subBars->keyAxis()->setSubTicks(false);
    subBars->rescaleAxes();
    // setup a ticker for subBars key axis that only gives integer ticks:
    QSharedPointer<QCPAxisTickerFixed> intTicker(new QCPAxisTickerFixed);
    intTicker->setTickStep(1.0);
    intTicker->setScaleStrategy(QCPAxisTickerFixed::ssMultiples);
    subBars->keyAxis()->setTicker(intTicker);


    plot->replot();
}

void MainWindow::setupColorMapDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Color Map Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);
    //    demoName = "Color Map Demo";

    // configure axis rect:
    plot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    plot->axisRect()->setupFullAxesBox(true);
    plot->xAxis->setLabel("x");
    plot->yAxis->setLabel("y");

    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(plot->xAxis, plot->yAxis);
    int nx = 200;
    int ny = 200;
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(-4, 4), QCPRange(-4, 4)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    double x, y, z;
    for (int xIndex=0; xIndex<nx; ++xIndex)
    {
        for (int yIndex=0; yIndex<ny; ++yIndex)
        {
            colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
            double r = 3*qSqrt(x*x+y*y)+1e-2;
            z = 2*x*(qCos(r+2)/r-qSin(r+2)/r); // the B field strength of dipole radiation (modulo physical constants)
            colorMap->data()->setCell(xIndex, yIndex, z);
        }
    }

    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(plot);
    plot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
    colorScale->axis()->setLabel("Magnetic Field Strength");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpPolar);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(plot);
    plot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    plot->rescaleAxes();

    plot->replot();
}

void MainWindow::setupFinancialDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Financial Charts Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);
    plot->legend->setVisible(true);

    // generate two sets of random walk data (one for candlestick and one for ohlc chart):
    int n = 500;
    QVector<double> time(n), value1(n), value2(n);
    QDateTime start = QDateTime(QDate(2014, 6, 11));
    start.setTimeSpec(Qt::UTC);
    double startTime = start.toTime_t();
    double binSize = 3600*24; // bin data in 1 day intervals
    time[0] = startTime;
    value1[0] = 60;
    value2[0] = 20;
    qsrand(9);
    for (int i=1; i<n; ++i)
    {
        time[i] = startTime + 3600*i;
        value1[i] = value1[i-1] + (qrand()/(double)RAND_MAX-0.5)*10;
        value2[i] = value2[i-1] + (qrand()/(double)RAND_MAX-0.5)*3;
    }

    // create candlestick chart:
    QCPFinancial *candlesticks = new QCPFinancial(plot->xAxis, plot->yAxis);
    candlesticks->setName("Candlestick");
    candlesticks->setChartStyle(QCPFinancial::csCandlestick);
    candlesticks->data()->set(QCPFinancial::timeSeriesToOhlc(time, value1, binSize, startTime));
    candlesticks->setWidth(binSize*0.9);
    candlesticks->setTwoColored(true);
    candlesticks->setBrushPositive(QColor(245, 245, 245));
    candlesticks->setBrushNegative(QColor(40, 40, 40));
    candlesticks->setPenPositive(QPen(QColor(0, 0, 0)));
    candlesticks->setPenNegative(QPen(QColor(0, 0, 0)));

    // create ohlc chart:
    QCPFinancial *ohlc = new QCPFinancial(plot->xAxis, plot->yAxis);
    ohlc->setName("OHLC");
    ohlc->setChartStyle(QCPFinancial::csOhlc);
    ohlc->data()->set(QCPFinancial::timeSeriesToOhlc(time, value2, binSize/3.0, startTime)); // divide binSize by 3 just to make the ohlc bars a bit denser
    ohlc->setWidth(binSize*0.2);
    ohlc->setTwoColored(true);

    // create bottom axis rect for volume bar chart:
    QCPAxisRect *volumeAxisRect = new QCPAxisRect(plot);
    plot->plotLayout()->addElement(1, 0, volumeAxisRect);
    volumeAxisRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, 100));
    volumeAxisRect->axis(QCPAxis::atBottom)->setLayer("axes");
    volumeAxisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");
    // bring bottom and main axis rect closer together:
    plot->plotLayout()->setRowSpacing(0);
    volumeAxisRect->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msBottom);
    volumeAxisRect->setMargins(QMargins(0, 0, 0, 0));
    // create two bar plottables, for positive (green) and negative (red) volume bars:
    plot->setAutoAddPlottableToLegend(false);
    QCPBars *volumePos = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
    QCPBars *volumeNeg = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
    for (int i=0; i<n/5; ++i)
    {
        int v = qrand()%20000+qrand()%20000+qrand()%20000-10000*3;
        (v < 0 ? volumeNeg : volumePos)->addData(startTime+3600*5.0*i, qAbs(v)); // add data to either volumeNeg or volumePos, depending on sign of v
    }
    volumePos->setWidth(3600*4);
    volumePos->setPen(Qt::NoPen);
    volumePos->setBrush(QColor(100, 180, 110));
    volumeNeg->setWidth(3600*4);
    volumeNeg->setPen(Qt::NoPen);
    volumeNeg->setBrush(QColor(180, 90, 90));

    // interconnect x axis ranges of main and bottom axis rects:
    connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), volumeAxisRect->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(volumeAxisRect->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), plot->xAxis, SLOT(setRange(QCPRange)));
    // configure axes of both main and bottom axis rect:
    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeSpec(Qt::UTC);
    dateTimeTicker->setDateTimeFormat("dd. MMMM");
    volumeAxisRect->axis(QCPAxis::atBottom)->setTicker(dateTimeTicker);
    volumeAxisRect->axis(QCPAxis::atBottom)->setTickLabelRotation(15);
    plot->xAxis->setBasePen(Qt::NoPen);
    plot->xAxis->setTickLabels(false);
    plot->xAxis->setTicks(false); // only want vertical grid in main axis rect, so hide xAxis backbone, ticks, and labels
    plot->xAxis->setTicker(dateTimeTicker);
    plot->rescaleAxes();
    plot->xAxis->scaleRange(1.025, plot->xAxis->range().center());
    plot->yAxis->scaleRange(1.1, plot->yAxis->range().center());

    // make axis rects' left side line up:
    QCPMarginGroup *group = new QCPMarginGroup(plot);
    plot->axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, group);
    volumeAxisRect->setMarginGroup(QCP::msLeft|QCP::msRight, group);

    plot->replot();
}

void MainWindow::setupAxisTagDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Axis Tag Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);

    // configure plot to have two right axes:
    plot->yAxis->setTickLabels(false);
    connect(plot->yAxis2, SIGNAL(rangeChanged(QCPRange)), plot->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    plot->yAxis2->setVisible(true);
    plot->axisRect()->addAxis(QCPAxis::atRight);
    plot->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
    plot->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags

    // create graphs:
    QPointer<QCPGraph> mGraph1 = plot->addGraph(plot->xAxis, plot->axisRect()->axis(QCPAxis::atRight, 0));
    QPointer<QCPGraph> mGraph2 = plot->addGraph(plot->xAxis, plot->axisRect()->axis(QCPAxis::atRight, 1));
    mGraph1->setPen(QPen(QColor(250, 120, 0)));
    mGraph2->setPen(QPen(QColor(0, 180, 60)));

    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    AxisTag *mTag1 = new AxisTag(mGraph1->valueAxis());
    mTag1->setPen(mGraph1->pen());
    AxisTag *mTag2 = new AxisTag(mGraph2->valueAxis());
    mTag2->setPen(mGraph2->pen());

    //    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    //    mDataTimer.start(40);

    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout,
            [=]() {

        mGraph1->addData(mGraph1->dataCount(), qSin(mGraph1->dataCount()/50.0)+qSin(mGraph1->dataCount()/50.0/0.3843)*0.25);
        mGraph2->addData(mGraph2->dataCount(), qCos(mGraph2->dataCount()/50.0)+qSin(mGraph2->dataCount()/50.0/0.4364)*0.15);

        // make key axis range scroll with the data:
        plot->xAxis->rescale();
        mGraph1->rescaleValueAxis(false, true);
        mGraph2->rescaleValueAxis(false, true);
        plot->xAxis->setRange(plot->xAxis->range().upper, 100, Qt::AlignRight);

        // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
        double graph1Value = mGraph1->dataMainValue(mGraph1->dataCount()-1);
        double graph2Value = mGraph2->dataMainValue(mGraph2->dataCount()-1);
        mTag1->updatePosition(graph1Value);
        mTag2->updatePosition(graph2Value);
        mTag1->setText(QString::number(graph1Value, 'f', 2));
        mTag2->setText(QString::number(graph2Value, 'f', 2));

        plot->replot();
    }
    );
    timer->start(40);
}

void MainWindow::setupHistoryDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Waterfall Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);

    plot->axisRect()->insetLayout()->setMargins(QMargins(0,0,0,0));

    int nbCurves = 40;
    qreal axisRectWidth = 0.7;
    qreal axisRectHeight = 0.5;

    qreal axisRectPosX = 1-axisRectWidth;
    qreal axisRectPosY = 0.0;

    qreal dX = -1*(1-axisRectWidth) / (nbCurves -1);
    qreal dY = (1-axisRectHeight) / (nbCurves -1);

    plot->yAxis->setVisible(false);
    plot->xAxis->setVisible(false);


    for(int i=nbCurves-1; i>=0; i--) {

        QCPAxisRect *axisRect = new QCPAxisRect(plot);
        axisRect->setMargins(QMargins(0,0,0,0));
        QRectF posRect(axisRectPosX,axisRectPosY,axisRectWidth,axisRectHeight);
        axisRectPosX += dX;
        axisRectPosY += dY;
        plot->axisRect()->insetLayout()->addElement(axisRect, posRect);

        QCPGraph *graph;

        if(i != nbCurves -1) {
            graph = plot->addGraph(axisRect->axis(QCPAxis::atBottom), axisRect->axis(QCPAxis::atLeft));
            graph->setPen(QPen(QColor(0,0,255, 150 - (100*double(i)/double(nbCurves)))));
            graph->setBrush(QBrush(Qt::white));
            axisRect->axis(QCPAxis::atBottom)->setRange(-18,20);
            axisRect->axis(QCPAxis::atLeft)->setRange(-0.1,3);
            axisRect->axis(QCPAxis::atBottom)->grid()->setZeroLinePen(Qt::NoPen);
            axisRect->axis(QCPAxis::atLeft)->grid()->setZeroLinePen(Qt::NoPen);
        } else {

            graph = plot->addGraph(axisRect->axis(QCPAxis::atTop), axisRect->axis(QCPAxis::atRight));
            graph->setPen(QPen(QColor(0,0,255, 150 - (100*double(i)/double(nbCurves)))));
            graph->setBrush(QBrush(Qt::white));
            axisRect->axis(QCPAxis::atTop)->setRange(-18,20);
            axisRect->axis(QCPAxis::atRight)->setRange(-0.1,3);
            axisRect->axis(QCPAxis::atBottom)->setRange(-18,20);
            axisRect->axis(QCPAxis::atLeft)->setRange(-0.1,3);

            axisRect->axis(QCPAxis::atBottom)->grid()->setZeroLinePen(Qt::NoPen);
            axisRect->axis(QCPAxis::atLeft)->grid()->setZeroLinePen(Qt::NoPen);
            axisRect->axis(QCPAxis::atTop)->setVisible(true);
            axisRect->axis(QCPAxis::atRight)->setVisible(true);
            axisRect->axis(QCPAxis::atTop)->setTickLabelSide(QCPAxis::lsInside);
            axisRect->axis(QCPAxis::atRight)->setVisible(true);
            axisRect->axis(QCPAxis::atRight)->setTickLabelSide(QCPAxis::lsInside);


            axisRect->axis(QCPAxis::atTop)->grid()->setVisible(true);
            axisRect->axis(QCPAxis::atRight)->grid()->setVisible(true);
        }

        if(i==0) {
            graph->setPen(QPen(QColor(0,0,255)));
            axisRect->axis(QCPAxis::atBottom)->grid()->setVisible(false);
            axisRect->axis(QCPAxis::atLeft)->grid()->setVisible(false);
            axisRect->axis(QCPAxis::atBottom)->setVisible(true);
            axisRect->axis(QCPAxis::atLeft)->setTickLabelSide(QCPAxis::lsInside);
            axisRect->axis(QCPAxis::atBottom)->setTickLabelSide(QCPAxis::lsInside);
        }

        if(i > 0 ) {
            axisRect->axis(QCPAxis::atBottom)->setVisible(false);
            axisRect->axis(QCPAxis::atLeft)->setVisible(false);
        }

    }

    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout,
            [=]() {

        double secs = QCPAxisTickerDateTime::dateTimeToKey(QDateTime::currentDateTime());
        int n = 500;
        double phase = secs*5;
        double k = 3;
        QVector<double> x(n), y(n);
        //        plot->graph(40)->data().data()->clear();
        for (int i=0; i<n; ++i)
        {
            x[i] = i/(double)(n-1)*34 - 17;
            y[i] = QRandomGenerator::global()->bounded(3.0) * qAbs(qExp(-x[i]*QRandomGenerator::global()->bounded(100.0)*x[i]/20.0)*qSin(k*x[i]+phase));
        }

        for(int j=0; j<nbCurves-1; j++) {
            plot->graph(j)->data()->set(*plot->graph(j+1)->data());
        }

        plot->graph(nbCurves-1)->setData(x, y);

        plot->replot();
    }

    );

    timer->start(250);

}

void MainWindow::setupBitFieldDemo(int row, int col, bool openGl)
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Bitfields Demo");
    widget->setMinimumHeight(400);
    widget->setMaximumHeight(400);

    QCustomPlot *plot = new QCustomPlot();
    plot->setOpenGl(openGl);
    QStatusBar *bar = new QStatusBar();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(widget->windowTitle()), 0);
    layout->addWidget(plot, 1);
    layout->addWidget(bar, 0);
    widget->setLayout(layout);

    _loGrid->addWidget(widget,row,col,1,1);

    QCPTextElement *textValue = new QCPTextElement(plot);
    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    subLayout->setRowSpacing(0);

    plot->plotLayout()->clear();
    plot->plotLayout()->addElement(0, 0, textValue); // insert axis rect in first row
    plot->plotLayout()->addElement(1, 0, subLayout);

    QCPMarginGroup *marginGroup = new QCPMarginGroup(plot);
    for(int i=0; i<16; i++) {
        QCPAxisRect *leftRect = new QCPAxisRect(plot);
        leftRect->setMinimumSize(10, 10);
        QCPAxisRect *rightRect = new QCPAxisRect(plot);
        rightRect->setMinimumSize(10, 10);

        subLayout->addElement(i, 0, leftRect);
        subLayout->addElement(i, 1, rightRect);

        leftRect->setMarginGroup(QCP::msLeft, marginGroup);
        rightRect->setMarginGroup(QCP::msRight, marginGroup);

        QCPGraph *leftGraph = plot->addGraph(leftRect->axis(QCPAxis::atBottom), leftRect->axis(QCPAxis::atLeft));
        leftGraph->valueAxis()->setRange(0, 1);
        leftGraph->keyAxis()->setVisible(false);
        leftGraph->valueAxis()->setTicks(false);
        leftGraph->valueAxis()->setTickLabels(false);
        leftGraph->valueAxis()->grid()->setVisible(false);
        leftGraph->valueAxis()->setLabel(QString::number(i));
        leftGraph->setPen(Qt::NoPen);
        leftGraph->setBrush(Qt::red);
        leftGraph->setLineStyle(QCPGraph::lsStepRight);
        QCPGraph *rightGraph = plot->addGraph(rightRect->axis(QCPAxis::atBottom), rightRect->axis(QCPAxis::atLeft));
        rightGraph->valueAxis()->setRange(0, 1);
        rightGraph->keyAxis()->setVisible(false);
        rightGraph->valueAxis()->setTicks(false);
        rightGraph->valueAxis()->setTickLabels(false);
        rightGraph->valueAxis()->grid()->setVisible(false);
        rightGraph->valueAxis()->setLabel(QString::number(16+i));
        rightGraph->setPen(Qt::NoPen);
        rightGraph->setBrush(Qt::red);
        rightGraph->setLineStyle(QCPGraph::lsStepLeft);
    }

    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout,
            [=]() {
        double secs = QCPAxisTickerDateTime::dateTimeToKey(QDateTime::currentDateTime());
        static quint32 value = 0;
        textValue->setText(QString::number(value) + QString(" - ") + QString::number( value, 16 ));
        std::bitset<32> bits(value);

        for (std::size_t i = 0; i < bits.size(); ++i) {

            QCPAxisRect *ar = qobject_cast<QCPAxisRect*>(subLayout->element(i%16,i/16));
            if(ar) {
                if(bits[i])
                    ar->graphs().at(0)->addData(secs, 1);
                else
                    ar->graphs().at(0)->addData(secs, 0);

                ar->graphs().at(0)->data()->removeBefore(secs-10);
                ar->graphs().at(0)->keyAxis()->rescale();
            }
        }
        value++;
        plot->replot();

    }
    );
    timer->start(100);


}

void MainWindow::setupPlayground(QCustomPlot *customPlot)
{
    Q_UNUSED(customPlot)
}

MainWindow::~MainWindow()
{
    delete ui;
}
