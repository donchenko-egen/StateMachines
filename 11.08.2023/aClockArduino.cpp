// Created 11.08.2023 18:18:15

#include "aClockArduino.h"





//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//   Обработка процедур в конечном автомате Автомат измерения температуры  DS18x20
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void conn_Temperature(void)  //  Обработка процедуры ПЕРЕХОДА между Состояними в конечном автомате Автомат измерения температуры  DS18x20
{
 
 switch (SW_Temperature.uCurState)
  {
  case 10: //  состояние Старт измерения DS18x20
     if (is_SW_Temperature_Wait(1))  // 1 Переход по условию:  WAIT(1000)
        {
         SW_Temperature.uNewState = 20; //  Перейти в новое состояние Измерение температуры
        }
  break;
  case 20: //  состояние Измерение температуры
     if (is_SW_Temperature_Wait(1))  // 1 Переход по условию:  WAIT(6000)
        {
         SW_Temperature.uNewState = 10; //  Перейти в новое состояние Старт измерения DS18x20
        }
  break;
  }
}
void in_Temperature(void)  //  Обработка ВХОДОВ в состояния для конечного автомата Автомат измерения температуры  DS18x20
{
  switch (SW_Temperature.uNewState) //  IN Case
     {
     case 10: //  состояние Старт измерения DS18x20
          DS18x20_start();
          set_SW_Temperature_WaitTime(1,1000); //   Задать время для WAIT(1000)
          set_SW_Temperature_WaitCount(1,-1); //  Количество повторений неограничено для WAIT(1000)
     break;
     case 20: //  состояние Измерение температуры
          DS18x20_read();
          set_SW_Temperature_WaitTime(1,6000); //   Задать время для WAIT(6000)
          set_SW_Temperature_WaitCount(1,-1); //  Количество повторений неограничено для WAIT(6000)
     break;
     }
}
void Temperature(void) //  процедури конечного автомата Автомат измерения температуры  DS18x20
{
   if ( SW_Temperature.uNewState != SW_Temperature.uCurState ) //   Если в ходе предыдущего шага сделан был запрос на изменение состояния конечного автомата  
      {
         in_Temperature();  //  Обработка ВХОДОВ в состояния для конечного автомата Автомат измерения температуры  DS18x20

         SW_Temperature.uCurState = SW_Temperature.uNewState;  //  Изменить состояние конечного автомата  Автомат измерения температуры  DS18x20
      }

   conn_Temperature();  //   Обработка процедуры ПЕРЕХОДА между Состояними в конечном автомате Автомат измерения температуры  DS18x20

}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//   Обработка процедур в конечном автомате Автомат измерения влажности
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void conn_Humanity(void)  //  Обработка процедуры ПЕРЕХОДА между Состояними в конечном автомате Автомат измерения влажности
{
 
 switch (SW_Humanity.uCurState)
  {
  case 10: //  состояние Иницизация датчика  влажности
     if (is_SW_Humanity_Wait(1))  // 1 Переход по условию:  WAIT(1000)
        {
         SW_Humanity.uNewState = 20; //  Перейти в новое состояние Цикл Измерения влажности
        }
  break;
  case 20: //  состояние Цикл Измерения влажности
     if (is_SW_Humanity_Wait(1))  // 1 Переход по условию:  WAIT(20000)
        {
         SW_Humanity.uNewState = 20; //  Состояние не меняется 
         getHumidity();
         set_SW_Humanity_WaitTime(1,20000); //  Заново задать время для  WAIT(20000) потому что состояние не меняется 
        }
  break;
  }
}
void in_Humanity(void)  //  Обработка ВХОДОВ в состояния для конечного автомата Автомат измерения влажности
{
  switch (SW_Humanity.uNewState) //  IN Case
     {
     case 10: //  состояние Иницизация датчика  влажности
          initHumidity();
          set_SW_Humanity_WaitTime(1,1000); //   Задать время для WAIT(1000)
          set_SW_Humanity_WaitCount(1,-1); //  Количество повторений неограничено для WAIT(1000)
     break;
     case 20: //  состояние Цикл Измерения влажности
          
          set_SW_Humanity_WaitTime(1,20000); //   Задать время для WAIT(20000)
          set_SW_Humanity_WaitCount(1,-1); //  Количество повторений неограничено для WAIT(20000)
     break;
     }
}
void Humanity(void) //  процедури конечного автомата Автомат измерения влажности
{
   if ( SW_Humanity.uNewState != SW_Humanity.uCurState ) //   Если в ходе предыдущего шага сделан был запрос на изменение состояния конечного автомата  
      {
         in_Humanity();  //  Обработка ВХОДОВ в состояния для конечного автомата Автомат измерения влажности

         SW_Humanity.uCurState = SW_Humanity.uNewState;  //  Изменить состояние конечного автомата  Автомат измерения влажности
      }

   conn_Humanity();  //   Обработка процедуры ПЕРЕХОДА между Состояними в конечном автомате Автомат измерения влажности

}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//   Обработка процедур в конечном автомате Автомат вывода на дисплей и светодиодную матрицу
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void conn_Display(void)  //  Обработка процедуры ПЕРЕХОДА между Состояними в конечном автомате Автомат вывода на дисплей и светодиодную матрицу
{
 
 switch (SW_Display.uCurState)
  {
  case 10: //  состояние Инициализация дисплея
     if (is_SW_Display_Wait(1))  // 1 Переход по условию:  WAIT(1000)
        {
         SW_Display.uNewState = 20; //  Перейти в новое состояние Цикл вывода на дисплей и матрицу
        }
  break;
  case 20: //  состояние Цикл вывода на дисплей и матрицу
     if (is_SW_Display_Wait(1))  // 1 Переход по условию:  WAIT(1000)
        {
         SW_Display.uNewState = 20; //  Состояние не меняется 
         Arduino_GFX_Display();
          WS2812_show_Time();
         set_SW_Display_WaitTime(1,1000); //  Заново задать время для  WAIT(1000) потому что состояние не меняется 
        }
  break;
  }
}
void in_Display(void)  //  Обработка ВХОДОВ в состояния для конечного автомата Автомат вывода на дисплей и светодиодную матрицу
{
  switch (SW_Display.uNewState) //  IN Case
     {
     case 10: //  состояние Инициализация дисплея
          Arduino_GFX_Display();
          set_SW_Display_WaitTime(1,1000); //   Задать время для WAIT(1000)
          set_SW_Display_WaitCount(1,-1); //  Количество повторений неограничено для WAIT(1000)
     break;
     case 20: //  состояние Цикл вывода на дисплей и матрицу
          
          set_SW_Display_WaitTime(1,1000); //   Задать время для WAIT(1000)
          set_SW_Display_WaitCount(1,-1); //  Количество повторений неограничено для WAIT(1000)
     break;
     }
}
void Display(void) //  процедури конечного автомата Автомат вывода на дисплей и светодиодную матрицу
{
   if ( SW_Display.uNewState != SW_Display.uCurState ) //   Если в ходе предыдущего шага сделан был запрос на изменение состояния конечного автомата  
      {
         in_Display();  //  Обработка ВХОДОВ в состояния для конечного автомата Автомат вывода на дисплей и светодиодную матрицу

         SW_Display.uCurState = SW_Display.uNewState;  //  Изменить состояние конечного автомата  Автомат вывода на дисплей и светодиодную матрицу
      }

   conn_Display();  //   Обработка процедуры ПЕРЕХОДА между Состояними в конечном автомате Автомат вывода на дисплей и светодиодную матрицу

}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//   Обработка процедур в конечном автомате Измерение температуры при помощи АЦП
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void conn_ADC(void)  //  Обработка процедуры ПЕРЕХОДА между Состояними в конечном автомате Измерение температуры при помощи АЦП
{
 
 switch (SW_ADC.uCurState)
  {
  case 10: //  состояние Инициализация АЦП
     if (is_SW_ADC_Wait(1))  // 1 Переход по условию:  WAIT(1000)
        {
         SW_ADC.uNewState = 20; //  Перейти в новое состояние Запуск канала 1
        }
  break;
  case 20: //  состояние Запуск канала 1
     if (is_SW_ADC_Wait(1))  // 1 Переход по условию:  WAIT(90)
        {
         SW_ADC.uNewState = 30; //  Перейти в новое состояние Измерение канала 1
        }
  break;
  case 30: //  состояние Измерение канала 1
     if (is_SW_ADC_Wait(1))  // 1 Переход по условию:  WAIT(10)
        {
         SW_ADC.uNewState = 40; //  Перейти в новое состояние Запуск канала 2
        }
  break;
  case 40: //  состояние Запуск канала 2
     if (is_SW_ADC_Wait(1))  // 1 Переход по условию:  WAIT(90)
        {
         SW_ADC.uNewState = 50; //  Перейти в новое состояние Измерение канала 2
        }
  break;
  case 50: //  состояние Измерение канала 2
     if (is_SW_ADC_Wait(1))  // 1 Переход по условию:  WAIT(10)
        {
         SW_ADC.uNewState = 20; //  Перейти в новое состояние Запуск канала 1
        }
  break;
  }
}
void in_ADC(void)  //  Обработка ВХОДОВ в состояния для конечного автомата Измерение температуры при помощи АЦП
{
  switch (SW_ADC.uNewState) //  IN Case
     {
     case 10: //  состояние Инициализация АЦП
            ADC_setup();
          set_SW_ADC_WaitTime(1,1000); //   Задать время для WAIT(1000)
          set_SW_ADC_WaitCount(1,-1); //  Количество повторений неограничено для WAIT(1000)
     break;
     case 20: //  состояние Запуск канала 1
          ADC_start1();
          set_SW_ADC_WaitTime(1,90); //   Задать время для WAIT(90)
          set_SW_ADC_WaitCount(1,-1); //  Количество повторений неограничено для WAIT(90)
     break;
     case 30: //  состояние Измерение канала 1
          ADC_read1();
          set_SW_ADC_WaitTime(1,10); //   Задать время для WAIT(10)
          set_SW_ADC_WaitCount(1,-1); //  Количество повторений неограничено для WAIT(10)
     break;
     case 40: //  состояние Запуск канала 2
          ADC_start1();
          set_SW_ADC_WaitTime(1,90); //   Задать время для WAIT(90)
          set_SW_ADC_WaitCount(1,-1); //  Количество повторений неограничено для WAIT(90)
     break;
     case 50: //  состояние Измерение канала 2
          ADC_read2();
          set_SW_ADC_WaitTime(1,10); //   Задать время для WAIT(10)
          set_SW_ADC_WaitCount(1,-1); //  Количество повторений неограничено для WAIT(10)
     break;
     }
}
void ADC(void) //  процедури конечного автомата Измерение температуры при помощи АЦП
{
   if ( SW_ADC.uNewState != SW_ADC.uCurState ) //   Если в ходе предыдущего шага сделан был запрос на изменение состояния конечного автомата  
      {
         in_ADC();  //  Обработка ВХОДОВ в состояния для конечного автомата Измерение температуры при помощи АЦП

         SW_ADC.uCurState = SW_ADC.uNewState;  //  Изменить состояние конечного автомата  Измерение температуры при помощи АЦП
      }

   conn_ADC();  //   Обработка процедуры ПЕРЕХОДА между Состояними в конечном автомате Измерение температуры при помощи АЦП

}

