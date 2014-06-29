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


/*
 *Main
 */
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
            break;
        }
        if(estado==PERSONALIZAR){
            mantenerconfiguracion(pestadoconfiguracion,display,pantalla);
            analizartecladoconfiguracion(eventos,pestadoconfiguracion,pestado,pmipantalla);
            
            
                    
        }
        
        
        
    }
    
    putuserdata(mipantalla);
    
    return (EXIT_SUCCESS);
}


int analizartecladoconfiguracion (ALLEGRO_EVENT_QUEUE* eventos,int * estadoconfiguracion, int* pestado, INFOPANTALLA* pantalla){
        //de aca en adelante es simplemente la funcionde leerteclado que por comodidad no la pongo afuera
    
    
    while(1){                   // esto es la funcion que lee de donde se clickeo
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventos,&ev);
        
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        } else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(ev.mouse.button & 1){
                //aca iran los ifs que veran el ev.mouse.x y el ev.mouse.y
                if(ev.mouse.x>30&&ev.mouse.x<110){      
                    if(ev.mouse.y>450&&ev.mouse.y<490){             //TECLA SELECT
                            if(*estadoconfiguracion==USUARIO){*estadoconfiguracion=INUSUARIO;break;} 
                            
                            else if(*estadoconfiguracion==COMPANIA){*estadoconfiguracion=CMOVISTAR; break;}
                            
                            else if(*estadoconfiguracion==CMOVISTAR){*estadoconfiguracion=USUARIO; pantalla->compania=MOVISTAR; break; }
                            
                            else if(*estadoconfiguracion==CPERSONAL){*estadoconfiguracion=USUARIO; pantalla->compania=PERSONAL; break;}
                            
                            else if(*estadoconfiguracion==CCLARO){*estadoconfiguracion=USUARIO; pantalla->compania=CLARO; break;}
                            
                            else if(*estadoconfiguracion==CNEXTEL){*estadoconfiguracion=USUARIO; pantalla->compania=NEXTEL; break;}
                            
                            else if(*estadoconfiguracion==TIPOESCRITURA){*estadoconfiguracion=TT9; break;}
                            
                            else if(*estadoconfiguracion==TT9){*estadoconfiguracion=USUARIO; pantalla->tipoescritura=T9; break;}
                            
                            else if(*estadoconfiguracion==CLASICO){*estadoconfiguracion=USUARIO; pantalla->tipoescritura=MODOLIBRE; break;}
                            
                            else if(*estadoconfiguracion==TECLADONORMAL){*estadoconfiguracion=USUARIO; pantalla->tipoescritura=TECLADOANALOGO; break;}
                            else if(*estadoconfiguracion==FONDO){*estadoconfiguracion=FBLANCO; break;}
                            
                            else if(*estadoconfiguracion==FBLANCO){*estadoconfiguracion=USUARIO; pantalla->fondo.entro=NOCAMBIO; break;}
                            
                            else if(*estadoconfiguracion==FROJO){*estadoconfiguracion=USUARIO; pantalla->fondo.entro=ROJO; break;}
                            else if(*estadoconfiguracion==FAMARILLO){*estadoconfiguracion=USUARIO; pantalla->fondo.entro=AMARILLO; break;}
                            else if(*estadoconfiguracion==FVERDE){*estadoconfiguracion=USUARIO; pantalla->fondo.entro=VERDE; break;}
                            else if(*estadoconfiguracion==FMORADO){*estadoconfiguracion=USUARIO; pantalla->fondo.entro=MORADO; break;}
                            else if(*estadoconfiguracion==FCELESTE){*estadoconfiguracion=USUARIO; pantalla->fondo.entro=CELESTE; break;}
                            else if(*estadoconfiguracion==FNARANJA){*estadoconfiguracion=USUARIO; pantalla->fondo.entro=NARANJA; break;}
                            else if(*estadoconfiguracion==FROSA){*estadoconfiguracion=USUARIO; pantalla->fondo.entro=ROSA; break;}
                            
                    }
                       
                } else if(ev.mouse.x>110&&ev.mouse.x<208){  //son las teclas de la linea media que incluyen los centrales
                    //analizo primero lo de las "flechitas"y el boton del medio
                    if(ev.mouse.y>450&&ev.mouse.y<460){
                            if(*estadoconfiguracion==COMPANIA){*estadoconfiguracion=USUARIO; break;}  //tecla para arrriba
                            
                            else if(*estadoconfiguracion==COMPANIA){*estadoconfiguracion=USUARIO; break;}
                            
                            else if(*estadoconfiguracion==CPERSONAL){*estadoconfiguracion=CMOVISTAR; break;}
                            
                            else if(*estadoconfiguracion==CCLARO){*estadoconfiguracion=CPERSONAL; break;}
                            
                            else if(*estadoconfiguracion==CNEXTEL){*estadoconfiguracion=CCLARO; break;}
                            
                            else if(*estadoconfiguracion==MENSAJEPERSONAL){*estadoconfiguracion=COMPANIA; break;}
                            
                            else if(*estadoconfiguracion==TIPOESCRITURA){*estadoconfiguracion=MENSAJEPERSONAL; break;}
                            
                            else if(*estadoconfiguracion==FONDO){*estadoconfiguracion=TIPOESCRITURA; break;}
                            
                            else if(*estadoconfiguracion==FROJO){*estadoconfiguracion=FBLANCO; break;}
                            else if(*estadoconfiguracion==FAMARILLO){*estadoconfiguracion=FROJO; break;}
                            else if(*estadoconfiguracion==FVERDE){*estadoconfiguracion=FAMARILLO; break;}
                            else if(*estadoconfiguracion==FMORADO){*estadoconfiguracion=FVERDE; break;}
                            else if(*estadoconfiguracion==FCELESTE){*estadoconfiguracion=FMORADO; break;}
                            else if(*estadoconfiguracion==FNARANJA){*estadoconfiguracion=FCELESTE; break;}
                            else if(*estadoconfiguracion==FROSA){*estadoconfiguracion=FNARANJA; break;}
                            
                            
                            
                            
                            
                        
                        
                    } else if (ev.mouse.y>525&&ev.mouse.y<540){
                           if(*estadoconfiguracion==USUARIO){*estadoconfiguracion=COMPANIA; break;} //teclaparaabajo
                           
                           else if(*estadoconfiguracion==COMPANIA){*estadoconfiguracion=MENSAJEPERSONAL; break;}
                           else if(*estadoconfiguracion==MENSAJEPERSONAL){*estadoconfiguracion=TIPOESCRITURA; break;}
                           else if(*estadoconfiguracion==TIPOESCRITURA){*estadoconfiguracion=FONDO; break;}
                           else if(*estadoconfiguracion==CMOVISTAR){*estadoconfiguracion=CPERSONAL; break;}
                           else if(*estadoconfiguracion==CPERSONAL){*estadoconfiguracion=CCLARO; break;}
                           else if(*estadoconfiguracion==CCLARO){*estadoconfiguracion=CNEXTEL; break;}
                           
                           else if(*estadoconfiguracion==FBLANCO){*estadoconfiguracion=FROJO; break;}
                           else if(*estadoconfiguracion==FROJO){*estadoconfiguracion=FAMARILLO; break;}
                            else if(*estadoconfiguracion==FAMARILLO){*estadoconfiguracion=FVERDE; break;}
                            else if(*estadoconfiguracion==FVERDE){*estadoconfiguracion=FMORADO; break;}
                            else if(*estadoconfiguracion==FMORADO){*estadoconfiguracion=FCELESTE; break;}
                            else if(*estadoconfiguracion==FCELESTE){*estadoconfiguracion=FNARANJA; break;}
                            else if(*estadoconfiguracion==FNARANJA){*estadoconfiguracion=FROSA; break;}
                            
                        
                        
                    } else if(ev.mouse.y>460&&ev.mouse.y<540){  //der, izq o medio
                                if(ev.mouse.x>130&&ev.mouse.x<188){
                                    
                                    
                                    
                                }     //la del medio
                    } 
                    
                } else if(ev.mouse.x>208&&ev.mouse.x<288){      //pueden ser back,colgar,3,6,9 o numeral
                    if(ev.mouse.y>450&&ev.mouse.y<490){             //se presiono la tecla back
                            if(*estadoconfiguracion==USUARIO||*estadoconfiguracion==COMPANIA||*estadoconfiguracion==MENSAJEPERSONAL||*estadoconfiguracion==TIPOESCRITURA||*estadoconfiguracion==FONDO){
                               *pestado=MENU;       //lo anterior seria menu
                               break;           
                            } if(*estadoconfiguracion==INUSUARIO||*estadoconfiguracion==INCOMPANIA||*estadoconfiguracion==MPCOLOR||*estadoconfiguracion==MPTEXTO||*estadoconfiguracion==MPTAMANO||*estadoconfiguracion==TT9||*estadoconfiguracion==CLASICO||*estadoconfiguracion==TECLADONORMAL||*estadoconfiguracion==FBLANCO||*estadoconfiguracion==FROJO||*estadoconfiguracion==FAMARILLO||*estadoconfiguracion==FVERDE||*estadoconfiguracion==FMORADO||*estadoconfiguracion==FCELESTE||*estadoconfiguracion==FNARANJA||*estadoconfiguracion==FROSA){
                                    *estadoconfiguracion=USUARIO;
                                    break;
                            }  
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                            *pestado=PANTALLAPRINCIPAL; //tecla roja,colgar
                            break;  //sin importar nada salgo al menu
                    }
                    
                    
                }
                
                }  
            }
        }
    
    

    return 0;
}

