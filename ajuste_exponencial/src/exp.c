#include <stdio.h>
#include <math.h>

typedef struct {
    int año;
    float x; // COLUMN_GLAC_MEAN
    float y; // COLUMN_GLOBAL_AVERAGE_SEA_LEVEL_CHANGE
} Registro;

Registro datos[] = {
    {2002, -18.6965, -5.655815},
    {2003, -14.9081, -4.752999},
    {2004, -29.08901, -3.978419},
    {2005, -22.8293, -3.452075},
    {2006, -11.06644, -2.64425},
    {2007, -16.89563, -1.977132},
    {2008, -9.371227, -1.448654},
    {2009, -7.32473, -0.8095224},
    {2010, -2.866128, 0.1041146},
    {2011, -7.194661, 0.7340445},
    {2012, 2.19746, 1.000621},
    {2013, 6.370174, 1.867449},
    {2014, 1.86894, 2.607803},
    {2015, 7.86952, 3.392661},
    {2016, 3.94186, 4.098025},
    {2017, 2.35805, 4.985921},
    {2018, 5.63572, 5.272038},
};

#define D_LIMIT 25 // limite desplazamiento vertical para las iteraciones

float modelo_exponencial(float x) {
    return 9.354366017 * expf(0.017232713*x);
}

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    float min_d;
    float min_error;

    // Sé que hay un error en la suma del punto flotante por la representación
    // del IEEE754, pero no cambia mucho ya que el desplazamiento de los datos
    // es estimativo
    for (float d=0; d < D_LIMIT; d+=0.000001) {
        float error = 0;
        for (int i = 0; i < sizeof(datos)/sizeof(datos[0]); i++) {
            Registro r = datos[i];

            float valor_modelo = modelo_exponencial(r.x);
            float valor_dato = r.y + d;

            float delta = valor_modelo - valor_dato;
            error += delta * delta;
        }

        if (d == 0.0 || error < min_error) {
            min_d = d;
            min_error = error;
        }

#ifdef DEBUG
        printf("Desplazamiento: %f --> E: %f\n", d, error);
#endif
    }

    printf("Menor error con d: %f y E: %f\n", min_d, min_error);
    return 0;
}
