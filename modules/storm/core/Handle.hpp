#ifndef STORM_CORE_HANDLE_HPP
#define STORM_CORE_HANDLE_HPP

#include <cstdint>
#include <format>
#include <limits>
#include <type_traits>

namespace storm {
// Generic handle class that is an id and could
// probably take a pointer to representing entity for quick access
struct Handle {
	template <class T>
		requires std::is_integral_v<T>
	constexpr operator T() const noexcept {
		return static_cast<T>(id);
	}

	Handle() :
			id{ std::numeric_limits<value_type>::max() } {}

	template <class T>
		requires std::is_arithmetic_v<T>
	Handle(T val) :
			id{ static_cast<uint32_t>(val) } {}

	auto operator<=>(const Handle &other) const {
		return id <=> other.id;
	}

	auto operator<=>(const uint32_t val) const {
		return id <=> static_cast<uint32_t>(val);
	}

	bool operator==(const Handle &other) const {
		return id == other.id;
	}

	using value_type = uint32_t;
	value_type id;

	template <class T>
		requires std::is_arithmetic_v<T>
	void operator=(T number) {
		id = static_cast<uint32_t>(number);
	}

	Handle(const Handle &) = default;
	Handle &operator=(const Handle &number) = default;
	Handle(Handle &&) = default;
	Handle &operator=(Handle &&number) = default;

	Handle &operator++(int) {
		++id;
		return *this;
	}

	Handle operator++() {
		auto save = *this;
		++id;
		return save;
	}

	bool IsValid() const {
		return id != std::numeric_limits<value_type>::max();
	}

	void Invalidate() {
		id = std::numeric_limits<value_type>::max();
	}
};
} //namespace storm

template <>
struct std::hash<storm::Handle> {
	std::size_t operator()(const storm::Handle &k) const {
		return std::hash<storm::Handle::value_type>()(k.id);
	}
};

#endif // STORM_CORE_HANDLE_HPP
