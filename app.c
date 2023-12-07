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
#include "css.h"
#include <memory.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/*Application Structures*/


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

struct_db_t *struct_db;

object_db_t *object_db;

void
struct_db_init(){
    /*Step 1 : Initialize a new structure database */
    struct_db = calloc(1, sizeof(struct_db_t));
    mld_init_primitive_data_types_support(struct_db);
}

void
struct_db_regis(){

    /*Step 2 : Create structure record for structure emp_t*/
    static field_info_t emp_fields[] = {
        FIELD_INFO(emp_t, emp_name, CHAR,    0),
        FIELD_INFO(emp_t, emp_id,   UINT32,  0),
        FIELD_INFO(emp_t, age,      UINT32,  0),
        FIELD_INFO(emp_t, mgr,      OBJ_PTR, emp_t),
        FIELD_INFO(emp_t, salary,   FLOAT, 0),
        FIELD_INFO(emp_t, p, OBJ_PTR, 0)
    };
    /*Step 3 : Register the structure in structure database*/
    REG_STRUCT(struct_db, emp_t, emp_fields);

    static field_info_t stud_fiels[] = {
        FIELD_INFO(student_t, stud_name, CHAR, 0),
        FIELD_INFO(student_t, rollno,    UINT32, 0),
        FIELD_INFO(student_t, age,       UINT32, 0),
        FIELD_INFO(student_t, aggregate, FLOAT, 0),
        FIELD_INFO(student_t, best_colleage, OBJ_PTR, student_t)
    };
    REG_STRUCT(struct_db, student_t, stud_fiels);

    

}

void 
object_db_init(){
    /*Working with object database*/
    /*Step 1 : Initialize a new Object database */
    object_db = calloc(1, sizeof(object_db_t));
    object_db->struct_db = struct_db;
}

void 
object_1_2_create(){
    /*Step 2 : Create some sample objects, equivalent to standard
     * calloc(1, sizeof(student_t))*/
    student_t *abhishek = xcalloc(object_db, "student_t", 5);
    mld_set_dynamic_object_as_root(object_db, abhishek);
    
    student_t *pranab = xcalloc(object_db, "student_t", 2);
    strncpy(pranab->stud_name, "pranab", strlen("pranab"));
    strncpy(pranab[1].stud_name, "nandy_2", strlen("nandy_2"));
    //abhishek->best_colleage = pranab;
}

void 
object_3_create(){
    student_t *shivani = xcalloc(object_db, "student_t", 1);
    strncpy(shivani->stud_name, "shivani", strlen("shivani"));
    //abhishek->best_colleage = shivani;

}

void 
object_4_create(){
    emp_t *joseph = xcalloc(object_db, "emp_t", 3);
    mld_set_dynamic_object_as_root(object_db, joseph);
    joseph->p = xcalloc(object_db, "int", 1);

}

int
main(int argc, char **argv){

    struct_db_init();
    struct_db_regis();
   
    /*Step 4 : Verify the correctness of structure database*/
    print_structure_db(struct_db);

    object_db_init();
   
    object_1_2_create(); 
    object_3_create();
    object_4_create(); 

    /*  Verify the correctness of object database*/ 
    print_object_db(object_db);

    run_mld_algorithm(object_db);
    printf("Leaked Objects : \n");
    report_leaked_objects(object_db);

    printf(ANSI_STYLE_UNDERLINE ANSI_STYLE_BOLD "\n ---------- Successfully freed the Leaked Objects  Memory -------- \n\n\n" ANSI_COLOR_RESET);
    print_object_db(object_db);

    return 0;
}
