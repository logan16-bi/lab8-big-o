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
 * n es la cantidad de actividades que hay en el arreglo activityIds.
 * La operacion representativa es leer un elemento del arreglo por su indice.
 * Es O(1): la funcion hace una sola lectura, activityIds[activityIndex], sin ningun
 * loop. En main se pide el indice 2 y devuelve 108 con una lectura; si el arreglo
 * tuviera 8000 actividades seguiria siendo una sola lectura.
 *
 * C2 - Count active activities
 * Answer:
 * n es activityCount, la cantidad de actividades que se revisan.
 * La operacion representativa es revisar isActive[index] para ver si es true.
 * Es O(n): hay un solo loop que va de 0 hasta activityCount - 1 y revisa cada
 * actividad una vez. En main son 8 actividades, entonces 8 revisiones, y el
 * resultado fue 4 activas. Si activityCount se duplica, las revisiones tambien.
 *
 * C3 - Binary search
 * Answer:
 * n es activityCount, la cantidad de IDs en el arreglo.
 * La operacion representativa es comparar el ID del medio con targetId
 * (comparisons++ en cada vuelta del while).
 * Es O(log n): en cada vuelta se descarta aproximadamente la mitad de los IDs
 * (first = middle + 1 o last = middle - 1). En main, buscar 140 en 8 IDs tomo 3
 * comparaciones: el medio fue 115, despues 136 y despues 140.
 * Requisito: los IDs tienen que estar ordenados de menor a mayor. Importa porque
 * el algoritmo decide cual mitad descartar suponiendo que si el ID del medio es
 * menor que el target, el target solo puede estar a la derecha. Si el arreglo
 * no esta ordenado puede descartar la mitad donde si estaba el ID y decir que no
 * existe aunque este en el arreglo.
 *
 * C4 - Halving steps
 * Answer:
 * Con itemCount = 16 los valores son 16, 8, 4, 2, 1. Son 4 pasos hasta llegar a 1.
 * La operacion que se repite es itemCount = itemCount / 2 junto con steps++.
 * Con 8 son 3 pasos, con 16 son 4 y con 32 son 5 (el output de main). Cada vez
 * que itemCount se duplica solo se agrega 1 paso. Eso es O(log n): para que el
 * numero de pasos suba 1 hay que duplicar la entrada.
 *
 * C5 - Distinct pairs
 * Answer:
 * El segundo loop empieza en first + 1 para no comparar una actividad contra si
 * misma y para no contar el mismo par dos veces (el par A-B y despues B-A). Asi
 * cada par distinto se visita una sola vez.
 * Si empezara en 0 se visitarian n * n pares: incluiria las comparaciones de una
 * actividad con ella misma y cada par repetido al reves, o sea mas del doble de
 * los pares reales. Con 4 actividades daria 16 en vez de 6.
 * La funcion es O(n^2): hace n(n-1)/2 visitas, 6 con 4 actividades y 28 con 8,
 * y el termino que domina es n^2.
 *
 * C6 - Compare the observed patterns
 * Answer:
 * Acceso directo (O(1)): una sola lectura del indice 2, sin loop, y el costo no
 * depende de n.
 * Contar activas (O(n)): un loop que revisa las 8 actividades, el trabajo crece
 * a la par de n.
 * Halving (O(log n)): 3, 4 y 5 pasos para 8, 16 y 32. La entrada se cuadruplica
 * de 8 a 32 pero los pasos solo suben de 3 a 5.
 * Pares (O(n^2)): 6 pares con 4 actividades y 28 con 8. Al duplicar n los pares
 * se multiplican por mas de 4 (6 * 4 = 24, y salieron 28).
 * Del que menos crece al que mas crece: O(1), O(log n), O(n), O(n^2).
 *
 * C7 - Sorting decision
 * Answer:
 * Si los IDs llegan desordenados y solo voy a buscar una vez, o muy pocas veces,
 * prefiero linear search sin ordenar: cuesta O(n) y ordenar primero cuesta mas
 * que eso (selection sort es O(n^2) porque recorre varias veces la parte que
 * falta ordenar), asi que el sorting nunca se paga con una sola busqueda.
 * Si voy a hacer muchas busquedas sobre los mismos datos si puede valer la pena
 * ordenar una sola vez. Ese costo se paga una vez y despues cada busqueda baja
 * de O(n) a O(log n). Mientras mas busquedas hay, mas se reparte el costo de
 * ordenar entre todas. Tambien hay que ordenar de nuevo si se agregan datos
 * desordenados, entonces conviene cuando los datos casi no cambian.
 *
 */
