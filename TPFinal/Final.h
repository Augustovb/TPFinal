/* 
 * File:   Final.h
 * Author: augustovb
 *
 * Created on June 25, 2014, 1:30 AM
 */

#ifndef FINAL_H
#define	FINAL_H


/*
 * Definicion de constantes
 */
#define ERROR           NULL
#define FPS             60
#define PANTALLA_ANCHO  330
#define PANTALLA_ALTO   765



/*
 * Definicion de funciones
 */

/*Inicializara los componentes de allegro*/

int inicializar (void);

/*Estas res funciones devuelven un puntero a estructuras de tipo allegro*/
ALLEGRO_DISPLAY* getdisplay(int ancho, int alto);   //devuelve el display con el alto y ancho pedido
ALLEGRO_EVENT_QUEUE* geteventqueue (void);
ALLEGRO_TIMER* gettimer (float periodo);             //un timer que genera eventos por cada periodo




/*      cambiopantalla()
 *  Esta funcion es muy importante para realizarle cambios a la pantalla de nuestro celular.
 * SE DEBE LLAMAR A ESTA FUNCION DOS VECES, para modificar cierto bitmap, en nuestro caso la pantala
 * una vez antes de realizar los cambios, y otra despues. 
 * 
 * Esta fucion automatiza la cantidad de veces que deberemos actualizar la pantalla
 * 
 */

void cambiopantalla (ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla);

/*      analizarteclado()
 *      Esta funcion se encarga de analizar, por medio del mouse, las teclas que se aprietan en el teclado virtual de el celular
 * 
 */

int analizarteclado (ALLEGRO_EVENT_QUEUE* eventos);




#endif	/* FINAL_H */

