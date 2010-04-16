/*
 *  alpm-query.h
 *
 *  Copyright (c) 2010 Tuxce <tuxce.net@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _ALPM_QUERY_H
#define _ALPM_QUERY_H
#include <alpm.h>
#include <alpm_list.h>

#define ROOTDIR "/"
#define DBPATH "var/lib/pacman"
#define CONFFILE "etc/pacman.conf"

/*
 * Filter
 */
#define F_FOREIGN 1
#define F_EXPLICIT 2
#define F_DEPS	4
#define F_UNREQUIRED 8
#define F_UPGRADES 16
#define F_GROUP 32


/*
 * Init alpm
 */
int init_alpm (const char *root_dir, const char *db_path);
int init_db_local ();

/*
 * Parse pacman config to find sync databases
 */
/* get_db_sync() returns new list, use FREELIST() to free the list */
alpm_list_t *get_db_sync (const char * config_file);
int init_db_sync (const char * config_file);


/*
 * ALPM search functions
 * Returns number of packages found
 * Those functions call print_package()
 */
int search_pkg_by_depends (pmdb_t *db, alpm_list_t *targets);
int search_pkg_by_conflicts (pmdb_t *db, alpm_list_t *targets);
int search_pkg_by_provides (pmdb_t *db, alpm_list_t *targets);
int search_pkg_by_replaces (pmdb_t *db, alpm_list_t *targets);

/* search by name or db/name and if modify is true, 
 * remove found items from targets.
 */
int search_pkg_by_name (pmdb_t *db, alpm_list_t **targets, int modify);
int search_pkg_by_grp (pmdb_t *db, alpm_list_t **targets, int modify, int listp);


int search_pkg (pmdb_t *db, alpm_list_t *targets);
int list_db (pmdb_t *db, alpm_list_t *targets);
int alpm_search_local (alpm_list_t **res);

/*
 * alpm_pkg_get_str() get info for package
 * alpm_grp_get_str() get info for group
 * str returned should not be passed to free
 */
const char *alpm_pkg_get_str (void *p, unsigned char c);
const char *alpm_local_pkg_get_str (const char *pkg_name, unsigned char c);
const char *alpm_grp_get_str (void *p, unsigned char c);


void alpm_cleanup ();

#endif