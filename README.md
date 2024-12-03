# Project Description

This project was developed with the intent to build upon [a previously-made console application](https://github.com/parsokev/graph_repo) that generates
graphical images from user-provided text files. This project provides a graphical user interface (GUI) with the same functionality as the
previous application to increase program accessiblity.

This was achieved through the utilization of:
   - [Qt Creator](https://doc.qt.io/qt-6/qt-intro.html) to develop an interactive cross-platform desktop application window that accepts user-requested
      graphical solutions from a graph whose edges are described in each separate line within a text file selected by the user.

   - [Graphviz](https://www.graphviz.org/) to visualize the submitted graphical information, along with the requested solution, in PNG-formatted images.

Upon completing the required steps for project setup outlined in the [Project Setup section](#project-setup),
the application will generate a desktop application window that will allow the user to generate and view
graphical visualizations after completing the following steps:

 1. Select a local text file providing graphical information to be processed/visualized in terms of individual edges.
    - Each separate line describes a unique edge found in the graph in the format of 
    ```
        vertex1, vertex2, distance-between-verticies
    ```
> [!NOTE]
> Example text files can be found in the [sample_graphs](./sample_graphs) directory.

> ![Image of File Selection UI](./ui_images/file-select-step.png)

2. Either manually enter an estimated number of verticies for the graph or request for the program to automatically estimate the number.

    ![Image of Vertex Selection UI](./ui_images/vertex-select-step.png)

3. Select whether the program should visualize the Minimum Spanning Tree or shortest path between two specified verticies, using the text file.

    ![Image of Solution Request UI](./ui_images/solution-select-step.png)

4. Upon confirmation of these, the project will generate the visualizations of both the graph depicted in the text file and that of the requested
   graphical solution overlaying the original graph. Upon determining the requested solution, the program will display a detailed overview of the generated
   solution information in a separate prompt window,and then begin image generation upon user-acknowledgment of the prompt information(clicks 'OK' button).

    ![Image of Image Selection UI](./ui_images/image-select-step.png)
    
    The generated images will be immediately viewable through clicking the buttons within the application window but can also be viewed in higher
    quality within their default local save location within the [graph_images](./graph_images) directory. They will be saved upon generation but
    will be overwritten upon processing a new text file or changing the requested solution type.

# Project Setup

> [!IMPORTANT]
> In order to reduce file size and maintain local-machine compatibility, the Graphviz directory has been omitted from the repository.
> Please download the most stable ZIP-archived version that is compatible with your local machine from the [download page for Graphviz](https://www.graphviz.org/download/),
> and place the extracted contents(excluding the main folder itself) directly into the cloned repository's [Graphviz directory](./Graphviz).
> This will eliminate the need to complete local setup/installation of Graphviz on the local machine while still allowing for its use by the application.

If wishing to clone this repository to your local machine, this application must be built ***using [QT Creator](https://doc.qt.io/qtcreator/index.html)***
***or [Visual Studio with QT extensions installed and enabled](https://marketplace.visualstudio.com/items?itemName=TheQtCompany.QtVisualStudioTools2022)***.
This allows for the generation of an application executable that is compatible with the local machine's OS.

## Setting up CMake Build Configurations for Local Execution and Debugging
Once the repository has been cloned locally using either platforms, if you wish to build the application to run within QT Creator/Visual Studio,
set the application's build directory path to mirror the path outlined below and ensure the CMake build kit is configured to be compatible with local machine's OS:
```
    <repo-root-directory>\build\<your-configuration-here>
```

CMakeLists and resource paths are configured to be set according to the CMake Build Type so ***ensure the CMake build path follows the path above and
the CMake Build Type is either 'Debug' or 'RelWithDebugInfo'(Release with Debug Information) and NOT 'Release' if wishing to build for local usage purposes***

> [!NOTE]
> The [build directory](./build) within the repo was intentionally left empty to provide expected location of build directory within the path represented above.
> The repository tree should follow the below image (some directories are not shown in image)

> ![Image of Hierarchy](./ui_images/rough-directory-tree.png)

Implementing the build path in QT Creator can be accomplished by selecting the `Projects` tab from the left-hand menu bar and adjusting the build directory
to match the path syntax listed above.
Selecting a kit that is compatible with the local machine's OS can be configured by clicking the `Manage Kits` button within the `Projects` page and choosing
for the selection of available kits presented.
This should be sufficient to build the project using CMake. This process using Visual Studio is accomplished in a similar fashion.
Further information on this process can be found [here](https://doc.qt.io/qtcreator/creator-how-to-activate-kits.html).

Upon completion of build process, the application will display the application window for accepting requests upon being executed. The most recently generated images
will be stored within the [graph_images](./graph_images) directory (they will be overwritten upon next execution if not copied and stored elsewhere locally)

## Setting up CMake Build Directory for Deploying as Stand-Alone Application

If wishing to deploy this application, Qt provides ability to deploy an application that can be executed locally without requiring Visual Studio or Qt Creator
to be installed. If wishing to deploy the application, set the application's build directory path to mirror the path outlined below and ensure the CMake build kit is
configured to be compatible with local machine's OS:
```
<repo-root-directory>\<deployed-app-directory-here>
```

> [!NOTE]
> The [App directory](./App) within the repo was intentionally left empty to provide expected location of deployment directory within the path represented above.

CMakeLists and resource paths are configured to be set according to the CMake Build Type so ***ensure the CMake build path follows the path above and
the CMake Build Type is 'Release' if wishing to deploy the application executable along with all required runtime and Qt dependencies***

Upon completion of build process, the directory in which the app was deployed can be executed locally without the programs required to build/run the application 
by simply double clicking the .exe file within the directory


# Sample Generated Images

A gallery of pre-generated graph images can be found in the [graph_images](./graph_images) directory, which were generated
to show visualizations of lower density graphs using [my_graph5.txt](./sample_graphs/my_graph5.txt) and of higher density graphs
using [my_graph6.txt](./sample_graphs/my_graph6.txt) both of which can be found in the [sample_graphs directory](./sample_graphs)

> [!CAUTION]
> When building visualizations for graphs with higher edge densities like `my_graph6.txt`, it may take several minutes for the
> visualization software to complete the image generation process. In such cases, the detailed progress of the visualization process can
> be monitored through standard error ouput in the console

Example Image Generated from `my_graph5.txt`

![Image of Shortest Path](./graph_images/sample_sp_graph5.png)

# Additional Resources

## Build Graphs using GoogleMaps API and the provided Python script

The `main.py` file found in the [py_builder directory](./py_builder) was utilized for testing and generating graph text files
while using the GoogleMaps API to provided simplified distance data between geographic locations. The `main.py` file can be used to:

1. Generate the maximum number of unique edges that can be generated from a list of city names using the `create_max_edges` function
2. Parse an existing text file with a list of edges (where each line follows format of `city1, city2, `) and have the rough distance
   between the two existing city locations (requested from [GoogleMaps' DistanceMatrixAPI](https://developers.google.com/maps/documentation/distance-matrix)
   ) written at the end of the edge for all edges with valid locations. 

If wishing to use this, please visit [the DistanceMatrixAPI homepage](https://developers.google.com/maps/documentation/distance-matrix) to
create an account and generate the API key needed to make requests with the program. For the requests made by the program, the cost for such requests will
be virtually free and free trials with GCP credits are available for new accounts.

# Citations

Third Party Software/Libraries Utilized in Building this Project Include:

- [Graphviz](https://www.graphviz.org/license/)

- [Qt](https://www.qt.io/licensing/open-source-lgpl-obligations#lgpl)

In accordance with the wishes of Qt and Graphviz, the LGPLv3 license has been included with this repository and the links to the
license agreements for both Graphviz and Qt are provided above.
