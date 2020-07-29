#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>

#define DEBUGGING


class VectorField { // for vector components as a scalar fields 
private:
	int SIZE_X = 2, SIZE_Y = 2, SIZE_Z = 2;
	static const int VectorDim = 3;
	class Component;

public:
	VectorField();
	VectorField(std::string FieldType);
	VectorField(int X, int Y, int Z);
	VectorField(int X, int Y, int Z, std::string FieldType);
	VectorField(const VectorField &other);
	~VectorField();	

	//  overload of operators
	Component& operator[] (int r);
	Component operator[] (int r) const;
	
	//  standart vector field operations
	//friend VectorField rot(const VectorField&);
	
	void PrintField(std::ostream&) const;

private:
	class Component {
	private:
		VectorField *that;
		float *projection;
		
	public:

		Component();
		Component(VectorField *outer_this);
		Component(VectorField *outer_this, std::string FieldType);
		Component(const Component &other);
		~Component();
	
		// overload of operators
		Component& operator = (const Component &other);
		float& operator() (int X, int Y, int Z);
		float operator() (int X, int Y, int Z) const;

	private:
		void MemoryAllocator();

	};

	Component Field[VectorDim];

};

VectorField rot(const VectorField&);