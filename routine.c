#include "routine.h"
#include "drive.h"
#include "lader.h"

int routine(){
    while(1){
      switch(bezigheid){
        case rijden:
          /*Hier moet de GPS zijn werk doen.*/
          break;
        case laden:
          /*Hier moeten we afhankelijk van wat de server zegt de lader gaan aansturen.*/
          break;
        default:
          /*Hier moeten we hem laten wachten.*/
          break;
      }
    }
}
