
/*--------------------------------------------------------------------*/
/*--- Create/destroy signal delivery frames.                       ---*/
/*---                                         sigframe-x86-linux.c ---*/
/*--------------------------------------------------------------------*/

/*
   This file is part of Valgrind, a dynamic binary instrumentation
   framework.

   Copyright (C) 2000-2013 Nicholas Nethercote
      njn@valgrind.org

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307, USA.

   The GNU General Public License is contained in the file COPYING.
*/

// Athul.M.A
#if defined(VGP_x86_gnu)

#include "pub_core_basics.h"
#include "pub_core_vki.h"
#include "pub_core_libcsetjmp.h"    // to keep _threadstate.h happy
#include "pub_core_threadstate.h"
#include "pub_core_aspacemgr.h" /* find_segment */
#include "pub_core_libcbase.h"
#include "pub_core_libcassert.h"
#include "pub_core_libcprint.h"
#include "pub_core_machine.h"
#include "pub_core_options.h"
#include "pub_core_signals.h"
#include "pub_core_tooliface.h"
#include "pub_core_trampoline.h"
#include "pub_core_sigframe.h"   /* self */

struct vg_sigframe
{
   /* Sanity check word. */
   UInt magicPI;

   UInt handlerflags;	/* flags for signal handler */


   /* Safely-saved version of sigNo, as described above. */
   Int  sigNo_private;

   /* XXX This is wrong.  Surely we should store the shadow values
      into the shadow memory behind the actual values? */
   VexGuestX86State vex_shadow1;
   VexGuestX86State vex_shadow2;

   /* HACK ALERT */
   VexGuestX86State vex;
   /* end HACK ALERT */

   /* saved signal mask to be restored when handler returns */
   vki_sigset_t	mask;

   /* Sanity check word.  Is the highest-addressed word; do not
      move!*/
   UInt magicE;
};

struct sigframe
{
   /* Sig handler's return address */
   Addr retaddr;
   Int  sigNo;

   struct vki_sigcontext sigContext;
   struct vg_sigframe vg;
};

struct rt_sigframe
{
   /* Sig handler's return address */
   Addr retaddr;
   Int  sigNo;

   /* ptr to siginfo_t. */
   Addr psigInfo;

   /* ptr to ucontext */
   Addr puContext;
   /* pointed to by psigInfo */
   vki_siginfo_t sigInfo;

   /* pointed to by puContext */
   struct vki_ucontext uContext;
   struct vg_sigframe vg;
};

void VG_(sigframe_create)( ThreadId tid, 
                           Addr esp_top_of_frame,
                           const vki_siginfo_t *siginfo,
                           const struct vki_ucontext *siguc,
                           void *handler, 
                           UInt flags,
                           const vki_sigset_t *mask,
		           void *restorer )
{

}

#endif
// end