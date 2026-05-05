#include <iostream>
#include <string>
#include "sqlite3.h"

using namespace std;

// Prototipi delle funzioni per i moduli
void inizializzaDB(sqlite3* db);
void gestisciCategorie(sqlite3* db);
void inserisciSpesa(sqlite3* db);
void definisciBudget(sqlite3* db);
void visualizzaReport(sqlite3* db);

int main() {
    sqlite3* db;
    // Apertura del database (crea il file se non esiste)
    int rc = sqlite3_open("spese_personali.db", &db);
    if (rc) {
        cerr << "Errore nell'apertura del DB: " << sqlite3_errmsg(db) << endl;
        return 1;
    }
    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", 0, 0, 0);
    inizializzaDB(db);
    cout << "Benvenuto nel Sistema Gestione Spese Personali!" << endl;


    int scelta = 0;
    while (scelta != 5) {
        cout << "\n-------------------------\n";
        cout << "SISTEMA SPESE PERSONALI\n";
        cout << "-------------------------\n";
        cout << "1. Gestione Categorie\n";
        cout << "2. Inserisci Spesa\n";
        cout << "3. Definisci Budget Mensile\n";
        cout << "4. Visualizza Report\n";
        cout << "5. Esci\n";
        cout << "-------------------------\n";
        cout << "Inserisci la tua scelta: ";

        cin >> scelta;

        switch (scelta) {
            case 1:
                gestisciCategorie(db);
                break;
            case 2:
                inserisciSpesa(db);
                break;
            case 3:
                definisciBudget(db);
                break;
            case 4:
                visualizzaReport(db);
                break;
            case 5:
                cout << "Chiusura del programma in corso. Arrivederci!" << endl;
                break;
            default:
                cout << "Scelta non valida. Riprovare." << endl;
        }
    }

    sqlite3_close(db);
    return 0;
}

void gestisciCategorie(sqlite3* db) {
    string nomeCategoria;

    cout << "\n--- INSERIMENTO NUOVA CATEGORIA ---" << endl;
    cout << "Inserisci il nome della categoria (es. Alimentari): ";
    cin >> nomeCategoria;

    // Controllo che non sia vuoto (anche se cin salta gli spazi bianchi di base)
    if (nomeCategoria.empty()) {
        cout << "Errore: il nome della categoria non puo' essere vuoto." << endl;
        return;
    }

    // Costruiamo la query SQL: INSERT INTO Categorie (nome) VALUES ('nomeCategoria');
    string sql = "INSERT INTO Categorie (nome) VALUES ('" + nomeCategoria + "');";
    char* messaggioErrore = nullptr;

    // Eseguiamo la query sul database
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &messaggioErrore);

    // Controlliamo il risultato
    if (rc != SQLITE_OK) {
        // Se c'è un errore (es. la categoria esiste già violando la PRIMARY KEY)
        cout << "Errore: La categoria esiste gia' o dato non valido." << endl;
        sqlite3_free(messaggioErrore);
    } else {
        cout << "Successo: Categoria inserita correttamente!" << endl;
    }
}

void inserisciSpesa(sqlite3* db) {
    string data, categoria, descrizione;
    double importo;

    cout << "\n--- INSERIMENTO NUOVA SPESA ---" << endl;

    cout << "Inserisci la data (Formato YYYY-MM-DD, es. 2025-01-15): ";
    cin >> data;

    cout << "Inserisci l'importo (es. 25.50): ";
    cin >> importo;

    // Validazione richiesta dalla traccia
    if (importo <= 0) {
        cout << "Errore: l'importo deve essere maggiore di zero." << endl;
        return; // Interrompe la funzione e torna al menu
    }

    cout << "Inserisci il nome della categoria: ";
    cin >> categoria;

    cout << "Inserisci una descrizione facoltativa: ";
    // cin.ignore() serve per "pulire" la memoria dalla pressione del tasto Invio precedente,
    // altrimenti getline salta l'input!
    cin.ignore();
    getline(cin, descrizione);

    // Costruiamo la query SQL unendo le stringhe e convertendo l'importo in testo
    string sql = "INSERT INTO Spese (data, importo, categoria_nome, descrizione) VALUES ('"
                 + data + "', " + to_string(importo) + ", '" + categoria + "', '" + descrizione + "');";

    char* messaggioErrore = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &messaggioErrore);

    if (rc != SQLITE_OK) {
        // Se la categoria non esiste, la FOREIGN KEY blocca l'inserimento e finiamo qui
        cout << "Errore: la categoria inserita non esiste nel database." << endl;
        sqlite3_free(messaggioErrore);
    } else {
        cout << "Successo: Spesa inserita correttamente!" << endl;
    }
}

void definisciBudget(sqlite3* db) {
    string mese, categoria;
    double importo;

    cout << "\n--- DEFINIZIONE BUDGET MENSILE ---" << endl;
    cout << "Inserisci il mese (Formato YYYY-MM, es. 2025-01): ";
    cin >> mese;

    cout << "Inserisci la categoria (es. Alimentari): ";
    cin >> categoria;

    cout << "Inserisci l'importo del budget: ";
    cin >> importo;

    if (importo <= 0) {
        cout << "Errore: il budget deve essere maggiore di zero." << endl;
        return;
    }

    // INSERT OR REPLACE inserisce o aggiorna in automatico!
    string sql = "INSERT OR REPLACE INTO Budget (mese, categoria_nome, importo) VALUES ('"
                 + mese + "', '" + categoria + "', " + to_string(importo) + ");";

    char* messaggioErrore = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &messaggioErrore);

    if (rc != SQLITE_OK) {
            cout << "ERRORE REALE DEL DATABASE: ";
            if (messaggioErrore != nullptr) {
                cout << messaggioErrore << endl;
            } else {
                cout << "Errore sconosciuto" << endl;
            }
            sqlite3_free(messaggioErrore);
        } else {
            cout << "Successo: Budget mensile salvato correttamente!" << endl;
        }
}


