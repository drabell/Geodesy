/**********************************************************************************
Module        : Geodesy.h | Header File | C++
Description   : Methods to calculate orthodromic distance between two geo-points
Version       : 20.1.001
***********************************************************************************
Author        : Alexander Bell
Copyright     : 2011-2025 Alexander Bell
***********************************************************************************
DISCLAIMER   : This Module is provided on AS IS basis without any warranty.
             : The user assumes the entire risk as to the accuracy and the use of
             : this module. In no event shall the author be liable for any damages
             : arising out of the use of or inability to use this module.
TERMS OF USE : This module is copyrighted. Please keep the Copyright notice intact.
***********************************************************************************/

#pragma once
#include <numbers>

/// <summary>
/// Class Geodesy contains three static methods to calculate the
/// great-circle (orthodromic) distance between two geo-points on Earth
/// specified by coordinates (Latitude, Longitude), e.g.
/// John F. Kennedy International Airport (JFK): {40.641766,-73.780968},
/// Los Angeles International Airport (LAX): {33.942791,-118.410042}
/// ====================================================================
/// Great-circle (orthodromic) distance between two geo-points:
///   JFK Lat / Lon : {40.641766, -73.780968}
///   LHR Lat / Lon : {51.470020, -0.454295}
///=====================================================================
/// Algorithm                       Kilometers          Miles
/// --------------------------------------------------------------------
/// Haversine                       5540.1754190795     3442.5054053574
/// Spherical Law of Cosines        5540.1754190795     3442.5054053574
/// Vincenty(Inverse)               5555.0656860095     3451.7577882724
/// --------------------------------------------------------------------
/// </summary>
class Geodesy {

private:
    // constants

    // Earth mean radius, km
    static constexpr double meanR = 6371.009;

    // miles to kilometers conversion factor
    static constexpr double mi2km = 1.609344; 

    static constexpr double π = std::numbers::pi;
    //note: alternatively for C++ Versions prior to C++20:
    //static constexpr double π = 3.141592653589793238462643383279502884;

    static constexpr double toRad = π / 180.0;

public:

    // SI: km, US: miles
    enum class Units { SI, US }; 


    static double Haversine(double lat1, double lon1,
                            double lat2, double lon2,
                            Units unit);
    static double SLC(double lat1, double lon1,
                      double lat2, double lon2,
                      Units unit);

    static double Vincenty(double lat1, double lon1,
                           double lat2, double lon2,
                           Units unit);
};