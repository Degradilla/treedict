#ifndef TREEDICT
#define TREEDICT

#include <stdlib.h>

typedef struct Treedict Treedict;

/* Create empty treedict */
Treedict* treedict_create (void);

/* Free treedict memory */
void treedict_free (Treedict* tree);

/* Append value in treedict by key */
void treedict_append (Treedict* tree, char* key, void* value);

/* Remove and return value from treedict by key */
void* treedict_remove (Treedict* tree, char* key);

/* Return value from treedict by key */
void* treedict_get (Treedict* tree, char* key);

#endif
