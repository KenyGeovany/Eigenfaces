/*Parámetros*/
#define N 64 /*INT*/
#define N2 4096 /*INT*/
#define M 1150 /*INT*/
#define MN2 1150*4096 /*INT*/
#define delta 13 /*INT*/
#define numVProp 1100 /*INT*/

/*Función que construye el nombre de un archivo pgm con un sufijo numérico: e. g. name_0342.pgm*/
char * build_name(char * prefix_name, int i ){
    char  * name_file = (char*)calloc(100, sizeof(char));
    char index[20];
    int digit_1 = i % 10;
    int digit_2 = ((i - i % 10) / 10) % 10;
    int digit_3 = ((i - i % 100) / 100) % 10;
    int digit_4 = ((i - i % 1000) / 1000) % 10;
    strcat(name_file, prefix_name);
    snprintf(index, 2, "%d", digit_4);
    strcat(name_file, index);
    snprintf(index, 2, "%d", digit_3);
    strcat(name_file, index);
    snprintf(index, 2, "%d", digit_2);
    strcat(name_file, index);
    snprintf(index, 2, "%d", digit_1);
    strcat(name_file, index);
    strcat(name_file, ".pgm");
    return name_file;
}

/*Función que calcula matriz de anticovarianza*/
void build_ANTICOV(){
    printf("PARTE I: construyendo ANTICOV.txt\n");
    /**
     * Out: out/faces/face_XXXX.pgm,  out/MX.txt,  out/MX.pgm
     *      out/X_avg.txt  out/X_avg.pgm  out/MX_avg.txt  out/MX_avg.pgm
     *      out/COV.txt  out/COV_divided.txt out/ANTICOV.txt out/ANTICOV_divided.txt
     */
    /*Variables*/
    int i, j; double sum;
    clock_t begin, end;
    double time_spent;
    /**
     * Primero cargamos las imagenes en la memoria del ordenador.
     */
    printf("1. Cargando las imagenes...\n"); begin = clock();
    char data_pgm[M][N2];
    /*Ariel Sharon*/
    for (i = 1; i < 71; i++) {
        char * name_data_pgm = build_name("data/Ariel_Sharon_",i);
        save_image(name_data_pgm, N2, data_pgm[i - 1]);
    }
    /*Colin Powell*/
    for (i = 1; i < 201; i++) {
        char * name_data_pgm = build_name("data/Colin_Powell_",i);
        save_image(name_data_pgm, N2, data_pgm[(i - 1) + 70]);
    }
    /*Donald Rumsfeld*/
    for (i = 1; i < 101; i++) {
        char * name_data_pgm = build_name("data/Donald_Rumsfeld_",i);
        save_image(name_data_pgm, N2, data_pgm[(i - 1) + 270]);
    }
    /*George W Bush*/
    for (i = 1; i < 501; i++) {
        char * name_data_pgm = build_name("data/George_W_Bush_",i);
        save_image(name_data_pgm, N2, data_pgm[(i - 1) + 370]);
    }
    /*Gerhard Schroeder*/
    for (i = 1; i < 101; i++) {
        char * name_data_pgm = build_name("data/Gerhard_Schroeder_",i);
        save_image(name_data_pgm, N2, data_pgm[(i - 1) + 870]);
    }
    /*Hugo Chávez*/
    for (i = 1; i < 61; i++) {
        char * name_data_pgm = build_name("data/Hugo_Chavez_",i);
        save_image(name_data_pgm, N2, data_pgm[(i - 1) + 970]);
    }
    /*Tony Blair*/
    for (i = 1; i < 121; i++) {
        char *name_data_pgm = build_name("data/Tony_Blair_", i);
        save_image(name_data_pgm, N2, data_pgm[(i - 1) + 1030]);
    }
    end = clock(); time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Imagenes cargadas. Tiempo de Ejec. %f\n",time_spent);

    /**
     * Imprimos las imagenes en la carpeta out/faces
     * Out: out/faces/face_XXXX.pgm
     */
    printf("2. Imprimiendo las imagenes cargadas en out/faces...\n"); begin = clock();
    for(i=0;i<M;i++){
        char *name_data_pgm = build_name("out/faces/face_", i);
        build_image(name_data_pgm,N2+delta,data_pgm[i]);
    }
    end = clock(); time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Impresión terminada. Tiempo de Ejec. %f\n",time_spent);

    /**
     * Creamos el archivo MX.txt que contiene las caras originales en columnas verticales.
     * Out: out/MX.txt
     */
    printf("3. Creando el archivo out/MX.txt...\n"); begin = clock();
    double **MX = crearMatriz(N2, M);
    for (i = 0; i < M; i++) {
        for (j = delta; j < N2; j++) {
            MX[j - delta][i] = (double) data_pgm[i][j];
        }
    }
    writeMatrizTXT(MX,N2,M,"out/MX.txt");
    end = clock(); time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Archivo creado. Se ha creado una matriz de dimensiones (N2 x M). Tiempo de Ejec. %f\n",time_spent);

    /**
     * Creamos el archivo MX.pgm que es una representación gráfica de MX.
     * Out: out/MX.pgm
     */
    printf("4. Creando el archivo out/MX.pgm...\n"); begin = clock();
    char * MX_char = (char*) calloc(MN2, sizeof(char));
    for(i=0;i<N2;i++){
        for(j=0;j<M;j++) MX_char[M * i + j] = (char)MX[i][j];
    }
    buil_pgm_p5("out/MX.pgm", N2, M, 255, MX_char);
    end = clock(); time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Archivo creado. Se ha creado una imagen pgm (N2 x M px). Tiempo de Ejec. %f\n",time_spent);

    /**
     * Creamos el archivo X_avg.txt que contiene el promedio de las caras.
     * Out: X_avg.txt
     */
    printf("5. Creando el archivo out/X_avg.txt...\n"); begin = clock();
    double * X_avg = crearVector(N2);
    for(i=0;i<N2;i++){
        sum = 0;
        for(j=0;j<M;j++){
            sum = sum + MX[i][j];
        }
        X_avg[i] = sum/(double)M;
    }
    writeVectorTXT(X_avg,N2,"out/X_avg.txt");
    end = clock(); time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Archivo creado. Se ha creado un vector de dimensión (N2 x 1). Tiempo de Ejec. %f\n",time_spent);

    /**
     * Creamos el archivo X_avg.pgm que es una representación gráfica de X_avg.
     * Out: out/X_avg.pgm
    */
    printf("6. Creando el archivo out/X_avg.pgm...\n"); begin = clock();
    char * X_avg_char = (char*) calloc(N2, sizeof(char));
    for(i=0;i<N2;i++) X_avg_char[i] = (char)X_avg[i];
    buil_pgm_p5("out/X_avg.pgm", N, N, 255, X_avg_char);
    end = clock(); time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Archivo creado. Se ha creado una imagen pgm (N x N px). Tiempo de Ejec. %f\n",time_spent);

    /**
     * Creamos el archivo MX_avg.txt que contiene la diferencia MX-X_avg
     * Out: out/MX_avg.txt
     */
    printf("7. Creando el archivo out/MX_avg.txt...\n"); begin = clock();
    double ** MX_avg = crearMatriz(N2,M);
    for(i=0;i<N2;i++){
        for(j=0;j<M;j++) MX_avg[i][j] = MX[i][j] -X_avg[i];
    }
    writeMatrizTXT(MX_avg,N2,M,"out/MX_avg.txt");
    end = clock(); time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Archivo creado. Se ha creado una matriz de tamaño (N2 x M). Tiempo de Ejec. %f\n",time_spent);

    /**
     * Creamos el archivo MX_avg.pgm que es una representación gráfica de MX_avg.
     * Out: out/MX_avg.pgm
     */
    printf("8. Creando el archivo out/MX_avg.pgm...\n"); begin = clock();
    char * MX_avg_char = (char*) calloc(MN2, sizeof(char));
    for(i=0;i<N2;i++){
        for(j=0;j<M;j++){
            MX_avg_char[M * i + j] = (char)MX_avg[i][j];
        }
    }
    buil_pgm_p5("out/MX_avg.pgm", N2, M, 255, MX_avg_char);
    end = clock(); time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Archivo creado. Se ha creado una imagen pgm (N2 x M px). Tiempo de Ejec. %f\n",time_spent);

    /**
     * Creamos el archivo COV.txt que contiene la matriz de covarianza COV
     * Out: out/COV.txt
    */
    printf("9. Creando el archivo out/COV.txt...\n"); begin = clock();
    double ** MX_avg_T = matrizTransp(MX_avg,N2,M,0); /*(M x N2)*/
    double ** MXMX_T = prodMatrices(MX_avg,MX_avg_T,N2,M,M,N2,0,0);
    writeMatrizTXT(MXMX_T,N2,N2,"out/COV.txt");
    end = clock(); time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Archivo creado. Se ha creado una matriz de tamaño (N2 x N2). Tiempo de Ejec. %f\n",time_spent);

    /**
     * Creamos el archivo COV_divided.txt que contiene la matriz de covarianza COV_divided
     * dividida por (M-1)
     * Out: out/COV_divided.txt
    */
    printf("10. Creando el archivo out/COV_divided.txt...\n"); begin = clock();
    for(int i=0;i<N2;i++){
        for(int j=0;j<N2;j++){
            MXMX_T[i][j] = MXMX_T[i][j]/((double)(M-1));
        }
    }
    writeMatrizTXT(MXMX_T,N2,N2,"out/COV_divided.txt");
    end = clock(); time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Archivo creado. Se ha creado una matriz de tamaño (N2 x N2). Tiempo de Ejec. %f\n",time_spent);

    /**
     * Creamos el archivo ANTICOV.txt que contiene la matriz de anticovarianza ANTICOV
     * Out: out/ANTICOV.txt
     */
    printf("11. Creando el archivo out/ANTICOV.txt...\n"); begin = clock();
    double ** MX_TMX = prodMatrices(MX_avg_T,MX_avg,M,N2,N2,M,0,0);
    writeMatrizTXT(MX_TMX,M,M,"out/ANTICOV.txt");
    end = clock(); time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Archivo creado. Se ha creado una matriz de tamaño (M x M). Tiempo de Ejec. %f\n",time_spent);

    /**
     * Creamos el archivo ANTICOV_divided.txt que contiene la matriz de anticovarianza ANTICOV_divided
     * dividida por (M-1)
     * Out: out/ANTICOV.txt
    */
    printf("12. Creando el archivo out/ANTICOV_divided.txt...\n"); begin = clock();
    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++){
            MX_TMX[i][j] = MX_TMX[i][j]/((double)(M-1));
        }
    }
    writeMatrizTXT(MX_TMX,M,M,"out/ANTICOV_divided.txt");
    end = clock(); time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Archivo creado. Se ha creado una matriz de tamaño (M x M). Tiempo de Ejec. %f\n",time_spent);

}

