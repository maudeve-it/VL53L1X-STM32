_**Piu' sotto, al termine della lingua inglese trovi il testo in italiano. </i>**_<br>
_**Below English text you'll find the Italian version</i>**_

<br>

# My VL53L1X library - Mode 1 - handling the TOF sensor


Library provides functions to initialize and communicate with the device enabling features, starting target detections and getting information.<br><br>
Library is made upon the [ULD APIs](https://www.st.com/en/embedded-software/stsw-img009.html) provided by STMicroelectronics. 
As you know these devices (TOF series by STM) do not have a register map (or something like that) of the sensors allowing their control. 
They need to be accessed through a library providing C functions for every commmand/request to send/receive to/from the sensor.<br>
More info on this YouTube video: [Gesture Recognition with ToF sensors: handling VL53L1X using Ultra Light Driver (ULD)](https://youtu.be/xNhK2Uju1b4)<br><br>
To run an STM32 using VL53L1X with my library, setup a project with the following steps. <br>
<br>

## Create a STM32CubeMX project


- Create a project for your favorite STM32.
- enable an I2C port to connect VL53L1X. 

I2C configuration is:<br>

|Parameter|Value|
|---|---|
|Speed mode|Standard/Fast Mode (no Fast Mode Plus)|
|Address Length|7-bit|

-	Assign these names to I2C pins:<br>

|I2C pin|Pinname to assign|
|---|---|
|SCL|TOF_SCL|
|SDA|TOF_SDA|

-	Appropriately set pin speed (you know: <i>slower is better</i>).<br>
-	If needed, the device can work only with the two I2C pins but the full functionality and improved performance are achieved by activating two additional communication pins:<br> 

|Pinname to assign|Output level|Mode|Pull-up/down|
|---|---|---|---|
|TOF_GPIO|-|Input mode|No pull-up/down|
|TOF_XSHUT|-|Output push pull|No pull-up/down|

<br>

-	Complete project configuration (set uC clock configuration, serial wire debug if needed, etc.), save it and generate C code.<br>

<br>

## STM32CubeIDE setup


-	Download from STM website the [ULD APIs package](https://www.st.com/en/embedded-software/stsw-img009.html)<br>
-	From the downloaded API/core folder copy <b><i>VL53L1X_api.c</i></b> and <b><i>VL53L1X_api.h</i></b> to the corresponding Core/Src and Core/Inc folders
-	Copy, from the [src](../src) folder of this repository, <b><i>vl53l1_platform.c</i></b> and <b><i>vl53l1_platform.h</i></b>, again to the corresponding project folder
-	edit <b><i>main.h</i></b> file and, in <i>"Private includes"</i> session, add include directive for the .h files:  
<br>

```sh
(main.h)
...
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "VL53L1X_api.h"
#include "vl53l1_platform.h"
/* USER CODE END Includes */
...
```
<br>

## Library configuration

Edit <b><i>vl53l1_platform.h</i></b> and set the configuration parameters in <i>USER/PROJECT PARAMETERS</i> session from <i>"STEP 1"</i> to <i>"STEP 5"</i>:
-	STEP 1 refers to the communication wiring to VL53L1X:
	-	 which I2C port is used
	-	the I2C address of VL53L1X
	-	if using XSHUT pin to put the sensor in HW standby, uncomment VL53L1__USING_XSHUT row. <br> Otherwisw, if the sensor is always active, disable VL53L1__USING_XSHUT row commenting it. In this case connect sensor Xshut pin to VCC following scheme <i>"1.4 Application schematic"</i> on the [VL53L1X datasheet](https://www.st.com/resource/en/datasheet/vl53l1x.pdf)
	-	if VL53L1__USING_GPIO is uncommented, library requires a TOF_GPIO pin available (connected to GPIO pin of VL53L1X) to get notification about the vailability of new ranging data set.<br> If this pin is not available (if the row is commented) library will poll the sensor, about this information, via I2C. 


<br>
<br>

-	STEP 2 refers to the ranging configuration on startup:
	-	Distance mode (mode 1 gives higher precision rangings but shorter maximum target distance)
	-	Timing budget (shorter is faster but with lower precision)
	-	VL53L1__TB_IM_DELTA is added to Timing budget to define intermeasurement time

<br>
<br>

-	STEP 3 refers to the definition of the ranging area definition:
	-	Window mode (4 modes available)
	-	Lower and upper ranging threshold. Meaning of these thresholds depends to the windows mode, see comments in the vl53l1_platform.h file.

<br>
<br>

-	STEP 4 calibration parameters: these two parameters are related to the single sensor wiu are using and (mailnly) to the protecting glass you are using in your project. STMiroelectronics provides, in its library, two functions to define these parameters. 

<br>
<br>


Having set above configuraon,<br>
you are ready to go working with VL53L1X<br>


## Available functions


<b>uint8_t VL53L1__Init()</b><br><br>
VL53L1__Init() is the sensor initializing function. It performs:
-	a test of VL53L1 presence on the configured port
-	initialize the sensor
-	it sets the default Distance Mode, Timing Budget and Intermeasurement time
<br>
It must be called as the first step before entering in uC main loop.<br>
<br>
It returns 0 if no errors detected.<br><br>

<i>
VL53L1__Init() terminates leaving VL53L1X in software standby mode. <br>
In order to activate target detection getting distance data  you must run <br>

VL53L1X_StartRanging(VL53L1__ADDR); //(ULD API from ST).
</i>
<br><br>


<b>uint8_t VL53L1__GetDistance(uint16_t *Distance)</b><br><br>
VL53L1__GetDistance() polls sensor asking data about a new target ranging.
It sets <i>Distance</i> parameter the new reading data if a ranging was performeed since its previous call.
If not, it hangs waiting for the new data availalable.



---

# La mia libreria VL53L1X - Mode 1 - gestire il sensore TOF

La libreria fornisce funzioni per inizializzare e comunicare con il dispositivo abilitando funzionalità, per avviare i rilevamenti e per leggere le informazioni.<br><br>
La libreria è basata sulle [API ULD](https://www.st.com/en/embedded-software/stsw-img009.html) fornite da STMicroelectronics.
Come sapete questi dispositivi (serie TOF della STM) non hanno una mappa dei registri (o qualcosa del genere) del sensore che ne consenta il controllo.
È necessario accedervi tramite una libreria che fornisce funzioni C per ogni comando/richiesta di invio/ricezione al/dal sensore.<br>
Maggiori informazioni su questo video di YouTube: [Gesture Recognition with ToF sensors: handling VL53L1X using Ultra Light Driver (ULD)](https://youtu.be/xNhK2Uju1b4)<br><br>
Per un STM32 utilizzando VL53L1X con la mia libreria, imposta un progetto con i seguenti passaggi. <br>
<br>



## Configurazione Parametri

- Crea un progetto per il tuo STM32 preferito.
- attiva una porta I2C da collegare a VL53L1X. 

La configurazione I2C è:<br>

|Parametro|Valore|
|---|---|
|Speed mode|Standard/Fast Mode (non Fast Mode Plus)|
|Address Length|7-bit|

-	assegna questi nomi ai pin I2C:<br>

|Pin I2C|Nome pin|
|---|---|
|SCL|TOF_SCL|
|SDA|TOF_SDA|

-	Imposta appropriatamente la velocità del pin (sai che: <i>più lenta è, meglio è</i>).<br>
-	Se necessario, il sensore può comunicare con i soli 2 pin I2C, ma la piena funzionalità e prestazioni migliori si ottengono attivando due pin addizionali:<br> 

|Nome pin|Livello output|Modo|Pull-up/down|
|---|---|---|---|
|TOF_GPIO|-|Input mode|No pull-up/down|
|TOF_XSHUT|-|Output push pull|No pull-up/down|

<br>

-	Completa la configurazione del progetto (imposta il clock del uC, la  porta serial wire debug se necessaria, ecc.), salva e genera il codice C.<br>

<br>

## STM32CubeIDE setup


-	Scarica dal sito di STM il [package ULD APIs](https://www.st.com/en/embedded-software/stsw-img009.html)<br>
-	Dalla cartella "core" delle API scaricate, copia <b><i>VL53L1X_api.c</i></b> and <b><i>VL53L1X_api.h</i></b> nelle cprrispondenti cartelle  Core/Src and Core/Inc del progetto
-	Copia, dalla cartella [src](../src) di questa repository, <b><i>vl53l1_platform.c</i></b> and <b><i>vl53l1_platform.h</i></b>, ancora nelle cartelle corrispondenti.
-	modifica il file <b><i>main.h</i></b>: nella sezione <i>"Private includes"</i> aggiungi le direttive include per i file .h:  
<br>

```sh
(main.h)
...
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "VL53L1X_api.h"
#include "vl53l1_platform.h"
/* USER CODE END Includes */
...
```
<br>



## Configurazione della libreria 

Modifica <b><i>vl53l1_platform.h</i></b> e imposta i parametri di configurazione nella sessione <i>USER/PROJECT PARAMETERS</i> da <i>"STEP 1"</i> a < i>"STEP 5"</i>:
- Il PASSOSTEP1 si riferisce al cablaggio di comunicazione al VL53L1X:
	- quale porta I2C viene utilizzata)
	- l'indirizzo I2C del VL53L1X
	- se si utilizza il pin XSHUT per porre il sensore in standby HW, rimuovere il commento dalla riga VL53L1__USING_XSHUT. <br> Se invece il sensore è sempre attivo, disabilita la riga VL53L1__USING_XSHUT commentandola. In questo caso, collegare il pin Xshut del sensore a VCC seguendo lo schema <i>"1.4 Application schematic"</i> di [VL53L1X datasheet](https://www.st.com/resource/en/datasheet/vl53l1x.pdf)
	- se VL53L1__USING_GPIO non è commentato, la libreria richiede un pin TOF_GPIO disponibile (collegato al pin GPIO di VL53L1X) per ricevere una notifica sulla disponibilità del nuova lettura del sensore.<br> Se questo pin non è disponibile (se la riga è commentata) la libreria interrogherà il sensore, riguardo questa informazione, tramite I2C.


<br>
<br>

- Lo STEP 2 si riferisce alla configurazione del rilevamento all'avvio:
	- Distance mode (Mode 1 fornisce intervalli di precisione più elevati ma una distanza massima del target minore)
	- Timing budget (più breve è più veloce ma con minore precisione)
	- VL53L1__TB_IM_DELTA viene aggiunto al timing budget per definire l'intermeasurement time
	
<br>
<br>

- Lo STEP 3 si riferisce alla definizione dell'area di lettura:
	- Window mode (4 modalità disponibili)
	- Soglia inferiore e superiore di lettura Il significato di queste soglie dipende dalla Window mode, vedere i commenti nel file vl53l1_platform.h.


<br>
<br>

- STEP 4 Parametri di calibrazione: questi due parametri sono relativi al singolo sensore che stai utilizzando e (principalmente) alla protezione trasparente che stai utilizzando nel tuo progetto. STMiroelectronics fornisce, nella sua libreria, due funzioni per definire questi parametri.


<br>
<br>


vendo impostato la configurazione sopra,<br>
sei pronto per lavorare con VL53L1X<br>
​
## funzioni disponibili 

<b>uint8_t VL53L1__Init()</b><br><br>
VL53L1__Init() è la funzione di inizializzazione del sensore. Esegue:
- un test di presenza del VL53L1 sulla porta configurata
- inizializzazione il sensore
- imposta i valori di default per Distance Mode, Timing Budget ed Intermeasurement.
<br>
Deve essere chiamata come primo step prima di entrare nel ciclo principale del uC.<br>
<br>
Restituisce 0 se non vengono rilevati errori.<br><br>

<i>
VL53L1__Init() termina lasciando VL53L1X in modalità standby software. <br>
Per attivare il rilevamento ottenendo la lettura dei dati è necessario eseguire<br>
VL53L1X_StartRanging(VL53L1__ADDR); //(API ULD di ST).
</i>
<br><br>

<b>uint8_t VL53L1__GetDistance(uint16_t *Distance)</b><br><br>
VL53L1__GetDistance() interroga il sensore e richiede i dati su una nuova lettura.
Restituisce (nel parametro <i>Distance</i>) i nuovi dati se è stata eseguita una misurazione dopo la precedente chiamata della funzione.
In caso contrario, rimane in attesa dei nuovi dati disponibili.
