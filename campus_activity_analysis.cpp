/*
 * Course: COEN 2220 - Programming 2
 * Name: Logan N. Ramirez Rodriguez
 * Lab: Lab 8 - Big-O / Time Complexity
 * Description: Resolved code for time-complexity analysis
 * Due date: 10/12/2026
 */

#include <iostream>
using namespace std;

/* Returns the ID stored at a valid position already known by the caller. */
int getActivityIdAt(const int activityIds[], int activityIndex)
{
    return activityIds[activityIndex]; // Read one known array position.
}

/* Returns how many activities have an active status. */
int countActiveActivities(const bool isActive[], int activityCount)
{
    int activeCount = 0;

    for (int index = 0; index < activityCount; index++)
    {
        if (isActive[index])
        {
            activeCount++;
        }
    }

    return activeCount;
}

/*
 * Returns how many middle IDs binary search compares before finding targetId.
 * Precondition: activityIds is sorted in ascending order and contains targetId.
 */
int countBinaryComparisons(const int activityIds[], int activityCount, int targetId)
{
    int first = 0;
    int last = activityCount - 1;
    int comparisons = 0;

    while (first <= last)
    {
        int middle = (first + last) / 2;
        comparisons++;

        if (activityIds[middle] == targetId)
        {
            break;
        }
        else if (activityIds[middle] < targetId)
        {
            first = middle + 1;
        }
        else
        {
            last = middle - 1;
        }
    }

    return comparisons;
}

/* Returns how many times a positive count can be reduced by half before reaching 1. */
int countHalvingSteps(int itemCount)
{
    int steps = 0;

    while (itemCount > 1)
    {
        itemCount = itemCount / 2; // Remove approximately half of the remaining items.
        steps++;
    }

    return steps;
}

/* Returns the number of distinct activity pairs visited by two nested loops. */
int countPossiblePairs(int activityCount)
{
    int pairCount = 0;

    for (int first = 0; first < activityCount; first++)
    {
        for (int second = first + 1; second < activityCount; second++)
        {
            pairCount++; // One distinct pair would be compared here.
        }
    }

    return pairCount;
}

int main()
{
    // These activity IDs are sorted so binary search is valid.
    int activityIds[] = {101, 104, 108, 115, 130, 136, 140, 155};
    bool isActive[] = {true, false, true, true, false, false, true, false};
    int activityCount = 8;

    cout << "Activity at index 2: "
         << getActivityIdAt(activityIds, 2) << endl;
    cout << "Active activities: "
         << countActiveActivities(isActive, activityCount) << endl;
    cout << "Binary comparisons for 140: "
         << countBinaryComparisons(activityIds, activityCount, 140) << endl;
    cout << "Halving steps for 8: " << countHalvingSteps(8) << endl;
    cout << "Halving steps for 16: " << countHalvingSteps(16) << endl;
    cout << "Halving steps for 32: " << countHalvingSteps(32) << endl;
    cout << "Possible pairs for 4 activities: " << countPossiblePairs(4) << endl;
    cout << "Possible pairs for 8 activities: " << countPossiblePairs(8) << endl;

    return 0;
}

/*
 * Analysis Answers
 *
 * C1 - Direct access
 * Answer:
 * n es la cantidad de actividades que hay en el arreglo.
 * Lo que se hace es leer una posicion del arreglo.
 * Es O(1). La funcion solo hace activityIds[activityIndex], una sola lectura,
 * y no tiene ningun loop. En main pide el indice 2 y devuelve 108. Si el arreglo
 * fuera mucho mas grande seguiria siendo una sola lectura.
 *
 * C2 - Count active activities
 * Answer:
 * n es activityCount, o sea cuantas actividades hay.
 * Lo que se hace es mirar cada isActive[index] para ver si es true.
 * Es O(n). Hay un loop que pasa por todas las actividades una vez. En main son 8
 * actividades, asi que mira 8 y encuentra 4 activas. Si hubiera el doble de
 * actividades miraria el doble.
 *
 * C3 - Binary search
 * Answer:
 * n es activityCount, la cantidad de IDs.
 * Lo que se hace es comparar el ID del medio con el que se busca.
 * Es O(log n). En cada vuelta del while se bota la mitad de los IDs que quedan,
 * y por eso casi no aumenta cuando n crece. En main buscar 140 se hizo en 3
 * comparaciones: primero 115, despues 136 y despues 140.
 * Los IDs tienen que estar ordenados de menor a mayor. Importa porque el
 * programa decide a que lado seguir buscando segun si el del medio es menor o
 * mayor. Si el arreglo esta desordenado puede botar la mitad donde si estaba el
 * numero y decir que no esta aunque si estaba.
 *
 * C4 - Halving steps
 * Answer:
 * Empezando en 16, itemCount va 16, 8, 4, 2, 1. Son 4 pasos.
 * Lo que se repite es dividir itemCount entre 2 y sumar 1 a steps.
 * Con 8 son 3 pasos, con 16 son 4 y con 32 son 5. Cada vez que el numero se
 * duplica solo se agrega 1 paso. Eso es O(log n).
 *
 * C5 - Distinct pairs
 * Answer:
 * El segundo loop empieza en first + 1 para no comparar una actividad con ella
 * misma y para no contar el mismo par dos veces (A con B y despues B con A).
 * Asi cada par se cuenta una sola vez.
 * Si empezara en 0 contaria n * n pares, o sea tambien las comparaciones con
 * ella misma y los pares repetidos. Con 4 actividades daria 16 en vez de 6.
 * La funcion es O(n^2). Hace n(n-1)/2 pares: 6 con 4 actividades y 28 con 8.
 *
 * C6 - Compare the observed patterns
 * Answer:
 * Acceso directo: una sola lectura (O(1)), no depende de cuantas actividades
 * haya.
 * Contar activas: un loop que revisa las 8 actividades (O(n)), crece parejo con
 * n.
 * Halving: dio 3, 4 y 5 pasos con 8, 16 y 32. La entrada se multiplico por 4 y
 * los pasos solo subieron 2 (O(log n)).
 * Pares: 6 con 4 actividades y 28 con 8. Al duplicar n los pares se multiplicaron
 * por mas de 4 (O(n^2)).
 * Del que menos crece al que mas crece: O(1), O(log n), O(n), O(n^2).
 *
 * C7 - Sorting decision
 * Answer:
 * Si los IDs llegan desordenados y solo voy a buscar una vez, o pocas veces,
 * uso linear search sin ordenar. Cuesta O(n), y ordenar primero cuesta mas
 * (selection sort es O(n^2) porque repite recorridos), asi que no vale la pena
 * por una sola busqueda.
 * Si voy a buscar muchas veces en los mismos datos si conviene ordenar una vez.
 * Ese costo se paga una sola vez y despues cada busqueda pasa de O(n) a O(log n).
 * Mientras mas busquedas hagas mas se nota la ganancia.
 *
 */
