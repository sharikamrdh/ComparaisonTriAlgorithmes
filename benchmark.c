#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Génère un fichier de benchmark pour un type spécifique de tableau
 * @param nom: nom du fichier à créer
 * @param taille: taille des tableaux
 * @param type: type de tableau (croissant, decroissant, constant, etc.)
 * @param nb_instances: nombre d'instances à générer
 */
void generer_croissant(char *nom, int taille, int nb_instances) {
    FILE *fp = fopen(nom, "w");
    if (fp == NULL) {
        printf("Erreur lors de la création du fichier %s\n", nom);
        return;
    }
    
    fprintf(fp, "%d\n", taille);
    
    // Une seule instance suffit pour un tableau trié croissant (toujours identique)
    for (int i = 0; i < taille; i++) 
        fprintf(fp, "%d ", i);
    fprintf(fp, "\n");
    
    fclose(fp);
    printf("✓ %s créé (1 instance)\n", nom);
}

void generer_decroissant(char *nom, int taille, int nb_instances) {
    FILE *fp = fopen(nom, "w");
    if (fp == NULL) {
        printf("Erreur lors de la création du fichier %s\n", nom);
        return;
    }
    
    fprintf(fp, "%d\n", taille);
    
    // Une seule instance suffit pour un tableau trié décroissant (toujours identique)
    for (int i = 0; i < taille; i++) 
        fprintf(fp, "%d ", taille - i - 1);
    fprintf(fp, "\n");
    
    fclose(fp);
    printf("✓ %s créé (1 instance)\n", nom);
}

void generer_constant(char *nom, int taille, int nb_instances) {
    FILE *fp = fopen(nom, "w");
    if (fp == NULL) {
        printf("Erreur lors de la création du fichier %s\n", nom);
        return;
    }
    
    fprintf(fp, "%d\n", taille);
    
    // Une seule instance suffit pour un tableau constant (toujours identique)
    int val = 42; // Valeur constante
    for (int i = 0; i < taille; i++) 
        fprintf(fp, "%d ", val);
    fprintf(fp, "\n");
    
    fclose(fp);
    printf("✓ %s créé (1 instance)\n", nom);
}

void generer_petites_valeurs(char *nom, int taille, int nb_instances) {
    FILE *fp = fopen(nom, "w");
    if (fp == NULL) {
        printf("Erreur lors de la création du fichier %s\n", nom);
        return;
    }
    
    fprintf(fp, "%d\n", taille);
    
    // Garder plusieurs instances pour les valeurs aléatoires
    for (int inst = 0; inst < nb_instances; inst++) {
        for (int i = 0; i < taille; i++) 
            fprintf(fp, "%d ", rand() % 101);
        fprintf(fp, "\n");
    }
    
    fclose(fp);
    printf("✓ %s créé (%d instances)\n", nom, nb_instances);
}

void generer_grandes_valeurs(char *nom, int taille, int nb_instances) {
    FILE *fp = fopen(nom, "w");
    if (fp == NULL) {
        printf("Erreur lors de la création du fichier %s\n", nom);
        return;
    }
    
    fprintf(fp, "%d\n", taille);
    
    // Garder plusieurs instances pour les valeurs aléatoires
    for (int inst = 0; inst < nb_instances; inst++) {
        for (int i = 0; i < taille; i++) 
            fprintf(fp, "%d ", 10000 + rand() % 40001);
        fprintf(fp, "\n");
    }
    
    fclose(fp);
    printf("✓ %s créé (%d instances)\n", nom, nb_instances);
}

void generer_aleatoire(char *nom, int taille, int nb_instances) {
    FILE *fp = fopen(nom, "w");
    if (fp == NULL) {
        printf("Erreur lors de la création du fichier %s\n", nom);
        return;
    }
    
    fprintf(fp, "%d\n", taille);
    
    // Garder plusieurs instances pour les valeurs aléatoires
    for (int inst = 0; inst < nb_instances; inst++) {
        for (int i = 0; i < taille; i++) 
            fprintf(fp, "%d ", rand() % 1001);
        fprintf(fp, "\n");
    }
    
    fclose(fp);
    printf("✓ %s créé (%d instances)\n", nom, nb_instances);
}

int main()
{
    char nom[255];
    int taille;
    int nb_instances = 100; // Nombre d'instances de test par fichier
    
    // Initialiser le générateur aléatoire
    srand(time(NULL));
    
    printf("=== GÉNÉRATION DES FICHIERS DE BENCHMARK ===\n\n");
    
    // Types de tableaux
    char *types[] = {"croissant", "decroissant", "constant", "petites_valeurs", "grandes_valeurs", "aleatoire"};
    int nb_types = 6;
    
    // Générer des fichiers pour différentes tailles et types
    for (taille = 1000; taille <= 10000; taille += 1000) {
        printf("\nGénération pour taille %d:\n", taille);
        
        // Tableau croissant
        sprintf(nom, "benchmark_%d_croissant.txt", taille);
        generer_croissant(nom, taille, nb_instances);
        
        // Tableau décroissant
        sprintf(nom, "benchmark_%d_decroissant.txt", taille);
        generer_decroissant(nom, taille, nb_instances);
        
        // Tableau constant
        sprintf(nom, "benchmark_%d_constant.txt", taille);
        generer_constant(nom, taille, nb_instances);
        
        // Tableau avec petites valeurs
        sprintf(nom, "benchmark_%d_petites_valeurs.txt", taille);
        generer_petites_valeurs(nom, taille, nb_instances);
        
        // Tableau avec grandes valeurs
        sprintf(nom, "benchmark_%d_grandes_valeurs.txt", taille);
        generer_grandes_valeurs(nom, taille, nb_instances);
        
        // Tableau aléatoire
        sprintf(nom, "benchmark_%d_aleatoire.txt", taille);
        generer_aleatoire(nom, taille, nb_instances);
    }
    
    printf("\n=== GÉNÉRATION TERMINÉE ===\n");
    printf("\nNombre total de fichiers créés: %d\n", 10 * nb_types);
    printf("Chaque fichier contient %d instances de test\n", nb_instances);
    
    return 0;
}