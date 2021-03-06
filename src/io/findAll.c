#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes.h"

/**
*
* @file   findAll.c
*
*
* @brief  imprime listados de empleados segun criterio ( mode )
* @param  { int } - mode: todos los empleados || jerarquicos || no jerarquicos
* @return { int } - status
*
*
*/

int findAll (int mode) {

    FILE * fp; /*   file pointer    */
    FILE * ip; /*   index pointer   */
    t_empleado * emp = malloc(sizeof(t_empleado));
    int clave, status, tipoReg, cant_empleados;
    long unsigned pos_f;
    char * nombre = malloc(sizeof(emp->nombre));
    char * fecha = malloc(sizeof(emp->fecha));
    char * nombre_oficina = malloc(sizeof(emp->jerarquia.d2.nombreOficina));
    char * categoria = malloc(sizeof(emp->jerarquia.d1.categoria));
    char * strCargo = malloc(strlen("jerarquico"));

    if (((fp = fopen(ARCH_EMP, "rb+"))==NULL) || ((ip = fopen(ARCH_INDEX, "rb+"))==NULL)) {

        printf("Error al abrir archivo\n");
        getchar();
        return FAILED;

    } else {
        switch(mode){
            case LIST_JERARQUICOS:
                enc_jefes();
                while (!feof(ip)){

                    fscanf(ip, "%d\t" "%d\t" "%d\t" "%lu\t\n", &clave, &status, &tipoReg, &pos_f);
                    if(status == ACTIVO && tipoReg == JERARQUICO){

                        fseek(fp, pos_f, SEEK_SET);
                        fscanf(fp, "%d\t %s\t %s\t %s\t %s\t %d\t \n", &clave, nombre, fecha, strCargo, nombre_oficina, &cant_empleados);
                        printf("%5.3i\t %-7.15s\t %-7.20s\t %-7.20s\t %20.3i\t\t\n", clave, nombre, fecha, nombre_oficina, cant_empleados);

                    }
                }
                while(getchar()!='\n');
                break;
            case LIST_NO_JERARQUICOS:
                enc_operarios();
                while (!feof(ip)){

                    fscanf(ip, "%d\t" "%d\t" "%d\t" "%lu\t\n", &clave, &status, &tipoReg, &pos_f);
                    if(status == ACTIVO && tipoReg == NO_JERARQUICO){

                        fseek(fp, pos_f, SEEK_SET);
                        fscanf(fp, "%d\t %s\t %s\t %s\t %s\t \n", &clave, nombre, fecha, strCargo, categoria);
                        printf("%7.3i\t\t %-7.15s\t %-7.15s\t %7.10s\t\n", clave, nombre, fecha, categoria);
                    }
                }
                getchar();
                break;
            case LIST_ALL:
                enc_total();
                while (!feof(ip)){

                    fscanf(ip, "%d\t" "%d\t" "%d\t" "%lu\t\n", &clave, &status, &tipoReg, &pos_f);
                    if(status == ACTIVO ){

                        fseek(fp, pos_f, SEEK_SET);
                        if(tipoReg == JERARQUICO){

                            fscanf(fp, "%d\t %s\t %s\t %s\t %d\t \n", &clave, nombre, fecha, nombre_oficina, &cant_empleados);
                            strncpy(strCargo, "Jerarquico", strlen("Jerarquico"));

                        } else {

                            fscanf(fp, "%d\t %s\t %s\t %s\t \n", &clave, nombre, fecha, categoria);
                            strncpy(strCargo, "Operario", strlen("Operario"));

                        }
                        printf("%7.3i\t\t %-7.20s\t %-7.10s\t %7.20s\t\n", clave, nombre, fecha, strCargo);
                    }
                }
                getchar();
                break;
            default: break;

        }

    free(emp);
    return SUCCESS;
    }
}
