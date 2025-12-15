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
#### Theory
The calculation of the great-circle (orthodromic) distance between two geographic points on the Earth's surface representas one of the core geodesic problems. Although this may appear to be a trivial geodesic task, it requires a non-trivial algorithmic implementation. If the problem were confined to plane geometry, the Pythagorean theorem would provide a simple solution. However, actual GIS computations involve three-dimensional models—specifically spherical or ellipsoidal representations of the Earth—which demand more elaborate approaches.

The spherical model introduces a systemic error, with a typical margin of about 0.1% to 0.5%. This level of accuracy is generally acceptable for many commercial-grade, general-purpose applications. In contrast, the more accurate ellipsoidal model of the Earth (as implemented, for example, in the inverse Vincenty algorithm) theoretically reduces the error margin to fractions of a millimeter, though at the cost of significantly increased computational complexity.
##### Systemic Error Margin
The Earth is an oblate spheroid, flattened at the poles and bulging at the equator. Its equatorial radius is approximately 6,378 km, while its polar radius is about 6,357 km. This difference of roughly 21 km means that the "true" radius varies with latitude.

The spherical Earth model is an approximation, and its primary systemic error arises from ignoring the Earth's oblateness. The error margin in orthodromic distance calculations using the spherical model depends on both the computational algorithm employed and the fixed radius assumed. For the commonly used mean Earth radius of 6,370 km, the maximum relative error is typically less than 0.56%, corresponding to about 21 km for very long distances, depending on the specific points and formula applied.
####  Spherical Earth Math Model/Algorithms
* Haversine
* Spherical Law of Cosines
* Spherical Earth Projection
####  Ellipsoidal Earth Math Model/Algorithm
* Inverse Vincenty formula
***
