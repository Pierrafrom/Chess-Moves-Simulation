#include <stdio.h>

// Définition des constantes pour les types de pièces
#define  PAWN 1
#define  ROOK 2
#define  KNIGHT 3
#define  BISHOP 4
#define  QUEEN 5
#define  KING 6

// Définition de la taille de l'échiquier
#define SIZE 8

// Définition des constantes pour les couleurs des pièces
#define WHITE 0
#define BLACK 1

/**
 * @brief Initialise l'échiquier en le remplissant de caractères '*' signifiant des cases vides.
 *
 * Cette fonction parcourt chaque case de l'échiquier et lui attribue le caractère '*',
 * indiquant que la case est vide. C'est généralement utilisé pour préparer un échiquier
 * pour une nouvelle partie ou pour réinitialiser son état.
 *
 * @param tab Pointeur vers le début du tableau représentant l'échiquier.
 * @param full_size Nombre total d'éléments dans le tableau (c'est-à-dire la taille de l'échiquier, par exemple, 64 pour un échiquier 8x8).
 */
void clear_board(int *tab, int full_size) {
    // Boucle à travers chaque élément du tableau.
    for (int i = 0; i < full_size; i++) {
        // Accéder à l'élément i du tableau et le remplir avec '*'.
        // L'arithmétique des pointeurs est utilisée ici pour accéder à l'élément approprié.
        *(tab + i) = '*';
    }
}

/**
 * @brief Affiche l'échiquier sur la console.
 *
 * Cette fonction parcourt chaque case de l'échiquier et l'affiche sur la console.
 * Après chaque ligne de l'échiquier (après chaque SIZE éléments), un saut à la ligne est effectué.
 * Cela garantit que l'échiquier est affiché dans une structure 2D, comme un véritable échiquier.
 *
 * @param tab Pointeur vers le début du tableau représentant l'échiquier.
 * @param full_size Nombre total d'éléments dans le tableau (c'est-à-dire la taille de l'échiquier, par exemple, 64 pour un échiquier 8x8).
 */
void print_chess(const int *tab, int full_size) {
    // Boucle à travers chaque élément du tableau.
    for (int i = 0; i < full_size; i++) {
        // Affiche le caractère à la position i du tableau.
        // L'arithmétique des pointeurs est utilisée pour accéder à l'élément approprié.
        printf("%c ", *(tab + i));

        // Après chaque ligne de l'échiquier (chaque SIZE éléments), effectuer un saut à la ligne.
        // Cela permet d'afficher l'échiquier en format 2D.
        if ((i + 1) % SIZE == 0) {
            printf("\n");
        }
    }
}

/**
 * @brief Place une pièce sur l'échiquier à la position spécifiée.
 *
 * Cette fonction demande à l'utilisateur de spécifier une position valide
 * si la position initiale n'est pas valide. Elle utilise ensuite l'arithmétique
 * des pointeurs pour définir la pièce à la position appropriée sur l'échiquier.
 *
 * @param tab Pointeur vers le début du tableau représentant l'échiquier.
 * @param size Taille d'une dimension de l'échiquier (par exemple, 8 pour un échiquier 8x8).
 * @param x Coordonnée x de la position où placer la pièce.
 * @param y Coordonnée y de la position où placer la pièce.
 * @param piece Valeur numérique de la pièce à placer.
 */
void set_piece(int *tab, int size, int x, int y, int piece) {
    // Boucle jusqu'à ce que l'utilisateur entre une position valide.
    // Vérifie si x et y sont à l'intérieur des limites de l'échiquier.
    while (x < 0 || x > size - 1 || y < 0 || y > size - 1) {
        // Informe l'utilisateur que la position est non valide.
        printf("Position non valide\n");
        // Indique les limites valides pour x et y.
        printf("Veuillez entrer des valeurs entre 0 et %d\n", size - 1);
        // Demande à l'utilisateur de saisir à nouveau x.
        printf("x : ");
        scanf("%d", &x);
        // Demande à l'utilisateur de saisir à nouveau y.
        printf("\ny : ");
        scanf("%d", &y);
    }

    // Une fois une position valide obtenue, place la pièce à cette position.
    // Convertit la valeur numérique de la pièce en caractère (par exemple, 2 devient '2') et la place à la position (x,y) de l'échiquier.
    *(tab + x * size + y) = piece + '0';
}

