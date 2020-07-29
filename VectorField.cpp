#include "VectorField.hpp"

// Component conctuctor & destructor ____________________________________________________

void VectorField::Component::MemoryAllocator() {
	projection = new float[that->SIZE_X * that->SIZE_Y * that->SIZE_Z];
	#ifdef DEBUGGING
		std::cout << "\t\t    mem. allocated: " << projection << "\n";
	#endif
}

VectorField::Component::Component() {
	that = nullptr;
	projection = nullptr;
}

VectorField::Component::Component(VectorField *outer_this) {
	that = outer_this;
	MemoryAllocator();
	#ifdef DEBUGGING
		std::cout << "\t    VF::Comp_::Comp_(VF *outer_this) [";
		std::cout <<  that->SIZE_X << ", " << that->SIZE_Y << ", " << that->SIZE_Z << "] {" << that << ", " << projection << "}\n";
	#endif
}

VectorField::Component::Component(VectorField *outer_this, std::string FieldType)
	: VectorField::Component(outer_this) {
	for (int i = 0; i < that->SIZE_X; ++i)
			for(int j = 0; j < that->SIZE_Y; ++j)
				for (int k = 0; k < that->SIZE_Z; ++k) {
					if (FieldType == "zeroes") {
						projection[i*that->SIZE_Y*that->SIZE_Z + j*that->SIZE_Z + k] = 0;	
					} else if (FieldType == "random") {
						projection[i*that->SIZE_Y*that->SIZE_Z + j*that->SIZE_Z + k] = 100 - rand() % 200 + 0.0001 * (rand() % 10000);			
					} else if (FieldType == "potential") {
						projection[i*that->SIZE_Y*that->SIZE_Z + j*that->SIZE_Z + k] = 1;
					} else if (FieldType == "solenoidal") {}
	}
}

VectorField::Component::Component(const Component &other) {
	#ifdef DEBUGGING
		std::cout << "\t    VF::Comp_::Comp_(const Comp_ &other) [";
		std::cout <<  that->SIZE_X << ", " << that->SIZE_Y << ", " << that->SIZE_Z << "] {" << that << ", " << projection << "}\n";
	#endif

	that = other.that;
	that->SIZE_X = other.that->SIZE_X;
	that->SIZE_Y = other.that->SIZE_Y;
	that->SIZE_Z = other.that->SIZE_Z;
	MemoryAllocator();

	for (int i = 0; i < that->SIZE_X; ++i)
			for(int j = 0; j < that->SIZE_Y; ++j)
				for (int k = 0; k < that->SIZE_Z; ++k)
					projection[i*that->SIZE_Y*that->SIZE_Z + j*that->SIZE_Z + k] = other.projection[i*that->SIZE_Y*that->SIZE_Z + j*that->SIZE_Z + k];
}

VectorField::Component::~Component() {
	if (projection != nullptr) {
		#ifdef DEBUGGING
			std::cout << "\t\t    mem. deleted: " << projection << "\n\n";
		#endif
		delete [] projection;
		projection = nullptr;
	}
}

// VectorField conctuctor & destructor __________________________________________________

VectorField::VectorField() {
	#ifdef DEBUGGING
		std::cout << "\n\tfrom VectorField()" << " {" << this << "}\n";
	#endif
	for (int r = 0; r < VectorDim; ++r) {
		Component r_temp(this);
		Field[r] = r_temp;
	}
	#ifdef DEBUGGING
		std::cout << "\tend of VectorField()\n";
	#endif
}

VectorField::VectorField(std::string FieldType) {
	#ifdef DEBUGGING
		std::cout << "\n\tfrom VectorField(std::string)" << " {" << this << "}\n";
	#endif
	for (int r = 0; r < VectorDim; ++r) {
		Component r_temp(this, FieldType);
		Field[r] = r_temp;
	}
	#ifdef DEBUGGING
		std::cout << "\tend of VectorField(std::string FieldType)\n";
	#endif
}

