#include "GPS.h"
#include "drive.h"

void initGPS(){
  initDrive();
  aantal_nodes=0;
  nodeNumber=0;
  track = (GPS_node*)malloc(0*sizeof(GPS_node));
}

void followTrack(){
  for(nodeNumber=0; nodeNumber<aantal_nodes; nodeNumber++){
   /*Richtingsaanwijzer*/
    switch(track[nodeNumber].dir){
      case forward:
        forward();
        break;
      case left:
        left();
        break;
      case right:
        right();
        break;
      default:
        forward();
    }
  }

  /*Snelheidsaanduider*/
  speed(track[nodeNumber].max_speed);  

  /*Kilometerteller*/
    

}

void downloadGPS(){

}

GPS_node* getTrack(){

}
