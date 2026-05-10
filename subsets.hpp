#pragma once

template <auto... Values>
struct value_sequence
{
	template <auto Value>
	using append = value_sequence<Values..., Value>;
};

template <typename... Types>
struct type_sequence
{
	template <typename Type>
	using append = type_sequence<Types..., Type>;
};

template <typename, typename, auto...>
struct subset_impl;

template <typename Accumulated, typename Subset, auto FirstValue, auto... OtherValues>
struct subset_impl<Accumulated, Subset, FirstValue, OtherValues...>
{
	using with_value = typename subset_impl<
		Accumulated,
		typename Subset::template append<FirstValue>,
		OtherValues...
	>::subsets;

	using subsets = typename subset_impl<
		with_value,
		Subset,
		OtherValues...
	>::subsets;
};

template <typename Accumulated, typename Subset>
struct subset_impl<Accumulated, Subset>
{
	using subsets = typename Accumulated::template append<Subset>;
};

template <auto... Values>
using subsets = typename subset_impl<type_sequence<>, value_sequence<>, Values...>::subsets;
