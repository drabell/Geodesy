# Geodesy | Class Lib | C++
#### Class Lib Version : 20.1.001

#### Author        : Alexander Bell

#### Copyright     : 2011-2025 Alexander Bell
***
##### Description: Three Methods to calculate great-circle (orthodromic) distance between two geo-points specified by their coordinates (Latitude, Longitude) in decimal format, e.g.
* _John F. Kennedy International Airport (JFK): {40.641766,-73.780968}_
* _Los Angeles International Airport (LAX): {33.942791,-118.410042}_
***
DISCLAIMER   : This Module is provided on AS IS basis without any warranty. The user assumes the entire risk as to the accuracy and the use of this module. In no event shall the author be liable for any damages arising out of the use of or inability to use this module.
             
TERMS OF USE : This module is copyrighted. Please keep the Copyright notice intact.
***
Sample calculation of the great-circle (orthodromic) distance between two geo-points (Lat/Lon):
* _JFK {40.641766,-73.780968}_
* _LHR {51.470020,-0.454295}_

| Method                        | Kilometers       | Miles            |Notes
|:------------------------------|:-----------------|:-----------------|:---------------------------------------|
| Haversine                     | 5540.1754190795  | 3442.5054053574  | High Accuracy (spherical algorithm)    |
| Spherical Law of Cosines      | 5540.1754190795  | 3442.5054053574  | High Accuracy (spherical algorithm)    |
| Inverse Vincenty              | 5555.0656860095  | 3451.7577882724  | Highest Accuracy (ellipsoid algorithm) |
| Expected value                |~5554.500 km      |~3451.400 miles   | ~ rounded                              |
***
