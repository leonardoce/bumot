#ifndef __BM2_DB
#define __BM2_DB

struct data_connection;
typedef struct data_connection data_connection;

struct result_set;
typedef struct result_set result_set;

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

/**
 * Esegue una query
 * @return True se va tutto bene
 */
void sql_exec(data_connection *dc, const char *sql);

/**
 * Esegue una query e prende il result set
 * @return Il result set
 */
result_set *sql_retrieve(data_connection *dc, const char *sql);

/**
 * Quante sono le colonne in questo result set?
 */
int rs_cols(result_set *rs);

/**
 * C'e' ancora una riga?
 */
bool rs_next(result_set *rs);

/**
 * Prende i dati della colonna "n" e li mette nella
 * bstring "to"
 */
void rs_get_string(result_set *rs, int n, bstring to);

/**
 * Dealloca tutte le risorse del result set
 */
void rs_destroy(result_set *rs);

#endif
