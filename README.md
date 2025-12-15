# Geodesy
3 Methods to calculate great-circle (orthodromic) distance between two geo-points (C++)

Class Lib Version       : 20.1.001
***********************************************************************************
Author        : Alexander Bell

Copyright     : 2011-2025 Alexander Bell
***********************************************************************************
DISCLAIMER   : This Module is provided on AS IS basis without any warranty. The user assumes the entire risk as to the accuracy and the use of this module. In no event shall the author be liable for any damages arising out of the use of or inability to use this module.
             
TERMS OF USE : This module is copyrighted. Please keep the Copyright notice intact.
***********************************************************************************

Sample calculation of the great-circle (orthodromic) distance between two geo-points:
* JFK {40.641766,-73.780968}
* LHR {51.470020,-0.454295}

| Method                        | Kilometers       | Miles            |Notes
|:------------------------------|:-----------------|:-----------------|:------------------|
| Haversine                     | 5540.1754190795  | 3442.5054053574  | High Accuracy     |
| Spherical Law of Cosines      | 5540.1754190795  | 3442.5054053574  | High Accuracy     |
| Inverse Vincenty              | 5555.0656860095  | 3442.5054053574  | Highest Accuracy  |
| Expected value                | ~ 5554.500 km    | ~3451.400 miles  |                   |

----------------------------------------------------------------------------

