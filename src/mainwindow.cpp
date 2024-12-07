#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "derived_hashmap.h"
#include "graph_processing.h"
#include "graph_input.h"
#include "gprintf.h"


#include <QImage>
#include <QtWidgets>
#include <QFileDialog>
#include <QDir>
#include <QPixmap>
#include <QImageReader>

/* Set paths to resource directories according to build path defined by CMake Configuration/Build Type
 * 'RELEASE' = App Deployment -> Build path = CMAKE_SOURCE_DIR/<deploy-directory>
 * 'DEBUG' or 'RELDEBUG' = Local Build -> Build path = CMAKE_SOURCE_DIR/build/<local-config-directory>
*/
#ifdef RELEASE
// Relative Paths for deployed executable that is within same directory as the executable
std::string path_filename = "./dot_graphs/shortest_path_overlay.gv";
std::string MST_filename = "./dot_graphs/MST_overlay.gv";
std::string graph_filename = "./dot_graphs/full_graph.gv";
std::string graphviz_path = "./Graphviz/bin/";
std::string MST_image = "./graph_images/MST_overlay.png";
std::string SP_image = "./graph_images/shortest_path_overlay.png";
QString graphDestination = "./graph_images/full_graph.png";
QString starting_file = "./sample_graphs";
#else
// Relative Paths for locally built executable that is two levels below resource files
std::string path_filename = "../../dot_graphs/shortest_path_overlay.gv";
std::string MST_filename = "../../dot_graphs/MST_overlay.gv";
std::string graph_filename = "../../dot_graphs/full_graph.gv";
std::string graphviz_path = "../../Graphviz/bin/";
std::string MST_image = "../../graph_images/MST_overlay.png";
std::string SP_image = "../../graph_images/shortest_path_overlay.png";
QString graphDestination = "../../graph_images/full_graph.png";
QString starting_file = "../../sample_graphs";
#endif

// Instead of using direct commands, program uses pre-made shell scripts for Linux OS
#ifdef __linux__
std::string Linux_SP_script = "../../scripts/Linux/visualize_graph_SP.sh";
std::string Linux_MST_script = "../../scripts/Linux/visualize_graph_MST.sh";
#endif

// Qt QString variables storing updated platform-selective text file/graph image locations
QString filename = "";  // Name of Selected Text File to Process
QString filepath = "";  // Name of Absolute Path to Selected Text File
QString requestedSolution = "";
QString requestedVertexMethod = "";
QString solutionDestination = "";
std::string c_filename;

// Conversions of QString variables that are used for pipeline script commands
std::string file_name = "";
std::string file_path = "";
std::string requested_solution = "";

// Handles tracking/storage of program-estimated or user-entered vertex count values
unsigned int vertex_count = 0;

// Main Application Window instance
MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Initialize UI and Basic Application Window Settings
    ui->setupUi(this);
    this->setWindowTitle("Welcome To Graph Path UI");
    ui->openButton->setText("Select Text File");
    // Toggle Display of UI elements that should not be initially be interacted with
    ui->manualVertexButton->hide();
    ui->estimateVertexButton->hide();
    ui->vertexSelectTitle->hide();
    ui->manualVertexEntry->hide();
    ui->manualVertexTitle->hide();
    ui->pathSelectTitle->hide();
    ui->step3Label->hide();
    ui->solutionSelectTitle->hide();
    ui->mstButton->hide();
    ui->shortestPathButton->hide();
    ui->startVertexSelect->hide();
    ui->destVertexSelect->hide();
    ui->submitButton->hide();
    ui->confirmFileButton->hide();
    ui->progressLabel->hide();
    ui->displayImgButton -> hide();
    ui->displayGraphButton->hide();
    ui->step2Label->hide();
    ui->fileNotificationLabel->setText("Invalid Selected Text File. Select Another File");
    ui->fileNotificationLabel->hide();
    ui->vertexNotificationLabel->setText("Invalid Vertex Combination");
    ui->vertexNotificationLabel->hide();
    ui->fileConfirmationLabel->setText("File selection is now disabled. If you wish to use a different file, close and restart the application");
    ui->fileConfirmationLabel->hide();


    // Preintialize Values for Hidden Elements that will be Revealed
    ui->startVertexSelect->setPlaceholderText("Select Starting Vertex");
    ui->destVertexSelect->setPlaceholderText("Select Destination Vertex");

    statusBar()->showMessage("Welcome to GraphUI. Please Select Text File for Processing and Provide a Form for Vertex Estimation");

    // Manage Connections between Event Handlers of UI and MainWindow Instance's Member Functions
    // File Selection Events
    ui->openButton->setDefaultAction(ui->actionOpen);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onActionOpenTriggered);


    // Vertex Selection Events
    connect(ui->estimateVertexButton, &QRadioButton::clicked, this, &MainWindow::onActionVertexEstimateSelected);
    connect(ui->manualVertexButton, &QRadioButton::clicked, this, &MainWindow::onActionVertexManualSelected);

    // File Confirmation Events
    connect(ui->confirmFileButton, &QToolButton::clicked, this, &MainWindow::onActionConfirmFileClicked);

    // Path Solution Selection Events
    connect(ui->shortestPathButton, &QRadioButton::clicked, this, &MainWindow::onActionShortestPathSelected);
    connect(ui->startVertexSelect, &QComboBox::currentIndexChanged, this, &MainWindow::onActionSrcVertexChanged);
    connect(ui->destVertexSelect, &QComboBox::currentIndexChanged, this, &MainWindow::onActionDestVertexChanged);
    connect(ui->mstButton, &QRadioButton::clicked, this, &MainWindow::onActionMSTSelected);

    // Final Submission and Generated Image Viewing Events
    connect(ui->submitButton, &QToolButton::clicked, this, &MainWindow::onActionSubmitClicked);
    connect(ui->displayImgButton, &QToolButton::clicked, this, &MainWindow::onActionDisplayImgClicked);
    connect(ui->displayGraphButton, &QToolButton::clicked, this, &MainWindow::onActionDisplayGraphClicked);
}

