#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define cant 20



typedef struct{
    int id;
    int sala;
    char pelicula[cant];
    int dia;
    int mes;
    int anio;
    char hora[6];
    int cantEntradas;
    int cantDescuentos;
}registro;


typedef struct{
    float recaudacion;
    int espectadores;
    char nombre[20];
}pelicula;


void inicio();
int menu();
void opciones(int opcion);
void mostrarRegistros();
void seleccionarEditarRegistro();
void imprimirTicket();
void computarGanancias();
void limpiarRegistroPeliculas(pelicula unaPelicula[], int dimX);
int comprobarArchivo(FILE *archivo);




void inicio(){
    printf("\t\t--------------------------------------------\n");
    printf("\t\t------------------CINEMARK------------------\n");
    printf("\t\t------------------ARGENTINA-----------------\n");
    printf("\t\t--------------------------------------------\n\n\n\n");
}


int menu(){
    int opcion = -1;

    printf("\t\t\t\t Cinemark Argentina\n\n\n");
    printf("\t\t\t-------------OPCIONES-------------\n");
    printf("\t1 - Mostrar listado de registros\n");
    printf("\t2 - Seleccionar y editar registro\n");
    printf("\t3 - Imprimir ticket\n");
    printf("\t4 - Computar ganancias\n");
    printf("\t0 - Salir del programa");
    printf("\n\nOpcion: ");
    scanf("%d", &opcion);
    printf("\n\n\n\n\n");
    fflush(stdin);
    opciones(opcion);
    printf("\n\n\n\n\n");
    return opcion;
}



void opciones(int opcion){
    switch(opcion){
        case 1:
            system("cls");
            mostrarRegistros();
            break;
        case 2:
            system("cls");
            seleccionarEditarRegistro();
            break;
        case 3:
            system("cls");
            imprimirTicket();
            break;
        case 4:
            system("cls");
            computarGanancias();
            break;
        case 0:
            system("cls");
            printf("\n\n----------Saliendo del programa----------\n\n\n");
            break;
        default:
            printf("Opcion ingresada incorrecta. Intentelo nuevamente\n\n\n");
            break;
    }
}




void mostrarRegistros(){
    char bytesleidos;
    int numReg = 0;
    registro unRegistro;
    FILE *archivo = fopen("entradasVendidas.dat", "rb");

    if(comprobarArchivo(archivo)){
        bytesleidos = fread(&unRegistro, sizeof(registro), 1, archivo);
        printf("\t   ID  Sala  Pelicula     Fecha     Hora     C. Entr   C. Dsto\n");
        while(bytesleidos != 0){
            printf("Registro %d: %d   %d   %s     %d-%d-%d   %s   %d   %d\n", numReg++, unRegistro.id, unRegistro.sala, unRegistro.pelicula, unRegistro.dia, unRegistro.mes, unRegistro.anio, unRegistro.hora, unRegistro.cantEntradas, unRegistro.cantDescuentos);
            bytesleidos = fread(&unRegistro, sizeof(registro), 1, archivo);
        }
        fclose(archivo);
    }
}





