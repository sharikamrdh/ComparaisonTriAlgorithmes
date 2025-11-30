#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *test_file;
    
    printf("=== GENERATION DES GRAPHIQUES AVEC GNUPLOT ===\n\n");
    
    // Vérifier que resultats.csv existe
    test_file = fopen("resultats.csv", "r");
    if (test_file == NULL) {
        printf("ERREUR: Le fichier resultats.csv n'existe pas!\n");
        printf("Veuillez d'abord executer ./mesure_performance\n");
        return EXIT_FAILURE;
    }
    fclose(test_file);
    printf("✓ Fichier resultats.csv trouve\n\n");
    
    // Vérifier que gnuplot est installé
    //int gnuplot_check = system("gnuplot --version > /dev/null 2>&1");
    int gnuplot_check = system("/opt/local/bin/gnuplot --version > /dev/null 2>&1");
    if (gnuplot_check != 0) {
        printf("ERREUR: gnuplot n'est pas installe!\n");
        printf("Installation: sudo apt-get install gnuplot\n");
        printf("Alternative: utilisez visualisation.py avec Python\n");
        return EXIT_FAILURE;
    }
    printf("✓ gnuplot est installe\n\n");
    
    // Préparer l'en-tête
    system("head -1 resultats.csv > header.csv");
    
    // ========================================
    // Graphique 1 : Tableau ALÉATOIRE (arbitraire)
    // ========================================
    printf("Generation du graphique 1 : Tableau aleatoire (arbitraire)...\n");
    
    system("grep 'Tableau aléatoire' resultats.csv > temp_aleatoire.csv");
    system("cat header.csv temp_aleatoire.csv > data_aleatoire.csv");
    
    FILE *gp = fopen("script1.gp", "w");
    fprintf(gp, "set terminal png size 1200,800\n");
    fprintf(gp, "set output 'graphique_aleatoire.png'\n");
    fprintf(gp, "set title 'Tableaux aleatoires (arbitraires) - Cas moyen'\n");
    fprintf(gp, "set key outside right\n");
    fprintf(gp, "set xlabel 'Taille des tableaux'\n");
    fprintf(gp, "set ylabel 'Temps moyen (secondes)'\n");
    fprintf(gp, "set datafile separator ','\n");
    fprintf(gp, "set style data linespoints\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "plot 'data_aleatoire.csv' using 1:5 every 9 title 'Tri Bulle Basique' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::1 title 'Tri Bulle Optimisation' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::2 title 'Tri Bulle Arret' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::3 title 'Tri Cocktail' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::4 title 'Tri Selection' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::5 title 'Tri Insertion' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::6 title 'Tri Denombrement' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::7 title 'Tri Fusion' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::8 title 'Tri Rapide' with linespoints lw 2\n");
    fclose(gp);
    //system("gnuplot script1.gp");
    system("/opt/local/bin/gnuplot script1.gp");

    printf("✓ Fichier cree : graphique_aleatoire.png\n\n");
    
    // ========================================
    // Graphique 2 : Tableau TRIÉ CROISSANT
    // ========================================
    printf("Generation du graphique 2 : Tableau trie croissant...\n");
    
    system("grep 'Tableau trié croissant' resultats.csv > temp_croissant.csv");
    system("cat header.csv temp_croissant.csv > data_croissant.csv");
    
    gp = fopen("script2.gp", "w");
    fprintf(gp, "set terminal png size 1200,800\n");
    fprintf(gp, "set output 'graphique_croissant.png'\n");
    fprintf(gp, "set title 'Tableaux tries croissants - Meilleur cas'\n");
    fprintf(gp, "set key outside right\n");
    fprintf(gp, "set xlabel 'Taille des tableaux'\n");
    fprintf(gp, "set ylabel 'Temps moyen (secondes)'\n");
    fprintf(gp, "set datafile separator ','\n");
    fprintf(gp, "set style data linespoints\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "plot 'data_croissant.csv' using 1:5 every 9 title 'Tri Bulle Basique' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::1 title 'Tri Bulle Optimisation' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::2 title 'Tri Bulle Arret' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::3 title 'Tri Cocktail' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::4 title 'Tri Selection' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::5 title 'Tri Insertion' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::6 title 'Tri Denombrement' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::7 title 'Tri Fusion' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::8 title 'Tri Rapide' with linespoints lw 2\n");
    fclose(gp);
    //system("gnuplot script2.gp");
    system("/opt/local/bin/gnuplot script2.gp");
    printf("✓ Fichier cree : graphique_croissant.png\n\n");
    
    // ========================================
    // Graphique 3 : Tableau TRIÉ DÉCROISSANT
    // ========================================
    printf("Generation du graphique 3 : Tableau trie decroissant...\n");
    
    system("grep 'Tableau trié décroissant' resultats.csv > temp_decroissant.csv");
    system("cat header.csv temp_decroissant.csv > data_decroissant.csv");
    
    gp = fopen("script3.gp", "w");
    fprintf(gp, "set terminal png size 1200,800\n");
    fprintf(gp, "set output 'graphique_decroissant.png'\n");
    fprintf(gp, "set title 'Tableaux tries decroissants - Pire cas'\n");
    fprintf(gp, "set key outside right\n");
    fprintf(gp, "set xlabel 'Taille des tableaux'\n");
    fprintf(gp, "set ylabel 'Temps moyen (secondes)'\n");
    fprintf(gp, "set datafile separator ','\n");
    fprintf(gp, "set style data linespoints\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "plot 'data_decroissant.csv' using 1:5 every 9 title 'Tri Bulle Basique' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::1 title 'Tri Bulle Optimisation' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::2 title 'Tri Bulle Arret' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::3 title 'Tri Cocktail' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::4 title 'Tri Selection' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::5 title 'Tri Insertion' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::6 title 'Tri Denombrement' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::7 title 'Tri Fusion' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::8 title 'Tri Rapide' with linespoints lw 2\n");
    fclose(gp);
    //system("gnuplot script3.gp");
    system("/opt/local/bin/gnuplot script3.gp");
    printf("✓ Fichier cree : graphique_decroissant.png\n\n");
    
    // ========================================
    // Graphique 4 : Tableau CONSTANT
    // ========================================
    printf("Generation du graphique 4 : Tableau constant...\n");
    
    system("grep 'Tableau constant' resultats.csv > temp_constant.csv");
    system("cat header.csv temp_constant.csv > data_constant.csv");
    
    gp = fopen("script4.gp", "w");
    fprintf(gp, "set terminal png size 1200,800\n");
    fprintf(gp, "set output 'graphique_constant.png'\n");
    fprintf(gp, "set title 'Tableaux constants - Tous elements identiques'\n");
    fprintf(gp, "set key outside right\n");
    fprintf(gp, "set xlabel 'Taille des tableaux'\n");
    fprintf(gp, "set ylabel 'Temps moyen (secondes)'\n");
    fprintf(gp, "set datafile separator ','\n");
    fprintf(gp, "set style data linespoints\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "plot 'data_constant.csv' using 1:5 every 9 title 'Tri Bulle Basique' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::1 title 'Tri Bulle Optimisation' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::2 title 'Tri Bulle Arret' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::3 title 'Tri Cocktail' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::4 title 'Tri Selection' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::5 title 'Tri Insertion' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::6 title 'Tri Denombrement' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::7 title 'Tri Fusion' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::8 title 'Tri Rapide' with linespoints lw 2\n");
    fclose(gp);
    //system("gnuplot script4.gp");
    system("/opt/local/bin/gnuplot script4.gp");
    printf("✓ Fichier cree : graphique_constant.png\n\n");
    
    // ========================================
    // Graphique 5 : Tableau PETITES VALEURS
    // ========================================
    printf("Generation du graphique 5 : Tableau petites valeurs...\n");
    
    system("grep 'Tableau avec petites valeurs' resultats.csv > temp_petites.csv");
    system("cat header.csv temp_petites.csv > data_petites.csv");
    
    gp = fopen("script5.gp", "w");
    fprintf(gp, "set terminal png size 1200,800\n");
    fprintf(gp, "set output 'graphique_petites_valeurs.png'\n");
    fprintf(gp, "set title 'Tableaux avec petites valeurs [0-100]'\n");
    fprintf(gp, "set key outside right\n");
    fprintf(gp, "set xlabel 'Taille des tableaux'\n");
    fprintf(gp, "set ylabel 'Temps moyen (secondes)'\n");
    fprintf(gp, "set datafile separator ','\n");
    fprintf(gp, "set style data linespoints\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "plot 'data_petites.csv' using 1:5 every 9 title 'Tri Bulle Basique' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::1 title 'Tri Bulle Optimisation' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::2 title 'Tri Bulle Arret' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::3 title 'Tri Cocktail' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::4 title 'Tri Selection' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::5 title 'Tri Insertion' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::6 title 'Tri Denombrement' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::7 title 'Tri Fusion' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::8 title 'Tri Rapide' with linespoints lw 2\n");
    fclose(gp);
    //system("gnuplot script5.gp");
    //system("/opt/local/bin/gnuplot script5.gp");
    system("/opt/local/bin/gnuplot script5.gp");
    printf("✓ Fichier cree : graphique_petites_valeurs.png\n\n");
    
    // ========================================
    // Graphique 6 : Tableau GRANDES VALEURS
    // ========================================
    printf("Generation du graphique 6 : Tableau grandes valeurs...\n");
    
    system("grep 'Tableau avec grandes valeurs' resultats.csv > temp_grandes.csv");
    system("cat header.csv temp_grandes.csv > data_grandes.csv");
    
    gp = fopen("script6.gp", "w");
    fprintf(gp, "set terminal png size 1200,800\n");
    fprintf(gp, "set output 'graphique_grandes_valeurs.png'\n");
    fprintf(gp, "set title 'Tableaux avec grandes valeurs [10000-50000]'\n");
    fprintf(gp, "set key outside right\n");
    fprintf(gp, "set xlabel 'Taille des tableaux'\n");
    fprintf(gp, "set ylabel 'Temps moyen (secondes)'\n");
    fprintf(gp, "set datafile separator ','\n");
    fprintf(gp, "set style data linespoints\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "plot 'data_grandes.csv' using 1:5 every 9 title 'Tri Bulle Basique' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::1 title 'Tri Bulle Optimisation' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::2 title 'Tri Bulle Arret' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::3 title 'Tri Cocktail' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::4 title 'Tri Selection' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::5 title 'Tri Insertion' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::6 title 'Tri Denombrement' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::7 title 'Tri Fusion' with linespoints lw 2, \\\n");
    fprintf(gp, "'' using 1:5 every 9::8 title 'Tri Rapide' with linespoints lw 2\n");
    fclose(gp);
    //system("gnuplot script6.gp");
    system("/opt/local/bin/gnuplot script6.gp");
    printf("✓ Fichier cree : graphique_grandes_valeurs.png\n\n");
    
    // Nettoyage des fichiers temporaires
    system("rm -f temp_*.csv data_*.csv header.csv script*.gp");
    
    printf("=== GENERATION TERMINEE ===\n");
    printf("\n✓ TOUS LES 6 TYPES DE TABLEAUX COUVERTS :\n");
    printf("  1. graphique_aleatoire.png - Tableaux arbitraires\n");
    printf("  2. graphique_croissant.png - Tableaux tries croissants\n");
    printf("  3. graphique_decroissant.png - Tableaux tries decroissants\n");
    printf("  4. graphique_constant.png - Tableaux constants\n");
    printf("  5. graphique_petites_valeurs.png - Tableaux petites valeurs\n");
    printf("  6. graphique_grandes_valeurs.png - Tableaux grandes valeurs\n");
    
    return EXIT_SUCCESS;
}
