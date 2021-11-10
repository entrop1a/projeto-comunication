#include "sense.h"

int main(void){
    int s_sock = wait_connect_server(7777); // servidor
    char check[] = "connect";
    char check2[] = "carga";
    char buffer_require[1024];
    char buffer_response[1024];
    float carga = 1.0;

    while (1){
      if(recv(s_sock, buffer_require, 1024, 0)){ // lê requisição de conexão do comp_central
        if(strncmp(check, buffer_require, sizeof(check)) == 0){
          printf("Require received: %s\n", buffer_require);
          sprintf(buffer_response, "%s", check);
          if(write(s_sock, buffer_response, 1024)) printf("Response send: %s\n\n", buffer_response);
        }
        
        if(strncmp(check2, buffer_require, sizeof(check2)) == 0){ // lê requisição de carga do comp_central
          printf("Require received: %s\n", buffer_require);
          bateria(&carga);
          sprintf(buffer_response,"%.3f", carga);
          if(write(s_sock, buffer_response, 1024)) printf("Response send: %s\n\n", buffer_response);
        }
          
      } 

    }

    return 0;
}
