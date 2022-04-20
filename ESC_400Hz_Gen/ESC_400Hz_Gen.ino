/* 400 Hz three phase generator
 * David Richards, 20th April 2022
 * see https://github.com/DavidJRichards/ESC_Inverter_400Hz 
 * Derived from:
 * Sensorless brushless DC (BLDC) motor control with Arduino UNO (Arduino DIY ESC).
 * This is a free software with NO WARRANTY.
 * https://simpl 8 MHz internal oscillatore-circuit.com/
 */

#define  FSYNC (1 << 2)    // port D2

byte bldc_step = 0, motor_speed;

void setup() {
  DDRD  |= (0x38 | FSYNC); // Configure pins 2 (sync), 3, 4 and 5 as outputs
  PORTD  = 0x00;
  DDRB  |= 0x07;           // Configure pins 9, 10 and 8 as outputs
  PORTB  = 0x38;
}

void AH_BL(){
  PORTB  =  0x02;
  PORTD &= ~(0x18 | FSYNC);
  PORTD |=  0x20;
}

void AH_CL(){
  PORTB  =  0x01;
  PORTD &= ~(0x18 | FSYNC);
  PORTD |=  0x20;
}

void BH_CL(){
  PORTB  =  0x01;
  PORTD &= ~(0x28 | FSYNC);
  PORTD |=  0x10;
}

void BH_AL(){
  PORTB  =  0x04;
  PORTD &= ~0x28;
  PORTD |=  (0x10 | FSYNC);
}

void CH_AL(){
  PORTB  =  0x04;
  PORTD &= ~0x30;
  PORTD |=  (0x08 | FSYNC);
}

void CH_BL(){
  PORTB  =  0x02;
  PORTD &= ~0x30;
  PORTD |=  (0x08 | FSYNC);
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
    delayMicroseconds(406); // ideal step rate is 1/6 of 1/400Hz (or 416)  
    bldc_move();
    bldc_step++;
    bldc_step %= 6;
  } 
}
