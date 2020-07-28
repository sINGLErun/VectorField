#include "VectorField.hpp"

ScalarField::ScalarField() {
	#ifdef DEBUGGING
		std::cout << "\t    ScalarField() [";
		std::cout <<  SIZE_X << ", " << SIZE_Y << ", " << SIZE_Z << "]\n";
	#endif
	sField = new float[SIZE_X * SIZE_Y * SIZE_Z];
	#ifdef DEBUGGING
		std::cout << "\t\tmem. allocated: " << sField << "\n";
	#endif
}

ScalarField::ScalarField(std::string FieldType) : ScalarField::ScalarField() {
	if (FieldType == "zeroes") {
		for (int i = 0; i < SIZE_X; ++i)
			for(int j = 0; j < SIZE_Y; ++j)
				for (int k = 0; k < SIZE_Z; ++k)
					sField[i*SIZE_Y*SIZE_Z + j*SIZE_Z + k] = 0;	

	} else if (FieldType == "random") {
		for (int i = 0; i < SIZE_X; ++i)
			for(int j = 0; j < SIZE_Y; ++j)
				for (int k = 0; k < SIZE_Z; ++k)
					sField[i*SIZE_Y*SIZE_Z + j*SIZE_Z + k] = 100 - rand() % 200 + 0.0001 * (rand() % 10000);	
		
	} else if (FieldType == "potential") {
		for (int i = 0; i < SIZE_X; ++i)
			for(int j = 0; j < SIZE_Y; ++j)
				for (int k = 0; k < SIZE_Z; ++k)
					sField[i*SIZE_Y*SIZE_Z + j*SIZE_Z + k] = 1;
		
	} else if (FieldType == "solenoidal") {}
}

ScalarField::ScalarField(int X, int Y, int Z) {
	SIZE_X = X;
	SIZE_Y = Y;
	SIZE_Z = Z;
	#ifdef DEBUGGING
		std::cout << "\t    ScalarField(int X, int Y, int Z) [";
		std::cout <<  SIZE_X << ", " << SIZE_Y << ", " << SIZE_Z << "]\n";
	#endif
	sField = new float[SIZE_X * SIZE_Y * SIZE_Z];
	#ifdef DEBUGGING
		std::cout << "\t\t\tmem. allocated: " << sField << "\n";	
	#endif
}

ScalarField::ScalarField(int X, int Y, int Z, std::string FieldType) : ScalarField::ScalarField(X, Y, Z) {
	if (FieldType == "zeroes") {
		for (int i = 0; i < SIZE_X; ++i)
			for(int j = 0; j < SIZE_Y; ++j)
				for (int k = 0; k < SIZE_Z; ++k)
					sField[i*SIZE_Y*SIZE_Z + j*SIZE_Z + k] = 0;	

	} else if (FieldType == "random") {
		for (int i = 0; i < SIZE_X; ++i)
			for(int j = 0; j < SIZE_Y; ++j)
				for (int k = 0; k < SIZE_Z; ++k)
					sField[i*SIZE_Y*SIZE_Z + j*SIZE_Z + k] = 100 - rand() % 200 + 0.0001 * (rand() % 10000);	
		
	} else if (FieldType == "potential") {
		for (int i = 0; i < SIZE_X; ++i)
			for(int j = 0; j < SIZE_Y; ++j)
				for (int k = 0; k < SIZE_Z; ++k)
					sField[i*SIZE_Y*SIZE_Z + j*SIZE_Z + k] = 1;
		
	} else if (FieldType == "solenoidal") {}
}

ScalarField::ScalarField(const ScalarField &other) {
	SIZE_X = other.SIZE_X;
	SIZE_Y = other.SIZE_Y;
	SIZE_Z = other.SIZE_Z;
	#ifdef DEBUGGING
		std::cout << "\t    ScalarField(const ScalarField &other) [";
		std::cout <<  SIZE_X << ", " << SIZE_Y << ", " << SIZE_Z << "]\n";
	#endif
	sField = new float[SIZE_X * SIZE_Y * SIZE_Z];
	#ifdef DEBUGGING
		std::cout << "\t\t\tmem. allocated: " << sField << "\n";
	#endif
	for (int i = 0; i < SIZE_X; ++i)
			for(int j = 0; j < SIZE_Y; ++j)
				for (int k = 0; k < SIZE_Z; ++k)
					sField[i*SIZE_Y*SIZE_Z + j*SIZE_Z + k] = other.sField[i*SIZE_Y*SIZE_Z + j*SIZE_Z + k];	
}

ScalarField::~ScalarField() {
	if (sField != nullptr) {
		#ifdef DEBUGGING
			std::cout << "\t\tmem. deleted: " << sField << "\n";
		#endif
		delete [] sField;
		sField = nullptr;
	}
}

VectorField::VectorField() {
	#ifdef DEBUGGING
		std::cout << "\n\tfrom VectorField()\n";
	#endif
	for (int r = 0; r < VectorDim; ++r) {
		ScalarField r_temp;
		Field[r] = r_temp;
	}
	#ifdef DEBUGGING
		std::cout << "\tend of VectorField()\n";
	#endif
}

