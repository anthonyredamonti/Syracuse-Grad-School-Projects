#pragma once
template < typename T >
T maximum(T value1, T value2, T value3, T value4) {
	T maximumValue = value1;
	if (value2 > maximumValue) {
		maximumValue = value2;
	}
	if (value3 > maximumValue) {
		maximumValue = value3;
	}
	if (value4 > maximumValue) {
		maximumValue = value4;
	}
	return(maximumValue);
}