SW_aClockArduino_Timer_t SW_aClockArduino = //  Глобальные таймеры документа
{
    0, // Clock  aClockArduino
    0, // Start  aClockArduino
};
SW_aClockArduino_State_t SW_Temperature; // Переменные конечного автомата Автомат измерения температуры  DS18x20
SW_aClockArduino_State_t SW_Humanity; // Переменные конечного автомата Автомат измерения влажности
SW_aClockArduino_State_t SW_Display; // Переменные конечного автомата Автомат вывода на дисплей и светодиодную матрицу
SW_aClockArduino_State_t SW_ADC; // Переменные конечного автомата Измерение температуры при помощи АЦП

void aClockArduino(void) //  Отработка шага вычислений для всех конечных автоматов проекта  
{
    if (!SW_aClockArduino.uStart)  //  Проверка первого запуска конечных автоматов проекта  
    {
        aClockArduino_init(); //  Инициализация всех конечных автоматов проекта  
        SW_aClockArduino.uStart=1; //  Проект запущен  
    }


    Temperature();   //  процедури для конечного автомата Автомат измерения температуры  DS18x20


    Humanity();   //  процедури для конечного автомата Автомат измерения влажности


    Display();   //  процедури для конечного автомата Автомат вывода на дисплей и светодиодную матрицу


    ADC();   //  процедури для конечного автомата Измерение температуры при помощи АЦП
}

