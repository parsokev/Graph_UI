# Project Description

This project was developed with the intent to build upon [a previously-made console application](https://github.com/parsokev/graph_repo) that generates
graphical images from user-provided text files. This project provides a graphical user interface (GUI) with the same functionality as the
previous application to increase program accessiblity.

This was achieved through the utilization of:
   - [Qt Creator](https://doc.qt.io/qt-6/qt-intro.html) to develop an interactive cross-platform desktop application window that accepts user-requested
      graphical solutions from a graph whose edges are described in each separate line within a text file selected by the user.

   - [Graphviz](https://www.graphviz.org/) to visualize the submitted graphical information, along with the requested solution, in PNG-formatted images.

<iframe id="kaltura_player" src='https://cdnapisec.kaltura.com/p/391241/embedPlaykitJs/uiconf_id/44855082?iframeembed=true&amp;entry_id=1_ua3kcbjd&amp;config%5Bprovider%5D=%7B%22widgetId%22%3A%221_l733oqs4%22%7D&amp;config%5Bplayback%5D=%7B%22startTime%22%3A0%7D'  style="width: 640px;height: 420px;border: 0;" allowfullscreen webkitallowfullscreen mozAllowFullScreen allow="autoplay *; fullscreen *; encrypted-media *" sandbox="allow-downloads allow-forms allow-same-origin allow-scripts allow-top-navigation allow-pointer-lock allow-popups allow-modals allow-orientation-lock allow-popups-to-escape-sandbox allow-presentation allow-top-navigation-by-user-activation" title="Graph Visualization UI Demo"></iframe>

[Demonstration Video](https://github.com/user-attachments/assets/ae2bc191-844e-494d-ba03-a11df1394161)



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

If wishing to clone this repository to your local machine, this application must be built ***using [QT Creator](https://doc.qt.io/qtcreator/index.html)
or [Visual Studio](https://visualstudio.microsoft.com/) with [VS QT Tools](https://doc.qt.io/qtvstools/index.html) installed and enabled***.
This allows for the generation of an application executable that is compatible with the local machine's OS.

Regardless of which IDE is utilized to build the program, the program was developed with the intention of using two separate build paths
that are dependent on the user's intended use for the program.

## Building the Project for Local Development and Execution

If intending to build the program for local debugging/testing/modification purposes, the program must be built
using the CMake build types of either **'Debug' or 'RelWithDebInfo' (Release With Debug Info)**.
   
For use of the program under these conditions, the **build path must adhere to the following relative path from the root directory**:
        
```
<repo-root-directory>\build\<your-configuration-name-here>
```

The program's CMake settings and its resource paths are adjusted according to the CMake Build Type so ***ensure the CMake build path follows the above path***
***and the CMake Build Type is either 'Debug' or 'RelWithDebugInfo'(Release with Debug Information)*** if wishing to build for local development.

> [!NOTE]
> The [build directory](./build) within the repository was intentionally left empty to provide the expected location of the build directory
> within the path represented above. The repository tree should follow that of the below image (some directories are not shown in image).

> ![Image of Hierarchy](./ui_images/rough-directory-tree.png)


## Building the Project for Application Deployment

The program provides the option to be deployed as a stand-alone application executable (can be run on devices with same OS and architecture without
requiring the installation of the IDE/toolchain used to build it).

If intending to build the program for deployment, the program must be built using the CMake build type of **'Release' exclusively**.
   
For use of the program under these conditions, the build path **must adhere to the following relative path from the root directory**:
    
```
<repo-root-directory>\<deployed-app-directory-here>
```

> [!NOTE]
> The [App directory](./App) within the repo was intentionally left empty to provide the expected location of deployment directory within the path
> represented above.

The program's CMake settings and its resource paths are adjusted according to the CMake Build Type so ***ensure the CMake build path for the 'Release'***
***Configuration follows the path above if wishing to deploy the application executable along with all required runtime and Qt dependencies***.

It should also be noted that the .png files stored in the 'graph_images' directory and .gv files stored in the 'dot_graphs' directory will be modified in each
successive execution of the application. This may be flagged by a device's anti-virus software if transferred to a different device when application is executed.
**To prevent this from occurring, delete all previously generated files from these two directories before transferring to a different device**.

Upon completion of the appropriate IDE setup and build process detailed in the sections below, the directory in which the app was deployed can be
executed locally without the programs required to build/run the application by simply double clicking the .exe file within the directory.


## Building the Project Using QT Creator

Setting up the program using Qt Creator after cloning the repository can be completed by either:

1. Updating the CMake Preset Configurations imported from the `CMakeUserPresets.json` file to use the desired toolchain/kit for building
the program without having to manually update the build paths for the different configurations

2. Generating the CMake Preset Configurations using Qt Creator, which will automatically set the appropriate toolchain/kit for building program
and then modifying the default build paths to their expected values for each configuration path after creating them.

### Option 1: Using the Imported CMake Preset Configurations

After cloning the repository, Qt Creator will gather the configuration presets listed in the `CMakeUserPresets.json` file and offer these upon intial setup window.
These will be listed as:
1. `Qt-Debug (CMake) -temporary` configuration which will set the expected build path for localized testing/execution of the program.
2. `Qt-Release (CMake) -temporary` configuration which will set the expected build path for deploying the application as a stand-alone executable

In order to ensure toolchain/kit flexibility, the required toolchain/kit information was omitted and must be manually applied to each preset separately.
To finish configuration setup:
1. In first page displayed after cloning the repository, ensure the presets with names matching those listed above are selected/checked for creation.
2. Hover the cursor over the far right-hand side of the box of each selected configuration to reveal the `Manage` button under the `Details` tab.
You may need to click the `Details` dropdown arrow before the `Manage` button may appear. Upon clicking the `Manage` button, a window should appear
with a list of various build options that can be selected for each configuration.
3. Select the required build options specific to the desired toolchain/kit to build the program (those available can be found in the local Qt directory)
    - Select the preferred `CMake Generator` option from the dropdown list (Ex: 'Ninja')
    - Select the preferred `Debugger` option from the dropdown list (Ex: GNU gdb)
    - Select the preferred `Compiler` option for both C and C++ compilers from the dropdown lists (Ex: MingGW for C,C++)
    - Select the preferred `Qt Version` option from the dropdown list (Ex: Qt Version 6.8.0 MinGW)
4. Click `Apply` to associate these settings to the imported configuration
5. After completing this for both `Qt-Debug` and `Qt-Release`, click the `Configure Project` button to complete the build setup.
6. Ensure you have placed the locally compatible version of Graphviz within the empty `Graphviz` directory as specified in the [intial setup section](#project-setup).

If uncertain of any of these options, the preset values for kits offered by Qt automatically will have the options offered by Qt itself.
    
After completing the above steps, either configuration can be built with the build paths set to the expected paths and executed immediately.

### Option 2: Modifying the Qt-Generated Preset Configurations

Qt automatically provides kits that will have all the CMake settings optimized according to the various toolchains/kits Qt provides for building locally.
These are automatically made available by Qt and can be selected upon cloning the repository. However, the build path for each configuration
must be manually changed to adhere to the [expected build path for the 'Release' configuration](#building-the-project-for-local-development-and-execution) and the
[expected build path for 'Debug' or 'RelWithDebugInfo' configuration](#building-the-project-for-application-deployment).

To create a new configuration using desired build type:
1. Select the `Projects` tab from the left-hand menu bar
2. Select a kit with name that includes the desired toolchain/kit by clicking the `Manage Kits` button within the `Projects` page and choosing
from the selection of available kits presented. All of the toolchain-specific settings should be preset to the desired CMake build settings.
3. Change the build path to match the path syntax listed above according the `CMAKE_BUILD_TYPE` value of the kit configuration by clicking
the `Manage` button to the left of the `build directory` item under the `CMake` section.
4. Ensure you have placed the locally compatible version of Graphviz within the empty `Graphviz` directory as specified in the [intial setup section](#project-setup).

This should be sufficient to build the project with either configuration using CMake.
Further information on this process can be found [here](https://doc.qt.io/qtcreator/creator-how-to-activate-kits.html).

Upon completion of build process, the application will display the application window for accepting requests when executed. The most recently generated
images will be stored within the [graph_images](./graph_images) directory (they will be overwritten upon next execution if not copied and stored
elsewhere locally).


## Building Project using Microsoft Visual Studio

Upon cloning the repository, Visual Studio will most likely immediately request to modify `CMakeUserPresets.json` file after VS QT Tools extension
detects the project is a Qt project to add the provided paths/settings for the required Qt Components/Resources to the CMake Build settings. 

If this does not occur upon cloning the repository, double click on the `Folder View` tab under the `Solution Explorer` section and ensure the 
VS Qt Tools Extension is listed under the `Extensions` tab and is enabled before proceeding.

After these modification have been made/applied:

- Check that the build paths originally provided in the `CMakeUserPresets.json` are available for selection from configuration dropdown
    in the top menu bar. These should now automatically have the correct associated build paths set.

- Ensure you have placed the locally compatible version of Graphviz within the empty `Graphviz` directory as specified in the [intial setup section](#project-setup).

- Verify the compiler path is set correctly:
     - Select the `Extensions` tab -> `Qt Tools` -> `Qt Versions`
     - If no compiler profile is set, click `Autodetect` and see if a compiler profile is generated. This should be set to MVSC with a path to qmake.exe
    
Upon checking all of the above conditions have been met, the preset configurations can be built and the program executed within Visual Studio.

# Sample Generated Images

A gallery of pre-generated graph images can be found in the [graph_images](./graph_images) directory, which were generated
to show visualizations of lower density graphs using [my_graph5.txt](./sample_graphs/my_graph5.txt) and of higher density graphs
using [my_graph6.txt](./sample_graphs/my_graph6.txt) both of which can be found in the [sample_graphs directory](./sample_graphs)

> [!CAUTION]
> When building visualizations for graphs with higher edge densities like `my_graph6.txt`, it may take several minutes for the
> visualization software to complete the image generation process. In such cases, the detailed progress of the visualization process can
> be monitored through standard error ouput in the console.

Example Image Generated from `my_graph5.txt`

![Image of Shortest Path](./graph_images/sample_sp_graph5.png)

# Additional Resources

## Build Graphs using GoogleMaps API and Flask

The `main.py` file found in the [py_builder directory](./py_builder) was utilized for testing and generating graph text files
while using the GoogleMaps API to provided simplified distance data between geographic locations. The `main.py` file can be used to:

1. Generate the maximum number of unique edges that can be generated from a list of city names using the `create_max_edges` function
2. Parse an existing text file with a list of edges (where each line follows format of `city1, city2, `) and have the rough distance
   between the two existing city locations (requested from [GoogleMaps' DistanceMatrixAPI](https://developers.google.com/maps/documentation/distance-matrix)
   ) written at the end of the edge for all edges with valid locations. 

If wishing to use this, please visit [the DistanceMatrixAPI homepage](https://developers.google.com/maps/documentation/distance-matrix) to
create an account and generate the API key needed to make requests with the program. For the requests made by the program, the cost for such requests will
be virtually free and free trials with GCP credits are available for new accounts.

Please ensure you generate a virtual environment and install the requirements listed in `requirements.txt` before executing the Flask application.

# Citations

Third Party Software/Libraries Utilized in Building this Project Include:

- [Graphviz](https://www.graphviz.org/license/)

- [Qt](https://www.qt.io/licensing/open-source-lgpl-obligations#lgpl)

In accordance with the wishes of Qt and Graphviz, the LGPLv3 license has been included with this repository and the links to the
license agreements for both Graphviz and Qt are provided above.
