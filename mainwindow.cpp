#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initToolBar();
    initQwtThermo();

    ui->spectrGLwidget->setHandleToMainWindow(this);
    mData = new dataReader();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initToolBar()
{
    actMesh = new QAction(" Сетка ", this);
    actMesh->setCheckable(true);
    actMesh->setChecked(true);
    connect(actMesh, SIGNAL(triggered(bool)), this, SLOT(slotSetDrawMesh(bool)));

    actMouse = new QAction(" Мышь ", this);
    actMouse->setCheckable(true);
    actMouse->setChecked(false);
    connect(actMouse, SIGNAL(triggered(bool)), this, SLOT(slotSetMouseTracking(bool)));

    ui->mainToolBar->addAction(actMesh);
    ui->mainToolBar->addAction(actMouse);
}

void MainWindow::initQwtThermo()
{
    mThermo = new QwtThermo(this);
    mThermo->setOrientation(Qt::Vertical);
    mThermo->setScalePosition(QwtThermo::LeadingScale);

    QVBoxLayout *layout = new QVBoxLayout( ui->qwtTermoWidget );
    layout->addWidget(mThermo);
    ui->qwtTermoWidget->setLayout(layout);
}

void MainWindow::repaintQwtThermo()
{
    mThermo->setScale(ui->spectrGLwidget->getMinData(), ui->spectrGLwidget->getMaxData());
    ColorMap *colorMap = new ColorMap();

    mThermo->setColorMap(colorMap);
    mThermo->setPipeWidth(10);
    mThermo->setValue(ui->spectrGLwidget->getMaxData());
    mThermo->setScalePosition(QwtThermo::LeadingScale);
    mThermo->setScaleMaxMajor( 10 );
    mThermo->setScaleMaxMinor( 5 );
}

QColor MainWindow::getPixelColor(int x, int y)
{
    return QColor(ui->spectrGLwidget->grabFrameBuffer().pixel(x, y));
}

void MainWindow::on_pbOpen_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    if(mData->readMesh(path))
    {
        ui->spectrGLwidget->getMesh(*mData);
        repaintQwtThermo();
    }
    else
        QMessageBox::information(NULL, "Error", "Wrong filename.");
}

void MainWindow::slotSetDrawMesh(bool aState)
{
    ui->spectrGLwidget->setDrawMesh(aState);
}

void MainWindow::slotSetMouseTracking(bool aState)
{
    ui->spectrGLwidget->setMouseTrackSt(aState);
    ui->spectrGLwidget->update();
}
