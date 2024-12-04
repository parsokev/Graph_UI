/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionVertexToggle;
    QAction *actionEstimateVertexClicked;
    QAction *actionManualVertexClicked;
    QWidget *centralwidget;
    QWidget *viewArea;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGroupBox *fileSelectBox;
    QToolButton *openButton;
    QPlainTextEdit *selectedFileText;
    QLabel *fileSelectTitle;
    QRadioButton *estimateVertexButton;
    QRadioButton *manualVertexButton;
    QSpinBox *manualVertexEntry;
    QLabel *manualVertexTitle;
    QLabel *vertexSelectTitle;
    QFrame *fileSelectSeparator;
    QToolButton *confirmFileButton;
    QLabel *progressLabel;
    QLabel *step1Label;
    QLabel *step2Label;
    QLabel *fileNotificationLabel;
    QLabel *fileConfirmationLabel;
    QGroupBox *solutionSelectBox;
    QLabel *solutionSelectTitle;
    QRadioButton *shortestPathButton;
    QRadioButton *mstButton;
    QComboBox *startVertexSelect;
    QComboBox *destVertexSelect;
    QLabel *pathSelectTitle;
    QToolButton *submitButton;
    QLabel *step3Label;
    QLabel *vertexNotificationLabel;
    QToolButton *displayImgButton;
    QToolButton *displayGraphButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionOpen->setMenuRole(QAction::MenuRole::TextHeuristicRole);
        actionVertexToggle = new QAction(MainWindow);
        actionVertexToggle->setObjectName("actionVertexToggle");
        actionVertexToggle->setMenuRole(QAction::MenuRole::TextHeuristicRole);
        actionEstimateVertexClicked = new QAction(MainWindow);
        actionEstimateVertexClicked->setObjectName("actionEstimateVertexClicked");
        actionEstimateVertexClicked->setMenuRole(QAction::MenuRole::TextHeuristicRole);
        actionManualVertexClicked = new QAction(MainWindow);
        actionManualVertexClicked->setObjectName("actionManualVertexClicked");
        actionManualVertexClicked->setMenuRole(QAction::MenuRole::TextHeuristicRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        viewArea = new QWidget(centralwidget);
        viewArea->setObjectName("viewArea");
        viewArea->setGeometry(QRect(10, 10, 781, 571));
        viewArea->setAutoFillBackground(false);
        viewArea->setStyleSheet(QString::fromUtf8(""));
        scrollArea = new QScrollArea(viewArea);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(-20, -20, 811, 581));
        scrollArea->setStyleSheet(QString::fromUtf8(""));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 809, 579));
        fileSelectBox = new QGroupBox(scrollAreaWidgetContents);
        fileSelectBox->setObjectName("fileSelectBox");
        fileSelectBox->setGeometry(QRect(40, 10, 721, 321));
        fileSelectBox->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        fileSelectBox->setAutoFillBackground(false);
        fileSelectBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
" border: 1px solid black;\n"
"	background-color: rgb(199, 199, 199);\n"
"	background-color: rgb(170, 170, 255);\n"
"}"));
        fileSelectBox->setAlignment(Qt::AlignmentFlag::AlignCenter);
        fileSelectBox->setFlat(false);
        openButton = new QToolButton(fileSelectBox);
        openButton->setObjectName("openButton");
        openButton->setGeometry(QRect(480, 70, 81, 31));
        openButton->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border: 1px solid black;\n"
"	\n"
"	background-color: rgb(210, 210, 210);\n"
"	font: 700 9pt \"Arial\";\n"
"}"));
        selectedFileText = new QPlainTextEdit(fileSelectBox);
        selectedFileText->setObjectName("selectedFileText");
        selectedFileText->setGeometry(QRect(80, 70, 401, 31));
        selectedFileText->setStyleSheet(QString::fromUtf8("QPlainTextEdit {\n"
"border: 1px solid black;\n"
"}\n"
""));
        selectedFileText->setTabChangesFocus(true);
        selectedFileText->setBackgroundVisible(false);
        fileSelectTitle = new QLabel(fileSelectBox);
        fileSelectTitle->setObjectName("fileSelectTitle");
        fileSelectTitle->setGeometry(QRect(200, 30, 311, 21));
        fileSelectTitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	color: maroon;\n"
