#include "register_types.h"

#include "core/JobScheduler.h"
#include "core/core_bind.h"
#include "core/object/class_db.h"
#include "core/os/memory.h"

static storm::JobScheduler *scheduler = nullptr;

void initialize_storm_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		// Register your types here.
		// Example: ClassDB::register_class<MyClass>();

		scheduler = memnew(storm::JobScheduler);
		Engine::get_singleton()->add_singleton(Engine::Singleton{ "JobScheduler", storm::JobScheduler::GetPtr() });
	}
	// Other initialization levels can be used for other purposes, like registering singletons.
	// Example: if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR) { ... }
}

void uninitialize_storm_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		memdelete(scheduler);
	}
}