// Event Handler for Clicking in "Open" Button that triggers File Dialog Window
void MainWindow::onActionOpenTriggered()
{
    filename = "";    // Holds name of selected text file (displayed to user in text bar)
    filepath = "";   // Holds absolute path to selected text file

    // Generate and Display File Selection Window for User to Select Text File with Graphical Information
    QFileDialog fileDialog(this, tr("Select Text File"), starting_file);
    bool verified_file = false;
    // Restrict File Selection to Text Files
    fileDialog.setNameFilter(tr("Text files (*.txt)"));
    if(fileDialog.exec()) {
        // Verify User Selected a Text File and Retrieve its Path for Referencing
        filepath = fileDialog.selectedFiles().constFirst();
        QFile *file = new QFile(filepath);
        QFileInfo fileinfo(*file);
        filename = fileinfo.fileName();
        if (fileinfo.size() > 0){
            // If User Selected a Text File, Display Name to User and Proceed to Display Next Section
            ui->selectedFileText->setStyleSheet("QPlainTextEdit{font: 10pt \"Gill Sans MT\"; color:limegreen;}");
            ui->selectedFileText->setPlainText(filename);
            verified_file = true;
        }

        if (!verified_file) {
            // Display Error Message and Disable Vertex Selection Buttons if File is Invalid
            filename = "";
            ui->manualVertexButton->setEnabled(false);
            ui->estimateVertexButton->setEnabled(false);
            ui->step3Label->hide();
            ui->solutionSelectTitle->hide();
            ui->mstButton->hide();
            ui->shortestPathButton->hide();
            ui->submitButton->hide();
            ui->selectedFileText->setStyleSheet("QPlainTextEdit{font: 10pt \"Gill Sans MT\"; color: crimson;}");
            ui->selectedFileText->setPlainText("Invalid File Selected!");

            ui->fileNotificationLabel->setVisible(true);
            this->statusBar()->setStyleSheet("QStatusBar{background-color: ghostwhite; font: 10pt \"Gill Sans MT\"; color: crimson;}");
            this->statusBar()->showMessage("File is not a valid text file! Please select an existing text file that is not empty to proceed");
        } else {
            // Make Vertex Information Form Visible Upon Verifying Selected File Exists and is not Empty
            QString fileNotification = filename;
            fileNotification.append(" is valid. Please choose method of vertex selection to begin processing of file");
            ui->estimateVertexButton->setVisible(true);
            ui->manualVertexButton->setVisible(true);
            ui->vertexSelectTitle->setVisible(true);
            ui->step3Label->setVisible(false);
            ui->solutionSelectTitle->setVisible(false);
            ui->mstButton->setVisible(false);
            ui->shortestPathButton->setVisible(false);
            ui->submitButton->setVisible(false);
            ui->manualVertexButton->setEnabled(true);
            ui->estimateVertexButton->setEnabled(true);
            ui->step2Label->setVisible(true);
            ui->fileNotificationLabel->setVisible(false);
            this->statusBar()->setStyleSheet("QStatusBar{background-color: ghostwhite; font: 10pt \"Gill Sans MT\"; color: limegreen;}");
            this->statusBar()->showMessage(fileNotification);
        }
        delete file;    // Cleanup allocation for QFile object
    }
}

// Event Handler triggered by Clicking on Estimate Vertex Count Radio Button
void MainWindow::onActionVertexEstimateSelected()
{
    // Verify Selected File is Valid before Allowing Access to Solution Selection
    if (filename.length() == 0){
        // If User Changed/Cleared Selected Text File after Intial Validation, Prevent Proceeding Further until Validated
        this->statusBar()->setStyleSheet("QStatusBar{background-color: ghostwhite; font: 10pt \"Gill Sans MT\"; color: crimson;}");
        this->statusBar()->showMessage("File is not a valid text file! Please select an existing text file that is not empty to proceed");
        ui->confirmFileButton->setVisible(false);
        ui->fileNotificationLabel->setVisible(true);
    } else {
        // Else, Toggle Selection Mode to Instruct Program to Execute Script to Retrieve Line Count of Selected Text File
        requestedVertexMethod = "Automatic";
        ui->confirmFileButton->setVisible(true);
        ui->fileNotificationLabel->setVisible(false);
    }
    // Toggle Visibility of too Hide UI elements for Receiving Manually-Entered Value for Total Vertex Count from User
    ui->manualVertexEntry->hide();
    ui->manualVertexTitle->hide();
}

// Event Handler triggered by Clicking on Manually Entry of Vertex Count Radio Button
void MainWindow::onActionVertexManualSelected()
{
    // Verify Selected File is Valid before Allowing Access to Solution Selection
    if (filename.length() == 0){
        // If User Changed/Cleared Selected Text File after Intial Validation, Prevent Proceeding Further until Validated
        this->statusBar()->setStyleSheet("QStatusBar{background-color: ghostwhite; font: 10pt \"Gill Sans MT\"; color: crimson;}");
        this->statusBar()->showMessage("File is not a valid text file! Please select an existing text file that is not empty to proceed");
        ui->confirmFileButton->setVisible(false);
        ui->fileNotificationLabel->setVisible(true);
    } else {
        // Else, Toggle Selection Mode to Instruct Program to Retrieve Value of Total Vertex Count from Value Entered by User
        ui->confirmFileButton->setVisible(true);
        ui->fileNotificationLabel->setVisible(false);
        requestedVertexMethod = "Manual";
    }
    // Toggle Visibility to Reveal UI elements for Receiving Manually-Entered Value for Total Vertex Count from User
    ui->manualVertexEntry->setVisible(true);
    ui->manualVertexTitle->setVisible(true);
}

