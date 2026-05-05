# Sistema Gestione Spese Personali

Un'applicazione in C++ a riga di comando per la gestione delle spese personali, sviluppata su ambiente Eclipse. L'applicativo permette di creare categorie, registrare le spese, definire un budget mensile e generare report dettagliati utilizzando un database SQLite.

---

## Requisiti per l'esecuzione

### Compilatore o interprete necessario
* **Compilatore C++**: È richiesto un compilatore che supporti lo standard C++11 o versioni successive (es. **GCC/g++**, **Clang**, o **MinGW** su Windows).
* **IDE (Opzionale ma consigliato)**: Sviluppato e testato su **Eclipse IDE for C/C++ Developers**.

### Librerie standard e di terze parti utilizzate
* **Librerie Standard C++**: 
  * `<iostream>`: Per l'input/output da console.
  * `<string>`: Per la gestione delle stringhe di testo.
* **Librerie Esterne**:
  * `sqlite3.h` / `sqlite3.c`: Libreria per la gestione del database locale SQLite. I file sorgente (o la libreria precompilata) di SQLite3 devono essere presenti nella directory del progetto o correttamente linkati nel compilatore/IDE.

---

## Istruzioni dettagliate per eseguire il programma

### Istruzioni di avvio e comandi da eseguire

Essendo il progetto sviluppato su **Eclipse**, hai due modalità per eseguire il programma: direttamente dall'IDE oppure tramite Terminale/Prompt dei comandi.

#### Opzione A: Esecuzione direttamente da Eclipse (Consigliata)
1. Assicurati di aver compilato il progetto (Tasto destro sul progetto -> **Build Project**).
2. Nella barra in alto, clicca sul pulsante verde **Play (Run)**, oppure fai clic destro sul progetto nel *Project Explorer* -> **Run As** -> **Local C/C++ Application**.
3. Interagisci con il programma direttamente dalla scheda **Console** in basso nell'interfaccia di Eclipse.
> **Nota:** In questo caso, il file del database `spese_personali.db` verrà creato automaticamente nella cartella principale (root) del tuo progetto Eclipse.

#### Opzione B: Esecuzione da Terminale / Prompt dei comandi
Quando Eclipse compila il progetto, inserisce il file eseguibile generato in una sottocartella specifica (solitamente chiamata `Debug` o `Release`).

1. Apri il Terminale (macOS/Linux) o il Prompt dei comandi/PowerShell (Windows).
2. Spostati nella cartella di compilazione del tuo progetto Eclipse usando il comando `cd`. Ad esempio:
   bash
   cd percorso/del/tuo/workspace/NomeProgetto/Debug
3. eseguire il comando .\NomeProgetto.exe
   
### Opzione C: Compilazione Manuale (Opzione universale)
Se non utilizzi un IDE, puoi compilare il progetto da terminale spostandoti nella cartella principale e digitando:

1. bash
   g++ src/main.cpp src/sqlite3.c -o NomeProgetto


## Visualizzazione e Controllo del Database (Opzionale)

Poiché l'applicazione salva i dati in un file di database locale (`spese_personali.db`), puoi ispezionare visivamente le tabelle, i record inseriti e verificare le operazioni eseguite utilizzando un'interfaccia grafica gratuita e open-source come **DB Browser for SQLite**.

**Come ispezionare il DB:**
1. Scarica e installa [DB Browser for SQLite](https://sqlitebrowser.org/) (disponibile per Windows, macOS e Linux).
2. Avvia il programma.
3. Clicca sul pulsante **"Apri database"** (Open Database) in alto a sinistra.
4. Naviga nella cartella del progetto e seleziona il file `spese_personali.db` (generato automaticamente al primo avvio dell'app).
5. Esplora il database:
   * Vai nella scheda **"Sfoglia dati"** (Browse Data) e usa il menu a tendina per visualizzare i record effettivi delle tabelle `Categorie`, `Spese` e `Budget`.
   * Vai nella scheda **"Struttura database"** (Database Structure) per controllare lo schema delle tabelle, le chiavi primarie (PK) e i vincoli esterni (Foreign Keys e CHECK).

> **Nota:** Assicurati di non avere modifiche non salvate su DB Browser (pulsante "Scrivi modifiche") mentre il programma C++ è in esecuzione, per evitare errori di blocco del database (`database is locked`).