#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "financiar.h"

// Funcție pentru afișarea meniului
void printMenu() {
    printf("\n======== Budget Planner Dashboard ========\n");
    printf("1. Adauga Venit\n");
    printf("2. Adauga Cheltuiala\n");
    printf("3. Afiseaza Tranzactii\n");
    printf("4. Afiseaza Balanta Curenta\n");
    printf("5. Modifica Venit\n");
    printf("6. Sterge Venit\n");
    printf("7. Modifica Cheltuiala\n");
    printf("8. Sterge Cheltuiala\n");
    printf("9. Seteaza Obiectiv Financiar\n");
    printf("10. Afiseaza Obiectiv si Perioada\n");
    printf("11. Sterge Cont\n");
    printf("12. Iesire\n");
    printf("==========================================\n");
    printf("Alege o optiune: ");
}

// Funcție pentru citirea unui șir de caractere de la tastatură
void readString(char *str, int length) {
    fgets(str, length, stdin);
    str[strcspn(str, "\n")] = 0; // Elimină newline
}

int main() {
    User user;
    initializeBudget(&user.budget);

    printf("Introdu numele tau: ");
    readString(user.nume, sizeof(user.nume));

    if (isReturningUser(user.nume)) {
        printf("Bine ai revenit, %s!\n", user.nume);
        loadUserData(&user);
    } else {
        printf("Bine ai venit, %s!\n", user.nume);
    }

    double obiectivFinanciar;
    printf("Introdu obiectivul tau financiar: ");
    scanf("%lf", &obiectivFinanciar);
    getchar();

    double venitLunar;
    printf("Care este venitul tau lunar mediu? ");
    scanf("%lf", &venitLunar);

    if (venitLunar > 0) {
        double luniNecesare = obiectivFinanciar / venitLunar;
        printf("Vei atinge obiectivul tau financiar in aproximativ %.2f luni.\n", luniNecesare);
    } else {
        printf("Introdu un venit lunar valid pentru a calcula timpul necesar.\n");
    }

    double balantaCurenta = calculateBalance(&user.budget);

    while (1) {
        printMenu();
        int optiune;
        double suma;
        char descriere[256];
        int index;

        scanf("%d", &optiune);
        getchar();

        switch (optiune) {
            case 1:
                printf("Suma venit: ");
                scanf("%lf", &suma);
                getchar(); // Elimină newline
                printf("Descriere: ");
                readString(descriere, sizeof(descriere));
                addTransaction(&user.budget, "Venit", suma, descriere);
                balantaCurenta = calculateBalance(&user.budget);
                printf("Balanta curenta actualizata: %.2f\n", balantaCurenta);
                if (balantaCurenta >= obiectivFinanciar) {
                    printf("Obiectivul financiar a fost atins!\n");
                }
                break;
            case 2:
                printf("Suma cheltuiala: ");
                scanf("%lf", &suma);
                getchar(); // Elimină newline
                printf("Descriere: ");
                readString(descriere, sizeof(descriere));
                addTransaction(&user.budget, "Cheltuiala", suma, descriere);
                balantaCurenta = calculateBalance(&user.budget);
                printf("Balanta curenta actualizata: %.2f\n", balantaCurenta);
                if (balantaCurenta >= obiectivFinanciar) {
                    printf("Obiectivul financiar a fost atins!\n");
                }
                break;
            case 3:
                printTransactions(&user.budget);
                break;
            case 4:
                printf("Balanta curenta: %.2f\n", balantaCurenta);
                break;
            case 5:
                printf("Indexul venitului de modificat: ");
                scanf("%d", &index);
                getchar(); // Elimină newline
                printf("Suma noua pentru venit: ");
                scanf("%lf", &suma);
                getchar(); // Elimină newline
                printf("Noua descriere pentru venit: ");
                readString(descriere, sizeof(descriere));
                modifyIncome(&user.budget, index, suma, descriere);
                balantaCurenta = calculateBalance(&user.budget);
                printf("Balanta curenta actualizata: %.2f\n", balantaCurenta);
                if (balantaCurenta >= obiectivFinanciar) {
                    printf("Obiectivul financiar a fost atins!\n");
                }
                break;
            case 6:
                printf("Indexul venitului de sters: ");
                scanf("%d", &index);
                getchar();
                deleteIncome(&user.budget, index);
                balantaCurenta = calculateBalance(&user.budget);
                printf("Balanta curenta actualizata: %.2f\n", balantaCurenta);
                if (balantaCurenta >= obiectivFinanciar) {
                    printf("Obiectivul financiar a fost atins!\n");
                }
                break;
            case 7:
                printf("Indexul cheltuielii de modificat: ");
                scanf("%d", &index);
                getchar();
                printf("Suma noua pentru cheltuiala: ");
                scanf("%lf", &suma);
                getchar();
                printf("Noua descriere pentru cheltuiala: ");
                readString(descriere, sizeof(descriere));
                modifyExpense(&user.budget, index, suma, descriere);
                balantaCurenta = calculateBalance(&user.budget);
                printf("Balanta curenta actualizata: %.2f\n", balantaCurenta);
                if (balantaCurenta >= obiectivFinanciar) {
                    printf("Obiectivul financiar a fost atins!\n");
                }
                break;
            case 8:
                printf("Indexul cheltuielii de sters: ");
                scanf("%d", &index);
                getchar();
                deleteExpense(&user.budget, index);
                balantaCurenta = calculateBalance(&user.budget);
                printf("Balanta curenta actualizata: %.2f\n", balantaCurenta);
                if (balantaCurenta >= obiectivFinanciar) {
                    printf("Obiectivul financiar a fost atins!\n");
                }
                break;
            case 9:
                printf("Introdu obiectivul tau financiar: ");
                scanf("%lf", &obiectivFinanciar);
                setFinancialGoal(&user.budget, obiectivFinanciar);
                break;
            case 10:
                printf("Obiectiv financiar: %.2f\n", user.budget.obiectivFinanciar);
                double luniNecesare;
                if (venitLunar > 0) {
                    balantaCurenta = calculateBalance(&user.budget);
                    if (balantaCurenta >= obiectivFinanciar) {
                        printf("Obiectivul financiar a fost atins!\n");
                    } else {
                        luniNecesare = (obiectivFinanciar - balantaCurenta) / venitLunar;
                        printf("Vei atinge obiectivul tau financiar in aproximativ %.2f luni.\n", luniNecesare);
                    }
                } else {
                    printf("Introdu un venit lunar valid pentru a calcula timpul necesar.\n");
                }
                break;
            case 11:
                printf("Esti sigur ca vrei sa stergi contul? (Da/Nu): ");
                char raspuns[10];
                readString(raspuns, sizeof(raspuns));

                if (strcmp(raspuns, "da") == 0) {
                    // Efectuăm ștergerea contului
                    freeBudget(&user.budget);
                    printf("Contul a fost sters. Iesire din program...\n");
                    exit(0);
                } else if (strcmp(raspuns, "nu") == 0) {
                    printf("Stergerea contului a fost anulata.\n");
                } else {
                    printf("Raspuns invalid. Stergerea contului a fost anulata.\n");
                }
                break;
            case 12:
                saveUserData(&user);
                printf("Datele au fost salvate. Iesire din program...\n");
                freeBudget(&user.budget);
                exit(0);
            default:
                printf("Optiune invalida. Te rog sa alegi din nou.\n");
        }
    }

    return 0;
}
