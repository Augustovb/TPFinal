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

void mantenerpantalla(INFOPANTALLA datos,ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla){
    ALLEGRO_BITMAP* compania;
    ALLEGRO_FONT* fuente;
    ALLEGRO_BITMAP* partearriba=NULL;        //sera un bitmp color grisaceo para darle mas armonia al menu principal
    
    ALLEGRO_BITMAP* fondo;
    fondo=al_create_bitmap(285,300);
    al_set_target_bitmap(fondo);
    if(datos.fondo.entro!=0){
        if (datos.fondo.entro==ROJO){
            al_clear_to_color(al_map_rgb(255,0,0));
        } else if(datos.fondo.entro==AMARILLO){
            al_clear_to_color(al_map_rgb(255,255,0));
        }else if(datos.fondo.entro==VERDE){
            al_clear_to_color(al_map_rgb(0,255,0));
        }else if(datos.fondo.entro==MORADO){
            al_clear_to_color(al_map_rgb(255,0,255));
        }else if(datos.fondo.entro==CELESTE){
            al_clear_to_color(al_map_rgb(102,255,255));
        }else if(datos.fondo.entro==NARANJA){
            al_clear_to_color(al_map_rgb(255,153,0));
        }else if(datos.fondo.entro==ROSA){
            al_clear_to_color(al_map_rgb(255,153,153));
        }
    } else {al_clear_to_color(al_map_rgb(255,255,255));}
    cambiopantalla(display,pantalla);
    al_draw_bitmap(fondo,0,15,0);
    cambiopantalla(display,pantalla);
    
    
    partearriba=al_create_bitmap(285,15);
    if(partearriba==NULL){fprintf(stderr,"Error al cargar el bitmap.\nEXITING PROGRAM \n"); exit-1;}
    
    al_set_target_bitmap(partearriba);
    al_clear_to_color(al_map_rgb(50,50,200));
    
    
    /*En datos. compania no debe haber otra cosa mas que un 0 1 2 o 3, si no, esto no tiene sentido*/
    if (datos.compania==PERSONAL){                  //si me dice que la persona es usuario de personal
        
        fuente=crearfuente(PEQUENA);
        
        
        cambiopantalla(display,pantalla);
        al_draw_bitmap(partearriba,0,0,0);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,0,ALLEGRO_ALIGN_LEFT,"Personal");
        cambiopantalla(display,pantalla);
        
        
    } else if(datos.compania==MOVISTAR){            //mismo procedimiento con movistar, nextel o claro
        if(datos.fondo.entro!=0){        //si al principio es distinto de lo predeterminado le cambio el fondo, sino no
            ALLEGRO_BITMAP* fondo=NULL;
            fondo=al_create_bitmap(300,300);    //mas grande total es solo en la pantalla
            al_set_target_bitmap(fondo);
            al_clear_to_color(datos.fondo.colorfondo);
            cambiopantalla(display,pantalla);
            al_draw_bitmap(fondo,0,0,0);
            cambiopantalla(display,pantalla);
            
        }
        fuente=crearfuente(PEQUENA);
        
        
        cambiopantalla(display,pantalla);
        al_draw_bitmap(partearriba,0,0,0);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,0,ALLEGRO_ALIGN_LEFT,"Movistar");
        cambiopantalla(display,pantalla); 
        
        
    } else if(datos.compania==CLARO){            
        if(datos.fondo.entro!=0){        //si al principio es distinto de lo predeterminado le cambio el fondo, sino no
            ALLEGRO_BITMAP* fondo=NULL;
            fondo=al_create_bitmap(300,300);    //mas grande total es solo en la pantalla
            al_set_target_bitmap(fondo);
            al_clear_to_color(datos.fondo.colorfondo);
            cambiopantalla(display,pantalla);
            al_draw_bitmap(fondo,0,0,0);
            cambiopantalla(display,pantalla);
            
        }
        fuente=crearfuente(PEQUENA);
        
        
        cambiopantalla(display,pantalla);
        al_draw_bitmap(partearriba,0,0,0);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,0,ALLEGRO_ALIGN_LEFT,"Claro");
        cambiopantalla(display,pantalla); 
        
        
    } else if(datos.compania==NEXTEL){              //es solo para agregar variedad, ya que no tiene sentido un nokia con compania NEXTEL         
        if(datos.fondo.entro!=0){        //si al principio es distinto de lo predeterminado le cambio el fondo, sino no
            ALLEGRO_BITMAP* fondo=NULL;
            fondo=al_create_bitmap(300,300);    //mas grande total es solo en la pantalla
            al_set_target_bitmap(fondo);
            al_clear_to_color(datos.fondo.colorfondo);
            cambiopantalla(display,pantalla);
            al_draw_bitmap(fondo,0,0,0);
            cambiopantalla(display,pantalla);
            
        }
        fuente=crearfuente(PEQUENA);
        
        
        
        cambiopantalla(display,pantalla);
        al_draw_bitmap(partearriba,0,0,0);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,0,ALLEGRO_ALIGN_LEFT,"Nextel");
        cambiopantalla(display,pantalla); 
    }
    
    //me encargare del nombre del usuario
    
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),106,0,ALLEGRO_ALIGN_CENTRE,datos.usuario);    //106 es para que este en el medio del bitmap (long 213 de x) y datos.usuario es un char*
    al_draw_text(fuente,al_map_rgb(0,0,0),213,0,ALLEGRO_ALIGN_RIGHT,__TIME__);
    cambiopantalla(display,pantalla);
    
    cambiopantalla(display,pantalla);           //aqui se escribira el mensaje personal elegido por el usuario, e su color elegido y tamaño
    fuente=crearfuente(datos.tamanomensaje);
    
    if(datos.mensajecolor.tipocolor!=0){
        if (datos.mensajecolor.tipocolor==ROJO){
            al_draw_text(fuente,al_map_rgb(255,0,0),0,30,ALLEGRO_ALIGN_LEFT,datos.mensajepersonal);
            
        } else if(datos.mensajecolor.tipocolor==AMARILLO){
            al_draw_text(fuente,al_map_rgb(255,255,0),0,30,ALLEGRO_ALIGN_LEFT,datos.mensajepersonal);
            
        }else if(datos.mensajecolor.tipocolor==VERDE){
            al_draw_text(fuente,al_map_rgb(0,255,0),0,30,ALLEGRO_ALIGN_LEFT,datos.mensajepersonal);
            
        }else if(datos.mensajecolor.tipocolor==MORADO){
            al_draw_text(fuente,al_map_rgb(255,0,255),0,30,ALLEGRO_ALIGN_LEFT,datos.mensajepersonal);
            
        }else if(datos.mensajecolor.tipocolor==CELESTE){
            al_draw_text(fuente,al_map_rgb(102,255,255),0,30,ALLEGRO_ALIGN_LEFT,datos.mensajepersonal);
            
        }else if(datos.mensajecolor.tipocolor==NARANJA){
            al_draw_text(fuente,al_map_rgb(255,153,0),0,30,ALLEGRO_ALIGN_LEFT,datos.mensajepersonal);
            
        }else if(datos.mensajecolor.tipocolor==ROSA){
            al_draw_text(fuente,al_map_rgb(255,153,153),0,30,ALLEGRO_ALIGN_LEFT,datos.mensajepersonal);
            
        }
    } else {al_draw_text(fuente,al_map_rgb(0,0,0),0,30,ALLEGRO_ALIGN_LEFT,datos.mensajepersonal);}

    cambiopantalla(display,pantalla);
    
    
    fuente=crearfuente(MEDIA);
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),0,270,ALLEGRO_ALIGN_LEFT,"Menu");         //creo boton menu o cualquier otro boton que quiera poner
    cambiopantalla(display,pantalla);
    
    al_destroy_font(fuente);
    al_destroy_bitmap(compania);
    al_destroy_bitmap(partearriba);
    al_destroy_bitmap(fondo);
}
void iniciarpantalla(INFOPANTALLA datos, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla){       //chequear que el mensaje personal no se pase de 140
    ALLEGRO_BITMAP* compania;
    ALLEGRO_FONT* fuente;
    ALLEGRO_BITMAP* partearriba=NULL;        //sera un bitmp color grisaceo para darle mas armonia al menu principal
    
    partearriba=al_create_bitmap(285,15);
    if(partearriba==NULL){fprintf(stderr,"Error al cargar el bitmap.\nEXITING PROGRAM \n"); exit-1;}
    
    al_set_target_bitmap(partearriba);
    al_clear_to_color(al_map_rgb(50,50,200));
    
    
    /*En datos. compania no debe haber otra cosa mas que un 0 1 2 o 3, si no, esto no tiene sentido*/
    if (datos.compania==PERSONAL){                  //si me dice que la persona es usuario de personal
        compania=al_load_bitmap("personal.png");
        fuente=crearfuente(PEQUENA);
        
        cambiopantalla(display,pantalla);                                               //prendo la pantalla con su nombre
        al_draw_bitmap(compania,-60,0,0);
        cambiopantalla(display,pantalla);
        
        sleep(4);                               //espero 2 segundos de manera que parezca que se esta prendiendo
        
        cambiopantalla(display,pantalla);
        al_draw_bitmap(partearriba,0,0,0);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,0,ALLEGRO_ALIGN_LEFT,"Personal");
        cambiopantalla(display,pantalla);
        
        
    } else if(datos.compania==MOVISTAR){            //mismo procedimiento con movistar, nextel o claro
        compania=al_load_bitmap("movistar.png");
        fuente=crearfuente(PEQUENA);
        
        cambiopantalla(display,pantalla);                                               //prendo la pantalla con su nombre
        al_draw_bitmap(compania,-60,0,0);
        cambiopantalla(display,pantalla);
        
        sleep(4);                               //espero 2 segundos de manera que parezca que se esta prendiendo
        
        cambiopantalla(display,pantalla);
        al_draw_bitmap(partearriba,0,0,0);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,0,ALLEGRO_ALIGN_LEFT,"Movistar");
        cambiopantalla(display,pantalla); 
        
        
    } else if(datos.compania==CLARO){            
        compania=al_load_bitmap("claro.png");
        fuente=crearfuente(PEQUENA);
        
        cambiopantalla(display,pantalla);                                               
        al_draw_bitmap(compania,-60,0,0);
        cambiopantalla(display,pantalla);
        
        sleep(4);                               
        
        cambiopantalla(display,pantalla);
        al_draw_bitmap(partearriba,0,0,0);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,0,ALLEGRO_ALIGN_LEFT,"Claro");
        cambiopantalla(display,pantalla); 
        
        
    } else if(datos.compania==NEXTEL){              //es solo para agregar variedad, ya que no tiene sentido un nokia con compania NEXTEL         
        compania=al_load_bitmap("nextel.png");
        fuente=crearfuente(PEQUENA);
        
        cambiopantalla(display,pantalla);                                               //prendo la pantalla con su nombre
        al_draw_bitmap(compania,-60,0,0);
        cambiopantalla(display,pantalla);
        
        sleep(4);                               //espero 2 segundos de manera que parezca que se esta prendiendo
        
        cambiopantalla(display,pantalla);
        al_draw_bitmap(partearriba,0,0,0);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,0,ALLEGRO_ALIGN_LEFT,"Nextel");
        cambiopantalla(display,pantalla); 
    }
    
    //me encargare del nombre del usuario
    
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),106,0,ALLEGRO_ALIGN_CENTRE,datos.usuario);    //106 es para que este en el medio del bitmap (long 213 de x) y datos.usuario es un char*
    al_draw_text(fuente,al_map_rgb(0,0,0),213,0,ALLEGRO_ALIGN_RIGHT,__TIME__);
    cambiopantalla(display,pantalla);
    
    cambiopantalla(display,pantalla);           //aqui se escribira el mensaje personal elegido por el usuario, e su color elegido y tamaño
    fuente=crearfuente(datos.tamanomensaje);
    al_draw_text(fuente,datos.mensajecolor.colormensaje,0,30,ALLEGRO_ALIGN_LEFT,datos.mensajepersonal);
    cambiopantalla(display,pantalla);
    
    
    fuente=crearfuente(MEDIA);
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),0,270,ALLEGRO_ALIGN_LEFT,"Menu");         //creo boton menu o cualquier otro boton que quiera poner
    cambiopantalla(display,pantalla);
    
    
}
void mantenermenu(int* pestado, int* estadomenu,ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla,INFOPANTALLA mipantalla){
    
    ALLEGRO_FONT* fuente;
    fuente=crearfuente(MEDIA);
    ALLEGRO_BITMAP* seleccion;      //SERA EL bitmap que marque lo que esta seleccionado
    ALLEGRO_BITMAP* fondo;
    fondo=al_create_bitmap(285,300);
    al_set_target_bitmap(fondo);
    al_clear_to_color(al_map_rgb(255,255,255));
    cambiopantalla(display,pantalla);
    al_draw_bitmap(fondo,0,15,0);
    cambiopantalla(display,pantalla);
    
    ALLEGRO_BITMAP* mensaje=NULL;
    ALLEGRO_BITMAP* personalizar=NULL;       //seran las fotos que usaran como "iconos"
    mensaje=al_load_bitmap("mensaje.png");
    personalizar=al_load_bitmap("personalizar.png");
    if(mensaje==NULL||personalizar==NULL){
        fprintf(stderr,"Error al cargar imagen");
        exit -1;
    }
    
    
    seleccion=al_create_bitmap(285,22);
    al_set_target_bitmap(seleccion);
    al_clear_to_color(al_map_rgb(150,150,150));
    
    if(*estadomenu==POS1){
        cambiopantalla(display,pantalla);
        al_draw_bitmap(seleccion,0,POS1,0);
        cambiopantalla(display,pantalla);
    } else if(*estadomenu==POS2){
        cambiopantalla(display,pantalla);
        al_draw_bitmap(seleccion,0,POS2,0);
        cambiopantalla(display,pantalla);
    }else if(*estadomenu==POS3){
        cambiopantalla(display,pantalla);               //pongo la "seleccion" en el lugar donde se eligio
        al_draw_bitmap(seleccion,0,POS3,0);
        cambiopantalla(display,pantalla);
    }else if(*estadomenu==POS4){
        cambiopantalla(display,pantalla);
        al_draw_bitmap(seleccion,0,POS4,0);
        cambiopantalla(display,pantalla);
    }
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),25,POS1,ALLEGRO_ALIGN_LEFT,"Mensaje");
    al_draw_bitmap(mensaje,-3,POS1-4,0);
    al_draw_text(fuente,al_map_rgb(0,0,0),25,POS2,ALLEGRO_ALIGN_LEFT,"Configuración");
    al_draw_bitmap(personalizar,0,POS2,0);
    cambiopantalla(display,pantalla);
    
    
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),0,270,ALLEGRO_ALIGN_LEFT,"Seleccionar");         //creo boton menu o cualquier otro boton que quiera poner
    al_draw_text(fuente,al_map_rgb(0,0,0),210,270,ALLEGRO_ALIGN_RIGHT,"Volver");
    cambiopantalla(display,pantalla);
    
    al_destroy_bitmap(seleccion);
    al_destroy_bitmap(fondo);
    al_destroy_font(fuente);
    al_destroy_bitmap(mensaje);
    al_destroy_bitmap(personalizar);
}   //debo setear cuando vuelva en estadomenu a pos1
int analizartecladomenu (ALLEGRO_EVENT_QUEUE* eventos,int* pestado,int* estadomenu){
        //de aca en adelante es simplemente la funcionde leerteclado que por comodidad no la pongo afuera
    
    
    while(1){                   // esto es la funcion que lee de donde se clickeo
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventos,&ev);
        
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            *pestado=FINALIZAR;
            break;
        } else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(ev.mouse.button & 1){
                //aca iran los ifs que veran el ev.mouse.x y el ev.mouse.y
                if(ev.mouse.x>30&&ev.mouse.x<110){      //pueden ser el select, llamar,1,4,7,*
                    if(ev.mouse.y>450&&ev.mouse.y<490){
                            if(*estadomenu==POS1){*pestado=MENSAJE;break;}
                            else if(*estadomenu==POS2){*pestado=PERSONALIZAR;break;}  //se presiono la teclaselect
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                              //tecla verde, llamar
                    }
                    else if(ev.mouse.y>540&&ev.mouse.y<585){
                                  //tecla 1
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                                   //tecla 4
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                                   //tecla7
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720&&ev.mouse.x>50){
                                //tecla asterisco
                    }    
                } else if(ev.mouse.x>110&&ev.mouse.x<208){  //son las teclas de la linea media que incluyen los centrales
                    //analizo primero lo de las "flechitas"y el boton del medio
                    if(ev.mouse.y>450&&ev.mouse.y<460){
                            if(*estadomenu==POS1){continue;}  //tecla para arrriba
                            if(*estadomenu==POS2){*estadomenu=POS1; break;}     //(subo)
                            
                            
                    } else if (ev.mouse.y>525&&ev.mouse.y<540){
                            if(*estadomenu==POS1){*estadomenu=POS2; break;}//teclaparaabajo
                            if(*estadomenu==POS2){continue;}
                    } else if(ev.mouse.y>460&&ev.mouse.y<540){  //der, izq o medio
                                if(ev.mouse.x<130){
                                         //hacia la izquierda
                                } else if(ev.mouse.x>188){
                                             //la de la derecha
                                } else{
                                    if(*estadomenu==POS1){*pestado=MENSAJE;break;}
                                    else if(*estadomenu==POS2){*pestado=PERSONALIZAR;break;}
                                }     //la del medio
                    } else if(ev.mouse.y>540&&ev.mouse.y<585){
                                   //tecla 2
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                                   //tecla 5
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                                   //tecla8
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720){
                                 //tecla 0
                    } 
                    
                } else if(ev.mouse.x>208&&ev.mouse.x<288){      //pueden ser back,colgar,3,6,9 o numeral
                    if(ev.mouse.y>450&&ev.mouse.y<490){
                        *pestado=PANTALLAPRINCIPAL;      //se presiono la tecla back
                        break;
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                        *pestado=PANTALLAPRINCIPAL;     //tecla roja,colgar
                        break;
                    }
                    else if(ev.mouse.y>540&&ev.mouse.y<585){
                                   //tecla 3
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                                   //tecla 6
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                                   //tecla9
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720&&ev.mouse.x<268){
                                 //tecla asterisco
                }
                
                }  
            }
        }
    }
    

    return 0;
}
void cambiopantalla (ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla){
    static bool modificopantalla=false;
    if(!modificopantalla){
        al_set_target_bitmap(pantalla);
        
        modificopantalla=!modificopantalla;
    } else if(modificopantalla){
        al_set_target_bitmap(al_get_backbuffer(display));       
        al_draw_bitmap(pantalla,48,118,0);
        al_flip_display();  
        
        modificopantalla=!modificopantalla;
    }
    
}
int analizartecladopantalla (ALLEGRO_EVENT_QUEUE* eventos,int* pestado,ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla ){            //lo unico para clickear es el menu
        //de aca en adelante es simplemente la funcionde leerteclado que por comodidad no la pongo afuera
    
    
    while(1){                   // esto es la funcion que lee de donde se clickeo
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventos,&ev);
        
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            *pestado=FINALIZAR;
            break;
        } else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(ev.mouse.button & 1){
                //aca iran los ifs que veran el ev.mouse.x y el ev.mouse.y
                if(ev.mouse.x>30&&ev.mouse.x<110){      //pueden ser el select, llamar,1,4,7,*
                    if(ev.mouse.y>450&&ev.mouse.y<490){
                        *pestado=MENU;      //se presiono la teclaselect
                        break;
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                              //tecla verde, llamar
                    }
                    else if(ev.mouse.y>540&&ev.mouse.y<585){
                                  //tecla 1
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                                   //tecla 4
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                                   //tecla7
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720&&ev.mouse.x>50){
                                //tecla asterisco
                    }    
                } else if(ev.mouse.x>110&&ev.mouse.x<208){  //son las teclas de la linea media que incluyen los centrales
                    //analizo primero lo de las "flechitas"y el boton del medio
                    if(ev.mouse.y>450&&ev.mouse.y<460){
                              //tecla para arrriba
                    } else if (ev.mouse.y>525&&ev.mouse.y<540){
                            //teclaparaabajo
                    } else if(ev.mouse.y>460&&ev.mouse.y<540){  //der, izq o medio
                                if(ev.mouse.x<130){
                                         //hacia la izquierda
                                } else if(ev.mouse.x>188){
                                             //la de la derecha
                                } else{}     //la del medio
                    } else if(ev.mouse.y>540&&ev.mouse.y<585){
                                   //tecla 2
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                                   //tecla 5
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                                   //tecla8
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720){
                                 //tecla 0
                    } 
                    
                } else if(ev.mouse.x>208&&ev.mouse.x<288){      //pueden ser back,colgar,3,6,9 o numeral
                    if(ev.mouse.y>450&&ev.mouse.y<490){
                              //se presiono la tecla back
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                             //tecla roja,colgar
                    }
                    else if(ev.mouse.y>540&&ev.mouse.y<585){
                                   //tecla 3
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                                   //tecla 6
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                                   //tecla9
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720&&ev.mouse.x<268){
                                 //tecla asterisco
                }
                
                }  
            }
        }
       
    }
    

    return 0;
}
int analizarteclado (ALLEGRO_EVENT_QUEUE* eventos){
        //de aca en adelante es simplemente la funcionde leerteclado que por comodidad no la pongo afuera
    
    
    while(1){                   // esto es la funcion que lee de donde se clickeo
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventos,&ev);
        
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        } else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(ev.mouse.button & 1){
                //aca iran los ifs que veran el ev.mouse.x y el ev.mouse.y
                if(ev.mouse.x>30&&ev.mouse.x<110){      //pueden ser el select, llamar,1,4,7,*
                    if(ev.mouse.y>450&&ev.mouse.y<490){
                              //se presiono la teclaselect
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                              //tecla verde, llamar
                    }
                    else if(ev.mouse.y>540&&ev.mouse.y<585){
                                  //tecla 1
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                                   //tecla 4
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                                   //tecla7
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720&&ev.mouse.x>50){
                                //tecla asterisco
                    }    
                } else if(ev.mouse.x>110&&ev.mouse.x<208){  //son las teclas de la linea media que incluyen los centrales
                    //analizo primero lo de las "flechitas"y el boton del medio
                    if(ev.mouse.y>450&&ev.mouse.y<460){
                              //tecla para arrriba
                    } else if (ev.mouse.y>525&&ev.mouse.y<540){
                            //teclaparaabajo
                    } else if(ev.mouse.y>460&&ev.mouse.y<540){  //der, izq o medio
                                if(ev.mouse.x<130){
                                         //hacia la izquierda
                                } else if(ev.mouse.x>188){
                                             //la de la derecha
                                } else{}     //la del medio
                    } else if(ev.mouse.y>540&&ev.mouse.y<585){
                                   //tecla 2
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                                   //tecla 5
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                                   //tecla8
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720){
                                 //tecla 0
                    } 
                    
                } else if(ev.mouse.x>208&&ev.mouse.x<288){      //pueden ser back,colgar,3,6,9 o numeral
                    if(ev.mouse.y>450&&ev.mouse.y<490){
                              //se presiono la tecla back
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                             //tecla roja,colgar
                    }
                    else if(ev.mouse.y>540&&ev.mouse.y<585){
                                   //tecla 3
                    }
                    else if(ev.mouse.y>585&&ev.mouse.y<630){
                                   //tecla 6
                    }
                    else if(ev.mouse.y>630&&ev.mouse.y<675){
                                   //tecla9
                    }
                    else if(ev.mouse.y>675&&ev.mouse.y<720&&ev.mouse.x<268){
                                 //tecla asterisco
                }
                
                }  
            }
        }
    }
    

    return 0;
}
ALLEGRO_DISPLAY* getdisplay(int ancho, int alto){
    
    ALLEGRO_DISPLAY* display=NULL;
    
    display=al_create_display(ancho,alto);
    if(display==NULL){
        fprintf(stderr,"No se pudo inicializar el display\n"); 
        return ERROR;
    }    //inicializar display
    
    return display;
}
ALLEGRO_EVENT_QUEUE* geteventqueue (void){
    
    ALLEGRO_EVENT_QUEUE* eventos=NULL;
    
    eventos=al_create_event_queue();
    
    if(eventos==NULL){
        fprintf(stderr,"No se inicializo el event queue.\n");
        
        return ERROR;
        
    }     //inicializo el event queue
    
    return eventos;
    
}
ALLEGRO_TIMER* gettimer (float periodo){
    ALLEGRO_TIMER* timer=NULL;
    
    timer=al_create_timer(periodo);
    if(timer==NULL){
        fprintf(stderr,"No se pudo inicializar el timer\n");
        return ERROR;
    }
    
    return timer;
    
}
ALLEGRO_FONT* crearfuente (int tamano){
    ALLEGRO_FONT* fuente=NULL;
    
    fuente=al_load_ttf_font("PTS55F.ttf",tamano,0);      //cargo la fuente predeterminada con el tamano pedido
    
    
    if (fuente==NULL){
        fprintf(stderr,"No se pudo cargar la imagen, el programa finalizara.\n");
        sleep(2);
        exit -1;
    }
    
    return fuente;
    
}
int inicializar (void){
    
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
    
    
    
    return 0;
}
INFOPANTALLA getuserdata(void){
    FILE* miarchivo=NULL;
    unsigned int i=0,j=0;   //contadores
    INFOPANTALLA pantalla;
    ALLEGRO_COLOR color;
    unsigned int check=0;       //esta varible sera para ver el numero con el que se pide el color
    char ayuda[5]={0,0,0,0,0};      //este arreglo para lo que sirve es para ir guardando los ascii para despues pasarlos a ints
    char caracter;
    
    char defaults[140];
    
    
    miarchivo=fopen("configuracion.txt","r");
    if(miarchivo==NULL){
        miarchivo=fopen("default.txt","r");
        while (((caracter = fgetc (miarchivo)) != '\n')) { 
                    *(defaults+j) = caracter;
                    j++; 
        }
        defaults[j]=0;
        j=0;
        strcpy(pantalla.usuario,defaults);
        
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        pantalla.compania=atoi(ayuda);
        while(i<5){
            ayuda[i]=0;
            ++i;
        }
        i=0;
        
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        check=atoi(ayuda);
        if(check==NOCAMBIO){
            pantalla.fondo.entro=0;
        }else if(check==ROJO){
            pantalla.fondo.entro=ROJO;
            pantalla.fondo.colorfondo=al_map_rgb(255,0,0);
        }else if(check==AMARILLO){
            pantalla.fondo.entro=AMARILLO;
            pantalla.fondo.colorfondo=al_map_rgb(255,255,0);
        }else if(check==VERDE){
            pantalla.fondo.entro=VERDE;
            pantalla.fondo.colorfondo=al_map_rgb(0,255,0);
        }else if(check==MORADO){
            pantalla.fondo.entro=MORADO;
            pantalla.fondo.colorfondo=al_map_rgb(255,0,255);
        }else if(check==CELESTE){
            pantalla.fondo.entro=CELESTE;
            pantalla.fondo.colorfondo=al_map_rgb(102,255,255);
        }else if(check==NARANJA){
            pantalla.fondo.entro=NARANJA;
            pantalla.fondo.colorfondo=al_map_rgb(255,153,0);
        }else if(check==ROSA){
            pantalla.fondo.entro=ROSA;
            pantalla.fondo.colorfondo=al_map_rgb(255,153,153);
        }
        
        while(i<5){
            ayuda[i]=0;
            ++i;
        }
        i=0;
        
        while (((caracter = fgetc (miarchivo)) != '\n')) { 
                    *(defaults+j) = caracter;
                    j++; 
        }
        defaults[j]=0;
        j=0;
        strcpy(pantalla.mensajepersonal,defaults);
        
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        check=atoi(ayuda);
        if(check==NOCAMBIO){
            pantalla.mensajecolor.colormensaje=al_map_rgb(0,0,0);
            pantalla.mensajecolor.tipocolor=NOCAMBIO;
        }else if(check==ROJO){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,0,0);
            pantalla.mensajecolor.tipocolor=ROJO;
        }else if(check==AMARILLO){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,255,0);
            pantalla.mensajecolor.tipocolor=AMARILLO;
        }else if(check==VERDE){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(0,255,0);
            pantalla.mensajecolor.tipocolor=VERDE;
        }else if(check==MORADO){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,0,255);
            pantalla.mensajecolor.tipocolor=MORADO;
        }else if(check==CELESTE){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(102,255,255);
            pantalla.mensajecolor.tipocolor=CELESTE;
        }else if(check==NARANJA){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,153,0);
            pantalla.mensajecolor.tipocolor=NARANJA;
        }else if(check==ROSA){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,153,153);
            pantalla.mensajecolor.tipocolor=ROSA;
        }
        
        while(i<5){
            ayuda[i]=0;
            ++i;
        }
        i=0;
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        pantalla.tamanomensaje=atoi(ayuda);
        
        while(i<5){
            ayuda[i]=0;
            ++i;
        }
        i=0;
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        pantalla.tipoescritura=atoi(ayuda);   
    } else {
        while (((caracter = fgetc (miarchivo)) != '\n')) { 
                    *(defaults+j) = caracter;
                    j++; 
        }
        defaults[j]=0;
        j=0;
        strcpy(pantalla.usuario,defaults);
        
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        pantalla.compania=atoi(ayuda);
        while(i<5){
            ayuda[i]=0;
            ++i;
        }
        i=0;
        
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        check=atoi(ayuda);
        if(check==NOCAMBIO){
            pantalla.fondo.entro=0;
        }else if(check==ROJO){
            pantalla.fondo.entro=ROJO;
            pantalla.fondo.colorfondo=al_map_rgb(255,0,0);
        }else if(check==AMARILLO){
            pantalla.fondo.entro=AMARILLO;
            pantalla.fondo.colorfondo=al_map_rgb(255,255,0);
        }else if(check==VERDE){
            pantalla.fondo.entro=VERDE;
            pantalla.fondo.colorfondo=al_map_rgb(0,255,0);
        }else if(check==MORADO){
            pantalla.fondo.entro=MORADO;
            pantalla.fondo.colorfondo=al_map_rgb(255,0,255);
        }else if(check==CELESTE){
            pantalla.fondo.entro=CELESTE;
            pantalla.fondo.colorfondo=al_map_rgb(102,255,255);
        }else if(check==NARANJA){
            pantalla.fondo.entro=NARANJA;
            pantalla.fondo.colorfondo=al_map_rgb(255,153,0);
        }else if(check==ROSA){
            pantalla.fondo.entro=ROSA;
            pantalla.fondo.colorfondo=al_map_rgb(255,153,153);
        }
        
        while(i<5){
            ayuda[i]=0;
            ++i;
        }
        i=0;
        
        while (((caracter = fgetc (miarchivo)) != '\n')) { 
                    *(defaults+j) = caracter;
                    j++; 
        }
        defaults[j]=0;
        j=0;
        strcpy(pantalla.mensajepersonal,defaults);
        
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        check=atoi(ayuda);
        if(check==NOCAMBIO){
            pantalla.mensajecolor.colormensaje=al_map_rgb(0,0,0);
            pantalla.mensajecolor.tipocolor=NOCAMBIO;
        }else if(check==ROJO){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,0,0);
            pantalla.mensajecolor.tipocolor=ROJO;
        }else if(check==AMARILLO){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,255,0);
            pantalla.mensajecolor.tipocolor=AMARILLO;
        }else if(check==VERDE){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(0,255,0);
            pantalla.mensajecolor.tipocolor=VERDE;
        }else if(check==MORADO){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,0,255);
            pantalla.mensajecolor.tipocolor=MORADO;
        }else if(check==CELESTE){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(102,255,255);
            pantalla.mensajecolor.tipocolor=CELESTE;
        }else if(check==NARANJA){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,153,0);
            pantalla.mensajecolor.tipocolor=NARANJA;
        }else if(check==ROSA){
            
            pantalla.mensajecolor.colormensaje=al_map_rgb(255,153,153);
            pantalla.mensajecolor.tipocolor=ROSA;
        }
        
        while(i<5){
            ayuda[i]=0;
            ++i;
        }
        i=0;
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        pantalla.tamanomensaje=atoi(ayuda);
        
        while(i<5){
            ayuda[i]=0;
            ++i;
        }
        i=0;
        
        fgets(ayuda,sizeof(INFOPANTALLA),miarchivo);
        pantalla.tipoescritura=atoi(ayuda);
    }
    
    return pantalla;
    fclose(miarchivo);
}
void putuserdata (INFOPANTALLA mipantalla){
    FILE* miarchivo=NULL;
    miarchivo=fopen("configuracion.txt","w");       //siempre destruyo si ya existe
    if (miarchivo==NULL){
        fprintf(stderr,"No se pudo abrir el archivo\n");
        exit -1;
    }
    fprintf(miarchivo,"%s\n",mipantalla.usuario);
    
    fprintf(miarchivo,"%d\n",mipantalla.compania);
    fprintf(miarchivo,"%d\n",mipantalla.fondo.entro);
    fprintf(miarchivo,"%s\n",mipantalla.mensajepersonal);
    fprintf(miarchivo,"%d\n",mipantalla.mensajecolor.tipocolor);
    fprintf(miarchivo,"%d\n",mipantalla.tamanomensaje);
    fprintf(miarchivo,"%d\n",mipantalla.tipoescritura);
    
    return ;
    
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
                            if(*estadoconfiguracion==MENSAJEPERSONAL){*estadoconfiguracion=MPCOLOR; break;}
                            
                            else if(*estadoconfiguracion==COMPANIA){*estadoconfiguracion=CMOVISTAR; break;}
                            
                            else if(*estadoconfiguracion==CMOVISTAR){*estadoconfiguracion=COMPANIA; pantalla->compania=MOVISTAR; break; }
                            
                            else if(*estadoconfiguracion==CPERSONAL){*estadoconfiguracion=COMPANIA; pantalla->compania=PERSONAL; break;}
                            
                            else if(*estadoconfiguracion==CCLARO){*estadoconfiguracion=COMPANIA; pantalla->compania=CLARO; break;}
                            
                            else if(*estadoconfiguracion==CNEXTEL){*estadoconfiguracion=COMPANIA; pantalla->compania=NEXTEL; break;}
                            
                            else if(*estadoconfiguracion==TIPOESCRITURA){*estadoconfiguracion=TT9; break;}
                            
                            else if(*estadoconfiguracion==TT9){*estadoconfiguracion=TIPOESCRITURA; pantalla->tipoescritura=T9; break;}
                            
                            else if(*estadoconfiguracion==CLASICO){*estadoconfiguracion=TIPOESCRITURA; pantalla->tipoescritura=MODOLIBRE; break;}
                            
                            else if(*estadoconfiguracion==TECLADONORMAL){*estadoconfiguracion=TIPOESCRITURA; pantalla->tipoescritura=TECLADOANALOGO; break;}
                            else if(*estadoconfiguracion==FONDO){*estadoconfiguracion=FBLANCO; break;}
                            
                            else if(*estadoconfiguracion==FBLANCO){*estadoconfiguracion=FONDO; pantalla->fondo.entro=NOCAMBIO; break;}
                            
                            else if(*estadoconfiguracion==FROJO){*estadoconfiguracion=FONDO; pantalla->fondo.entro=ROJO; break;}
                            else if(*estadoconfiguracion==FAMARILLO){*estadoconfiguracion=FONDO; pantalla->fondo.entro=AMARILLO; break;}
                            else if(*estadoconfiguracion==FVERDE){*estadoconfiguracion=FONDO; pantalla->fondo.entro=VERDE; break;}
                            else if(*estadoconfiguracion==FMORADO){*estadoconfiguracion=FONDO; pantalla->fondo.entro=MORADO; break;}
                            else if(*estadoconfiguracion==FCELESTE){*estadoconfiguracion=FONDO; pantalla->fondo.entro=CELESTE; break;}
                            else if(*estadoconfiguracion==FNARANJA){*estadoconfiguracion=FONDO; pantalla->fondo.entro=NARANJA; break;}
                            else if(*estadoconfiguracion==FROSA){*estadoconfiguracion=FONDO; pantalla->fondo.entro=ROSA; break;}
                            
                            else if(*estadoconfiguracion==MPCOLOR){*estadoconfiguracion=MPROJO; break;}
                            else if(*estadoconfiguracion==MPTAMANO){*estadoconfiguracion=MPPEQUENA; break;}
                            else if(*estadoconfiguracion==MPTEXTO){printf("Todavia nadaaa!\n"); break;}
                            
                            else if(*estadoconfiguracion==MPBLANCO){*estadoconfiguracion=MPCOLOR; pantalla->mensajecolor.tipocolor=NOCAMBIO; break;}
                            else if(*estadoconfiguracion==MPROJO){*estadoconfiguracion=MPCOLOR; pantalla->mensajecolor.tipocolor=ROJO; break;}
                            else if(*estadoconfiguracion==MPAMARILLO){*estadoconfiguracion=MPCOLOR; pantalla->mensajecolor.tipocolor=AMARILLO; break;}
                            else if(*estadoconfiguracion==MPVERDE){*estadoconfiguracion=MPCOLOR; pantalla->mensajecolor.tipocolor=VERDE; break;}
                            else if(*estadoconfiguracion==MPMORADO){*estadoconfiguracion=MPCOLOR; pantalla->mensajecolor.tipocolor=MORADO; break;}
                            else if(*estadoconfiguracion==MPCELESTE){*estadoconfiguracion=MPCOLOR; pantalla->mensajecolor.tipocolor=CELESTE; break;}
                            else if(*estadoconfiguracion==MPNARANJA){*estadoconfiguracion=MPCOLOR; pantalla->mensajecolor.tipocolor=NARANJA; break;}
                            else if(*estadoconfiguracion==MPROSA){*estadoconfiguracion=MPCOLOR; pantalla->mensajecolor.tipocolor=ROSA; break;}
                            
                            else if(*estadoconfiguracion==TT9){*estadoconfiguracion=TIPOESCRITURA; pantalla->tipoescritura=T9; break;}
                            else if(*estadoconfiguracion==CLASICO){*estadoconfiguracion=TIPOESCRITURA; pantalla->tipoescritura=MODOLIBRE; break;}
                            else if(*estadoconfiguracion==TECLADONORMAL){*estadoconfiguracion=TIPOESCRITURA; pantalla->tipoescritura=TECLADOANALOGO; break;}
                            
                            
                            else if(*estadoconfiguracion==MPPEQUENA){*estadoconfiguracion=MPTAMANO; pantalla->tamanomensaje=PEQUENA; break;}
                            else if(*estadoconfiguracion==MMEDIA){*estadoconfiguracion=MPTAMANO; pantalla->tamanomensaje=MEDIA; break;}
                            else if(*estadoconfiguracion==MGRANDE){*estadoconfiguracion=MPTAMANO; pantalla->tamanomensaje=GRANDE; break;}
                            else if(*estadoconfiguracion==MGIGANTE){*estadoconfiguracion=MPTAMANO; pantalla->tamanomensaje=GIGANTE; break;}
                            
                    }
                       
                } else if(ev.mouse.x>110&&ev.mouse.x<208){  //son las teclas de la linea media que incluyen los centrales
                    //analizo primero lo de las "flechitas"y el boton del medio
                    if(ev.mouse.y>450&&ev.mouse.y<460){
                            if(*estadoconfiguracion==COMPANIA){*estadoconfiguracion=USUARIO; break;}  //tecla para arrriba
                            else if(*estadoconfiguracion==TT9){*estadoconfiguracion=TECLADONORMAL; break;}
                            else if(*estadoconfiguracion==CLASICO){*estadoconfiguracion=TT9; break;}
                            else if(*estadoconfiguracion==TECLADONORMAL){*estadoconfiguracion=CLASICO; break;}
                            else if(*estadoconfiguracion==MPCOLOR){*estadoconfiguracion=MPTAMANO; break;}
                           else if(*estadoconfiguracion==MPTAMANO){*estadoconfiguracion=MPTEXTO; break;}
                           else if(*estadoconfiguracion==MPTEXTO){*estadoconfiguracion=MPCOLOR; break;}
                            
                            
                            
                            else if(*estadoconfiguracion==USUARIO){*estadoconfiguracion=FONDO; break;}
                            
                            else if(*estadoconfiguracion==COMPANIA){*estadoconfiguracion=USUARIO; break;}
                            
                            else if(*estadoconfiguracion==CPERSONAL){*estadoconfiguracion=CMOVISTAR; break;}
                            
                            else if(*estadoconfiguracion==CCLARO){*estadoconfiguracion=CPERSONAL; break;}
                            
                            else if(*estadoconfiguracion==CNEXTEL){*estadoconfiguracion=CCLARO; break;}
                            
                            else if(*estadoconfiguracion==CMOVISTAR){*estadoconfiguracion=CNEXTEL; break;}
                            
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
                            
                            else if(*estadoconfiguracion==MPBLANCO){*estadoconfiguracion=MPROSA; break;}
                            else if(*estadoconfiguracion==MPROJO){*estadoconfiguracion=MPBLANCO; break;}
                            else if(*estadoconfiguracion==MPAMARILLO){*estadoconfiguracion=MPROJO; break;}
                            else if(*estadoconfiguracion==MPVERDE){*estadoconfiguracion=MPAMARILLO; break;}
                            else if(*estadoconfiguracion==MPMORADO){*estadoconfiguracion=MPVERDE; break;}
                            else if(*estadoconfiguracion==MPCELESTE){*estadoconfiguracion=MPMORADO; break;}
                            else if(*estadoconfiguracion==MPNARANJA){*estadoconfiguracion=MPCELESTE; break;}
                            else if(*estadoconfiguracion==MPROSA){*estadoconfiguracion=MPNARANJA; break;}
                            else if(*estadoconfiguracion==FBLANCO){*estadoconfiguracion=FROSA; break;}
                            
                            
                            else if(*estadoconfiguracion==MGRANDE){*estadoconfiguracion=MMEDIA; break;}
                            else if(*estadoconfiguracion==MGIGANTE){*estadoconfiguracion=MGRANDE; break;}
                            else if(*estadoconfiguracion==MPPEQUENA){*estadoconfiguracion=MGIGANTE; break;}
                           else if(*estadoconfiguracion==MMEDIA){*estadoconfiguracion=MPPEQUENA; break;}
                            
                            
                            
                        
                        
                    } else if (ev.mouse.y>525&&ev.mouse.y<540){
                           if(*estadoconfiguracion==USUARIO){*estadoconfiguracion=COMPANIA; break;} //teclaparaabajo
                           else if(*estadoconfiguracion==TT9){*estadoconfiguracion=CLASICO; break;}
                           else if(*estadoconfiguracion==CLASICO){*estadoconfiguracion=TECLADONORMAL; break;}
                           else if(*estadoconfiguracion==TECLADONORMAL){*estadoconfiguracion=TT9; break;}
                           
                           
                           else if(*estadoconfiguracion==MPCOLOR){*estadoconfiguracion=MPTEXTO; break;}
                            else if(*estadoconfiguracion==MPTAMANO){*estadoconfiguracion=MPCOLOR; break;}
                            else if(*estadoconfiguracion==MPTEXTO){*estadoconfiguracion=MPTAMANO; break;}
                           
                           else if(*estadoconfiguracion==MPPEQUENA){*estadoconfiguracion=MMEDIA; break;}
                            else if(*estadoconfiguracion==MMEDIA){*estadoconfiguracion=MGRANDE; break;}
                            else if(*estadoconfiguracion==MGRANDE){*estadoconfiguracion=MGIGANTE; break;}
                           else if(*estadoconfiguracion==MGIGANTE){*estadoconfiguracion=MPPEQUENA; break;}
                            
                           
                           
                           else if(*estadoconfiguracion==COMPANIA){*estadoconfiguracion=MENSAJEPERSONAL; break;}
                           else if(*estadoconfiguracion==FONDO){*estadoconfiguracion=USUARIO; break;}
                           else if(*estadoconfiguracion==MENSAJEPERSONAL){*estadoconfiguracion=TIPOESCRITURA; break;}
                           else if(*estadoconfiguracion==TIPOESCRITURA){*estadoconfiguracion=FONDO; break;}
                           else if(*estadoconfiguracion==CMOVISTAR){*estadoconfiguracion=CPERSONAL; break;}
                           else if(*estadoconfiguracion==CPERSONAL){*estadoconfiguracion=CCLARO; break;}
                           else if(*estadoconfiguracion==CCLARO){*estadoconfiguracion=CNEXTEL; break;}
                           else if(*estadoconfiguracion==CNEXTEL){*estadoconfiguracion=CMOVISTAR; break;}
                           
                           else if(*estadoconfiguracion==FBLANCO){*estadoconfiguracion=FROJO; break;}
                           else if(*estadoconfiguracion==FROJO){*estadoconfiguracion=FAMARILLO; break;}
                            else if(*estadoconfiguracion==FAMARILLO){*estadoconfiguracion=FVERDE; break;}
                            else if(*estadoconfiguracion==FVERDE){*estadoconfiguracion=FMORADO; break;}
                            else if(*estadoconfiguracion==FMORADO){*estadoconfiguracion=FCELESTE; break;}
                            else if(*estadoconfiguracion==FCELESTE){*estadoconfiguracion=FNARANJA; break;}
                            else if(*estadoconfiguracion==FNARANJA){*estadoconfiguracion=FROSA; break;}
                           else if(*estadoconfiguracion==FROSA){*estadoconfiguracion=FBLANCO; break;}
                           
                           else if(*estadoconfiguracion==MPBLANCO){*estadoconfiguracion=MPROJO; break;}
                           else if(*estadoconfiguracion==MPROJO){*estadoconfiguracion=MPAMARILLO; break;}
                            else if(*estadoconfiguracion==MPAMARILLO){*estadoconfiguracion=MPVERDE; break;}
                            else if(*estadoconfiguracion==MPVERDE){*estadoconfiguracion=MPMORADO; break;}
                            else if(*estadoconfiguracion==MPMORADO){*estadoconfiguracion=MPCELESTE; break;}
                            else if(*estadoconfiguracion==MPCELESTE){*estadoconfiguracion=MPNARANJA; break;}
                            else if(*estadoconfiguracion==MPNARANJA){*estadoconfiguracion=MPROSA; break;}
                           else if(*estadoconfiguracion==MPROSA){*estadoconfiguracion=MPBLANCO; break;}
                           
                           
                            
                        
                        
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
                            }  if(*estadoconfiguracion==CPERSONAL||*estadoconfiguracion==CMOVISTAR||*estadoconfiguracion==CCLARO||*estadoconfiguracion==CNEXTEL){
                               *estadoconfiguracion=COMPANIA;
                               break;
                            } 
                            if(*estadoconfiguracion==MPBLANCO||*estadoconfiguracion==MPROJO||*estadoconfiguracion==MPAMARILLO||*estadoconfiguracion==MPVERDE||*estadoconfiguracion==MPMORADO||*estadoconfiguracion==MPCELESTE||*estadoconfiguracion==MPNARANJA||*estadoconfiguracion==MPROSA||*estadoconfiguracion==MPPEQUENA||*estadoconfiguracion==MMEDIA||*estadoconfiguracion==MGRANDE||*estadoconfiguracion==MGIGANTE){
                                *estadoconfiguracion=MPCOLOR;
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
    ALLEGRO_BITMAP* foto=NULL;
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
    foto=NULL;
    foto=al_load_bitmap("usuario.png");    if(foto==NULL){fprintf(stderr,"No se abrio la foto\n"); exit -1;}
    al_draw_bitmap(foto,0,CONF1-1,0);
    al_destroy_bitmap(foto);
    cambiopantalla(display,pantalla);
    cambiopantalla(display,pantalla);
    foto=NULL;
    
    foto=al_load_bitmap("compania.png");    if(foto==NULL){fprintf(stderr,"No se abrio la foto\n"); exit -1;}
    al_draw_bitmap(foto,0,CONF2,0);
    al_destroy_bitmap(foto);
    cambiopantalla(display,pantalla);
    cambiopantalla(display,pantalla);
    foto=NULL;
    
    foto=al_load_bitmap("mensaje_personal.png");    if(foto==NULL){fprintf(stderr,"No se abrio la foto\n"); exit -1;}
    al_draw_bitmap(foto,0,CONF3,0);
    al_destroy_bitmap(foto);
    cambiopantalla(display,pantalla);
    cambiopantalla(display,pantalla);
    foto=NULL;
    
    foto=al_load_bitmap("tipo_escritura.png");   if(foto==NULL) {fprintf(stderr,"No se abrio la foto\n"); exit -1;}
    al_draw_bitmap(foto,0,CONF4-3,0);
    al_destroy_bitmap(foto);
    cambiopantalla(display,pantalla);
    cambiopantalla(display,pantalla);
    foto=NULL;
    
    foto=al_load_bitmap("fondo.png");    if(foto==NULL){fprintf(stderr,"No se abrio la foto\n"); exit -1;}
    al_draw_bitmap(foto,0,CONF5-2,0);
    al_destroy_bitmap(foto);
    cambiopantalla(display,pantalla);
    
    
    
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
        foto=NULL;
        cambiopantalla(display,pantalla);
        foto=al_load_bitmap("t9.png");    if(foto==NULL){fprintf(stderr,"No se abrio la foto\n"); exit -1;}
        al_draw_bitmap(foto,0,CONF1-1,0);
        al_destroy_bitmap(foto);
        cambiopantalla(display,pantalla);
        cambiopantalla(display,pantalla);
        foto=NULL;
        foto=al_load_bitmap("clasico.png");    if(foto==NULL){fprintf(stderr,"No se abrio la foto\n"); exit -1;}
        al_draw_bitmap(foto,0,CONF2-1,0);
        al_destroy_bitmap(foto);
        cambiopantalla(display,pantalla);
        cambiopantalla(display,pantalla);
        foto=NULL;
        foto=al_load_bitmap("teclado.png");    if(foto==NULL){fprintf(stderr,"No se abrio la foto\n"); exit -1;}
        al_draw_bitmap(foto,0,CONF3-1,0);
        al_destroy_bitmap(foto);
        cambiopantalla(display,pantalla);
        
        
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
        
        
    } else if(*estadoconfiguracion==MPCOLOR||*estadoconfiguracion==MPTEXTO||*estadoconfiguracion==MPTAMANO){
        if(*estadoconfiguracion==MPCOLOR){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,CONF1,0);
            cambiopantalla(display,pantalla);
        } else if(*estadoconfiguracion==MPTEXTO){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,CONF2,0);
            cambiopantalla(display,pantalla);
        }else if(*estadoconfiguracion==MPTAMANO){
            cambiopantalla(display,pantalla);               //pongo la "seleccion" en el lugar donde se eligio
            al_draw_bitmap(seleccionar,0,CONF3,0);
            cambiopantalla(display,pantalla);
        }
        
        cambiopantalla(display,pantalla);
        al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF1,ALLEGRO_ALIGN_LEFT,"Color Mensaje");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF2,ALLEGRO_ALIGN_LEFT,"Contenido");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF3,ALLEGRO_ALIGN_LEFT,"Tamano");
        fuente=crearfuente(PEQUENA);
        al_draw_text(fuente,al_map_rgb(255,0,0),0,150,ALLEGRO_ALIGN_LEFT,"Sea cauteloso ya que la longitud y ta-");
        al_draw_text(fuente,al_map_rgb(255,0,0),0,175,ALLEGRO_ALIGN_LEFT,"maño de su mensaje pueden llegar a ser ");
        al_draw_text(fuente,al_map_rgb(255,0,0),0,200,ALLEGRO_ALIGN_LEFT,"demasiado grandes para caber en pantalla.");

        cambiopantalla(display,pantalla);
        
    } else if(*estadoconfiguracion==MPBLANCO||*estadoconfiguracion==MPROJO||*estadoconfiguracion==MPAMARILLO||*estadoconfiguracion==MPVERDE||*estadoconfiguracion==MPMORADO||*estadoconfiguracion==MPCELESTE||*estadoconfiguracion==MPNARANJA||*estadoconfiguracion==MPROSA){
        if(*estadoconfiguracion==MPBLANCO){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,20,0);
            cambiopantalla(display,pantalla);
        } else if(*estadoconfiguracion==MPROJO){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,45,0);
            cambiopantalla(display,pantalla);
        }else if(*estadoconfiguracion==MPAMARILLO){
            cambiopantalla(display,pantalla);               //pongo la "seleccion" en el lugar donde se eligio
            al_draw_bitmap(seleccionar,0,70,0);
            cambiopantalla(display,pantalla);
        }else if(*estadoconfiguracion==MPVERDE){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,95,0);
            cambiopantalla(display,pantalla);
        }else if(*estadoconfiguracion==MPMORADO){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,120,0);
            cambiopantalla(display,pantalla);
        }else if(*estadoconfiguracion==MPCELESTE){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,145,0);
            cambiopantalla(display,pantalla);
        }else if(*estadoconfiguracion==MPNARANJA){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,170,0);
            cambiopantalla(display,pantalla);
        }else if(*estadoconfiguracion==MPROSA){
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
        
        
    }else if(*estadoconfiguracion==MPPEQUENA||*estadoconfiguracion==MMEDIA||*estadoconfiguracion==MGRANDE||*estadoconfiguracion==MGIGANTE){
            if(*estadoconfiguracion==MPPEQUENA){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,CONF1,0);
            cambiopantalla(display,pantalla);
        } else if(*estadoconfiguracion==MMEDIA){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,CONF2,0);
            cambiopantalla(display,pantalla);
        }else if(*estadoconfiguracion==MGRANDE){
            cambiopantalla(display,pantalla);               //pongo la "seleccion" en el lugar donde se eligio
            al_draw_bitmap(seleccionar,0,CONF3,0);
            cambiopantalla(display,pantalla);
        }else if(*estadoconfiguracion==MGIGANTE){
            cambiopantalla(display,pantalla);
            al_draw_bitmap(seleccionar,0,CONF4,0);
            cambiopantalla(display,pantalla);
        }
        
        cambiopantalla(display,pantalla);
        al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF1,ALLEGRO_ALIGN_LEFT,"Pequena");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF2,ALLEGRO_ALIGN_LEFT,"Media");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF3,ALLEGRO_ALIGN_LEFT,"Grande");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF4,ALLEGRO_ALIGN_LEFT,"Exagerada");
        cambiopantalla(display,pantalla);
        
        
    }
    
    
    fuente=crearfuente(MEDIA);
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),0,270,ALLEGRO_ALIGN_LEFT,"Seleccionar");         //creo boton menu o cualquier otro boton que quiera poner
    al_draw_text(fuente,al_map_rgb(0,0,0),210,270,ALLEGRO_ALIGN_RIGHT,"Volver");
    cambiopantalla(display,pantalla);
    
    
    al_destroy_font(fuente);
    al_destroy_bitmap(seleccionar);
    al_destroy_bitmap(resetpantalla);
}