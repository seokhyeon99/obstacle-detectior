# obstacle-detector
    * it is the program that can make car to avoid obstacles.
    * car has two sensors on the forward-left and forward-right.
    * if they get pressed, car goes backward and changes direction.  
   ![obstacle detection car](/detection_car.jpg)

## AVR studio 4
  * 'AVR studio' is an IDE(Intergrated Development Environment) provided free of charge by ATMEL, which develops and produces AVR micro controller.
     * Assembler: execution code generation program that generates executable files by assembling code written in assembly language
     * Editor: editor that write assembly code or C code by editing various codes or documents
     * Debugger: tools for diagnosing and correcting logical errors in code written by users
     * Downloader: program that allows users to execute the user-generated execution code by sending it to the target board

  ![AVR studio 4 logo](/avr_studio4.png)
  
## GPIO
   * GPIO which is General Purpose Input & Output is digital signal pin of intergrated circuit or electric circuit board. GPIO has three I/O registers(DDRx, PORTx, PINx) and can choose input and output freely.  
   
   Register | Work  
   --------- | --------  
   DDRx | set input of output (1: output, 0: input)  
   PORTx | when output, set out voltage (1: voltage, 0: GND)  
   PINx | when input, it changes register from external voltage  

## Interrupt
   * When we need to deal with exception, Interrupt makes the CPU notified.  
   If a particular event occurs during the CPU's operation, it immediately stops its running and tackle the event.  
