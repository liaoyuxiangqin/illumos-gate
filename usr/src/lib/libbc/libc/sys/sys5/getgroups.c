/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License, Version 1.0 only
 * (the "License").  You may not use this file except in compliance
 * with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 1990 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#pragma ident	"%Z%%M%	%I%	%E% SMI"

/*
 * POSIX.1 compatible getgroups() routine
 * This is needed while gid_t is not the same size as int (or whatever the
 * syscall is using at the time).
 */

#include <sys/types.h>
#include <sys/param.h>
#include <sys/syscall.h>

int
getgroups(int gidsetsize, gid_t grouplist[])
{
	int	glist[NGROUPS];	/* getgroups() syscall returns ints */
	int	i;	/* loop control */
	int	rc;	/* return code hold area */

	rc = _syscall(SYS_getgroups, gidsetsize, glist);
	if (rc > 0 && gidsetsize != 0)
		for (i = 0; i < rc; i++)
			grouplist[i] = (gid_t)glist[i];
	return (rc);
}
