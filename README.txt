# AEP_SchedulerWindowLifter

Window Lifter with Binary Progression Scheduler and State Machines at Continental

AEP 2017

Lastest Release: 2017/11/25


Authors: Habib Alejandro Apez González

       	 Estefania López Villagómez



Contact: habibapez@hotmail.com

         elovillagomez@gmail.com
      

Location: Querétaro, México.


The Scheduler uses the Binary Progression Algorithm to determine the execution of the tasks.

1. The scheduler was implemented in the S32K144EVB.
2. This project was compiled in IAR.
3. The code was developed following the AUTOSAR Software Architecture: MCAL, HAL, SERVICES and APP Layers were defined.
4. To implement the Scheduler’s Tick, the SysTick Interruption of the microcontroller was used. The Scheduler has a 781.25us Tick.
5. All code files of the project are attached as well as the Scheduler Design document.


Content:
*Documentation
	** Design: Contains the Scheduler Design.
      	** Report: Contains the Scheduler Report.
      	** Requirements: Contains the files with requirements of the project.
*lib
   	** APP: Contains the application file (main.c).
 	** Common: Contains the file with definition of the data types used.
   	** HAL: Contains the Hardware Abstraction Layer modules.
    	** MCAL: Contains the Microcontroller Abstraction Layer modules.
     	** SERVICES: Contains the Service Layer modules.
*projects
   	** WindowLifterScheduler: Contains the project settings of IAR.  
      	** settings: Contains the workspace settings of IAR.  
