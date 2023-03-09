#!/bin/bash

API_URL="https://gps-track3r-api.herokuapp.com"

# Get current location of tracker node -> GPS-NODE:A28D6AFFA1397C914D
curl "$API_URL/gps?id=GPS-NODE:A28D6AFFA1397C914DF&target=currentLocation"

# Get track data log on tracer node -> GPS-NODE:A28D6AFFA1397C914D
curl "$API_URL/gps?id=GPS-NODE:A28D6AFFA1397C914DF&target=tracking"

# Post location data to API (Used by tracker)
curl "$API_URL/api?longitude=30.97&latitude=-17.79&id=GPS-NODE:A28D6AFFA1397C914DF"

