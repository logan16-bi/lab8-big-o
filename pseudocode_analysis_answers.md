# Lab 8 — Part D Pseudocode Analysis

## D1 — Search and scan pseudocode
**Answer:**

n es `count`, la cantidad de IDs.

La primera parte es una busqueda binaria. Lo que se hace es comparar `sortedIds[middle]` con `targetId`. En cada vuelta del WHILE se bota la mitad de los IDs que quedan, asi que en el peor caso (cuando el ID no esta) hace como log n comparaciones. Esa parte es O(log n).

La segunda parte es un FOR que mira `isActive[index]` para todos los elementos, una vez cada uno. Esa parte es O(n).

Todo el procedimiento es O(log n) + O(n). Cuando n crece, la parte de n es la que manda, asi que en total es O(n).

No se multiplican porque no estan uno dentro del otro. El WHILE termina completo y despues empieza el FOR, y el FOR no repite la busqueda en cada vuelta. Cuando son uno despues del otro se suman. Se multiplican solo cuando hay un loop dentro de otro loop.

## D2 — Potential-conflict pseudocode
**Answer:**

n es `count`, la cantidad de actividades.

Lo que se cuenta es comparar `startTimes[first]` con `startTimes[second]`.

`second` empieza en `first + 1` para no comparar una actividad con ella misma (siempre tendria la misma hora y daria un conflicto falso) y para que cada par se revise una sola vez. Si empezara en 0, el par A-B se contaria y despues B-A tambien.

En el peor caso se hacen (n-1) + (n-2) + ... + 1 = n(n-1)/2 comparaciones. El termino que manda es n^2, asi que es O(n^2).

Si `count` se duplica, el trabajo se multiplica por casi 4. Por ejemplo con 4 actividades son 6 comparaciones y con 8 son 28. Con 50 son 1225 y con 100 son 4950.
