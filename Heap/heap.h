/**
* @file heap.h
* @author Bruno
* @brief
*/

#ifndef HEAP_H
#define HEAP_H

#include "../main.h"

typedef struct object {
    ClassFile *this_class;
    struct object *super_class;
    u4 *fields;
    u4 *fields_index;
} Object;

/**
*   @fn void nova_heap()
*   @brief
*/
void nova_heap();

/**
*   @fn Object novo_objeto(ClassFile *this_class)
*   @brief
*   @param this_class
*   @return
*/
Object novo_objeto(ClassFile *this_class);

/**
*   @fn u4 get_field(Object *objeto, u4 name_index)
*   @brief
*   @param objeto
*   @param name_index
*   @return
*/
u4 get_field(Object *objeto, u4 name_index);

/**
*   @fn u8 get_field_wide(Object *objeto, u4 name_index)
*   @brief
*   @param objeto
*   @param name_index
*   @return
*/
u8 get_field_wide(Object *objeto, u4 name_index);

/**
*   @fn void set_field(Object *objeto, u4 name_index, u4 field)
*   @brief
*   @param objeto
*   @param name_index
*   @param field
*/
void set_field(Object *objeto, u4 name_index, u4 field);

/**
*   @fn void set_field(Object *objeto, u4 name_index, u8 field)
*   @brief
*   @param objeto
*   @param name_index
*   @param field
*/
void set_field_wide(Object *objeto, u4 name_index, u8 field);

#endif // HEAP_H
