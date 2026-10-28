#include <stdio.h>
#include <stdlib.h>

//Funcion que lee la caja: caja[i][j] es la moneda del espacio (i, j), o 0 si esta vacio
int **leerCaja(int f, int c){
    int **caja = malloc(f * sizeof(int *));
    for(int i = 0; i < f; i++){
        caja[i] = malloc(c * sizeof(int));
        for(int j = 0; j < c; j++){
            scanf("%d", &caja[i][j]);
        }
    }
    for (int i = 0; i < f; i ++){
        free(caja[i]);
    }
    free(caja);
    return caja;
}

//Funcion que revisa si cada fila tiene al menos tanta plata como la siguiente
int estaOrdenada(int *plata, int f){
    int ordenada = 1;
    for(int i = 0; i < f - 1; i++){
        if(plata[i] < plata[i + 1]){
            ordenada = 0;
        }
    }
    return ordenada;
}

//Programa para revisar la caja de monedas
int main(){
    int f, c;
    scanf("%d %d", &f, &c);
    int **caja = leerCaja(f, c);

    int *plata = malloc(f * sizeof(int));
    int *monedas = malloc(f * sizeof(int));
    int *promedio = malloc(f * sizeof(int));
    for(int i = 0; i < f; i++){
        plata[i] = 0;
        monedas[i] = 0;
        for(int j = 0; j < c; j++){
            if(caja[i][j] > 0){
                plata[i] += caja[i][j];
                monedas[i]++;
            }
        }
        //Promedio solo se calcula si la fila tiene monedas (division por 0)
        if(monedas[i] > 0){
            promedio[i] = plata[i] / monedas[i];
        }
        printf("Fila %d: $%d (%d monedas)\n", i + 1, plata[i], monedas[i]);
    }

    int grandes = 0;
    for(int i = 0; i < f; i++){
       promedio[i]=0;
       if(promedio[i] >= 100 && monedas[i] > 0){
            grandes++;
        }
    }
    printf("Filas de monedas grandes: %d\n", grandes);

    if(estaOrdenada(plata, f)){
        printf("Caja ordenada: Si\n");
    }
    else{
        printf("Caja ordenada: No\n");
    }

    //acum[i] es la plata que hay en las primeras i filas (acum[0] = 0)
    int *acum = malloc((f+1) * sizeof(int));
    acum[0] = 0;
    for(int i = 0; i < f; i++){
        acum[i + 1] = acum[i] + plata[i];
    }

    int q;
    scanf("%d", &q);
    for(int k = 0; k < q; k++){
        int precio;
        scanf("%d", &precio);
        int fila = 1;
        while(fila <= f && acum[fila] < precio){
            fila++;
        }
        if(fila <= f){
            printf("Compra %d: hasta la fila %d\n", k + 1, fila);
        }
        else{
            printf("Compra %d: no alcanza\n", k + 1);
        }
    }

    free(acum);
    free(promedio);
    free(monedas);
    free(plata);
    return 0;
}

