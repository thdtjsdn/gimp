/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* NOTE: This file is auto-generated by pdbgen.pl. */

#include "config.h"

#include <gegl.h>

#include <gdk-pixbuf/gdk-pixbuf.h>

#include "libgimpbase/gimpbase.h"

#include "libgimpbase/gimpbase.h"

#include "pdb-types.h"

#include "core/gimp-parasites.h"
#include "core/gimp-utils.h"
#include "core/gimp.h"
#include "core/gimpparamspecs.h"

#include "gimppdb.h"
#include "gimpprocedure.h"
#include "internal-procs.h"


static GimpValueArray *
version_invoker (GimpProcedure         *procedure,
                 Gimp                  *gimp,
                 GimpContext           *context,
                 GimpProgress          *progress,
                 const GimpValueArray  *args,
                 GError               **error)
{
  GimpValueArray *return_vals;
  gchar *version = NULL;

  version = g_strdup (GIMP_VERSION);

  return_vals = gimp_procedure_get_return_values (procedure, TRUE, NULL);
  g_value_take_string (gimp_value_array_index (return_vals, 1), version);

  return return_vals;
}

static GimpValueArray *
getpid_invoker (GimpProcedure         *procedure,
                Gimp                  *gimp,
                GimpContext           *context,
                GimpProgress          *progress,
                const GimpValueArray  *args,
                GError               **error)
{
  GimpValueArray *return_vals;
  gint32 pid = 0;

  pid = gimp_get_pid ();

  return_vals = gimp_procedure_get_return_values (procedure, TRUE, NULL);
  g_value_set_int (gimp_value_array_index (return_vals, 1), pid);

  return return_vals;
}

static GimpValueArray *
quit_invoker (GimpProcedure         *procedure,
              Gimp                  *gimp,
              GimpContext           *context,
              GimpProgress          *progress,
              const GimpValueArray  *args,
              GError               **error)
{
  gboolean success = TRUE;
  gboolean force;

  force = g_value_get_boolean (gimp_value_array_index (args, 0));

  if (success)
    {
      gimp_exit (gimp, force);
    }

  return gimp_procedure_get_return_values (procedure, success,
                                           error ? *error : NULL);
}

static GimpValueArray *
attach_parasite_invoker (GimpProcedure         *procedure,
                         Gimp                  *gimp,
                         GimpContext           *context,
                         GimpProgress          *progress,
                         const GimpValueArray  *args,
                         GError               **error)
{
  gboolean success = TRUE;
  const GimpParasite *parasite;

  parasite = g_value_get_boxed (gimp_value_array_index (args, 0));

  if (success)
    {
      gimp_parasite_attach (gimp, parasite);
    }

  return gimp_procedure_get_return_values (procedure, success,
                                           error ? *error : NULL);
}

static GimpValueArray *
detach_parasite_invoker (GimpProcedure         *procedure,
                         Gimp                  *gimp,
                         GimpContext           *context,
                         GimpProgress          *progress,
                         const GimpValueArray  *args,
                         GError               **error)
{
  gboolean success = TRUE;
  const gchar *name;

  name = g_value_get_string (gimp_value_array_index (args, 0));

  if (success)
    {
      gimp_parasite_detach (gimp, name);
    }

  return gimp_procedure_get_return_values (procedure, success,
                                           error ? *error : NULL);
}

static GimpValueArray *
get_parasite_invoker (GimpProcedure         *procedure,
                      Gimp                  *gimp,
                      GimpContext           *context,
                      GimpProgress          *progress,
                      const GimpValueArray  *args,
                      GError               **error)
{
  gboolean success = TRUE;
  GimpValueArray *return_vals;
  const gchar *name;
  GimpParasite *parasite = NULL;

  name = g_value_get_string (gimp_value_array_index (args, 0));

  if (success)
    {
      parasite = gimp_parasite_copy (gimp_parasite_find (gimp, name));

      if (! parasite)
        success = FALSE;
    }

  return_vals = gimp_procedure_get_return_values (procedure, success,
                                                  error ? *error : NULL);

  if (success)
    g_value_take_boxed (gimp_value_array_index (return_vals, 1), parasite);

  return return_vals;
}

