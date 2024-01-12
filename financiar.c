#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "financiar.h"

// Funcție pentru a crea o nouă tranzacție
static Transaction* createTransaction(const char *tip, double suma, const char *descriere) {
        // Alocă memorie pentru noua tranzacție și inițializează câmpurile
    Transaction *newTransaction = (Transaction*)malloc(sizeof(Transaction));
    newTransaction->tip = strdup(tip); // Copiază tipul tranzacției
    newTransaction->suma = suma; // Setează suma tranzacției
    newTransaction->descriere = strdup(descriere); // Copiază descrierea tranzacției
    newTransaction->prev = newTransaction->next = NULL; // Inițializează legăturile către alte tranzacții
    return newTransaction;
}

// Inițializează un buget
void initializeBudget(Budget *budget) {
    // Setează listele de tranzacții și obiectivul financiar la valorile inițiale
    budget->incomeTransactions = NULL;
    budget->expenseTransactions = NULL;
    budget->obiectivFinanciar = 0.0;
}

// Adaugă o tranzacție în buget
void addTransaction(Budget *budget, const char *tip, double suma, const char *descriere) {
      // Creează o nouă tranzacție și o adaugă în lista corespunzătoare de tranzacții
    Transaction *newTransaction = createTransaction(tip, suma, descriere);
// Verifică tipul tranzacției și o adaugă în lista corespunzătoare
    if (strcmp(tip, "Venit") == 0) {
            // Adaugă tranzacția la venituri
        newTransaction->next = budget->incomeTransactions;
        if (budget->incomeTransactions != NULL)
            budget->incomeTransactions->prev = newTransaction;
        budget->incomeTransactions = newTransaction;
    } else if (strcmp(tip, "Cheltuiala") == 0) {
        // Adaugă tranzacția la cheltuieli
        newTransaction->next = budget->expenseTransactions;
        if (budget->expenseTransactions != NULL)
            budget->expenseTransactions->prev = newTransaction;
        budget->expenseTransactions = newTransaction;
    }
}
// Printează tranzacțiile din buget
void printTransactions(const Budget *budget) {
    // Parcurge și afișează tranzacțiile de venit
    Transaction *current = budget->incomeTransactions;
    printf("Venituri:\n");
    while (current != NULL) {
        printf("Venit: %.2f, Descriere: %s\n", current->suma, current->descriere);
        current = current->next;
    }
 // Parcurge și afișează tranzacțiile de cheltuială
    current = budget->expenseTransactions;
    printf("Cheltuieli:\n");
    while (current != NULL) {
        printf("Cheltuiala: %.2f, Descriere: %s\n", current->suma, current->descriere);
        current = current->next;
    }
}
// Setează un obiectiv financiar pentru buget
void setFinancialGoal(Budget *budget, double obiectiv) {
    budget->obiectivFinanciar = obiectiv; // Actualizează obiectivul financiar al bugetului
}
// Calculează balanța actuală a bugetului
double calculateBalance(const Budget *budget) {
    double incomeBalance = 0.0;
    double expenseBalance = 0.0;
       // Calculează suma totală a veniturilor
    Transaction *current = budget->incomeTransactions;
    while (current != NULL) {
        incomeBalance += current->suma;
        current = current->next;
    }
  // Calculează suma totală a cheltuielilor
    current = budget->expenseTransactions;
    while (current != NULL) {
        expenseBalance += current->suma;
        current = current->next;
    }
 // Returnează diferența dintre venituri și cheltuieli
    return incomeBalance - expenseBalance;
}
// Modifică o tranzacție de venit existentă în buget
void modifyIncome(Budget *budget, int index, double newSuma, const char *newDescriere) {
    Transaction *current = budget->incomeTransactions; // Pointer la prima tranzacție de venit
    int currentIndex = 0;
    // Parcurge lista de venituri până când găsește indexul dorit sau sfârșitul listei
    while (current != NULL && currentIndex < index) {
        current = current->next;// Mergi la următoarea tranzacție
        currentIndex++;
    }
// Dacă tranzacția este găsită, o modifică
    if (current != NULL) {
        current->suma = newSuma;
        free(current->descriere);
        current->descriere = strdup(newDescriere);
    } else {
        printf("Venitul cu indexul %d nu exista.\n", index);
    }
}
// Șterge o tranzacție de venit din buget
void deleteIncome(Budget *budget, int index) {
    Transaction *current = budget->incomeTransactions;
    int currentIndex = 0;
    // Parcurge lista de venituri până când găsește indexul dorit sau sfârșitul listei
    while (current != NULL && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }
    // Dacă tranzacția este găsită, o șterge
    if (current != NULL) {
        if (current->prev != NULL) {
            current->prev->next = current->next;
        } else {
            budget->incomeTransactions = current->next;
        }

        if (current->next != NULL) {
            current->next->prev = current->prev;
        }

        free(current->tip);
        free(current->descriere);
        free(current);
    } else {
        printf("Venitul cu indexul %d nu exista.\n", index);
    }
}
// Modifică o tranzacție de cheltuială existentă în buget
void modifyExpense(Budget *budget, int index, double newSuma, const char *newDescriere) {
    Transaction *current = budget->expenseTransactions;
    int currentIndex = 0;

    while (current != NULL && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }

    if (current != NULL) {
        current->suma = newSuma;
        free(current->descriere);
        current->descriere = strdup(newDescriere);
    } else {
        printf("Cheltuiala cu indexul %d nu exista.\n", index);
    }
}
// Șterge o tranzacție de cheltuială în funcție de index
void deleteExpense(Budget *budget, int index) {
    Transaction *current = budget->expenseTransactions;
    int currentIndex = 0;

    while (current != NULL && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }

    if (current != NULL) {
        if (current->prev != NULL) {
            current->prev->next = current->next;
        } else {
            budget->expenseTransactions = current->next;
        }

        if (current->next != NULL) {
            current->next->prev = current->prev;
        }

        free(current->tip);
        free(current->descriere);
        free(current);
    } else {
        printf("Cheltuiala cu indexul %d nu exista.\n", index);
    }
}
// Eliberează memoria alocată pentru toate tranzacțiile din buget
void freeBudget(Budget *budget) {
    Transaction *current = budget->incomeTransactions;
    while (current != NULL) {
        Transaction *next = current->next;
        free(current->descriere);
        free(current->tip);
        free(current);
        current = next;
    }

    current = budget->expenseTransactions;
    while (current != NULL) {
        Transaction *next = current->next;
        free(current->descriere);
        free(current->tip);
        free(current);
        current = next;
    }
}
// Salvează datele utilizatorului într-un fișier
void saveUserData(const User *user) {
    FILE *file = fopen("Date_utilizatori.txt", "a");
    if (file == NULL) {
        printf("Eroare la deschiderea fisierului.\n");
        return;
    }

    fprintf(file, "Utilizator: %s\n", user->nume);
    fprintf(file, "Balanta curenta: %.2f\n", calculateBalance(&user->budget));
    fprintf(file, "Obiectiv financiar: %.2f\n", user->goal);

    // Adăugarea detaliilor despre venituri
    Transaction *current = user->budget.incomeTransactions;
    while (current != NULL) {
        fprintf(file, "Venit: %.2f, Descriere: %s\n", current->suma, current->descriere);
        current = current->next;
    }

    // Adăugarea detaliilor despre cheltuieli
    current = user->budget.expenseTransactions;
    while (current != NULL) {
        fprintf(file, "Cheltuiala: %.2f, Descriere: %s\n", current->suma, current->descriere);
        current = current->next;
    }

    fclose(file);
}
// Verifică dacă un utilizator este întors
int isReturningUser(const char *nume) {
    FILE *file = fopen("Date_utilizatori.txt", "r");
    if (file == NULL) {
        return 0; // Fișierul nu există, deci utilizatorul este nou
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strstr(buffer, nume) != NULL) {
            fclose(file);
            return 1; // Numele utilizatorului a fost găsit în fișier
        }
    }

    fclose(file);
    return 0; // Numele utilizatorului nu a fost găsit
}
// Încarcă datele utilizatorului din fișier
void loadUserData(User *user) {
    FILE *file = fopen("Date_utilizatori.txt", "r");
    if (file == NULL) {
        printf("Nu s-a putut deschide fisierul pentru citire.\n");
        return;
    }

    char buffer[1024];
    int foundUser = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strstr(buffer, user->nume) != NULL) {
            foundUser = 1;
            sscanf(buffer, "%*s %lf", &user->goal);
            // Continuam să citim și să adăugam tranzacțiile utilizatorului
            while (fgets(buffer, sizeof(buffer), file)) {
                if (strstr(buffer, "Cheltuiala") != NULL || strstr(buffer, "Venit") != NULL) {
                    double suma;
                    char descriere[256];
                    sscanf(buffer, "%*s %lf, Descriere: %[^\n]", &suma, descriere);
                    // Adăugați tranzacția în buget
                    if (strstr(buffer, "Cheltuiala")) {
                        addTransaction(&user->budget, "Cheltuiala", suma, descriere);
                    } else {
                        addTransaction(&user->budget, "Venit", suma, descriere);
                    }
                }
            }
            break;
        }
    }

    if (!foundUser) {
        printf("Utilizatorul nu a fost gasit in fisier.\n");
    }

    fclose(file);
}
// Șterge un cont de utilizator
void removeAccount(const char *nume) {
    FILE *inputFile = fopen("Date_utilizatori.txt", "r");
    if (inputFile == NULL) {
        printf("Eroare la deschiderea fisierului pentru citire.\n");
        return;
    }

    FILE *tempFile = fopen("Temp_utilizatori.txt", "w");
    if (tempFile == NULL) {
        printf("Eroare la crearea fisierului temporar.\n");
        fclose(inputFile);
        return;
    }

    char buffer[1024];
    int foundUser = 0;
    char currentUser[256];

    while (fgets(buffer, sizeof(buffer), inputFile)) {
        if (strstr(buffer, "Utilizator:") != NULL) {
            sscanf(buffer, "Utilizator: %[^\n]", currentUser);
            if (strcmp(currentUser, nume) == 0) {
                // Am găsit utilizatorul, nu copiem această linie în fișierul temporar
                foundUser = 1;
                continue;
            }
        }
        fputs(buffer, tempFile);
    }

    fclose(inputFile);
    fclose(tempFile);

    if (!foundUser) {
        printf("Utilizatorul nu a fost gasit in fisier.\n");
        remove("Temp_utilizatori.txt"); // Ștergem fișierul temporar
        return;
    }

    // Înlocuim fișierul original cu fișierul temporar
    if (rename("Temp_utilizatori.txt", "Date_utilizatori.txt") == 0) {
        printf("Contul utilizatorului a fost sters cu succes.\n");
    } else {
        printf("Eroare la stergerea contului utilizatorului.\n");
    }
}

