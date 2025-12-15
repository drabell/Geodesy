/**********************************************************************************
Module        : Geodesy.cpp | Class Lib | C++
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

#include <cmath>
#include <numbers>
#include <stdexcept>
#include "Geodesy.h"

// Haversine algorithm *************************************************************
/// <summary>
/// Haversine algorithm enables high-accuracy geodesic calculation 
/// of the great-circle (a.k.a. orthodromic) distance (km/miles) 
/// between two geographic points on the Earth's surface.
/// </summary>
/// <param name="Lat1">double: 1st point Latitude</param>
/// <param name="Lon1">double: 1st point Longitude</param>
/// <param name="Lat2">double: 2nd point Latitude</param>
/// <param name="Lon2">double: 2nd point Longitude</param>
/// <returns>double: distance, km/miles</returns>
double Geodesy::Haversine(double lat1, double lon1,
                          double lat2, double lon2,
                          Units unit) {
    try {
        double φ1 = lat1 * toRad;
        double φ2 = lat2 * toRad;

        double a = std::sin((φ2 - φ1) / 2);
        a *= a;

        double b = std::sin(((lon2 - lon1) / 2) * toRad);
        b *= b * std::cos(φ1) * std::cos(φ2);

        // central angle
        double ca = 2 * std::asin(std::sqrt(a + b));
        
        return ca * meanR * (unit == Units::SI ? 1.0 : 1.0 / mi2km);
    }
    catch (...) { return -1; }
}

// Spherical Law of Cosines ********************************************************
/// <summary>
/// Spherical Law of Cosines (SLC) algorithm enableshigh-accuracy 
/// geodesic calculation of the great-circle (a.k.a. orthodromic) 
/// distance (km/miles) between two geographic points on Earth's.
/// Note: results are close to Haversine formula, which is generally 
/// preferred for numerical stability with small distances calculation.
/// </summary>
/// <param name="Lat1">double: 1st point Latitude</param>
/// <param name="Lon1">double: 1st point Longitude</param>
/// <param name="Lat2">double: 2nd point Latitude</param>
/// <param name="Lon2">double: 2nd point Longitude</param>
/// <returns>double: distance, km/miles</returns>
double Geodesy::SLC(double lat1, double lon1,
                    double lat2, double lon2,
                    Units unit) {
    try {
        double φ1 = lat1 * toRad;
        double φ2 = lat2 * toRad;
        double Δλ = (lon1 - lon2) * toRad;

        // central angle
        double ca = std::acos(std::sin(φ1) * std::sin(φ2) +
            std::cos(φ1) * std::cos(φ2) * std::cos(Δλ));

        return ca * meanR * (unit == Units::SI ? 1.0 : 1.0 / mi2km);
    }
    catch (...) { return -1; }
}

// Vincenty inverse algorithm (ellipsoid) ******************************************
/// <summary>
/// Inverse Vincenty (ellipsoid) algorithm enables very high-accuracy 
/// geodesic calculation of the great-circle (orthodromic)
/// distance between two geographic points on the Earth's surface.
/// Notes ----------------------------------------------------------------
/// Inverse Vincenty (ellipsoid) algorithm provides the highest accuracy 
/// among the common spherical/ellipsoidal computational methods, 
/// but it is not a closed-form. This inverse solution for the distance 
/// and bearings between two points on the ellipsoid uses an efficient 
/// iterative algorithm with nested expressions well-suited for
/// the software implementation. 
/// Regarding its accuracy and robustness:
/// - Convergence:
/// The inverse method can fail near antipodal points.
/// Use a max-iteration guard and a small epsilon; if it fails, fall back
/// to a more robust geodesic algorithm.
/// - Precision:
/// Double precision is sufficient; avoid premature rounding of inputs.
/// Keep lat/lon in radians for the loop.
/// - Model choice:
/// WGS84 is standard. For different datum (e.g., GRS80), set 𝑎/𝑓 accordingly.
/// - Outputs:
/// Besides distance, this method can return initial/final bearings.
/// - AI vibe coding:
/// This Inverse Vincenty geodesic method was implemented in AI-assisted
/// pair programming (vibe coding) interactive session with AI Copilot.
/// ---------------------------------------------------------------------------
/// </summary>
/// <returns>double: orthodromic distance, km/miles</returns>
double Geodesy::Vincenty(double lat1, double lon1,
                             double lat2, double lon2,
                             Units unit) {
    const double a = 6378137.0; // WGS84 Earth equatorial radius (m)
    const double f = 1.0 / 298.257223563;
    const double b = a * (1.0 - f);
    try {
        double φ1 = lat1 * toRad, φ2 = lat2 * toRad;
        double Δλ = (lon2 - lon1) * toRad;

        double U1 = std::atan((1 - f) * std::tan(φ1));
        double U2 = std::atan((1 - f) * std::tan(φ2));

        double sinU1 = std::sin(U1), cosU1 = std::cos(U1);
        double sinU2 = std::sin(U2), cosU2 = std::cos(U2);

        double λ = Δλ, λPrev;
        int iterLimit = 100;
        const double ε = 1e-12;

        double sinσ, cosσ, σ, sinα, cos2α, cos2σM;
        double u2, A, B, Δσ;

        do {
            double sinλ = std::sin(λ), cosλ = std::cos(λ);
            double term1 = cosU2 * sinλ;
            double term2 = cosU1 * sinU2 - sinU1 * cosU2 * cosλ;

            sinσ = std::sqrt(term1 * term1 + term2 * term2);
            if (sinσ == 0.0) return 0.0; // coincident points

            cosσ = sinU1 * sinU2 + cosU1 * cosU2 * cosλ;
            σ = std::atan2(sinσ, cosσ);

            sinα = (cosU1 * cosU2 * sinλ) / sinσ;
            double sin2α = sinα * sinα;
            cos2α = 1.0 - sin2α;

            cos2σM = (cos2α != 0.0) ? cosσ - (2.0 * sinU1 * sinU2) / cos2α : 0.0;

            u2 = (cos2α * (a * a - b * b)) / (b * b);

            A = 1.0 + (u2 / 16384.0) *
                (4096.0 + u2 * (-768.0 + u2 * (320.0 - 175.0 * u2)));
            B = (u2 / 1024.0) * (256.0 + u2 * (-128.0 + u2 * (74.0 - 47.0 * u2)));

            double cos2αM2 = cos2σM * cos2σM;
            Δσ = B * sinσ * (cos2σM + (B / 4.0) * (cosσ * (-1.0 + 2.0 * cos2αM2) -
                (B / 6.0) * cos2σM * (-3.0 + 4.0 * sinσ * sinσ) *
                (-3.0 + 4.0 * cos2αM2)));

            double C = (f / 16.0) * cos2α * (4.0 + f * (4.0 - 3.0 * cos2α));

            λPrev = λ;
            λ = Δλ + (1.0 - C) * f * sinα *
                (σ + C * sinσ * (cos2σM + C * cosσ * (-1.0 + 2.0 * cos2αM2)));

            if (std::fabs(λ - λPrev) < ε) break;
        } while (--iterLimit > 0);

        if (iterLimit == 0) throw std::runtime_error("Vincenty: No convergence");

        double s = b * A * (σ - Δσ) / 1000.0;

        return s * (unit == Units::SI ? 1.0 : 1.0 / mi2km);
    }
    catch (...) { return -1; }
}