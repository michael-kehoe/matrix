#include "sparsematrix.h"
#include <vector>
#include <map>
#include <iostream>
#include <cstdlib>
#include <iomanip> 
#include <sstream>


#pragma region Contructs
#pragma region BasicConstructs
SparseMatrix::SparseMatrix()
	{
		this->row_count = 0;
		this->col_count = 0;
		this->longest_column = 0;
		this->is_null = true;
		this->num_elements = 0;
	}
SparseMatrix::SparseMatrix(long rows, long columns)
	{
		this->is_null = true;
		if( rows >= 0 && columns >= 0)
			{
				this->row_count = rows;
				this->col_count = columns;
				this->longest_column = columns;
				this->is_null = true;
				this->num_elements = 0;
			}
	}
SparseMatrix::SparseMatrix(const SparseMatrix &copy)
	{
		this->row_count= copy.row_count;
		this->col_count = copy.col_count;
		this->longest_column = copy.longest_column;
		this->is_null = copy.is_null;
		this->SMMatrix = copy.SMMatrix;
		this->num_elements = copy.num_elements;
	}
SparseMatrix::~SparseMatrix()
	{

	}
#pragma endregion BasicConstructs

#pragma region StringConstruct
SparseMatrix::SparseMatrix(std::string str)
	{
		this->row_count = 0;
		this->col_count = 0;
		this->longest_column = 0;
		this->is_null = true;
		this->num_elements = 0;
		row tempColumn;
		std::string temp = "";
		bool invalid = false;
		bool entered = false;

		#pragma region Test_invalid
		for(unsigned int i = 0 ; i < str.length() ; i++)
			{
				if((str[i] == '1')||(str[i] != '2')||(str[i] != '3')||(str[i] != '4')||(str[i] != '5')||(str[i] != '6')||(str[i] != '7')||(str[i] != '8')||(str[i] != '9')||(str[i] != '0'))
					{
						entered = true;	
					}

				if((str[i] != '1')&&(str[i] != '2')&&(str[i] != '3')&&(str[i] != '4')&&(str[i] != '5')&&(str[i] != '6')&&(str[i] != '7')&&(str[i] != '8')&&(str[i] != '9')&&(str[i] != '0')&&(str[i] != ';')&&(str[i] != ' ')&&(str[i] != '-'))
					{
						invalid = true;
						this->is_null = true;
						break;
					}
				else if(str[0] == ' ')
					{
						invalid = true;
						this->is_null = true;
						break;
					}
				else if(str[str.length()-1] == ' ')
					{
						invalid = true;
						this->is_null = true;
						break;
					}
				else if(str[i] == ';' && i > 0)
					{
						if(str[i-1] != ' ')
						{
							invalid = true;	
							this->is_null = true;
							break;
						}
					}
				else if(str[0] == ';' && str[1] == ' ' && str[2] == ';' )
					{
						invalid = true;	
						this->is_null = true;
						break;
					}
				else 
					{
						invalid = false;
					}
			}
		#pragma endregion Test_invalid
		#pragma region build_matrix
		if(invalid==false) //If no problems, build the matrix
			{
				this->row_count = 0;
				this->col_count = 0;
				this->longest_column = 0;
				for(unsigned int i = 0 ; i < str.length() ; i++)
					{	
						if(str[i] != ' ' && str[i] != ';') //Normal element
							{
								temp += str[i];
								//cout << "New Digit: " << temp << "\n";
							}
						if(str[i] == ' ') //Space between numbers, new column
							{	
								if(temp.length() > 0)
									{
										//cout << "Ready to Add: " << temp << "\n";							
										tempColumn.insert(pair<long, double>(col_count, atof(temp.c_str())));
										num_elements++;
										col_count += 1;
										temp.clear();
										if(col_count > this->longest_column)
											{
												longest_column = col_count;
											}
									}	
							}
						if(str.length()-1 == i)  //End of string //new column, add row
							{
								//cout << "Reached end of string, add this: " << temp << " @row: " << row_count << "\n";
								if(temp.length() > 0)
									{
										//cout << "inside \n";
										tempColumn.insert(pair<long, double>(col_count, atof(temp.c_str())));
										num_elements++;
										SMMatrix.insert(pair<long, row>(row_count, tempColumn));
										//cout << this->str() << "\n";
										temp.clear();
										tempColumn.clear();
										entered = true;
									}
								col_count += 1;
								if(col_count > longest_column)
									{
										longest_column = col_count;
									}
								col_count = 0;
								row_count += 1;
							}
						if(str[i] == ';') 
							{
								//cout << "End of row:" << row_count <<  "\n";
								//if(temp.length() > 0)
									//{
										//cout << "Hello";
										//tempColumn.insert(pair<long, double>(col_count, atof(temp.c_str())));
										//num_elements++;
										SMMatrix.insert(pair<long, row>(row_count, tempColumn));
										temp.clear();
										tempColumn.clear();
										//cout << this->str() << "\n";
										entered = true;
									//}
								
								if(col_count > longest_column)
									{
										longest_column = col_count;
									}
								col_count = 0;
								row_count += 1;
							}
					}

				col_count = longest_column;
				this->is_null = false;
			}
		else 
			{
				this->is_null = true;
			}
		#pragma endregion build_matrix
	}
