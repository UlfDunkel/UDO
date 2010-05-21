**** STUPARGV.S ************************************************************************

*	Startup-Code fr Pure C

*

*	V 2.0	11.09.2002 von Stefan Kuhr @ OS

*

*	 ù Quoting (Komandozeilenparameter mit Leerzeichen)

*	 ù ARGV (Komandozeilenparameter mit mehr als 125 Zeichen werden im Environment

*	   bergeben)

*	 ù erweitertes ARGV (šbergabe von leeren Parametern)

*	 ù Zeiger auf die Komandozeilenargumente und Environmentvariablen verkleinern

*	   den Stack nicht zwangsl„ufig

*	 ù optionale FPU-Initialisierung

*	 ù Parserschnittstelle zum C-Code

*	 ù zus„tzliche Informationen ber den erfolgten Startup an das Hauptprogramm

*	 ù fast vollst„ndig konfigurierbar





*	TEXT	DATA	BSS

*	<------><------><------|----------------->				Programmheader

*							Heap		 Stack

*							<-----><--------->				Accessory

*							Heap		Stack/TPA-Ende

*							<-----><----------------->		Programm

*

*	Der Startup-Code berechnet zuerst die Gr”e der drei Segmente ohne den vom 

*	Linker im BSS-Segment reservierten Stackspeicher. Direkt hinter diesen

*	Bereich schliet sich dann der Heap an, in den der Sartup-Code die Felder 

*	envp und argv ablegen wird. 

*	Vom hintersten Ende des Programmspeichers wird anschlieend ein minimaler 

*	Systemstack (SYSSTKSIIZE) abgezogen, der immer frei bleibt, und somit die 

*	maximale Heap-Gr”e bestimmt.

*	Mit dem Ablegen der Zeiger von zun„chst envp und anschlieend argv w„chst 

*	der Heap auf seine tats„chliche Gr”e.

*	Bei Programmen wird nach dem Aufbau der Felder die gewnschte Stackgr”e

*	auf das Ende des Heaps addiert und so die ben”tigte TPA-Gr”e festgelegt. 

*	Auf diese Gr”e wird dann die TPA geschrumpft.

*

*	Allerdings kann es passieren, dass durch einen groen Heap die zur Verfgung

*	stehende TPA nicht mehr die gewnschte Stackgr”e fasst. In diesem Fall 

*	haben wir eine „hnliche Situation wie bei Accessories. Teile von argv und 

*	envp liegen dann im untersten Stackbereich.

*	Bei Accessories schrumpft bereits das Betriebssystem die TPA auf die Summe

*	der drei Segmente. Der Heap w„chst deshalb zwangsl„ufig komplett von unten 

*	in den Stack hinein.

*

*	Im Worst-Case werden im Programmverlauf durch einen wachsenden Stack die 

*	Felder argv und envp komplett zerst”rt. Deshalb sollte auf einen ausreichend 

*	groen Stack geachtet werden. Im Zweifelsfall sollten argv und envp 

*	m”glichst frh und mit geringem Stackbedarf ausgewertet werden.

*	Der oberste Bereich des Stacks (in einer Gr”e von SYSSTKSIZE) wird 

*	allerdings nie durch enpv und argv belegt, so dass bei einer frhzeitigen

*	und nicht stackintensiven Auswertung keine groe Gefahr besteht.







.EQU			FPUINIT,		0			* Wenn 1, wird _fpuinit aufgerufen.



.EQU			HEAPOVERFLOW,	1			* Wenn 1, wird errno auf EHEAPOVF anstatt auf 

											* E_OK gesetzt, wenn argv oder argv und envp 

											* wegen Speichermangels nicht komplett belegt 

											* werden konnten. 

											* Das obere Ende des Stacks in der Gr”e von

											* SYSSTKSIZE wird allerdings nie durch argv

											* oder envp belegt. Bei entsprechend kleinem

											* Stackbedarf kann also ohne Gefahr auf alle 

											* bergebenen argv- und envp-Elemente zugegriffen

											* werden.

											



.EQU			HEAPONSTACK,	1			* Wenn 1, wird _HeapOnStk als unsigned long 

											* definiert, der angibt, wie viele Bytes des 

											* unteren Stack-Endes durch den Heap belegt 

											* werden.

											

.EQU			CHECKSTACK,		0			* Wenn 1, wird sichergestellt, dass mindestens 

											* ein Rest-Stack der Gr”e SYSSTKSIZE komplett

											* frei bleibt; ansonsten wird illegal ausgefhrt.

											* Am einfachsten l„sst sich das aber 

											* sicherstellen, indem im Linker eine Stack-Gr”e

											* von mindesten SYSSTKSIZE+12 Byte definiert wird.

											* In diesem Fall ist CHECKSTACK unn”tig und sollte

											* deshalb auf 0 gesetz werden.



