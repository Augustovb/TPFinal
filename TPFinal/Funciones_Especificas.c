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


int analizartecladoconfiguracion (ALLEGRO_EVENT_QUEUE* eventos,int * estadoconfiguracion, int* pestado, INFOPANTALLA* pantalla){
        //de aca en adelante es simplemente la funcionde leerteclado que por comodidad no la pongo afuera
    int infoFtdi=0;
    unsigned char info;
    
    while(1){                   // esto es la funcion que lee de donde se clickeo
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventos,&ev);
        infoFtdi=readBUTTONS();
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        } else if((ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)||(infoFtdi!=0)){
            if((ev.mouse.button & 1)||(infoFtdi!=0)){
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
                            
                            else if(*estadoconfiguracion==MODOLIBRE){*estadoconfiguracion=TIPOESCRITURA; pantalla->tipoescritura=CLASICO; break;}
                            
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
                            else if(*estadoconfiguracion==MPTEXTO){*estadoconfiguracion=INGRESARTEXTO; break;}
                            
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
                       
                } else if((ev.mouse.x>110&&ev.mouse.x<208)||(infoFtdi!=0)){  //son las teclas de la linea media que incluyen los centrales
                    //analizo primero lo de las "flechitas"y el boton del medio
                    if((ev.mouse.y>450&&ev.mouse.y<460)||infoFtdi==ARRIBA){
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
                            
                            
                            
                        
                        
                    } else if ((ev.mouse.y>525&&ev.mouse.y<540)||(infoFtdi==ABAJO)){
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
                           
                           
                            
                        
                        
                    } else if((ev.mouse.y>460&&ev.mouse.y<540)||(infoFtdi!=0)){  //der, izq o medio
                                if((ev.mouse.x<130&&ev.mouse.x>0)||(infoFtdi==IZQUIERDA)){
                                     *pestado=MENU;    //hacia la izquierda
                                     break;
                                } else if(ev.mouse.x>188||infoFtdi==DERECHA){
                                    break;         //la de la derecha
                                } else if ((infoFtdi==MEDIO)) {    //la del medio
                            if(*estadoconfiguracion==USUARIO){*estadoconfiguracion=INUSUARIO;break;} 
                            if(*estadoconfiguracion==MENSAJEPERSONAL){*estadoconfiguracion=MPCOLOR; break;}
                            
                            else if(*estadoconfiguracion==COMPANIA){*estadoconfiguracion=CMOVISTAR; break;}
                            
                            else if(*estadoconfiguracion==CMOVISTAR){*estadoconfiguracion=COMPANIA; pantalla->compania=MOVISTAR; break; }
                            
                            else if(*estadoconfiguracion==CPERSONAL){*estadoconfiguracion=COMPANIA; pantalla->compania=PERSONAL; break;}
                            
                            else if(*estadoconfiguracion==CCLARO){*estadoconfiguracion=COMPANIA; pantalla->compania=CLARO; break;}
                            
                            else if(*estadoconfiguracion==CNEXTEL){*estadoconfiguracion=COMPANIA; pantalla->compania=NEXTEL; break;}
                            
                            else if(*estadoconfiguracion==TIPOESCRITURA){*estadoconfiguracion=TT9; break;}
                            
                            else if(*estadoconfiguracion==TT9){*estadoconfiguracion=TIPOESCRITURA; pantalla->tipoescritura=T9; break;}
                            
                            else if(*estadoconfiguracion==MODOLIBRE){*estadoconfiguracion=TIPOESCRITURA; pantalla->tipoescritura=CLASICO; break;}
                            
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
                            else if(*estadoconfiguracion==MPTEXTO){*estadoconfiguracion=INGRESARTEXTO; break;}
                            
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
                                    break;
                                }    //la del medio
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
void mantenerconfiguracion(int * estadoconfiguracion,ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla,ALLEGRO_EVENT_QUEUE* eventos, int* pestado,INFOPANTALLA* mipantalla){
    ALLEGRO_BITMAP* resetpantalla=NULL;
    ALLEGRO_BITMAP* foto=NULL;
    unsigned int j=0;
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
    al_draw_bitmap(foto,-18,CONF5-3,0);
    al_destroy_bitmap(foto);
    cambiopantalla(display,pantalla);
    
    
    
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF1,ALLEGRO_ALIGN_LEFT,"Usuario");
    al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF2,ALLEGRO_ALIGN_LEFT,"Cambiar compania");
    al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF3,ALLEGRO_ALIGN_LEFT,"Mensaje Personal");
    al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF4,ALLEGRO_ALIGN_LEFT,"Tipo Escritura");
    al_draw_text(fuente,al_map_rgb(0,0,0),25,CONF5,ALLEGRO_ALIGN_LEFT,"Fondo");
    cambiopantalla(display,pantalla);
    
    
    
    } else if(*estadoconfiguracion==INGRESARTEXTO){     //aca entro cuando debo escribir el mensaje personal
        cambiopantalla(display,pantalla);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,15,ALLEGRO_ALIGN_LEFT,"Su nuevo mensaje:");
        
        al_draw_text(fuente,al_map_rgb(0,0,0),0,270,ALLEGRO_ALIGN_LEFT,"Set");
        cambiopantalla(display,pantalla);
        
        
        if(mipantalla->tipoescritura==MODOLIBRE){
            tecladoCLASSIC2(eventos,pantalla,display,mipantalla,pestado,estadoconfiguracion);
            ++j;
        } else if(mipantalla->tipoescritura==TECLADOANALOGO){
          
            cambiopantalla(display,pantalla);
            al_draw_text(fuente,al_map_rgb(255,0,10),0,100,ALLEGRO_ALIGN_LEFT,"SU MENSAJE ESTA");
            al_draw_text(fuente,al_map_rgb(255,0,10),0,125,ALLEGRO_ALIGN_LEFT,"SIENDO INTRODUCI-");
            al_draw_text(fuente,al_map_rgb(255,0,10),0,150,ALLEGRO_ALIGN_LEFT,"DO MEDIANTE EL TE-");
            al_draw_text(fuente,al_map_rgb(255,0,10),0,175,ALLEGRO_ALIGN_LEFT,"CLADO ANALOGO. (se");
            al_draw_text(fuente,al_map_rgb(255,0,10),0,200,ALLEGRO_ALIGN_LEFT,"actualizara solo)");
            cambiopantalla(display,pantalla);
            
            printf("\nINGRESE SU MENSAJE AQUI Y SERA CARGADO EN EL CELULAR\n");
            printf("\nRECUERDE QUE ESTA INGRESANDO EL MENSAJE PERSONAL\n");
            char personalmessage[140];
            unsigned int i=0;
            while(i<140){
                personalmessage[i]=getchar();
                
                if(personalmessage[i]=='\n'){
                    personalmessage[i]=0;
                    break;
                }
                ++i;
                
            }
            strcpy(mipantalla->mensajepersonal,personalmessage);
            cambiopantalla(display,pantalla);
            al_draw_bitmap(resetpantalla,0,15,0);
            al_draw_text(fuente,al_map_rgb(255,103,0),0,150,ALLEGRO_ALIGN_LEFT,"Se seteo el mensaje");
            cambiopantalla(display,pantalla);
            sleep(1);
            *estadoconfiguracion=MENSAJEPERSONAL;
            
        } else if(mipantalla->tipoescritura==T9){
            cambiopantalla(display,pantalla);
            al_draw_text(fuente,al_map_rgb(0,0,0),100,270,ALLEGRO_ALIGN_CENTRE,"<Elegir>");
            cambiopantalla(display,pantalla);
            tecladoT92(eventos,pantalla,display,mipantalla,estadoconfiguracion);
        }
        
        
        
    }
    
    
    
    else if(*estadoconfiguracion==INUSUARIO){
        cambiopantalla(display,pantalla);
        al_draw_text(fuente,al_map_rgb(0,0,0),0,15,ALLEGRO_ALIGN_LEFT,"Introduzca su nombre:");
        al_draw_text(fuente,al_map_rgb(0,0,0),0,40,ALLEGRO_ALIGN_LEFT,"(Máx 15 caracteres)");
        al_draw_text(fuente,al_map_rgb(0,0,0),0,270,ALLEGRO_ALIGN_LEFT,"Setear nombre");
        cambiopantalla(display,pantalla);
        
        //si o si en clasico se escribira el nombre
        if(mipantalla->tipoescritura==MODOLIBRE||mipantalla->tipoescritura==T9||mipantalla->tipoescritura==TECLADOANALOGO){
            
            tecladoCLASSIC1(eventos,pantalla,display,mipantalla,pestado,estadoconfiguracion);
            
            
        }   //EL ELSE ES AL IMPLEMENTAR EL MODO CON EL TECLADO
        ++j;
        //aca la fucion para leer teclado ira que analice cual es el nombre del usuario
    }
    
    
    
    
    
    else if(*estadoconfiguracion==INCOMPANIA||*estadoconfiguracion==CMOVISTAR||*estadoconfiguracion==CPERSONAL||*estadoconfiguracion==CCLARO||*estadoconfiguracion==CNEXTEL){
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
        
        
    }
    
    
    
    
    
    else if(*estadoconfiguracion==TT9||*estadoconfiguracion==CLASICO||*estadoconfiguracion==TECLADONORMAL){
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
    }  
    
    
    
    
    else if(*estadoconfiguracion==FBLANCO||*estadoconfiguracion==FROJO||*estadoconfiguracion==FAMARILLO||*estadoconfiguracion==FVERDE||*estadoconfiguracion==FMORADO||*estadoconfiguracion==FCELESTE||*estadoconfiguracion==FNARANJA||*estadoconfiguracion==FROSA){
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
    
    
    
    
    else if(*estadoconfiguracion==MPCOLOR||*estadoconfiguracion==MPTEXTO||*estadoconfiguracion==MPTAMANO){
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
        
    }
    
    
    
    
    else if(*estadoconfiguracion==MPBLANCO||*estadoconfiguracion==MPROJO||*estadoconfiguracion==MPAMARILLO||*estadoconfiguracion==MPVERDE||*estadoconfiguracion==MPMORADO||*estadoconfiguracion==MPCELESTE||*estadoconfiguracion==MPNARANJA||*estadoconfiguracion==MPROSA){
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
        al_draw_text(fuente,al_map_rgb(0,0,0),25,20,ALLEGRO_ALIGN_LEFT,"Negro");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,45,ALLEGRO_ALIGN_LEFT,"Rojo");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,70,ALLEGRO_ALIGN_LEFT,"Amarillo");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,95,ALLEGRO_ALIGN_LEFT,"Verde");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,120,ALLEGRO_ALIGN_LEFT,"Morado");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,145,ALLEGRO_ALIGN_LEFT,"Celeste");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,170,ALLEGRO_ALIGN_LEFT,"Naranja");
        al_draw_text(fuente,al_map_rgb(0,0,0),25,195,ALLEGRO_ALIGN_LEFT,"Rosa");
    
        cambiopantalla(display,pantalla);
        
        
    }
    
    
    
    
    else if(*estadoconfiguracion==MPPEQUENA||*estadoconfiguracion==MMEDIA||*estadoconfiguracion==MGRANDE||*estadoconfiguracion==MGIGANTE){
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
    if(j==0){
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),0,270,ALLEGRO_ALIGN_LEFT,"Seleccionar");         //creo boton menu o cualquier otro boton que quiera poner
    al_draw_text(fuente,al_map_rgb(0,0,0),210,270,ALLEGRO_ALIGN_RIGHT,"Volver");
    cambiopantalla(display,pantalla);
    } else{j=0;}
    
    al_destroy_font(fuente);
    al_destroy_bitmap(seleccionar);
    al_destroy_bitmap(resetpantalla);
}
void escribirmensaje(ALLEGRO_EVENT_QUEUE* eventos,ALLEGRO_DISPLAY* display,ALLEGRO_BITMAP* pantalla,int*pestado,INFOPANTALLA* mipantalla){
    ALLEGRO_FONT* fuente=NULL;
    ALLEGRO_BITMAP* fondo=NULL;
    fondo=al_create_bitmap(250,300); al_set_target_bitmap(fondo); al_clear_to_color(al_map_rgb(255,255,255));
    
    fuente=crearfuente(PEQUENA); if(fuente==NULL){fprintf(stderr,"Fallo al cargar la fuente en escribirmensaje()\n"); exit -1;}
    cambiopantalla(display,pantalla);
    al_draw_bitmap(fondo,0,15,0);
    
    al_draw_text(fuente,al_map_rgb(0,0,0),0,15,ALLEGRO_ALIGN_LEFT,"Escriba su SMS:");
    fuente=crearfuente(MEDIA);
    al_draw_text(fuente,al_map_rgb(0,0,0),0,270,ALLEGRO_ALIGN_LEFT,"Enviar");
    cambiopantalla(display,pantalla);
    
    if(mipantalla->tipoescritura==MODOLIBRE){
            tecladoCLASSIC3(eventos,pantalla,display,mipantalla,pestado);
    
    } else if(mipantalla->tipoescritura==TECLADOANALOGO){
          
        cambiopantalla(display,pantalla);
        al_draw_text(fuente,al_map_rgb(255,0,10),0,100,ALLEGRO_ALIGN_LEFT,"SU MENSAJE ESTA");
        al_draw_text(fuente,al_map_rgb(255,0,10),0,125,ALLEGRO_ALIGN_LEFT,"SIENDO INTRODUCI-");
        al_draw_text(fuente,al_map_rgb(255,0,10),0,150,ALLEGRO_ALIGN_LEFT,"DO MEDIANTE EL TE-");
        al_draw_text(fuente,al_map_rgb(255,0,10),0,175,ALLEGRO_ALIGN_LEFT,"CLADO ANALOGO. (se");
        al_draw_text(fuente,al_map_rgb(255,0,10),0,200,ALLEGRO_ALIGN_LEFT,"actualizara solo)");
        cambiopantalla(display,pantalla);
            
        printf("\nINGRESE SU MENSAJE AQUI Y SERA CARGADO EN EL CELULAR\n");
        printf("\nRECUERDE QUE ESTA INGRESANDO EL MENSAJE PERSONAL\n");

            
        } else if(mipantalla->tipoescritura==T9){
            tecladoT9(eventos,pantalla,display);
        }
    *pestado=PANTALLAPRINCIPAL;
    
    ALLEGRO_BITMAP* enviandosms=NULL;
    ALLEGRO_BITMAP* enviado=NULL;
    
    enviandosms=al_load_bitmap("enviando.png");
    enviado=al_load_bitmap("enviado.png");
    if(enviandosms==NULL||enviado==NULL){fprintf(stderr,"No se cargaron las imagenees de enviar sms"); exit;}
    
    cambiopantalla(display,pantalla);
    al_draw_bitmap(fondo,0,15,0);
    al_draw_bitmap(enviandosms,-50,-20,0);
    cambiopantalla(display,pantalla);
    sleep(2);
    
    fuente=crearfuente(GRANDE);
    
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),50,200,ALLEGRO_ALIGN_CENTRE,".");
    cambiopantalla(display,pantalla);
    sleep(1);
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),70,200,ALLEGRO_ALIGN_CENTRE,".");
    cambiopantalla(display,pantalla);
    sleep(1);
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),90,200,ALLEGRO_ALIGN_CENTRE,".");
    cambiopantalla(display,pantalla);
    sleep(1);
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),110,200,ALLEGRO_ALIGN_CENTRE,".");
    cambiopantalla(display,pantalla);
    sleep(1);
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),130,200,ALLEGRO_ALIGN_CENTRE,".");
    cambiopantalla(display,pantalla);
    sleep(1);
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),150,200,ALLEGRO_ALIGN_CENTRE,".");
    cambiopantalla(display,pantalla);
    sleep(1);
    
    cambiopantalla(display,pantalla);
    al_draw_bitmap(fondo,0,15,0);
    al_draw_bitmap(enviado,-5,15,0);
    cambiopantalla(display,pantalla);
    
    sleep(2);
   
    
    al_destroy_bitmap(enviandosms);
    al_destroy_bitmap(enviado);
    al_destroy_bitmap(fondo);
    al_destroy_font(fuente);
    
}
void mantenerpantalla(INFOPANTALLA datos,ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla){
    
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
    
    al_destroy_bitmap(partearriba);
   
}
int analizartecladopantalla (ALLEGRO_EVENT_QUEUE* eventos,int* pestado,ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla ){            //lo unico para clickear es el menu
        //de aca en adelante es simplemente la funcionde leerteclado que por comodidad no la pongo afuera
    int infoFtdi=0;
    unsigned char info;
    
    while(1){                   // esto es la funcion que lee de donde se clickeo
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventos,&ev);
        infoFtdi=readBUTTONS();
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            *pestado=FINALIZAR;
            break;
        } else if((ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)||(infoFtdi!=0)){
            if((ev.mouse.button & 1)||(infoFtdi!=0)){
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
                } else if((ev.mouse.x>110&&ev.mouse.x<208)||(infoFtdi!=0)){  //son las teclas de la linea media que incluyen los centrales
                    //analizo primero lo de las "flechitas"y el boton del medio
                    if((ev.mouse.y>450&&ev.mouse.y<460)||infoFtdi==ARRIBA){
                              //tecla para arrriba
                    } else if ((ev.mouse.y>525&&ev.mouse.y<540)||(infoFtdi==ABAJO)){
                            //teclaparaabajo
                    } else if((ev.mouse.y>460&&ev.mouse.y<540)||(infoFtdi!=0)){  //der, izq o medio
                        
                                if((ev.mouse.x<130&&ev.mouse.x>0)||(infoFtdi==IZQUIERDA)){
                                         //hacia la izquierda
                                } else if((ev.mouse.x>188)||(infoFtdi==DERECHA)){
                                             //la de la derecha
                                } else {
                                    
                                    *pestado=MENU;
                                    break;
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
    ALLEGRO_BITMAP* linterna=NULL;
    ALLEGRO_BITMAP* fiesta=NULL;
    ALLEGRO_BITMAP* personalizar=NULL;       //seran las fotos que usaran como "iconos"
    mensaje=al_load_bitmap("mensaje.png");
    personalizar=al_load_bitmap("personalizar.png");
    linterna=al_load_bitmap("linterna.png");
    fiesta=al_load_bitmap("fiesta.png");
    if(mensaje==NULL||personalizar==NULL||linterna==NULL||fiesta==NULL){
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
    al_draw_text(fuente,al_map_rgb(0,0,0),25,POS3,ALLEGRO_ALIGN_LEFT,"Linterna");
    al_draw_bitmap(linterna,-4,POS3-3,0);
    al_draw_text(fuente,al_map_rgb(0,0,0),25,POS4,ALLEGRO_ALIGN_LEFT,"Fiesta");
    al_draw_bitmap(fiesta,-5,POS4-5,0);
    cambiopantalla(display,pantalla);
    
    
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),0,270,ALLEGRO_ALIGN_LEFT,"Seleccionar");         //creo boton menu o cualquier otro boton que quiera poner
    al_draw_text(fuente,al_map_rgb(0,0,0),210,270,ALLEGRO_ALIGN_RIGHT,"Volver");
    cambiopantalla(display,pantalla);
    
    al_destroy_bitmap(fiesta);
    al_destroy_bitmap(linterna);
    al_destroy_bitmap(seleccion);
    al_destroy_bitmap(fondo);
    al_destroy_font(fuente);
    al_destroy_bitmap(mensaje);
    al_destroy_bitmap(personalizar);
}   //debo setear cuando vuelva en estadomenu a pos1

int analizartecladomenu (ALLEGRO_EVENT_QUEUE* eventos,int* pestado,int* estadomenu){
        //de aca en adelante es simplemente la funcionde leerteclado que por comodidad no la pongo afuera
    int infoFtdi=0;
    unsigned char info;
    
    while(1){                   // esto es la funcion que lee de donde se clickeo
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventos,&ev);
        infoFtdi=readBUTTONS();
        
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            *pestado=FINALIZAR;
            break;
        } else if((ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)||(infoFtdi!=0)){
            if((ev.mouse.button & 1)||(infoFtdi!=0)){
                //aca iran los ifs que veran el ev.mouse.x y el ev.mouse.y
                if(ev.mouse.x>30&&ev.mouse.x<110){      //pueden ser el select, llamar,1,4,7,*
                    if(ev.mouse.y>450&&ev.mouse.y<490){
                            if(*estadomenu==POS1){*pestado=MENSAJE;break;}
                            else if(*estadomenu==POS2){*pestado=PERSONALIZAR;break;}  //se presiono la teclaselect
                            else if(*estadomenu==POS3){*pestado=LINTERNA;break;}
                            else if(*estadomenu==POS4){*pestado=FIESTA;break;}

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
                } else if((ev.mouse.x>110&&ev.mouse.x<208)||(infoFtdi!=0)){  //son las teclas de la linea media que incluyen los centrales
                    //analizo primero lo de las "flechitas"y el boton del medio
                    if((ev.mouse.y>450&&ev.mouse.y<460)||infoFtdi==ARRIBA){
                            if(*estadomenu==POS1){continue;}  //tecla para arrriba
                            if(*estadomenu==POS2){*estadomenu=POS1; break;}     //(subo)
                            if(*estadomenu==POS3){*estadomenu=POS2; break;}
                            if(*estadomenu==POS4){*estadomenu=POS3; break;}
                            
                            
                    } else if ((ev.mouse.y>525&&ev.mouse.y<540)||(infoFtdi==ABAJO)){
                            if(*estadomenu==POS1){*estadomenu=POS2; break;}//teclaparaabajo
                            if(*estadomenu==POS2){*estadomenu=POS3; break;}
                            if(*estadomenu==POS3){*estadomenu=POS4; break;}
                            if(*estadomenu==POS4){continue;}
                    } else if((ev.mouse.y>460&&ev.mouse.y<540)||(infoFtdi!=0)){  //der, izq o medio
                                if((ev.mouse.x<130&&ev.mouse.x>0)||(infoFtdi==IZQUIERDA)){
                                     *pestado=PANTALLAPRINCIPAL;    //hacia la izquierda
                                     break;
                                } else if(ev.mouse.x>188||infoFtdi==DERECHA){
                                    break;         //la de la derecha
                                } else if ((infoFtdi==MEDIO)) {    //la del medio
                                    if(*estadomenu==POS1){*pestado=MENSAJE;break;}
                                else if(*estadomenu==POS2){*pestado=PERSONALIZAR;break;}  //se presiono la teclaselect
                                else if(*estadomenu==POS3){*pestado=LINTERNA;break;}
                                else if(*estadomenu==POS4){*pestado=FIESTA;break;}

                                    
                                }
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

void mantenerlinterna(int* pestado,ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla, INFOPANTALLA mipantalla){
    
    ALLEGRO_FONT* fuente;
    fuente=crearfuente(MEDIA);
    ALLEGRO_BITMAP* prendido=NULL;
    ALLEGRO_BITMAP* apagado=NULL;
    ALLEGRO_BITMAP* fondo;
    fondo=al_create_bitmap(285,300);
    al_set_target_bitmap(fondo);
    al_clear_to_color(al_map_rgb(255,255,255));
    cambiopantalla(display,pantalla);
    al_draw_bitmap(fondo,0,15,0);
    cambiopantalla(display,pantalla);
    
    
    prendido=al_load_bitmap("prendido.png");
    apagado=al_load_bitmap("apagado.png");
    if(prendido==NULL||apagado==NULL){
        fprintf(stderr,"Error al cargar imagen");
        exit -1;
    }
    
    unsigned char data;
                                    //yo pondre como linterna el bit 0
    
    
    data=readFTDI();
    
    data&=0x20;
    if (data==0x20){
        
        cambiopantalla(display,pantalla);
        al_draw_bitmap(prendido,3,15,0);
        cambiopantalla(display,pantalla);
    } else {
        cambiopantalla(display,pantalla);
        al_draw_bitmap(apagado,3,15,0);
        cambiopantalla(display,pantalla);
    }
    
    cambiopantalla(display,pantalla);
    al_draw_text(fuente,al_map_rgb(0,0,0),0,270,ALLEGRO_ALIGN_LEFT,"Flechitas!");         //creo boton menu o cualquier otro boton que quiera poner
    al_draw_text(fuente,al_map_rgb(0,0,0),210,270,ALLEGRO_ALIGN_RIGHT,"Volver");
    cambiopantalla(display,pantalla);
    
    al_destroy_bitmap(prendido);
    al_destroy_bitmap(apagado);
    al_destroy_bitmap(fondo);
    al_destroy_font(fuente);
}

int analizartecladolinterna(ALLEGRO_EVENT_QUEUE* eventos, int* pestado){
    
            //de aca en adelante es simplemente la funcionde leerteclado que por comodidad no la pongo afuera
    int infoFtdi=0;
    unsigned char info;
    while(1){                   // esto es la funcion que lee de donde se clickeo
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventos,&ev);
        infoFtdi=readBUTTONS();
        
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        } else if((ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)||(infoFtdi!=0)){
            if((ev.mouse.button & 1)||(infoFtdi!=0)){
                
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
                } else if((ev.mouse.x>110&&ev.mouse.x<208)||(infoFtdi!=0)){  //son las teclas de la linea media que incluyen los centrales
                    //analizo primero lo de las "flechitas"y el boton del medio
                    if((ev.mouse.y>450&&ev.mouse.y<460)||infoFtdi==ARRIBA){
                        
                                info= readFTDI();

                                info|=0x20;

                                writeFTDI(info);//tecla para arrriba
                                
                                break;
                    } else if ((ev.mouse.y>525&&ev.mouse.y<540)||(infoFtdi==ABAJO)){
                        
                                info= readFTDI();

                                info&=0xDF;

                                writeFTDI(info);//teclaparaabajo
                                
                                break;
                    } else if((ev.mouse.y>460&&ev.mouse.y<540)||(infoFtdi!=0)){  //der, izq o medio
                        
                                if((ev.mouse.x<130)||(infoFtdi==IZQUIERDA)){
                                     *pestado=MENU;    //hacia la izquierda
                                     break;
                                } else if(ev.mouse.x>188||infoFtdi==DERECHA){
                                    break;         //la de la derecha
                                } else if ((infoFtdi==MEDIO)) {    //la del medio
                                    break;
                                }
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
                            *pestado=MENU;//se presiono la tecla back
                            break;
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                            *pestado=PANTALLAPRINCIPAL;//tecla roja,colgar
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




int analizartecladofiesta (ALLEGRO_EVENT_QUEUE* eventos, int* pestado ,ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla){
    
    int infoFtdi=0;
    unsigned char info;
    while(1){                   // esto es la funcion que lee de donde se clickeo
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventos,&ev);
        infoFtdi=readBUTTONS();
        
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        } else if((ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)||(infoFtdi!=0)){
            if((ev.mouse.button & 1)||(infoFtdi!=0)){
                
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
                } else if((ev.mouse.x>110&&ev.mouse.x<208)||(infoFtdi!=0)){  //son las teclas de la linea media que incluyen los centrales
                    //analizo primero lo de las "flechitas"y el boton del medio
                    if((ev.mouse.y>450&&ev.mouse.y<460)||infoFtdi==ARRIBA){
                                        info= readFTDI();

                                        info|=0x20;

                                        writeFTDI(info);                   
                                        
                                        sleep(1);
                                        info= readFTDI();

                                        info&=0xDF;

                                        writeFTDI(info);
                                        
                                
                                
                    } else if ((ev.mouse.y>525&&ev.mouse.y<540)||(infoFtdi==ABAJO)){
                                *pestado=MENU;

                                break;
                    } else if((ev.mouse.y>460&&ev.mouse.y<540)||(infoFtdi!=0)){  //der, izq o medio
                        
                                if((ev.mouse.x<130 && ev.mouse.x>0)||(infoFtdi==IZQUIERDA)){//hacia la izquierda
                                        info= readFTDI();

                                        info|=0x40;

                                        writeFTDI(info);                   
                                        
                                        sleep(1);
                                        info= readFTDI();

                                        info&=0xBF;

                                        writeFTDI(info);
                                
                                     
                                } else if(ev.mouse.x>188||infoFtdi==DERECHA){
                                        info= readFTDI();

                                        info|=0x80;

                                        writeFTDI(info);                   
                                        
                                        sleep(0.6);
                                        info= readFTDI();

                                        info&=0x7F;

                                        writeFTDI(info);
                                        sleep(0.6);
                                        info= readFTDI();

                                        info|=0x80;

                                        writeFTDI(info);                   
                                        
                                        sleep(1);
                                        info= readFTDI();

                                        info&=0x7F;

                                        writeFTDI(info);
                                        sleep(1);
                                        info= readFTDI();

                                        info|=0x80;

                                        writeFTDI(info);                   
                                        
                                        sleep(2);
                                        info= readFTDI();

                                        info&=0x7F;

                                        writeFTDI(info);
                                        
                                             //la de la derecha
                                } else if ((infoFtdi==MEDIO)) {    //la del medio
                                    fiesta(eventos,pestado, display, pantalla);
                                    
                                }
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
                            *pestado=MENU;//se presiono la tecla back
                            break;
                    }
                    else if(ev.mouse.y>490&&ev.mouse.y<540){
                            *pestado=PANTALLAPRINCIPAL;//tecla roja,colgar
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
     




void fiesta (ALLEGRO_EVENT_QUEUE* eventos, int* pestado ,ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla){
    ALLEGRO_BITMAP* partypeople=NULL;
    partypeople=al_load_bitmap("partypeople.png");
    if(partypeople==NULL){
        fprintf(stderr,"fallo la foto partypeolple\n");
        exit-1;
    }
    cambiopantalla (display,pantalla);
    al_draw_bitmap(partypeople,0,20,0);
    cambiopantalla (display,pantalla);
    unsigned char info;
   

    sleep(0.5);
                                        info= readFTDI();

                                        info|=0xE0;

                                        writeFTDI(info);
    sleep(0.5);
                                        info= readFTDI();

                                        info&=0x3F;

                                        writeFTDI(info);
    sleep(0.5);
                                        info= readFTDI();

                                        info|=0x80;

                                        writeFTDI(info);
                                        info&=0xDF;
                                        writeFTDI(info);
    sleep(0.5);
   info= readFTDI();

                                        info|=0xE0;

                                        writeFTDI(info);
    sleep(0.5);
    
                                        info= readFTDI();

                                        info&=0x1F;

                                        writeFTDI(info);
    
    
    al_destroy_bitmap (partypeople);
    dontstoptheparty(pestado,display,pantalla);
}

void dontstoptheparty (int* pestado, ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* pantalla){
    ALLEGRO_FONT* fuente;
    fuente=crearfuente(MEDIA);
    ALLEGRO_BITMAP* led=NULL;
    ALLEGRO_BITMAP* beeper=NULL;
    ALLEGRO_BITMAP* tiraleds=NULL;
    ALLEGRO_BITMAP* flechitas=NULL;
    ALLEGRO_BITMAP* fondo;
    fondo=al_create_bitmap(285,300);
    al_set_target_bitmap(fondo);
    al_clear_to_color(al_map_rgb(255,255,255));
    cambiopantalla(display,pantalla);
    al_draw_bitmap(fondo,0,15,0);
    cambiopantalla(display,pantalla);
    
    led=al_load_bitmap("led.png");
    beeper=al_load_bitmap("beeper.png");
    tiraleds=al_load_bitmap("tiraled.png");
    flechitas=al_load_bitmap("flechitas.png");
    if(led==NULL||beeper==NULL||tiraleds==NULL){
        fprintf(stderr,"Error al cargar imagen");
        exit -1;
    }
    
    
    cambiopantalla(display,pantalla);
    al_draw_bitmap(led,85,20,0);        //flecha para arriba
    al_draw_bitmap(beeper,5,124,0); //izquierda
    al_draw_bitmap(tiraleds,170,124,0); //derecha
    al_draw_bitmap(flechitas,60,70,0);
    al_draw_text(fuente,al_map_rgb(0,0,0),0,270,ALLEGRO_ALIGN_LEFT,"Toogle fiesta on/off");
    cambiopantalla(display,pantalla);
    
    
    
    al_destroy_bitmap(beeper);
    al_destroy_bitmap(led);
    al_destroy_bitmap(tiraleds);
    al_destroy_bitmap(fondo);
    al_destroy_font(fuente);
}

