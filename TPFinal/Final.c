
/* 
 * File:   Final.c
 * Author: augustovb
 *
 * Created on June 25, 2014, 12:48 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>              //son todas las librerias que se utilizaran
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <string.h>
#include "Final.h"
#include <ftdi.h>
#include <unistd.h>
/*
 *Main
 */

//DESDE ACA
#ifndef LODELAFT
#define LODELAFT
void writeFTDI (unsigned char data);
unsigned char readFTDI (void);
int readBUTTONS (void);
#endif
struct ftdi_context ftdic;
unsigned char buf[1024];
char lastval;


int inicializar (void);


 /* HASTA ACA DESPROLIJIDAD SOLO POR LA FERIA*/ 



int main(int argc, char** argv) {
    int estado=0;
    int* pestado=&estado;
    int estadomenu=POS1;
    int* pestadomenu=&estadomenu;
    int estadoconfiguracion=USUARIO;
    int* pestadoconfiguracion=&estadoconfiguracion;
    int condiciones=0;      //por lo que me devuelva la funcion setear comienzo
    
    
    
    if(inicializar()){
        return -1;
    }
    
    ALLEGRO_DISPLAY* display=NULL;
    ALLEGRO_EVENT_QUEUE* eventos=NULL;      //Son basicamente los punteros a estructuras propias de Allegro para la inicializacion de lo 
    ALLEGRO_TIMER*  timer=NULL;             //basico y necesario para hacer funcionar las funciones de esta libreria
    
    display=getdisplay(PANTALLA_ANCHO,PANTALLA_ALTO);
    eventos=geteventqueue();                              //llamo las funciones que crearan los displays y eventos
    timer=gettimer(1.0/FPS);
    if(display==ERROR||eventos==ERROR||timer==ERROR){
        return -1;                                      //si fallo alguna de las funciones llamadas, retorno del main, mostrando que hubo un error
    }
    
    al_register_event_source(eventos, al_get_display_event_source(display));

    al_register_event_source(eventos, al_get_timer_event_source(timer));     //registro los eventos
 
    al_register_event_source(eventos, al_get_mouse_event_source()); 
    
    al_register_event_source(eventos,al_get_keyboard_event_source());
    
    ALLEGRO_BITMAP* imagencelular=NULL;
    
    imagencelular=al_load_bitmap("foto_celular.png");
    if(imagencelular==NULL){fprintf(stderr,"No se pudo cargar la imagen\n");return -1;}     //chequeo que no haya habido errores
    
    al_draw_bitmap(imagencelular,-40,-20,0);
    al_flip_display();
    
    ALLEGRO_BITMAP* pantalla=NULL;      //a partir de ahora, solo trabajaremos graficamente en la pantalla
    pantalla=al_create_bitmap(220,288); //tiene el tamaño de la pantalla
    
    cambiopantalla(display,pantalla);
    al_clear_to_color(al_map_rgb(255,255,255));             //siempre que quiera modificar al bitmap pantalla para despues "pegarlo"
    cambiopantalla(display,pantalla);
    
    /*
     *  La secuencia que realizamos aqui... al_set_target_bitmap(pantalla);
     *                                      
     *                                      CAMBIOS ASOCIADOS A LA PANTALLA
     * 
     *                                      al_set_target_bitmap(al_get_backbuffer(display));
     *                                      al_draw_bitmap(pantalla,48,118,0);
     *                                      al_flip_display();
     * es la que esta comprimida en estas dos funciones
     * 
     */

    
    
    al_start_timer(timer);   //inicializo el timer
    
    INFOPANTALLA mipantalla=getuserdata();
    INFOPANTALLA* pmipantalla=&mipantalla;
    iniciarpantalla(mipantalla,display,pantalla);
    
    while(estado!=FINALIZAR){
        if(estado==PANTALLAPRINCIPAL){
            mantenerpantalla(mipantalla,display,pantalla);
            analizartecladopantalla(eventos,pestado,display,pantalla);
            
        } 
        if(estado==MENU){
            mantenermenu(pestado,pestadomenu,display,pantalla,mipantalla);
            analizartecladomenu(eventos,pestado,pestadomenu);
        }
        if(estado==MENSAJE){
            escribirmensaje(eventos,display,pantalla,pestado,pmipantalla);
        
        }
        if(estado==PERSONALIZAR){
            mantenerconfiguracion(pestadoconfiguracion,display,pantalla,eventos,pestado,pmipantalla);
            analizartecladoconfiguracion(eventos,pestadoconfiguracion,pestado,pmipantalla);        
        }
        if(estado== LINTERNA){
            mantenerlinterna(pestado,display,pantalla,mipantalla);
            analizartecladolinterna(eventos,pestado);
            mantenerlinterna(pestado,display,pantalla,mipantalla);
            
        }
        if(estado==FIESTA){
            dontstoptheparty (pestado,display,pantalla);
            
        }
        
        
        
    }
    
    putuserdata(mipantalla);
    *pestado=PANTALLAPRINCIPAL;
    
    return (EXIT_SUCCESS);
    
}







