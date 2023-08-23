// Created 23.08.2023 13:46:38

#include "aTrafficLight.h"


int iBlink = 0; // Фаза мигания
void led_init(void)
{
    pinMode(2, OUTPUT);  pinMode(3, OUTPUT);  pinMode(4, OUTPUT); // D2, D3, D4 == LED
}
void led(int iColor)
{
   if (iColor & RED) digitalWrite(2, HIGH); else digitalWrite(2, LOW);
   if (iColor & GREEN) digitalWrite(4, HIGH); else digitalWrite(4, LOW);
   if (iColor & YELLOW) digitalWrite(3, HIGH); else digitalWrite(3, LOW);
}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//   Обработка процедур в конечном автомате Светофор
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
static inline void conn_traffic(void)  //  Обработка процедуры ПЕРЕХОДА между Состояними в конечном автомате Светофор
{
 
 switch (SW_traffic.uCurState)
  {
  case 10: //  состояние Инициация 
     if (is_SW_traffic_Wait(1))  // 1 Переход по условию:  WAIT(1000)
        {
         SW_traffic.uNewState = 20; //  Перейти в новое состояние Зеленый
        }
  break;
  case 20: //  состояние Зеленый
     if (is_SW_traffic_Wait(1))  // 1 Переход по условию:  WAIT(2000)
        {
         SW_traffic.uNewState = 30; //  Перейти в новое состояние Зеленый мигающий
        }
  break;
  case 30: //  состояние Зеленый мигающий
     if (! (iBlink) )//  Перезапуск времени, если условие AFTER не соблюдено
         set_SW_traffic_WaitTime(1,400); // для AFTER(iBlink,400)
     if (! ( ! iBlink) )//  Перезапуск времени, если условие AFTER не соблюдено
         set_SW_traffic_WaitTime(2,200); // для AFTER( ! iBlink,200)

     if (is_SW_traffic_Wait(3))  // 1 Переход по условию:  WAIT(2000)
        {
         SW_traffic.uNewState = 40; //  Перейти в новое состояние Желтый
        }
     else
     if (is_SW_traffic_After(1))  // 2 Переход по условию:  AFTER(iBlink,400)
        {
         SW_traffic.uNewState = 30; //  Состояние не меняется 
         iBlink=0;  led(OFF);
         set_SW_traffic_WaitTime(1,400); //   Заново задать время для  AFTER(iBlink,400) потому что состояние не меняется 
        }
     else
     if (is_SW_traffic_After(2))  // 3 Переход по условию:  AFTER( ! iBlink,200)
        {
         SW_traffic.uNewState = 30; //  Состояние не меняется 
         iBlink=1;  led(GREEN);
         set_SW_traffic_WaitTime(2,200); //   Заново задать время для  AFTER( ! iBlink,200) потому что состояние не меняется 
        }
  break;
  case 40: //  состояние Желтый
     if (is_SW_traffic_Wait(1))  // 1 Переход по условию:  WAIT(2000)
        {
         SW_traffic.uNewState = 50; //  Перейти в новое состояние Красный
        }
  break;
  case 50: //  состояние Красный
     if (is_SW_traffic_Wait(1))  // 1 Переход по условию:  WAIT(2000)
        {
         SW_traffic.uNewState =  60; //  Перейти в новое состояние Красно-желтый
        }
  break;
  case  60: //  состояние Красно-желтый
     if (is_SW_traffic_Wait(1))  // 1 Переход по условию:  WAIT(2000)
        {
         SW_traffic.uNewState = 20; //  Перейти в новое состояние Зеленый
        }
  break;
  }
}
static inline void in_traffic(void)  //  Обработка ВХОДОВ в состояния для конечного автомата Светофор
{
  switch (SW_traffic.uNewState) //  IN Case
     {
     case 10: //  состояние Инициация 
          led_init(); 
           led(OFF);
          set_SW_traffic_WaitTime(1,1000); //   Задать время для WAIT(1000)
          set_SW_traffic_WaitCount(1,-1); //  Количество повторений неограничено для WAIT(1000)
     break;
     case 20: //  состояние Зеленый
          led(GREEN);
          set_SW_traffic_WaitTime(1,2000); //   Задать время для WAIT(2000)
          set_SW_traffic_WaitCount(1,-1); //  Количество повторений неограничено для WAIT(2000)
     break;
     case 30: //  состояние Зеленый мигающий
          iBlink = 0; 
          led(OFF);
          set_SW_traffic_WaitTime(1,400); //  Задать время для AFTER(iBlink,400)
          set_SW_traffic_WaitTime(2,200); //  Задать время для AFTER( ! iBlink,200)
          set_SW_traffic_WaitTime(3,2000); //   Задать время для WAIT(2000)
          set_SW_traffic_WaitCount(3,-1); //  Количество повторений неограничено для WAIT(2000)
     break;
     case 40: //  состояние Желтый
          led(YELLOW);
          set_SW_traffic_WaitTime(1,2000); //   Задать время для WAIT(2000)
          set_SW_traffic_WaitCount(1,-1); //  Количество повторений неограничено для WAIT(2000)
     break;
     case 50: //  состояние Красный
          led(RED);
          set_SW_traffic_WaitTime(1,2000); //   Задать время для WAIT(2000)
          set_SW_traffic_WaitCount(1,-1); //  Количество повторений неограничено для WAIT(2000)
     break;
     case  60: //  состояние Красно-желтый
          led(RED+YELLOW);
          set_SW_traffic_WaitTime(1,2000); //   Задать время для WAIT(2000)
          set_SW_traffic_WaitCount(1,-1); //  Количество повторений неограничено для WAIT(2000)
     break;
     }
}
static inline void traffic(void) //  процедури конечного автомата Светофор
{
   if ( SW_traffic.uNewState != SW_traffic.uCurState ) //   Если в ходе предыдущего шага сделан был запрос на изменение состояния конечного автомата  
      {
         in_traffic();  //  Обработка ВХОДОВ в состояния для конечного автомата Светофор

         SW_traffic.uCurState = SW_traffic.uNewState;  //  Изменить состояние конечного автомата  Светофор
      }

   conn_traffic();  //   Обработка процедуры ПЕРЕХОДА между Состояними в конечном автомате Светофор

}

