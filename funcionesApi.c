#include "funciones.h"

cJSON* cuerpo_post(const char* nom, const char* codigo_grupo, int vencedor){

    cJSON *resultado = cJSON_CreateObject();
    cJSON *jugador = cJSON_CreateObject();

    if(cJSON_AddStringToObject(resultado, "codigoGrupo", codigo_grupo) == NULL){
        cJSON_Delete(resultado);
        cJSON_Delete(jugador);
        return NULL;
    }
    if(cJSON_AddStringToObject(jugador, "nombre", nom) == NULL){
        cJSON_Delete(resultado);
        cJSON_Delete(jugador);
        return NULL;
    }

    if(cJSON_AddNumberToObject(jugador, "vencedor", vencedor) == NULL){
        cJSON_Delete(resultado);
        cJSON_Delete(jugador);
        return NULL;
    }

    if(!cJSON_AddItemToObject(resultado, "jugador", jugador)){
        cJSON_Delete(resultado);
        cJSON_Delete(jugador);
        return NULL;
    }

    return resultado;
}

int peticion_post(const char* str_cuerpo, const char* api){
    CURL *curl_hnd;
    struct curl_slist *headers = NULL;
    long http_code = 0;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl_hnd = curl_easy_init();
    if(!curl_hnd){
        curl_global_cleanup();
        return 0;
    }

    headers = curl_slist_append(headers, "Content-Type: application/json; charset=utf-8");
    curl_easy_setopt(curl_hnd, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl_hnd, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl_hnd, CURLOPT_SSL_VERIFYHOST, 0L);

    curl_easy_setopt(curl_hnd, CURLOPT_URL, api);
    curl_easy_setopt(curl_hnd, CURLOPT_POSTFIELDS, str_cuerpo);
    curl_easy_setopt(curl_hnd, CURLOPT_POSTFIELDSIZE, (long)strlen(str_cuerpo));

    curl_easy_perform(curl_hnd);

    curl_easy_getinfo(curl_hnd, CURLINFO_RESPONSE_CODE, &http_code);


    curl_slist_free_all(headers);
    curl_easy_cleanup(curl_hnd);
    curl_global_cleanup();

    if(http_code>=300)
        return 0;

    return 1;
}

int enviar_resultado_api(const char* nombre_jugador, int vencedor){
    cJSON *jugador = NULL;
    char url_api[MAX_LINEA], codigo_grupo[MAX_LINEA];
    char *str_cuerpo = NULL;

    leer_configuracion_api("api.txt", url_api, codigo_grupo);
    jugador = cuerpo_post(nombre_jugador, codigo_grupo, vencedor);
    str_cuerpo = cJSON_Print(jugador);
    if(!peticion_post(str_cuerpo, url_api))
        return 0;
    return 1;
}

size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata){
    size_t tam = size * nmemb;
    Buffer *buffer = (Buffer *)userdata;

    char *temp = realloc(buffer->data, buffer->size + tam + 1);
    if (temp == NULL)
        return 0;

    buffer->data = temp;
    memcpy(buffer->data + buffer->size, ptr, tam);
    buffer->size += tam;
    *(buffer->data + buffer->size) = '\0';

    return tam;
}


cJSON* peticion_get(const char* url_api, const char* codigo_grupo){
    CURL *curl_hnd;
    CURLcode res;
    cJSON *ranking = NULL;
    Buffer buffer = {NULL, 0};
    char api[MAX_LINEA];
    strcpy(api, url_api);
    strcat(api, codigo_grupo);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl_hnd = curl_easy_init();
    if(!curl_hnd){
        curl_global_cleanup();
        return NULL;
    }

    curl_easy_setopt(curl_hnd, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl_hnd, CURLOPT_SSL_VERIFYHOST, 0L);

    curl_easy_setopt(curl_hnd, CURLOPT_URL, api);

    curl_easy_setopt(curl_hnd, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl_hnd, CURLOPT_WRITEDATA, (void*) &buffer);

    res = curl_easy_perform(curl_hnd);

    curl_easy_cleanup(curl_hnd);
    curl_global_cleanup();

    if(res != CURLE_OK || buffer.data == NULL){
        free(buffer.data);
        return NULL;
    }
    ranking = cJSON_Parse(buffer.data);
    free(buffer.data);
    return ranking;
}

void mostrar_ranking(cJSON* ranking){
    cJSON *jugador = NULL;
    cJSON *nombre = NULL;
    cJSON *cant = NULL;
    int i = 0;

    while((jugador = cJSON_GetArrayItem(ranking, i)) != NULL){
        nombre = cJSON_GetObjectItem(jugador, "nombreJugador");
        cant = cJSON_GetObjectItem(jugador, "cantidadPartidasGanadas");
        printf("Nombre del jugador: %s\nCantidad de partidas ganadas: %.0f\n\n", cJSON_GetStringValue(nombre), cJSON_GetNumberValue(cant));
        i++;
    }
    cJSON_Delete(jugador);
}

int leer_configuracion_api(const char* nombre_archivo, char* url_api, char* codigo_grupo){
    FILE *p = fopen(nombre_archivo, "rt");
    char linea[MAX_LINEA], *aux;
    if(!p)
        return 0;
    fgets(linea, sizeof(linea), p);
    aux = strchr(linea, '\n');
    if(aux)
        *aux='\0';
    aux = strrchr(linea, '|');
    if(codigo_grupo){
        *aux = '/';
        strcpy(codigo_grupo, aux);
    }
    if(url_api){
        *aux='\0';
        strcpy(url_api, linea);
    }
    fclose(p);
    return 1;
}

void obtener_ranking(){
    char url_api[MAX_LINEA];
    char codigo_grupo[MAX_LINEA];
    cJSON *ranking = NULL;
    leer_configuracion_api("api.txt", url_api, codigo_grupo);
    ranking = peticion_get(url_api, codigo_grupo);
    if(!ranking){
        printf("ERROR no fue posible obtener el ranking.\n");
        return;
    }
    printf("|---------RANKING DE JUGADORES---------|\n");
    mostrar_ranking(ranking);
    cJSON_Delete(ranking);
}
