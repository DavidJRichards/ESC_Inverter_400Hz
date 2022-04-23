/* 400 Hz three phase generator
 * David Richards, 20th April 2022
 * see https://github.com/DavidJRichards/ESC_Inverter_400Hz 
 * Derived from:
 * Sensorless brushless DC (BLDC) motor control with Arduino UNO (Arduino DIY ESC).
 * This is a free software with NO WARRANTY.
 * https://simpl 8 MHz internal oscillatore-circuit.com/
 */

#define  FSYNC   (1 << 2)    // port D2

#define  BpFET   (1 << 7)
#define  ApFET   (1 << 5)
#define  CpFET   (1 << 4)

#define  CnFET   (1 << 3)
#define  BnFET   (1 << 1)
#define  AnFET   (1 << 0)


byte bldc_step = 0, motor_speed;

void setup() {
  DDRD  = (AnFET | BnFET | CnFET | ApFET | BpFET | CpFET | FSYNC); // Configure pins 0,1,3, 4,5,7, and 2 as outputs
  PORTD  = 0x00;
}

void AH_BL(){
  PORTD = ApFET | BnFET;
}

void AH_CL(){
  PORTD = ApFET | CnFET;
}

void BH_CL(){
  PORTD = BpFET | CnFET;
}

void BH_AL(){
  PORTD = BpFET | AnFET | FSYNC;
}

void CH_AL(){
  PORTD = CpFET | AnFET | FSYNC;
}

void CH_BL(){
  PORTD = CpFET | BnFET | FSYNC;
}

void bldc_move(){        // BLDC motor commutation function
  switch(bldc_step){
    case 0:
      AH_BL();
      break;
    case 1:
      AH_CL();
      break;
    case 2:
      BH_CL();
      break;
    case 3:
      BH_AL();
      break;
    case 4:
      CH_AL();
      break;
    case 5:
      CH_BL();
      break;
  }
}

void loop() {
  // generate 400 Hz three phase
  while(true) {
    // delay value chosen for nearest approximation to 400 Hz output
    delayMicroseconds(408); // ideal step rate is 1/6 of 1/400Hz (or 416)  
    bldc_move();
    bldc_step++;
    bldc_step %= 6;
  } 
}