#pragma endregion StringConstruct
#pragma endregion Constructs

#pragma region Operators
#pragma region Operator()
double SparseMatrix::operator()(long row, long col) const
	{
		if(((row >= 0) && (row < this->rowCount())) && ((col >= 0) && (col < this->colCount())))
		{
			SparseMatrix NewMatrix(*this);
			NewMatrix.SMMatrix[row][col];
			return NewMatrix.SMMatrix[row][col];
		}
	else
		{
			throw InvalidMatrixSize();
		}
	}
#pragma endregion Operator() 
#pragma region =
SparseMatrix &SparseMatrix::operator=(const SparseMatrix &b)
	{
		this->row_count= b.row_count;
		this->col_count = b.col_count;
		this->longest_column = b.longest_column;
		this->is_null = b.is_null;
		this->SMMatrix = b.SMMatrix;
		this->num_elements = b.num_elements;
		return(*this);
	}
#pragma endregion ==

#pragma region ==
bool SparseMatrix::operator==(const SparseMatrix &b) const
	{
		if ((this->colCount() == b.colCount())&&(this->rowCount() == b.rowCount()))
			{
				SMatrix::const_iterator row_it;
				row::const_iterator col_it;
				for (row_it = this->SMMatrix.begin(); row_it != this->SMMatrix.end(); row_it++)
					{
						long current_row = row_it->first;
						row current_row_map = row_it->second;  
						for (col_it = current_row_map.begin(); col_it != current_row_map.end(); col_it++)
							{
								long current_col = col_it->first;
								double current_row_col_value = col_it->second;
								if ((*this)(current_row,current_col) != b(current_row,current_col))
									{
										return false;
									}
							
							}
					}
		for (row_it = b.SMMatrix.begin(); row_it != b.SMMatrix.end(); row_it++)
			{
				long current_row = row_it->first;
				row current_row_map = row_it->second;  
				for (col_it = current_row_map.begin(); col_it != current_row_map.end(); col_it++)
					{
						long current_col = col_it->first;
						double current_row_col_value = col_it->second;
						if ((*this)(current_row,current_col) != b(current_row,current_col))
							{
								return false;
							}
						
					}	
			}
		return true;
	}
	else 
	{
		return false;
	}
}
#pragma endregion ==

