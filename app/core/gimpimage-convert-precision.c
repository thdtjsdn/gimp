/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * gimpimage-convert-precision.c
 * Copyright (C) 2012 Michael Natterer <mitch@gimp.org>
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

#include "config.h"

#include <gegl.h>

#include "core-types.h"

#include "gegl/gimp-gegl-utils.h"

#include "gimpdrawable.h"
#include "gimpimage.h"
#include "gimpimage-convert-precision.h"
#include "gimpimage-undo.h"
#include "gimpimage-undo-push.h"
#include "gimpprogress.h"

#include "gimp-intl.h"


void
gimp_image_convert_precision (GimpImage     *image,
                              GimpPrecision  precision,
                              GimpProgress  *progress)
{
  GList       *all_drawables;
  GList       *list;
  const gchar *undo_desc = NULL;
  gint         nth_drawable, n_drawables;

  g_return_if_fail (GIMP_IS_IMAGE (image));
  g_return_if_fail (precision != gimp_image_get_precision (image));
  g_return_if_fail (precision == GIMP_PRECISION_U8 ||
                    gimp_image_get_base_type (image) != GIMP_INDEXED);
  g_return_if_fail (progress == NULL || GIMP_IS_PROGRESS (progress));

  all_drawables = g_list_concat (gimp_image_get_layer_list (image),
                                 gimp_image_get_channel_list (image));

  n_drawables = g_list_length (all_drawables);

  switch (precision)
    {
    case GIMP_PRECISION_U8:
      undo_desc = C_("undo-type", "Convert Image to 8 bit integer");
      break;

    case GIMP_PRECISION_U16:
      undo_desc = C_("undo-type", "Convert Image to 16 bit integer");
      break;

    case GIMP_PRECISION_U32:
      undo_desc = C_("undo-type", "Convert Image to 32 bit integer");
      break;

    case GIMP_PRECISION_HALF:
      undo_desc = C_("undo-type", "Convert Image to 16 bit floating point");
      break;

    case GIMP_PRECISION_FLOAT:
      undo_desc = C_("undo-type", "Convert Image to 32 bit floating point");
      break;
    }

  if (progress)
    gimp_progress_start (progress, undo_desc, FALSE);

  g_object_freeze_notify (G_OBJECT (image));

  gimp_image_undo_group_start (image, GIMP_UNDO_GROUP_IMAGE_CONVERT,
                               undo_desc);

  /*  Push the image precision to the stack  */
  gimp_image_undo_push_image_precision (image, NULL);

  /*  Set the new precision  */
  g_object_set (image, "precision", precision, NULL);

  for (list = all_drawables, nth_drawable = 0;
       list;
       list = g_list_next (list), nth_drawable++)
    {
      GimpDrawable *drawable = list->data;

      gimp_drawable_convert_type (drawable, image,
                                  gimp_drawable_get_base_type (drawable),
                                  precision, TRUE);

      if (progress)
        gimp_progress_set_value (progress,
                                 (gdouble) nth_drawable / (gdouble) n_drawables);
    }

  /*  convert the selection mask  */
  {
    GimpChannel *mask = gimp_image_get_mask (image);
    GeglBuffer  *buffer;

    gimp_image_undo_push_mask_precision (image, NULL, mask);

    buffer = gimp_gegl_buffer_new (GEGL_RECTANGLE (0, 0,
                                                   gimp_image_get_width  (image),
                                                   gimp_image_get_height (image)),
                                   gimp_image_get_mask_format (image));

    gegl_buffer_copy (gimp_drawable_get_buffer (GIMP_DRAWABLE (mask)), NULL,
                      buffer, NULL);

    gimp_drawable_set_buffer (GIMP_DRAWABLE (mask), FALSE, NULL, buffer);
    g_object_unref (buffer);
  }

  gimp_image_undo_group_end (image);

  gimp_image_precision_changed (image);
  g_object_thaw_notify (G_OBJECT (image));

  if (progress)
    gimp_progress_end (progress);
}
