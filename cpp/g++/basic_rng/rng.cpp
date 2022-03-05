#include <random>
#include <limits>

template <typename T>
class RNG32{
public:
	RNG32<T>(T beg = std::numeric_limits<T>::min(), T end = std::numeric_limits<T>::max()){
		rd = new std::random_device();
		gen = new std::mt19937((*rd)());
		dis = new std::uniform_int_distribution<T>(beg, end);
	}
	T operator()(){
		return (*dis)(*gen);
	}
private:
	std::random_device* rd;
	std::mt19937* gen;
	std::uniform_int_distribution<T>* dis;
};

template <typename T>
class RNG64{
public:
	RNG64<T>(T beg = std::numeric_limits<T>::min(), T end = std::numeric_limits<T>::max()){
		rd = new std::random_device();
		gen = new std::mt19937_64((*rd)());
		dis = new std::uniform_int_distribution<T>(beg, end);
	}
	T operator()(){
		return (*dis)(*gen);
	}
private:
	std::random_device* rd;
	std::mt19937_64* gen;
	std::uniform_int_distribution<T>* dis;
};