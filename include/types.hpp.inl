namespace cxbqn::types {

template<typename T>
Array<T>::Array() : values{nullptr} { }

template<typename T>
Array<T>::Array(std::initializer_list<T> vs) {
  shape.push_back(vs.size());
  values = new T[vs.size()];
  std::copy(vs.begin(), vs.end(), values);
}

template<typename T>
Array<T>::Array(std::initializer_list<uz> szs, std::initializer_list<T> vs) {
  std::copy(szs.begin(), szs.end(), std::back_inserter(shape));
  uz len = std::accumulate(szs.begin(), szs.end(), 1, std::multiplies<uz>());
  values = new T[len];
  std::copy(vs.begin(), vs.end(), values);
}

template<typename T>
Array<T>::~Array() {
  if (nullptr == values)
    return;
  delete[] values;
}

#define EXT_EXPLICIT_INSTANTIATE(TYPE) extern template struct Array< TYPE >;

CXBQN_FOR_ALL_TS(EXT_EXPLICIT_INSTANTIATE);

#undef EXT_EXPLICIT_INSTANTIATE

}
