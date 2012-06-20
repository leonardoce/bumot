#include <stdbool.h>
#include <stdlib.h>
#include "bstrlib.h"
#include "bm2_db.h"
#include "sqlite3.h"
#include "logging.h"

struct data_connection {
	sqlite3 *db;
};

struct result_set {
	sqlite3_stmt *stmt;
};

data_connection *new_data_connection(const char *connString) {
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

bool check_data_connection(data_connection *dc) {
	// Una dataconnection sqlite, se viene allocata,
	// va sempre benone
	return true;
}

void delete_data_connection(data_connection *dc) {
	sqlite3_close(dc->db);
	free(dc);
}

void sql_exec(data_connection *dc, const char *sql) {
	if (sqlite3_exec(dc->db, sql, NULL, NULL, NULL)!=SQLITE_OK) {
		// Errore in esecuzione di una query
		log_error("Errore SQL: ", sql);
	}
}

void sql_into(data_connection *dc, const char *sql, bstring to) {
	sqlite3_stmt *stmt;

	if (sqlite3_prepare (dc->db, sql, strlen(sql), &stmt, NULL)!=SQLITE_OK) {
		// Errore nella query
		sqlite3_finalize(stmt);
		log_error("Errore SQL: ", sql, NULL);
		return;
	}

	btrunc(to, 0);

	while (true) {
		int status = sqlite3_step(stmt);
		if (status==SQLITE_ROW) {
			const char *contents = (const char *)sqlite3_column_text(stmt, 0);
			bcatcstr(to, contents);
		}
	}

	sqlite3_finalize(stmt);
}

result_set *sql_retrieve(data_connection *dc, const char *sql) {
	sqlite3_stmt *stmt;
	int status;
	result_set *rs;

	rs = (result_set *)malloc(sizeof(struct result_set));
	rs->stmt = NULL;

	status = sqlite3_prepare (dc->db, sql, strlen(sql), &stmt, NULL);
	if (status!=SQLITE_OK) {
		sqlite3_finalize(stmt);
		log_error("Errore SQL: ", sql, NULL);
		return rs;
	}

	rs->stmt = stmt;
	return rs;
}

int rs_cols(result_set *rs)
{
	if (rs->stmt==NULL) {
		return 0;
	}

	return sqlite3_column_count(rs->stmt);
}

bool rs_next(result_set *rs)
{
	if (rs->stmt==NULL) {
		return false;
	}

	while (true) {
		int status = sqlite3_step(rs->stmt);
		if (status==SQLITE_ROW) {
			return true;
		} else if (status==SQLITE_DONE) {
			return false;
		} else {
			log_error("Error stepping result set!", NULL);
			return false;
		}
	}
}

void rs_get_string(result_set *rs, int n, bstring to) {
	btrunc(to, 0);

	if (rs->stmt==NULL) {
		return;
	}

	const char *contents = (const char *)sqlite3_column_text(rs->stmt, n);
	if (contents==NULL) {
		return;
	}

	bcatcstr(to, contents);
}

void rs_destroy(result_set *rs) {
	if (rs->stmt!=NULL) {
		sqlite3_finalize(rs->stmt);
	}

	free(rs);
}
