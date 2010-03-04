/*
 * permission.h
 *
 *  Created on: Mar 3, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef PERMISSION_H_
#define PERMISSION_H_

typedef unsigned int perm_set_t;

enum Permission {
    ADD_MEMBER              =(1<<0),
    MOVE_MEMBER             =(1<<1),
    EDIT_MEMBER_INFO        =(1<<2),
    EDIT_MEMBER_STATUS      =(1<<3),
    DELETE_MEMBER           =(1<<4),
    INIT_MEMBER_COMMITTEE   =(1<<5),
    EDIT_MEMBER_COMMITTEE   =(1<<6),
    ADD_COMMITTEE           =(1<<7),
    EDIT_COMMITTEE          =(1<<8),
    PRINT_PRIVATE_LIST      =(1<<9),
    PRINT_PUBLIC_LIST       =(1<<10),
    PRINT_COMMITTEE_LIST    =(1<<11),
    ADD_TASK                =(1<<12),
    EDIT_TASK               =(1<<13),
    DELETE_TASK             =(1<<14),
    PRINT_TASK_LIST         =(1<<15),
    ADD_TASK_SPEC           =(1<<16),
    DELETE_TASK_SPEC        =(1<<17),
    ACTIVATE_TASK_SPEC      =(1<<18)
};

#endif /* PERMISSION_H_ */
