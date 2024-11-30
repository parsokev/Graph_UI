# Project Description:

This project was developed with the intent to convert [a previous application that generates graphical images from user-provided text files strictly through interaction with a command console](https://github.com/parsokev/graph_repo)
into a graphical user interface (GUI) that provides the same functionality.

This was achieved through the utilization of:
   - [Qt Creator](https://doc.qt.io/qt-6/qt-intro.html) to develop an interactive cross-platform application window that accepts user-requested graphical solutions from a graph
      whose edges are described in each separate line within a text file selected by the user.

   - [Graphviz](https://www.graphviz.org/) was utilized to visualize the submitted graphical information, along with the requested solution, in PNG-formatted images.

# Requirements
[!WARNING]
[
- In order to reduce file size and maintain local-machine compatibility, the Graphviz directory has been ommitted from the repository.
- [Please visit Graphviz to download the most stable ZIP-archived version that is compatible with your local machine](https://www.graphviz.org/download/), copy/extract its contents (excluding the main folder),
- and place them directly within the cloned repository's [Graphviz directory](./Graphviz). This will eliminate the required installation of Graphviz on the local machine while still allowing for its use by the application.
]

# Deploying Executable


# Citations:
Third Party Software/Libraries Utilized in Building this Project Include:

- [Graphviz](https://www.graphviz.org/license/)

- [Qt](https://www.qt.io/licensing/open-source-lgpl-obligations#lgpl)
