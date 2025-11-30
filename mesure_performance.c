#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <float.h>

// ============= ALGORITHMES DE TRI =============

// Tri à bulles - Version basique
void tri_bulle_basique(int *tab, int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (tab[j] > tab[j + 1]) {
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
}

// Tri à bulles - Optimisation de boucle
void tri_bulle_optimisation(int *tab, int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (tab[j] > tab[j + 1]) {
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
}

// Tri à bulles - Optimisation d'arrêt
void tri_bulle_arret(int *tab, int n) {
    int temp;
    bool echanger = true;
    int i = 0;
    
    while (i < n - 1 && echanger) {
        echanger = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (tab[j] > tab[j + 1]) {
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
                echanger = true;
            }
        }
        i++;
    }
}

// Tri par sélection
void tri_selection(int *tab, int taille) {
    int temp, indice_min;
    for (int i = 0; i < taille - 1; i++) {
        indice_min = i;
        for (int j = i + 1; j < taille; j++) {
            if (tab[j] < tab[indice_min]) {
                indice_min = j;
            }
        }
        temp = tab[i];
        tab[i] = tab[indice_min];
        tab[indice_min] = temp;
    }
}

// Tri par insertion
void tri_insertion(int *tab, int taille) {
    int temp, j;
    for (int i = 1; i < taille; i++) {
        temp = tab[i];
        j = i - 1;
        while (j >= 0 && tab[j] > temp) {
            tab[j + 1] = tab[j];
            j--;
        }
        tab[j + 1] = temp;
    }
}

// Tri cocktail
void tri_cocktail(int *tab, int taille) {
    bool echange = true;
    int debut = 0;
    int fin = taille - 1;
    int tmp;
    
    while (echange) {
        echange = false;
        // Parcours de gauche à droite
        for (int i = debut; i < fin; i++) {
            if (tab[i] > tab[i + 1]) {
                tmp = tab[i];
                tab[i] = tab[i + 1];
                tab[i + 1] = tmp;
                echange = true;
            }
        }
        fin--;
        
        if (!echange) break;
        
        echange = false;
        // Parcours de droite à gauche
        for (int i = fin; i > debut; i--) {
            if (tab[i] < tab[i - 1]) {
                tmp = tab[i];
                tab[i] = tab[i - 1];
                tab[i - 1] = tmp;
                echange = true;
            }
        }
        debut++;
    }
}

// Tri par dénombrement
void tri_denombrement(int *tab, int taille) {
    // Trouver la valeur maximale
    int max = tab[0];
    for (int i = 1; i < taille; i++) {
        if (tab[i] > max) {
            max = tab[i];
        }
    }
    
    // Créer et initialiser le tableau de comptage
    int *comptage = (int*)calloc(max + 1, sizeof(int));
    
    // Compter les occurrences
    for (int i = 0; i < taille; i++) {
        comptage[tab[i]]++;
    }
    
    // Reconstruire le tableau trié
    int index = 0;
    for (int i = 0; i <= max; i++) {
        for (int j = 0; j < comptage[i]; j++) {
            tab[index] = i;
            index++;
        }
    }
    
    free(comptage);
}

// Fonction de fusion pour le tri fusion
int* fusion(int *tab1, int *tab2, int taille1, int taille2) {
    int *tab = (int*)malloc(sizeof(int) * (taille1 + taille2));
    int i = 0, j = 0, k = 0;
    
    while (i < taille1 && j < taille2) {
        if (tab1[i] < tab2[j]) {
            tab[k] = tab1[i];
            i++;
        } else {
            tab[k] = tab2[j];
            j++;
        }
        k++;
    }
    
    // Si tab2 est vide, copier le reste de tab1
    while (i < taille1) {
        tab[k] = tab1[i];
        k++;
        i++;
    }
    
    // Si tab1 est vide, copier le reste de tab2
    while (j < taille2) {
        tab[k] = tab2[j];
        k++;
        j++;
    }
    
    return tab;
}

// Tri fusion (version récursive originale)
int* tri_fusion_recursif(int *tab, int taille) {
    // --- Cas de base ---
    if (taille == 1) {
        int *res = (int*)malloc(sizeof(int));
        res[0] = tab[0];
        return res;
    }
    
    // --- Division du tableau ---
    int milieu = taille / 2;
    int taille1 = milieu;
    int taille2 = taille - milieu;

    // Création des sous-tableaux T1 et T2
    int *tab1 = (int*)malloc(sizeof(int) * taille1);
    int *tab2 = (int*)malloc(sizeof(int) * taille2);

    for (int i = 0; i < taille1; i++) tab1[i] = tab[i];
    for (int i = 0; i < taille2; i++) tab2[i] = tab[i + milieu];

    // --- Appels récursifs ---
    int *tab1_trie = tri_fusion_recursif(tab1, taille1);
    int *tab2_trie = tri_fusion_recursif(tab2, taille2);

    // --- Fusion des résultats ---
    int *tab_trie = fusion(tab1_trie, tab2_trie, taille1, taille2);

    // Libération mémoire temporaire
    free(tab1);
    free(tab2);
    free(tab1_trie);
    free(tab2_trie);

    return tab_trie;
}

// Tri fusion (version wrapper pour compatibilité avec mesurer_temps)
void tri_fusion_wrapper(int *tab, int taille) {
    if (taille <= 1) return;
    
    int *tab_trie = tri_fusion_recursif(tab, taille);
    
    // Copier le résultat dans le tableau original
    for (int i = 0; i < taille; i++) {
        tab[i] = tab_trie[i];
    }
    
    free(tab_trie);
}

// Fonction de partition pour le tri rapide
int partition(int *tab, int debut, int fin) {
    int val_pivot = tab[fin];
    int i = debut - 1;
    
    for (int j = debut; j < fin; j++) {
        if (tab[j] <= val_pivot) {
            i++;
            int temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp;
        }
    }
    
    int temp = tab[i + 1];
    tab[i + 1] = tab[fin];
    tab[fin] = temp;
    
    return i + 1;
}

// Tri rapide (fonction récursive)
void tri_rapide_recursif(int *tab, int debut, int fin) {
    if (fin - debut <= 0) return; // cas de base
    
    int indice_pivot = partition(tab, debut, fin); // partitionner
    tri_rapide_recursif(tab, debut, indice_pivot - 1);        // tri gauche
    tri_rapide_recursif(tab, indice_pivot + 1, fin);          // tri droite
}

// Tri rapide (version wrapper pour compatibilité avec mesurer_temps)
void tri_rapide(int *tab, int taille) {
    if (taille > 1) {
        tri_rapide_recursif(tab, 0, taille - 1);
    }
}

// ============= FONCTIONS UTILITAIRES =============

// Fonction pour dupliquer un tableau
int* copier_tableau(int *source, int taille) {
    int *copie = (int*)malloc(taille * sizeof(int));
    for (int i = 0; i < taille; i++) {
        copie[i] = source[i];
    }
    return copie;
}

// Fonction pour lire un tableau depuis un fichier
int* lire_ligne_tableau(FILE *fp, int taille) {
    int *tab = (int*)malloc(taille * sizeof(int));
    for (int i = 0; i < taille; i++) {
        fscanf(fp, "%d", &tab[i]);
    }
    return tab;
}

// Fonction pour mesurer le temps d'exécution d'un tri
double mesurer_temps(void (*fonction_tri)(int*, int), int *tab, int taille) {
    clock_t debut, fin;
    int *copie = copier_tableau(tab, taille);
    
    debut = clock();
    fonction_tri(copie, taille);
    fin = clock();
    
    free(copie);
    return (double)(fin - debut) / CLOCKS_PER_SEC;
}

// Structure pour stocker les résultats
typedef struct {
    double temps_min;
    double temps_max;
    double temps_moyen;
    int nb_executions;
} ResultatTri;

// Fonction pour analyser un fichier benchmark
ResultatTri analyser_benchmark(void (*fonction_tri)(int*, int), char *nom_fichier) {
    FILE *fp = fopen(nom_fichier, "r");
    ResultatTri resultat = {DBL_MAX, 0.0, 0.0, 0};
    
    if (fp == NULL) {
        printf("Erreur: impossible d'ouvrir %s\n", nom_fichier);
        return resultat;
    }
    
    int taille;
    fscanf(fp, "%d", &taille);
    
    double somme_temps = 0.0;
    int nb_tableaux = 0;
    int **tableaux_lus = NULL;
    int nb_lignes_lues = 0;
    
    // Lire tous les tableaux du fichier
    while (!feof(fp)) {
        int *tab = lire_ligne_tableau(fp, taille);
        
        // Vérifier si on a vraiment lu un tableau valide
        if (feof(fp)) {
            free(tab);
            break;
        }
        
        // Stocker le tableau
        tableaux_lus = (int**)realloc(tableaux_lus, (nb_lignes_lues + 1) * sizeof(int*));
        tableaux_lus[nb_lignes_lues] = tab;
        nb_lignes_lues++;
    }
    
    fclose(fp);
    
    // Si une seule instance (tableaux déterministes), la mesurer plusieurs fois
    int nb_mesures = (nb_lignes_lues == 1) ? 100 : nb_lignes_lues;
    
    for (int i = 0; i < nb_mesures; i++) {
        // Choisir le tableau (toujours le premier si une seule instance)
        int *tab = tableaux_lus[i % nb_lignes_lues];
        
        // Mesurer le temps
        double temps = mesurer_temps(fonction_tri, tab, taille);
        
        // Mettre à jour les statistiques
        if (temps < resultat.temps_min) resultat.temps_min = temps;
        if (temps > resultat.temps_max) resultat.temps_max = temps;
        somme_temps += temps;
        nb_tableaux++;
    }
    
    resultat.temps_moyen = somme_temps / nb_tableaux;
    resultat.nb_executions = nb_tableaux;
    
    // Libérer la mémoire
    for (int i = 0; i < nb_lignes_lues; i++) {
        free(tableaux_lus[i]);
    }
    free(tableaux_lus);
    
    return resultat;
}

// ============= PROGRAMME PRINCIPAL =============

int main() {
    // Liste des algorithmes à tester
    typedef struct {
        char nom[50];
        void (*fonction)(int*, int);
    } Algorithme;
    
    Algorithme algos[] = {
        {"Tri Bulle Basique", tri_bulle_basique},
        {"Tri Bulle Optimisation", tri_bulle_optimisation},
        {"Tri Bulle Arret", tri_bulle_arret},
        {"Tri Cocktail", tri_cocktail},
        {"Tri Selection", tri_selection},
        {"Tri Insertion", tri_insertion},
        {"Tri Denombrement", tri_denombrement},
        {"Tri Fusion", tri_fusion_wrapper},
        {"Tri Rapide", tri_rapide}
    };
    
    int nb_algos = 9;
    
    // Types de tableaux à tester
    typedef struct {
        char nom[50];
        char suffixe[50];
    } TypeTableau;
    
    TypeTableau types[] = {
        {"Tableau trié croissant", "croissant"},
        {"Tableau trié décroissant", "decroissant"},
        {"Tableau constant", "constant"},
        {"Tableau avec petites valeurs", "petites_valeurs"},
        {"Tableau avec grandes valeurs", "grandes_valeurs"},
        {"Tableau aléatoire", "aleatoire"}
    };
    
    int nb_types = 6;
    
    // Fichier de résultats CSV
    FILE *resultats = fopen("resultats.csv", "w");
    fprintf(resultats, "Taille,Type_Tableau,Algorithme,Temps_Min,Temps_Max,Temps_Moyen\n");
    
    printf("=== MESURE DES PERFORMANCES ===\n\n");
    
    // Tester chaque taille
    for (int taille = 1000; taille <= 10000; taille += 1000) {
        
        // Tester chaque type de tableau
        for (int t = 0; t < nb_types; t++) {
            char nom_fichier[100];
            sprintf(nom_fichier, "benchmark_%d_%s.txt", taille, types[t].suffixe);
            
            printf("\nAnalyse pour taille %d...\n", taille);
            printf("Avec %s\n", types[t].nom);
            
            // Tester chaque algorithme
            for (int i = 0; i < nb_algos; i++) {
                printf("  - %s... ", algos[i].nom);
                fflush(stdout);
                
                ResultatTri res = analyser_benchmark(algos[i].fonction, nom_fichier);
                
                printf("Min: %.6fs | Max: %.6fs | Moy: %.6fs\n", 
                       res.temps_min, res.temps_max, res.temps_moyen);
                
                // Enregistrer dans le CSV
                fprintf(resultats, "%d,%s,%s,%.6f,%.6f,%.6f\n",
                        taille, types[t].nom, algos[i].nom, 
                        res.temps_min, res.temps_max, res.temps_moyen);
            }
        }
        printf("\n%s\n", "========================================");
    }
    
    fclose(resultats);
    
    printf("\n=== ANALYSE TERMINÉE ===\n");
    printf("Résultats sauvegardés dans: resultats.csv\n");
    
    return 0;
}