static GimpValueArray *
get_parasite_list_invoker (GimpProcedure         *procedure,
                           Gimp                  *gimp,
                           GimpContext           *context,
                           GimpProgress          *progress,
                           const GimpValueArray  *args,
                           GError               **error)
{
  GimpValueArray *return_vals;
  gint32 num_parasites = 0;
  gchar **parasites = NULL;

  parasites = gimp_parasite_list (gimp, &num_parasites);

  return_vals = gimp_procedure_get_return_values (procedure, TRUE, NULL);

  g_value_set_int (gimp_value_array_index (return_vals, 1), num_parasites);
  gimp_value_take_stringarray (gimp_value_array_index (return_vals, 2), parasites, num_parasites);

  return return_vals;
}

void
register_gimp_procs (GimpPDB *pdb)
{
  GimpProcedure *procedure;

  /*
   * gimp-version
   */
  procedure = gimp_procedure_new (version_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-version");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-version",
                                     "Returns the host GIMP version.",
                                     "This procedure returns the version number of the currently running GIMP.",
                                     "Manish Singh",
                                     "Manish Singh",
                                     "1999",
                                     NULL);
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_string ("version",
                                                           "version",
                                                           "GIMP version number",
                                                           FALSE, FALSE, FALSE,
                                                           NULL,
                                                           GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-getpid
   */
  procedure = gimp_procedure_new (getpid_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-getpid");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-getpid",
                                     "Returns the PID of the host GIMP process.",
                                     "This procedure returns the process ID of the currently running GIMP.",
                                     "Michael Natterer <mitch@gimp.org>",
                                     "Michael Natterer",
                                     "2005",
                                     NULL);
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_int32 ("pid",
                                                          "pid",
                                                          "The PID",
                                                          G_MININT32, G_MAXINT32, 0,
                                                          GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-quit
   */
  procedure = gimp_procedure_new (quit_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-quit");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-quit",
                                     "Causes GIMP to exit gracefully.",
                                     "If there are unsaved images in an interactive GIMP session, the user will be asked for confirmation. If force is TRUE, the application is quit without querying the user to save any dirty images.",
                                     "Spencer Kimball & Peter Mattis",
                                     "Spencer Kimball & Peter Mattis",
                                     "1995-1996",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               g_param_spec_boolean ("force",
                                                     "force",
                                                     "Force GIMP to quit without asking",
                                                     FALSE,
                                                     GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-attach-parasite
   */
  procedure = gimp_procedure_new (attach_parasite_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-attach-parasite");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-attach-parasite",
                                     "Add a global parasite.",
                                     "This procedure attaches a global parasite. It has no return values.",
                                     "Jay Cox",
                                     "Jay Cox",
                                     "1998",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_parasite ("parasite",
                                                         "parasite",
                                                         "The parasite to attach",
                                                         GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-detach-parasite
   */
  procedure = gimp_procedure_new (detach_parasite_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-detach-parasite");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-detach-parasite",
                                     "Removes a global parasite.",
                                     "This procedure detaches a global parasite from. It has no return values.",
                                     "Jay Cox",
                                     "Jay Cox",
                                     "1998",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("name",
                                                       "name",
                                                       "The name of the parasite to detach.",
                                                       FALSE, FALSE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-get-parasite
   */
  procedure = gimp_procedure_new (get_parasite_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-get-parasite");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-get-parasite",
                                     "Look up a global parasite.",
                                     "Finds and returns the global parasite that was previously attached.",
                                     "Jay Cox",
                                     "Jay Cox",
                                     "1998",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("name",
                                                       "name",
                                                       "The name of the parasite to find",
                                                       FALSE, FALSE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_parasite ("parasite",
                                                             "parasite",
                                                             "The found parasite",
                                                             GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-get-parasite-list
   */
  procedure = gimp_procedure_new (get_parasite_list_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-get-parasite-list");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-get-parasite-list",
                                     "List all parasites.",
                                     "Returns a list of all currently attached global parasites.",
                                     "Marc Lehmann",
                                     "Marc Lehmann",
                                     "1999",
                                     NULL);
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_int32 ("num-parasites",
                                                          "num parasites",
                                                          "The number of attached parasites",
                                                          0, G_MAXINT32, 0,
                                                          GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_string_array ("parasites",
                                                                 "parasites",
                                                                 "The names of currently attached parasites",
                                                                 GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);
}