.EQU			CMDLINEINPLACE,	0			* Wenn 1, wird die Kommandozeile nicht ins BSS

											* kopiert und statt dessen inplace in der 

											* Basepage geparst.

											* Wird allerdings Fsfirst() aufgerufen, ohne

											* zuvor mit Fsetdta() die DTA in einen anderen

											* Bereich zu legen, wird die Kommandozeile 

											* berschrieben.

											* Wenn 0 werden 128 Byte im BSS eingespart, die

											* bei Verwendung des ARGV-Verfahrens eh nicht 

											* ben”tigt werden.



.EQU			USEARGV,		1			* Wenn 1, wird das ARGV-Verfahren untersttzt.



.EQU			EXTENDEDARGV,	1			* Wenn 1, wird das erweiterte ARGV-Verfahren

											* genutzt, mit dem auch leere Parameter bergeben

											* werden k”nnen.

											* Zus„tzlich muss auch USEARGV gesetzt sein.

											

.EQU			PATHFIX,		3			* Definiert die Fix-Methode des 'PATH=\0' Fehlers.

											* 0: keine Fehlerbehebung

											*	 PATH ist immer leer, dessen eigentlicher Wert

											*	 ist eine ungltige Variable.

											* 1: PATH=;C:\bin\0

											* 	 Es wird zuerst im aktuellen Verzeichnis

											*	 gesucht, wodurch z.B. andere Programme

											*	 gestartet werden als eigentlich beabsichtigt.

											* 2: PATH=C:\bin\0\0

											*	 Das doppelte Nullbyte am Ende verhindert ein

											*	 korrektes Vererben des Environments an andere

											*	 Prozesse.

											* 3: PATH=C:\bin;\0

											*	 Durch das aktuelle Verzeichnis am Ende des

											*	 Suchpfades werden eventuell Dateien gefunden,

											*	 die eigentlich nicht gefunden werden sollten.



.EQU			SYSSTKSIZE,		256			* Stackreserve fr Systemfunktionen,

											* muss ein gerader Wert sein.

											* Der Stack muss mindestens genauso gro sein:

											* _StkSize >= SYSSTKSIZE

											* Es wird garantiert, dass dieser Stackbereich

											* niemals durch argv oder envp belegt wird,

											* sofern CHECKSTACK genutzt wird oder die Stack-

											* Angabe im Linker entsprechend gro ausf„llt.



.EQU			MAXCMDLEN,		126			* Maximal gltiger Wert fr Kommandozeilenl„nge.

											* Definiert ist eine L„nge von 125, aber MagiCDesk

											* bergibt bis zu 126 Zeichen in der Basepage.





.EXPORT			parse_cmdline

.EXPORT			errno

.EXPORT			exit

.EXPORT			_app

.EXPORT			_BasPag

.EXPORT			_AtExitVec

.EXPORT			_FilSysVec

.EXPORT			_StkLim

.EXPORT			_PgmSize

.IF HEAPONSTACK

.EXPORT			_HeapOnStk

.ENDIF

.EXPORT 		__text

.EXPORT 		__data

.EXPORT 		__bss

.EXPORT			__exit



.IMPORT			main

.IMPORT			_fpuinit

.IMPORT			_FreeAll

.IMPORT			_StkSize					* Stackgr”en unter SYSSTKSIZE+12 Byte fhren bei Accessories

											* und gesetztem CHECKSTACK immer zu einer Illegal-Exception,  

											* bei Programmen ist das nur der Fall, wenn die TPA zu klein ist.







.OFFSET										* Basepage-Struktur

TpaStart:		.DS.L	1

TpaEnd: 		.DS.L	1

TextSegStart:	.DS.L	1

TextSegSize:	.DS.L	1

DataSegStart:	.DS.L	1

DataSegSize:	.DS.L	1

BssSegStart:	.DS.L	1

BssSegSize: 	.DS.L	1

DtaPtr: 		.DS.L	1

PntPrcPtr:		.DS.L	1

Reserved0:		.DS.L	1

EnvStrPtr:		.DS.L	1

Reserved1:		.DS.B	7

CurDrv: 		.DS.B	1

Reserved2:		.DS.L	18

CmdLine:		.DS.B	128

BasePageSize:	.DS.B	0







.DATA



__data:

_AtExitVec: 	.DC.L	0					* Vektor fr atexit()