/*Función que calcula los eigenfaces*/
void get_EigenV(){
    printf("PARTE II: construyendo los Eigenfaces.\n");
    /**
    * Una vez ya creado la matriz de anticovarianza y guardada en un txt, la llamamos y obtenemos
    * los eigenfaces y sus respectivos eigenvalores.
    * Out: EigenFace_vec.txt (numVProp x N2), EigenFace_val.txt (numVProp x 1)
    */
    /*Variables*/
    int i, aux_int;
    clock_t begin, end;
    double time_spent;

    /**
     * Primero cargamos los datos necesarios en la memoria del ordenador.
    */
    printf("1. Cargando los datos...\n"); begin = clock();
    double ** ANTICOV = crearMatrizTXT("out/ANTICOV_divided.txt",&aux_int,&aux_int);
    double ** MX = crearMatrizTXT("out/MX.txt",&aux_int,&aux_int);
    end = clock(); time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Datos cargados. Tiempo de Ejec. %f\n",time_spent);

    /**
     * Encontramos los eigenvalores y los eigenfaces respectivos usando el
     * método de la potencia con deflación.
    */
    printf("2. Calculando los eigenfaces...\n"); begin = clock();
    /*Usamos el método de la potencia con deflación*/
    double * EigenFace_val;
    double ** EigenFace_vec;
    double * V_init = sumaRealVectorCW(crearVector(M),1,M,1);
    double tol = 0.000000001;
    int numIter = 1000000000;
    EigenFace_vec = (double**)calloc(numVProp,sizeof(double*));
    EigenFace_val = metodoPotenciaConDeflacion(ANTICOV,V_init,M,numVProp,numIter,tol,EigenFace_vec);

    /*Multiplicamos por A y normalizamos*/
    for(i=0;i<numVProp;i++){
        EigenFace_vec[i] = prodMatVec(MX,EigenFace_vec[i],N2,M,M);
        EigenFace_vec[i] = normalizarVector(EigenFace_vec[i],N2,1);
    }
    end = clock(); time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Eigenfaces calculados. Tiempo de Ejec. %f\n",time_spent);

    /**
     * Finalmente guardamos en un archivo txt los resultados obtenidos.
     * Usamos el formato %.12lf para guardar 12 decimales.
     * Out: EigenFace_val.txt, EigenFace_vec.txt
     */
    printf("3. Guardando los resultados...\n"); begin = clock();
    writeVectorTXT(EigenFace_val,numVProp,"out/EigenFace_val.txt");
    writeMatrizTXT(EigenFace_vec,numVProp,N2,"out/EigenFace_vec.txt");
    end = clock(); time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Datos guardados. Se han creado out/EigenFace_val.txt (numVProp x 1)\n"
           "y out/EigenFace_vec.txt (numVProp x N2). Tiempo de Ejec. %f\n",time_spent);
}

