#include <sqlite3ext.h>
SQLITE_EXTENSION_INIT1

static void freeMyString(void* mystring)
{
    sqlite3_free(mystring);
}
        

/*
** The rep() SQL function returns a string of repeated characters.
*/
static void repFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
    char* myString, *repchar;
    int repcount;
    int i;

    repchar = (char*)sqlite3_value_text(argv[0]);
    repcount = sqlite3_value_int(argv[1]);

    myString = (char*)sqlite3_malloc(repcount+1);

    for(i=0; i<repcount; i++) {
        myString[i] = repchar[0];
    }

    sqlite3_result_text(context, myString, -1, freeMyString);
}

/* SQLite invokes this routine once when it loads the extension.
** Create new functions, collating sequences, and virtual table
** modules here.  This is usually the only exported symbol in
** the shared library.
*/
int sqlite3_extension_init(
  sqlite3 *db,
  char **pzErrMsg,
  const sqlite3_api_routines *pApi
){
  SQLITE_EXTENSION_INIT2(pApi)
  sqlite3_create_function(db, "rep", 2, SQLITE_ANY, 0, repFunc, 0, 0);
  return 0;
}
