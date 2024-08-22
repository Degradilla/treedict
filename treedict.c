#include "treedict.h"

struct Treedict {
    char      character;
    void*     value;
    Treedict* parent;
    Treedict* next;
    Treedict* child;
};

Treedict* treedict_create(void){
    return calloc(1, sizeof(Treedict) );
}

void treedict_free(Treedict* tree){
    if (tree){
        treedict_free(tree->next);
        treedict_free(tree->child);
        free(tree);
    }
}

void treedict_append(Treedict* tree, char* key, void* value){
        if (!key || !*key) return;
        if (tree->character) goto check_next;
        tree->character = *key;
        goto check_child;

    check_next:
        if (tree->character == *key) goto check_child;
        if (!tree->next) goto create_next; 
        tree = tree->next;
        goto check_next;

    check_child:
        ++key;
        if (!*key) goto write_value;
        if (!tree->child) goto create_child;
        tree = tree->child;
        goto check_next;

    create_child:
        tree->child = calloc(1, sizeof(Treedict) );
        tree->child->parent = tree;
        tree = tree->child;
    append_character:
        tree->character = *key;
        ++key;
        if (*key) goto create_child;

    write_value:
        tree->value = value;
        return;

    create_next:
        tree->next = calloc(1, sizeof(Treedict) );
        tree->next->parent = tree;
        tree = tree->next;
        goto append_character;
}

void* treedict_get(Treedict* tree, char* key){
        if (!key || !*key) return NULL;

    check_next:
        if (tree->character == *key) goto check_child;
        if (!tree->next) return NULL; 
        tree = tree->next;
        goto check_next;

    check_child:
        ++key;
        if (!*key) goto return_value;
        if (!tree->child) return NULL;
        tree = tree->child;
        goto check_next;

    return_value:
        return tree->value;
}

void* treedict_remove(Treedict* tree, char* key){
        Treedict* last;
        void* temp;
        if (!key || !*key) return NULL;

    check_next:
        if (tree->character == *key) goto check_child;
        if (!tree->next) return NULL; 
        tree = tree->next;
        goto check_next;

    check_child:
        ++key;
        if (!*key) goto remove_value;
        if (!tree->child) return NULL;
        tree = tree->child;
        goto check_next;

    remove_value:
        temp = tree->value;
        tree->value = NULL;
        if (tree->next || tree->child) return temp;

    free_useless:
        last = tree;
        tree = tree->parent;
        if (tree->value || (tree->next && tree->child)) goto clear_pointers;
        free(last);
        goto free_useless;

    clear_pointers:
        if (tree->child == last) tree->child = NULL;
        else tree->next = NULL;

    return_value:
        return temp;
}