void visualizzaReport(sqlite3* db) {
    int sceltaReport = 0;

    while (sceltaReport != 4) {
        cout << "\n--- MENU REPORT ---" << endl;
        cout << "1. Totale spese per categoria\n";
        cout << "2. Spese mensili vs budget\n";
        cout << "3. Elenco completo delle spese\n";
        cout << "4. Ritorna al menu principale\n";
        cout << "Inserisci la tua scelta: ";
        cin >> sceltaReport;

        if (sceltaReport == 1) {
            // REPORT 1
            string sql = "SELECT categoria_nome, SUM(importo) FROM Spese GROUP BY categoria_nome;";
            sqlite3_stmt* stmt;
            sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

            cout << "\nCategoria\tTotale Speso" << endl;
            cout << "----------------------------" << endl;
            // sqlite3_step va avanti riga per riga nei risultati
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                cout << sqlite3_column_text(stmt, 0) << "\t\t" << sqlite3_column_double(stmt, 1) << endl;
            }
            sqlite3_finalize(stmt); // Chiude la query
        }
        else if (sceltaReport == 2) {
            // REPORT 2: Query avanzata con LEFT JOIN
            string sql = "SELECT B.mese, B.categoria_nome, B.importo, IFNULL(SUM(S.importo), 0) "
                         "FROM Budget B LEFT JOIN Spese S "
                         "ON B.categoria_nome = S.categoria_nome AND strftime('%Y-%m', S.data) = B.mese "
                         "GROUP BY B.mese, B.categoria_nome;";
            sqlite3_stmt* stmt;
            sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

            cout << "\n--- SPESE VS BUDGET ---" << endl;
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                // Estraiamo i dati indicando il numero della colonna (0, 1, 2, 3...)
                const unsigned char* mese = sqlite3_column_text(stmt, 0);
                const unsigned char* cat = sqlite3_column_text(stmt, 1);
                double budget = sqlite3_column_double(stmt, 2);
                double speso = sqlite3_column_double(stmt, 3);

                cout << "Mese: " << mese << "\nCategoria: " << cat
                     << "\nBudget: " << budget << "\nSpeso: " << speso << endl;

                // Controllo logico del superamento
                if (speso > budget) {
                    cout << "Stato: SUPERAMENTO BUDGET\n" << endl;
                } else {
                    cout << "Stato: IN REGOLA\n" << endl;
                }
            }
            sqlite3_finalize(stmt);
        }
        else if (sceltaReport == 3) {
            // REPORT 3
            string sql = "SELECT data, categoria_nome, importo, descrizione FROM Spese ORDER BY data DESC;";
            sqlite3_stmt* stmt;
            sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

            cout << "\nData\t\tCategoria\tImporto\tDescrizione" << endl;
            cout << "---------------------------------------------------" << endl;
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                // Leggiamo la descrizione (gestendo il caso in cui sia vuota/NULL)
                const unsigned char* desc = sqlite3_column_text(stmt, 3);
                string descrizione_testo = (desc != nullptr) ? (const char*)desc : "";

                cout << sqlite3_column_text(stmt, 0) << "\t"
                     << sqlite3_column_text(stmt, 1) << "\t\t"
                     << sqlite3_column_double(stmt, 2) << "\t"
                     << descrizione_testo << endl;
            }
            sqlite3_finalize(stmt);
        }
        else if (sceltaReport != 4) {
            cout << "Scelta non valida." << endl;
        }
    }
}

void inizializzaDB(sqlite3* db) {
	char* messaggioErrore = nullptr;

    // Stringa SQL con i vincoli richiesti (PRIMARY KEY, FOREIGN KEY, CHECK, UNIQUE)
    const char* sql =
        "CREATE TABLE IF NOT EXISTS Categorie ("
        "nome TEXT PRIMARY KEY CHECK (nome <> ''));"

        "CREATE TABLE IF NOT EXISTS Spese ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "data TEXT NOT NULL,"
        "importo REAL NOT NULL CHECK (importo > 0),"
        "categoria_nome TEXT NOT NULL,"
        "descrizione TEXT,"
        "FOREIGN KEY (categoria_nome) REFERENCES Categorie(nome));"

        "CREATE TABLE IF NOT EXISTS Budget ("
        "mese TEXT NOT NULL," // Formato YYYY-MM
        "categoria_nome TEXT NOT NULL,"
        "importo REAL NOT NULL CHECK (importo > 0),"
        "PRIMARY KEY (mese, categoria_nome),"
        "FOREIGN KEY (categoria_nome) REFERENCES Categorie(nome));";

    // Esecuzione del comando SQL
    int rc = sqlite3_exec(db, sql, 0, 0, &messaggioErrore);

    if (rc != SQLITE_OK) {
        cerr << "Errore nella creazione delle tabelle: " << messaggioErrore << endl;
        sqlite3_free(messaggioErrore);
    } else {
        cout << "Database inizializzato correttamente!" << endl;
    }
}