_FilSysVec: 	.DC.L	0					* Vektor zur Deinitialisierung von Dateifunktionen

.EQU			E_OK,			0

errno:			.DC.W	E_OK				* globale Fehler-Variable (ERROR.H)



.IF HEAPOVERFLOW

.EQU			EHEAPOVF,		1

.ENDIF



.IF HEAPONSTACK

_HeapOnStk:		.DC.L	0

.ENDIF







.BSS



__bss:

_BasPag:		.DS.L	1					* Zeiger auf Basepage

_app:			.DS.W	1					* Applikationsflag

_StkLim:		.DS.L	1					* Stacklimit

_PgmSize:		.DS.L	1					* Programmgr”e



.IF CMDLINEINPLACE

.ELSE

CmdLineArgs:	.DS.B	128					* Platz fr Kommandozeile, wegen Fsfirst()

.ENDIF



.EVEN







.TEXT

											* A6 Heap			frei

											* A5 Basepage		frei

											* A4 envp			frei

											* A3 argv			frei

											* A2 				frei

											* A1 				frei

											* A0 				frei

											* D7 argc			frei

											* D6 _app			frei

											* D5 Heap-Ende		frei

											* D4 heap_overflow	frei

											* D3 				frei

											* D2 				frei

											* D1 				frei

											* D0 				frei

__text:

				move.l	A0,A5				* Basepage-Zeiger retten, falls Accessory

				bra		Begin

				.ASCIIZ	'Pure C ARGV V2.0'

				.EVEN

Begin:

				moveq.l	#0,D6				* vorsorglich als Accessory markieren

				move.l	A0,D0				* prfen, ob's wirklich ein Accessory ist

				bne 	Cont				* wenn Accessory ->



				movea.l 4(SP),A5			* Basepage-Zeiger vom Stack

				moveq.l	#1,D6				* Programm ist Applikation

Cont:

.IF HEAPOVERFLOW

				moveq.l	#EHEAPOVF,D4		* D4 heap_overflow	gltig

.ENDIF

											* A5 Basepage		gltig

											* D6 _app			gltig



				move.l	A5,_BasPag			* Basepageadresse sichern



				move.l	BssSegStart(A5),D0	* Startadresse des BSS-Segments

				add.l	BssSegSize(A5),D0	* + dessen Gr”e => hinter Ende des BSS-Segments

											* = Stackadresse fr Accessories

				move.w	D6,_app				* Programmart vermerken

				bne		SetHeap				* kein Accessory ->



				move.l	D0,D1				* ein Accessory hat noch keinen Stack

				and.b	#$FE,D1				* D1 auf gerade Adresse abrunden

				move.l	D1,SP				* Stack einrichten

				sub.l	A5,D1				* Differenz zwischen Stack und Basepage

				move.l	D1,_PgmSize			* ist die Programmgr”e

SetHeap:

				sub.l	#_StkSize-1,D0		* BSS-Ende - (Stackgr”e-1) => Adresse des Heaps

				and.b	#$FE,D0				* und Heap-Adresse auf gerade Adresse abrunden

				move.l	D0,A6				* A6 ist nun der Heap



											* A6 Heap			gltig

.IF PATHFIX

				move.l	#'HTAP',D0			* D0 fr Fehlerabfang bei 'PATH=\0'

.ENDIF				

				move.l	#'VGRA',D1			* D1 fr ARGV Abfrage

				move.b	#'=',D2 			* D2 fr '='



				move.l	SP,D5				* der Stackpointer ist gleichzeitig Ende des Heaps

				sub.l	#SYSSTKSIZE+8,D5	* Sicherheitszone fr Systemstack

											* und Platz fr argv0, argv1 reservieren

				sub.l	A6,D5				* Gr”e des Heaps berechnen

				and.b	#$FC,D5				* auf Vielfaches von vier abrunden

				add.l	A6,D5				* Heap + Gr”e = Heap-Ende



											* D5 Heap-Ende - 8	gltig

.IF CHECKSTACK				

				cmp.l	A6,D5				* prfen, ob es berhaupt einen Heap gibt

				bhi		EndCheckStack1		* wenn es keinen Heap gibt l„uft das Programm auf 

				illegal						* illegal auf

											* im Accessory-Betrieb muss der Stack also

											* mindestens SYSSTKSIZE+12 Byte gro sein

EndCheckStack1:										

.ENDIF



				movea.l EnvStrPtr(A5),A0	* A0 zeigt auf das Environment

				movea.l A6,A4				* A4 wird envp



											* A6 Heap			gltig

											* A5 Basepage		gltig

											* A4 envp			gltig

											* A3 argv			frei

											* A2 				frei

											* A1 				frei

											* A0 Environment

											* D7 argc			frei

											* D6 _app			gltig

											* D5 Heap-Ende - 8	gltig

											* D4 heap_overflow	gltig

											* D3 				frei

											* D2 '='

											* D1 'ARGV'

											* D0 'PATH'

