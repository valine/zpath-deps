/* $Id: pari.h 12142 2010-02-13 13:49:19Z bill $

Copyright (C) 2000  The PARI group.

This file is part of the PARI/GP package.

PARI/GP is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation. It is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY WHATSOEVER.

Check the License for details. You should have received a copy of it, along
with the package; see the file 'COPYING'. If not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. */

#ifndef __GENPARI__
#define __GENPARI__
#include "paricfg.h"

#include <stdlib.h>   /* malloc, free, atoi */
#ifdef UNIX
#  define _INCLUDE_POSIX_SOURCE /* for HPUX */
#  include <sys/types.h> /* size_t */
#endif

#ifdef WINCE
#  include <windows.h>
#else
#  include <signal.h>
#  include <stdio.h>
#endif

#include <stdarg.h>
#include <setjmp.h>
#include <string.h>
#if !defined(_WIN32) && !defined(WINCE)
#  include <unistd.h>
#else
#  include <io.h>
#endif
#include <math.h>
#include <memory.h>
#include <ctype.h>

#ifdef WINCE
#  include "parice.h"
#endif
#include "parisys.h"
#include "parigen.h"
#include "paricast.h"
#include "paristio.h"
#include "paricom.h"
#include "pariold.h"
#include "parierr.h"
BEGINEXTERN
#include "paridecl.h"
#include "paritune.h"
#ifndef PARI_NO_MPINL_H
#  include "mpinl.h"
#endif
#ifndef PARI_NO_PARIINL_H
#  include "pariinl.h"
#endif
ENDEXTERN
#endif