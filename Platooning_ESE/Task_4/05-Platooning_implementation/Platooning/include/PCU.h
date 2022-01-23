#ifndef PCU_HPP
#define PCU_HPP

class pcu
{
    public:
      pcu();
      void static pcu_setup();
      void static pcu_loop();
      void serializeData();
      void deserializeData();
      void dataProcesssing();
      void updateCoordinates(double latitude, double longitude);
      void updateGap(int gap);
      void updateIntruder(bool detected_status);
      void updateRxFrame(char* frame);
};



#endif