void mantenerconfiguracion(int * estadoconfiguracion,ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla){
    ALLEGRO_BITMAP* resetpantalla=NULL;
    resetpantalla=al_create_bitmap(400,400);    //importante para poner en blanco la pantalla y empezar con mi estado
    if(resetpantalla==NULL){
        fprintf(stderr,"Error al abrir bitmap\n");
        exit -1;
    }
    al_set_target_bitmap(resetpantalla);
    al_clear_to_color(al_map_rgb(255,255,255));
    
    ALLEGRO_FONT* fuente=NULL;
    fuente=crearfuente(MEDIA);
    if(fuente==NULL){fprintf(stderr,"No cargo la fuente\n");exit -1;}
    
    cambiopantalla(display,pantalla);
    al_draw_bitmap(resetpantalla,0,15,0);
    cambiopantalla(display,pantalla);
    
    ALLEGRO_BITMAP* seleccionar=NULL;
    seleccionar=al_create_bitmap(285,22);
    if(seleccionar==NULL){
        fprintf(stderr,"Error al abrir el bitmaaap\n");
        exit -1;
    }
    al_set_target_bitmap(seleccionar);                  //al igual que en el del menu, señalizara lo apuntado
    al_clear_to_color(al_map_rgb(150,150,150));
    if(*estadoconfiguracion==USUARIO||*estadoconfiguracion==COMPANIA||*estadoconfiguracion==MENSAJEPERSONAL||*estadoconfiguracion==TIPOESCRITURA||*estadoconfiguracion==FONDO){
    if(*estadoconfiguracion==USUARIO){
        cambiopantalla(display,pantalla);
        al_draw_bitmap(seleccionar,0,CONF1,0);
        cambiopantalla(display,pantalla);
    } else if(*estadoconfiguracion==COMPANIA){
        cambiopantalla(display,pantalla);
        al_draw_bitmap(seleccionar,0,CONF2,0);
        cambiopantalla(display,pantalla);
    }else if(*estadoconfiguracion==MENSAJEPERSONAL){
        cambiopantalla(display,pantalla);               //pongo la "seleccion" en el lugar donde se eligio
        al_draw_bitmap(seleccionar,0,CONF3,0);
        cambiopantalla(display,pantalla);
    }else if(*estadoconfiguracion==TIPOESCRITURA){
        cambiopantalla(display,pantalla);
        al_draw_bitmap(seleccionar,0,CONF4,0);
        cambiopantalla(display,pantalla);
    }else if(*estadoconfiguracion==FONDO){
        cambiopantalla(display,pantalla);
        al_draw_bitmap(seleccionar,0,CONF5,0);
        cambiopantalla(display,pantalla);
    }
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF1,ALLEGRO_ALIGN_LEFT,"Usuario");
    al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF2,ALLEGRO_ALIGN_LEFT,"Cambiar compania");
    al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF3,ALLEGRO_ALIGN_LEFT,"Mensaje Personal");
    al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF4,ALLEGRO_ALIGN_LEFT,"Tipo Escritura");
    al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF5,ALLEGRO_ALIGN_LEFT,"Fondo");
    cambiopantalla(display,pantalla);
    
    
    
    }else if(*estadoconfiguracion==INUSUARIO){
        //aca la fucion para leer teclado ira que analice cual es el nombre del usuario
    } else if(*estadoconfiguracion==INCOMPANIA||*estadoconfiguracion==CMOVISTAR||*estadoconfiguracion==CPERSONAL||*estadoconfiguracion==CCLARO||*estadoconfiguracion==CNEXTEL){
            if(*estadoconfiguracion==CMOVISTAR){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,CONF1,0);
            cambiopantalla(display,pantalla);
        } else if(*estadoconfiguracion==CPERSONAL){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,CONF2,0);
            cambiopantalla(display,pantalla);
        }else if(*estadoconfiguracion==CCLARO){
            cambiopantalla(display,pantalla);               //pongo la "seleccion" en el lugar donde se eligio
            al_draw_bitmap(seleccionar,0,CONF3,0);
            cambiopantalla(display,pantalla);
        }else if(*estadoconfiguracion==CNEXTEL){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,CONF4,0);
            cambiopantalla(display,pantalla);
        }
        
        cambiopantalla(display,pantalla);
        al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF1,ALLEGRO_ALIGN_LEFT,"Movistar");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF2,ALLEGRO_ALIGN_LEFT,"Personal");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF3,ALLEGRO_ALIGN_LEFT,"Claro");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF4,ALLEGRO_ALIGN_LEFT,"Nextel");
        cambiopantalla(display,pantalla);
        
        
    } else if(*estadoconfiguracion==TT9||*estadoconfiguracion==CLASICO||*estadoconfiguracion==TECLADONORMAL){
        if(*estadoconfiguracion==TT9){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,CONF1,0);
            cambiopantalla(display,pantalla);
        } else if(*estadoconfiguracion==CLASICO){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,CONF2,0);
            cambiopantalla(display,pantalla);
        }else if(*estadoconfiguracion==TECLADONORMAL){
            cambiopantalla(display,pantalla);               //pongo la "seleccion" en el lugar donde se eligio
            al_draw_bitmap(seleccionar,0,CONF3,0);
            cambiopantalla(display,pantalla);
        }
        
        cambiopantalla(display,pantalla);
        al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF1,ALLEGRO_ALIGN_LEFT,"Texto Predictivo");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF2,ALLEGRO_ALIGN_LEFT,"Texto Clasico");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF3,ALLEGRO_ALIGN_LEFT,"Teclado Analogo");
        cambiopantalla(display,pantalla);
    }   else if(*estadoconfiguracion==FBLANCO||*estadoconfiguracion==FROJO||*estadoconfiguracion==FAMARILLO||*estadoconfiguracion==FVERDE||*estadoconfiguracion==FMORADO||*estadoconfiguracion==FCELESTE||*estadoconfiguracion==FNARANJA||*estadoconfiguracion==FROSA){
        if(*estadoconfiguracion==FBLANCO){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,20,0);
            cambiopantalla(display,pantalla);
        } else if(*estadoconfiguracion==FROJO){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,45,0);
            cambiopantalla(display,pantalla);
        }else if(*estadoconfiguracion==FAMARILLO){
            cambiopantalla(display,pantalla);               //pongo la "seleccion" en el lugar donde se eligio
            al_draw_bitmap(seleccionar,0,70,0);
            cambiopantalla(display,pantalla);
        }else if(*estadoconfiguracion==FVERDE){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,95,0);
            cambiopantalla(display,pantalla);
        }else if(*estadoconfiguracion==FMORADO){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,120,0);
            cambiopantalla(display,pantalla);
        }else if(*estadoconfiguracion==FCELESTE){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,145,0);
            cambiopantalla(display,pantalla);
        }else if(*estadoconfiguracion==FNARANJA){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,170,0);
            cambiopantalla(display,pantalla);
        }else if(*estadoconfiguracion==FROSA){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,195,0);
            cambiopantalla(display,pantalla);
        }
        cambiopantalla(display,pantalla);
        al_draw_text(fuente,al_map_rgb(0,0,0),25,20,ALLEGRO_ALIGN_LEFT,"Blanco");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,45,ALLEGRO_ALIGN_LEFT,"Rojo");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,70,ALLEGRO_ALIGN_LEFT,"Amarillo");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,95,ALLEGRO_ALIGN_LEFT,"Verde");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,120,ALLEGRO_ALIGN_LEFT,"Morado");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,145,ALLEGRO_ALIGN_LEFT,"Celeste");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,170,ALLEGRO_ALIGN_LEFT,"Naranja");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,195,ALLEGRO_ALIGN_LEFT,"Rosa");
    
        cambiopantalla(display,pantalla);
        
        
    }
    
    
    
    
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),0,270,ALLEGRO_ALIGN_LEFT,"Seleccionar");         //creo boton menu o cualquier otro boton que quiera poner
    al_draw_text(fuente,al_map_rgb(0,0,0),210,270,ALLEGRO_ALIGN_RIGHT,"Volver");
    cambiopantalla(display,pantalla);
    
    
    al_destroy_font(fuente);
    al_destroy_bitmap(seleccionar);
    al_destroy_bitmap(resetpantalla);
}
