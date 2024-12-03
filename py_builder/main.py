import googlemaps
import requests
import flask
import math
import secrets
from helpers import validate_line, create_max_edges

# Extract API Key for GoogleMaps API from separate file
# NOTE: Simpler requests to DistanceMatrix API are free (example below)
with open('api_client.txt', "r") as api_file:
    app_secret = api_file.readline()

# Intialize constants to mitigate errors from typos
KEY = app_secret    # API key for DistanceMatrix API access
REFERENCE_FILE = 'empty.txt'    # Text file to be referenced in validation
GRAPH_FILE = 'full.txt'     # Text file to be filled with distance data

# List of all cities used generate and write formatted edges to GRAPH_FILE.
# Edges are used to build requests for edge distances from DistanceMatrix API
cities = ["Abilene", "Atlanta", "Austin", "Baltimore", "Baton Rouge", "Boise",
          "Colorado Springs", "Columbus", "Concord", "Cupertino", "Dallas",
          "Detroit", "Fargo", "Flagstaff", "Fresno", "Helena", "Houston",
          "Las Vegas", "Little Rock", "Los Angeles", "Lubbock", "Medford",
          "Minneapolis", "Montpelier", "Nashville", "New York", "Newark",
          "Oklahoma City", "Omaha", "Orlando", "Philadelphia", "Portland",
          "Providence", "Redding", "Sacramento", "San Diego", "San Francisco",
          "San Jose", "San Barbara", "Santa Cruz", "Santa Monica", "Seattle",
          "South Padre Island", "Tampa"]

# Generate GMAPS object for placing requests
gmaps = googlemaps.Client(key=KEY)

app = flask.Flask(__name__)
app.secret_key = secrets.token_urlsafe(32)

edge_list = []  # List to be populated with tuples of (city1, city2)
run_server = True  # Toggle whether to run server for API requests


# OPTION # 1: PROVIDE LIST OF CITIES TO BE USED TO GENERATE GRAPH TEXT FILE
# The maximum number of edges that can be generated from the city names listed
# in 'cities' are written to GRAPH_FILE on separate lines with the distance
# values retrieved from Google's DistanceMatrix API being added to each edge

# Max # of unique edges = (N * (N - 1)) / 2, where N = total # of unique cities
exp_edge_count = math.floor(len(cities) * (len(cities) - 1) / 2)

# Verify total # of lines written equals max # of possible unique edges
added_edges = create_max_edges(cities, edge_list)
if added_edges != exp_edge_count:
    print(
        'Expected edges to be added was {} but {} were added'.format(
            exp_edge_count, added_edges)
        )
    run_server = False
# -------------------------------------------------------------------------- #

# OPTION # 2: PROVIDE PRE-MADE TEXT FILE WITH EACH EDGE ON SEPARATE LINES
# Each line in provided REFERENCE_FILE will be verified to match the format
# of 'CITY1, CITY2, ' and then will have distance values retrieved from
# Google's DistanceMatrix API added for each edge listed in REFERENCE_FILE

# UNCOMMENT THIS SECTION AND COMMENT OUT OPTION #1 SECTION FOR USE OF OPTION #2
# with open(REFERENCE_FILE, "r+") as locations_file:
#     for line in locations_file:
#         # Verify line matches expected format for extraction of edge info
#         valid_results = validate_line(line)
#         if valid_results is None:
#             run_server = False
#             break

#         vertex1, vertex2 = valid_results
#         edge_list.append(valid_results)
# --------------------------------------------------------------------- #


# Upon completion of requests, GRAPH_FILE will have all distance information
@app.route("/")
def get_distance():
    with open(GRAPH_FILE, 'w+') as write_file:
        edge_count = 0
        for edge in edge_list:
            vertex_1, vertex_2 = edge
            # Examples for specifying a particular city with multiple locations
            # Otherwise, such request(s) to DistanceMatrix API may fail
            v1_concord = vertex_1 == "Concord"
            v2_concord = vertex_2 == "Concord"
            includes_concord = v1_concord or v2_concord
            v1_helena = vertex_1 == "Helena"
            v2_helena = vertex_2 == "Helena"
            includes_helena = vertex_1 == "Helena" or vertex_2 == "Helena"
            v1_fargo = vertex_1 == "Fargo"
            v2_fargo = vertex_2 == "Fargo"
            includes_fargo = vertex_1 == "Fargo" or vertex_2 == "Fargo"
            # %2C(unicode comma) to increase location precision to a state
            # Repeat for country if necessary
            if includes_concord:
                vertex_1 = (vertex_1 + "%2CNC" if v1_concord
                            else vertex_1)
                vertex_2 = (vertex_2 + "%2CNC" if v2_concord
                            else vertex_2)
            if includes_fargo:
                vertex_1 = (vertex_1 + "%2CND" if v1_fargo
                            else vertex_1)
                vertex_2 = (vertex_2 + "%2CND" if v2_fargo
                            else vertex_2)
            if includes_helena:
                vertex_1 = (vertex_1 + "%2CMT" if v1_helena
                            else vertex_1)
                vertex_2 = (vertex_2 + "%2CMT" if v2_helena
                            else vertex_2)
            # Build request using extracted city names in line and send to API
            dis_req = (
                'https://maps.googleapis.com/maps/api/distancematrix/json?'
                'destinations={}'
                '&origins={}'
                '&key={}'.format(vertex_2, vertex_1, KEY)
            )
            loc_info = requests.get(dis_req).json()
            # Convert to preferred distance unit from default value of meters
            miles = math.ceil(int(
                loc_info['rows'][0]['elements'][0]['distance']['value']
                ) * 0.000621371)

            # If cities had to be further specified, revert to initial names
            vertex_1 = (vertex_1[:len(vertex_1)-5] if vertex_1.find('%') != -1
                        else vertex_1)
            vertex_2 = (vertex_2[:len(vertex_2)-5] if vertex_2.find('%') != -1
                        else vertex_2)
            # Prevent addition of final newline after last edge
            if edge_count > 0:
                write_file.write('\n')
            # Add formatted line with retrieved distance value to file
            write_file.write(
                "{}, {}, {}".format(vertex_1, vertex_2, str(miles))
            )
            edge_count += 1
    return ("", 200)


if __name__ == "__main__":
    # Ensure server only starts if edge information for request is valid
    if run_server:
        app.run(host="127.0.0.1", port=8080, debug=True)
