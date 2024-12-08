#include <iostream>
#include <vector>
#include <iosfwd>
#include <string>
#include <cstdio>

#include "derived_hashmap.h"
#include "graph_input.h"
#include "gprintf.h"

#include <QMessageBox>

/**
 * Overloading function for printing string Vector-type container arrays to standard output stream
 */
std::ostream& operator<<(std::ostream& out, const std::vector<std::string>& string_list) {
    out << "[ ";
    out << '\n';
    int key_counter = 0;
    for (auto& key : string_list) {
        if (key_counter == 10) {
            out << '\n';
            key_counter = 0;
        }
        if ( key == string_list.back()) {
            out << key;
        } else {
            out << key << ", ";
        }
        key_counter ++;
    }
    out << '\n';
    out << " ]";
    return out;
}

/**
 * Parses the absolute path, `abspath_to_file` for directory/file names with spaces and modifies
 * the path to be read-compatible for OS when passed as arguments within command line
 * @param abspath_to_file string holding absolute path of file to be parsed/modified
 * @returns modified version of absolute path to be read compatible
 */
static void path_parser(std::string& abspath_to_file) {
    size_t next_space = abspath_to_file.find(" ");
    // Determine Whether Spaces are found in path
    if(next_space != abspath_to_file.npos) {
        // Determine OS type by checking syntax natively generated path
        size_t next_back_slash = abspath_to_file.find("\\");
        size_t next_forward_slash = abspath_to_file.find("/");

        // Handle Search using backslash character if path has Windows path syntax
        if (next_back_slash != abspath_to_file.npos) {
            // Establish initial positions of slashes surrounding first detected space
            next_back_slash = abspath_to_file.rfind("\\", next_space);
            size_t closing_slash = abspath_to_file.find("\\", next_space);

            // Insert '"' character immediately after front slash and '\"' immediately before end slash
            abspath_to_file.insert(abspath_to_file.begin() + static_cast<long int>(next_back_slash) + static_cast<long int>(1), '"');
            abspath_to_file.insert(abspath_to_file.begin() + static_cast<long int>(closing_slash) + static_cast<long int>(1), '\\');
            abspath_to_file.insert(abspath_to_file.begin() + static_cast<long int>(closing_slash) + static_cast<long int>(2), '"');
            // Reposition front and end slashes according to position of next detected space
            next_back_slash = static_cast<size_t>(closing_slash + 3);
            closing_slash = abspath_to_file.find("\\", static_cast<size_t>(next_back_slash + 1));
            next_space = abspath_to_file.find(" ", static_cast<size_t>(next_back_slash));

            // Continue parsing each slice of front and end slashes until end of path is reached
            while (next_space != abspath_to_file.npos) {
                // If next space is not within slashes, update slash postioning until it is
                if (static_cast<size_t>(closing_slash) < static_cast<size_t>(next_space)) {
                    while (static_cast<size_t>(closing_slash) < static_cast<size_t>(next_space)) {
                        next_back_slash = static_cast<size_t>(closing_slash);
                        closing_slash = abspath_to_file.find("\\", static_cast<size_t>(next_back_slash + 1));
                    }
                }
                // Handle insertion when current section is not at end of path and contains a space
                if (next_space != abspath_to_file.npos && closing_slash != abspath_to_file.npos) {
                    // Insert '"' character immediately after front slash and '\"' immediately before end slash
                    abspath_to_file.insert(abspath_to_file.begin() + static_cast<long int>(next_back_slash) + static_cast<long int>(1), '"');
                    abspath_to_file.insert(abspath_to_file.begin() + static_cast<long int>(closing_slash) + static_cast<long int>(1), '\\');
                    abspath_to_file.insert(abspath_to_file.begin() + static_cast<long int>(closing_slash) + static_cast<long int>(2), '"');
                    // Reposition front and end slashes according to position of next detected space
                    next_back_slash = static_cast<size_t>(closing_slash + 3);
                    closing_slash = abspath_to_file.find("\\", static_cast<size_t>(next_back_slash) + static_cast<size_t>(1));
                    next_space = abspath_to_file.find(" ", static_cast<size_t>(next_back_slash));
                } else {
                    // Handle insertion when current section contains a space and is at end (would otherwise be bypassed at beginning of iteration)
                    abspath_to_file.insert(abspath_to_file.begin() + static_cast<long int>(next_back_slash) + static_cast<long int>(1), '"');
                    abspath_to_file.insert(abspath_to_file.end(), '\\');
                    abspath_to_file.insert(abspath_to_file.end(), '"');
                    break;
                }
            }
        }

        // Handle Search using forward slash character if path has Unix path syntax
        if (next_forward_slash != abspath_to_file.npos) {
            // Handle Search using forward slash character if path has Windows path syntax
            if (next_forward_slash != abspath_to_file.npos) {
                // Establish initial positions of slashes surrounding first detected space
                next_forward_slash = abspath_to_file.rfind("/", next_space);
                size_t closing_slash = abspath_to_file.find("/", next_space);
                // Insert '"\' substrings immediately after front slash and immediately before end slash
                abspath_to_file.insert(abspath_to_file.begin() + static_cast<long int>(next_forward_slash) + static_cast<long int>(1), '\\');
                abspath_to_file.insert(abspath_to_file.begin() + static_cast<long int>(next_forward_slash) + static_cast<long int>(2), '"');
                abspath_to_file.insert(abspath_to_file.begin() + static_cast<long int>(closing_slash) + static_cast<long int>(2), '\\');
                abspath_to_file.insert(abspath_to_file.begin() + static_cast<long int>(closing_slash) + static_cast<long int>(3), '"');
                // Reposition front and end slashes according to position of next detected space
                next_forward_slash = static_cast<size_t>(closing_slash + 3);
                closing_slash = abspath_to_file.find("/", static_cast<size_t>(next_forward_slash + 1));
                next_space = abspath_to_file.find(" ", next_forward_slash);
                // Continue parsing each slice of front and end slashes until end of path is reached
                while (next_space != abspath_to_file.npos) {
                    // If next space is not within slashes, update slash postioning until it is
                    if (closing_slash < next_space) {
                        while (closing_slash < next_space) {
                            next_forward_slash = static_cast<size_t>(closing_slash);
                            closing_slash = abspath_to_file.find("/", static_cast<size_t>(next_forward_slash + 1));
                        }
                    }
                    // Handle insertion when current section is not at end of path and contains a space
                    if (next_space != abspath_to_file.npos && closing_slash != abspath_to_file.npos) {
                        // Insert '"\' substrings immediately after front slash and immediately before end slash
                        abspath_to_file.insert(abspath_to_file.begin() + static_cast<long int>(next_forward_slash) + static_cast<long int>(1), '\\');
                        abspath_to_file.insert(abspath_to_file.begin() + static_cast<long int>(next_forward_slash) + static_cast<long int>(2), '"');
                        abspath_to_file.insert(abspath_to_file.begin() + static_cast<long int>(closing_slash) + static_cast<long int>(2), '\\');
                        abspath_to_file.insert(abspath_to_file.begin() + static_cast<long int>(closing_slash) + static_cast<long int>(3), '"');
                        // Reposition front and end slashes according to position of next detected space
                        next_forward_slash = static_cast<size_t>(closing_slash + 3);
                        closing_slash = abspath_to_file.find("/", static_cast<size_t>(next_forward_slash + 1));
                        next_space = abspath_to_file.find(" ", next_forward_slash);
                    } else {
                        // Handle insertion when current section contains a space and is at end (would otherwise be bypassed at beginning of iteration)
                        abspath_to_file.insert(abspath_to_file.begin() + static_cast<long int>(next_forward_slash) + static_cast<long int>(1), '\\');
                        abspath_to_file.insert(abspath_to_file.begin() + static_cast<long int>(next_forward_slash) + static_cast<long int>(2), '"');
                        abspath_to_file.insert(abspath_to_file.end(), '\\');
                        abspath_to_file.insert(abspath_to_file.end(), '"');
                        break;
                    }
                }
            }
        }
    }
    return;
}