EnvLoop:

				move.l	A0,(A6)+			* Adresse einer Env.-Variablen vermerken

				cmp.l	A6,D5				* auf Heap-šberlauf prfen

				bls		EnvExit				* bei šberlauf das Environment abschlieen



.IF (USEARGV = 0)  & (PATHFIX = 0)

				tst.b	(A0)+

				beq		EnvExit

.ELSE

				movea.l SP,A1

				move.b	(A0)+,-(A1) 		* n„chstes Byte

				beq 	EnvExit 			* =0 -> Ende des Environments, Kommandozeile auswerten



				move.b	(A0)+,-(A1) 		* n„chstes Byte

				beq 	EnvLoop 			* =0 -> neue Variable



				move.b	(A0)+,-(A1) 		* n„chstes Byte

				beq 	EnvLoop 			* =0 -> neue Variable



				move.b	(A0)+,-(A1) 		* n„chstes Byte

				beq 	EnvLoop 			* =0 -> neue Variable

.ENDIF

.IF USEARGV

				cmp.l	(A1),D1				* 'ARGV'?

				beq		TestARGV			* ja ->

.ENDIF

.IF PATHFIX > 0

				cmp.l	(A1),D0 			* 'PATH'?

				bne 	ScanEnv				* nein ->



				move.b	(A0)+,D3			* ja, n„chstes Byte

				beq 	EnvLoop 			* =0 -> neue Variable

				cmp.b	D2,D3				* '='?

				bne 	ScanEnv 			* nein ->



				tst.b	(A0)+				* n„chstes Byte nach 'PATH=' k”nnte 0 sein

				bne 	ScanEnv 			* ist ein bekannter TOS-Fehler

				tst.b	(A0)				* bei 'PATH=\0\0' ist das Environment aber zu Ende

				beq		EnvLoop				* 'PATH' war die letzte Environmentvariable ->

											* ein Sprung zu EnvExit wrde den Zeiger auf 'PATH' l”schen

.IF PATHFIX = 1				

				move.b	#';',-1(A0)			* PATH=;C:\bin;\0

.ELSE		

				lea		-1(A0),A2			* Adresse des Nullbytes hinter 'PATH=' merken

MovePath:		move.b	(A0)+,(A2)+			* und alle Zeichen eins nach vorne kopieren

				bne		MovePath			* bis zum n„chsten Nullbyte

											* PATH=C:\bin\0\0

.ENDIF

.IF PATHFIX = 3

				move.b	#';',-(A2)			* PATH=C:\bin;\0

.ENDIF

.ENDIF



ScanEnv:

				tst.b	(A0)+				* bis zur 0 suchen

				bne 	ScanEnv

				bra 	EnvLoop 			* n„chste Env.-Variable



.IF USEARGV

TestARGV:

				move.b	(A0)+,D3			* n„chstes Byte

				beq 	EnvLoop 			* =0 -> neue Variable

				cmp.b	D2,D3				* '='?

				bne 	ScanEnv 			* nein ->



				clr.b	-5(A0)				* 'AGRV=' -> '\0RGV='



				cmp.b	#127,CmdLine(A5)	* Komandozeilenl„nge =127?

				bne 	EnvExit 			* nein -> (dort wird der Zeiger auf 'ARGV=' gel”scht)



**** ARGV-Kommandos ********************************************************************

				clr.l	-4(A6)				* letzten Zeiger l”schen, und envp mit NULL-Pointer abschlieen

				movea.l A0,A1				* Zeiger auf 'NULL:' retten

				movea.l A6,A3				* A3 ist 'char *argv[]'

				moveq.l	#-1,D7				* D7 wird 'int argc'

											* aber 'ARGV=' soll nicht gez„hlt werden, drum -1



											* Environment ist somit abgeschlossen

				addq.l	#8,D5				* Heap-Ende korrigieren, Platz fr argv0 und argv1 ist noch da



											* A6 Heap			gltig

											* A5 Basepage		gltig

											* A4 envp			gltig

											* A3 argv			gltig

											* A2 				frei

											* A1 'NULL:'		frei

											* A0 ARGV-Argumente

											* D7 argc			fast gltig

											* D6 _app			gltig

											* D5 Heap-Ende 		gltig

											* D4 heap_overflow	gltig

											* D3 				frei

											* D2 				frei

											* D1 				frei

											* D0 				frei