VectorField::VectorField(int X, int Y, int Z) {
	#ifdef DEBUGGING
		std::cout << "\n\tfrom VectorField(int, int, int)" << " {" << this << "}\n";
	#endif
	SIZE_X = X; SIZE_Y = Y; SIZE_Z = Z;
	for (int r = 0; r < VectorDim; ++r) {
		Component r_temp(this);
		Field[r] = r_temp;
	}
	#ifdef DEBUGGING
		std::cout << "\tend of VectorField(int, int, int)\n";
	#endif
}

VectorField::VectorField(int X, int Y, int Z, std::string FieldType) {
	#ifdef DEBUGGING
		std::cout << "\n\tfrom VectorField(int, int, int, std::string)" << " {" << this << "}\n";
	#endif
	SIZE_X = X; SIZE_Y = Y; SIZE_Z = Z;
	for (int r = 0; r < VectorDim; ++r) {
		Component r_temp(this, FieldType);
		Field[r] = r_temp;
	}
	#ifdef DEBUGGING
		std::cout << "\tend of VectorField(int, int, int, std::string)\n";
	#endif
}

VectorField::VectorField(const VectorField &other) {
	#ifdef DEBUGGING
		std::cout << " VF::VF(const VectorField &other)\n";
	#endif
	SIZE_X = other.SIZE_X; SIZE_Y = other.SIZE_Y; SIZE_Z = other.SIZE_Z;
	for (int r = 0; r < VectorDim; ++r)
		Field[r] = other.Field[r];
}

VectorField::~VectorField() {
	#ifdef DEBUGGING
		std::cout << "\t\t~VectorField()" << " {" << this << "}\n";
	#endif
}

//_______________________________________________________________________________________

VectorField::Component& VectorField::Component::operator = (const Component &other) {
	#ifdef DEBUGGING
		std::cout << "\t\tVF::Comp_& VF::Comp_::operator = (const Comp_ &other)\n";		
	#endif
	if (projection != nullptr) {
		#ifdef DEBUGGING
			std::cout << "\t\t\tmem. deleted: " << projection << "\n\n";
		#endif
		delete [] projection;
		projection = nullptr;
	} 

	if (that == nullptr) { that = other.that; }	
	that->SIZE_X = other.that->SIZE_X;
	that->SIZE_Y = other.that->SIZE_Y;
	that->SIZE_Z = other.that->SIZE_Z;
	MemoryAllocator();
	for (int i = 0; i < that->SIZE_X; ++i)
		for(int j = 0; j < that->SIZE_Y; ++j)
			for (int k = 0; k < that->SIZE_Z; ++k)
				projection[i*that->SIZE_Y*that->SIZE_Z +
						  j*that->SIZE_Z +
						  k] = other.projection[i*that->SIZE_Y*that->SIZE_Z +
											   j*that->SIZE_Z +
											   k];
	
	return *this;
}

float& VectorField::Component::operator() (int X, int Y, int Z) { 
	return projection[X*that->SIZE_Y*that->SIZE_Z + Y*that->SIZE_Z + Z]; }
VectorField::Component& VectorField::VectorField::operator[] (int r) { return Field[r]; } 

// to work with const Component %Name
float VectorField::Component::operator() (int X, int Y, int Z) const {
	return projection[X*that->SIZE_Y*that->SIZE_Z + Y*that->SIZE_Z + Z]; }
VectorField::Component VectorField::VectorField::operator[] (int r) const { return Field[r]; }

//БЛЯ, КАК КРАСИВО ЭТО РАБОТАЕТ
void VectorField::PrintField(std::ostream &os) const {
	for (int i = 0; i < SIZE_X; ++i) {
		os << " x:" << i << "\n"; 
		for(int j = 0; j < SIZE_Y; ++j) {
			os << " y:" << j;
			for (int k = 0; k < SIZE_Z; ++k) {
				os << " z:" << k;		
				os << std::setprecision(4) << std::fixed 
				<< " ("; for (int r = 0; r < VectorDim - 1; ++r)
							os <<  std::setw(9) << Field[r](i, j, k) << ", ";
							os <<  std::setw(9) << Field[VectorDim - 1](i, j, k) << ")";
			}
			os << "\n";
		}
		os << "\n";
	}
}