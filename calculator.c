/*Doc:  Programa escrito en C con la api win32 para crear interfaces
        gráficas, desarrollando de una calculadora simple pero bastante
        compleja al momento de implementar interfaces gráficas.
        Compilador: GNU GCC Compiler
  Author: Fran Espino Mostacero   |  https//www.fraporitmos.com
*/
#include <windows.h>
#include <string.h>
#define BTN_LEER 100
#define BTN_SALIR 101
#define EDIT_1 102
#define LABEL 103
#define CB_UNIDADES1 104
#define CB_UNIDADES2 105
#define EDIT_2 106
#define EDIT_RESULTADO 106
#define BTN_CONVERITR 106

/*WINAPI (POE): Calificador de funciones, una funcion puede ser llamada por otra funcion
Indica que la funcion será llamada por otra funcion fuera del codigo, en este
caso WINAPI idica que WinMain será llamado por el OS,tiene 4 parametros:
1 HINSTANCE: Manipulador de la Instancia actual del programa.
2 HINSTANCE: Manipulador de la instancia previa del programa.
3 LPSTR: Puntero a una cadena de caracteres, donde almacena los argumentos
de la linea de comandos
4 int nCmdShow : Entero que indica la forma en que se muestra la pantalla (max,min,etc).
h -> HANDLE (manejador de ventana)
lp -> long pointer
i o n -> int
*/
LRESULT CALLBACK WndPrincipalProc(HWND ventana,UINT msg, WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstanciaActual,HINSTANCE hInstanciaPrevia,LPSTR lpCmdLinea,int nCmdShow){
    WNDCLASSEX clase; //estructura que contienen un conjunto de elementos que caracterizan a una ventana
    HWND ventana; //manejador de ventana
    MSG mensaje; //mensaje que recibiran todos mensajes de la aplicacion

    clase.cbSize = sizeof(WNDCLASSEX); //tamaño de la clase es igual al tamaño de ka estructura
    clase.cbWndExtra = 0; //tamaño extra
    clase.cbClsExtra = 0; //bytes extras para la clase
    clase.style = CS_HREDRAW|CS_VREDRAW; //se puede dibujar horizontalmente y verticalmente
    clase.lpfnWndProc = WndPrincipalProc;
    clase.hInstance = hInstanciaActual;
    clase.hIcon = LoadIcon(NULL,IDI_INFORMATION); //Identificador de icono
    clase.hIconSm =LoadIcon(NULL,IDI_INFORMATION);
    clase.hCursor = LoadCursor(NULL,IDC_ARROW); //Identificador de cursor
    clase.lpszClassName = "MI CLASE 1"; //puntero largo a una cadena que termine en cero o null
    clase.lpszMenuName = NULL;
    clase.hbrBackground = (HBRUSH)COLOR_WINDOW;   //manipulador de pincel

    if(!RegisterClassEx(&clase)){ //si no se ha registrado la clase
        MessageBox( NULL,"No se pudo ejecutar la aplicacion","Error",MB_ICONERROR);
        return EXIT_FAILURE;
    }
    ventana = CreateWindowEx(0,"MI CLASE 1","Ejemplo1",WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU,310,0,560,630,HWND_DESKTOP,NULL,hInstanciaActual,NULL);

    if(ventana == NULL){
        MessageBox( NULL,"No se pudo crear la ventana","Error",MB_ICONERROR);
        return EXIT_FAILURE;
    }
    ShowWindow(ventana,nCmdShow);
    UpdateWindow(ventana);//Actualizar la ventana

    while(GetMessage(&mensaje,NULL,0,0)>0){ //cuando la pila de mensaje recibe el mensaje cero se acaba el programa
            TranslateMessage(&mensaje); //traducir el mensjae que a capturado la funcion GetMesage
            DispatchMessage(&mensaje); //enviar el mensaje traducido al procedimiento de ventana
            //llama al procedimiento de ventana
    }

    //MessageBox(HWND_DESKTOP,"Hola Mundo","Mensaje emergente",MB_OK);
    return mensaje.wParam;

}



