# Lab 8 — Part D Pseudocode Analysis

## D1 — Search and scan pseudocode
**Answer:**

n es `count`, la cantidad de IDs que hay en `sortedIds`.

La operacion representativa de la primera parte es comparar `sortedIds[middle]` con `targetId`. En cada vuelta del WHILE se descarta mas o menos la mitad de los IDs que quedan (`first = middle + 1` o `last = middle - 1`), asi que en el peor caso, cuando el ID no esta, hace unas log n comparaciones. Esa parte es O(log n).

La operacion representativa de la segunda parte es revisar `isActive[index]`. El FOR pasa por los `count` elementos una vez, sin importar lo que paso en la busqueda, asi que esa parte es O(n).

Todo el procedimiento es O(log n) + O(n), y cuando n crece el termino n es el que domina, entonces el procedimiento completo es O(n).

Los costos no se multiplican porque los dos bloques no estan uno dentro del otro. El WHILE termina completo y despues empieza el FOR; cada vuelta del FOR no vuelve a ejecutar la busqueda. Los costos se multiplican cuando hay un loop anidado dentro de otro, aqui se hacen uno despues del otro, entonces se suman.

## D2 — Potential-conflict pseudocode
**Answer:**

n es `count`, la cantidad de actividades en `startTimes`.

La operacion representativa es comparar `startTimes[first]` con `startTimes[second]`.

`second` empieza en `first + 1` para no comparar una actividad contra si misma (siempre tendria la misma hora y daria un conflicto falso) y para que cada par se revise una sola vez. Si empezara en 0, el par A-B se contaria y despues tambien B-A.

En el caso que mas trabajo requiere (que siempre es el mismo porque los dos loops no se detienen antes) se hacen (n-1) + (n-2) + ... + 1 = n(n-1)/2 comparaciones. El termino que domina es n^2, entonces el procedimiento es O(n^2).

Si `count` se duplica, el trabajo se multiplica por casi 4. Por ejemplo con 4 actividades son 6 comparaciones y con 8 son 28; con 50 son 1225 y con 100 son 4950.
