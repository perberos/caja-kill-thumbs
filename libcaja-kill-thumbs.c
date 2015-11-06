#include "libcaja-kill-thumbs.h"
#include <libcaja-extension/caja-info-provider.h>

static GType killthumbs_type = 0;

/**
 * Esta funcion se ejecuta cada vez que se pide informacion sobre
 * un archivo. Lo que lo hace algo caro en consumo de recursos.
 */
static CajaOperationResult
killthumbs_update_file_info (CajaInfoProvider* provider,
                             CajaFileInfo* file,
                             GClosure* update_complete,
                             CajaOperationHandle** handle)
{
	gchar* name = caja_file_info_get_name (file);
	// let's hadoooooooooken
	if (name != NULL)
	{
		if (g_strcmp0 (name, "Thumbs.db") == 0)
		{
			char* scheme = caja_file_info_get_uri_scheme (file);

			if (scheme != NULL)
			{
				// ignoramos el archivo si ya está en la basura
				if (g_strcmp0 (scheme, "trash") != 0)
				{
					gchar* uri = caja_file_info_get_uri (file);

					if (uri != NULL)
					{
						GFile* file = g_file_new_for_uri (uri);

						if (file != NULL)
						{
							gboolean ret = g_file_trash (file, NULL, NULL); // silent
							
							if (ret == FALSE)
							{
								g_file_delete (file, NULL, NULL);
							}
							
							g_object_unref (file);
						}

						g_free (uri);
					}

					// una pequeña referencia de que será borrado
					caja_file_info_add_emblem (file, "unreadable");
				}

				g_free (scheme);
			}
		}

		g_free (name);
	}

	return CAJA_OPERATION_COMPLETE;
}

/**
 * esto es realmente necesario?
 */
static void
killthumbs_instance_init (killthumbs_t* instance)
{
}

/**
 * esto es realmente necesario?
 */
static void
killthumbs_class_init (killthumbs_class_t* class)
{
}

/**
 * Se establecen los callbacks de la clase CajaInfo
 */
static void
killthumbs_iface_init (CajaInfoProviderIface* iface)
{
	iface->update_file_info = killthumbs_update_file_info;
}


/**
 * Solamente devuelve el ID del tipo de objeto, pero necesita ser registrado
 * antes de usarlo.
 */
GType
killthumbs_get_type (void)
{
	return killthumbs_type;
}

/**
 * Se registran los objetos del plugin.
 * ¿Es posible limpiar esto al desactivar el plugin?
 */
void
killthumbs_register_type (GTypeModule* module)
{
	static const GTypeInfo info = {
		sizeof (killthumbs_class_t),
		(GBaseInitFunc) NULL,
		(GBaseFinalizeFunc) NULL,
		(GClassInitFunc) killthumbs_class_init,
		NULL,
		NULL,
		sizeof (killthumbs_t),
		0,
		(GInstanceInitFunc) killthumbs_instance_init,
	};

	static const GInterfaceInfo iface = {
		(GInterfaceInitFunc) killthumbs_iface_init,
		NULL
	};

	/**
	 * registramos el tipo con glib
	 */
	killthumbs_type = g_type_module_register_type (module,
	                                               G_TYPE_OBJECT,
	                                               "killthumbs",
	                                               &info,
	                                               0);

	g_type_module_add_interface (module,
	                             killthumbs_type,
	                             caja_info_provider_get_type (),
	                             &iface);
}

/**
 * Inicializacion y finalizacion del plugin
 */
static GType type_list[1];

/**
 * Esto se ejecuta al iniciar el programa Caja
 */
void
caja_module_initialize (GTypeModule* module)
{
	killthumbs_register_type (module);
	// cache
	type_list[0] = killthumbs_get_type ();
}

/**
 * Esto se ejecuta al terminar el plugin, no el programa
 */
void
caja_module_shutdown (void)
{
}

/**
 * ¿¿¿???
 */
void
caja_module_list_types (const GType** types, int* num_types)
{
	*types = type_list;
	*num_types = 1;
}