LRESULT CALLBACK WndPrincipalProc(HWND ventana,UINT msg, WPARAM wParam,LPARAM lParam){

   HWND controles,hlogito,numero1,numero2;//instancias de tipo Handle windows
   HBITMAP hlogoBinario; //instancia de tipo Handle bitmap para cargar la imagen
    void LoadImage(){
    //casting de tipo HBITMAP y especificación de la ruta
    hlogoBinario= (HBITMAP)LoadImageW(NULL,L"calculator.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    }

   static HINSTANCE Instancia; //no se destruye por ser estatica
   int nitems; //entero para guardar los items del combobox
   const char *unidades [] = {"Suma","Resta","Multiplicacion","Division"}; //arreglo de puntero a cada cada caracter
   nitems = (sizeof(unidades)/(sizeof(char *))); //capturamos el tamaño del array

    switch(msg){
                case WM_CREATE:{
                          LoadImage(); //crea la imagen
                          Instancia =((LPCREATESTRUCT)lParam)->hInstance; //cassting para convertir en una structura que lleva almacenada la info de la ventana.
                          CreateWindowW(L"Static",L"Ingrese un numero : ",WS_VISIBLE | WS_CHILD | WS_TILED, 90,100,150,20,ventana,(HBRUSH)COLOR_GRADIENTACTIVECAPTION,NULL,NULL);
                          CreateWindowEx(0,"EDIT","",ES_AUTOHSCROLL|ES_LEFT|WS_CHILD|WS_VISIBLE,250,100,40,20,ventana,(HMENU)EDIT_1,Instancia,NULL);
                          CreateWindowW(L"Static",L"Ingrese un numero : ",WS_VISIBLE | WS_CHILD | WS_TILED, 90,150,150,20,ventana,(HBRUSH)COLOR_GRADIENTACTIVECAPTION,NULL,NULL);
                          CreateWindowEx(0,"EDIT","",ES_AUTOHSCROLL|ES_LEFT|WS_CHILD|WS_VISIBLE,250,150,40,20,ventana,(HMENU)EDIT_2,Instancia,NULL);

                          hlogito = CreateWindowW(L"Static",NULL,WS_VISIBLE | WS_CHILD | WS_BORDER | SS_BITMAP, 80,340,0,0,ventana,NULL,NULL,NULL);
                          SendMessageW(hlogito,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM) hlogoBinario);

                          CreateWindow("COMBOBOX","",CBS_DROPDOWNLIST|WS_CHILD|WS_VISIBLE,340,120,100,500,ventana,(HMENU)CB_UNIDADES1,Instancia,NULL);

                           for(int i=0;i<nitems;i++){ //Llenar el combobox
                            SendDlgItemMessage(ventana,CB_UNIDADES1,CB_ADDSTRING,0,(LPARAM)unidades[i]);  //enviar mensajes a un control
                            SendDlgItemMessage(ventana,CB_UNIDADES1,CB_SETCURSEL,(WPARAM)3,(LPARAM)0); //quien aparecera por defecto
                           }

                          CreateWindowEx(0,"BUTTON","Resolver",BS_PUSHBUTTON|BS_CENTER|WS_VISIBLE|WS_CHILD,260,250,150,30,ventana,(HMENU)BTN_LEER ,Instancia,NULL);
                          CreateWindowEx(0,"BUTTON","Salir del programa",BS_PUSHBUTTON|BS_CENTER|WS_VISIBLE|WS_CHILD,400,550,150,30,ventana,(HMENU)BTN_SALIR ,Instancia,NULL);
                          break;
                }




                case WM_COMMAND:{
                        switch(LOWORD(wParam)){ //identificador de control
                            case BTN_LEER:{ //si es presionado el boton
                                char guardarR[20]; //guarda las cadenas que optenemos del combobox1
                                int itemIndice = SendDlgItemMessage(ventana,CB_UNIDADES1,CB_GETCURSEL,0,0); //obtenemos el mensaje del combobox
                                SendDlgItemMessage(ventana,CB_UNIDADES1,CB_GETLBTEXT,itemIndice,(LPARAM)guardarR); //RECUPERAMOS EL INDICE DEL COMBOBOX SELECCIONADO (0 en la ultima instancia si lo hacemos como el comentario de abajo
                                //Tres variables Strings para que seran donde almacenaremos la infromacion del Edit
                                char numeroUno[10];
                                char numeroDos[10];
                                char respuesta[10];
                                //capturamos los edit
                                GetDlgItemText(ventana,EDIT_1,numeroUno,10); //manipulador de la ventana que contiene el control (1°param)
                                GetDlgItemText(ventana,EDIT_2,numeroDos,10);


                                //creamos y realizamos un casting para las variables de tipo double
                                double nmr1 = atof(numeroUno);
                                double nmr2 = atof(numeroDos);
                                //comparamos el combobox en su valor de itemIndice y el nombre "Suma","Resta"...
                                if(strcmp(unidades[itemIndice],"Suma")==0){
                                        double nmr = nmr1 +nmr2;
                                        itoa(nmr,respuesta,10);
                                        CreateWindow("STATIC",respuesta,ES_CENTER|WS_CHILD|WS_VISIBLE,450,123,80,25,ventana,(HMENU)EDIT_RESULTADO,Instancia,NULL); //unidades[itemIndice]
                                }else  if(strcmp(unidades[itemIndice],"Resta")==0){
                                        double nmr = nmr1 -nmr2;
                                        itoa(nmr,respuesta,10);
                                        CreateWindow("STATIC",respuesta,ES_CENTER|WS_CHILD|WS_VISIBLE,450,123,80,25,ventana,(HMENU)EDIT_RESULTADO,Instancia,NULL); //unidades[itemIndice]
                                }else  if(strcmp(unidades[itemIndice],"Multiplicacion")==0){
                                        double nmr = nmr1 * nmr2;
                                        itoa(nmr,respuesta,10);
                                        CreateWindow("STATIC",respuesta,ES_CENTER|WS_CHILD|WS_VISIBLE,450,123,80,25,ventana,(HMENU)EDIT_RESULTADO,Instancia,NULL); //unidades[itemIndice]
                                }else  if(strcmp(unidades[itemIndice],"Division")==0){
                                        if(nmr2==0){ //no se puede dividir un numero entre cero
                                        CreateWindow("STATIC","Error",ES_CENTER|WS_CHILD|WS_VISIBLE,450,123,80,80,ventana,(HMENU)EDIT_RESULTADO,Instancia,NULL); //unidades[itemIndice]

                                        }else{

                                        double nmr = nmr1 / nmr2;
                                        itoa(nmr,respuesta,10);
                                        CreateWindow("STATIC",respuesta,ES_CENTER|WS_CHILD|WS_VISIBLE,450,123,80,25,ventana,(HMENU)EDIT_RESULTADO,Instancia,NULL); //unidades[itemIndice]
                                        }
                                }

                                break;
                            }

                            case BTN_SALIR:{ //si es presionado el boton
                                 if(MessageBox(ventana,"Estas seguro que desea salir?","Salir",MB_DEFBUTTON1|MB_OKCANCEL|MB_ICONQUESTION)==IDOK){
                                 SendMessage(ventana,WM_DESTROY,0,0);
                                 }

                                break;
                            }

                        }

                    break;
                }

                case WM_DESTROY:{
                PostQuitMessage(0); //este cero pasará al bucle para que acabe el programa
                break;
                }

                default:{
                return DefWindowProc(ventana, msg,wParam,lParam);
                }

    }

    return 0;



}



