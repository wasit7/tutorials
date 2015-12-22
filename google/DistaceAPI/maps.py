# -*- coding: utf-8 -*-
"""
Created on Fri Oct 16 11:30:30 2015

@author: Wasit
"""
from datetime import datetime
import googlemaps
import json
import codecs

# Replace the API key below with a valid API key.
keyfile=open('google.key','r')

gmaps = googlemaps.Client(key=keyfile.read())

# Geocoding and address
#geocode_result = gmaps.geocode('1600 Amphitheatre Parkway, Mountain View, CA')

# Look up an address with reverse geocoding
#reverse_geocode_result = gmaps.reverse_geocode((40.714224, -73.961452))

# Request directions via public transit
now = datetime.now()
directions_result = gmaps.directions("Department of Computer Science TU",
                                     "Future Park Rangsit Rangsit Pathum Thani",
                                     mode="driving",
                                     departure_time=now)
str_directions=json.dumps(directions_result,
                   sort_keys=True,
                   indent=4, 
                   separators=(',', ': '))
with codecs.open("directions.txt", "w", "utf-8-sig") as temp:
    temp.write(str_directions)