// Event Handler triggered by Clicking the File Confirmation Button
void MainWindow::onActionConfirmFileClicked()
{
    /*
     * Due to Time-Delay Incurred by:
     * - Executing Pipelined Shell Commands to Retrieve Line Count of Selected Text File
     * - Pre-Allocating Memory for Container used to Store and Organize Graphical Information from Selected Text File
     *
     *  Generate and Display a Window Notifying the User of Program Progress as Soon as Program Begins Processing
    */
    QProgressDialog fileBuildBar("Parsing Selected Text File...", nullptr, 0, 100);
    fileBuildBar.setStyleSheet("QProgressDialog{font: 700 10pt \"Sylfaen\";} QLabel{font: 700 10pt \"Sylfaen\"; color: rgb(0, 85, 0);}");
    fileBuildBar.setMinimumDuration(0);
    fileBuildBar.setWindowTitle("File Validation Progress");
    QApplication::processEvents();

    // Verify Selected File is Valid before Allowing Access to Solution Selection
    if (filename.length() == 0){
        // In User Changes/Deselects File After Completing Vertex Selection/Entry, Prevent Further Progress
        this->statusBar()->setStyleSheet("QStatusBar{background-color: ghostwhite; font: 10pt \"Gill Sans MT\"; color: crimson;}");
        this->statusBar()->showMessage("Graph Text File is Invalid! Please select a text file containing the graph information before proceeding");
        ui->fileNotificationLabel->setVisible(true);
        // Prevent User from Accessing UI Elements that are Populated with Data Extracted from User-Selected Text file
        ui->step3Label->hide();
        ui->solutionSelectTitle->hide();
        ui->mstButton->hide();
        ui->shortestPathButton->hide();
        ui->confirmFileButton->hide();
    } else {
        /*
         * Build main_hashmap Container to Store Relevant Graphical Information Extracted from User-Provided Text File
         * Write Relevant Extracted Information in Dot Language Format to Designated .gv File for Building Graph Visualization
        */

        // If Text File Submitted by User is an Existing Text FIle, Proceed with Reading File and Extracting Edge Information
        ui->openButton->setEnabled(false);
        ui->estimateVertexButton->setEnabled(false);
        ui->manualVertexButton->setEnabled(false);
        ui->fileNotificationLabel->setVisible(false);
        // Update ProgressBar to Indicate Progression to User and Change Element State for Continued Display of Progress
        fileBuildBar.setValue(10);
        fileBuildBar.setLabelText("Assessing User Vertex Input...");
        QApplication::processEvents();

        // Preallocate Memory for Container Storing Graphical Information Based on Total Number of Unique Verticies and Begin Processing of Text File
        if (requestedVertexMethod == "Automatic") {
            /*
             * If User Selected Mode Instructing Program to Estimate Total Number of Unique Verticies from Selected Graph File:
             * - Execute OS-Compatible Shell Commands through Pipeline To Retrieve Total Number of Lines in Selected Text File
             * - Expected File Format requires each Line denotes a Unique Edge and Is Used to Estimate Vertex Count for a Graph of Medium Density
             * - Preallocate Memory for Customized Unordered Map Container to Efficiently Build an Adjancency List while Parsing Selected Text File
             * - Verify Read Operation Success and Prepopulate UI Elements to Display Solution Selection Data to User
             */
            // Update Progress Bar and UI Element State to Assure User of Progress
            this->statusBar()->setStyleSheet("QStatusBar{background-color: ghostwhite; font: 10pt \"Gill Sans MT\"; color: limegreen;}");
            this->statusBar()->showMessage("Estimating Number of Verticies based on Selected Text File...");
            c_filename = filename.toStdString();
            gprintf("Estimating number of unique verticies from '%s'...\n", c_filename.c_str());
            fileBuildBar.setValue(25);
            fileBuildBar.setLabelText("Estimating Number of Verticies based on Selected Text File...");
            QApplication::processEvents();

            // Execute Piped Shell Command to get line count of selected text file and store calculated vertex count in referenced variable
            int approx_output = 0;
            file_path = filepath.toStdString();
            approx_output = approximate_graph_vertex_count(vertex_count, file_path);
            if (approx_output < 0) {
                std::cerr << "An Error was encountered in generating estimated vertex_count";
                QMessageBox reportEstimateError;
                reportEstimateError.setIcon(QMessageBox::Critical);
                reportEstimateError.setText("Error(s) were encountered while attempting estimate the vertex count from the selected text file");
                reportEstimateError.setInformativeText("Shell commands used to estimate the number of verticies in the file failed to execute properly."
                                                       "\nThe Local OS may not be compatible with the commands or requires elevated permissions to execute\n"
                                                       "Please restart the application and manually provide an estimated value for vertex count if you wish to continue.");
                reportEstimateError.setWindowTitle("Shell Command Error Encountered");
                reportEstimateError.exec();
                QApplication::exit(1);
                return;
            }
            // Display update if successful
            QString estVtoNum = estVtoNum.number(vertex_count);
            QString updateEstimateMsg = "Estimation Complete! Estimated Total Number of Unique Verticies: ";
            updateEstimateMsg.append(estVtoNum);
            this->statusBar()->showMessage(updateEstimateMsg);
        } else if (requestedVertexMethod == "Manual"){
            /*
             * If User Selected Mode Instructing Program to Use the Value Entered by the User as the Number of Total Unique Vertices:
             * - Preallocate Memory for Customized Unordered Map Container using Value Provided to Increase Processing Performance
             * - Build an Adjancency List while Parsing Selected Text File
             * - Verify Read Operation Success and Prepopulate UI Elements to Display Solution Selection Data to User
             */

            // Update Progress Bar and UI Element State to Assure User of Progress
            this->statusBar()->setStyleSheet("QStatusBar{background-color: ghostwhite; font: 10pt \"Gill Sans MT\"; color: limegreen;}");
            this->statusBar()->showMessage("Using Provided Number of Verticies to Decrease File Processing Time...");
            c_filename = filename.toStdString();
            gprintf("Estimating number of unique verticies from '%s'...\n", c_filename.c_str());
            fileBuildBar.setValue(25);
            fileBuildBar.setLabelText("Using Provided Number of Verticies to Decrease File Processing Time...");
            QApplication::processEvents();

            // Read and Store Value Entered by User (Adjust accordingly if Entered Value is unfeasible)
            vertex_count = ui->manualVertexEntry->value();
            ui->manualVertexEntry->setEnabled(false);
            if (vertex_count <= 0) {
                vertex_count = 5;
            }
        } else {
            std::cerr << "Unexpected value of requested Solution type received\n";
            QMessageBox reportUnexpectedError;
            reportUnexpectedError.setIcon(QMessageBox::Critical);
            reportUnexpectedError.setText("Error(s) were encountered while attempting to determine selected vertex estimation type");
            reportUnexpectedError.setInformativeText("An unexpected value was received for the selected request vertex estimation type.\n"
                                                     "Please restart the application and try again.");
            reportUnexpectedError.setWindowTitle("Unexpected Vertex Request Read Error");
            reportUnexpectedError.exec();
            QApplication::exit(1);
            return;
        }
        gprintf("Process finished processing vertex count input. Building unordered map container...");

        // Initialize Storage Container with Allocated Storage Capacity According Vertex Count Value
        unsigned int file_vertex_count = static_cast<unsigned int>(vertex_count);
        auto main = std::make_unique<main_hashmap<double>>(file_vertex_count);
        *(this->main_hash) = std::move(*main);

        // Initialize Variables for Passing to Function for Reading File and Storing Parsed Information
        int output = 0;
        file_name = filepath.toStdString();

        // Update Progress Notification
        gprintf("Building graph from '%s' file contents...", c_filename.c_str());
        gprintf("Writing graph information to file '%s' for image processing...", graph_filename.c_str());
        fileBuildBar.setLabelText("Processing and Storing Edge Information from Selected File...");
        fileBuildBar.setValue(50);
        QApplication::processEvents();

        // Call Function and Verify Output Indicates Read Operation did not return Errors (file reading or format errors)
        try {
            output = build_adjacency_list(file_name, graph_filename, file_vertex_count, std::move(*(this->main_hash)));
        } catch(std::exception& e) {
            std::cerr << e.what() << std::endl;
            QMessageBox reportException;
            reportException.setIcon(QMessageBox::Warning);
            reportException.setText(e.what());
            reportException.setInformativeText("Exception was thrown while parsing selected text file\nEnsure the file is properly formatted.");
            reportException.setWindowTitle("File Error Encountered");
            reportException.exec();
            QApplication::exit(1);
            return;
        }

        if (output < 0) {
            std::cerr << "An error was encountered while reading from graph text file";
            QMessageBox reportFileError;
            reportFileError.setIcon(QMessageBox::Critical);
            reportFileError.setText("Error(s) were encountered while reading the selected text file");
            reportFileError.setInformativeText("The selected file is most likely not properly formatted.\n"
                                               "Each Line should follow format:\n\n 'Vertex1_name, Vertex2_name, Distance'\n\n"
                                               "Please Modify the file and restart the application");
            reportFileError.setWindowTitle("File Error Encountered");
            reportFileError.exec();
            QApplication::exit(1);
            return;
        }

        // Update Progress Notification upon Success
        fileBuildBar.setValue(75);
        fileBuildBar.setLabelText("Finalizing Results for User Selection...");
        QApplication::processEvents();
        gprintf("Graph Successfully Built!");
#ifdef debug
        std::cerr << "Filled Hashmap is: " << *(this->main_hash) << '\n';
#endif \
        // Fill DropDowns with Verticies Found
        auto vertex_list = this->main_hash->get_keys();
        vertex_list.sort();
        for (auto& vertex : vertex_list) {
            QString qvertex = qvertex.fromStdString(vertex);
            ui->startVertexSelect->addItem(qvertex);
            ui->destVertexSelect->addItem(qvertex);
            qvertex = "";
        }

        // Indicate Successful Completion and Provide User Access to Solution Selection Section with Populated Data
        fileBuildBar.setValue(100);
        statusBar()->setStyleSheet("QStatusBar{background-color: ghostwhite; font: 10pt \"Gill Sans MT\"; color: limegreen;}");
        statusBar()->showMessage("Graph Contents Validated! If you wish to choose a different file, please restart the application.");
        ui->step3Label->setVisible(true);
        ui->solutionSelectTitle->setVisible(true);
        ui->mstButton->setVisible(true);
        ui->shortestPathButton->setVisible(true);
        ui->confirmFileButton->setVisible(false);
        ui->fileConfirmationLabel->setVisible(true);
        QMessageBox confInfo;
        confInfo.setWindowTitle("File Processing Complete");
        confInfo.setStyleSheet("QMessageBox {background-color: qlineargradient(x1: 0, y1: 0.5, x2: 0.5, y2: 1, stop: 0 ghostwhite, stop: 1 lightsteelblue); font: 700 10pt \"Sylfaen\";}"
                               " QMessageBox QLabel{color: indigo; font: 700 10pt \"Sylfaen\";}");
        QString confMessage = "File Validation and Processing Complete!\n\nPlease note that if you wish to have a different text file processed, you must restart the application to do so.";
        confInfo.setText(confMessage);
        confInfo.exec();
    }
}