SW_aTrafficLight_Timer_t SW_aTrafficLight = //  Глобальные таймеры документа
{
    0, // Clock  aTrafficLight
    0, // Start  aTrafficLight
};
SW_aTrafficLight_State_t SW_traffic; // Переменные конечного автомата Светофор

void aTrafficLight(void) //  Отработка шага вычислений для всех конечных автоматов проекта  
{
    if (!SW_aTrafficLight.uStart)  //  Проверка первого запуска конечных автоматов проекта  
    {
        aTrafficLight_init(); //  Инициализация всех конечных автоматов проекта  
        SW_aTrafficLight.uStart=1; //  Проект запущен  
    }


    traffic();   //  процедури для конечного автомата Светофор
}

static inline void aTrafficLight_init(void) //  Инициализация всех конечных автоматов проекта  
{
    SW_aTrafficLight.uClock = 0; // Встановлення початкового значення CLOCK

    SW_traffic.uNewState = 10; // Goto Base state Светофор
    SW_traffic.uCurState = 9999999; // for run in block
}
 // SW_Wait block 

static void set_SW_traffic_WaitTime(uint32_t uNumWait, uint32_t uTim_Wait) // Set time for wait
    {
        uSW_traffic_Wait_Time[uNumWait] = uTim_Wait+1; //Set SW_Wait time + 1 
    }
 
static void set_SW_traffic_WaitCount(uint32_t uNumWait, int32_t iTim_Count) // Set time for wait
    {
        iSW_traffic_Wait_Count[uNumWait] = iTim_Count; //Set SW_Count 
    }
 
static uint32_t is_SW_traffic_Wait(uint32_t uNumWait) // is time for wait clear
    {
       if ( iSW_traffic_Wait_Count[uNumWait] !=0 ) 
          {
            if ( uSW_traffic_Wait_Time[uNumWait] )  
                return 0; // no end wait
            else   
                return 1; // end wait
          }
       else 
            return 0; // no count wait
    }

static uint32_t is_SW_traffic_After(uint32_t uNumWait ) // is time for After clear && Condtion != 0 
    {
       if ( uSW_traffic_Wait_Time[uNumWait] )  
                return 0; // no end wait
       else   
                return 1; // end wait
    }

static inline void dec_SW_traffic_WaitCount(uint32_t uNumWait) // count wait decrement
    {
       if (iSW_traffic_Wait_Count[uNumWait] > 0)
              iSW_traffic_Wait_Count[uNumWait]-- ; 
    }

uint32_t uSW_traffic_Wait_Time[4]; // Wait time array

int32_t iSW_traffic_Wait_Count[4]; // Wait Count array



void aTrafficLight_Systick(void) // Dec SW_Wait
    {
       SW_aTrafficLight.uClock++; //  Инкремент значения  CLOCK
       for (int iCount = 0; iCount < 4; iCount++)
            if (uSW_traffic_Wait_Time[iCount]) (uSW_traffic_Wait_Time[iCount])--; // Dec SW_Wait time 
       
    }

void aTrafficLight_Mills(void) // Dec SW_Wait Mills
    {
     static uint32_t timer_old = 0; // mills old
     static uint32_t timer_diff = 0; // mills dif
     if (millis()==timer_old) // if add time 
         return; 
     if (millis()<timer_old) // if time overrun 
         {
         timer_old = millis(); // clear old if overrun
         return; 
         }
     timer_diff = millis() - timer_old; 
     timer_old = millis(); // set old
     for(int iTimCount = 0; iTimCount < timer_diff; iTimCount++) 
       {
          SW_aTrafficLight.uClock ++; //  Инкремент значения  CLOCK
       for (int iCount = 0; iCount < 4; iCount++)
            if (uSW_traffic_Wait_Time[iCount]) (uSW_traffic_Wait_Time[iCount])--; // Dec SW_Wait time 
       
       }
    }

