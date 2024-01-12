#ifndef FINANCIAR_H
#define FINANCIAR_H

// Structura pentru o tranzacție (venit sau cheltuială)
typedef struct Transaction {
    char *tip; // Tipul tranzacției ("Venit" sau "Cheltuiala")
    double suma; // Suma tranzacției
    char *descriere; // Descrierea tranzacției
    struct Transaction *prev, *next; // Referințe la tranzacțiile anterioare și următoare
} Transaction;

// Structura pentru buget
typedef struct Budget {
    Transaction *incomeTransactions; // Lista tranzacțiilor de venit
    Transaction *expenseTransactions; // Lista tranzacțiilor de cheltuială
    double obiectivFinanciar; // Obiectivul financiar
} Budget;

// Structura pentru utilizator
typedef struct User {
    char nume[100]; // Numele utilizatorului
    Budget budget; // Bugetul utilizatorului
    double goal; // Obiectivul financiar al utilizatorului
} User;

// Declarațiile funcțiilor
void printMenu(); // Afișează meniul
void readString(char *str, int length); // Citește o șir de caractere de la intrare
void initializeBudget(Budget *budget); // Inițializează bugetul
void addTransaction(Budget *budget, const char *tip, double suma, const char *descriere); // Adaugă o tranzacție
void modifyIncome(Budget *budget, int index, double newSuma, const char *newDescriere); // Modifică un venit
void deleteIncome(Budget *budget, int index); // Șterge un venit
void modifyExpense(Budget *budget, int index, double newSuma, const char *newDescriere); // Modifică o cheltuială
void deleteExpense(Budget *budget, int index); // Șterge o cheltuială
void printTransactions(const Budget *budget); // Afișează tranzacțiile
void setFinancialGoal(Budget *budget, double obiectiv); // Setează obiectivul financiar
double calculateBalance(const Budget *budget); // Calculează balanța
void freeBudget(Budget *budget); // Eliberează memoria alocată pentru buget
void saveUserData(const User *user); // Salvează datele utilizatorului
int isReturningUser(const char *nume); // Verifică dacă utilizatorul este înregistrat
void loadUserData(User *user); // Încarcă datele utilizatorului
int hasAccount(const char *username); // Verifică dacă există un cont cu un anumit username
void removeAccount(const char *nume); // Șterge un cont de utilizator

#endif