int approximate_graph_vertex_count(unsigned int& vertex_count, std::string& read_name) {
    // Properly edit path string to ensure any directories or filenames with whitespace in name read properly
    path_parser(read_name);
    FILE *pipe_stream;
// Gather line count of text file containing graphical information using Linux-compliant bash command 'grep'
#ifdef __linux__
    std::string command_val = "grep -c ^ ";
    command_val.append(read_name);
// Gather line count of text file containing graphical information using MacOS-compliant bash command 'ggrep' for HomeBrew
#elif __APPLE__
    std::string command_val = "ggrep -c ^ ";
    command_val.append(read_name);
// Gather line count of text file containing graphical information using Windows-compliant powershell piped command captured as a single command
#elif _WIN32
    std::string command_val = "powershell -Command \"(Get-Content -Path ";
    command_val.append(read_name).append(" | Measure-Object -Line).Lines\"");
// Exit if unexpected OS-type is detected due to potentially incompatibility or undefined behavior in pipe operation
#else
    std::cerr << "Compatibility of OS with 'popen' command cannot be verified. Please restart program and manually enter an approximate value for total number of unique verticies\n";
    return -1;
#endif
    // Establish stream with intent to read from buffer containing the command line output written to standard output
#ifdef _WIN32
    pipe_stream = _popen(command_val.c_str(), "r");
#else
    pipe_stream = popen(command_val.c_str(), "r");
#endif

    std::string line;
    char buf[11];   // Digit count should not exceed maxmimum number for capacity allocation of data structures holding vertex information

    char *result;
    // If stream is successfully established with pipeline and is able to read it, extract the line count printed by grep command
    if (pipe_stream != NULL) {
        result = fgets(buf, sizeof(buf), pipe_stream);
        if (result) {
            line.append(result);
        }
        // Close stream using system-compatible version of pclose
#ifdef _WIN32
        _pclose(pipe_stream);
#else
        pclose(pipe_stream);
#endif
    } else {
        // Exit if fork or pipe operations fail
        perror("pipe/fork");
        std::cerr << "ERROR: Failed to establish pipeline stream for reading the line count from '" << read_name << "'\n";
        return -1;
    }

    if (line.size() == 0) {
        // If fails to extract information from buffer, exit with proper notification
        std::cerr << "ERROR: Reading of output for pipeline stream failed to extract line count from text file '" << read_name << "'\n";
        return -1;
    }
    // Convert extracted grep command ouput to a long integer and assign half its value to estimate the number of unique verticies for graph
    unsigned long vertex_conversion = strtoul(line.c_str(), nullptr, 10);

    if (errno == ERANGE || errno == EINVAL || vertex_conversion <= 0 || vertex_conversion > UINT_MAX) {
        std::cerr << "ERROR: Conversion of extracted line count for '" << read_name << "' failed. Please ensure text file is not empty and file is not exceedingly large\n";
        return -1;
    }

    double edge_density = 0.5;
    unsigned int edge_count = static_cast<unsigned int>(vertex_conversion);
    /*
     *  Assuming no overlapping edges are listed, can use formula for edge density of directed graphs
     *  to estimate the number of unique verticies from the number of lines in the text file(each line = 1 edge):
     *      Edge Density = # of Edges / (# of Verticies * (# of Verticies - 1))
     */
    vertex_count = static_cast<unsigned int>((((edge_density) + std::sqrt((pow(edge_density, 2)) + (4 * (edge_count) * (edge_density)))) / (2 * edge_density)));


    // Handle Exceedingly Small Line Counts in Parsing User-Selected Text File
    if (vertex_count < 5) {
        vertex_count = 5;
    }
    gprintf("Estimating Vertex Count to %i", vertex_count);
    return 0;
}
