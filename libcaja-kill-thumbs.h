#ifndef __KILL_THUMBS_H__
#define __KILL_THUMBS_H__

#include <glib-object.h>

G_BEGIN_DECLS

typedef struct killthumbs_s {
	GObject parent;
} killthumbs_t;

typedef struct killthumbs_class_s {
	GObjectClass parent;
} killthumbs_class_t;

GType
killthumbs_get_type (void);

void
killthumbs_register_type (GTypeModule* module);

void
caja_module_initialize (GTypeModule* module);

void
caja_module_shutdown (void);

void
caja_module_list_types (const GType** types, int* num_types);

G_END_DECLS

#endif /* __KILL_THUMBS_H__ */