"	font: 12pt \"Javanese Text\";\n"
"}"));
        fileSelectTitle->setTextFormat(Qt::TextFormat::RichText);
        estimateVertexButton = new QRadioButton(fileSelectBox);
        estimateVertexButton->setObjectName("estimateVertexButton");
        estimateVertexButton->setGeometry(QRect(50, 200, 331, 20));
        estimateVertexButton->setStyleSheet(QString::fromUtf8("QRadioButton{\n"
"	font: 700 10pt \"Arial\";\n"
"	color: rgb(0, 85, 0);\n"
"}"));
        manualVertexButton = new QRadioButton(fileSelectBox);
        manualVertexButton->setObjectName("manualVertexButton");
        manualVertexButton->setGeometry(QRect(410, 200, 191, 16));
        manualVertexButton->setStyleSheet(QString::fromUtf8("QRadioButton{\n"
"	font: 700 10pt \"Arial\";\n"
"	color: rgb(0, 85, 0);\n"
"}"));
        manualVertexEntry = new QSpinBox(fileSelectBox);
        manualVertexEntry->setObjectName("manualVertexEntry");
        manualVertexEntry->setGeometry(QRect(460, 240, 141, 21));
        manualVertexEntry->setStyleSheet(QString::fromUtf8(""));
        manualVertexEntry->setAlignment(Qt::AlignmentFlag::AlignCenter);
        manualVertexEntry->setReadOnly(false);
        manualVertexEntry->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::PlusMinus);
        manualVertexEntry->setProperty("showGroupSeparator", QVariant(false));
        manualVertexEntry->setMaximum(1000);
        manualVertexEntry->setValue(5);
        manualVertexTitle = new QLabel(fileSelectBox);
        manualVertexTitle->setObjectName("manualVertexTitle");
        manualVertexTitle->setGeometry(QRect(450, 220, 221, 20));
        manualVertexTitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	font: 10pt \"Javanese Text\";\n"
"}"));
        vertexSelectTitle = new QLabel(fileSelectBox);
        vertexSelectTitle->setObjectName("vertexSelectTitle");
        vertexSelectTitle->setGeometry(QRect(190, 150, 491, 21));
        vertexSelectTitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	color: maroon;\n"
"	font: 12pt \"Javanese Text\";\n"
"}"));
        vertexSelectTitle->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        fileSelectSeparator = new QFrame(fileSelectBox);
        fileSelectSeparator->setObjectName("line");
        fileSelectSeparator->setGeometry(QRect(-10, 120, 731, 20));
        fileSelectSeparator->setStyleSheet(QString::fromUtf8(""));
        fileSelectSeparator->setFrameShape(QFrame::Shape::HLine);
        fileSelectSeparator->setFrameShadow(QFrame::Shadow::Sunken);
        confirmFileButton = new QToolButton(fileSelectBox);
        confirmFileButton->setObjectName("confirmFileButton");
        confirmFileButton->setGeometry(QRect(270, 280, 141, 31));
        confirmFileButton->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	font: 9pt \"Franklin Gothic Medium\";\n"
"	border: 1px solid firebrick;\n"
"	background-color: rgb(230, 230, 230);\n"
"}"));
        progressLabel = new QLabel(fileSelectBox);
        progressLabel->setObjectName("progressLabel");
        progressLabel->setGeometry(QRect(210, 220, 281, 20));
        progressLabel->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	color: rgb(85, 255, 0);\n"
"	font: 700 italic 10pt \"Calibri\";\n"
"}"));
        step1Label = new QLabel(fileSelectBox);
        step1Label->setObjectName("step1Label");
        step1Label->setGeometry(QRect(170, 30, 21, 20));
        step1Label->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	border: 1px solid darkslategrey;\n"
"	font: 12pt \"Verdana\";\n"
"	color: green;\n"
"	background-color: rgb(214, 107, 0);\n"
"}"));
        step1Label->setFrameShape(QFrame::Shape::Box);
        step1Label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        step2Label = new QLabel(fileSelectBox);
        step2Label->setObjectName("step2Label");
        step2Label->setGeometry(QRect(160, 150, 21, 20));
        step2Label->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	border: 1px solid darkslategrey;\n"
"	font: 12pt \"Verdana\";\n"
"	color: green;\n"
"	background-color: rgb(214, 107, 0);\n"
"}"));
        step2Label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        fileNotificationLabel = new QLabel(fileSelectBox);
        fileNotificationLabel->setObjectName("fileNotificationLabel");
        fileNotificationLabel->setGeometry(QRect(80, 106, 401, 20));
        fileNotificationLabel->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	font: italic 10pt \"Calibri\";\n"