ARGVLoop:

				tst.b	(A0)+				* suche Ende eines ARGV-Parameters

				bne 	ARGVLoop

				move.l	A0,(A6)+			* und schreibe die Adresse des folgenden ARGV-Kommandos in den Heap

				addq.l	#1,D7				* z„hle Anzahl der ARGV-Kommandos



				cmp.l	A6,D5				* auf Heap-šberlauf prfen

				bls		BreakARGV			* Argumentliste beenden

											* da D5 eben erst um 8 erh”ht wurde, ist garantiert

											* noch Platz fr zwei Zeiger auf dem Heap d.h.

											* argc (D7) wird >= 1 und somit garantiert gltig



				tst.b	(A0)+				* doppeltes Nullbyte?

				bne 	ARGVLoop			* nein, n„chstes ARGV-Kommando ermitteln

.IF HEAPOVERFLOW

											* das ganze Environment ausgewertet

				moveq.l	#E_OK,D4			* heap_overflow=false

.ENDIF

				

BreakARGV:

				clr.l	-4(A6)				* letzte kopierte Adresse eines ARGV-Arguments ungltig

											* l”schen, um das Ende der Argumente zu markieren

											* auf den Heap wurden nun die Adressen der

											* Environmentvariablen und ARGV-Argumente gepackt,

											* somit markiert nun A6 die untere Stackgrenze



.IF EXTENDEDARGV

				tst.l	D7					* wenn wir keine ARGV-Kommandos bekommen haben,

				beq 	Start				* k”nnen wir auch keine l”schen ->



				lea 	7(A1),A2			* berechne kleinstm”gliche Adresse von argv[0]

				cmpa.l	(A3),A2 			* wenn argv[0] kleiner als diese Adresse ist

				bhi 	Start				* keine Parameter l”schen ->



				cmpi.b	#'N',(A1)+			* und prfen, ob ARGV=NULL: ist

				bne 	Start

				cmpi.b	#'U',(A1)+

				bne 	Start

				cmpi.b	#'L',(A1)+

				bne 	Start

				cmpi.b	#'L',(A1)+

				bne 	Start

				cmpi.b	#':',(A1)+

				bne 	Start



EmptyARGV:

				moveq.l	#0,D2				* bekommt die Nummern der zu leerenden Parameter

				move.b	(A1)+,D2			* erstes Zeichen holen

				cmp.b	#'9',D2

				bhi 	Start				* gr”er als 9, Fehler ->

				sub.b	#'0',D2 			* '0' abziehen um Wert zu bekommen

				blo 	Start				* kleiner als 0, Fehler ->

				moveq.l	#0,D1				* D1 auf Long l”schen

ARGVNumber:

				move.b	(A1)+,D1			* n„chste Ziffer holen

				cmp.b	#'9',D1

				bhi 	Start				* gr”er als 9 - also auch kein Komma, Fehler ->

				sub.b	#'0',D1 			* in Dezimalzahl wandeln

				blo 	ClearARGV			* war keine ASCII-Zahl mehr ->

				move.l	D2,D3				* D2*=10

				lsl.l	#3,D2				* = D2*8 + D2 + D2

				add.l	D3,D2

				add.l	D3,D2

				add.l	D1,D2				* D2+=D1

				bra 	ARGVNumber			* n„chstes Zeichen auswerten

ClearARGV:

				cmp.l	D2,D7				* prfen, ob es einen Parameter mit dem Index gibt

				bls 	Start				* gibt's nicht, Fehler ->

				lsl.l	#2,D2				* D2*=4

				movea.l 0(A3,D2.l),A2		* A1=argv[D2], sollte somit auf " \0" zeigen

				cmpi.b	#' ',(A2)+			* Parameter muss " \0" sein, prfe ' '

				bne 	Start				* Fehler ->

				tst.b	(A2)				* Parameter muss " \0" sein, prfe '\0'

				bne 	Start				* Fehler ->

				clr.b	-(A2)				* alles korrekt, leeren Parameter leer machen

				cmp.b	#','-'0',D1 		* Trennzeichen nach der Nummer prfen

				beq 	EmptyARGV			* bei einem Komma folgen noch weitere leere Parameter

.ENDIF

				bra 	Start				* war kein Komma ->

.ENDIF



