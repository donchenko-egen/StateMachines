// Created 11.08.2023 18:18:15

#ifndef FSA_aClockArduino_H
#define FSA_aClockArduino_H

#include <Data.h>
void DS18x20_start(void);
void DS18x20_read(void);
void Arduino_GFX_Display();
void WS2812_show_Time(void);
bool initHumidity();
bool getHumidity();
void  ADC_setup();
void ADC_read1();
void ADC_read2();
void ADC_start1();
void ADC_start2();

typedef struct  {
  volatile uint32_t uNewState;
  volatile uint32_t uOldState;
  volatile uint32_t uIsBackReturn; // Flag Return BACK
  volatile uint32_t uCallState;
  volatile uint32_t uIsCallReturn; // Flag Return Call
  volatile uint32_t uCurState;
  volatile int32_t  iCounter; // COUNT
} SW_aClockArduino_State_t;

extern SW_aClockArduino_State_t SW_Temperature; // Переменные конечного автомата Автомат измерения температуры  DS18x20
extern SW_aClockArduino_State_t SW_Humanity; // Переменные конечного автомата Автомат измерения влажности
extern SW_aClockArduino_State_t SW_Display; // Переменные конечного автомата Автомат вывода на дисплей и светодиодную матрицу
extern SW_aClockArduino_State_t SW_ADC; // Переменные конечного автомата Измерение температуры при помощи АЦП

typedef struct  {
  volatile uint32_t uClock; // Clock aClockArduino
  volatile uint32_t uStart; // Start Project aClockArduino
} SW_aClockArduino_Timer_t;

extern SW_aClockArduino_Timer_t SW_aClockArduino; // Timer Var

extern uint32_t uSW_Temperature_Wait_Time[]; // Wait time
extern int32_t iSW_Temperature_Wait_Count[]; // Wait count

void set_SW_Temperature_WaitTime(uint32_t uNumWait, uint32_t uTim_Wait); // Set time for wait
void set_SW_Temperature_WaitCount(uint32_t uNumWait, int32_t iTim_Count); // Set Count for wait
uint32_t is_SW_Temperature_Wait(uint32_t uNumWait); // is time for wait clear
uint32_t is_SW_Temperature_After(uint32_t uNumWait); // is time for After clear 
void dec_SW_Temperature_WaitCount(uint32_t uNumWait); // count wait decrement

void Temperature(void); //  for run one Temperature if need (parexamle in systick)

extern uint32_t uSW_Humanity_Wait_Time[]; // Wait time
extern int32_t iSW_Humanity_Wait_Count[]; // Wait count

void set_SW_Humanity_WaitTime(uint32_t uNumWait, uint32_t uTim_Wait); // Set time for wait
void set_SW_Humanity_WaitCount(uint32_t uNumWait, int32_t iTim_Count); // Set Count for wait
uint32_t is_SW_Humanity_Wait(uint32_t uNumWait); // is time for wait clear
uint32_t is_SW_Humanity_After(uint32_t uNumWait); // is time for After clear 
void dec_SW_Humanity_WaitCount(uint32_t uNumWait); // count wait decrement

void Humanity(void); //  for run one Humanity if need (parexamle in systick)

extern uint32_t uSW_Display_Wait_Time[]; // Wait time
extern int32_t iSW_Display_Wait_Count[]; // Wait count

void set_SW_Display_WaitTime(uint32_t uNumWait, uint32_t uTim_Wait); // Set time for wait
void set_SW_Display_WaitCount(uint32_t uNumWait, int32_t iTim_Count); // Set Count for wait
uint32_t is_SW_Display_Wait(uint32_t uNumWait); // is time for wait clear
uint32_t is_SW_Display_After(uint32_t uNumWait); // is time for After clear 
void dec_SW_Display_WaitCount(uint32_t uNumWait); // count wait decrement

void Display(void); //  for run one Display if need (parexamle in systick)

extern uint32_t uSW_ADC_Wait_Time[]; // Wait time
extern int32_t iSW_ADC_Wait_Count[]; // Wait count

void set_SW_ADC_WaitTime(uint32_t uNumWait, uint32_t uTim_Wait); // Set time for wait
void set_SW_ADC_WaitCount(uint32_t uNumWait, int32_t iTim_Count); // Set Count for wait
uint32_t is_SW_ADC_Wait(uint32_t uNumWait); // is time for wait clear
uint32_t is_SW_ADC_After(uint32_t uNumWait); // is time for After clear 
void dec_SW_ADC_WaitCount(uint32_t uNumWait); // count wait decrement

void ADC(void); //  for run one ADC if need (parexamle in systick)

void aClockArduino(void); // Run All automate aClockArduino

void aClockArduino_init(void); //Init All automate aClockArduino

void aClockArduino_Mills(); //  Step Timers

void aClockArduino_Systick(void); // For run all Wait in Systick
#endif
