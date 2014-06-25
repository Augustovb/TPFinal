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








#endif	/* FINAL_H */

