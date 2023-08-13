/*
 * =====================================================================================
 *
 *       Filename:  mld.h
 *
 *    Description:  This file defines the data structures used for MLD tool
 *
 *        Version:  1.0
 *        Created:  13 February 2023 05:14:18  IST
 *       Revision:  1.0
 *       Compiler:  gcc
 *
 *         Author:  Pranab Nandy
 *        
 *        
 *        This file is part of the MLD distribution (https://github.com/PranabNandy/MLD/).
 *        Copyright (c) 2017 Pranab Nandy.
 *        This program is free software: you can redistribute it and/or modify
 *        it under the terms of the GNU General Public License as published by  
 *        the Free Software Foundation, version 3.
 *
 *        This program is distributed in the hope that it will be useful, but 
 *        WITHOUT ANY WARRANTY; without even the implied warranty of 
 *        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 *        General Public License for more details.
 *
 *        You should have received a copy of the GNU General Public License 
 *        along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * =====================================================================================
 */

#ifndef __MLD__

/*Structure Data base Definition Begin*/

#define MAX_STRUCTURE_NAME_SIZE 128
#define MAX_FIELD_NAME_SIZE 128

/*Enumeration for data types*/
typedef enum {
    UINT8,
    UINT32,
    INT32,
    CHAR,
    OBJ_PTR,
    FLOAT,
    DOUBLE,
    OBJ_STRUCT
} data_type_t;

#define OFFSETOF(struct_name, fld_name) \
    (unsigned int)&(((struct_name *)0)->fld_name)

typedef struct _struct_db_rec_t struct_db_rec_t;

/*Structure to store the information of one field of a 
 * C structure*/
typedef struct _field_info_{
    char fname [MAX_FIELD_NAME_SIZE];   /*Name of the field*/
    data_type_t dtype;                  /*Data type of the field*/
    unsigned int size;                  /*Size of the field*/
    unsigned int offset;                /*Offset of the field*/
    // Below field is meaningful only if dtype = OBJ_PTR, Or OBJ_STRUCT
    char nested_str_name[MAX_STRUCTURE_NAME_SIZE];
} field_info_t;

/*Structure to store the information of one C structure
 * which could have 'n_fields' fields*/
struct _struct_db_rec_t{
    struct_db_rec_t *next;  /*Pointer to the next structure in the linked list*/
    char struct_name [MAX_STRUCTURE_NAME_SIZE];  // key
    unsigned int ds_size;   /*Size of the structure*/
    unsigned int n_fields;  /*No of fields in the structure*/
    field_info_t fields[0]; /*array of Fields info, no of elements = n_fields*/
};

/*Finally the head of the linked list representing the structure
 * database*/
typedef struct _struct_db_{
    struct_db_rec_t *head;
    unsigned int count;
} struct_db_t;


/*Structure Data base Definition Ends*/

/* Printing functions*/
void
print_structure_rec (struct_db_rec_t *struct_rec);

void
print_structure_db(struct_db_t *struct_db);

/* Fn to add the structure record in a structure database */

int /*return 0 on success, -1 on failure for some reason*/
add_structure_to_struct_db(struct_db_t *struct_db, struct_db_rec_t *struct_rec);

#endif /* __MLD__ */