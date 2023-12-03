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
If not connected to the uC, XSHUT pin of VL52L1x must be connected to VCC<br>
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
- copy from this repository the file <b>vl53l1_platform.c</b> and put it in the source folder<br>
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
Follow these steps:<br>
- setup the project as indicated above<b>
- copy from this repository the file <b>vl53l1_test.h</b> and put it in the headers folder<br>
- copy from this repository the file <b>vl53l1_test.c</b> and put it in the source folder<br>
- copy from this repository the file <b>vl53l1_test.json</b> and put it in the project root folder<br>
- add the #include vl53l1_test.h to <b>main.h</b> as indicated above<br>
- edit <b>main.c</b> adding the device inizialization and starting ranging as indicated above
- in the main loop of main.c add the call to the VL53L1__test() function. That will populate the global variables read by CubeMonitor
- open STMCubeMonitor<br>
  -  import a flow
  -  browse to the project main folder
  -  doubleclick <b>vl53l1_test.json</b> and confirm import
  -  deploy <b>Vl53l1X_TEST</b>, run the dashboard flow and you'll see the data read from the device. 



<br><br><br><br><br><br>

# Usare VL53L1X con la libreria ULD API driver di STMicroelectronics


<br>
Qui trovi l'implementazione delle funzioni di comunicazione richieste dal driver ULD.<br>
Il driver ULD per VL53L1X e' disponibile qui: https://www.st.com/en/embedded-software/stsw-img009.html <br>
Come indicato [nel mio video](https://youtu.be/xNhK2Uju1b4) su questo set di funzioni, per usare VL53L1X ed il driver ULD devi semplicemente:<br>

## in CubeMX
-	crea un progetto (io uso CubeIDE)<br>
-	abilita una porta I2C, in standard mode o fast mode, a cui collegare il sensore TOF<br>
-	(opzionale) abilita un pin GPIO in input cui collegare il pin GPIO di VL53L1X (chiamato INT pin su alcune breakout boards)<br>
-	(optionale) abilita un pin GPIO in output cui collegare il pin XSHUT di VL53L1X (chiamato SHUT pin su alcune breakout boards)<br>
<br>
Se non collegato al uC, XSHUT pin of VL52L1x deve essere connesso a VCC<br>
<br>
Dai ai pin questi nomi:<br>
-	TOF_SDA<br>
-	TOF_SCL<br>
-	TOF_GPIO<br>
-	TOF_XSHUT<br>
<br>  
Salva il progetto<br>
<br>


## in CubeIDE
- scarica dal sito web di ST il driver ULD per VL53L1X e<br>
  -  dalla cartella API/core del pacchetto scaricato, copia <b>VL53L1X_api.c</b> nella cartella source del progetto<br>
  -  dalla cartella API/core del pacchetto scaricato, copia <b>VL53L1X_api.h</b> nella cartella header del progetto<br>
- copia da questa repository il file <b>vl53l1_platform.h</b> e mettilo nella catrtella headers<br>
- copia da questa repository il file <b>vl53l1_platform.c</b> e mettilo nella catrtella source<br>
- edita <b>main.h</b> aggiungendo le include delle librerie in questo modo:<br> 
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
- infine edita <b>vl53l1_platform.h</b> e configura i parametri da STEP1 a STEP5<br>
<br>
<br>
Ora puoi editare <b>main.c</b> attivando VL53L1X e avviando la rilevazione.<br>
In questo modo:<br>
-  inizializza il sensore in USER CODE BEGIN 2:<br>

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
-  avvia il rilevamento in "USER CODE BEGIN WHILE":

```sh
(main.c)
...
  /* USER CODE BEGIN WHILE */

  VL53L1X_StartRanging (TOF_ADDR);
...
```
<br>
-  poi procedi a leggere i dati rilevati:

```sh
(main.c)
...
uint16_t Distance=VL53L1__GetDistance(2);
...
```
<br>

<br>
<br>

## Analizzare VL53L1X su STM32CubeMonitor<br>
<br>
Questa repository include anche una funzione di tested un flow per CubeMonitor per analizzare i risultati del test su PC in tempo reale<br>
Un esempio dell'analisi fatta con CubeMonitor attraverso questa funzione si vede nello stesso [video YoutTube](https://youtu.be/xNhK2Uju1b4) citato all'inizio di questa pagina.<br>
<br>
Segui questi passaggi:<br>
- crea un progetto come indicato sopra<br>
- copia da questa repository il file <b>vl53l1_test.h</b> e salvalo nella cartella headers<br>
- copia da questa repository il file <b>vl53l1_test.c</b> e salvalo nella cartella source<br>
- copia da questa repository il file <b>vl53l1_test.json</b> e salvalo nella cartella root del progetto<br>
- aggiungi la #include vl53l1_test.h a <b>main.h</b> come indicato sopra<br>
- edita <b>main.c</b> aggiungendo l'inizializzazione del sensore e l'avvio del rilevamento come indicato sopra<br>
- nel loop principale di main.c aggiungi la chiamata alla funzione VL53L1__test(). Questa popolerà le variabili globali lette da CubeMonitor<br>
- apri STMCubeMonitor<br>
  -  scegli la voce di menu: import a flow<br>
  -  vai alla cartella principale del progetto<br>
  -  fai un doppioclick su <b>vl53l1_test.json</b> e conferma l'importazione<br>
  -  clicca "Deploy" sul flow <b>Vl53l1X_TEST</b>, esegui la Dashboard e vedtrai i dati letti dal sensore.<br> 

