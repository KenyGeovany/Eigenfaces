void save_image(char * input_file, int size_image, char * buffer){
    /*buffer debe pre-inicializarse como vector de tamaño size_image.*/
    /*Abrimos el archivo*/
    FILE *  file = fopen(input_file,"r");
    int i=0;
    while(i<size_image){
        buffer[i] = fgetc(file);
        i++;
    }
    fclose(file);
}

void build_image(char * output_file, int size_image, char * buffer){
    /*buffer debe pre-inicializarse como vector de tamaño size_image.*/
    /*Abrimos el archivo*/
    FILE *  file = fopen(output_file,"w+");
    for(int i=0;i<size_image;i++) {
        fprintf(file,"%c", buffer[i]);
    }
    fclose(file);
}

void printf_image(char * jpeg_file, int size_image){
    /*Abrimos el archivo*/
    FILE *  file = fopen(jpeg_file,"r");
    for(int i=0;i<size_image;i++) {
        printf("%c", fgetc(file));
    }
    fclose(file);
}

void copy_image(char * jpeg_file, char * name_copy, int size_image){
    char buffer[size_image];
    save_image(jpeg_file,size_image,buffer);
    build_image(name_copy,size_image,buffer);
}

void buil_pgm_p5(char * name_pgm, int rows, int cols, int gray_scale, char * data){
    /*Tenemos que asumir que la cabcer no tiene más de 50 carácteres*/
    int size = rows*cols + 150;
    char * buffer = (char*)calloc(size, sizeof(char));
    /*Definimos la cabecera*/
    buffer[0] = 'P'; buffer[1] = '5'; buffer[2] = '\n';
    /*Definimos el ancho*/
    int resto = cols; int i=0; char temp[20]; /*asumimos que las medidas no tienen más de 20 dígitos.*/
    while(resto != 0) {
        temp[i] = resto % 10 + 48;
        resto = (resto - resto % 10) / 10;
        i++;}
    for(int k=0;k<i;k++) buffer[3+k] = temp[(i-1)-k];
    buffer[3+i] = ' ';
    int posicion_actual = 4+i;
    /*Definimos el ancho*/
    resto = rows; i=0;
    while(resto != 0) {
        temp[i] = resto % 10 + 48;
        resto = (resto - resto % 10) / 10;
        i++;}
    for(int k=0;k<i;k++) buffer[posicion_actual+k] = temp[(i-1)-k];
    buffer[posicion_actual+i] = '\n';
    posicion_actual = posicion_actual + i + 1;
    /*Definimos el valor máximo de la escala de grises*/
    resto = gray_scale; i=0;
    while(resto != 0) {
        temp[i] = resto % 10 + 48;
        resto = (resto - resto % 10) / 10;
        i++;}
    for(int k=0;k<i;k++) buffer[posicion_actual + k] = temp[(i-1)-k];
    buffer[posicion_actual+i] = '\n';
    posicion_actual = posicion_actual + i + 1;
    for(int k = posicion_actual;k<posicion_actual+rows*cols;k++){
        buffer[k] = data[k-posicion_actual];
    }
    posicion_actual = posicion_actual + rows*cols;
    build_image(name_pgm,posicion_actual,buffer);
}
