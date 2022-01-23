#ifndef lidar_h
#define lidar_h

class lidar
{
    public:
      lidar();
      void lidar_setup();
      void lidar_loop();
      void captureGap();
};

#endif