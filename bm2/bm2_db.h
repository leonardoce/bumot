#ifndef __BM2_DB
#define __BM2_DB

struct data_connection;
typedef struct data_connection data_connection;

/**
 * Crea una nuova data connection
 * @param connString Nome della data connection
 * @return La data connection creata
 */
data_connection *new_data_connection(const char *connString);

/**
 * Controlla se la connessione dati va bene
 */
bool check_data_connection(data_connection *dc);

/**
 * Distrugge la data connection 
 */
void delete_data_connection(data_connection *dc);

#endif