/**
 * @brief Lit la valeur de la pièce à une position spécifiée de l'échiquier.
 *
 * Cette fonction utilise l'arithmétique des pointeurs pour accéder à la valeur
 * de la pièce située à la position (x, y) sur l'échiquier. La valeur retournée
 * est convertie en un nombre entier (par exemple, le caractère '2' est converti
 * en 2) pour faciliter le traitement ultérieur.
 *
 * @param tab Pointeur vers le début du tableau représentant l'échiquier.
 * @param size Taille d'une dimension de l'échiquier (par exemple, 8 pour un échiquier 8x8).
 * @param x Coordonnée x de la position à lire.
 * @param y Coordonnée y de la position à lire.
 * @return La valeur numérique de la pièce à la position (x,y).
 */
int read_square(const int *tab, int size, int x, int y) {
    // Utilise l'arithmétique des pointeurs pour accéder à la valeur à la position (x, y) de l'échiquier.
    // Convertit ensuite cette valeur en nombre entier et la retourne.
    return *(tab + x * size + y) - '0';
}

/**
 * @brief Détermine les mouvements possibles d'un pion sur un échiquier.
 *
 * Cette fonction est utilisée pour marquer les cases où un pion (soit blanc, soit noir)
 * peut se déplacer sur un échiquier. Elle prend en compte les règles spécifiques
 * des mouvements de pion, notamment le fait qu'un pion puisse avancer de deux cases
 * depuis sa position initiale.
 *
 * @param tab Pointeur vers le début du tableau représentant l'échiquier.
 * @param size Taille d'une dimension de l'échiquier (par exemple, 8 pour un échiquier 8x8).
 * @param x Coordonnée x de la position actuelle du pion.
 * @param y Coordonnée y de la position actuelle du pion.
 * @param color Couleur du pion (soit WHITE soit BLACK).
 */
void pawn_moves(int *tab, int size, int x, int y, int color) {
    if (color == WHITE) { // Si le pion est blanc
        if (x == 6) {
            // Si le pion blanc est à sa position initiale (ligne 6 pour un échiquier 8x8),
            // il peut avancer de deux cases.
            *(tab + (x - 1) * size + y) = '-'; // Marque la case immédiatement devant le pion.
            *(tab + (x - 2) * size + y) = '-'; // Marque la case deux positions devant le pion.
        } else if (x > 0) {
            // Si le pion blanc n'est pas sur la première ligne, il avance d'une seule case.
            *(tab + (x - 1) * size + y) = '-';
        }
    } else if (color == BLACK) { // Si le pion est noir
        if (x == 1) {
            // Si le pion noir est à sa position initiale (ligne 1 pour un échiquier 8x8),
            // il peut avancer de deux cases.
            *(tab + (x + 1) * size + y) = '-'; // Marque la case immédiatement devant le pion.
            *(tab + (x + 2) * size + y) = '-'; // Marque la case deux positions devant le pion.
        } else if (x < size - 1) {
            // Si le pion noir n'est pas sur la dernière ligne, il avance d'une seule case.
            *(tab + (x + 1) * size + y) = '-';
        }
    }
}

/**
 * @brief Détermine les mouvements possibles d'une tour sur un échiquier.
 *
 * Cette fonction est utilisée pour marquer les cases où une tour peut se déplacer
 * sur un échiquier. La tour a la capacité de se déplacer horizontalement ou verticalement
 * sur toute la longueur de l'échiquier, tant qu'il n'y a pas d'autre pièce bloquant
 * son chemin. Cependant, cette fonction ne prend pas en compte les éventuelles
 * obstructions et marque simplement toutes les cases possibles.
 *
 * @param tab Pointeur vers le début du tableau représentant l'échiquier.
 * @param size Taille d'une dimension de l'échiquier (par exemple, 8 pour un échiquier 8x8).
 * @param x Coordonnée x de la position actuelle de la tour.
 * @param y Coordonnée y de la position actuelle de la tour.
 */
void rook_moves(int *tab, int size, int x, int y) {
    for (int i = 0; i < size; i++) {
        if (i != x) {
            // Marquer les mouvements verticaux sauf la position actuelle de la tour
            *(tab + i * size + y) = '-';
        }
        if (i != y) {
            // Marquer les mouvements horizontaux sauf la position actuelle de la tour
            *(tab + x * size + i) = '-';
        }
    }
}