// Event Handler triggered by Changing the Starting Vertex Selected from UI Dropdown box for the Shortest Path
void MainWindow::onActionSrcVertexChanged()
{
    // Compare Currently Selected Values for Destination and Source Verticies
    std::string source_vertex = ui->startVertexSelect->currentText().toStdString();
    std::string dest_vertex = ui->destVertexSelect->currentText().toStdString();
    // If Destination and Source Verticies are the Same, Notify user of Invalid Selection and Prevent User from Submitting with Selected Value Combination
    if (dest_vertex.compare(source_vertex) == 0) {
        statusBar()->setStyleSheet("QStatusBar{background-color: ghostwhite; font: 10pt \"Gill Sans MT\"; color: crimson;}");
        statusBar()->showMessage("WARNING: Destination is same as Starting Point. Please select another vertex before proceeding.");
        ui->submitButton->setVisible(false);
        ui->vertexNotificationLabel->setVisible(true);
    } else {
        // Otherwise, Indicate to User that Combination is Valid
        statusBar()->setStyleSheet("QStatusBar{background-color: ghostwhite; font: 10pt \"Gill Sans MT\"; color: limegreen;}");
        statusBar()->showMessage("Please Select a Starting and Ending point for path");
        ui->submitButton->setVisible(true);
        ui->vertexNotificationLabel->setVisible(false);
    }
}

// Event Handler triggered by Chaning the Destination Vertex Selected from UI Dropdown Box for the Shortest Path
void MainWindow::onActionDestVertexChanged()
{
    // Compare Currently Selected Values for Destination and Source Verticies
    std::string source_vertex = ui->startVertexSelect->currentText().toStdString();
    std::string dest_vertex = ui->destVertexSelect->currentText().toStdString();
    // If Destination and Source Verticies are the Same, Notify user of Invalid Selection and Prevent User from Submitting with Selected Value Combination
    if (dest_vertex.compare(source_vertex) == 0) {
        statusBar()->setStyleSheet("QStatusBar{background-color: ghostwhite; font: 10pt \"Gill Sans MT\"; color: crimson;}");
        statusBar()->showMessage("WARNING: Destination is same as Starting Point. Please select another vertex before proceeding.");
        ui->submitButton->setVisible(false);
        ui->vertexNotificationLabel->setVisible(true);
    } else {
        // Otherwise, Indicate to User that Combination is Valid
        statusBar()->setStyleSheet("QStatusBar{background-color: ghostwhite; font: 10pt \"Gill Sans MT\"; color: limegreen;}");
        statusBar()->showMessage("Please Select a Starting and Ending point for path");
        ui->submitButton->setVisible(true);
        ui->vertexNotificationLabel->setVisible(false);
    }
}

