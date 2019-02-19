#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datareader.h"
#include <qwt_thermo.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initToolBar();
    void initQwtThermo();
    void repaintQwtThermo();
    QColor getPixelColor(int x, int y);

private Q_SLOTS:
    void on_pbOpen_clicked();
    void slotSetDrawMesh(bool aState);
    void slotSetMouseTracking(bool aState);

private:
    Ui::MainWindow *ui;
    dataReader *mData;

    QAction *actMesh;
    QAction *actMouse;

    QwtThermo *mThermo;
};

#endif // MAINWINDOW_H