void seleccionarEditarRegistro(){
    FILE *archivo = fopen("entradasVendidas.dat", "r+b");
    int posicion, opcion = -1, anio, cantRegistros;
    registro registroSelec;

    if(comprobarArchivo(archivo)){
        printf("Ingrese el numero de registro que desea ver y modificar:\n");
        printf("Registro: ");
        scanf("%d", &posicion);
        fflush(stdin);
        /*Realizar un controlador para verificar que la posicion ingresada no sea mas alta que la cantidad de registros*/
        fseek(archivo, 0, SEEK_END);
        cantRegistros = ftell(archivo)/sizeof(registro);
        if(posicion < cantRegistros && posicion >= 0){
            fseek(archivo, (posicion)*sizeof(registro), SEEK_SET);
            printf("Posicion %d  nro %d tamaño %d\n", ftell(archivo), ftell(archivo)/sizeof(registro), sizeof(registro));
            fread(&registroSelec, sizeof(registro), 1, archivo);
            do{
                printf("\t        ID  Sala  Pelicula     Fecha     Hora     C. Entr   C. Dsto\n");
                printf("Registro %d: ID: %d  %d  %s     %d-%d-%d    %s   %d   %d\n\n", posicion, registroSelec.id, registroSelec.sala, registroSelec.pelicula, registroSelec.dia, registroSelec.mes, registroSelec.anio, registroSelec.hora, registroSelec.cantEntradas, registroSelec.cantDescuentos);
                printf("Seleccione que campo desea editar:\n\n");
                printf("\t1 - Sala\n");
                printf("\t2 - Nombre de la pelicula\n");
                printf("\t3 - Dia\n");
                printf("\t4 - Mes\n");
                printf("\t5 - Anio\n");
                printf("\t6 - Hora\n");
                printf("\t7 - Cantidad de entradas\n");
                printf("\t8 - Cantidad de descuentos\n");
                printf("\t0 - Cancelar\n");
                printf("\t-1 - Guardar y salir\n");
                printf("Opcion: ");
                scanf("%d", &opcion);
                fflush(stdin);
                printf("\n\n");
                switch(opcion){
                    case 1:
                        do{
                            printf("Ingrese el numero de sala (Salas 1 a 3): ");
                            scanf("%d", &(registroSelec.sala));
                            fflush(stdin);
                            if(registroSelec.sala < 1 || registroSelec.sala > 3){
                                printf("La sala ingresada es incorrecta. Intentelo nuevamente\n\n");
                            }
                        }while(registroSelec.sala < 1 || registroSelec.sala > 3);
                        break;

                    case 2:
                        printf("Ingrese el nombre de la pelicula: ");
                        gets(registroSelec.pelicula);
                        fflush(stdin);
                        break;

                    case 3:
                        do{
                            printf("Ingrese el numero de dia (Dia 1 a 30): ");
                            scanf("%d", &(registroSelec.dia));
                            fflush(stdin);
                            if(registroSelec.dia < 1 || registroSelec.dia > 30){
                                printf("El dia ingresado es incorrecto. Intentelo nuevamente\n\n");
                            }
                        }while(registroSelec.dia < 1 || registroSelec.dia > 30);
                        break;

                    case 4:
                        do{
                            printf("Ingrese el numero de mes (Mes 1 a 12): ");
                            scanf("%d", &(registroSelec.mes));
                            fflush(stdin);
                            if(registroSelec.mes < 1 || registroSelec.mes > 12){
                                printf("El mes ingresado es incorrecto. Intentelo nuevamente\n\n");
                            }
                        }while(registroSelec.mes < 1 || registroSelec.mes > 12);
                        break;

                    case 5:
                        anio = registroSelec.anio;
                        do{

                            printf("Ingrese el numero de anio: ");
                            scanf("%d", &(registroSelec.anio));
                            fflush(stdin);
                            if(registroSelec.anio < anio){
                                printf("El anio ingresado debe ser igual o mayor al anio actual. Intentelo nuevamente\n\n");
                            }
                        }while(registroSelec.anio < anio);
                        break;

                    case 6:
                        printf("Ingrese el horario de la pelicula (Formato HH:MM): ");
                        scanf("%s", &(registroSelec.hora));
                        fflush(stdin);
                        break;

                    case 7:
                        do{
                            printf("Ingrese la cantidad de entradas: ");
                            scanf("%d", &(registroSelec.cantEntradas));
                            fflush(stdin);
                            if(registroSelec.cantEntradas <= 0){
                                printf("La cantidad de entradas debe de ser mayor a 0. Intentelo nuevamente\n\n");
                            }

                            if(registroSelec.cantEntradas < registroSelec.cantDescuentos && registroSelec.cantEntradas > 0){
                                printf("La cantidad ingresada es menor a los descuentos. Igualando la cantidad de descuentos a la cantidad de entradas actuales\n\n");
                                registroSelec.cantDescuentos = registroSelec.cantEntradas;
                            }
                        }while(registroSelec.cantEntradas <= 0);
                        break;

                    case 8:
                        do{
                            printf("Ingrese la cantidad de descuentos: ");
                            scanf("%d", &(registroSelec.cantDescuentos));;
                            fflush(stdin);
                            if(registroSelec.cantDescuentos < 0){
                                printf("La cantidad de descuentos debe de ser mayor o igual a 0. Intentelo nuevamente\n\n");
                            }else if(registroSelec.cantDescuentos > registroSelec.cantEntradas){
                                printf("La cantidad de descuentos debe de ser menor o igual a la cantidad de entradas. Intentelo nuevamente\n\n");
                            }
                        }while(registroSelec.cantDescuentos < 0 || registroSelec.cantDescuentos > registroSelec.cantEntradas);
                        break;
                    case 0:
                        printf("Volviendo al menu principal\n\n");
                        fclose(archivo);
                        break;

                    case -1:
                        printf("Guardando los cambios. Volviendo al menu principal\n\n");
                        fseek(archivo, -sizeof(registro), SEEK_CUR);
                        fwrite(&registroSelec, sizeof(registro), 1, archivo);
                        fclose(archivo);
                        break;


                    default:
                        printf("Opcion ingresada incorrecta. Intentelo nuevamente\n\n\n");
                        break;
                }
                printf("\n\n");
            }while(opcion != 0 && opcion != -1);
        }else{
            printf("El registro no existe. Volviendo al menu principal\n\n");
        }
    }
}

