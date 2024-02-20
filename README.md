# Ardunio ATINY85 x27 Stepper Speedo Gauge LS Swap
Program to control a x27 Stepper motor as a speedo, using an ATTiny or Arduino Uno using the signal from the PCM (Gen 3 Pin 50 LS SWAP) *default 4000 pulses Gen 3 speedo singal from PCM*

## Info
Right now the program is setup for a 1966 C10 Speedo, but take my code as a example for your project. (the number i multiply the steps by is my guesstimate angle i use for my gauge)
- Code does the following
  - Gets the singal period
  - Convert period to hz
  - Converts to mph (4000 pulses per mile singal)
  - mph to steps (1.288 is the angle per mile on my gauge)
  - Does the above 3 times and gets an average on steps
    - Any crazy movements above 14mph(54 steps) is taken out of the final average calculation.
  - updates the stepper motor to the average position

 - Atinty85 i have is at 16mhz
 - i recomend you use caps above 16v for extra cushion

# Warnings
Its a bit jumpy because your not suposed to control stepper motors with a atiny or ardunio usualy your going to use a stepper control chip like a AX1201728SG with the same libaray if you want that smooooothness. 

I personally did it this way to have a speedo without spending like 100+$ on a device that converts the speedo signal into the spinning speedo cable.

If you buy parts off aliexpress it comes out really cheap, maybe the most expensive parts would be the stepper motors and what ever your going to use as a programer

# Example board
I have 2 versions of this project Circuit board on PCBWAY

Keep in mind these are for cars.
- https://www.pcbway.com/project/shareproject/V2_SMD_X27_Stepper_Gauge_PWM_ATtiny85_5bdaa886.html
  - SMD version with thru holds to fit in a 1966 c10.

- https://www.pcbway.com/project/shareproject/X27_Stepper_Gauge_PWM_ATtiny85_bbd4aff2.html
  - Through hole version example. 
