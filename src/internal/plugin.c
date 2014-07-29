/* Copyright (C) 2012-2014 Zeex
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>

#include <sampgdk/platform.h>

#if SAMPGDK_WINDOWS
  #include <windows.h>
#else
  #include <dlfcn.h>
  #include <string.h>
#endif

#include "array.h"
#include "init.h"
#include "plugin.h"

static struct sampgdk_array _sampgdk_plugins;

SAMPGDK_MODULE_INIT(plugin) {
  return sampgdk_array_new(&_sampgdk_plugins,
                           1,
                           sizeof(struct sampgdk_plugin));
}

SAMPGDK_MODULE_CLEANUP(plugin) {
  sampgdk_array_free(&_sampgdk_plugins);
}

int sampgdk_plugin_register(void *handle) {
  struct sampgdk_plugin plugin;

  assert(handle != NULL);

  plugin.handle = handle;
  return sampgdk_array_append(&_sampgdk_plugins, &plugin);
}

int sampgdk_plugin_unregister(void *handle) {
  int i;
  struct sampgdk_plugin *plugin;

  assert(handle != NULL);

  for (i = 0; i < _sampgdk_plugins.count; i++) {
    plugin = sampgdk_array_get(&_sampgdk_plugins, i);
    if (plugin->handle == handle) {
      plugin->handle = NULL;
      return 0;
    }
  }

  return -EINVAL;
}

struct sampgdk_plugin *sampgdk_plugin_table(int *number) {
  assert(number != NULL);
  *number = _sampgdk_plugins.count;
  return _sampgdk_plugins.data;
}

int sampgdk_plugin_count(void) {
  return _sampgdk_plugins.count;
}

#if SAMPGDK_WINDOWS

void *sampgdk_plugin_get_symbol(void *handle, const char *name)  {
  assert(handle != NULL);
  assert(name != NULL);
  return (void*)GetProcAddress((HMODULE)handle, name);
}

void *sampgdk_plugin_get_handle(void *address) {
  MEMORY_BASIC_INFORMATION mbi;
  assert(address != NULL);
  if (VirtualQuery(address, &mbi, sizeof(mbi)) == 0) {
    return NULL;
  }
  return (void*)mbi.AllocationBase;
}

void sampgdk_plugin_get_filename(void *address, char *filename, size_t size) {
  HMODULE module = (HMODULE)sampgdk_plugin_get_handle(address);
  assert(address != NULL);
  assert(filename != NULL);
  GetModuleFileName(module, filename, size);
}

#else /* SAMPGDK_WINDOWS */

void *sampgdk_plugin_get_symbol(void *handle, const char *name)  {
  assert(handle != NULL);
  assert(name != NULL);
  return dlsym(handle, name);
}

void *sampgdk_plugin_get_handle(void *address) {
  Dl_info info;
  assert(address != NULL);
  if (dladdr(address, &info) != 0) {
    return dlopen(info.dli_fname, RTLD_NOW);
  }
  return NULL;
}

void sampgdk_plugin_get_filename(void *address, char *filename, size_t size) {
  Dl_info info;
  assert(address != NULL);
  assert(filename != NULL);
  if (dladdr(address, &info) != 0) {
    strncpy(filename, info.dli_fname, size);
  }
}

#endif /* !SAMPGDK_WINDOWS */
