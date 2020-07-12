
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 
#define OC1A_WIDTH OCR1A
#define OC1_PERIOD ICR1

enum tone_scale
{
   No, Do, Rae, Mi, Pa, Sol, Ra, Si_P, Si, Do_5, Rae_5, DO_3, SI_2, SOL_2, PA_2, SI_0, DO_1
};

uint16_t frequency_return(uint16_t fre); 

void tone(uint8_t scale, uint16_t delay);

void delay_ms(int ms)
{
   while(ms-- != 0)
   {
      _delay_ms(1);
   }
}

uint16_t tone_array[17] = {0,1046,1174,1318,1396,1567,1760,1864,1975,2093,2349, 4435, 3951, 3322, 2960, 988, 1109 }; 

//------------------------------------Direction----------------------------------------
void Forward(uint8_t speed);
void Backward(uint8_t speed);
void Turn_left(uint8_t speed);
void Turn_right(uint8_t speed); 

//------------------------------------Buzzer--------------------------------------------
void BuzzerN();
void BuzzerS();//buzzer when first moving forward
void BuzzerL();//buzzer when left sensor sense something
void BuzzerR();//buzzer when right sensor sense something
void BuzzerB();//buzzer when both sensor sense comething

//-----------------------------------Interrupt-----------------------------------------
ISR(TIMER3_OVF_vect) 
{
    PORTB =0b00001000;
    PORTD =0b00000100;
    _delay_ms(250);
     TCNT3 = 0xffff - 7812; // Every 1 second
} 

//-------------------------------------Main--------------------------------------------
int main()
{
   DDRB = 0b10101100; //PB7, PB3, PB5: OUTPUT
   DDRD = 0b00000111; //PD1, PD0 : OUTPUT
   DDRF = 0b11111100;
   
   PORTF=0b00000011; 
   
   TCCR0A = 0b11110001; // PWM, Phase and Frequency Correct
   TCCR0B = 0b00000100; // Prescaler: 256

   TCCR1A = 0b10000000; // PWM, OC1A On, Phase and Frequency Correct 
   TCCR1B = 0b00010010; //prescaler 8   
   
   TCCR3A = 0b00000000; // Normal
   TCCR3B = 0b00000101; //prescaler 1024
   
   TIMSK3 = 0b00000001;
   
   sei();
   
   while(1)
   {
      if(!(PINF & (1<<0)) && !(PINF & (1<<1)))
      {
          BuzzerN();
         Forward(100);
         BuzzerS();
         TCNT3 = 0xffff-1500;
         while(1)
         {
            if(!(PINF & (1<<0)))//왼쪽 스위치가 눌렸을 때
            {
               if(!(PINF & (1<<1)))
               {
                  TCNT3 = 0xffff-9000;
                  Backward(190);
                  BuzzerB();
                  Turn_right(10);
                  delay_ms(90);
                  Forward(100);
               }
               else
               {
                  TCNT3 = 0xffff-9000;
                  Backward(190);
                  BuzzerL();
                  Turn_left(10);
                  _delay_ms(100);
               }
            } //if문   
            else if(!(PINF & (1<<1)))//오른쪽 스위치가 눌렸을 때
            {
               if(!(PINF & (1<<0)))
               {
                  TCNT3 = 0xffff-9000;
                  Backward(190);
                  BuzzerB();
                  Turn_right(10);
                  _delay_ms(90);
                  Forward(100);
               }
               else
               {
                  TCNT3 = 0xffff-13000; 
                  Backward(190); 
                  BuzzerR();  
                  Turn_right(10);
                  _delay_ms(115);
               }
            } //else if문 
            else
            {
               Forward(100);
            }
         }//while문
      }//최초 if문
   }//최초 while문
   return 0;
}

void Forward(uint8_t speed)
{
PORTB =0b00000100;
PORTD =0b00000100;
OCR0A = speed+200;
OCR0B = speed+200;
}

void Backward(uint8_t speed)
{
PORTB =0b00001000;
PORTD =0b00000010;
OCR0A = speed+30;
OCR0B = speed+30;
}

void Turn_left(uint8_t speed)
{
   PORTB = 0b00000000;
   PORTD = 0b00000010;
   OCR0A = speed;
   OCR0B = speed+50;
}

void Turn_right(uint8_t speed) 
{
   PORTB = 0b00001000;
   PORTD = 0b00000000;
   OCR0A = speed+50;
   OCR0B = speed;
}

void tone(uint8_t scale, uint16_t delay) 
{
    OC1_PERIOD = frequency_return(tone_array[scale]); //period 
   OC1A_WIDTH = frequency_return(tone_array[scale])/20; //width
    delay_ms(delay);
}

uint16_t frequency_return(uint16_t fre) // PWM Period to Frequency
{
   int8_t period_1 = 2; // period 2us
   int set_period = 0;
   int16_t return_fre = 0; 
   set_period = 1000000 / fre;
    return_fre = set_period /period_1;
    return return_fre;
}

void BuzzerN()
{
    
   int dulation = 25;

   tone(DO_1, dulation);
   tone(No, 1);
   tone(DO_1, dulation);
   tone(No, 1);

   tone(DO_3, dulation);
   //tone(No, 1);
   tone(SI_2, dulation);
   tone(No, 1);

   tone(SI_0, dulation);
   tone(No, 1);
   tone(SI_0, dulation);
   tone(No, 1);

   tone(SOL_2, dulation);
   //tone(No, 1);
   tone(PA_2, dulation);
   tone(No, 1);

   tone(DO_1, dulation*2);
   //tone(No, 1);
   tone(DO_1, dulation*2);
   //tone(No, 1);
   tone(DO_1, dulation*3);
   tone(No, 1);
}
  


void BuzzerS()//Buzzer when moving first forward
{
  int dulation = 30;
   tone(Mi, dulation);
   tone(0, 20);
}

void BuzzerL()
{
   int dulation = 30;
   tone(Mi, dulation);
   tone(0, 20);

   tone(Sol, dulation);
   tone(0 , 20);
   
   tone(Sol, dulation); 
   tone(0 , 20);

   tone(Mi, dulation); 
   tone(0, 0);

    tone(Sol, dulation+50);
   tone(0 , 20);

    tone(Ra, dulation);
   tone(0 , 20);
   
   tone(Ra, dulation);
   tone(0 , 20);
   
   tone(Sol, dulation);
   tone(0 , 20);
}

void BuzzerR()
{
   int dulation = 50;
   
   tone(Pa, dulation);
   tone(0, 5);
   
   tone(Pa, dulation);
   tone(0, 5);
   
   tone(Ra, dulation);
   tone(0, 5);

   tone(Ra, dulation);
   tone(0, 5);

   tone(Si_P, dulation+10);
   //tone(0, 30);

    tone(Ra, dulation);
    tone(0, 5);

   tone(Si_P, dulation);
   tone(0, 5);

   tone(Rae_5, dulation);
   tone(0, 5);

   tone(Do_5, dulation);
   tone(0, 5);

   tone(Si_P, dulation);
   tone(0, 10);
}

void BuzzerB()
{
   int dulation = 50;
   tone(Si, dulation);
   tone(0 , 5); 
   
   tone(Ra, dulation);
   tone(0 , 5); 

   tone(Si, dulation);
   tone(0 , 5);

   tone(Ra, dulation);
   tone(0 , 5);
}