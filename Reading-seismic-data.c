/*	Programa de lectura de datos de archivos asa
 *	Aprendizaje Maquinal
 *	Garduño Juárez Eduardo 
 *	2/ENERO/2020
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

/*------------------Prototipos-------------------*/
void LeeDatos(char*);

/*------------Variables Globales------------------*/
FILE *a1;
FILE *a2;
FILE *a3;

int cont;


/*---------------Funcion principal--------------------*/
int main () {
	
	DIR *folder1, *folder2, *folder3;
	struct dirent *entry, *entry2, *entry3;
	int files = 0, files2 = 0, files3 = 0;
	char *dir = "2017/"; 
	char *aux = (char*) malloc(100*sizeof(char));
	char *aux2 = (char*) malloc(100*sizeof(char));
	char *aux3 = (char*) malloc(100*sizeof(char));
	
	a1 = fopen("datos1_2017.dat","wt");
	a2 = fopen("datos2_2017.dat","wt");
	a3 = fopen("datos3_2017.dat","wt");
	
	cont = 0;
	
	folder1 = opendir(dir);
	if(folder1 == NULL){
		perror("Error");
		return 1;
	}
	 
	while ((entry = readdir(folder1))) {
		files++;
		if(files >= 3){
			strcpy(aux, dir);
			strcat(aux, entry -> d_name);
			strcat(aux,"/");
			folder2 = opendir(aux);
			if(folder2 == NULL){
				perror("Error");
				return 1;
			} 
			
			while ((entry2 = readdir(folder2))){
				files2++;
				if(files2 >= 3 ){
					strcpy(aux2, aux);
					strcat(aux2, entry -> d_name);
					strcat(aux2,"/");
					folder3 = opendir(aux2);
					if(folder3 == NULL){
						perror("Error");
						return 1;
					}
					files3 = 0;
					while((entry3 = readdir(folder3))){
						files3++;
						if(files3 >= 3){
							strcpy(aux3, aux);
							srtcat(aux3, entry -> d_name);
							LeeDatos(aux3);
							cont++;
							if(cont == 3){
								cont = 0;
							}
						}
					}
					closedir(folder3);
				}
			}
			closedir(folder2);
		}
	}
	closedir(folder1);
	
	fclose(a1);
	fclose(a2);
	fclose(a3);
	
	return 0;
}

/*--------------Función para leer los datos------------------*/
void LeeDatos(char* nombre){
	FILE *archivo;
	char lee[85];
	int linea = 0, prof;
	char *aux = (char*)malloc(100*sizeof(char));
	double mag, lat, lon;
	double n_s, v, e_o;
	
	archivo = fopen(nombre, "r");
	
	while(fgets(lee, 85, archivo)){
		if(linea == 58){
			strncpy(aux, lee+45, 84);
			mag = atof(aux);
		}
		if(linea == 59){
			strcnpy(aux, lee+41, 46);
			lat = atof(aux);
		}
		if(linea == 60){
			strncpy(aux, lee+41, 46);
			lon = atof(aux);
		}
		if(linea == 61){
			strncpy(aux, lee+41, 84);
			prof = atoi(aux);
		}
		if(linea >= 109){
			strncpy(aux, lee+2, 10);
			n_s = atof(aux);
			
			strncpy(aux, lee+12, 20);
			v = atof(aux);
			
			strncpy(aux, lee+22, 30);
			e_o = atof(aux);
			
			if(mag < 5.4){
				if(cont == 0){
					fprintf(a1,"%d	%d	%f	%f	%f Leve\n", prof, linea-108, n_s, v, e_o);
				}else if (cont == 1){
					fprintf(a2,"%d	%d	%f	%f	%f Leve\n", prof, linea-108, n_s, v, e_o);
				}else{
					fprintf(a3,"%d	%d	%f	%f	%f Leve\n", prof, linea-108, n_s, v, e_o);
				}
			}else if(mag >= 5.4 && mag < 6.9){
				if(cont == 0){
					fprintf(a1,"%d	%d	%f	%f	%f Moderado\n", prof, linea-108, n_s, v, e_o);
				}else if (cont == 1){
					fprintf(a2,"%d	%d	%f	%f	%f Moderado\n", prof, linea-108, n_s, v, e_o);
				}else{
					fprintf(a3,"%d	%d	%f	%f	%f Moderado\n", prof, linea-108, n_s, v, e_o);
				}	
			}else if(mag >= 6.9){
				if(cont == 0){
					fprintf(a1,"%d	%d	%f	%f	%f Fuerte\n", prof, linea-108, n_s, v, e_o);
				}else if (cont == 1){
					fprintf(a1,"%d	%d	%f	%f	%f Fuerte\n", prof, linea-108, n_s, v, e_o);
				}else{
					fprintf(a1,"%d	%d	%f	%f	%f Fuerte\n", prof, linea-108, n_s, v, e_o);
				}
			}
		}
		linea ++;
	}
}