#pragma region plus
SparseMatrix SparseMatrix::operator+(const SparseMatrix &b) const
{
	SparseMatrix OriginalMatrix(*this);
	if ((this->colCount() == b.colCount())&&(this->rowCount() == b.rowCount()))
			{
				SparseMatrix NewMatrix(this->rowCount(),this->colCount());
				SMatrix::const_iterator row_it;
				row::const_iterator col_it;
				for (row_it = this->SMMatrix.begin(); row_it != this->SMMatrix.end(); row_it++)
					{
						long current_row = row_it->first;
						row current_row_map = row_it->second;  
						for (col_it = current_row_map.begin(); col_it != current_row_map.end(); col_it++)
							{
								long current_col = col_it->first;
								double current_row_col_value = col_it->second;
								NewMatrix.set(current_row,current_col,current_row_col_value); 
							}
					}
				for (row_it = b.SMMatrix.begin(); row_it != b.SMMatrix.end(); row_it++)
					{
						long current_row = row_it->first;
						row current_row_map = row_it->second;  
						for (col_it = current_row_map.begin(); col_it != current_row_map.end(); col_it++)
							{
								long current_col = col_it->first;
								double current_row_col_value = col_it->second;
								NewMatrix.set(current_row,current_col,current_row_col_value+NewMatrix(current_row,current_col)); 
		
							}	
					}
				return NewMatrix;
			}
	else 
	{
		throw InvalidMatrixSize();
		return OriginalMatrix;
	
	}

}
#pragma endregion plus

#pragma region minus
SparseMatrix SparseMatrix::operator-(const SparseMatrix &b) const
{
	SparseMatrix OriginalMatrix(*this);
	if ((this->colCount() == b.colCount())&&(this->rowCount() == b.rowCount()))
			{
				SparseMatrix NewMatrix(this->rowCount(),this->colCount());
				SMatrix::const_iterator row_it;
				row::const_iterator col_it;
				for (row_it = this->SMMatrix.begin(); row_it != this->SMMatrix.end(); row_it++)
					{
						long current_row = row_it->first;
						row current_row_map = row_it->second;  
						for (col_it = current_row_map.begin(); col_it != current_row_map.end(); col_it++)
							{
								long current_col = col_it->first;
								double current_row_col_value = col_it->second;
								NewMatrix.set(current_row,current_col,current_row_col_value); 
							}
					}
				for (row_it = b.SMMatrix.begin(); row_it != b.SMMatrix.end(); row_it++)
					{
						long current_row = row_it->first;
						row current_row_map = row_it->second;  
						for (col_it = current_row_map.begin(); col_it != current_row_map.end(); col_it++)
							{
								long current_col = col_it->first;
								double current_row_col_value = col_it->second;
								NewMatrix.set(current_row,current_col,NewMatrix(current_row,current_col)-current_row_col_value); 
							}	
					}
				return NewMatrix;
			}
	else 
	{
		throw InvalidMatrixSize();
		return OriginalMatrix;
	}
}
#pragma endregion minus

#pragma region *b
SparseMatrix SparseMatrix::operator*(const double &b) const
{
				SparseMatrix OriginalMatrix(*this);
				SMatrix::const_iterator row_it;
				row::const_iterator col_it;
				for (row_it = this->SMMatrix.begin(); row_it != this->SMMatrix.end(); row_it++)
					{
						long current_row = row_it->first;
						row current_row_map = row_it->second;  
						for (col_it = current_row_map.begin(); col_it != current_row_map.end(); col_it++)
							{
								long current_col = col_it->first;
								double current_row_col_value = col_it->second;
								OriginalMatrix.set(current_row,current_col,OriginalMatrix(current_row,current_col)*b); 
							}
					}
				return OriginalMatrix;
			
	
	
	}
#pragma endregion *b

#pragma region *sm