// Event Handler triggered by Clicking on Shortest Path Solution Radio Button
void MainWindow::onActionShortestPathSelected()
{
    if (ui->startVertexSelect->currentText().toStdString().compare(ui->destVertexSelect->currentText().toStdString()) == 0){
        statusBar()->setStyleSheet("QStatusBar{background-color: ghostwhite; font: 10pt \"Gill Sans MT\"; color: crimson;}");
        statusBar()->showMessage("WARNING: Destination is same as Starting Point. Please select another vertex before proceeding.");
        ui->submitButton->setVisible(false);
        ui->vertexNotificationLabel->setVisible(true);
    } else {
        QString SPMsg = "STATUS: Vertex Count of ";
        QString set_size = set_size.number(vertex_count);
        SPMsg.append(set_size);
        SPMsg.append(" detected with selected solution of Shortest Path");
        statusBar()->setStyleSheet("QStatusBar{background-color: ghostwhite; font: 10pt \"Gill Sans MT\"; color: limegreen;}");
        statusBar()->showMessage(SPMsg);
        ui->submitButton->setVisible(true);
        ui->vertexNotificationLabel->setVisible(false);
    }
    // Hide UI Elements for Displaying Generated Solution Images
    // Make DropDown Selection Elements for Destination/Source Verticies Visible along with Submision Button
    ui->displayImgButton->hide();
    ui->displayGraphButton->hide();
    ui->pathSelectTitle->setVisible(true);
    ui->startVertexSelect->setVisible(true);
    ui->destVertexSelect->setVisible(true);
    requestedSolution ="S";
}

// Event Handler triggered by Clicking on MST Solution Radio Button
void MainWindow::onActionMSTSelected()
{
    // Hide UI Elements for Collecting Shortest Path Information and Dislaying Generated Solution Images
    ui->displayImgButton->hide();
    ui->displayGraphButton->hide();
    ui->pathSelectTitle->hide();
    ui->startVertexSelect->hide();
    ui->destVertexSelect->hide();
    ui->submitButton->setVisible(true);
    ui->vertexNotificationLabel->setVisible(false);
    requestedSolution = "M";
    QString MSTMsg = "STATUS: Vertex Count of ";
    QString set_size = set_size.number(vertex_count);
    MSTMsg.append(set_size);
    MSTMsg.append(" detected with selection solution of MST");
    statusBar()->setStyleSheet("QStatusBar{background-color: ghostwhite; font: 10pt \"Gill Sans MT\"; color: limegreen;}");
    statusBar()->showMessage(MSTMsg);
}


