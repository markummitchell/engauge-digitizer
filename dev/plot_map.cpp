#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

void pointToPoint (ofstream &ofile, double latFrom, double lonFrom, double latTo, double lonTo)
{
  const int NUM_I = 100;
  const double D2R = 3.1416/ 180.0;

  double xFrom = cos (latFrom * D2R) * cos (lonFrom * D2R);
  double yFrom = cos (latFrom * D2R) * sin (lonFrom * D2R);
  double zFrom = sin (latFrom * D2R);

  double xTo = cos (latTo * D2R) * cos (lonTo * D2R);
  double yTo = cos (latTo * D2R) * sin (lonTo * D2R);
  double zTo = sin (latTo * D2R);

  for (int i = 0; i < NUM_I; i++) {
    double s = (double) i / (double) NUM_I;
    double x = (1.0 - s) * xFrom + s * xTo;
    double y = (1.0 - s) * yFrom + s * yTo;
    double z = (1.0 - s) * zFrom + s * zTo;

    double r = sqrt (x * x + y * y + z * z);

    double lat = asin (z / r) / D2R;
    double lon = atan2 (y, x) / D2R;

    ofile << lon << " " << lat << endl;
  }
}

int main (int argc, char** argv)
{
  double latLosAngeles = 34.05, lonLosAngeles = -118.25;
  double latParis = 48.86, lonParis = 2.35;
  double latTokyo = 35.41, lonTokyo = 139.5;
  double latMelbourne = -37.8, lonMelbourne = 144.96;
  double latLagos = 6.45, lonLagos = 3.39;
  double latRio = -22.9, lonRio = -43.2;

  ofstream ofile;
  ofile.open ("plot_map.dat");

  pointToPoint (ofile, latLosAngeles, lonLosAngeles, latParis, lonParis);
  pointToPoint (ofile, latParis, lonParis, latTokyo, lonTokyo);
  pointToPoint (ofile, latTokyo, lonTokyo, latMelbourne, lonMelbourne);
  pointToPoint (ofile, latMelbourne, lonMelbourne, latLagos, lonLagos);
  pointToPoint (ofile, latLagos, lonLagos, latRio, lonRio);
  pointToPoint (ofile, latRio, lonRio, latLosAngeles, lonLosAngeles);

  ofile.close ();
}
