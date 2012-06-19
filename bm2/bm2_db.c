#include <stdbool.h>
#include <stdlib.h>
#include "bm2_db.h"
#include "sqlite3.h"

struct data_connection {
  sqlite3 *db;
};

data_connection *new_data_connection(const char *connString)
{
  data_connection *dc;

  dc = (data_connection *)malloc(sizeof(struct data_connection));
  if (dc==NULL) return NULL;

  if (sqlite3_open (connString, &dc->db)!=SQLITE_OK) {
    sqlite3_close(dc->db);
    free (dc);
    return NULL;
  }

  return dc;
}

bool check_data_connection(data_connection *dc)
{
  // Una dataconnection sqlite, se viene allocata,
  // va sempre benone
  return true;
}

void delete_data_connection(data_connection *dc)
{
  sqlite3_close(dc->db);
  free(dc);
}

