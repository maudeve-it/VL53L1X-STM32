_**Piu' sotto, al termine della lingua inglese trovi il testo in italiano. </i>**_
_**<br>Below the English text you'll find the Italian version</i>**_
<br>

# Using VL53L1X through STM ULD API driver


<br>
Here is an implementations of the interfacing funtions required by ULD driver.<br>
As indicated on my video about this set of functions, to use VL53L1X you just need to:<br>

## on CubeMX
-	create a project (I use CubeIDE)<br>
-	enable an I2C port, in standard mode or fast mode, to connect TOF sensor<br>
-	(optional) enable an input GPIO pin connecting the GPIO pin of VL53L1X (INT pin on some breakout boards)<br>
-	(optional) enable an output GPIO pin connecting the XSHUT pin of VL53L1X (SHUT pin on some breakout boards)<br>
<br>
If not connected to the uC, XHUT pin of VL52L1x must be connected to VCC-<br>
<br>
Save the project<br>
<br>

## on CubeIDE
- download from ST website the ULD driver for VL53L1X and
  -  from the  API/core folder of the downloaded package copy <b>VL53L1X_api.c</b> into the project source folder
  -  from the  API/core folder of the downloaded package copy <b>VL53L1X_api.h</b> into the project header folder
-	copy from this repository file "vl53l1_platform.h" and put it in the headers folder<br>
-	copy from this repository file "vl53l1_platform.c" and put it in the headers folder<br>
- edit main.h file adding the libraries include, this way: 
<br>

```sh
(main.h)
...
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "vl53l1_platform.h"
#include "VL53L1X_api.h"
/* USER CODE END Includes */
...
```
<br>
Now you can enable VL53L1X and start ranging from main.<br>
This way:<br>
-  initialize the device in USER CODE BEGIN 2:<br>

```sh
(main.c)
...
  /* USER CODE BEGIN 2 */

  if (VL53L1__Init())
	  while (1) {};

  /* USER CODE END 2 */
...
```
<br>
-  start ranging in "USER CODE BEGIN WHILE":

```sh
(main.c)
...
  /* USER CODE BEGIN WHILE */

  VL53L1X_StartRanging (TOF_ADDR);
...
```
<br>
-  then proceeding getting renging values:

```sh
(main.c)
...
uint16_t Distance=VL53L1__GetDistance(2);
...
```
<br>

<br>
<br><br><br><br><br><br>
# VL53L1X-STM32 una libreria per il riconoscimento dei gesti


<br>

Questa repository contiene il sorgente C, i programmi Node-RED, schemi and informazini sui progetti mostrati nella mia playlist YouTube su Gesture Recognition attraverso la famiglia TOF VL53Lxx di STMicroelectronics.<br>
La playlist è stata creata nel dec '23 e non è ancora popolataa con i video che entrano nel dettaglio della gestione di (semplici) progetti di Gesture Recognition.<br>
Attualmente c'e' una descrizione su come gestire il sensore VL53L1X attraverso il driver ULD API di STMicroelectronics.<br>
I dettagli sulla integrazione, le funzioni di interfaccia di esempio, il programma Node-RED usato su STM32CubeMonitor per testare il sensore TOF, sono contenuti nella [cartella corrispondente](./interfacing_the_ULD_API_driver).<br>