EnvExit:

											* A6 Heap			gltig

											* A5 Basepage		gltig

											* A4 envp			gltig

											* A3 argv			frei

											* A2 				frei

											* A1 				frei

											* A0 Ende von evnp	ungltig

											* D7 argc			frei

											* D6 _app			gltig

											* D5 Heap-Ende - 8	gltig

											* D4 heap_overflow	gltig

											* D3 				frei

											* D2 				frei

											* D1 				frei

											* D0 				frei



				lea 	-4(A6),A0			* letzte kopierte Adresse einer Environmentvariable

				clr.l	(A0)				* war ungltig, l”schen, um das Ende der Variablen

											* zu markieren

											* Auf den Heap wurden nun die Adressen der

											* Environmentvariablen inklusive NULL-Pointer

											* gepackt, A6 zeigt auf die n„chste freie Position.



**** Kommandozeile *********************************************************************

											* fr argv0 und argv1 ist immer Platz auf dem Heap

				movea.l A6,A3				* A3 ist 'char *argv[]'

				move.l	A0,(A6)+			* A0 zeigt auf ein Nullbyte,

											* wird als Programmname in argv[0] eingetragen

				clr.l	(A6)+				* argv zuvor schon mit einem Nullbyte abschlieen

				moveq.l	#1,D7				* D7 ist argc und wird auf 1 gesetzt

											* somit sind argc und argv gltig



				add.l	#8,D5				* Heap-Ende korrigieren



											* A6 Heap			gltig

											* A5 Basepage		gltig

											* A4 envp			gltig

											* A3 argv			gltig

											* A2 				frei

											* A1 				frei

											* A0 				frei

											* D7 argc			gltig

											* D6 _app			gltig

											* D5 Heap-Ende 		gltig

											* D4 heap_overflow	gltig

											* D3 				frei

											* D2 				frei

											* D1 				frei

											* D0 				frei



				cmp.l	A6,D5				* auf Heap-šberlauf prfen

				bls		Start				* Kommandozeile nicht auswerten, einfach starten



.IF HEAPOVERFLOW

				moveq.l	#E_OK,D4			* heap_overflow=false

.ENDIF

				lea		CmdLine(A5),A0		* Adresse der Kommandozeile in A0

.IF CMDLINEINPLACE

				move.l	A0,A1				* A1 = Zielspeicher fr geparste Kommandozeile

.ELSE

				move.l	CmdLineArgs,A1		* A1 = BSS-Speicher fr geparste Kommandozeile

.ENDIF

				clr.w	D3					* D3 als Word l”schen

				move.b	(A0)+,D3			* L„ngenbyte der Kommandozeile nach D3

				beq		Start				* wenn das 0 ist ->

.IF USEARGV				

				cmp.b	#MAXCMDLEN,D3		* auf maximal gltige Kommandozeilenl„nge prfen

.ELSE

				cmp.b	#127,D3				* wenn kein ARGV genutzt wird, wird das Maximum 

											* aus der Kommandozeile heraus geholt

.ENDIF

				bhi 	Start				* ungltige L„nge ->

				clr.b	0(A0,D3.w)			* Kommandozeile mit Nullbyte abschlieen



											* maximale argv-Feldgr”e bestimmen

				move.l	D5,D0				* Heap-Ende nach D0 kopieren

				sub.l	A6,D0				* Heap-Adresse abziehen

				lsr.l	#2,D0				* D0/=4 um die Anzahl der Pointer zu berechnen

											* Argument 3 enth„lt nun die Feldgr”e

				move.l	D0,D3				* Feldgr”e sichern



				subq.l	#4,A6				* Nullpointer in argv[1] berschreiben lassen



											* D0 = Gr”e des argv-Feldes

											* A0 = Kommandozeile

											* A1 = Zielspeicher fr geparste Kommandozeile

				move.l	A6,-(SP)			* Zieladresse des argv-Feldes auf den Stack legen



				bsr		parse_cmdline		* Kommandozeile parsen



				addq.l	#4,SP				* Stack aufr„umen



				add.l	D0,D7				* Anzahl geparster Argumente auf argc (=1) addieren

				cmp.l	D3,D0				* prfen, ob das argv-Feld bergelaufen ist 

				blo		SetArgc				* kein šberlauf (weniger geparste Argumente als Pl„tze im Feld) ->

				move.l	D3,D7				* argc setzen

.IF HEAPOVERFLOW

				moveq.l	#EHEAPOVF,D4		* heap_overflow=true

.ENDIF

SetArgc:				

				move.l	D7,D0				* argc kopieren

				lsl.l	#2,D0				* L„nge des argv-Feldes in Byte

				lea		(A6,D0.l),A6		* Heap um Feldl„nge korrigieren

											* wenn das argv-Feld bergelaufen ist, ist es

											* nicht durch einen NULL-Zeiger abgeschlossen

				clr.l	-4(A6)				* argv[argc]=NULL, bei šberlauf des argv-Feldes 

											* fehlt sonst der NULL-Zeiger als Abschlus

