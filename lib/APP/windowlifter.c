/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: windowlifter.c $
 * $Revision: version 4 $
 * $Author: Habib Apez $
 * $Date: 2017-11-08 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \windowlifter.c
    Source of windowlifter application. Located at APP.
*/
/*============================================================================*/
/* COPYRIGHT (C) CONTINENTAL AUTOMOTIVE 2014                                  */
/* AUTOMOTIVE GROUP, Interior Division, Body and Security                     */
/* ALL RIGHTS RESERVED                                                        */
/*                                                                            */
/* The reproduction, transmission, or use of this document or its content is  */
/* not permitted without express written authority. Offenders will be liable  */
/* for damages.                                                               */
/* All rights, including rights created by patent grant or registration of a  */
/* utility model or design, are reserved.                                     */
/*                                                                            */
/*============================================================================*/
/*============================================================================*/
/*                    REUSE HISTORY - taken over from                         */
/*============================================================================*/
/*  Author             |        Version     | FILE VERSION (AND INSTANCE)     */
/*----------------------------------------------------------------------------*/
/* Habib Apez          |          1         |   Initial version               */
/* Habib Apez          |          2         |   Naming conventions            */
/*                     |                    |   and MISRA checked             */
/* Habib Apez          |          3         |   New function to mange the     */
/*                     |                    |   10 segment led bar included   */
/* Habib Apez          |          4         |   Function descriptions added   */
/*                                              and uses delays module        */ 
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: windowlifter.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "windowlifter.h"

/* Constants and types  */
/*============================================================================*/
#define TOP 10
#define BOTTON 0   
    
/* Variables */
/*============================================================================*/
T_UBYTE lub_UpFlag, lub_DownFlag, lub_AntipinchFlag, lub_Level = 0;

/* Private functions prototypes */
/*============================================================================*/
void windowlifter_UpNormal(void);
void windowlifter_DownNormal(void);
void windowlifter_OneTouchUp(void);
void windowlifter_OneTouchDown(void);
void windowlifter_Antipinch(void);

/* Inline functions */
/*============================================================================*/

/* Private functions */
/*============================================================================*/
/**************************************************************
 *  Name                 : windowlifter_UpNormal
 *  Description          : Moves the Window upwards
 *  Parameters           : [void]
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void windowlifter_UpNormal(void){
  if(button_DebounceButtonAntipinch()){
    windowlifter_Antipinch();
  }
  else {
    if(lub_Level<TOP){
      leds_TurnOnUpLED();
      lub_Level++;
      delays_Wait400ms();
      segmentbar_SetLevelBar(lub_Level, lub_UpFlag, lub_DownFlag);
      leds_TurnOffUpLED();
    }
  }
}

/**************************************************************
 *  Name                 : windowlifter_DownNormal
 *  Description          : Moves the Window downwards
 *  Parameters           : [void]
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void windowlifter_DownNormal(void){
  if(lub_Level>BOTTON){
    leds_TurnOnDownLED();
    lub_Level--;
    delays_Wait400ms();
    segmentbar_SetLevelBar(lub_Level, lub_UpFlag, lub_DownFlag);
    leds_TurnOffDownLED();
  }
}

/**************************************************************
 *  Name                 : windowlifter_OneTouchUp
 *  Description          : Moves the Window upwards until it is totally closed
 *  Parameters           : [void]
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void windowlifter_OneTouchUp(void){
  while(lub_Level<TOP & lub_UpFlag){
    if(button_DebounceButtonDown())
      lub_UpFlag = 0;
    if(lub_UpFlag)
      windowlifter_UpNormal(); //Verify if it comes from a onetouch
  }
}

/**************************************************************
 *  Name                 : windowlifter_OneTouchDown
 *  Description          : Moves the Window downwards until it is totally opened
 *  Parameters           : [void]
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void windowlifter_OneTouchDown(void){

  while(lub_Level>BOTTON & lub_DownFlag){ 
    if(button_DebounceButtonUp() && (lub_AntipinchFlag == 0))
      lub_DownFlag = 0;
    if(lub_DownFlag)
    windowlifter_DownNormal();       
  }
}

/**************************************************************
 *  Name                 : windowlifter_Antipinch
 *  Description          : Moves the Window downwards until it is totally opened,
                          then ignores any signal during 5s
 *  Parameters           : [void]
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void windowlifter_Antipinch(void){
  lub_AntipinchFlag = 1;
  leds_TurnOffUpLED();
  lub_UpFlag = 0;
  lub_DownFlag = 1;
  leds_TurnOnAntipinchLED();          
  windowlifter_OneTouchDown();
  delays_Wait5s();
  leds_TurnOffAntipinchLED();  
  lub_AntipinchFlag = 0;
}


/* Exported functions */
/*============================================================================*/
/**************************************************************
 *  Name                 : main
 *  Description          : Implements the windowlifter application
 *  Parameters           : [void]
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void main(void)              
{
    clock_InitClock();
    button_InitButtons();
    leds_InitLeds();
    segmentbar_InitBar();
    delays_InitTimer();
    
    for(;;){
        
      start:
        if(button_DebounceButtonUp()){
          lub_UpFlag = 1;
          delays_Wait490ms();
          if(button_CheckButtonUp()){
            Up_normal:
              lub_UpFlag = 1;
              windowlifter_UpNormal();
              if(button_CheckButtonUp()){
                lub_UpFlag = 0;
                goto Up_normal;
              }
              else {
                lub_UpFlag = 0;
                goto start;
              }
          }
          else{
            windowlifter_OneTouchUp();
            if(lub_UpFlag==0)
              delays_Wait400ms();
            lub_UpFlag = 0;
            goto start;
          }
        }
        else {
          if(button_DebounceButtonDown()){
            lub_DownFlag = 1;
            delays_Wait490ms();
            if(button_CheckButtonDown()){
              Down_normal:
                lub_DownFlag = 1;
                windowlifter_DownNormal();
                if(button_CheckButtonDown()){
                  lub_DownFlag = 0;
                  goto Down_normal;
                }
                else {
                  lub_DownFlag = 0;
                  goto start;
                }
              }
              else {
                windowlifter_OneTouchDown();
                if(lub_DownFlag==0)
                  delays_Wait400ms();
                lub_DownFlag = 0;
                goto start;
              }
            }
          else {
              goto start;
          }
        }
    }
}
 /* Notice: the file ends with a blank new line to avoid compiler warnings */
