#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>

//#define DEBUGGING

class VectorField;

class ScalarField {
protected:
	int SIZE_X = 2, SIZE_Y = 2, SIZE_Z = 2;
	float *sField;

public:
	ScalarField();
	ScalarField(std::string FieldType);
	ScalarField(int X, int Y, int Z);
	ScalarField(int X, int Y, int Z, std::string FieldType);
	ScalarField(const ScalarField &other);
	~ScalarField();

	// overload of operators
	ScalarField& operator = (const ScalarField &other);
	ScalarField operator + (const ScalarField&) const;
	ScalarField operator - (const ScalarField&) const;
	ScalarField operator * (const float a) const;
	float& operator() (int X, int Y, int Z);
	float operator() (int X, int Y, int Z) const;

	// standart scalar field operation
	friend VectorField grad(const ScalarField&, float dx, float dy, float dz);
	void PrintField(std::ostream&) const;

};


class VectorField : public ScalarField { // for vector components as a scalar fields 
private:
	static const int VectorDim = 3;
	ScalarField Field[VectorDim];

public:

	VectorField();
	VectorField(std::string FieldType);
	VectorField(int X, int Y, int Z);
	VectorField(int X, int Y, int Z, std::string FieldType);
	~VectorField();	

	//  overload of operators
	VectorField operator + (const VectorField&) const;
	VectorField operator - (const VectorField&) const;
	VectorField operator * (const float a) const;
	ScalarField& operator[] (int r);
	ScalarField operator[] (int r) const;
	
	//  standart vector field operations
	friend VectorField rot(const VectorField&, float dx, float dy, float dz);
	friend ScalarField div(const VectorField&, float dx, float dy, float dz);

	void PrintField(std::ostream&) const;

};

VectorField grad(const VectorField::ScalarField&, float dx, float dy, float dz);
VectorField::ScalarField div(const VectorField&, float dx, float dy, float dz);
VectorField rot(const VectorField&, float dx, float dy, float dz);