void aClockArduino_init(void) //  Инициализация всех конечных автоматов проекта  
{
    SW_aClockArduino.uClock = 0; // Встановлення початкового значення CLOCK

    SW_Temperature.uNewState = 10; // Goto Base state Автомат измерения температуры  DS18x20
    SW_Temperature.uCurState = 9999999; // for run in block
    SW_Humanity.uNewState = 10; // Goto Base state Автомат измерения влажности
    SW_Humanity.uCurState = 9999999; // for run in block
    SW_Display.uNewState = 10; // Goto Base state Автомат вывода на дисплей и светодиодную матрицу
    SW_Display.uCurState = 9999999; // for run in block
    SW_ADC.uNewState = 10; // Goto Base state Измерение температуры при помощи АЦП
    SW_ADC.uCurState = 9999999; // for run in block
}
 // SW_Wait block 

void set_SW_Temperature_WaitTime(uint32_t uNumWait, uint32_t uTim_Wait) // Set time for wait
    {
        uSW_Temperature_Wait_Time[uNumWait] = uTim_Wait+1; //Set SW_Wait time + 1 
    }
 
void set_SW_Temperature_WaitCount(uint32_t uNumWait, int32_t iTim_Count) // Set time for wait
    {
        iSW_Temperature_Wait_Count[uNumWait] = iTim_Count; //Set SW_Count 
    }
 
