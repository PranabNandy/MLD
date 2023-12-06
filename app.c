/*
 * =====================================================================================
 *
 *       Filename:  app.c
 *
 *    Description:  This file represents the application demonstrating the use of MLD library
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

#include "mld.h"
#include <memory.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/*Application Structures*/

typedef struct emp_ {

    char emp_name[30];
    unsigned int emp_id;
    unsigned int age;
    struct emp_ *mgr;
    float salary;
    int *p;
} emp_t;

typedef struct student_{

    char stud_name[32];
    unsigned int rollno;
    unsigned int age;
    float aggregate;
    struct student_ *best_colleage;
} student_t;

int
main(int argc, char **argv){

    /*Step 1 : Initialize a new structure database */
    struct_db_t *struct_db = calloc(1, sizeof(struct_db_t));
    
    mld_init_primitive_data_types_support(struct_db);

    /*Step 2 : Create structure record for structure emp_t*/
    static field_info_t emp_fields[] = {
        FIELD_INFO(emp_t, emp_name, CHAR,    0),
        FIELD_INFO(emp_t, emp_id,   UINT32,  0),
        FIELD_INFO(emp_t, age,      UINT32,  0),
        FIELD_INFO(emp_t, mgr,      OBJ_PTR, emp_t),
        FIELD_INFO(emp_t, salary,   FLOAT, 0),
        FIELD_INFO(emp_t, p, OBJ_PTR, 0)
    };
    static field_info_t stud_fiels[] = {
        FIELD_INFO(student_t, stud_name, CHAR, 0),
        FIELD_INFO(student_t, rollno,    UINT32, 0),
        FIELD_INFO(student_t, age,       UINT32, 0),
        FIELD_INFO(student_t, aggregate, FLOAT, 0),
        FIELD_INFO(student_t, best_colleage, OBJ_PTR, student_t)
    };
    
    /*Step 3 : Register the structure in structure database*/
    REG_STRUCT(struct_db, emp_t, emp_fields);
    REG_STRUCT(struct_db, student_t, stud_fiels);

    /*Step 4 : Verify the correctness of structure database*/
    print_structure_db(struct_db);
    
    
    

    
    
    
    /*Working with object database*/
    
    
    /*Step 1 : Initialize a new Object database */
    object_db_t *object_db = calloc(1, sizeof(object_db_t));
    object_db->struct_db = struct_db;

    /* Step 2 : Create some sample objects, equivalent to standard 
     * calloc(1, sizeof(student_t))
     */
    student_t *abhishek = xcalloc(object_db, "student_t", 1);
    mld_set_dynamic_object_as_root(object_db, abhishek);
    
    student_t *shivani = xcalloc(object_db, "student_t", 1);
    strncpy(shivani->stud_name, "shivani", strlen("shivani"));
    //abhishek->best_colleage=shivani;            // Leaked the shiani object
    
    emp_t *joseph = xcalloc(object_db, "emp_t", 2);
    strncpy(joseph->emp_name, "joseph_1", strlen("joseph_1"));
    strncpy(joseph[1].emp_name, "joseph_2", strlen("joseph_2"));
    mld_set_dynamic_object_as_root(object_db, joseph);  // Not Leaked the joseph object
    joseph->p = xcalloc(object_db, "int", 5);  // for joseph_1 object
    *(joseph->p)=1000;
    joseph[1].p = xcalloc(object_db, "int", 10); // for joseph_2 object
    *(joseph[1].p)=2000;
    
    print_object_db(object_db);
    
    
    run_mld_algorithm(object_db);
    printf("Leaked Objects : \n");
    report_leaked_objects(object_db);

    return 0;
}
