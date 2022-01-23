#ifndef wifi_h
#define wifi_h

class wifi
{
    public:
      wifi();
      void wifi_setup();
      void wifi_loop();
      void TxSend();
      void RxReceive();
      void updateTxFrame();

};

#endif