# Project Description:

This project was developed with the intent to convert [a previous application](https://github.com/parsokev/graph_repo) that generates graphical images 
from user-provided text files strictly through interaction with a command console into a graphical user interface (GUI) that provides the same functionality.

This was achieved through the utilization of:
   - [Qt Creator](https://doc.qt.io/qt-6/qt-intro.html) to develop an interactive cross-platform application window that accepts user-requested
      graphical solutions from a graph
      whose edges are described in each separate line within a text file selected by the user.

   - [Graphviz](https://www.graphviz.org/) was utilized to visualize the submitted graphical information, along with the requested solution, in PNG-formatted images.

Upon completing the required steps for project setup outlined in the [Project Setup section](#project-setup),
the application will generate an application window that will allow the user to:
    1. Select a local text file providing graphical information to be processed/visualized in terms of individual edges.
        - Each separate line describes a unique edge found in the graph in the format of:
            - `vertex1, vertex2, distance-between-verticies`
    2. Either manually enter an estimated number of verticies for the graph or request for the program automatically estimate the number
    3. Select whether the program should visualize the Minimum Spanning Tree or shortest path between two specified verticies, using the text file



# Project Setup
> [!IMPORTANT]
> In order to reduce file size and maintain local-machine compatibility, the Graphviz directory has been omitted from the repository.
> Please download the most stable ZIP-archived version that is compatible with your local machine from the [download page for Graphviz](https://www.graphviz.org/download/),
> and place the extracted contents(excluding the main folder itself) directly into the cloned repository's [Graphviz directory](./Graphviz).
> This will eliminate the required installation of Graphviz on the local machine while still allowing for its use by the application.



# Deploying Executable


# Citations:
Third Party Software/Libraries Utilized in Building this Project Include:

- [Graphviz](https://www.graphviz.org/license/)

- [Qt](https://www.qt.io/licensing/open-source-lgpl-obligations#lgpl)