/**
 * @brief Affiche les mouvements possibles d'un cavalier sur un échiquier.
 *
 * Cette fonction utilise les mouvements typiques d'un cavalier (en forme de "L")
 * pour mettre à jour les positions possibles du mouvement sur l'échiquier.
 *
 * @param tab Pointeur vers le début du tableau représentant l'échiquier.
 * @param size Taille d'une rangée ou d'une colonne de l'échiquier (typiquement 8 pour un échiquier standard).
 * @param x Position x (rangée) actuelle du cavalier sur l'échiquier.
 * @param y Position y (colonne) actuelle du cavalier sur l'échiquier.
 */
void knight_moves(int *tab, int size, int x, int y) {
    // Liste des mouvements possibles d'un cavalier.
    // Un cavalier peut se déplacer de 2 cases dans une direction et 1 dans une autre (en forme de "L").
    int moves[8][2] = {
            {2,  1},
            {1,  2},
            {-1, 2},
            {-2, 1},
            {-2, -1},
            {-1, -2},
            {1,  -2},
            {2,  -1}
    };

    // Boucle à travers chacun des mouvements possibles.
    for (int i = 0; i < 8; i++) {
        // Calcul de la nouvelle position en ajoutant le mouvement actuel à la position actuelle du cavalier.
        int nx = x + moves[i][0];
        int ny = y + moves[i][1];

        // Vérification que la nouvelle position est valide (c'est-à-dire qu'elle est à l'intérieur de l'échiquier).
        if (nx >= 0 && nx < size && ny >= 0 && ny < size) {
            // Mise à jour de l'échiquier pour indiquer un mouvement possible du cavalier avec le caractère '-'.
            *(tab + nx * size + ny) = '-';
        }
    }
}

/**
 * @brief Affiche les mouvements possibles d'un fou sur un échiquier.
 *
 * Cette fonction utilise les mouvements diagonaux typiques d'un fou pour mettre
 * à jour les positions possibles du mouvement sur l'échiquier.
 *
 * @param tab Pointeur vers le début du tableau représentant l'échiquier.
 * @param size Taille d'une rangée ou d'une colonne de l'échiquier (typiquement 8 pour un échiquier standard).
 * @param x Position x (rangée) actuelle du fou sur l'échiquier.
 * @param y Position y (colonne) actuelle du fou sur l'échiquier.
 */
void bishop_moves(int *tab, int size, int x, int y) {
    // Boucle à travers chaque distance possible depuis la position actuelle du fou.
    // i représente le nombre de cases que le fou se déplace en diagonale.
    for (int i = 1; i < size; i++) {
        // Liste des directions diagonales possibles pour le fou.
        // Chaque direction est définie par un couple (dx, dy) où dx est le déplacement en rangée et dy est le déplacement en colonne.
        int directions[4][2] = {
                {i,  i},    // Diagonale haut-droite
                {i,  -i},   // Diagonale haut-gauche
                {-i, i},    // Diagonale bas-droite
                {-i, -i}    // Diagonale bas-gauche
        };

        // Boucle à travers chacune des directions diagonales.
        for (int j = 0; j < 4; j++) {
            // Calcul de la nouvelle position en ajoutant la direction actuelle à la position actuelle du fou.
            int nx = x + directions[j][0];
            int ny = y + directions[j][1];

            // Vérification que la nouvelle position est valide (c'est-à-dire qu'elle est à l'intérieur de l'échiquier).
            if (nx >= 0 && nx < size && ny >= 0 && ny < size) {
                // Mise à jour de l'échiquier pour indiquer un mouvement possible du fou avec le caractère '-'.
                *(tab + nx * size + ny) = '-';
            }
        }
    }
}

/**
 * @brief Affiche les mouvements possibles d'une reine sur un échiquier.
 *
 * Une reine combine les capacités de mouvement d'une tour et d'un fou.
 * Par conséquent, cette fonction utilise simplement les fonctions de mouvement de la tour et du fou pour
 * afficher tous les mouvements possibles de la reine sur l'échiquier.
 *
 * @param tab Pointeur vers le début du tableau représentant l'échiquier.
 * @param size Taille d'une rangée ou d'une colonne de l'échiquier (typiquement 8 pour un échiquier standard).
 * @param x Position x (rangée) actuelle de la reine sur l'échiquier.
 * @param y Position y (colonne) actuelle de la reine sur l'échiquier.
 */
void queen_moves(int *tab, int size, int x, int y) {
    // Appel de la fonction rook_moves pour afficher tous les mouvements possibles
    // de la reine en tant que tour (mouvements horizontaux et verticaux).
    rook_moves(tab, size, x, y);

    // Appel de la fonction bishop_moves pour afficher tous les mouvements possibles
    // de la reine en tant que fou (mouvements diagonaux).
    bishop_moves(tab, size, x, y);
}