SparseMatrix SparseMatrix::operator*(const SparseMatrix &b) const
{
	SparseMatrix temp =b;
	SparseMatrix OriginalMatrix(*this);
	SparseMatrix ResultMatrix(this->rowCount(), b.colCount());
	if (this->colCount() == b.rowCount())
			{

				SMatrix::const_iterator row_itA;
				row::const_iterator col_itA;
				for (row_itA = this->SMMatrix.begin(); row_itA != this->SMMatrix.end(); row_itA++)
					{
						long current_rowA = row_itA->first;
						row current_row_mapA = row_itA->second;  
						for (col_itA = current_row_mapA.begin(); col_itA != current_row_mapA.end(); col_itA++)
							{
								long current_colA = col_itA->first;
								double current_row_col_valueA = col_itA->second;

								//cout << "value @ Matrix A in position: " << current_rowA << "," << current_colA << "= "  <<current_row_col_valueA << "\n";
								SMatrix::const_iterator row_itB;
								row::const_iterator col_itB;
								row current_row_mapB = temp.SMMatrix[current_colA];
								for (col_itB = current_row_mapB.begin(); col_itB != current_row_mapB.end(); col_itB++)
								{
									long current_colB = col_itB->first;
									double current_row_col_valueB = col_itB->second;
									ResultMatrix.set(current_rowA,current_colB, ResultMatrix(current_rowA,current_colB)+current_row_col_valueB *current_row_col_valueA);

								}

								
							}
							
					}
				return ResultMatrix;
		}
	else
	{
		throw InvalidMatrixSize();
		return OriginalMatrix;
	}
}
#pragma endregion *sm

#pragma endregion Operators

#pragma region Functions
long SparseMatrix::rowCount() const
	{
		return this->row_count;
	}
long SparseMatrix::colCount() const
	{
		return this->col_count;
	}
bool SparseMatrix::isSquare() const
	{
		if(((this->colCount() > 0) && (this->rowCount() > 0)) && this->colCount() == this->rowCount())
			{
				return true;
			}
		else return false;
	}
bool SparseMatrix::isNull() const
	{
		if(this->SMMatrix.size() == 0)
			{
				return true;
			}
		else return false;
	}
#pragma endregion Functions

#pragma region Other

void SparseMatrix::set(long row, long col, double value)
	{
		if(row < this->row_count && col < this->col_count && row >= 0 && col >= 0)
			{
				SMMatrix[row][col] = value;
			}
		else
			{
				throw InvalidMatrixSize();
			}
	}
std::string SparseMatrix::str() const
	{
		string result;
		SparseMatrix NewMatrix(*this);
		for(long i=0; i < this->rowCount();i++)//over rows
			{
				for(long j=0; j < this->longest_column; j++)//over vals
					{
						std::ostringstream out; 
						out << NewMatrix.SMMatrix[i][j]; 
						result.append(out.str()+ " ");
					}
				result.append("; ");
			}
		if (result.length() > 0) 
			{
				result.erase(result.end() - 1);
				result.erase(result.end() - 1);
				result.erase(result.end() - 1);
			}
		return result;
	}


SparseMatrix SparseMatrix::transpose() const
{
				SparseMatrix OriginalMatrix((*this).colCount(), (*this).rowCount());
				SMatrix::const_iterator row_it;
				row::const_iterator col_it;
				for (row_it = (*this).SMMatrix.begin(); row_it != (*this).SMMatrix.end(); row_it++)
					{
						long current_row = row_it->first;
						row current_row_map = row_it->second;  
						for (col_it = current_row_map.begin(); col_it != current_row_map.end(); col_it++)
							{
								long current_col = col_it->first;
								double current_row_col_value = col_it->second;
								OriginalMatrix.set(current_col,current_row,current_row_col_value); 
							}
					}
				return OriginalMatrix;
}