VectorField::VectorField(std::string FieldType) {
	#ifdef DEBUGGING
		std::cout << "\n\tfrom VectorField(std::string FieldType)\n";
	#endif
	for (int r = 0; r < VectorDim; ++r) {
		ScalarField r_temp(FieldType);
		Field[r] = r_temp;
	}
	#ifdef DEBUGGING
		std::cout << "\tend of VectorField(std::string FieldType)\n";
	#endif
}

VectorField::VectorField(int X, int Y, int Z) {
	#ifdef DEBUGGING
		std::cout << "\n\tfrom VectorField(int X, int Y, int Z)\n";
	#endif
	SIZE_X = X; SIZE_Y = Y; SIZE_Z = Z;
	for (int r = 0; r < VectorDim; ++r) {
		ScalarField r_temp(SIZE_X, SIZE_Y, SIZE_Z);
		Field[r] = r_temp;
	}
	#ifdef DEBUGGING
		std::cout << "\tend of VectorField(int X, int Y, int Z)\n";
	#endif
}

VectorField::VectorField(int X, int Y, int Z, std::string FieldType) {
	#ifdef DEBUGGING
		std::cout << "\n\tfrom VectorField(int X, int Y, int Z, std::string FieldType)\n";
	#endif
	SIZE_X = X; SIZE_Y = Y; SIZE_Z = Z;
	for (int r = 0; r < VectorDim; ++r) {
		ScalarField r_temp(SIZE_X, SIZE_Y, SIZE_Z, FieldType);
		Field[r] = r_temp;
	}
	#ifdef DEBUGGING
		std::cout << "\tend of VectorField(int X, int Y, int Z, std::string FieldType)\n";
	#endif
}

VectorField::~VectorField() {
	std::cout << "\t~VectorField()\n";
}

//VectorField grad(const VectorField &f, float dx, float dy, float dz) {
//	VectorField temp_f(f.SIZE_X, f.SIZE_Y, f.SIZE_Z);
//}	

//VectorField div(const VectorField &f, float dx, float dy, float dz) {
//
//}

VectorField rot(const VectorField &f, float dx, float dy, float dz) {
	VectorField rot_f(f.SIZE_X, f.SIZE_Y, f.SIZE_Z);
	for (int i = 1; i < f.SIZE_X - 1; ++i)
		for(int j = 1; j < f.SIZE_Y - 1; ++j)
			for (int k = 1; k < f.SIZE_Z - 1; ++k) {
				rot_f[0](i, j, k) = (f[2](i, j+1, k) - f[2](i, j, k))/dy - (f[1](i, j, k+1) - f[1](i, j, k))/dz;
				rot_f[1](i, j, k) = (f[0](i, j, k+1) - f[0](i, j, k))/dz - (f[2](i+1, j, k) - f[2](i, j, k))/dx;
				rot_f[1](i, j, k) = (f[1](i+1, j, k) - f[1](i, j, k))/dz - (f[0](i, j+1, k) - f[0](i, j, k))/dx;
			}
	return rot_f;
}

ScalarField& ScalarField::operator = (const ScalarField &other) {
	std::cout << "\t\t    ScalarField& operator = (const ScalarField &other)\n";		
	if (sField != nullptr) {
		std::cout << "\t\t\tmem. deleted: " << sField << "\n";
		delete [] sField;
		sField = nullptr;
	} 

	SIZE_X = other.SIZE_X;
	SIZE_Y = other.SIZE_Y;
	SIZE_Z = other.SIZE_Z;
	sField = new float[SIZE_X * SIZE_Y * SIZE_Z];
	std::cout << "\t\t\tmem. allocated: " << sField << "\n";
	for (int i = 0; i < SIZE_X; ++i)
			for(int j = 0; j < SIZE_Y; ++j)
				for (int k = 0; k < SIZE_Z; ++k)
					sField[i*SIZE_Y*SIZE_Z + j*SIZE_Z + k] = other.sField[i*SIZE_Y*SIZE_Z + j*SIZE_Z + k];
	
	return *this;
}

float& ScalarField::operator() (int X, int Y, int Z) {
	return sField[X*SIZE_Y*SIZE_Z + Y*SIZE_Z + Z];
}
ScalarField& VectorField::operator[] (int r) { return Field[r]; } 

// to work with const ScalarField %Name
float ScalarField::operator() (int X, int Y, int Z) const {
	return sField[X*SIZE_Y*SIZE_Z + Y*SIZE_Z + Z];
}
ScalarField VectorField::operator[] (int r) const { return Field[r]; }

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

void ScalarField::PrintField(std::ostream &os) const {
	for (int i = 0; i < SIZE_X; ++i) {
		os << " x:" << i << "\n"; 
		for(int j = 0; j < SIZE_Y; ++j) {
			os << " y:" << j;
			for (int k = 0; k < SIZE_Z; ++k) {
				os << " z:" << k;		
				os << std::setprecision(4) << std::fixed 
				<<  std::setw(9) << sField[i*SIZE_Y*SIZE_Z + j*SIZE_Z + k] << " ";
			}
			os << "\n";
		}
		os << "\n";
	}
}