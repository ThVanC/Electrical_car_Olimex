//
//  soc_test.h
//  Electrical_Car_Olimex
//
//  Created by Zeger Van de Vannet on 21/04/13.
//  Copyright (c) 2013 Zeger Van de Vannet. All rights reserved.
//

#ifndef Electrical_Car_Olimex_soc_test_h
#define Electrical_Car_Olimex_soc_test_h
#include "controller_car.h"

unsigned long start_time;
unsigned long now;
battery specs;

int measureV();
int measureI();

#endif
