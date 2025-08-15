#include "register_types.h"

void initialize_storm_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		// Register your types here.
		// Example: ClassDB::register_class<MyClass>();
	}
	// Other initialization levels can be used for other purposes, like registering singletons.
	// Example: if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR) { ... }
}

void uninitialize_storm_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}