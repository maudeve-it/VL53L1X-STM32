_**Piu' sotto, al termine della lingua inglese trovi il testo in italiano. </i>**_<br>
_**Below English text you'll find the Italian version</i>**_

<br>

# My VL53L1X library - Mode 3 - a gesture menu system

Library provides a function that, allows to assign functions to single/double/long clicks to easily setup a system controlled by gestures.<br>
Function simply receives the distance value measured by the sensor detecting gestures and assigning them any number of functions in a structured way.<br>

Example of using this function is on this YouTube video: [Gesture Recognition with ToF sensors: gesture detection and a gesture menu system using VL53L1X](https://youtu.be/igdWc8bO9kg)<br><br>
<br>

## Create a STM32CubeMX project

Follow all steps in Mode 1
<br>

## STM32CubeIDE setup

Follow all steps in Mode 1<br>
Follow all steps in Mode 2<br>
<br>

## Library configuration

Edit <b><i>z_vl53l1_gesture.h</i></b> and set the configuration parameters in <i>USER/PROJECT PARAMETERS</i> session on <i>"STEP 2"</i>:
-	number if items in the menu (number of menu levels)
-	menu enabling sequence and sequence timeout(protecting against unwanted activations)
-	menu items switching sequence
-	menu inactive timeout
<br>
  
(details and examples on each above parameter on [Using a gesture controlled menu](https://www.youtube.com/watch?v=igdWc8bO9kg&t=999s))<br>
<br>
<br>

## Available functions

<br>
<b>uint8_t VL53L1__GestureMenu(uint8_t SStatus,uint16_t Distance);</b><br><br>
VL53L1__GestureMenu() detects gestures, verifies enabling sequence and the execution of menu commands<br>
To assign commands/functions to menu items (gestures) setup the function:

<br>

<br>
<b>void VL53L1X__GestureMenu_Items(uint8_t menuItem, uint8_t firstCall, uint8_t shortClick,uint8_t longClick,int16_t *longClickVal,int16_t *longClickLowerValue,int16_t *longClickUpperValue);
</b><br><br>

VL53L1X__GestureMenu_Items() receives the current menu item (menuItem), indicating if the current call is the first one in a calling series (firstCall=1).<br>
Other parameters specifies if the function is called having detected a single, a double or a long click (please note: single and double clicks are signaled just 1 time, while a long click si signaled (calling VL53L1X__GestureMenu_Items()) each time until sensor detects the longclick)<br>
Next, function receives the current value of the longclick corresponding to the "long detection" and the two limits (the lower and the upper one).<br>
Long click value, lower and upper limits can be modified by VL53L1X__GestureMenu_Items(): typically (only) on the first call, the function set te current value and its limits.<br><br>

An example of a running VL53L1X__GestureMenu_Items() function is available in <b><i>z_vl53l1_test.c</i></b>.<br>

<br>


## Usage
<br>

```sh
...

	SStatus=VL53L1__GetDistance(&Distance);
	if (SStatus<=VL53L1__RANGE_STATUS_THRESH)	
		VL53L1__GestureMenu(SStatus, Distance);

...
```
<br>



## A menu status led
<br>
Having available a pin and a timer (any type) on the uC, the library allows setting up a menu status led, helping the end user to handle menu in a system that might not have any other visual user interface.<br>
Led will be off when menu is disabled and will repeate blinking cycles which number of flashes is equal to the current menu level.<br>

(see [A gesture-menu status led](https://www.youtube.com/watch?v=igdWc8bO9kg&t=1604s) for an example)<br>

<br>

### Cubemx configuration 
<br>
Setup a pin handling led:<br>

|Pinname to assign|Output level|Mode|Pull-up/down|
|---|---|---|---|
MENU_LED|x|OutputENU_LED|x|Output x|x|

Set initial output level, pin mode (push pull/open drain), pulled up/down as per your preferred pin configuration.<br>
<br>
Setup a counting up timer.<br>
Set the prescaler allowing to conveniently assign ARR values allowing a readable blinking.<br>

### Library configuration 
<br>
Edit <b><i>z_vl53l1_gesture.h</i></b> and set the configuration parameters in <i>USER/PROJECT PARAMETERS</i> session on <i>"STEP 3"</i>:<br>

-	remove comment on "_ISLED" define indicating that there is a menu led in the project.
-	notify which pin level makes led on (GPIO_PIN_SET if led is ground connected, GPIO_PIN_RESET if connected to VCC
-	which timer is used to drive blinking
-	ARR assigned counting values when led is on in a blinking series, when it is off, pause duration between two series.<br>
<br>

### Usage
<br>
Connect LED (and a resistor) to the pin.<br>
There is nothing else/more to do: entering in manu, led will start fhashing,
showing current menu level.
<br>
<br>

## Testing the system
<br>

In the [src](../src) folder of this repository, you can find also <b><i>z_vl53l1_test.c</i></b> and <b><i>z_vl53l1_test.h</i></b>, containing the test function shown on [Testing a gesture menu](https://www.youtube.com/watch?v=igdWc8bO9kg&t=1359s).

-	Copy the two _test files in the corresponding core/src and core/inc folders.
-	Copy "TestMenu_VL53L1X.json" file in the project main folder.
-	just call "VL53L1__testMenu()" function in the main loop (after device and ranging initialization and ranging start, as always):
<br>

```sh
(main.c)
...
  /* USER CODE BEGIN WHILE */
  if (VL53L1__Init())
	  while (1) {};
  VL53L1__InitGesture();
  VL53L1X_StartRanging(VL53L1__ADDR);   /* Enabling ranging */

  while (1)
  {

	VL53L1__testMenu();
...
```
<br>

-	open CubeMonitor, load TestMenu_VL53L1X.json script, deploy it and run 
Dashboard...

<br>
<br>
<br>
<br>


---

# La mia libreria VL53L1X - Mode 2 - riconoscimento gesti

La libreria mette a disposizione una funzione che consente di assegnare funzioni a clic singoli/doppi/lunghi per impostare facilmente un sistema controllato da gesti.<br>
La funzione riceve semplicemente il valore della distanza misurata dal sensore rilevando i gesti e assegnando loro un numero qualsiasi di funzioni in modo strutturato.<br>

Un esempio di utilizzo di questa funzione si trova in questo video di YouTube:  [Gesture Recognition with ToF sensors: gesture detection and a gesture menu system using VL53L1X](https://youtu.be/igdWc8bO9kg)<br><br>

## Crea un progetto STM32CubeMX

Esegui tutti i passi come in Mode 1
<br>

## STM32CubeIDE setup

Esegui tutti i passi come in Mode 1<br>
Esegui tutti i passi come in Mode 2<br>
<br>

## Configurazione della libreria

Modifica <b><i>z_vl53l1_gesture.h</i></b> e imposta i parametri di configurazione nella sessione <i>USER/PROJECT PARAMETERS</i> nel <i>"STEP 2"</i>:
- il numero di voci del menu (numero di livelli del menu)
- la sequenza di attivazione del menu e timeout della sequenza (per la protezione da attivazioni indesiderate)
- la sequenza di commutazione delle voci del menu
- il timeout di inattività del menu
(dettagli ed esempi su ciascun parametro sopra riportato su [Using a gesture controlled menu](https://www.youtube.com/watch?v=igdWc8bO9kg&t=999s))
<br>
<br>
## Funzioni disponibili

<br>
<b>uint8_t VL53L1__GestureMenu(uint8_t SStatus,uint16_t Distance);</b><br><br>
VL53L1__GestureMenu() rileva i gesti, verifica la sequenza di attivazione e l'esecuzione dei comandi del menu<br>
Per assegnare comandi e funzioni alle voci di menu (gesti) impostare la funzione:

<br>

<br>
<b>void VL53L1X__GestureMenu_Items(uint8_t menuItem, uint8_t firstCall, uint8_t shortClick,uint8_t longClick,int16_t *longClickVal,int16_t *longClickLowerValue,int16_t *longClickUpperValue);
</b><br><br>

VL53L1X__GestureMenu_Items() riceve la voce di menu corrente (menuItem), indicando se la chiamata corrente è la prima di una serie di chiamate (firstCall=1).<br>
Altri parametri specificano se la funzione viene chiamata dopo aver rilevato un clic singolo, doppio o lungo (nota: i clic singoli e doppi vengono segnalati solo 1 volta, mentre un clic lungo viene segnalato (chiamando VL53L1X__GestureMenu_Items()) ogni volta finché il sensore non rileva il clic lungo)<br>
Di seguito, la funzione riceve il valore corrente di longclick corrispondente al "rilevamento lungo" e i due limiti (quello inferiore e quello superiore).<br>
Il valore del longclick, i limiti inferiore e superiore possono essere modificati da VL53L1X__GestureMenu_Items(): tipicamente (solo) alla prima chiamata, la funzione imposta il valore corrente e i suoi limiti.<br>

Un esempio di una funzione VL53L1X__GestureMenu_Items() in esecuzione è disponibile in <b><i>z_vl53l1_test.c</i></b>.<br>

<br>

## Utilizzo
<br>

```sh
...

	SStatus=VL53L1__GetDistance(&Distance);
	if (SStatus<=VL53L1__RANGE_STATUS_THRESH)
		VL53L1__GestureMenu(SStatus, Distance);

...
```
<br>


## Un led di stato del menù
<br>

Se nel progetto rimane libero un pin del UC ed un timer (di qualunque tipo), la libreria consente di impostare un led che mostra lo stato del menu, aiutando l'utente finale in un sistema che potrebbe non avere alcun altra interfaccia utente visiva.<br>

(vedi [A gesture-menu status led](https://www.youtube.com/watch?v=igdWc8bO9kg&t=1604s) per un esempio)

<br>

### Configurazione Cubemx 
<br>
Configura un pin per il led:<br>

|Nome Pin|Output level|Mode|Pull-up/down|
|---|---|---|---|
|MENU_LED|x|Output x|x|

<br>
Imposta l'output level iniziale, il pin mode (push pull/open drain), se pull up/down secondo le tua modalità di gestione del led.<br><br>

Configura un timer counting up.<br>
Imposta il prescaler in modo da permettere di assegnare valori ARR che permettano lampeggi interpretabili.<br>

### Configurazione libreria 
<br>
Modifica <b><i>z_vl53l1_gesture.h</i></b> ed imposta i parametri di configurazione in <i>USER/PROJECT PARAMETERS</i> nella sessione <i>"STEP 3"</i>:<br>

-	togli il commento alla define "_ISLED" indicando che c'e' un menu_led nel progetto.
-	indica quale livello pin accende il led (GPIO_PIN_SET se il led e' connesso a terra, GPIO_PIN_RESET se a VCC
-	quale timer viene usato per il lampeggio del led
-	i valori assegnati a ARR quando il led e' acceso in una serie di lampeggi, quando è spento, la duratsa della pausa tra due serie.<br>

<br>

### Utilizzo

<br>

Collega il LED (e la sua resistenza) al pin.<br>
Non c'e' altro da fare: entrando nel menù, il led inizierà a lampeggiare,
mostrando il livello di menu corrente.
<br>

## Test del sistema

<br>

Nella cartella [src](../src) di questa repository, puoi trovare anche <b><i>z_vl53l1_test.c</i></b> e <b><i>z_vl53l1_test.h</i ></b>, contenenti la funzione di test mostrata in [Testing a gesture menu](https://www.youtube.com/watch?v=igdWc8bO9kg&t=1359s).

- Copia i due file _test nelle cartelle core/src e core/inc corrispondenti.
- Copia il file "TestMenu_VL53L1X.json" nella cartella principale del progetto.
- basta chiamare la funzione "VL53L1__testMenu()" nel ciclo principale (dopo l'inizializzazione del dispositivo e della lettura e l'avvio delle letture, come sempre):
<br>

```sh
(main.c)
...
  /* USER CODE BEGIN WHILE */
  if (VL53L1__Init())
	  while (1) {};
  VL53L1__InitGesture();
  VL53L1X_StartRanging(VL53L1__ADDR);   /* Enabling ranging */

  while (1)
  {

	VL53L1__testMenu();
...
```
<br>

-	apri CubeMonitor, carica lo script TestMenu_VL53L1X.json, fai il deploy ed esegui la Dashboard...







---
