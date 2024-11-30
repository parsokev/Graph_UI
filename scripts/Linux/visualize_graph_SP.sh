#!/usr/bin/env bash
graphviz_path='../../Graphviz/bin/dot.exe'
# Change Permission to ensure dot.exe can be executed for generating .gv file output to png format
chmod +x "$graphviz_path"
if [ $? -ne 0 ]; then
    echo ""
    echo "Permissions change for Graphviz dot.exe failed"
    echo "bash may also be in wrong env path and denied permission for script execution"
    echo ""
else
    echo "Permissions elevated to execute Graphviz dot executable for image generation"
fi

# Attempt to generate image of entire processed graph using graphviz
"$graphviz_path" -Tpng:cairo ../../dot_graphs/full_graph.gv -o ../../graph_images/full_graph.png
if [ $? -ne 0 ]; then
    echo "" 
    echo "VISUALIZATION ERROR DETECTED: An error was encountered while attempting to generate the image for the Complete Graph within \"full_graph.png\""
    echo "Please view the lines printed immediately above these to determine the potential nature of the detected errors"
    echo "For further information on feature access and troubleshooting please view the README: https://github.com/parsokev/graph_repo"
    echo ""
else
    echo "Success! The generated image of the COMPLETE GRAPH can now be viewed at \"graph_images/full_graph.png\""
fi

# Attempt to generate image of MST overlaying the entire processed graph using graphviz
"$graphviz_path" -Tpng:cairo ../../dot_graphs/full_graph.gv -o ../../graph_images/shortest_path_overlay.png
if [ $? -ne 0 ]; then
    echo ""
    echo "VISUALIZATION ERROR DETECTED: An error was encountered while attempting to generate the image for the Shortest Path within \"shortest_path_overlay.png\""
    echo "Please view the lines printed immediately above these to determine the potential nature of the detected errors"
    echo "For further information on feature access and troubleshooting please view the README: https://github.com/parsokev/graph_repo"
    echo ""
else
    echo "Success! The generated image of the SHORTEST PATH can now be viewed at \"graph_images/shortest_path_overlay.png\""
fi