"	color: crimson;\n"
"}"));
        fileConfirmationLabel = new QLabel(fileSelectBox);
        fileConfirmationLabel->setObjectName("fileConfirmationLabel");
        fileConfirmationLabel->setGeometry(QRect(10, 180, 681, 20));
        fileConfirmationLabel->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	font: 600 italic 9pt \"Lucida Sans\";\n"
"	color: navajowhite;\n"
"}\n"
""));
        solutionSelectBox = new QGroupBox(scrollAreaWidgetContents);
        solutionSelectBox->setObjectName("solutionSelectBox");
        solutionSelectBox->setGeometry(QRect(40, 330, 721, 181));
        solutionSelectBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"	background-color: rgb(170, 170, 255);\n"
"	border: 1px solid black;\n"
"}"));
        solutionSelectTitle = new QLabel(solutionSelectBox);
        solutionSelectTitle->setObjectName("solutionSelectTitle");
        solutionSelectTitle->setGeometry(QRect(200, 20, 331, 20));
        solutionSelectTitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	color: maroon;\n"
"	font: 12pt \"Javanese Text\";\n"
"}"));
        solutionSelectTitle->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        shortestPathButton = new QRadioButton(solutionSelectBox);
        shortestPathButton->setObjectName("shortestPathButton");
        shortestPathButton->setGeometry(QRect(40, 60, 141, 16));
        shortestPathButton->setStyleSheet(QString::fromUtf8("QRadioButton{\n"
"	font: 700 10pt \"Arial\";\n"
"	color: rgb(0, 85, 0);\n"
"}"));
        mstButton = new QRadioButton(solutionSelectBox);
        mstButton->setObjectName("mstButton");
        mstButton->setGeometry(QRect(390, 60, 231, 16));
        mstButton->setStyleSheet(QString::fromUtf8("QRadioButton{\n"
"	font: 700 10pt \"Arial\";\n"
"	color: rgb(0, 85, 0);\n"
"}"));
        startVertexSelect = new QComboBox(solutionSelectBox);
        startVertexSelect->setObjectName("startVertexSelect");
        startVertexSelect->setGeometry(QRect(40, 100, 231, 22));
        startVertexSelect->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"	font: 9pt \"Arial\";\n"
"	border: 1px solid black;\n"
"}"));
        destVertexSelect = new QComboBox(solutionSelectBox);
        destVertexSelect->setObjectName("destVertexSelect");
        destVertexSelect->setGeometry(QRect(40, 130, 231, 22));
        destVertexSelect->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"	font: 9pt \"Arial\";\n"
"	border: 1px solid black;\n"
"}"));
        pathSelectTitle = new QLabel(solutionSelectBox);
        pathSelectTitle->setObjectName("pathSelectTitle");
        pathSelectTitle->setGeometry(QRect(-10, 80, 251, 21));
        pathSelectTitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	color: darkbrown;\n"
"	font: 10pt \"Javanese Text\";\n"
"}"));
        pathSelectTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        submitButton = new QToolButton(solutionSelectBox);
        submitButton->setObjectName("submitButton");
        submitButton->setGeometry(QRect(560, 140, 151, 31));
        submitButton->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border: 1px solid red;\n"
"	font: 10pt \"Franklin Gothic Medium\";\n"
"	background-color: rgb(239, 239, 239);\n"
"}"));
        step3Label = new QLabel(solutionSelectBox);
        step3Label->setObjectName("step3Label");
        step3Label->setGeometry(QRect(170, 20, 21, 20));
        step3Label->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	border: 1px solid darkslategrey;\n"
"	font: 12pt \"Verdana\";\n"
"	color: green;\n"
"	background-color: rgb(214, 107, 0);\n"
"}"));
        step3Label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        vertexNotificationLabel = new QLabel(solutionSelectBox);
        vertexNotificationLabel->setObjectName("vertexNotificationLabel");
        vertexNotificationLabel->setGeometry(QRect(30, 156, 351, 20));
        vertexNotificationLabel->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	font: italic 10pt \"Calibri\";\n"
