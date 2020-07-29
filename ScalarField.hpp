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