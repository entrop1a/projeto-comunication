#include "central.h"

int main(){
    Fila* fila;
    fila = criar_fila();
    Element dados;
    
    // condição híbrida de cliente e servidor
    int c_sock = wait_connect_client(7777); // cliente para o sensor
    int s_sock = wait_connect_server(8888); // servidor para a interface
    char buffer_require[1024];
    char buffer_response[1024];
    char conf[] = "connect"; 
    char conf2[] = "carga";
    char alert[] = "[ALERTA]: BATERIA FRACA!";
    char relax[] = "BATERIA PERMANECE NA ZONA SEGURA!";
    char finish[] = "[ALERTA MÁXIMO] O SENSOR ESTÁ TOTALMENTE DESCARREGADO!";
    int cout = 0;

    int cicle;
    float limit;
    
   if(read(s_sock, buffer_response, 1024)){ // lê a requisição de ciclos da interface do usuário
       cicle = atoi(buffer_response);
       memset(buffer_response,'\0',sizeof(buffer_response));
       if(read(s_sock, buffer_response, 1024)){ // lê a requisição de limite da interface do usuário
           limit = atof(buffer_response);
           memset(buffer_response,'\0',sizeof(buffer_response));
            while(1){
                usleep(cicle*1000000);
                sprintf(buffer_require, "%s", conf);
                if(send(c_sock, buffer_require, 1024, 0)){ // envia requisição para o sensor
                    printf("Require send: %s\n", buffer_require);

                    if(read(c_sock, buffer_response, 1024)){ // lê resposta do sensor sinalizando conexão

                        if(strncmp(buffer_response,buffer_require, sizeof(buffer_require)) == 0){
                            printf("Response receive: %s\n\n", buffer_response);
                            sprintf(buffer_require, "%s", conf2);

                            if(send(c_sock, buffer_require, 1024, 0)){ // envia requisição solicitando nível de carga
                                printf("Require send: %s\n", buffer_require);

                                if(read(c_sock, buffer_response, 1024)){ // lê resposta com nível de carga
                                    printf("Response receive: %s\n\n", buffer_response);
                                    cout++;
                                    dados.info.b_level = atof(buffer_response); // recebe a carga e atribui a uma estrutura de dados

                                    if(insere_fila(fila, dados.info)){
                                        if(cout%5 != 0 && cout > 5){
                                            remove_fila(fila);
                                        }
                                        if(cout%5 == 0){
                                            printf("Dados coletados sendo analisados...\n");
                                            imprime_fila(fila);
                                            if(verifica_limit(fila, limit) == 0){
                                                memset(buffer_response,'\0',sizeof(buffer_response));
                                                sprintf(buffer_response, "%s", alert);
                                                send(s_sock, buffer_response, 1024, 0);
                                                printf("A Bateria do sensor chegou ao limite!\n\n");
                                            }
                                            if(verifica_limit(fila, limit) == 1){
                                                memset(buffer_response,'\0',sizeof(buffer_response));
                                                sprintf(buffer_response, "%s", relax);
                                                send(s_sock, buffer_response, 1024, 0);
                                                printf("A bateria permanece na zona segura!\n\n");
                                            }
                                            if(verifica_limit(fila, limit) == 2){
                                                memset(buffer_response,'\0',sizeof(buffer_response));
                                                sprintf(buffer_response, "%s", finish);
                                                send(s_sock, buffer_response, 1024, 0);
                                                printf("O sensor está totalmente descarregado!\n\n");
                                            }
                                            remove_fila(fila);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }   
            }
        }    
    }
    return 0;
}