"	color: crimson;\n"
"}"));
        displayImgButton = new QToolButton(scrollAreaWidgetContents);
        displayImgButton->setObjectName("displayImgButton");
        displayImgButton->setGeometry(QRect(400, 530, 231, 31));
        displayImgButton->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	border: 1px solid black;\n"
"	font: 11pt \"Javanese Text\";\n"
"	background-color: rgb(255, 170, 127);\n"
"}"));
        displayGraphButton = new QToolButton(scrollAreaWidgetContents);
        displayGraphButton->setObjectName("displayGraphButton");
        displayGraphButton->setGeometry(QRect(160, 530, 221, 31));
        displayGraphButton->setStyleSheet(QString::fromUtf8("QToolButton{\n"
"	border: 1px solid black;\n"
"	background-color: rgb(255, 255, 127);\n"
"	font: 11pt \"Javanese Text\";\n"
"}"));
        scrollArea->setWidget(scrollAreaWidgetContents);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 18));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        statusbar->setStyleSheet(QString::fromUtf8("background-color: ghostwhite;\n"
"font: 10pt \"Calibri\";\n"
"color: lightcoral;"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionVertexToggle->setText(QCoreApplication::translate("MainWindow", "VertexToggle", nullptr));
        actionEstimateVertexClicked->setText(QCoreApplication::translate("MainWindow", "EstimateVertexClicked", nullptr));
        actionManualVertexClicked->setText(QCoreApplication::translate("MainWindow", "ManualVertexClicked", nullptr));
        fileSelectBox->setTitle(QString());
#if QT_CONFIG(tooltip)
        openButton->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Select a text file containing the specified format of  `vertex1, vertex2, distance/cost value` for each unique edge present in the graph to be processed</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        openButton->setText(QCoreApplication::translate("MainWindow", "Select Text File", nullptr));
        fileSelectTitle->setText(QCoreApplication::translate("MainWindow", "Select A Text File to Process", nullptr));
#if QT_CONFIG(tooltip)
        estimateVertexButton->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Program will estimate total number of unique verticies based on a preset graph density and the number of edges detected in selected text file</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        estimateVertexButton->setText(QCoreApplication::translate("MainWindow", "Have Program Estimate (Based on Selected File)", nullptr));
#if QT_CONFIG(tooltip)
        manualVertexButton->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Program will accept a manually-entered value provided by user</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        manualVertexButton->setText(QCoreApplication::translate("MainWindow", "Provide Manually", nullptr));
        manualVertexTitle->setText(QCoreApplication::translate("MainWindow", "Enter the Total Number of Verticies:", nullptr));
        vertexSelectTitle->setText(QCoreApplication::translate("MainWindow", "Select Method for Estimating Total Number of Graph Verticies", nullptr));
#if QT_CONFIG(tooltip)
        confirmFileButton->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Submit text file for processing and organizing graph information for generating pathing solutions</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        confirmFileButton->setText(QCoreApplication::translate("MainWindow", "Confirm File Information", nullptr));
        progressLabel->setText(QString());
        step1Label->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        step2Label->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        fileNotificationLabel->setText(QString());
        fileConfirmationLabel->setText(QString());
        solutionSelectBox->setTitle(QString());
        solutionSelectTitle->setText(QCoreApplication::translate("MainWindow", "Select Graphical Solution Type", nullptr));
#if QT_CONFIG(tooltip)
        shortestPathButton->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Path with shortest total distance that connects a selected starting vertex to a specified destination vertex</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        shortestPathButton->setText(QCoreApplication::translate("MainWindow", "Shortest Path", nullptr));
#if QT_CONFIG(tooltip)
        mstButton->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Collection of edges that connect all of the verticies in graph with the minimum total cost/distance</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        mstButton->setText(QCoreApplication::translate("MainWindow", "Minimum Spanning Tree (MST)", nullptr));
        pathSelectTitle->setText(QCoreApplication::translate("MainWindow", "Select Verticies for Shortest Path:", nullptr));
#if QT_CONFIG(tooltip)
        submitButton->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Generate the Images of the Complete Graph and the Request Solution Type</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        submitButton->setText(QCoreApplication::translate("MainWindow", "Generate Solution Image", nullptr));
        step3Label->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        vertexNotificationLabel->setText(QString());
        displayImgButton->setText(QCoreApplication::translate("MainWindow", "View Generated Solution", nullptr));
        displayGraphButton->setText(QCoreApplication::translate("MainWindow", "View Generated Full Graph", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
