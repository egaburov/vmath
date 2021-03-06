#include <array>
#include <iostream>

constexpr int f(int i) { return 2 * i; }

template <int M, int N, int... Ts>
struct t { 
  using type = typename t<M, N - 1, Ts..., M+1 - N>::type; 
};

template <int M, int... Ts>
struct t<M, 0u, Ts...>
{
  using type = t<M, 0u, Ts...>;
  static std::array<int, sizeof...(Ts)> apply() { return {{f(Ts)...}}; }
};


int main()
{
  using v = typename t<100, 100>::type;
  auto x = v::apply();
  fprintf(stderr, "size= %d\n", x.size());
  for (int i = 0; i < x.size(); i++)
  {
    fprintf(stderr, "x[%2d]= %d\n", i, x[i]);

  }
}
