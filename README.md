<br>


_**Piu' sotto, al termine della lingua inglese trovi il testo in italiano. </i>**_<br>
_**Below English text you'll find the Italian version</i>**_

<br>
<br>

# VL53L1X - STM32 -  a gesture recognition handling library

This repository contains the C code of a set of functions for an STM32 microcontroller handling a VL53L1X time-of-flight sensor through the [ULP APIs](https://www.st.com/en/embedded-software/stsw-img032.html) provided by STMicroelectronics. It is the source and documentation archive of [my YouTube playlist about gesture recognition](https://youtube.com/playlist?list=PL6Fwy7aR3zSlArL6TJnSjWSbKmxM5BHnb&si=_yf3am68zesmYO3j).<br>
<br>
Library can be used as:<br>
-	<b>Mode 1 - Directly handle VL53L1X</b>:<br>
	library provides functions to initialize and communicate with the device via I2C and STM APIs.<br>
	Just setting up configurations parameters you should be able to fully handle the device.<br>
	Reference for this usage mode is:<br>
	[YouTube Video](https://youtu.be/xNhK2Uju1b4)<br> 
	[Guidelines](./1-direct_handling)<br>
-	<b>Mode 2 - Gesture recognition</b>:<br>
	library includes function to detect defined gestures through the handling above indicated.<br>
	Reference for this usage mode is:<br>
	[YouTube Video](https://youtu.be/igdWc8bO9kg)<br> 
	[Guidelines](./2-gesture_detection)<br>
-	<b>Mode 3 - Gesture menu handling</b>:<br>
	any number of project functions can be assigned to gestures in a structured way. <br>
	Reference for this usage mode is:<br>
	[YouTube Video](https://www.youtube.com/watch?v=igdWc8bO9kg&t=1001s) <br>
	[Guidelines](./3-gesture_menu_handling)<br>
<br>
Developed software is based on HAL over STM32CubeIDE.<br>
<br>
				
---

## Project Folders

As above indicated the folder you see here are:<br>
-	1 - A guide to setup a project [handling VL53L1X](./1-direct_handling) with this library<br>
-	2 - A guide to enable [gesture detection](./2-gesture_detection)<br>
-	3 - A guide to setup a [gesture menu](./3-gesture_menu_handling)<br>
plus
-	the folder containing the [source files](./src) of the library, of the test functions, and the testing STM32CubeMonitor scripts (see next in the instruction folders) 
<br>
Each of the three <i>"library modes"</i>, mentionned above, requires the preceding configurations completed:<br>
- Mode 2 requires also Mode 1 configuration completed<br>
- Needing Mode 3, you must complete configuration also of Mode 1 and 2<br>
- If you just need using library in Mode 1 you can forget mode 2 and 3<br>
<br>
<br>

---
> Please Note:
> The software, schemes and PCB designs in this set of repositories are provided just for 
> illustrative purposes, sharing the personal experience on this project. 
> The software and design artifacts are provided as-is without any mantainence and without
> warranty of any kind. There is no guarantee of fitness for any particular application, 
> and no guarantee of completeness and correctness. 
> By downloading and using these materials the user accepts all risks associated with the
> run of the software and construction and use of the circuits and devices described.<br>
---

## Troubleshooting
<br>
---

## rev. history

-	1.0		-	Mode 1 available
-	2.0		-	Mode 2 and Mode 3 added
<br>
<br>
<br>

---
---

<br>


# VL53L1X - STM32 -  una libreria per il riconoscimento dei gesti

Questa repository contiene il codice C di un set di funzioni per un microcontrollore STM32 che gestisce un sensore time-of-flight VL53L1X attraverso le [ULP APIs](https://www.st.com/en/embedded-software/stsw-img032.html) fornite da STMicroelectronics. Rappresenta l'archivio dei programmi e della documentazione relativa alla [mia playlist YouTube sulla <i>gesture recognition</i>](https://youtube.com/playlist?list=PL6Fwy7aR3zSlArL6TJnSjWSbKmxM5BHnb&si=_yf3am68zesmYO3j).<br>
<br>
La libreria può essere utilizzata per:<br>
-	<b>Mode 1 - Gestire direttamente VL53L1X</b>:<br>
	la libreria mette a disposizione le funzioni per inizializzare e comunicare con il sensore via I2c e le API di STM.<br>
	Semplicemente impostando i parametri di configurazione dovresti essere in grado di gestire pienamente il sensore.<br>
	Il riferimento per usare questo modo è:<br>
	[Video YouTube](https://youtu.be/xNhK2Uju1b4)<br> 
	[Istruzioni](./1-direct_handling)<br>
-	<b>Mode 2 - Rilevamento gesti</b>:<br>
	la libreria contiene le funzioni necessare per rilevare determinati gesti attraverso la gestione indicata sopra<br>
	qui, puoi impostare la libreria per gestire l'intero set di 	Il riferimento per usare questo modo è:<br>
	[Video YouTube](https://youtu.be/igdWc8bO9kg)<br> 
	[Istruzioni](./2-direct_handling)<br>
-	<b>Mode 3 - Creare un menù gestuale</b>:<br>
	qualunque numero di funzioni del progetto può essere assegnato a gesti<br>  
	Il riferimento per usare questo modo è:<br>
	[Video YouTube](https://www.youtube.com/watch?v=igdWc8bO9kg&t=1001s) <br>
	[Istruzioni](./3-gesture_menu_handling)<br>
<br>
Il software sviluppato, si basa su HAL attraverso STM32CubeIDE.<br>
<br>

---

## Cartelle del progetto 

Come indicato sopra, le tre cartelle che vedi qui sono:<br>
-1 La guida per configurare un progetto [basato su VL53L1X](./1-direct_handling)<br>
-2 La guida per attivare il [rilevamento gesti](./2-gesture_detection)<br>
-3 La guida per configurare un [menù basato su gesti](./3-gesture_menu_handling)<br>
<br>
Ogni <i>"Modo d'uso"</i> della libreria, citato sopra, richiede che vengano completate le configurazioni dei "modi" precedenti:<br>
- Il modo 2 richiede venga completata anche la configurazione del modo 1<br>
- Occorrendo il modo 3, devi completare anche le configurazioni del modo 1 e 2<br>
- Se occorre la libreria solo nel modo 1 puoi tralasciare il modo 2 e 3<br>
<br>
<br>

---
> Il software e gli schemi di progetto come i layout PCB in questa serie di repository 
> sono messe a disposizione con puro intento illustrativo e di condivisione dell'esperienza fatta
> Il software and gli elementi del progetto sono messi a disposizione "allo stato in cui sono"
> senza impegno di manutenzione e senza garanzie di alcun tipo. Piu' esplicitamente, non c'e' garanzia di 
> adeguatezza a soddisfare specifiche esigenze, ne di completezza o correttezza di alcuna parte.
> Scaricando ed utilizzando questo materiale l'utilizzatore accetta il rischio associato alla
> realizzazione ed all'utilizzo del circuito, del software e dei componenti descritti in questi file.<br> 

---



---

## Soluzione a qualche problema
<br>	

---

## rev. history

-	1.0		-	prima release: Modo 1 disponibile
-	2.0		-	aggiunti Modo 2 e Modo 3


---
---


