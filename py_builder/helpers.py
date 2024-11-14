
# Line Validation Helper Function
def validate_line(edge: str) -> tuple | None:
    """
    Verifies if the line `edge` adheres to the required format
    of `city1_name, city2_name, ` for use in requests
    Returns a tuple of strings if valid, else returns None
    """
    first_comma = edge.find(",")
    if first_comma == -1:
        print(
            'Comma between city1 and city2 not found in line {}!'.format(
                edge)
        )
        return None
    vertex_1 = edge[:first_comma]
    # print(vertex_1)
    # print(edge[first_comma])
    if len(vertex_1) == 0:
        print(
            'No city1 name found before first comma in line {}'
            '!'.format(edge)
        )
        return None
    second_comma = edge.find(",", first_comma + 1, len(edge) - 1)
    # print(edge[second_comma])
    if second_comma == -1:
        print(
            'Comma between city2 and distance to be added not found in'
            'line {}'.format(edge)
        )
        return None
    middle_space = edge.find(" ", first_comma, len(edge) - 1)
    # print(edge[middle_space + 1])
    if middle_space == -1:
        print(
            'Whitespace separating first comma and first letter of'
            'city2 not found in line {}'.format(edge)
            )
        return None
    vertex_2 = edge[middle_space + 1: second_comma]
    if len(vertex_2) == 0:
        print(
            'No city2 name found after second comma in line {}'
            '!'.format(edge)
        )
        return None
    end_space = edge.find(" ", second_comma, len(edge))
    if end_space == -1:
        print(
            'Whitespace separating seond comma and end of line {}'
            'not found'.format(edge)
        )
        return None
    return (vertex_1, vertex_2)


def create_max_edges(city_list: list, edge_list) -> int:
    """
    Generates the maximum number of possible unique edges that can be derived
    from the cities/verticies found within the list array, `city_list`, using
    the list array, `edge_list` to both store the cities compromising of each
    unique edge in a tuple.
    Returns total number of unique edges generated and stored in `edge_list`
    """
    for city in city_list:
        for adj_city in city_list:
            if city == adj_city:
                continue
            city1_name = ""
            city2_name = ""
            already_exists = False
            for edge in edge_list:
                city1_name, city2_name = edge
                forward_match = (city1_name == city and
                                 city2_name == adj_city)
                reverse_match = (city1_name == adj_city and
                                 city2_name == city)
                if forward_match or reverse_match:
                    already_exists = True
                    break
            if not already_exists:
                edge_pair = (city, adj_city)
                edge_list.append(edge_pair)
    return len(edge_list)
