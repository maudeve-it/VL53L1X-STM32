_**Piu' sotto, al termine della lingua inglese trovi il testo in italiano. </i>**_
_**<br>Below the English text you'll find the Italian version</i>**_
<br>

# Using VL53L1X through STM ULD API driver


<br>
Here is an implementations of the communication funtions required by ULD driver.<br>
VL53L1X ULD driver is available here: https://www.st.com/en/embedded-software/stsw-img009.html <br>
As indicated [on my video](https://youtu.be/xNhK2Uju1b4) about this set of functions, to use VL53L1X and ULD driver you just need to:<br>

## on CubeMX
-	create a project (I use CubeIDE)<br>
-	enable an I2C port, in standard mode or fast mode, to connect TOF sensor<br>
-	(optional) enable an input GPIO pin connecting the GPIO pin of VL53L1X (INT pin on some breakout boards)<br>
-	(optional) enable an output GPIO pin connecting the XSHUT pin of VL53L1X (SHUT pin on some breakout boards)<br>
<br>
If not connected to the uC, XHUT pin of VL52L1x must be connected to VCC<br>
<br>
Give the pin theese names:<br>
-	TOF_SDA<br>
-	TOF_SCL<br>
-	TOF_GPIO<br>
-	TOF_XSHUT<br>
<br>  
Save the project<br>
<br>

## on CubeIDE
- download from ST website the ULD driver for VL53L1X and<br>
  -  from the  API/core folder of the downloaded package copy <b>VL53L1X_api.c</b> into the project source folder<br>
  -  from the  API/core folder of the downloaded package copy <b>VL53L1X_api.h</b> into the project header folder<br>
- copy from this repository the file <b>vl53l1_platform.h</b> and put it in the headers folder<br>
- copy from this repository the file <b>vl53l1_platform.c</b> and put it in the headers folder<br>
- edit <b>main.h</b> file adding the libraries include, this way:<br> 
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
- finally edit <b>vl53l1_platform.h</b> and set the configuration parameters in STEP1 to STEP5<br>
<br>
<br>
Now you can edit <b>main.c</b> enabling VL53L1X and starting ranging.<br>
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
-  then proceeding getting ranging values:

```sh
(main.c)
...
uint16_t Distance=VL53L1__GetDistance(2);
...
```
<br>

<br>
<br>
## Testing VL53L1X on STM32CubeMonitor<br>
<br>
This repository includes also a testing function and a flow for CubeMonitor to analyze testing results on a PC on real time.<br>
An example of CubeMonitor working with this testing fonction is within the same [YoutTube video](https://youtu.be/xNhK2Uju1b4) mentionned on top of this page.<br>
<br>
- setup the project as indicated above<b>
- copy from this repository the file <b>vl53l1_test.h</b> and put it in the headers folder<br>
- copy from this repository the file <b>vl53l1_test.c</b> and put it in the headers folder<br>
- copy from this repository the file <b>vl53l1_test.json</b> and put it in the project root folder<br>
- add the #include vl53l1_test.h to <b>main.h</b> as indicated above<br>
- edit <b>main.c</b> adding the device inizialization and starting ranging as indicated above
- in the main loob of main.c add the call to the function 



<br><br><br><br><br><br>

# Usare VL53L1X con la libreria ULD API driver di STMicroelectronics


<br>
Qui trovi l'implementazione delle funzioni di comunicazione richieste dal driver ULD.<br>
Il driver ULD per VL53L1X e' disponibile qui: https://www.st.com/en/embedded-software/stsw-img009.html <br>
Come indicato [nel mio video](https://youtu.be/xNhK2Uju1b4) su questo set di funzioni, per usare VL53L1X ed il driver ULD devi semplicemente:<br>

## on CubeMX
-	create a project (I use CubeIDE)<br>
-	enable an I2C port, in standard mode or fast mode, to connect TOF sensor<br>
-	(optional) enable an input GPIO pin connecting the GPIO pin of VL53L1X (INT pin on some breakout boards)<br>
-	(optional) enable an output GPIO pin connecting the XSHUT pin of VL53L1X (SHUT pin on some breakout boards)<br>
<br>
If not connected to the uC, XHUT pin of VL52L1x must be connected to VCC<br>
<br>
Save the project<br>
<br>

## on CubeIDE
- download from ST website the ULD driver for VL53L1X and
  -  from the  API/core folder of the downloaded package copy <b>VL53L1X_api.c</b> into the project source folder
  -  from the  API/core folder of the downloaded package copy <b>VL53L1X_api.h</b> into the project header folder
-	copy from this repository the file "vl53l1_platform.h" and put it in the headers folder<br>
-	copy from this repository the file "vl53l1_platform.c" and put it in the headers folder<br>
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
-  then proceeding getting ranging values:

```sh
(main.c)
...
uint16_t Distance=VL53L1__GetDistance(2);
...
```
<br>