Start:

											* A6 Heap			gltig

											* A5 Basepage		gltig

											* A4 envp			gltig

											* A3 argv			gltig

											* A2 				frei

											* A1 				frei

											* A0 				frei

											* D7 argc			gltig

											* D6 _app			gltig

											* D5 Heap-Ende		gltig

											* D4 heap_overflow	gltig

											* D3 				frei

											* D2 				frei

											* D1 				frei

											* D0 				frei



				tst.w	D6					* wenn's ein Accessory ist, muss der Speicher nicht

				beq		SetStkLimit			* geschrumpft werden, der Stack wurde fr Accessories 

											* bereits beim Berechnen des Heaps geprft



				move.l	A6,D3				* Heap-Adresse kopieren

				add.l	#_StkSize,D3		* Heap + Stackgr”e = neuer SP

											* der Linker sorgt dafr, dass _StkSize immer gerade ist

											* deshalb kann hier auf ein Abrunden verzichtet werden

				cmp.l	SP,D3				* wenn wir ber das Ende der TPA hinaus kommen

				bhs		SetStkLimit			* Stack nicht „ndern und Speicher nicht schrumpfen ->



				move.l	D3,SP				* neuen Stack einrichten

				sub.l	A5,D3				* Differenz von Stackadresse und Basepageadresse ist

				move.l	D3,_PgmSize			* Programmgr”e, diese vermerken



				move.l	D3,-(SP)			* Programmgr”e auf den Stack

				move.l	A5,-(SP)			* TPA-Start = Basepageadresse auf den Stack

				pea		$4A0000				* eine 0 und den Mshrink-Opcode auf den Stack

				trap	#1					* Mshrink aufrufen

				lea		12(SP),SP			* Stack korrigieren



SetStkLimit:

				move.l	SP,D3					

				sub.l	#_StkSize-SYSSTKSIZE,D3

											* Stacklimit = BSS-Ende - (Stackgr”e - Sicherheitszone)

				move.l	D3,_StkLim			* Stacklimit vermerken

.IF CHECKSTACK

				cmp.l	SP,D3				* falls die Stackadresse kleiner als _StkLim ist

				bls		EndCheckStack2		* l„uft das Programm auf illegal		

				illegal

EndCheckStack2:			

.ENDIF				



.IF FPUINIT

****************************************************************************************

*	Test auf 68881 FPU

				jsr		_fpuinit			* Test auf 68881

.ENDIF



											* A6 Heap			gltig

											* A4 envp			gltig

											* A3 argv			gltig

											* D7 argc			gltig

											* D4 heap_overflow	gltig

											* D3 _StkLim

.IF HEAPONSTACK

				sub.l	#SYSSTKSIZE,D3		* absolutes Stack-Ende berechnen

				move.l	A6,D2				* D2 enth„lt sp„ter die Anzahl Bytes, die der 

											* Heap in den Stack hineingewachsen ist

				sub.l	D3,D2				* Heap und Stack-Ende vergleichen

				blo		NoHeapOnStk			* wenn der Heap ber dem Stack-Ende liegt, die Gr”e

				move.l	D2,_HeapOnStk		* der šberschneidung in _HeapOnStk ablegen,

NoHeapOnStk:						

.ENDIF



.IF HEAPOVERFLOW

				move.w	D4,errno			* heap_overflow in errno ablegen

.ENDIF

				move.l	D7,D0				* argc nach D0

				move.l	A3,A0				* argv nach A0

				move.l	A4,A1				* envp nach A1



**** int main(unsigned long argc, char *argv[], char *envp[]) **************************

*	<D0.L> = Kommandozeilenparameteranzahl								argc

*	<A0.L> = Zeiger auf Kommandozeilenparameterfeld 					argv

*	<A1.L> = Zeiger auf Environmentvariablenfeld						envp

*	Vom Standard abweichend wird argc als unsigned long bergeben!

*	Falls HEAPOVERFLOW gesetzt ist, kann das Hauptprogramm errno berprfen;

*	errno ist EHEAPOVF, wenn envp oder argv nicht komplett ausgewertet wurden.

*	Falls HEAPONSTACK gesetzt ist, ist _HeapOnStk als unsigned long definiert und

*	gibt an, wie viele Bytes des unteren Stack-Endes durch den Heap belegt werden.

				jsr 	main







**** void exit (int status) ************************************************************

*	<D0.W> = Rckgabewert des Programms



