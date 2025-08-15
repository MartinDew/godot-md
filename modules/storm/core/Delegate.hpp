#ifndef STORM_CORE_DELEGATE_HPP
#define STORM_CORE_DELEGATE_HPP

#include <functional>

#include "Handle.hpp"
#include "StaticIndexedArray.hpp"

template <class... Args>
class Delegate {
	using DelegateFuncType = std::function<void(Args...)>;
	StaticIndexedArray<DelegateFuncType> listeners;

public:
	Handle Subscribe(const DelegateFuncType &callback) {
		return listeners.Add(callback);
	}

	void Execute(const Args &...args) {
		if (listeners.Empty()) {
			return;
		}

		for (auto &&l : listeners) {
			l(args...);
		}
	}

	void Remove(Handle &handle) {
		Remove(const_cast<const Handle &>(handle));
		handle.Invalidate();
	}

	void Remove(const Handle &handle) {
		if (!handle.IsValid() || !listeners.HasValue(handle)) {
			return;
		}

		listeners.Remove(handle);
	}

	void Clear() {
		listeners.Clear();
	}
};

#endif // STORM_CORE_DELEGATE_HPP