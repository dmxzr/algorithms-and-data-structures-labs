#ifndef KEY_H
#define KEY_H


#include <stdio.h>
#include <stdlib.h>

#define ULLI unsigned long long int

typedef ULLI KeyType;
typedef ULLI RelType;
typedef ULLI InfoType;

typedef struct KeySpace {
		KeyType key;
		RelType release;
		InfoType info;
} KeySpace;

#endif /* KEY_H */