// Event Handler triggered by Clicking on Button for Generating Images of Entire Graph and Requested Solution Type
void MainWindow::onActionSubmitClicked()
{
    gprintf("Generating Images...");
    ui->vertexNotificationLabel->setVisible(false);
    // Handle User Input for Preferred Calculation to Apply using Extracted Information
    if (requestedSolution == "M") {
        std::cerr << "Beginning Minimum Spanning Tree Calculations..." << '\n';
        // Call Function to Collect and Display all Edges that User-Requested MST is Comprised of
        std::string start_vertex = this->main_hash->get_keys().front();
        int valid_tree = 0;
        try {
            valid_tree = find_MST(start_vertex, graph_filename, MST_filename, std::move(*(this->main_hash)));
        } catch (std::exception& e) {
            std::cerr << e.what() << '\n';
            QMessageBox reportException;
            reportException.setIcon(QMessageBox::Warning);
            reportException.setText(e.what());
            reportException.setInformativeText("Exception was thrown building MST file\n.The selected text file may contain incomplete/corrupted data.\n");
            reportException.setWindowTitle("MST Processing Error Encountered");
            reportException.exec();
            QApplication::exit(1);
            return;
        }

        if (valid_tree < 0) {
            std::cerr << "An Error was Encountered while Building MST\n";

            QMessageBox reportMSTBuildError;
            reportMSTBuildError.setIcon(QMessageBox::Critical);
            reportMSTBuildError.setText("Error(s) were encountered while attempting to calculate the MST solution");
            reportMSTBuildError.setInformativeText("The selected text file depicts a graph that has one or more disconnected verticies.\n"
                                                   "You may try again with corrected file or another text file depicting a connected graph.");
            reportMSTBuildError.setWindowTitle("MST Build Error Encountered");
            reportMSTBuildError.exec();
            QApplication::exit(1);
            return;
        }
    } else if (requestedSolution == "S") {
        // If Shortest Path is Selected, Verify Source and Destination Verticies are Valid Before Beginning Calculations
        std::string source_vertex = ui->startVertexSelect->currentText().toStdString();
        std::string dest_vertex = ui->destVertexSelect->currentText().toStdString();
        gprintf("Beginning Shortest Path Calculations Starting at '%s' and Ending at '%s'", source_vertex.c_str(), dest_vertex.c_str());
        if (source_vertex.empty() || dest_vertex.empty()){
            // If User failed to Select a Destination or Source Vertex, Prevent Submission and Redirect User back to Vetex Selection
            ui->submitButton->setVisible(false);
            statusBar()->setStyleSheet("QStatusBar{background-color: ghostwhite; font: 10pt \"Gill Sans MT\"; color: crimson;}");
            statusBar()->showMessage("WARNING: Please ensure both starting vertex and destination vertex have been selected!");
            ui->vertexNotificationLabel->setVisible(true);
            return;
        }

        if (source_vertex.compare(dest_vertex) == 0){
            // If User Selected Same Vertex as both Destination and Source of Shortest Path, Prevent Submission and Redirect User back to Vetex Selection
            ui->submitButton->setVisible(false);
            statusBar()->setStyleSheet("QStatusBar{background-color: ghostwhite; font: 10pt \"Gill Sans MT\"; color: crimson;}");
            statusBar()->showMessage("WARNING: Please ensure both starting vertex and destination vertex have been selected!");
            ui->vertexNotificationLabel->setVisible(true);
            return;
        }

        // Call Function to Collect and Display all Verticies in User-Requested Shortest Path from Selected Source/Destination Verticies
        int valid_path = 0;
        try {
            valid_path = find_shortest_path(source_vertex, dest_vertex, graph_filename, path_filename, std::move(*(this->main_hash)));
        } catch (std::exception& e) {
            std::cerr << e.what() << '\n';
            QMessageBox reportException;
            reportException.setIcon(QMessageBox::Warning);
            reportException.setText(e.what());
            reportException.setInformativeText("Exception was thrown building the shortest path from selected text file.\n"
                                               "The selected text file may contain incomplete/corrupted data.");
            reportException.setWindowTitle("Shortest Path Processing Error Encountered");
            reportException.exec();
            QApplication::exit(1);
            return;
        }

        if (valid_path < 0) {
            std::cerr << "An Error was Encountered while Building Shortest Path";
            QMessageBox reportSPBuildError;
            reportSPBuildError.setIcon(QMessageBox::Critical);
            reportSPBuildError.setText("Error(s) were encountered while attempting to calculate the shortest path solution");
            reportSPBuildError.setInformativeText("The selected text file depicts a graph that has one or more disconnected verticies.\n"
                                                  "You may try again with corrected file or another text file depicting a connected graph.");
            reportSPBuildError.setWindowTitle("Shortest Path Build Error Encountered");
            reportSPBuildError.exec();
            QApplication::exit(1);
            return;
        }
    } else {
        std::cerr << "Unexpected value of requested Solution type received\n";
        QMessageBox reportUnexpectedError;
        reportUnexpectedError.setIcon(QMessageBox::Critical);
        reportUnexpectedError.setText("Error(s) were encountered while attempting to determine selected solution request type");
        reportUnexpectedError.setInformativeText("An unexpected value was received for the selected solution request type.\n"
                                                 "Please restart the application and try again.");
        reportUnexpectedError.setWindowTitle("Unexpected Solution Request Read Error");
        reportUnexpectedError.exec();
        QApplication::exit(1);
        return;
    }
    /*
     * Due to Time-Delay Incurred by:
     * - Executing Pipelined Shell Commands or Executing Shell Scripts to Call Multiple Commands
     * - Time Required for Graphviz Processing Dot-Formatted Files and Painting Image to Specified Location
     *
     *  Generate and Display a Window Notifying the User of Program Progress as Soon as Program Begins Processing
    */
    QProgressDialog imgProgressBar("Selecting local OS-compatible Script for Solution Imaging...", nullptr, 0, 100);
    imgProgressBar.setStyleSheet("QProgressDialog{font: 700 10pt \"Sylfaen\";} QLabel{font: 700 10pt \"Sylfaen\"; color: rgb(0, 85, 0);}");
    imgProgressBar.setMinimumDuration(0);
    imgProgressBar.resize(this->width(), imgProgressBar.height() + 100);
    imgProgressBar.setWindowTitle("Solution Image Generation Progress");
    QApplication::processEvents();

    // Immediately Update Event State of Progress Bar before Longest Expected Span of Processing Time
    imgProgressBar.setValue(45);
    imgProgressBar.setLabelText("Executing local OS-compatible Script for Solution Imaging.\nThis may take up to several minutes to complete...");

    QApplication::processEvents();

    // Initialize Path Variables that will be Employed Based on Detected Platform's OS
    std::string script_path = "";
    std::string request_type = "";
    std::string destination_file = "";
    std::string command_val = "";
    std::string c_graphfile = graphDestination.toStdString();
    // Set Universal Printed Output and Graph Image Locations based on type of Information Requested By User
    if (requestedSolution == "S") {
        request_type = "SHORTEST PATH";
        destination_file = SP_image;
    } else {
        request_type = "MINIMUM SPANNING TREE";
        destination_file = MST_image;
    }

// Select Linux-Compatible Bash Script and set CLI command to environment path to linux bash if Linux is detected
#ifdef __linux__
    // Preset Script Path and Graph Image Locations based on User Requested Information for Linux Users
    command_val = "/bin/bash"
        if (requestedSolution == "S") {
        script_path = Linux_SP_script;

    } else {
        script_path = Linux_MST_script;
    }
    // Ensure script written in Windows have carriage return characters replaced for read compatibility with Linux/Unix systems
    windows_check = check_for_CLRF(script_path);
    if (windows_check < 0) {
        std::cerr << "ERROR: Read error(s) were encountered while checking file '" << script_path << "'\n";
        return -1;
    }
#endif
    // If Preprocessor Conditional Detects MacOS, Directly Execute Multiple Bash Commands to Graphviz's Dot Executable through A Pipeline
    // Program Requires use of HomeBrew Executable to set Bash environment path and Graphviz bin path
#ifdef __APPLE__
    command_val = "";
    std::string dot_path = "./Graphviz/bin/dot.exe";
    // Preset Script Path and Graph Image Locations based on User Requested Information for MacOS Users
    if (requestedSolution == "S") {
        // Set Output Image File Path Designated for Shortest Path and Specify Output Format to Graphviz's Dot using Appropriate .gv files for Input
        script_path = "chmod +x ";
        script_path..append(dot_path).append("; ").append(dot_path).append(" -Tpng:cairo ").append(graph_filename).append(" -o ").append(graphDestination.toStdString()).append(" -v; ");
        script_path.append(dot_path).append(" -Tpng:cairo ").append(path_filename).append(" -o ").append(destination_file).append(" -v");
        gprintf("Path for Full Graph Image is '%s'", c_graphfile.c_str());
        gprintf("Path for Shortest Path Solution Image is '%s'", path_filename.c_str());
    } else {
        // Set Output Image File Path Designated for MST and Specify Output Format to Graphviz's Dot using Appropriate .gv files for Input
        script_path = "chmod +x ";
        script_path.append(dot_path).append("; ").append(dot_path).append(" -Tpng:cairo ").append(graph_filename).append(" -o ").append(graphDestination.toStdString()).append(" -v; ");
        script_path.append(dot_path).append(" -Tpng:cairo ").append(MST_filename).append(" -o ").append(destination_file).append(" -v");
        gprintf("Path for Full Graph Image is '%s'", c_graphfile.c_str());
        gprintf("Path for MST Solution Image is '%s'", MST_filename.c_str());
    }
#endif

#ifdef _WIN32
    // If Preprocessor Conditional Detects Windows OS, Directly Execute Multiple Powershell Commands to Graphviz's Dot Executable through A Pipeline
    command_val = "powershell -Command \"";
    if (requestedSolution == "S") {
        // Set Output Image File Path Designated for Shortest Path and Specify Output Format to Graphviz's Dot using Appropriate .gv files for Input
        script_path = graphviz_path;
        script_path.append("dot -Tpng:cairo ").append(graph_filename).append(" -o ").append(graphDestination.toStdString()).append(" -v; ");
        script_path.append(graphviz_path).append("dot -Tpng:cairo ").append(path_filename).append(" -o ").append(destination_file).append(" -v\"");
        gprintf("Path for Full Graph Image is '%s'", c_graphfile.c_str());
        gprintf("Path for Shortest Path Solution Image is '%s'", path_filename.c_str());
    } else {
        // Set Output Image File Path Designated for MST and Specify Output Format to Graphviz's Dot using Appropriate .gv files for Input
        script_path = graphviz_path;
        script_path.append("dot -Tpng:cairo ").append(graph_filename).append(" -o ").append(graphDestination.toStdString()).append(" -v; ");
        script_path.append(graphviz_path).append("dot -Tpng:cairo ").append(MST_filename).append(" -o ").append(destination_file).append(" -v\"");
        gprintf("Path for Full Graph Image is '%s'", c_graphfile.c_str());
        gprintf("Path for MST Solution Image is '%s'", MST_filename.c_str());
    }

#endif
    // Return Without Executing Script Program if Preprocessor Conditionals indicate Unexpected/Undefined OS Detection
    if (script_path.size() == 0) {
        QMessageBox reportUnexpectedOSError;
        reportUnexpectedOSError.setIcon(QMessageBox::Critical);
        reportUnexpectedOSError.setText("Error(s) were encountered while attempting to detect local operating system");
        reportUnexpectedOSError.setInformativeText("The operating system in which this application has been executed does not match"
                                                   " any of the operating systems that are compatible with this application.\n");
        reportUnexpectedOSError.setWindowTitle("Incompatible Operating System Detected");
        reportUnexpectedOSError.exec();
        QApplication::exit(1);
        return;
    }
    gprintf("Attempting to Execute Script or Command of '%s'...", script_path.c_str());

// Execute Bash Shell Scripts using Linux-Compliant <sys/wait.h> Library Functions for Image Generation if Linux OS is Detected
#ifdef __linux__
    // Run Appropriate Bash Script for Generating Graph Images
    pid_t pid = fork();
    int child_status;
    switch(pid) {
    case -1:
        perror("fork");
        break;
    case 0:
        gprintf("Executing '%s' to overlay the '%s' using the processed graphical information...\n", script_path, request_type);
        gprintf("\n=============================== IMAGE GENERATION RESULTS ====================================\n");
        execl(command_val.c_str(), bash_path, script_path.c_str(), nullptr);
        perror("execl");
        break;
    default:
        pid = waitpid(pid, &child_status, 0);
    }
    gprintf("Success!\nThe Image of the '%s' was placed within '%s'\n", request_type, destination_file);
    gprintf("The Image of the Entire Graph was placed within:   '%s'", graphDestination.toStdString());
#else
    // Use popen(MacOS) or _popen (Windows), to Execute Commands/Scripts within a Pipeline and Read/Monitor its Output for Errors
    FILE *pipe_stream;
    command_val.append(script_path);
    gprintf("Generating the '%s' using the processed graphical information...\n", request_type.c_str());
    gprintf("\n=============================== IMAGE GENERATION RESULTS ====================================\n");
#ifdef _WIN32

    // Establish Stream with Intent to both Execute the Powershell Script and Read from Buffer containing the Command Line Output for Error Detection
    // Use _popen for compatibility over broader range of windows systems
    pipe_stream = _popen(command_val.c_str(), "r");
#else
    // If MacOS use standard popen instead
    pipe_stream = popen(command_val.c_str(), "r");
#endif
    // If Stream is Successfully Established with Pipeline, Attempt to Execute Powershell Commands to Generate Requested Solution and Full Graph Images
    if (pipe_stream != NULL) {
#ifdef _WIN32
        // Use _pclose for windows
        int script_error = _pclose(pipe_stream);
#else \
    // Uee standard pclose for MacOS
        int script_error = pclose(pipe_stream);
#endif \
    // If One or More Errors are Encountered in Execution of Powershell/Bash Commands, Notify User
        if (script_error == -1) {
            std::cerr << "ERROR: '" << script_path << "' encountered error(s) while executing to generate image of '"<< request_type << "' \n";
            QMessageBox reportImgGenError;
            reportImgGenError.setIcon(QMessageBox::Warning);
            reportImgGenError.setText("Error(s) were encountered while attempting to generate the solution images");
            reportImgGenError.setInformativeText("The program failed to generate the images from the processed data using Graphviz's dot executable."
                                                 "Please ensure the 'Graphviz' folder exists within the 'Common' folder.\n"
                                                 "Additionally, the commands to generate images may require elevated permissions to execute.\n");
            reportImgGenError.setWindowTitle("Image Generation Error Encountered");
            reportImgGenError.exec();
            QApplication::exit(1);
            return;
        } else {
            // Else, Proceed with Indicating Images are Ready for Viewing, report to debugging for status checking
            gprintf("Success!\nThe Image of the '%s' was placed within '%s'\n", request_type.c_str(), destination_file.c_str());
            gprintf("The Image of the Entire Graph was placed within:   '%s'", c_graphfile.c_str());
        }

    } else {
        // Exit if Internal Fork or Pipe Operations Fail
        perror("pipe/fork");
        std::cerr << "ERROR: Failed to establish pipeline stream for executing shell commands using popen with '" << script_path << "'\n";
        QMessageBox reportImgGenError;
        reportImgGenError.setIcon(QMessageBox::Warning);
        reportImgGenError.setText("Error(s) were encountered while attempting to generate the solution images");
        reportImgGenError.setInformativeText("The program failed to generate the images from the processed data using Graphviz's dot executable."
                                             "Please ensure the 'Graphviz' folder exists within the 'Common' folder.\n"
                                             "Additionally, the commands to generate images may require elevated permissions to execute.\n");
        reportImgGenError.setWindowTitle("Image Generation Error Encountered");
        reportImgGenError.exec();
        QApplication::exit(1);
        return;
    }
    // Establish Stream with Intent to both Execute the Powershell Script and Read from Buffer containing the Command Line Output for Error Detection
    pipe_stream = _popen(command_val.c_str(), "r");
    // If Stream is Successfully Established with Pipeline, Attempt to Execute Powershell Commands to Generate Requested Solution and Full Graph Images
    if (pipe_stream != NULL) {
        int script_error = _pclose(pipe_stream);
        // If One or More Errors are Encountered in Execution of Powershell/Bash Commands, Notify User
        if (script_error == -1) {
            std::cerr << "ERROR: '" << script_path << "' encountered error(s) while executing to generate image of '" << request_type << "' \n";
            QMessageBox reportImgGenError;
            reportImgGenError.setIcon(QMessageBox::Warning);
            reportImgGenError.setText("Error(s) were encountered while attempting to generate the solution images");
            reportImgGenError.setInformativeText("The program failed to generate the images from the processed data using Graphviz's dot executable."
                                                 "Please ensure the 'Graphviz' folder exists within the 'Common' folder.\n"
                                                 "Additionally, the commands to generate images may require elevated permissions to execute.\n");
            reportImgGenError.setWindowTitle("Image Generation Error Encountered");
            reportImgGenError.exec();
            QApplication::exit(1);
            return;
        }
        else {
            // Else, Proceed with Indicating Images are Ready for Viewing
            gprintf("Success!\nThe Image of the '%s' was placed within '%s'\n", request_type.c_str(), destination_file.c_str());
            gprintf("The Image of the Entire Graph was placed within:   '%s'", c_graphfile.c_str());
        }
        _pclose(pipe_stream);
    }
    else {
        // Exit if Internal Fork or Pipe Operations Fail
        perror("pipe/fork");
        std::cerr << "ERROR: Failed to establish pipeline stream for executing shell commands using popen with '" << script_path << "'\n";
        QMessageBox reportImgGenError;
        reportImgGenError.setIcon(QMessageBox::Warning);
        reportImgGenError.setText("Error(s) were encountered while attempting to generate the solution images");
        reportImgGenError.setInformativeText("The program failed to generate the images from the processed data using Graphviz's dot executable."
                                             "Please ensure the 'Graphviz' folder exists within the 'Common' folder.\n"
                                             "Additionally, the commands to generate images may require elevated permissions to execute.\n");
        reportImgGenError.setWindowTitle("Image Generation Error Encountered");
        reportImgGenError.exec();
        QApplication::exit(1);
        return;
    }
#endif
    // If Script/Command Executions are Successful, Present User with UI Elements that Allow for Viewing Generated Images
    imgProgressBar.setValue(100);
    statusBar()->setStyleSheet("QStatusBar{background-color: ghostwhite; font: 10pt \"Gill Sans MT\"; color: limegreen;}");
    statusBar()->showMessage("Image Generation Complete!");
    solutionDestination = solutionDestination.fromStdString(destination_file);
    // Notify user of ways to view the newly generated images and/or locate them if they wish to save/delete them.
    QMessageBox imgInfo;
    imgInfo.setWindowTitle("Viewing your Generated Image Results");
    imgInfo.setStyleSheet("QMessageBox {background-color: qlineargradient(x1: 0, y1: 0.5, x2: 0.5, y2: 1, stop: 0 ghostwhite, stop: 1 lightsteelblue); font: 700 10pt \"Sylfaen\";}"
                          " QMessageBox QLabel{color: indigo; font: 700 10pt \"Sylfaen\";}");
    QString imgMessage = "Image Generation Complete! You may now view the generated images by:\n\n1. Clicking the buttons that appear at the bottom of the window to view the images at reduced quality.\n";
    imgMessage.append("\n2. Locating them within the \"graph_images\" folder and opening each image using your operating system's native image-viewing application to view the image(s) at a higher quality.\n");
    if (request_type.compare("SHORTEST PATH") == 0) {
        imgMessage.append("\nThe generated shortest path image will be named \"shortest_path_overlay.png\" and full graph will be named \"full_graph.png\"\n");
    } else {
        imgMessage.append("\nThe generated MST image will be named \"MST_overlay.png\" and full graph will be named \"full_graph.png\"\n");
    }
    imgInfo.setText(imgMessage);
    imgInfo.exec();
    // Make image viewing buttons available after providing viewing instructions
    ui->displayImgButton->setVisible(true);
    ui->submitButton->setVisible(true);
    ui->displayGraphButton->setVisible(true);
}

