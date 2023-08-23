// Created 23.08.2023 13:46:38

#ifndef FSA_aTrafficLight_H
#define FSA_aTrafficLight_H

#define OFF	0
#define RED	1
#define GREEN	2
#define YELLOW	4
#include <arduino.h>
typedef struct  {
  volatile uint32_t uNewState;
  volatile uint32_t uOldState;
  volatile uint32_t uIsBackReturn; // Flag Return BACK
  volatile uint32_t uCallState;
  volatile uint32_t uIsCallReturn; // Flag Return Call
  volatile uint32_t uCurState;
  volatile int32_t  iCounter; // COUNT
} SW_aTrafficLight_State_t;

extern SW_aTrafficLight_State_t SW_traffic; // Переменные конечного автомата Светофор

typedef struct  {
  volatile uint32_t uClock; // Clock aTrafficLight
  volatile uint32_t uStart; // Start Project aTrafficLight
} SW_aTrafficLight_Timer_t;

extern SW_aTrafficLight_Timer_t SW_aTrafficLight; // Timer Var

extern uint32_t uSW_traffic_Wait_Time[]; // Wait time
extern int32_t iSW_traffic_Wait_Count[]; // Wait count

static void set_SW_traffic_WaitTime(uint32_t uNumWait, uint32_t uTim_Wait); // Set time for wait
static void set_SW_traffic_WaitCount(uint32_t uNumWait, int32_t iTim_Count); // Set Count for wait
static uint32_t is_SW_traffic_Wait(uint32_t uNumWait); // is time for wait clear
static uint32_t is_SW_traffic_After(uint32_t uNumWait); // is time for After clear 
static inline void dec_SW_traffic_WaitCount(uint32_t uNumWait); // count wait decrement

static inline void traffic(void); //  for run one traffic if need (parexamle in systick)

void aTrafficLight(void); // Run All automate aTrafficLight

static inline void aTrafficLight_init(void); //Init All automate aTrafficLight

void aTrafficLight_Mills(); //  Step Timers

void aTrafficLight_Systick(void); // For run all Wait in Systick
#endif