int inicializar(void){
    
    if(!al_init()){
        fprintf(stderr,"No se pudo inicializar Allegro\n");
        return 1;
    }
    
    al_install_keyboard();
    al_install_mouse();     //instalo los perifericos
    al_install_audio();
    
    al_init_font_addon();    // inicializo el font addon
    
    
    
    if(!al_init_ttf_addon()){
        fprintf(stderr,"No se inicializo el addon ttf.\n");
        return -1;     
        
        
    }// inicializo el True Type Font addon
    
    
    if(!al_init_acodec_addon()){
        fprintf(stderr,"No se inicializo el addon de acodec\n");
        return -1;
    }           //es el addon de audio
    
    if(!al_init_image_addon()){
        fprintf(stderr,"No se inicializo el addon de imagenes\n");
        return -1;
    }           //addon de imagenes
    
    
    if(!al_init_primitives_addon()){
        fprintf(stderr,"No se inicializo el addon de acodec\n");
        return -1;
    }       //por ultimo el de primitivas
    
   
    
    
    //Aca empieza la inicializacion ftdiezca
        int ret=0;
        //Initialize context for subsequent function calls 
        ftdi_init(&ftdic);

    // Open FTDI device based on FT245R vendor & product IDs 
        if(ftdi_usb_open(&ftdic, 0x0403, 0x6001) < 0) {
            puts("Can't open device");
            return -1;
    
        }

        if ((ret = ftdi_set_bitmode(&ftdic, 0xE0, 0x01)) < 0) {
            fprintf(stderr, "unable to set bitmode\n");
            return -1;
        }
        
        writeFTDI((unsigned char)0x1F);
       
    return 0;
}





void writeFTDI (unsigned char data)

 {
   
    static unsigned char x = 0xFF;
    x = data;
    ftdi_write_data(&ftdic, &x, 1);
                       
}

unsigned char readFTDI (void)
{
    
    int f = 0; 
    f= ftdi_read_data(&ftdic,buf,sizeof(buf));
    
    return buf[0]; 

}





int readBUTTONS (void){
    int f = 0; 
    
    
    
    f = ftdi_read_data(&ftdic, buf, sizeof(buf));
    
    lastval = (buf[0] & 0x1F);
   
    while ((lastval == (buf[0] & 0x1F)) && lastval != 0x1F)
        f = ftdi_read_data(&ftdic, buf, sizeof(buf));
    
    if (lastval==0x1E){
        return ARRIBA;
    } else if(lastval==0x1D){
        return IZQUIERDA;
    } else if(lastval==0x17){
        return DERECHA;
    } else if (lastval==0x1B){
        return MEDIO;
    }else if (lastval==0x0F){
        return ABAJO;
    } else {return 0;}
    
}



