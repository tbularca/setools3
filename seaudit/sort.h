/* Copyright (C) 2003 Tresys Technology, LLC
 * see file 'COPYING' for use and warranty information */

/*
 * Author: Karl MacMillan <kmacmillan@tresys.com>
 */

#ifndef LIBAUDIT_SORT_H
#define LIBAUDIT_SORT_H

#include "auditlog.h"

struct sort_action_node;
typedef int (*sort_action_t)(const msg_t *a, const msg_t *b, struct sort_action_node *cl);

typedef struct sort_action_node {
	int msg_types;
	sort_action_t sort;
	struct sort_action_node *prev;
	struct sort_action_node *next;
} sort_action_node_t;

void sort_action_list_destroy(sort_action_node_t *cl);

/* this is not reentrant! */
int audit_log_sort(audit_log_t *log);

int audit_log_append_sort(audit_log_t *log, sort_action_node_t *node);
int audit_log_remove_sort(audit_log_t *log, sort_action_node_t *node);

/* main sort function for qsort */
int msg_compare(const void *a, const void *b);

sort_action_node_t *date_sort_action_create(void);
sort_action_node_t *src_user_sort_action_create(void);
sort_action_node_t *tgt_user_sort_action_create(void);
sort_action_node_t *src_role_sort_action_create(void);
sort_action_node_t *tgt_role_sort_action_create(void);
sort_action_node_t *src_type_sort_action_create(void);
sort_action_node_t *tgt_type_sort_action_create(void);
sort_action_node_t *obj_class_sort_action_create(void);
sort_action_node_t *exe_sort_action_create(void);
sort_action_node_t *path_sort_action_create(void);
sort_action_node_t *dev_sort_action_create(void);
sort_action_node_t *inode_sort_action_create(void);
sort_action_node_t *pid_sort_action_create(void);


#endif