uint32_t is_SW_Temperature_Wait(uint32_t uNumWait) // is time for wait clear
    {
       if ( iSW_Temperature_Wait_Count[uNumWait] !=0 ) 
          {
            if ( uSW_Temperature_Wait_Time[uNumWait] )  
                return 0; // no end wait
            else   
                return 1; // end wait
          }
       else 
            return 0; // no count wait
    }

uint32_t is_SW_Temperature_After(uint32_t uNumWait ) // is time for After clear && Condtion != 0 
    {
       if ( uSW_Temperature_Wait_Time[uNumWait] )  
                return 0; // no end wait
       else   
                return 1; // end wait
    }

void dec_SW_Temperature_WaitCount(uint32_t uNumWait) // count wait decrement
    {
       if (iSW_Temperature_Wait_Count[uNumWait] > 0)
              iSW_Temperature_Wait_Count[uNumWait]-- ; 
    }

uint32_t uSW_Temperature_Wait_Time[2]; // Wait time array

int32_t iSW_Temperature_Wait_Count[2]; // Wait Count array

 // SW_Wait block 

void set_SW_Humanity_WaitTime(uint32_t uNumWait, uint32_t uTim_Wait) // Set time for wait
    {
        uSW_Humanity_Wait_Time[uNumWait] = uTim_Wait+1; //Set SW_Wait time + 1 
    }
 
void set_SW_Humanity_WaitCount(uint32_t uNumWait, int32_t iTim_Count) // Set time for wait
    {
        iSW_Humanity_Wait_Count[uNumWait] = iTim_Count; //Set SW_Count 
    }
 
uint32_t is_SW_Humanity_Wait(uint32_t uNumWait) // is time for wait clear
    {
       if ( iSW_Humanity_Wait_Count[uNumWait] !=0 ) 
          {
            if ( uSW_Humanity_Wait_Time[uNumWait] )  
                return 0; // no end wait
            else   
                return 1; // end wait
          }
       else 
            return 0; // no count wait
    }

uint32_t is_SW_Humanity_After(uint32_t uNumWait ) // is time for After clear && Condtion != 0 
    {
       if ( uSW_Humanity_Wait_Time[uNumWait] )  
                return 0; // no end wait
       else   
                return 1; // end wait
    }

void dec_SW_Humanity_WaitCount(uint32_t uNumWait) // count wait decrement
    {
       if (iSW_Humanity_Wait_Count[uNumWait] > 0)
              iSW_Humanity_Wait_Count[uNumWait]-- ; 
    }

uint32_t uSW_Humanity_Wait_Time[2]; // Wait time array

int32_t iSW_Humanity_Wait_Count[2]; // Wait Count array

 // SW_Wait block 

void set_SW_Display_WaitTime(uint32_t uNumWait, uint32_t uTim_Wait) // Set time for wait
    {
        uSW_Display_Wait_Time[uNumWait] = uTim_Wait+1; //Set SW_Wait time + 1 
    }
 
void set_SW_Display_WaitCount(uint32_t uNumWait, int32_t iTim_Count) // Set time for wait
    {
        iSW_Display_Wait_Count[uNumWait] = iTim_Count; //Set SW_Count 
    }
 
uint32_t is_SW_Display_Wait(uint32_t uNumWait) // is time for wait clear
    {
       if ( iSW_Display_Wait_Count[uNumWait] !=0 ) 
          {
            if ( uSW_Display_Wait_Time[uNumWait] )  
                return 0; // no end wait
            else   
                return 1; // end wait
          }
       else 
            return 0; // no count wait
    }