double SparseMatrix::determinant() const
{
	SparseMatrix copy(*this);
	double d = 0;
	long rows = this->rowCount();
	long cols = this->colCount();
	if(this->colCount() == this->rowCount())
		{
			if(this->isNull() == true)
				{
					throw InvalidMatrixSize();
				
				}
			else
				{
					#pragma region large_sparse_matrix
					if(this->SMMatrix.size() < this->rowCount() || this->transpose().SMMatrix.size() < this->rowCount())
						{
							return 0;
						}
					#pragma endregion large_sparse_matrix
					if (this->rowCount() == 1)
						{
							d+= copy(0,0);
						}
					else if (this->rowCount() == 2)  
						{
							d+= copy(0, 0) * copy(1, 1) - copy(1, 0) * copy(0, 1);
						}	
					else if (this->rowCount() == 3) 
						{
							d+=  (copy(0, 0) *((copy(1, 1)*copy(2, 2))-(copy(1, 2)*copy(2, 1))))- \
									(copy(0, 1) *((copy(1, 0)*copy(2, 2))-(copy(1, 2)*copy(2, 0))))+ \
									(copy(0, 2) *((copy(1, 0)*copy(2, 1))-(copy(1, 1)*copy(2, 0))));
						}
					else if (this->rowCount()== 4) 
					{
						d +=    copy(0,3) * copy(1,2) * copy(2,1) * copy(3,0) - copy(0,2) * copy(1,3) * copy(2,1) * copy(3,0)-
								copy(0,3) * copy(1,1) * copy(2,2) * copy(3,0)+copy(0,1) * copy(1,3) * copy(2,2) * copy(3,0)+
								copy(0,2) * copy(1,1) * copy(2,3) * copy(3,0)-copy(0,1) * copy(1,2) * copy(2,3) * copy(3,0)-
								copy(0,3) * copy(1,2) * copy(2,0) * copy(3,1)+copy(0,2) * copy(1,3) * copy(2,0) * copy(3,1)+
								copy(0,3) * copy(1,0) * copy(2,2) * copy(3,1)-copy(0,0) * copy(1,3) * copy(2,2) * copy(3,1)-
								copy(0,2) * copy(1,0) * copy(2,3) * copy(3,1)+copy(0,0) * copy(1,2) * copy(2,3) * copy(3,1)+
								copy(0,3) * copy(1,1) * copy(2,0) * copy(3,2)-copy(0,1) * copy(1,3) * copy(2,0) * copy(3,2)-
								copy(0,3) * copy(1,0) * copy(2,1) * copy(3,2)+copy(0,0) * copy(1,3) * copy(2,1) * copy(3,2)+
								copy(0,1) * copy(1,0) * copy(2,3) * copy(3,2)-copy(0,0) * copy(1,1) * copy(2,3) * copy(3,2)-
								copy(0,2) * copy(1,1) * copy(2,0) * copy(3,3)+copy(0,1) * copy(1,2) * copy(2,0) * copy(3,3)+
								copy(0,2) * copy(1,0) * copy(2,1) * copy(3,3)-copy(0,0) * copy(1,2) * copy(2,1) * copy(3,3)-
								copy(0,1) * copy(1,0) * copy(2,2) * copy(3,3)+copy(0,0) * copy(1,1) * copy(2,2) * copy(3,3);
					}
					else if (this->rowCount()== 5) 
						{  
							d += (copy(0,0)*this->minor(0,0).determinant()) - (copy(0,1)*this->minor(0,1).determinant()) + (copy(0,2)*this->minor(0,2).determinant()) - (copy(0,3)*this->minor(0,3).determinant()) + (copy(0,4)*this->minor(0,4).determinant());
							
						}  
					else {
					
							return 0;
					}

				}
		}
	else 
		{
			throw InvalidMatrixSize();
		}
	return d;
}
SparseMatrix SparseMatrix::minor(int row, int col)  const
    {  
         //printf("minor(row=%i, col=%i), rows=%i, cols=%i\n", row, col, rows, cols);  
        SparseMatrix copy(*this);  
		SparseMatrix result(this->rowCount()-1, this->colCount()-1);  
		
		
		for(int a = 0; a  < 5; a++)
			{
				for(int b = 0; b  < 5; b++)
					{
						if(a < row && b < col)
							{
								result.set(a,b,copy(a,b));
							}
						else if(a < row && b > col)
							{
								result.set(a,b-1,copy(a,b));
							}
						else if(a > row && b < col)
							{
								result.set(a-1,b,copy(a,b));
							}
						else if(a > row && b > col)
							{
								result.set(a-1,b-1,copy(a,b));
							}

					}

			}

				
			
		
			
			
			

   return result;

     }  
#pragma endregion Other
