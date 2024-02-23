_**Piu' sotto, al termine della lingua inglese trovi il testo in italiano. </i>**_<br>
_**Below English text you'll find the Italian version</i>**_

<br>

# My VL53L1X library - Mode 2 - gesture recognition


Library provides a function that, receiving as parameter the detected distance of a target (a hand moving in front of the sensor), recognize
three types of gestures:
-	a fast movement in front of the sensor (a hand quickly moving). This gesture is called a "<b>SINGLE CLICK</b>"
-	two fast movement in front of the sensor in a short time (a hand quickly moving forth and back):  a "<b>DOUBLE CLICK</b>"
-	a target detected for a long time by the sensor (a hand keeping in front of the sensor): a "<b>LONG CLICK</b>"

Function returns the gestures detected and (in case of a long click) the target distance for the whole time gesture is detected. 

Example of using this function is on this YouTube video: [Gesture Recognition with ToF sensors: gesture detection and a gesture menu system using VL53L1X](https://youtu.be/igdWc8bO9kg)<br><br>
<br>

## Create a STM32CubeMX project

Follow all steps in Mode 1
<br>

## STM32CubeIDE setup

Follow all steps in Mode 1
<br>
Then <br>
-	Copy, from the [src](../src) folder of this repository, <b><i>z_vl53l1_gesture.c</i></b> and <b><i>z_vl53l1_gesture.h</i></b>, again to the corresponding project folder
-	edit <b><i>main.h</i></b> file and, in <i>"Private includes"</i> session, add include directive for the .h files:  
<br>

```sh
(main.h)
...
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "VL53L1X_api.h"
#include "vl53l1_platform.h"
#include "z_vl53l1_gesture.h"
/* USER CODE END Includes */
...
```
<br>


## Library configuration

Edit <b><i>z_vl53l1_gesture.h</i></b> and set the configuration parameters in <i>USER/PROJECT PARAMETERS</i> session on <i>"STEP 1"</i>:
-	max and min distance where gesture are detected (within the ranging threshold definition (see vl53l1_platform.h, STEP 3)
-	time threshold to detect a double click
-	time threshold to detect a long click
-	timing budget in single/doubleclick detection
- 	timing budget when in long click
-	"differential smoothness" (see [Controlling values with gesture recognition: an incremental algorithm](https://www.youtube.com/watch?v=igdWc8bO9kg&t=952s))
<br>


## Available functions

<br>
<b>void VL53L1__InitGesture();</b><br><br>
VL53L1__InitGesture() initialize sensor as per gesture detection parameters.
<br>

<br>
<b>uint8_t VL53L1__CheckGesture(uint16_t dist, uint8_t *sClick, uint8_t *dClick, uint8_t *lClick, int16_t *lClickVal, const int16_t lClickLower, const int16_t lClickUpper);</b><br><br>

VL53L1__CheckGesture() receives distance measured by the sensor (dist) and detects clicks, setting to 1 sClick, dClick, lClick if detected single, double or long clicks.<br>
In case of a long click running, function sets lClickVal as per long click detection within limits defined by lClickLower and lClickUpper.
(see [Using the gesture recognition function](https://www.youtube.com/watch?v=igdWc8bO9kg&t=439s) for an example)

<br>


## Usage
<br>

```sh
...

	SStatus=VL53L1__GetDistance(&Distance);
	if (SStatus<=VL53L1__RANGE_STATUS_THRESH)
		VL53L1__CheckGesture(Distance, &shortClick, &doubleClick, &longClick, &longClickVal, TESTGESTURE_LCLICK_LOWER, TESTGESTURE_LCLICK_UPPER);

...
```
<br>





---

# La mia libreria VL53L1X - Mode 2 - riconoscimento gesti

La libreria fornisce una funzione che, ricevendo come parametro la distanza rilevata di un target (una mano che si muove davanti al sensore), riconosce
tre tipi di gesti:
- un movimento veloce davanti al sensore (una mano che si muove velocemente). Questo gesto è chiamato "<b>SINGLE CLICK</b>"
- due movimenti veloci davanti al sensore in breve tempo (una mano che si muove velocemente avanti e indietro): un "<b>DOUBLE CLICK</b>"
- un bersaglio rilevato a lungo dal sensore (una mano che rimane davanti al sensore): un "<b>LONG CLICK</b>"

La funzione restituisce i gesti rilevati e (in caso di long click) la distanza target per l'intero tempo in cui viene rilevato il gesto.

Un esempio di utilizzo di questa funzione si trova in questo video YouTube: [Gesture Recognition with ToF sensors: gesture detection and a gesture menu system using VL53L1X](https://youtu.be/igdWc8bO9kg)<br><br>
<br>
​
## Crea un progetto STM32CubeMX

Esegui tutti i passi come in Mode 1
<br>

## STM32CubeIDE setup

Esegui tutti i passi come in Mode 1<br>
Poi<br>
- Copia, dalla cartella [src](../src) di questa repository, <b><i>z_vl53l1_gesture.c</i></b> e <b><i>z_vl53l1_gesture.h</i> </b>, nuovamente nella corrispondente cartella del progetto 
- modifica il file <b><i>main.h</i></b> e, nella sessione <i>"Include private"</i>, aggiungi la direttiva include per i file .h:
<br>

```sh
(main.h)
...
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "VL53L1X_api.h"
#include "vl53l1_platform.h"
#include "z_vl53l1_gesture.h"
/* USER CODE END Includes */
...
```
<br>

## Configurazione della libreria

Modifica <b><i>z_vl53l1_gesture.h</i></b> e imposta i parametri di configurazione nella sessione <i>USER/PROJECT PARAMETERS</i> nello <i>"STEP 1"</i>:
- distanza massima e minima in cui vengono rilevati i gesti (entro la definizione dell'area di lettura (vedere vl53l1_platform.h, FASE 3)
- soglia temporale per rilevare un doppio clic
- soglia temporale per rilevare un clic lungo
- Budget temporale nel rilevamento del singolo/doppio clic
- Budget temporale durante il clic lungo
- "differential smoothness" (vedi [Controlling values with gesture recognition: an incremental algorithm](https://www.youtube.com/watch?v=igdWc8bO9kg&t=952s))
<br>


## Funzioni disponibili

<br>
<b>void VL53L1__InitGesture();</b><br><br>
VL53L1__InitGesture() inizializza il sensore secondo i parametri richiesti per il rilevamento dei gesti.
<br>

<br>
<b>uint8_t VL53L1__CheckGesture(uint16_t dist, uint8_t *sClick, uint8_t *dClick, uint8_t *lClick, int16_t *lClickVal, const int16_t lClickLower, const int16_t lClickUpper);</b><br><br>

VL53L1__CheckGesture() riceve la distanza misurata dal sensore (dist) e rileva i click, impostando a 1 sClick, dClick, lClick se rilevati clic singoli, doppi o lunghi.<br>
In caso di clic lungo, la funzione imposta lClickVal in base alla distanza rilevata del clic lungo, entro i limiti definiti da lClickLower e lClickUpper.
(vedi [Using the gesture recognition function](https://www.youtube.com/watch?v=igdWc8bO9kg&t=439s) per un esempio)
<br>


## Utilizzo
<br>

```sh
...

	SStatus=VL53L1__GetDistance(&Distance);
	if (SStatus<=VL53L1__RANGE_STATUS_THRESH)
		VL53L1__CheckGesture(Distance, &shortClick, &doubleClick, &longClick, &longClickVal, TESTGESTURE_LCLICK_LOWER, TESTGESTURE_LCLICK_UPPER);

...
```
<br>





---
