#include <SwitecX25.h>

#define PCMpin 11
// 315 degrees of range = 315x3 steps = 945 steps
// declare motor1 with 945 steps on pins 4-7
// For Refrence i am using a x27 motor and the X27 code is on the bottom LEFT of the steppter motor (the below instructions are based on looking at the motor from this angle(from where you can see the x27 code)) (pins should be on the opposite side of this face)
// I have my pins in the following order --- 5 Bottom Left, 4 Bottom Right, 7 TOP LEFT, 6 TOP Right 
SwitecX25 motor1(315*3, 4,5,6,7);


void setup(void) {
  pinMode(PCMpin,INPUT);
  Serial.begin(9600);
  Serial.println("Go!");
  // run both motors against stops to re-zero
  motor1.zero();// this is a slow, blocking operation
  // Set X as the starting point for this project, X being where 0 mph would be on your gauge
  motor1.setPosition(212);
  motor1.updateBlocking();
}

void setMotor(int steps){
  motor1.setPosition(steps);
  }
  
double mph_conversion(int htz){
  double mph = htz * 60;
  mph = mph * 60;
  ///The 4000 here is super important
  // 4000 is what my PCM is spitting out for Pulses PER Miles, if yours is diffrent change it here
  mph = mph / 4000;
  return(mph);
  }
  
double pcmhz(){
  //gets the cycle in microseconds
  //unsigned long hz1High = pulseIn(PCMpin, HIGH);
  //unsigned long hz1Low = pulseIn(PCMpin, LOW);
  // below is the cycle is microseconds
  //double period;
  //period = hz1High + hz1Low;
  // convert to hz (its microseconds, this means we need to convert microseconds to HZ, which is just microseconds to seconds, microseconds to seconds is just X(Microseconds) * 1,000,000)
  // the real method is to divid it
  //double hz = 1000000.0 / period;
  //return(hz);
  //return 60;
  }

  
int mph_to_steps(int mph){
  ////My gauge is from a 1966 c10 so its flat 180 degrees, this is where you will have to go out and measure and figure out for yourself what you need
  // stepper motor has 315 degreens of range and it does a 1/3 of this each step so we have 945 steps we can do
  // my max is 180 * 3 so i have 540 steps to reach the end of my gague, but i need to figure out what my starting point is and add this to my max.
  // i did 315 degrees - 180 = 135 then i did 180 - 135 == 45 degrees then i converted this to steps flmao 45 * 3 = 135
  // so my starting point is 135 steps and now i need to figure out my stop point, 180 degrees is 540 steps, i need to add my starting point which is 135 so 135 + 540 == 675
  // realisticly, you can just copy what i did give or take or just adjust your needle by hand (carefully)
  // Reminder this is just for a 0 - 180 angle gauge if yours is more than 180 just do the math for the steps and where your starting point is.
  // NEXT PART!!!~ the degrees traveld from 0-10 and 10-20(just to sanity check) after you figure out this should be easy, divide each degrees of measurement by 10 and then multiple by 3
  // after you have done the above part you should have how many steps it takes to equal 1 mph, you could divide by 20 and multiply by 3 for more resolution that would be steps for every 1/2 mph which is what imma do. (i want that smooth smooth)
  // 1965 gauge is not 180 its offset the following are my reading 70 degree is 40 mph, 35 deg is 0mph, 90 degrees is 50, 155 degrees is 100 mph, 33degrees is 10 mph and 45 degrees is 20 mph
  // Each 5 mph is ABOUT 6.44 degrees is around 6.44 degrees (GIVE OR TAKE)(side note i bet its gonna be like 6.45xxxx or something dumb like that)
  // divide 6.44 by 5 to get how many degrees for every mph
  // i need to make sure my min is starting at where my zero 0 my zero is 45 degrees +25.76 == 70.76 then i multiply by 3 == 212.28
  // middle of my gauge is 90 so its 45 + 90.16 * 3 = 405
  // my max would be 45 + 154.56 * 3 == 
  //int max = 675; // max range 180 degrees (this is my old max for 180 degrees)
  //int max = 599; // low key these measurements are killing me 6.44 is werid af
  int min = 212; // min range would be 0 on gauge
  int middle = 405; // just putting this here for fun
  // as i put this in the vehcial i can tune this to be more accurate.ill print the mph to the console to log
  double move = mph * 1.288;
  move = move + 70.76; // 70.76 is the base angle at 0 which is 212 / 3 (not exact since i am using 6.44 per 5 mph)
  int Final_Steps = move * 3;
  return Final_Steps;
  }

void loop(void) {
  unsigned long hz1High = pulseIn(PCMpin, HIGH); ///remove/add the 300ul, No signal from pcm slows the script
  unsigned long hz1Low = pulseIn(PCMpin, LOW);
  // below is the cycle is microseconds
  double period;
  period = hz1High + hz1Low;
  // convert to hz (its microseconds, this means we need to convert microseconds to HZ, which is just microseconds to seconds, microseconds to seconds is just X(Microseconds) * 1,000,000)
  // the real method is to divid it
  double hz = 1000000 / period;
  Serial.println("PCM HZ");
  Serial.println(hz);
  int mph = mph_conversion(hz);
  Serial.println("MPH");
  Serial.println(mph);
  int steps = mph_to_steps(mph);
  Serial.println("STEPS");
  Serial.println(steps);
  motor1.setPosition(steps);
  motor1.updateBlocking();
  
  

}