/*Verificamos que los eigenfaces sean correctos*/
void verificar_EigenV(){
    /**
     * Comprobamos que los primeros eigenvectores (eigenvalores) sean correctos.
    */
    /*Variables*/
    int numVProp_to_test=10;
    int i,j, aux_int;
    double sum;
    clock_t begin, end;
    double time_spent;

    printf("Comprando que los eigenfaces sean correctos...\n"); begin = clock();
    double ** EigenFace_vec = crearMatrizTXT("out/EigenFace_vec.txt",&aux_int,&aux_int);
    double * EigenFace_val = crearVectorTXT("out/EigenFace_val.txt",&aux_int);
    double ** COV_divided = crearMatrizTXT("out/COV_divided.txt",&aux_int,&aux_int);

    double * XV;
    double * LV;
    if(numVProp_to_test <= numVProp) {
        for (i = 0; i < numVProp_to_test; i++) {
            XV = prodMatVec(COV_divided, EigenFace_vec[i], N2, N2, N2);
            LV = multiplicaRealVectorCW(EigenFace_vec[i], EigenFace_val[i], N2, 0);
            sum = 0;
            for (j = 0; j < N2; j++) sum = sum + (XV[j] - LV[j]) * (XV[j] - LV[j]);
            printf("Error absoluto del %d-esimo eigenvector = %lf \n", i + 1, sum);
        }
    }
    else{
        printf("Error: debe testear a lo más numVProp eigenvectores.\n");
    }
    end = clock(); time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Comprobación terminada. Tiempo de Ejec. %f\n",time_spent);
}

