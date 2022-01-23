#ifndef gps_h
#define gps_h

class gps
{
    public:
      gps();
      void gps_setup();
      void gps_loop();
      void captureCoordinates();
};

#endif