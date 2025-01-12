#include "all.h"

OBJ2D* searchSet0(OBJ2D arr[], int dataNum, OBJ2D::MOVE moveAlg, VECTOR2 pos)
{
    for (int i = 0; i < dataNum; ++i)
    {
        if (arr[i].moveAlg != NULL)  continue;

        arr[i] = {};
        arr[i].moveAlg = moveAlg;
        arr[i].pos = pos;
        return &arr[i];
    }

    return NULL;
}
