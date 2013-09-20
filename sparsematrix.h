#include <map>
#include <cstdlib>
#include <cstdio>
using namespace std;

class SparseMatrix
{
public:
	typedef map<long, double> row; //Rowmap
	typedef map<long, row> SMatrix; //mappy
	SMatrix SMMatrix; //mmap

	long col_count;
	long row_count;
	long longest_column;
	long num_elements;
	bool is_null;
	bool equal;


	SparseMatrix();
	SparseMatrix(const SparseMatrix &copy);
	SparseMatrix(long rows, long columns);
	SparseMatrix(std::string str);
	~SparseMatrix();

	long rowCount() const;
	long colCount() const;
	bool isSquare() const;
	bool isNull() const;

	double determinant() const;
	SparseMatrix minor(int row, int col)  const;

	SparseMatrix transpose() const;

	SparseMatrix operator+(const SparseMatrix &b) const;
	SparseMatrix operator-(const SparseMatrix &b) const;
	SparseMatrix operator*(const SparseMatrix &b) const;
	SparseMatrix operator*(const double &b) const;
	bool operator==(const SparseMatrix &b) const;

	SparseMatrix &operator=(const SparseMatrix &b);
	double operator()(long row, long col) const;
	void set(long row, long col, double value);
	std::string str() const;
};


class InvalidMatrixSize : public std::exception
{
public:
	InvalidMatrixSize() : std::exception() {}
	InvalidMatrixSize(const std::string &errorMessage) :
	std::exception(errorMessage.c_str()) {}
};
