#include <iostream>
#include <omp.h>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define SIZE 100

int recolector(std::string temperatura[], std::string presion[]){
    int i = 0, j = 0; 
    std::string linea;
    std::ifstream archivo("datos_temperatura.txt");
    while (getline(archivo, linea) && i<SIZE) {
        temperatura[i] = linea;
        i++;
    }
    archivo.close();
    std::string linea2;
    std::ifstream archivo2("datos_presion.txt");
        while (getline(archivo2, linea2) && i<SIZE) {
        presion[j] = linea2;
        j++; 
    }
    archivo2.close();
    if (j>=i){
         return j;
    }
    else
    {
        return i;
    }   
}

int main()
{
    float Temperatura[SIZE];
    std::string info_string_temp[SIZE];
    std::string info_string_pres[SIZE];
    float Presion[SIZE];
    float valores_k[SIZE];
    int i;
    int size = recolector(info_string_temp, info_string_pres);
#pragma omp parallel for
    for (i = 0; i < size; i++)
    {
        char* char_arr;
        std::string str_obj(info_string_temp[i]);
        char_arr = &str_obj[0];
        char delimitador[] = ",";
        char* token = strtok(char_arr, delimitador);
        if (token != NULL) {
            while (token != NULL) {
#pragma omp critical
                {
                        Temperatura[i] = atof(token);
                }
                token = strtok(NULL, delimitador);
            }

        }
    }
#pragma omp parallel for
    for (i = 0; i < size; i++)
    {
        char* char_arr;
        std::string str_obj(info_string_pres[i]);
        char_arr = &str_obj[0];
        char delimitador[] = ",";
        char* token = strtok(char_arr, delimitador);
        if (token != NULL) {
            while (token != NULL) {
#pragma omp critical
                {
                    Presion[i] = atof(token);
                }
                token = strtok(NULL, delimitador);
            }

        }
    }
#pragma omp parallel for
    for (i = 0; i < size; i++)
    {
#pragma omp critical
        valores_k[i] = (Presion[i] * 0.000987f) / (Temperatura[i] + 273.15f);
        float a = (Presion[i] * 0.000987f) / (Temperatura[i] + 273.15f);
        
    }
    for (i = 0; i < size; i++)
    {
        printf("Constante K:  %.16f\n", valores_k[i]);

    }
    
    return 0;
}


