#ifndef GRAPH_INPUT_H
#define GRAPH_INPUT_H

#pragma once
#include <string>
#include "derived_hashmap.h"

#include <QProgressDialog>

/**
 * Assigns the value of the number of unique verticies found within the graph, `vertex_count`,
 * represented by the graphical information stored within the text file `read_name` to be exactly
 * half the number of lines found within the `read_name`
 * @param vertex_count Number of unique verticies found within graph represented by information stored in `read_name`
 * @param read_name Name of text file that user has chosen for processing by the program
 * @return 0 if successful, -1 upon failure
 */
extern int approximate_graph_vertex_count(unsigned int& vertex_count, std::string& read_name);
#endif // GRAPH_INPUT_H
