#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "image_lib.h"
#include "NMLIB/nmlib.h"
#include "eigenface_lib.h"

int main() {
    printf("Iniciando programa.\n");

    /**
     * Tareas
    */
    build_ANTICOV();
    //get_EigenV();
    //verificar_EigenV();
    show_eigenfaces();
    show_faces_recovered();
    calcular_var_expl();

    printf("\nPrograma terminado.");
    return 0;
}

/**
* Fuentes:
    * https://conradsanderson.id.au/lfwcrop/
    * http://vision.ucsd.edu/content/yale-face-database
    * https://www.convertsimple.com/convert-pgm-to-png/
    * http://www.vision.jhu.edu/teaching/vision08/Handouts/case_study_pca1.pdf
    * https://math.stackexchange.com/questions/1520832/real-life-examples-for-eigenvalues-eigenvectors
    * https://scikit-learn.org/stable/auto_examples/applications/plot_face_recognition.html#sphx-glr-download-auto-examples-applications-plot-face-recognition-py
    * https://en.wikipedia.org/wiki/Eigenface
*/