/**
 * @brief Affiche les mouvements possibles d'un roi sur un échiquier.
 *
 * Le roi a la capacité unique de se déplacer d'une case dans n'importe quelle direction :
 * verticalement, horizontalement, ou diagonalement. Cette fonction utilise un tableau
 * de mouvements possibles pour vérifier chaque direction depuis la position actuelle
 * du roi et affiche les mouvements valides sur l'échiquier.
 *
 * @param tab Pointeur vers le début du tableau représentant l'échiquier.
 * @param size Taille d'une rangée ou d'une colonne de l'échiquier (typiquement 8 pour un échiquier standard).
 * @param x Position x (rangée) actuelle du roi sur l'échiquier.
 * @param y Position y (colonne) actuelle du roi sur l'échiquier.
 */
void king_moves(int *tab, int size, int x, int y) {
    // Tableau des déplacements possibles du roi. Chaque sous-tableau représente un mouvement
    // sous la forme {déplacement en x, déplacement en y}.
    int moves[8][2] = {
            {1,  1},  // Diagonale haut droit
            {1,  0},  // Verticalement vers le haut
            {1,  -1}, // Diagonale haut gauche
            {0,  -1}, // Horizontalement vers la gauche
            {-1, -1}, // Diagonale bas gauche
            {-1, 0},  // Verticalement vers le bas
            {-1, 1},  // Diagonale bas droit
            {0,  1}   // Horizontalement vers la droite
    };

    // Pour chaque direction possible...
    for (int i = 0; i < 8; i++) {
        // Calculer la nouvelle position (nx, ny) en ajoutant le mouvement à la position actuelle du roi
        int nx = x + moves[i][0];
        int ny = y + moves[i][1];

        // Vérifier si la nouvelle position est valide (c'est-à-dire qu'elle est à l'intérieur de l'échiquier).
        // Si c'est le cas, marquer cette position comme un mouvement valide (avec '-')
        if (nx >= 0 && nx < size && ny >= 0 && ny < size) {
            *(tab + nx * size + ny) = '-';
        }
    }
}

/**
 * @brief Affiche les mouvements possibles d'une pièce d'échecs donnée sur un échiquier.
 *
 * Cette fonction identifie le type de pièce présent sur une case donnée de l'échiquier
 * et, en fonction de cette pièce, appelle la fonction appropriée pour afficher ses
 * mouvements possibles.
 *
 * @param tab Pointeur vers le début du tableau représentant l'échiquier.
 * @param size Taille d'une rangée ou d'une colonne de l'échiquier (typiquement 8 pour un échiquier standard).
 * @param x Position x (rangée) actuelle de la pièce sur l'échiquier.
 * @param y Position y (colonne) actuelle de la pièce sur l'échiquier.
 * @param color Couleur de la pièce (important pour le pion qui se déplace différemment en fonction de sa couleur).
 */
void possible_movements(int *tab, int size, int x, int y, int color) {
    // Lire la pièce présente sur la case donnée de l'échiquier.
    int piece = read_square(tab, size, x, y);

    // En fonction de la pièce identifiée, appeler la fonction appropriée pour afficher ses mouvements possibles.
    switch (piece) {
        case PAWN: // Si c'est un pion...
            pawn_moves(tab, size, x, y, color);
            break;
        case ROOK: // Si c'est une tour...
            rook_moves(tab, size, x, y);
            break;
        case KNIGHT: // Si c'est un cavalier...
            knight_moves(tab, size, x, y);
            break;
        case BISHOP: // Si c'est un fou...
            bishop_moves(tab, size, x, y);
            break;
        case QUEEN: // Si c'est une reine...
            queen_moves(tab, size, x, y);
            break;
        case KING: // Si c'est un roi...
            king_moves(tab, size, x, y);
            break;
        default:
            // Si la case est vide (représentée par '*'), alors ne rien faire.
            break;
    }
}

int main() {
    // creation de l echiquier (8*8)
    int echiquier[SIZE * SIZE];
    clear_board(echiquier, SIZE * SIZE);

    // placement de la reine en (1,7)
    set_piece(echiquier, SIZE, 1, 1, PAWN);

    // mouvements possibles de la reine
    possible_movements(echiquier, SIZE, 1, 1, BLACK);

    // affichage de l echiquier
    print_chess(echiquier, SIZE * SIZE);

    return 0;
}
