/**
 *  @file rule_diff.h
 *  Public Interface for computing a semantic differences in av rules
 *  (allow, neverallow, auditallow, dontaudit) and in te rules
 *  (type_transition, type_change, type_member).
 *
 *  @author Kevin Carr kcarr@tresys.com
 *  @author Jeremy A. Mowery jmowery@tresys.com
 *  @author Jason Tang jtang@tresys.com
 *
 *  Copyright (C) 2006 Tresys Technology, LLC
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef POLDIFF_RULE_DIFF_H
#define POLDIFF_RULE_DIFF_H

#include <apol/vector.h>
#include <poldiff/poldiff.h>

/******************** avrules diff ********************/

typedef struct poldiff_avrule poldiff_avrule_t;

/**
 *  Get an array of statistics for the number of differences of each
 *  form for av rules.
 *
 *  @param diff The policy difference structure from which to get the
 *  stats.
 *  @param stats Array into which to write the numbers (array must be
 *  pre-allocated).  The order of the values written to the array is
 *  as follows:  number of items of form POLDIFF_FORM_ADDED, number of
 *  POLDIFF_FORM_REMOVED, number of POLDIFF_FORM_MODIFIED, number of
 *  POLDIFF_FORM_ADD_TYPE, and number of POLDIFF_FORM_REMOVE_TYPE.
 */
extern void poldiff_avrule_get_stats(poldiff_t *diff, size_t stats[5]);

/**
 *  Get the vector of av rule differences from the av rule difference
 *  summary.
 *
 *  @param diff The policy difference structure associated with the av
 *  rule difference summary.
 *
 *  @return A vector of elements of type poldiff_avrule_t, or NULL on
 *  error.  The caller should <b>not</b> destroy the vector returned.
 *  If the call fails, errno will be set.
 */
extern apol_vector_t *poldiff_get_avrule_vector(poldiff_t *diff);

/**
 *  Obtain a newly allocated string representation of a difference in
 *  an av rule.
 *
 *  @param diff The policy difference structure associated with the av
 *  rule.
 *  @param avrule The av rule from which to generate the string.
 *
 *  @return A string representation of av rule difference; the caller
 *  is responsible for free()ing this string.  On error, return NULL
 *  and set errno.
 */
extern char *poldiff_avrule_to_string(poldiff_t *diff, const void *avrule);

/**
 *  Get the form of difference from an av rule diff.
 *
 *  @param avrule The av rule from which to get the difference form.
 *
 *  @return The form of difference (one of POLDIFF_FORM_*) or
 *  POLDIFF_FORM_NONE on error.
 */
extern poldiff_form_e poldiff_avrule_get_form(const void *avrule);

/**
 *  Get the type of rule this is from an av rule diff.
 *
 *  @param avrule The av rule from which to get the rule type.
 *
 *  @return One of QPOL_RULE_ALLOW etc, suitable for printing via
 *  apol_rule_type_to_str().
 */
extern uint32_t poldiff_avrule_get_rule_type(const poldiff_avrule_t *avrule);

/**
 *  Get the source type from an av rule diff.
 *
 *  @param avrule The av rule from which to get the type.
 *
 *  @return A string for the type.  <b>Do not free() this string.</b>
 */
extern const char *poldiff_avrule_get_source_type(const poldiff_avrule_t *avrule);

/**
 *  Get the target type from an av rule diff.
 *
 *  @param avrule The av rule from which to get the type.
 *
 *  @return A string for the type.  <b>Do not free() this string.</b>
 */
extern const char *poldiff_avrule_get_target_type(const poldiff_avrule_t *avrule);

/**
 *  Get the object class from an av rule diff.
 *
 *  @param avrule The av rule from which to get the class.
 *
 *  @return A string for the class.  <b>Do not free() this string.</b>
 */
extern const char *poldiff_avrule_get_object_class(const poldiff_avrule_t *avrule);

/**
 *  Get a vector of permissions unmodified by the av rule.  If the
 *  avrule was added or removed by the policy, then this vector will
 *  hold all of the permissions that were added or removed.
 *
 *  @param avrule The av rule diff from which to get the permissions
 *  vector.
 *
 *  @return A vector of permissions strings (type char *) added to the
 *  rule in the modified policy.  If no permissions were added the
 *  size of the returned vector will be 0.  The caller must not
 *  destroy this vector.
 */
extern apol_vector_t *poldiff_avrule_get_unmodified_perms(const poldiff_avrule_t *avrule);

/**
 *  Get a vector of permissions added to the av rule.  Note that this
 *  vector will be non-empty only if the form is
 *  POLDIFF_FORM_MODIFIED.
 *
 *  @param avrule The av rule diff from which to get the permissions
 *  vector.
 *
 *  @return A vector of permissions strings (type char *) added to the
 *  rule in the modified policy.  If no permissions were added the
 *  size of the returned vector will be 0.  The caller must not
 *  destroy this vector.
 */
extern apol_vector_t *poldiff_avrule_get_added_perms(const poldiff_avrule_t *avrule);

