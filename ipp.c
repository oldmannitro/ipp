/* See LICENSE file for copyright and license details
 *
 * ipp is a photo manager for IOS.  It provides functions such as copying favourite photos.
 * It assumes the IOS file systems is already mounted using a tool such as ifuse.
 */

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int
callback(void *data, int argc, char **argv, char **azColName)
{
	int i;
	fprintf(stderr, "%s: ", (const char *)data);
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int
main(int argc, char *argv[])
{
	if (argc !=2) {
		fprintf(stderr, "Usage: %s <ios mount point> <destination>\n", argv[0]));
		return 1;
	}

	if (geteuid() != 0) {
		fprintf(stderr, "This program must be run as root.\n");
		return 2;
	}
	sqlite3 *db;
	char *err_msg = 0;
	int rc;
	rc = sqlite3_open("/mnt/ios/PhotoData/Photos.sqlite", &db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 3;
	}
		char *sql = "SELECT ZDIRECTORY, ZFILENAME, ZFAVORITE FROM ZASSET where ZFAVORITE=1";
	rc = sqlite3_exec(db, sql, callback, 0, &err_msg); if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Failed to select data\n");
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
		sqlite3_close(db);
		return 4;
	}
	sqlite3_close(db);
	return 0;
}
