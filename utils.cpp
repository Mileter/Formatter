template < typename F, typename T, std::size_t N, std::size_t ... Idx >
decltype(auto) apply_impl(F f, T(&t)[N], std::index_sequence < Idx ... >)
{
	return f(t[Idx], ...);

}

template < typename F, typename T, std::size_t N >
decltype(auto) apply(F f, T(&t)[N])
{
	return apply_impl(f, t, std::make_index_sequence < N > { }
	);
}
