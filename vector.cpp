#include "vector.h"

//Vector


Vector::Vector(const Value* rawArray, const size_t size, float coef)
:_size(size), _multiplicativeCoef(coef){
	reserve(_size);
	for(int i = 0; i < _size; i++){
		_data[i] = rawArray[i];
	}
}



Vector::Vector(const Vector& other){
    _size = other._size;
    _capacity = other._capacity;
    _data = new Value[_capacity];
    for(int i = 0; i < _size; i++){
        _data[i] = other._data[i];    
    }
}

Vector& Vector::operator=(const Vector& other){
    if(&other == this){
        return *this;
    }
    delete[] _data;
	_size = other._size;
    _capacity = other._capacity;
    _data = new Value[_capacity];
    for(int i = 0; i < _size; i++){
        _data[i] = other._data[i];    
    }
    return *this;
}

Vector::Vector(Vector&& other) noexcept{
	_size = other._size;
    _capacity = other._capacity;
    _data = other._data;
	other._data = nullptr;
    other._size = 0;
    other._capacity = 1;
}
Vector& Vector::operator=(Vector&& other) noexcept{
    if(&other == this){
        return *this;
    }
    delete[] _data;
	_size = other._size;
    _capacity = other._capacity;
    _data = other._data;
	other._data = nullptr;
    other._size = 0;
    other._capacity = 1;	
    return *this;	
}


Vector::~Vector(){
	delete[] _data;
}

void Vector::pushBack(const Value& Value){
	reserve(_size + 1);
	_size++;
	_data[_size - 1] = Value;
}

void Vector::pushFront(const Value& value){
	reserve(_size + 1);
	_size++;
	for(int i = _size - 1; i > 0; i--){
		_data[i] = _data[i - 1];
	}
	_data[0] = value;
}

void Vector::insert(const Value& value, size_t pos){
	if(pos >= _size){
		return;
	}
	reserve(_size + 1);
	_size++;
	for(int i = _size; i > pos; i--){
		_data[i] = _data[i - 1];
	}
	_data[pos] = value;
}

void Vector::insert(const Value* values, size_t size, size_t pos){
	if(pos >= _size){
		return;
	}
	reserve(_size + size);
	_size += size;
	for(int i = _size; i > pos; i--){
		_data[i] = _data[i - size];
	}
	for(int i = 0; i < size; i++){
		_data[pos + i] = values[i];
	}	
}

void Vector::insert(const Vector& vector, size_t pos){
	if(pos >= _size){
		return;
	}
	reserve(_size + vector.size());
	_size += vector.size();
	for(int i = _size; i > pos; i--){
		_data[i] = _data[i - vector.size()];
	}
	for(int i = 0; i < vector.size(); i++){
		_data[pos + i] = vector[i];
	}
}


void Vector::popFront(){
	erase(0);
}

void Vector::popBack(){
	if(_size > 0){
		_size--;
	}
}

void Vector::erase(size_t pos, size_t count){
	if(pos >= _size){
		return;
	}
	if((pos + count) > (_size)){
		count = _size - pos;
	}
	_size -= count;
	for(int i = pos; i < _size; i++){
		_data[i] = _data[i + count];
	}
}

void Vector::eraseBetween(size_t beginPos, size_t endPos){
	if(beginPos >= endPos){
		return;
	}
	erase(beginPos, endPos - beginPos);
	// size_t length;
	// if((endPos - beginPos) > (_size - beginPos)){
	// 	length = _size - beginPos;
	// }
	// else{
	// 	length = endPos - beginPos;
	// }
	// _size -= length;
	// for(int i = beginPos; i < _size; i++){
	// 	_data[i] = _data[i + length];
	// }
}

size_t Vector::size() const{
	return _size;
}

size_t Vector::capacity() const{
	return _capacity;
}

double Vector::loadFactor() const{
	return  static_cast<double>(_size)/_capacity;
}


Value& Vector::operator[](size_t idx){
	return _data[idx];
}


const Value& Vector::operator[](size_t idx) const{
	return _data[idx];
}


long long Vector::find(const Value& value) const{
	for(int i = 0; i < _size; i++){
		if(value == _data[i]){
			return i;
		}
	}
	return -1;
}

void Vector::reserve(size_t capacity){
	if(_nullCheck()){
		_data = new Value[_capacity];
	}
	if(capacity > _capacity){
		while(capacity > _capacity){
			_capacity = static_cast<size_t>(_capacity * _multiplicativeCoef);
		}
		_realloc();
	}
}

void Vector::shrinkToFit(){
	if(_capacity / _multiplicativeCoef >= _size){
		while(_capacity / _multiplicativeCoef >= _size){
			_capacity /= _multiplicativeCoef;
		}
		_realloc();
	}
}

bool Vector::_nullCheck(){
	if (_data == nullptr){
		return true;
	}
	return false;
};

void Vector::_realloc(){
	Value* newdata = new Value[_capacity];
	for(int i = 0; i < _size; i++){
		newdata[i] = _data[i];
	}
	delete[] _data;
	_data = newdata;
}

Vector::Iterator Vector::begin() const
	{
		return Vector::Iterator(&_data[0]);
	}

Vector::Iterator Vector::end() const
	{
		return Vector::Iterator(&_data[_size]);
	}

std::ostream& operator<<(std::ostream& out, const Vector& vector){
	for(auto&& number : vector){
		out << number << ' ';
	}
	return out;
}

//Iterator

Vector::Iterator::Iterator(Value* ptr) : _ptr(ptr)
{}

Value& Vector::Iterator::operator*()
{
	return *_ptr;
}

const Value& Vector::Iterator::operator*() const
{
	return *_ptr;
}

Value* Vector::Iterator::operator->()
{
	return _ptr;
}

const Value* Vector::Iterator::operator->() const
{
	return _ptr;
}



Vector::Iterator Vector::Iterator::operator+(int x)
{
	Vector::Iterator bufIt(_ptr + x); 
	return bufIt;
}

void Vector::Iterator::operator+=(int x)
{
	*this = *this + x;
}

Vector::Iterator Vector::Iterator::operator-(int x)
{
	Vector::Iterator bufIt(_ptr - x); 
	return bufIt;
}

void Vector::Iterator::operator-=(int x)
{
	*this = *this - x;
}

Vector::Iterator Vector::Iterator::operator++()
{
	++_ptr;
	return *this;
}

Vector::Iterator Vector::Iterator::operator++(int)
{
	Vector::Iterator bufIt = *this;
	++*this;
	return bufIt;
}

Vector::Iterator Vector::Iterator::operator--()
{
	--_ptr;
	return *this;
}

Vector::Iterator Vector::Iterator::operator--(int)
{
	Vector::Iterator bufIt = *this;
	--*this;
	return bufIt;
}

bool Vector::Iterator::operator==(const Vector::Iterator& other) const
{
	return _ptr == other._ptr;
}

bool Vector::Iterator::operator!=(const Vector::Iterator& other) const
{
	return !(*this == other);
}