void imprimirTicket(){
    FILE* tickets = fopen("tickets.txt", "wt");
    FILE* archivo = fopen("entradasVendidas.dat", "rb");
    FILE* config = fopen("config.txt", "rt");
    registro unRegistro;
    char bytesleidos;
    float descuento, total, precio;
    int dto;
    char empresa[cant];

    if(comprobarArchivo(tickets)){
        if(comprobarArchivo(archivo)){
            if(comprobarArchivo(config)){
            fscanf(config, "Empresa: %s\n", empresa);
            fscanf(config, "Precio de entrada ($): %f\n", &precio);
            fscanf(config, "Descuento Club INSPT (%%): %d", &dto);
            descuento = (float)dto/100;

            printf("Imprimiendo los tickets...\n");

            bytesleidos = fread(&unRegistro, sizeof(registro), 1, archivo);
            while(bytesleidos != 0){
                total = (precio * (unRegistro.cantEntradas-unRegistro.cantDescuentos)) + (precio * unRegistro.cantDescuentos * (1- descuento));
                fprintf(tickets, "********* CINEMARK ARGENTINA *********\n");
                fprintf(tickets, "Pelicula: %s\n", unRegistro.pelicula);
                fprintf(tickets, "Sala: %d\n", unRegistro.sala);
                fprintf(tickets, "Dia: %d/%d/%d\n", unRegistro.dia, unRegistro.mes, unRegistro.anio);
                fprintf(tickets, "Hora: %s\n", unRegistro.hora);
                fprintf(tickets, "Cant. entradas: %d\n", unRegistro.cantEntradas);
                fprintf(tickets, "Cant. descuentos: %d\n", unRegistro.cantDescuentos);
                fprintf(tickets, "Precio total: $%.2f\n", total);
                fprintf(tickets, "**********************************\n\n");
                bytesleidos = fread(&unRegistro, sizeof(registro), 1, archivo);
            }

            fclose(tickets);
            fclose(archivo);
            fclose(config);
            }else{
                printf("Archivo config.txt\n\n\n");
            }
        }else{
            printf("Archivo entradasVendidas.dat\n\n\n");
        }
    }else{
        printf("Archivo Tickets.txt\n\n\n");
    }
}

