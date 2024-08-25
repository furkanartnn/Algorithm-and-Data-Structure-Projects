#include "ImaginaryPoint.h"

// Constructor (tam anlamadým)
ImaginaryPoint::ImaginaryPoint(int real, int imaginary) : real_part(real), imaginary_part(imaginary) {}


// Destructor (IDK)
ImaginaryPoint::~ImaginaryPoint(){}


// Calculate magnitude squared (okay)
int ImaginaryPoint::get_magnitude_squared() const {
	return (real_part * real_part) + (imaginary_part * imaginary_part);
}

// Getter for real part (okay)
int ImaginaryPoint::get_real_part() const{
	return real_part;
}


// Getter for imaginary part (okay)
int ImaginaryPoint::get_imaginary_part() const{
	return imaginary_part;
}

// Overload addition operator (okay)
ImaginaryPoint ImaginaryPoint::operator+(const ImaginaryPoint& other) const{
	return ImaginaryPoint(real_part + other.real_part, imaginary_part + other.imaginary_part);
}

// Overload subtraction operator (okay)
ImaginaryPoint ImaginaryPoint::operator-(const ImaginaryPoint& other) const{
    return ImaginaryPoint(real_part - other.real_part, imaginary_part - other.imaginary_part);
}

// Overload multiplication operator (okay)
ImaginaryPoint ImaginaryPoint::operator*(const ImaginaryPoint& other) const{
    //(1+2i)* (2+4i) = (1*2 - 2*4) + (1*4 + 2*2)i
	int result_real      = ((real_part * other.real_part) - (imaginary_part * other.imaginary_part));
	int result_imaginary = ((real_part* other.imaginary_part)+ (imaginary_part*other.real_part));

	return ImaginaryPoint(result_real,result_imaginary);
}

// Overload less than operator (okay)
bool ImaginaryPoint::operator<(const ImaginaryPoint& other) const
{
    return get_magnitude_squared()< other.get_magnitude_squared();
}