/*Mostramos los eigenfaces en el directorio out/eigenfaces*/
void show_eigenfaces(){
    printf("PARTE III: Mostrando los eigenfaces en el directorio out/eigenfaces. \n");
    /*variables*/
    int i,j, aux_int;
    double mas_grande;
    clock_t begin, end;
    double time_spent;
    /**
     * Visualizamos los eigenfaces
     */
    printf("Construyendo los eigenfaces en formato pgm...\n"); begin = clock();
    double ** EigenFace_vec = crearMatrizTXT("out/EigenFace_vec.txt",&aux_int,&aux_int);
    for(i=0;i<numVProp;i++){
        /*Reescalamos los eigenfaces para que no se salgan sus pixeles del rango 0-255*/
        mas_grande = 0;
        for(j=0;j<N2;j++){
            if(fabs(mas_grande) < fabs(EigenFace_vec[i][j])){
                mas_grande = EigenFace_vec[i][j];
            }
        }
        for(j=0;j<N2;j++) EigenFace_vec[i][j] = (EigenFace_vec[i][j]*255)/mas_grande;
        /*Si algun pixel se llega a salir del rango 0-255 entonces
         * lo redondeamos a uno de estos extremos. */
        char EigenFace_vec_char[N2];
        for(j=0;j<N2;j++){
            if((0.00000001<= EigenFace_vec[i][j]<=255.9999999)&&(0.00000001<=EigenFace_vec[i][j])){
                EigenFace_vec_char[j] = (char)floor(EigenFace_vec[i][j]);
            }
            else if(EigenFace_vec[i][j]>255.9999999){
                EigenFace_vec_char[j] = (char)255;
            }
            else if(EigenFace_vec[i][j]<0.00000001){
                EigenFace_vec_char[j] = (char)0;
            }
        }
        /*Mostramos los resultados en el directorio out/eigenfaces */
        char * name_file = build_name("out/eigenfaces/eigenface_",i);
        buil_pgm_p5(name_file,N,N,255,EigenFace_vec_char);
    }
    end = clock(); time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Eigenfaces construidos. Tiempo de Ejec. %f\n",time_spent);
}