// Event Handler triggered by Clicking on Button for Viewing Generated Solution Image
void MainWindow::onActionDisplayImgClicked(){
    // Read Generated Image of Solution from Location Reserved according to Solution Type with ImageReader
    QImageReader readSolution;
    readSolution.setAllocationLimit(0);
    readSolution.setFileName(solutionDestination);

    // Create New Dialogbox to be Used for Displaying Image to User in Separate Modeless Window
    QDialog solutionImg;
    QLabel solutionLabel(&solutionImg);
    // Create PixMap to Load Image from Designated File Location
    QPixmap solutionMap(solutionDestination);

    if (requestedSolution == "M"){
        QString windowTitle = "Minimum Spanning Tree Image (Higher Quality Image can be viewed at \"";
        windowTitle.append(solutionDestination).append("\")");
        solutionImg.setWindowTitle(windowTitle);
    } else {
        QString windowTitle = "Shortest Path Image (Higher Quality Image can be viewed at \"";
        windowTitle.append(solutionDestination).append("\")");
        solutionImg.setWindowTitle(windowTitle);
    }

    // Fill Dialog Window with Pixmap that is Scaled to fill its Child Label with Aspect Ratio Intact
    if(!solutionMap.isNull()) {
        solutionLabel.resize(this->width() + 100, this->height() + 100);
        solutionLabel.setPixmap(solutionMap.scaled(solutionLabel.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        solutionLabel.setScaledContents(true);
        // Execute Dialog Window with properly Adjusted Image of Solution to Appear
        solutionImg.exec();
    }
}

// Event Handler triggered by Clicking on Button for Viewing Generated Full Graph Image
void MainWindow::onActionDisplayGraphClicked()
{
    // Generate QImageReader to Collect Image Details from File Holding Generated Full Graph Image
    QImageReader readFullGraph;
    readFullGraph.setAllocationLimit(0);
    readFullGraph.setFileName(graphDestination);

    // Store Image in PixMap and scale its Contents to Size of Label used to Display Image, Maintaining Original Image's Aspect Ratio
    QDialog fullGraphImg;
    QLabel fullGraphLabel(&fullGraphImg);
    QPixmap fullGraphMap(graphDestination);
    QString windowTitle = "Generated Full Graph Image (Higher Quality Image can be viewed at \"";
    windowTitle.append(graphDestination).append("\")");
    fullGraphImg.setWindowTitle(windowTitle);
    // Verify PixMap was Successfully Built using Image File Before Attempting to Display Scaled Version of Image to User
    if (!fullGraphMap.isNull()){
        // Scale Image to Fit Size of Label child of Parent Dialog Box and Display Image to User
        fullGraphLabel.resize(this->width() + 100, this->height() + 100);
        fullGraphLabel.setPixmap(fullGraphMap.scaled(fullGraphLabel.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        fullGraphLabel.setScaledContents(true);
        fullGraphImg.exec();
    } else {
        // Notify User that Generated Full Graph Image does not Exist or Path used is Invalid
        QString imgErrorMsg = "Program Failed to Extract Generated Full Graph Image From \"";
        imgErrorMsg.append(graphDestination).append("\". Please Ensure Path to \"").append(graphDestination).append("\" is Valid");
        statusBar()->setStyleSheet("QStatusBar{background-color: ghostwhite; font: 10pt \"Gill Sans MT\"; color: crimson;}");
        this->statusBar()->showMessage(imgErrorMsg);
        std::cerr << "Failed to Extract Generated Image of Full Graph!";
    }
}

// Class Destructor (destroy all smart pointers, including Ui child)
MainWindow::~MainWindow(){}
