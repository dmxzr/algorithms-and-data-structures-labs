#ifndef KEY_H
#define KEY_H


#include <stdio.h>
#include <stdlib.h>

#define ULLI unsigned long long int

typedef int BusyType;
typedef ULLI KeyType;
typedef ULLI RelType;
typedef char InfoType;

typedef struct KeySpace {
		BusyType busy;
		KeyType key;
		RelType release;
		InfoType *info;
} KeySpace;

#endif /* KEY_H */