uint32_t is_SW_Display_After(uint32_t uNumWait ) // is time for After clear && Condtion != 0 
    {
       if ( uSW_Display_Wait_Time[uNumWait] )  
                return 0; // no end wait
       else   
                return 1; // end wait
    }

void dec_SW_Display_WaitCount(uint32_t uNumWait) // count wait decrement
    {
       if (iSW_Display_Wait_Count[uNumWait] > 0)
              iSW_Display_Wait_Count[uNumWait]-- ; 
    }

uint32_t uSW_Display_Wait_Time[2]; // Wait time array

int32_t iSW_Display_Wait_Count[2]; // Wait Count array

 // SW_Wait block 

void set_SW_ADC_WaitTime(uint32_t uNumWait, uint32_t uTim_Wait) // Set time for wait
    {
        uSW_ADC_Wait_Time[uNumWait] = uTim_Wait+1; //Set SW_Wait time + 1 
    }
 
void set_SW_ADC_WaitCount(uint32_t uNumWait, int32_t iTim_Count) // Set time for wait
    {
        iSW_ADC_Wait_Count[uNumWait] = iTim_Count; //Set SW_Count 
    }
 
uint32_t is_SW_ADC_Wait(uint32_t uNumWait) // is time for wait clear
    {
       if ( iSW_ADC_Wait_Count[uNumWait] !=0 ) 
          {
            if ( uSW_ADC_Wait_Time[uNumWait] )  
                return 0; // no end wait
            else   
                return 1; // end wait
          }
       else 
            return 0; // no count wait
    }

uint32_t is_SW_ADC_After(uint32_t uNumWait ) // is time for After clear && Condtion != 0 
    {
       if ( uSW_ADC_Wait_Time[uNumWait] )  
                return 0; // no end wait
       else   
                return 1; // end wait
    }

void dec_SW_ADC_WaitCount(uint32_t uNumWait) // count wait decrement
    {
       if (iSW_ADC_Wait_Count[uNumWait] > 0)
              iSW_ADC_Wait_Count[uNumWait]-- ; 
    }

uint32_t uSW_ADC_Wait_Time[2]; // Wait time array

int32_t iSW_ADC_Wait_Count[2]; // Wait Count array



void aClockArduino_Systick(void) // Dec SW_Wait
    {
       SW_aClockArduino.uClock++; //  Инкремент значения  CLOCK
       for (int iCount = 0; iCount < 2; iCount++)
            if (uSW_Temperature_Wait_Time[iCount]) (uSW_Temperature_Wait_Time[iCount])--; // Dec SW_Wait time 
       
       for (int iCount = 0; iCount < 2; iCount++)
            if (uSW_Humanity_Wait_Time[iCount]) (uSW_Humanity_Wait_Time[iCount])--; // Dec SW_Wait time 
       
       for (int iCount = 0; iCount < 2; iCount++)
            if (uSW_Display_Wait_Time[iCount]) (uSW_Display_Wait_Time[iCount])--; // Dec SW_Wait time 
       
       for (int iCount = 0; iCount < 2; iCount++)
            if (uSW_ADC_Wait_Time[iCount]) (uSW_ADC_Wait_Time[iCount])--; // Dec SW_Wait time 
       
    }

void aClockArduino_Mills(void) // Dec SW_Wait Mills
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
          SW_aClockArduino.uClock ++; //  Инкремент значения  CLOCK
       for (int iCount = 0; iCount < 2; iCount++)
            if (uSW_Temperature_Wait_Time[iCount]) (uSW_Temperature_Wait_Time[iCount])--; // Dec SW_Wait time 
       
       for (int iCount = 0; iCount < 2; iCount++)
            if (uSW_Humanity_Wait_Time[iCount]) (uSW_Humanity_Wait_Time[iCount])--; // Dec SW_Wait time 
       
       for (int iCount = 0; iCount < 2; iCount++)
            if (uSW_Display_Wait_Time[iCount]) (uSW_Display_Wait_Time[iCount])--; // Dec SW_Wait time 
       
       for (int iCount = 0; iCount < 2; iCount++)
            if (uSW_ADC_Wait_Time[iCount]) (uSW_ADC_Wait_Time[iCount])--; // Dec SW_Wait time 
       
       }
    }