void computarGanancias(){
    FILE* archivo = fopen ("entradasVendidas.dat", "rb");
    FILE* config = fopen ("config.txt", "rt");
    registro unRegistro;
    pelicula unaPelicula[cant];
    char bytesLeidos, empresa[cant];
    float ingresoNorm = 0, ingresoDto = 0, precio = 0, ingresoMax = 0, descuento;
    int totalNorm = 0, totalDto = 0, dto = 0, i, numPelicula = 0, registrada, max = -1;

    if(comprobarArchivo(archivo)){
        if(comprobarArchivo(config)){
            limpiarRegistroPeliculas(unaPelicula, cant);
            fscanf(config, "Empresa: %s\n", empresa);
            fscanf(config, "Precio de entrada ($): %f\n", &precio);
            fscanf(config, "Descuento Club INSPT (%%): %d", &dto);
            descuento = (float)dto/100;

            bytesLeidos = fread(&unRegistro, sizeof(registro), 1, archivo);
            while(bytesLeidos != 0){
                registrada = 0;
                totalNorm += (unRegistro.cantEntradas-unRegistro.cantDescuentos);
                ingresoNorm += ((unRegistro.cantEntradas-unRegistro.cantDescuentos) * precio);
                totalDto += unRegistro.cantDescuentos;
                ingresoDto += (unRegistro.cantDescuentos * (precio * (1-descuento)));

                for(i = 0; i < cant; i ++){
                    if(strcmp(unRegistro.pelicula, unaPelicula[i].nombre)== 0){
                        unaPelicula[i].recaudacion += (precio * (unRegistro.cantEntradas-unRegistro.cantDescuentos)) + (precio * unRegistro.cantDescuentos * (1-descuento));
                        unaPelicula[i].espectadores += unRegistro.cantEntradas;
                        i = cant;
                        registrada = 1;
                    }
                }

                if(registrada == 0){
                    strcpy(unaPelicula[numPelicula].nombre, unRegistro.pelicula);
                    unaPelicula[numPelicula].recaudacion += (precio * (unRegistro.cantEntradas-unRegistro.cantDescuentos)) + (precio * unRegistro.cantDescuentos * (1-descuento));
                    unaPelicula[numPelicula].espectadores += unRegistro.cantEntradas;
                    numPelicula = numPelicula + 1;
                }
                bytesLeidos = fread(&unRegistro, sizeof(registro), 1, archivo);
            }

            for(i = 0; i < cant; i ++){
                if(unaPelicula[i].recaudacion > ingresoMax){
                    ingresoMax = unaPelicula[i].recaudacion;
                    max = i;
                }
            }

            printf("\t\t-----INFORME-----\n\n");
            printf("Entradas sin descuento:\n");
            printf("\tCantidad: %d\tIngreso: $%.2f\n\n", totalNorm, ingresoNorm);
            printf("Entradas con descuento:\n");
            printf("\tCantidad: %d\tIngreso: $%.2f\n\n", totalDto, ingresoDto);
            printf("Total de ingreso: $%.2f\n\n", ingresoNorm+ingresoDto);
            printf("Pelicula mas taquillera:\n");
            printf("\tPelicula: %s\n", unaPelicula[max].nombre);
            printf("Cantidad de expectadores: %d\n", unaPelicula[max].espectadores);
            fclose(archivo);
            fclose(config);
        }else{
            printf("Archivo config.txt\n\n\n");
        }
    }else{
        printf("Archivo entradasVendidas.dat\n\n\n");
    }
}

void limpiarRegistroPeliculas(pelicula unaPelicula[], int dimX){
    int i;
    for(i = 0; i < dimX; i ++){
        strcpy(unaPelicula[i].nombre, "");
        unaPelicula[i].recaudacion = 0;
        unaPelicula[i].espectadores = 0;
    }
}

int comprobarArchivo(FILE *archivo){
    if(archivo != NULL){
        return 1;
    }else{
        printf("Error en la apertura del archivo.\n\n\n");
        return 0;
    }
}

int main(){
    int opcion = -1;

    inicio();

    while(opcion != 0){
        opcion = menu();
    }
    return 0;
}
