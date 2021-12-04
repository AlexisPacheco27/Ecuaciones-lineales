/* 
 * File:   main.cpp
 * Author: Alexis Pacheco
 *
 * Created on 11 de noviembre de 2021, 05:13 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Prototipos
int menu(void);
void newton(void);
void solucion(float*, int);
void imprime_coeficientes(float*, int);
float *leen(float*, int);
void descartes(float*, int);
void grafica(int, int, int);
int *genera_factores(float, int*, int*);
void imprime_factores(int*, int);
float divide(float*, float, int);
float doblediv(float*, float, int);
void r_enteras(float*, int*, int, int);
void r_reales(float*, int*, int, int);
int gauss(float**, int, int, int*);
float **lee(float**, int, int*);
void imprime(float**, int, int);
void resultado(float**, int, int);
void determinante(void);
void sistecuaciones(void);
void caracteristico(void);
void resultado1(float*, int);
void multiplica(float**, float*, int);
void acomoda(float**, float*, int, int);

int main(){
    setbuf(stdout, NULL);
    int x;
    do{
        x = menu();
        getchar();
    }while(x < 3);
    return 0;
    return (EXIT_SUCCESS);
}

int menu(){
    int x;
    printf("    MENU    \n");
    printf("1. Solucion de ecuaciones lineales.\n");
    printf("2. Calculo del determinante.\n");
    printf("3. Solucion de polinomios. \n");
    printf("4. Ecuacion caracteristica, valores caracteristicos. \n");
    printf("5. Salir.\n");
    printf("Seleccione una opcion: \n");
    scanf("%d",&x);
    switch(x){
        case 1:
            sistecuaciones();
            break;
        case 2:
            determinante();
            break;
        case 3:
            newton();
            break;
        case 4:
            caracteristico();
            break;
        case 5:
            break;
    }
    return (x);
}

void newton(){
    float *polinomio = NULL;
    int grado_del_polinomio;
    printf("Digite el grado del polinomio:");
    scanf("%d", &grado_del_polinomio);
    polinomio = leen(polinomio, grado_del_polinomio);
    solucion(polinomio, grado_del_polinomio);
}

void solucion(float *polinomio, int grado_del_polinomio){
    printf("EL POLINOMIO QUE ME DISTE ES: \n");
    imprime_coeficientes(polinomio, grado_del_polinomio);
    descartes(polinomio, grado_del_polinomio);
    int *factores = NULL;
    int num_factores = 0;
    factores = genera_factores(*(polinomio + grado_del_polinomio), factores, &num_factores);
    imprime_factores(factores, num_factores);
    r_enteras(polinomio, factores, grado_del_polinomio, num_factores);
    r_reales(polinomio, factores, grado_del_polinomio, num_factores);
}

void imprime_coeficientes(float *p, int n){
    int i;
    for(i = 0; i <= n; i++){
        printf("(%f)X**%d", *(p + i), n - i);
        if(i <= n - 1)
            printf("+");
    }
}

void descartes(float *p, int n){
    int i, cont = 0;
    float a[n], *pmenos;
    pmenos = a;
    if(n % 2 == 0){
        cont = 1;
    }
    for(i = 0; i <= n; i++){
        *(pmenos + i) = *(p + i);
    }
    do{
        *(pmenos + cont) = -(*(p + cont));
        cont += 2;
    }while(cont < n);
    printf("\nEL POLINOMIO NEGATIVO ES:\n");
    imprime_coeficientes(pmenos, n);
    int pos = 0, neg = 0;
    for(i = 0; i < n; i++){
        if((*(p + i))*(*(p + i + 1)) < 0)
            pos++;
        if((*(pmenos + i))*(*(pmenos + i + 1)) < 0)
            neg++;
    }
    grafica(pos, neg, n);
}

void grafica(int p, int n, int grado) {
    int comp1 = 0, comp2 = 0, p2 = p, n2 = n;
    if (p > 2)
        p2 = p - 2;
    if (n > 2)
        n2 = n - 2;
    if (p + n < grado)
        comp1 = grado - p - n;
    if (p2 + n2 < grado)
        comp2 = grado - p2 - n2;
    printf("\nREGLA DE DESCARTES\n");
    printf(" caso I caso II\n");
    printf(" positivas %d %d\n", p, p2);
    printf(" negativas %d %d\n", n, n2);
    printf(" complejas %d %d\n", comp1, comp2);
    printf(" total: %d %d\n", p + n + comp1, p2 + n2 + comp2);
}

float *leen(float *polinomio, int grado_del_polinomio){
    int i;
    for(i=0; i <= grado_del_polinomio; i++){
        printf("Digite el coeficiente de la variable de grado %d:\n", grado_del_polinomio-i);
        polinomio = (float*)realloc((float*)polinomio,(i + 1)*sizeof(float));
        scanf("%f", &polinomio[i]);
    }
}
int *genera_factores(float f, int *factores, int *num_fatores) {
    if (f < 0)
        f = -f;
    int i = (int) f;
    int cont, j = i;
     printf("************ FACTORES *******\n");
    cont = 0;
    printf("El numero a factorar es:%d\n", j);
    while (i >= 1) {
        if (j % i == 0) {
            factores = (int *) realloc((int *) factores, ((cont + 1) * 2) * sizeof (int));
            factores[cont] = i;
            cont++;
        }
        i--;
    }
    int k = cont - 1;
    for (i = cont; i < 2 * cont; i++) {
        *(factores + i) = -(*(factores + k));
        k--;
    }
    printf("El numero de factores es:%d\n", i);
    *num_fatores = 2 * cont;
    return factores;
}

void imprime_factores(int *fac, int n){
    printf("Los factores posibles son:\n");
    int i;
    for(i = 0; i < n; i++)
        printf("%d..", *(fac + i));
}

float divide(float *p, float x, int n) {
    float a = *(p);
    int i;
    for (i = 1; i <= n; i++)
        a = a * x + *(p + i);
    return (a);
}

float doblediv(float *p, float f, int n) {
    float c, a = *p, b = *p;
    int i;
    for (i = 1; i <= n; i++) {
        a = a * f + *(p + i);
        b = b * f + a;
        if (i == n - 1)
            c = b;
 }
    return (a / c);
}

void r_enteras(float *polinomio, int *factores, int grado_del_polimonio, int num_factores) {
    int bandera = 0, j = 0;
    float a, b;
    do {
        b = *(factores + j);
        a = divide(polinomio, b, grado_del_polimonio);
        if (a == 0) {
            if (bandera == 0) {
                printf("\n*** RAICES ENTERAS ***\n");
                bandera = 1;
            }
            printf("RAIZ ENTERA:%d\n", *(factores + j));
        }
        j++;
        } while (j <= num_factores);
}

void r_reales(float *polinomio, int *factores, int grado_del_polinomio, int num_factores) {
    int j = 0, bandera;
    float a, e, a1, x, x1, error, error1;
    printf("\n************ RAICES REALES **********\n");
    printf("Da el error a aceptar:");
    scanf("%f", &e);
    printf(" x x1 f(x) f(x1)\n");
    do {
        error1 = 100000;
        bandera = 0;
        x = *(factores + j);
        x1 = *(factores + j + 1);
        a = divide(polinomio, x, grado_del_polinomio);
        a1 = divide(polinomio, x1, grado_del_polinomio);
        printf(" %13G %13G %13G %13G\n", x, x1, a, a1);
        if (a * a1 < 0) {
            x = (x + x1) / 2;
            do {
                x1 = x - doblediv(polinomio, x, grado_del_polinomio);
                error = x - x1;
                if (error < 0)
                    error = -error;
                if (error > error1)
                    bandera = 1;
            error1 = error;
            x = x1;
            if (bandera == 1)
                printf("EL METODO DIVERGE EN EL INTERVALO\n");
            } while (error > e && bandera == 0);
            printf("RAIZ=%f\n", x1);
        }
        j++; 
    } while (j < num_factores - 1);
}

int gauss(float **a, int n, int s, int *p){
    int k, i, j, c, f, puedo = 0;
    float m, M, temp;
    if(s == 0){
        f = n;
        c = n;
    }else{
        f = n;
        c = n+1;
    }
    
    for(k = 0; k < f-1; k++){
        //busqueda del mayor abajo de la diagonal
        int piv = 0;
        M = fabs(*(*(a + k)+ k));
        for(i = k; i < f-1; i++){
            temp = fabs(*(*(a + i + 1)+ k));
            if(M < temp){
                *p = -1 * *p;
                piv = i + 1;
                M = temp;
            }
        }
        //cambio de fila
        if(M > fabs(*(*(a + k)+ k))){
            printf("ANTES DE PERMUTACION:\n");
            imprime(a, n, s);
            for(j = k; j < c; j++){
                temp = *(*(a + k)+ j);
                *(*(a + k) + j) = *(*(a + piv) + j);
                *(*(a + piv)+ j) = temp;
            }
            printf("DESPUES DE PERMUTACION:\n");
            imprime(a, n, s);
        }
        if(*(*(a + k)+ k) == 0){
            puedo = 1;
            break;
        }else{
            for(i = k + 1; i < f; i++){
                m = -((*(*(a + i)+ k)) / (*(*(a + k)+ k)));
                for(j = k; j < c; j++){
                    *(*(a + i) + j) = (*(*(a + i)+ j)) + ((m)*(*(*(a + k)+j)));
                }
            }
        }
    }
    printf("DESPUES DE LA TRANSFORMACION:\n");
    imprime(a, n, s);
    if(*(*(a + n-1) + (n-1)) == 0)
        puedo = 1;
    return(puedo);
}

float **lee(float **matriz, int k, int *num_ecuaciones){
    int columnas, i, j, filas;
    printf("Digite el numero de filas: \n");
    scanf("%d", &filas);
    columnas = filas+1;
    if(k == 0)
        columnas = filas;
    printf("Digite los elementos de la matriz A.\n");
    matriz = (float **)malloc(sizeof(float)* filas);
    for(k = 0; k < filas; k++)
        matriz[k] = (float *)malloc(sizeof(float)* columnas);
    for(i = 0; i < filas; i++){
        for(j = 0; j < columnas; j++){
            printf("Digite el valor a[%d][%d]=", i, j);
            scanf("%f", (*(matriz + i) + j));
        }
    }
    *num_ecuaciones = filas;
    return matriz;
}

void imprime(float **matriz, int m, int x){
    int i, j, n = m+1;
    if(x == 0)
        n = m;
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            float temp = *(*(matriz + i) + j);
            if(fabs(temp)<.000001 && j < i)
                temp = 0;
            printf("%13G", temp);
        }
        printf("\n");
    }
    getchar();
}

void resultado1(float *a, int n){
    int i;
    for(i = 0; i < n; i++)
        printf("X[%d] = %15G\n", i, *(a + i));
    getchar();
    getchar();
}

void resultado(float **b, int n, int h){
    int k, i;
    float x[n];
    x[n - 1] = *(*(b + (n - 1))+n) / (*(*(b +(n - 1))+ (n - 1)));
    for(k = n - 2; k >= 0; k--){
        x[k]=*(*(b + k)+ n);
        for(i = k + 1; i < n; i++)
            x[k] = x[k] - (*(*(b + k)+ i))*x[i];
        x[k] = x[k] / *(*(b + k)+ k);
    }
    if(h == 0){
        resultado1(x, n);
    }else{
        resultado1(x, n);
        for(i = n; i > 0; i--)
            x[i] = x[i - 1];
        x[0] = 1;
        printf("ECUACIÓN CARACTERISTICA:\n");
        solucion(x, n);
    }
}

void determinante() {
    int i, j, k, piv = 1;
    float **a=NULL;
    a = lee(a, 0,&i);
    printf("El determinante a resolver es:\n");
    imprime(a, i, 0);
    j = gauss(a, i, 0, &piv);
    if (j == 0) {
        printf("la matriz diagonalizada es:\n");
        imprime(a, i, 0);
        float det = 1;
        for (k = 0; k < i; k++)
            det = det * (*(*(a + k) + k));
            printf("DETERMINANTE=%f\n", det * piv);
    } else
        printf("DEPENDENCIA LINEAL"); 
}

void sistecuaciones(){
    int j, piv, num_ecuaciones = 0;
    float **matriz = NULL;
    matriz = lee(matriz, 1, &num_ecuaciones);
    printf("El sistema a resolver es:\n");
    imprime(matriz, num_ecuaciones, 1);
    j = gauss(matriz, num_ecuaciones, 1, &piv);
    if(j == 0){
        printf("La matriz diagonalizada es:\n");
        imprime(matriz, num_ecuaciones, 1);
        printf("El resultado es:\n");
        resultado(matriz, num_ecuaciones, 0);
    }else{
        printf("SISTEMA CON DEPENDENCIA LINEAL");
        getchar();
        getchar();
    }
}

void multiplica(float **a, float *b, int n) {
    float c[n];
    int i, j;
    for (i = 0; i < n; i++) {
        c[i] = 0;
        for (j = 0; j < n; j++)
            c[i] = *(*(a+i)+j) * (*(b+j)) + c[i];
        }
    for (i = 0; i < n; i++)
        *(b+i) = c[i];
}

void acomoda(float **a, float *b, int n, int k) {
    int i, m = k, s = 1;
    if (k == -1) {
        m = n;
        s = -s;
    }
    for (i = 0; i < n; i++)
        *(*(a+i)+m)=s * (*(b+i)); 
}

void caracteristico() {
    int num_ecuaciones,i, j;
    float **a=NULL,**c;
    printf("ECUACIONES Y VALORES CARACTERISTICOS.\n");
    a = lee(a, 0,&num_ecuaciones);
    float b[num_ecuaciones];
    printf("LA MATRIZ A TRABAJAR ES:\n");
    imprime(a, num_ecuaciones, 0);
    b[0] = 1;
    for (i = 1; i < num_ecuaciones; i++)
        b[i] = 0;
    c=(float **)malloc(sizeof(float)*num_ecuaciones);
    for (i = 0;i < num_ecuaciones; i++)
        c[i]=(float*)malloc(sizeof(float)*num_ecuaciones);
    for(i = 0; i < num_ecuaciones; i++) 
        for (j = 0; j < num_ecuaciones; j++){
            *(*(c+i)+j)=0;
        }
    acomoda(c, b, num_ecuaciones, (num_ecuaciones) - 1);
    for (i = (num_ecuaciones) - 2; i >= -1; i--) {
        printf("Multiplicacion No:%d \n", (num_ecuaciones) - i - 1);
        multiplica(a, b, num_ecuaciones);
        resultado1(b, num_ecuaciones);
        acomoda(c, b, num_ecuaciones, i);
        imprime(c, num_ecuaciones, 1);
    }
    int p;
    j = gauss(c, num_ecuaciones, 1, &p);
    if (j == 0)
        resultado(c, num_ecuaciones, 1); 
}

