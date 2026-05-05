CREATE TABLE IF NOT EXISTS Categorie (
nome TEXT PRIMARY KEY CHECK (nome <> ''));

CREATE TABLE IF NOT EXISTS Spese (
id INTEGER PRIMARY KEY AUTOINCREMENT,
data TEXT NOT NULL,
importo REAL NOT NULL CHECK (importo > 0),
categoria_nome TEXT NOT NULL,
descrizione TEXT,
FOREIGN KEY (categoria_nome) REFERENCES Categorie(nome));

CREATE TABLE IF NOT EXISTS Budget (
mese TEXT NOT NULL, --Formato YYYY-MM
categoria_nome TEXT NOT NULL,
importo REAL NOT NULL CHECK (importo > 0),
PRIMARY KEY (mese, categoria_nome),
FOREIGN KEY (categoria_nome) REFERENCES Categorie(nome));


--ESEMPIO DI INSERIMENTO
INSERT INTO Categorie (nome) VALUES ('Alimentari');
INSERT INTO Spese (data, importo, categoria_nome, descrizione) 
VALUES ('2025-05-01', 15.50, 'Alimentari', 'Spesa al supermercato');
INSERT OR REPLACE INTO Budget (mese, categoria_nome, importo) 
VALUES ('2025-05', 'Alimentari', 300.00);




-- ==========================================
-- SCRIPT DI CREAZIONE DATABASE E TABELLE
-- ==========================================

-- Tabella Categorie (Dimostrazione PRIMARY KEY e CHECK)
CREATE TABLE Categorie (
    nome VARCHAR(50) PRIMARY KEY,
    CHECK (nome <> '')
);

-- Tabella Spese (Dimostrazione AUTOINCREMENT, NOT NULL, CHECK, FOREIGN KEY)
CREATE TABLE Spese (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    data DATE NOT NULL,
    importo DECIMAL(10,2) NOT NULL CHECK (importo > 0),
    categoria_nome VARCHAR(50) NOT NULL,
    descrizione TEXT,
    FOREIGN KEY (categoria_nome) REFERENCES Categorie(nome)
);

-- Tabella Budget (Dimostrazione Chiave Primaria Composta, NOT NULL, CHECK, FOREIGN KEY)
CREATE TABLE Budget (
    mese VARCHAR(7) NOT NULL, 
    categoria_nome VARCHAR(50) NOT NULL,
    importo DECIMAL(10,2) NOT NULL CHECK (importo > 0),
    PRIMARY KEY (mese, categoria_nome),
    FOREIGN KEY (categoria_nome) REFERENCES Categorie(nome)
);

-- ==========================================
-- SCRIPT DI INSERIMENTO DATI DI ESEMPIO
-- ==========================================
INSERT INTO Categorie (nome) VALUES ('Alimentari'), ('Trasporti'), ('Svago');

INSERT INTO Spese (data, importo, categoria_nome, descrizione) 
VALUES ('2025-01-15', 25.00, 'Alimentari', 'Pranzo in mensa');
INSERT INTO Spese (data, importo, categoria_nome, descrizione) 
VALUES ('2025-01-20', 50.00, 'Trasporti', 'Abbonamento bus');

INSERT INTO Budget (mese, categoria_nome, importo) 
VALUES ('2025-01', 'Alimentari', 300.00);