/**
 *  Get a vector of permissions removed from the av rule.  Note that
 *  this vector will be non-empty only if the form is
 *  POLDIFF_FORM_MODIFIED.
 *
 *  @param avrule The av rule diff from which to get the permissions
 *  vector.
 *
 *  @return A vector of permissions strings (type char *) removed from
 *  the rule in the original policy.  If no permissions were removed
 *  the size of the returned vector will be 0.  The caller must not
 *  destroy this vector.
 */
extern apol_vector_t *poldiff_avrule_get_removed_perms(const poldiff_avrule_t *avrule);

/******************** terules diff ********************/

typedef struct poldiff_terule poldiff_terule_t;

/**
 *  Get an array of statistics for the number of differences of each
 *  form for te rules.
 *
 *  @param diff The policy difference structure from which to get the
 *  stats.
 *  @param stats Array into which to write the numbers (array must be
 *  pre-allocated).  The order of the values written to the array is
 *  as follows:  number of items of form POLDIFF_FORM_ADDED, number of
 *  POLDIFF_FORM_REMOVED, number of POLDIFF_FORM_MODIFIED, number of
 *  POLDIFF_FORM_ADD_TYPE, and number of POLDIFF_FORM_REMOVE_TYPE.
 */
extern void poldiff_terule_get_stats(poldiff_t *diff, size_t stats[5]);

/**
 *  Get the vector of te rule differences from the te rule difference
 *  summary.
 *
 *  @param diff The policy difference structure associated with the te
 *  rule difference summary.
 *
 *  @return A vector of elements of type poldiff_terule_t, or NULL on
 *  error.  The caller should <b>not</b> destroy the vector returned.
 *  If the call fails, errno will be set.
 */
extern apol_vector_t *poldiff_get_terule_vector(poldiff_t *diff);

/**
 *  Obtain a newly allocated string representation of a difference in
 *  a te rule.
 *
 *  @param diff The policy difference structure associated with the te
 *  rule.
 *  @param terule The te rule from which to generate the string.
 *
 *  @return A string representation of te rule difference; the caller
 *  is responsible for free()ing this string.  On error, return NULL
 *  and set errno.
 */
extern char *poldiff_terule_to_string(poldiff_t *diff, const void *terule);

/**
 *  Get the form of difference from a te rule diff.
 *
 *  @param terule The te rule from which to get the difference form.
 *
 *  @return The form of difference (one of POLDIFF_FORM_*) or
 *  POLDIFF_FORM_NONE on error.
 */
extern poldiff_form_e poldiff_terule_get_form(const void *terule);

/**
 *  Get the type of rule this is from a te rule diff.
 *
 *  @param avrule The av rule from which to get the rule type.
 *
 *  @return One of QPOL_RULE_TYPE_TRANS etc, suitable for printing via
 *  apol_rule_type_to_str().
 */
extern uint32_t poldiff_terule_get_rule_type(const poldiff_terule_t *terule);

/**
 *  Get the source type from a te rule diff.
 *
 *  @param terule The te rule from which to get the type.
 *
 *  @return A string for the type.  <b>Do not free() this string.</b>
 */
extern const char *poldiff_terule_get_source_type(const poldiff_terule_t *terule);

/**
 *  Get the target type from a te rule diff.
 *
 *  @param terule The te rule from which to get the type.
 *
 *  @return A string for the type.  <b>Do not free() this string.</b>
 */
extern const char *poldiff_terule_get_target_type(const poldiff_terule_t *terule);

/**
 *  Get the object class from a te rule diff.
 *
 *  @param terule The te rule from which to get the class.
 *
 *  @return A string for the class.  <b>Do not free() this string.</b>
 */
extern const char *poldiff_terule_get_object_class(const poldiff_terule_t *terule);

/**
 *  Get the object class from a te rule diff.
 *
 *  @param terule The te rule from which to get the class.
 *
 *  @return A string for the class.  <b>Do not free() this string.</b>
 */
extern const char *poldiff_terule_get_object_class(const poldiff_terule_t *terule);

/**
 *  Get the original default type for this type rule.  Note that if
 *  this rule was added (form POLDIFF_FORM_ADDED or
 *  POLDIFF_FORM_ADD_TYPE) then the return value will be NULL.
 *
 *  @param terule The te rule diff from which to get the original
 *  default type.
 *
 *  @return Original default type.  If there was no original type or
 *  upon error then return NULL.  <b>Do not free() this string.</b>
 */
extern const char *poldiff_terule_get_original_default(const poldiff_terule_t *terule);

/**
 *  Get the modified default type for this type rule.  Note that if
 *  this rule was removed (form POLDIFF_FORM_REMOVED or
 *  POLDIFF_FORM_REMOVE_TYPE) then the return value will be NULL.
 *
 *  @param terule The te rule diff from which to get the modified
 *  default type.
 *
 *  @return Modified default type.  If there was no modified type or
 *  upon error then return NULL.  <b>Do not free() this string.</b>
 */
extern const char *poldiff_terule_get_modified_default(const poldiff_terule_t *terule);

#endif /* POLDIFF_RULE_DIFF_H */