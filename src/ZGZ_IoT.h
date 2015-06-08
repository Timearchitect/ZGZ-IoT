#ifndef ZGZ_IoT_h
#define ZGZ_IoT_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//pin definitions
#define I0 A0
#define I1 A1
#define I2 A2
#define I3 A3
#define I4 A4
#define I5 A5
#define O0 11
#define O1 10
#define O2 9
#define O3 6
#define O4 5
#define O5 3


#define LED_LENGTH 20
#define BUTTONGROUP_LENGTH 10


#define MELODY_LENGTH 32

String urlEncode(String);

class Melody{
	public:
		Melody(int pin);
		void play(int length, int notes[],int diration[], float speed=1.3);
		void beep(int note=20, int length=30);
		void playTone(int note, int length=10);

		void effect_win();
		void effect_gameover();
		void effect_score();

	private:
		int pin;

};

class Button{
	public:
		Button(int pin=8,bool pressedValue=HIGH);
		void begin();
		bool pressed(int timeout=0);
		bool released(int timeout=0);
		bool doublePressed(int timeout=0,int tolerance=500);
		virtual bool getState();

	protected:
		int pin;
		bool pressedValue;
		bool checkPress(int timeout, bool requiredState);

};

class ButtonGroup{
	public:
		ButtonGroup();
		void begin(int length, int buttons[], bool pressedValue=HIGH);
		int pressed(int timeout=0);
	private:
		int buttons[BUTTONGROUP_LENGTH];
		//bool iStarted[BUTTONGROUP_LENGTH];
		int buttonsCount;
		bool pressedValue;

		int checkPress(int timeout, bool requiredState);
};

class LDR : public Button{
	public:
		LDR(int pin=A1);
		void config(int baseValue,int threashold);
		virtual bool getState();
		void test();

	protected:
		int base;
		int threashold;

};

class TiltSwitch : public Button{
	public:
		TiltSwitch(int pin, bool pressedValue=LOW);
};

class LED{
	//Mostly for the LED component in Tinkerkit
	public:
		LED(int pin=9);
		void begin();
		void on();
		void off();
		void blink(int speed,int times=1);
	private:
		int pin;
};

class PiezoKnockSensor{
	public:
		PiezoKnockSensor(int pin=A0);
		void config(int threshold=40,int debounceTime=80);
		bool knocked(int timeout=0);
		void test();
	private:
		int pin;
		int threshold;
		long debounceTime;
};

class Knob{
	public:
		Knob(int pin);
		int getValue();
		void setLevels(int levels);
		int getLevel();
	private:
		int pin;
		int levels;
};

class Joystick{
    public:
        Joystick(int x, int y);
        int getX();
        int getY();
    private:
        int x;
        int y;
    };

class UltrasonicSensor{
    public:
        UltrasonicSensor(int trig=11, int echo=12);
		int getDistance();
    private:
		int trig, echo;
};

#endif
