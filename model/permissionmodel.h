/*
 * permission.h
 *
 *  Created on: Mar 3, 2010
 *      Author: petergoodman
 *     Version: $Id$
 */

#ifndef PERMISSION_H_
#define PERMISSION_H_

typedef unsigned int PermissionModelSet;

typedef enum {
    ADD_MEMBER              =(1<<0),
    MOVE_MEMBER             =(1<<1),
    EDIT_MEMBER_INFO        =(1<<2),
    EDIT_MEMBER_STATUS      =(1<<3),
    DELETE_MEMBER           =(1<<4),
    INIT_MEMBER_COMMITTEE   =(1<<5),
    EDIT_MEMBER_COMMITTEE   =(1<<6),
    ADD_COMMITTEE           =(1<<7),
    EDIT_COMMITTEE          =(1<<8),
    DELETE_COMMITTEE        =(1<<9),
    PRINT_PRIVATE_LIST      =(1<<10),
    PRINT_PUBLIC_LIST       =(1<<11),
    PRINT_COMMITTEE_LIST    =(1<<12),
    ADD_SELF_TASK           =(1<<13),
    EDIT_SELF_TASK          =(1<<14),
    DELETE_SELF_TASK        =(1<<15),
    PRINT_SLEF_TASK_LIST    =(1<<16),
    ADD_SELF_TASK_SPEC      =(1<<17),
    DELETE_SELF_TASK_SPEC   =(1<<18),
    ACTIVATE_SELF_TASK_SPEC =(1<<19),

    EDIT_COMMITTEE_CHAIR    =(1<<20),
    EDIT_COMMITTEE_SECRETARY=(1<<21),

    VIEW_SELF_INFO          =(1<<22),
    VIEW_OTHER_INFO         =(1<<23),
    EDIT_SELF_PASS          =(1<<24),
    ADD_TASK                =(1<<25),
    EDIT_TASK               =(1<<26),
    DELETE_TASK             =(1<<27),
    PRINT_TASK_LIST         =(1<<28),
    ADD_TASK_SPEC           =(1<<29),
    DELETE_TASK_SPEC        =(1<<30),
    ACTIVATE_TASK_SPEC           =(1<<31)

} PermissionModel;

/*
PermissionModelSet operator|(PermissionModel,PermissionModel);
PermissionModelSet operator|(PermissionModel,PermissionModelSet);
PermissionModelSet operator|(PermissionModelSet,PermissionModel);
PermissionModelSet operator|(PermissionModelSet,PermissionModelSet);
*/

#endif /* PERMISSION_H_ */
