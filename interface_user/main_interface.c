#include "interface.h"

int main(int argc, char *argv[]){
    int c_sock = wait_connect_client(8888); // cliente
    char buffer_require[1024];
    char buffer_response[1024];
    char *conf = "connect"; 
    char *conf2 = "carga";
    char *accept = "OK";

    int cicle = atoi(argv[1]); //entrada para a definição do intervalo de tempo entre as atualizações
    float limit = atof(argv[2]); //entrada para definição de limite para alerta de bateria fraca de que varia de 1.000 a 0.001

    printf("#### ~~~ BEM-VINDO AO SISTEMA DE MONITORAMENTO DE BATERIAS ~~~ ####\n\n");
    sprintf(buffer_require, "%i", cicle); // atribui a primeira ao buffer de requisição
    if(send(c_sock, buffer_require, 1024, 0)){ // validação e envio do buffer
        memset(buffer_require,'\0',sizeof(buffer_require));
        sprintf(buffer_require, "%f", limit); // atribui a segunda entrada ao buffer de requisição
        if(send(c_sock, buffer_require, 1024, 0)){ // validação e envio do buffer
            while(1){
                if(read(c_sock, buffer_response, 1024)){ // validação e recebimento do buffer de resposta
                    printf("\n%s\n", buffer_response); //imprime os pacotes recebidos do comp_central
                }
            }
        }
    }

  return 0;
}