exit:

				move.w	D0,-(SP)			* Returnwert von main auf den Stack

				move.l	_AtExitVec,D0		* alle registrierten atexit-Prozeduren ausfhren

				beq 	exit1

				movea.l D0,A0

				jsr 	(A0)

exit1:

				move.l	_FilSysVec,D0		* Dateisystem deinitialisieren

				beq 	exit2

				movea.l D0,A0

				jsr 	(A0)

exit2:

				jsr 	_FreeAll			* alle Speicherbl”cke freigeben

											* Returnwert von main liegt schon auf dem Stack

				move.w	#76,-(SP)			* Pterm-Opcode auf den Stack

				trap	#1					* Programm beenden







****************************************************************************************

*	unsigned long parse_cmdline(char * cmdline, char * cmdarg, char ** argv, unsigned long max_argc)  

*	in		A0: char*

*				Zeiger auf einen nullterminierten Kommandostring ohne L„ngenangabe

*	in		A1: char*

*				Zeiger auf einen Speicherbereich, in den die geparsten Parameter

*				hineingeschrieben werden. Wenn der NULL ist, wird A1 mit A0

*				gleichgesetzt, also inplace ersetzt.

*	in		SP: char**

*				Zeiger auf ein Feld von Zeigern, in denen Zeiger auf die einzelnen

*				Parameter abgelegt werden, darf auch NULL sein.

*	in/out	D0:	unsigned long

*				in	Gr”e des Zeigerfeldes

*				out	Anzahl der geparsten Parameter



parse_cmdline:

				move.l	A2,-(SP)			* Register sichern

				movea.l 8(SP),A2			* A2 zeigt auf das Feld argv fr die Parameterzeiger

				move.l	D0,D2				* D2 ist max_argc

				

				move.l	A1,D1				* Zieladresse fr Kommandos testen

				bne		InitFieldPointer

				move.l	A0, A1				* bei NULL inplace ersetzen

InitFieldPointer:

				move.l	A2,D1				* wenn der Zeiger auf das Feld 0 ist, 

				bne 	InitArgc			* wird D2 auf 0 gesetzt, somit werden keine Zeiger 

				moveq.l	#0,D2				* in das argv-Feld geschrieben

InitArgc:

				moveq.l	#0,D0				* D0 = argc

											* A2 = argv

											* D2 = maximale Feldgr”e von argv

											* A0 = Kommandozeile

											* A1 = Zieladresse fr Kommandos

											* D1 = aktuelles Zeichen aus Kommandozeile



				bra		ScanCmdLine

ParseCmd:

				cmp.b	#' ',D1 			* fhrende Leerzeichen abschneiden

				beq 	ScanCmdLine

				tst.l	D2					* wenn kein Eintrag im Feld mehr frei ist

				beq		IncrArgc			* nur noch den Z„hler erh”hen ->

				subq.l	#1,D2				* ansonsten den Feldz„hler verringern

				move.l	A1,(A2)+			* und die Adresse eines Kommandos speichern

IncrArgc:

				addq.l	#1,D0				* argc erh”hen

				cmp.b	#39,D1				* Kommando beginnt mit '?

				bne 	NormalCmd			* nein -> normalCmd

NextChar:

				move.b	(A0)+,D1			* n„chstes Zeichen

				beq 	CmdLineReady

				cmp.b	#39,D1				* '?

				bne 	NormalChar			* nein ->

				move.b	(A0)+,D1			* n„chstes Zeichen

				beq 	CmdLineReady

				cmp.b	#' ',D1 			* ' '?

				beq 	CloseCmd			* ja, Ende des Kommandos ->

				move.b	#39,(A1)+			* nein, ' bernehmen

				cmp.b	#39,D1				* '?

				beq 	NextChar

NormalChar:

				move.b	D1,(A1)+			* nein, Zeichen bernehmen

				bra 	NextChar



NormalCmd:

				move.b	D1,(A1)+			* Zeichen bernehmen

NextNormalChar:

				move.b	(A0)+,D1

				beq 	CmdLineReady

				cmp.b	#' ',D1 			* Kommandoende?

				bne 	NormalCmd			* nein ->

CloseCmd:

				clr.b	(A1)+				* 0 bernehmen

ScanCmdLine:

				move.b	(A0)+,D1			* n„chstes Zeichen holen

				bne 	ParseCmd



CmdLineReady:

				clr.b	(A1)				* 0 hintendran

				tst.l	D2					* wenn kein Eintrag im Feld mehr frei ist

				beq		ClearStack			* nur noch aufr„umen ->

				clr.l	(A2)				* ansonsten noch argv[argc]=NULL setzen

ClearStack:

				move.l 	(SP)+,A2

				rts







.END

