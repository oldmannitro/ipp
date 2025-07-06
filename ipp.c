/* See LICENSE file for copyright and license details
 *
 * ipp (IOS Photo Processor) provides functions such as copying favourite photos.
 * It assumes the IOS file systems is already mounted using a tool such as ifuse.
 *
 * Future enhancement will include the ability to specifiy a source album
 */

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ipp.h"
#include <string.h>

static int
callback(void *data, int argc, char **argv, char **azColName)
{
    CallbackData *cb_data = (CallbackData *)data;
    char src_path[1024];
    char dest_path[1024];
    char command[2048];
    char *zdirectory = NULL;
    char *zfilename = NULL;

    for (int i = 0; i < argc; i++) {
        if (strcmp(azColName[i], "ZDIRECTORY") == 0) {
            zdirectory = argv[i];
        } else if (strcmp(azColName[i], "ZFILENAME") == 0) {
            zfilename = argv[i];
        }
    }

    if (zdirectory && zfilename) {
        snprintf(src_path, sizeof(src_path), "%s/%s/%s", cb_data->mountpoint, zdirectory, zfilename);
        snprintf(dest_path, sizeof(dest_path), "%s/%s", cb_data->destination, zfilename);
        snprintf(command, sizeof(command), "cp \"%s\" \"%s\" 2>/dev/null", src_path, dest_path);

        printf("Copying %s to %s\n", src_path, dest_path);
        if (system(command) == -1) {
            fprintf(stderr, "Failed to copy file\n");
        }
    } else {
        fprintf(stderr, "Error: ZDIRECTORY or ZFILENAME not found in query results.\n");
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    if (argc !=3) {
        fprintf(stderr, "Usage: %s <ios mount point> <destination>\n", argv[0]);
        return 1;
    }

    if (geteuid() != 0) {
        fprintf(stderr, "This program must be run as root.\n");
        return 2;
    }
    sqlite3 *db;
    char *err_msg = 0;
    int rc;
    CallbackData cb_data;
    char db_path[1024];

    cb_data.mountpoint = argv[1];
    cb_data.destination = argv[2];

    snprintf(db_path, sizeof(db_path), "%s/PhotoData/Photos.sqlite", cb_data.mountpoint);
    rc = sqlite3_open(db_path, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 3;
    }
    char *sql = "SELECT ZDIRECTORY, ZFILENAME, ZFAVORITE FROM ZASSET where ZFAVORITE=1";
    rc = sqlite3_exec(db, sql, callback, &cb_data, &err_msg); if (rc != SQLITE_OK)
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