/*Función que recupera las imagenes originales y las guarda
 * en el directorio out/faces_recovered */
void show_faces_recovered(){
    printf("PARTE IV: \n");
    int i,j,aux_int;
    clock_t begin, end;
    double time_spent;
    /**
     * Reconstruimos las caras
     * Out: COEF.txt
     */
    printf("Reconstruyendo las caras...\n"); begin = clock();
    /*Cargamos los datos*/
    double ** EigenFace_vec = crearMatrizTXT("out/EigenFace_vec.txt",&aux_int,&aux_int);
    double ** MX = crearMatrizTXT("out/MX_avg.txt",&aux_int,&aux_int);
    double ** MX_T = matrizTransp(MX,N2,M,0);
    double * X_avg = crearVectorTXT("out/X_avg.txt",&aux_int);

    double ** W = crearMatriz(M,numVProp); /*(M x numVProp)*/
    char * eigenface_recovered = (char*) calloc(N2, sizeof(char));
    double * sum_v = crearVector(N2);
    char * name_file;
    for(j=0;j<M;j++){
        for(i=0;i<numVProp;i++) W[j][i] = productoPunto(EigenFace_vec[i],MX_T[j],N2);

        for(i=0;i<N2;i++) sum_v[i]= 0;
        for(i=0;i<numVProp;i++){
            sum_v = sumaVectores(sum_v,multiplicaRealVectorCW(EigenFace_vec[i],W[j][i],N2,0),N2,1,1);
        }

        /*Sumamos la media*/
        for(i=0;i<N2;i++) sum_v[i] = sum_v[i]+X_avg[i];

        /*Hacemos un casting de float a char*/
        for(i=0;i<N2;i++) eigenface_recovered[i] = (char)(sum_v[i]);

        /*Construimos la imagen en formate pgm*/
        name_file = build_name("out/faces_recovered/face_recov_",j);
        buil_pgm_p5(name_file,N,N,255,eigenface_recovered);

    }
    writeMatrizTXT(W,M,numVProp,"out/COEF.txt");
    end = clock(); time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Reconstrucción terminada. Se creó el archivo out/COEF.txt Tiempo de Ejec. %f\n",time_spent);
    /*Liberamos la memoria*/
    free(sum_v);
    free(name_file);
}

/*Calculamos la varianza explicada acomulada para cada número de componentes entre 0 y 1100*/
void calcular_var_expl(){
    int i;
    double sum;
    int aux_int;
    double * LAMBDA = crearVectorTXT("out/EigenFace_val.txt",&aux_int);
    double * cum_var_expl = crearVector(numVProp);

    /*Hallamos la varianza explicada total*/
    sum = 0;
    for(i=0;i<numVProp;i++) sum = sum + LAMBDA[i];
    double var_total = sum;

    /*Hallamos la varianza explicada acomulada para cada eigenface*/
    sum=0;
    for(i=0;i<numVProp;i++){
        sum = sum + LAMBDA[i];
        cum_var_expl[i] = sum/var_total;
    }

    /*Creamos un matriz con los puntos a graficar.*/
    double ** data = crearMatriz(numVProp,2);
    for(i=0;i<numVProp;i++) data[i][1] = i+1;
    for(i=0;i<numVProp;i++) data[i][2] = cum_var_expl[i];

    /*Escribimos el archivo con los puntos a graficar y lo graficamos en R.*/
    writeMatrizTXT(data,numVProp,2,"out/plot_var.txt");
}