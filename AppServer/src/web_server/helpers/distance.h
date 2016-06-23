#ifndef _DISTANCE_HELPER_
#define _DISTANCE_HELPER_

/** Include area. */
#include <cmath> 

/** Constants. */
#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

class DistanceHelper{
public:
  /** This function converts decimal degrees to radians.
   *
   *  \param deg the input degrees value.
   *
   *  \return the value in radians.
   */
  static double deg2rad(double deg) {
    return (deg * pi / 180);
  }


  /** This function converts radians to decimal degrees
   *
   *  \param rad Is the input value in radians.
   *
   *  \return The same value in decimal.
   */
  static double rad2deg(double rad) {
    return (rad * 180 / pi);
  }


  /** Returns the distance between two points on the Earth.
   *  Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
   *
   *  \param lat1d Latitude of the first point in degrees
   *  \param lon1d Longitude of the first point in degrees
   *  \param lat2d Latitude of the second point in degrees
   *  \param lon2d Longitude of the second point in degrees
   *  \return The distance between the two points in kilometers
   */
  static double distanceEarth(
      double lat1d, 
      double lon1d, 
      double lat2d, 
      double lon2d) {
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = deg2rad(lat1d);
    lon1r = deg2rad(lon1d);
    lat2r = deg2rad(lat2d);
    lon2r = deg2rad(lon2d);
    u = sin((lat2r - lat1r)/2);
    v = sin((lon2r - lon1r)/2);
    return 2.0 * earthRadiusKm * 
      asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
  }
};

#endif
