#include <Arduino.h>
int ENA = 18;  // Enable pin for motor (controls speed via PWM)
int IN1 = 21;  // Input pin 1 (controls direction)
int IN2 = 19;  // Input pin 2 (controls direction)
int IN3 = 17;
int IN4 = 16;

const int frequency = 1000;  // PWM frequency (1kHz)
const int pwm_channelA = 0;   // PWM channel (using channel 0)
const int pwm_channelB = 1;   // PWM channel (using channel 1) 
const int pwm_channelC = 2;
const int pwm_channelD = 3;
const int resolution = 8;    // 8-bit resolution (0-255 for speed control)

void setUpPWM() {
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);


    // Set motor direction: IN1 HIGH, IN2 LOW (forward)
    // digitalWrite(IN1, LOW);
    // digitalWrite(IN2, HIGH);

    // Setup PWM on the IN1 pin
    ledcSetup(pwm_channelA, frequency, resolution);
    ledcAttachPin(IN1, pwm_channelA);
    ledcSetup(pwm_channelB, frequency, resolution);
    ledcAttachPin(IN2, pwm_channelB);

    ledcSetup(pwm_channelC, frequency, resolution);
    ledcAttachPin(IN3, pwm_channelC);
    ledcSetup(pwm_channelD, frequency, resolution);
    ledcAttachPin(IN4, pwm_channelD);
}

void setPWM(int pwm) {
    if (pwm > 0) {
        ledcWrite(pwm_channelB, 0);
        ledcWrite(pwm_channelD, 0);
        ledcWrite(pwm_channelA, pwm);
        ledcWrite(pwm_channelC, pwm);
    }
    else if (pwm < 0) {
        ledcWrite(pwm_channelA, 0);
        ledcWrite(pwm_channelC, 0);
        ledcWrite(pwm_channelB, abs(pwm));
        ledcWrite(pwm_channelD, abs(pwm));
    }
    else {
        ledcWrite(pwm_channelA, pwm);
        ledcWrite(pwm_channelC, pwm);
        ledcWrite(pwm_channelB, abs(pwm));
        ledcWrite(pwm_channelD, abs(pwm));
    }
    
    
}
