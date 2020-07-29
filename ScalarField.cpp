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