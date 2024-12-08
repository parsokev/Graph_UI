// Suppress non-critical compiler warnings if using Microsoft Visual Studio compiler
#ifdef VS_PRESENT
#pragma warning(disable : 4265 4625 4626 4688 4710 4711 4866 4820 5045 )
#endif

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QButtonGroup>

#include "derived_hashmap.h"

// UI Child of Parent QMainWindow for GUI
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // public slots:

private slots:
    // Declare Private QT Slots/Attributes
    // Open File Action
    void onActionOpenTriggered();

    // Actions for Handling Elements in Vertex Count Selection
    void onActionVertexManualSelected();
    void onActionVertexEstimateSelected();
    void onActionConfirmFileClicked();

    // Actions for Handling Elements in Solution Selection
    void onActionShortestPathSelected();
    void onActionMSTSelected();
    void onActionSrcVertexChanged();
    void onActionDestVertexChanged();

    // Actions for Handling Elements in Displaying and Generating Graphical Images
    void onActionSubmitClicked();
    void onActionDisplayGraphClicked();
    void onActionDisplayImgClicked();

    // protected:

private:
         // Declare Private Instances / Allocated Resources for Class Members
    std::unique_ptr<Ui::MainWindow> ui;
    std::unique_ptr<main_hashmap<double>> main_hash = std::make_unique<main_hashmap<double>>(50);
};

#endif // MAINWINDOW_H
