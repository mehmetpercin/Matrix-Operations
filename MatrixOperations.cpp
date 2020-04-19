#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <cmath>

using namespace std;

template <typename T>
class Matrix
{
    public:
        Matrix();
        Matrix(int rowSize,int  columnSize,T value);
        Matrix(int rowSize,int columnSize,char value);
        void matrixResize(int newRow,int newColumn);
        void print()const;
        void print(const string fileName)const;
        Matrix operator+(const Matrix& matrixIn)const;
        Matrix operator-(const Matrix& matrixIn)const;
        Matrix operator*(const Matrix& matrixIn)const;
        Matrix operator+(const T scalarIn)const;
        Matrix operator-(const T scalarIn)const;
        Matrix operator*(const T scalarIn)const;
        Matrix operator/(const T scalarIn)const;
        Matrix operator%(const T scalarIn)const;
        Matrix operator^(const T scalarIn)const;
        Matrix transpose();
        Matrix emul(const Matrix& matrixIn);
        void inverse();
        T det();
        virtual ~Matrix();

    protected:
        int rows;
        int columns;
        T** matrix;
    private:
        T setDeterminant(const Matrix& matrixIn,int matrixSize);
};

template<typename T>
Matrix<T>::Matrix(){
    this->rows = 10;
    this->columns = 10;

    this->matrix = new T *[rows];
    for(int i = 0; i < this->rows; i++)
        this->matrix[i] = new T[this->columns];
}

template<typename T>
Matrix<T>::Matrix(int rowSize,int columnSize,T value){
    this->rows = rowSize;
    this->columns = columnSize;

    this->matrix = new T *[this->rows];
    for(int i = 0; i < this->rows; i++)
        this->matrix[i]=new T[this->columns];

    for(int i=0;i<this->rows;i++){
        for(int j=0;j<this->columns;j++){
            this->matrix[i][j]=value;
        }
    }
}

template<typename T>
Matrix<T>::Matrix(int rowSize,int columnSize,char value){
    if(value=='e'){
        this->rows = rowSize;
        this->columns = columnSize;

        this->matrix = new T *[this->rows];
        for(int i = 0; i < this->rows; i++)
            this->matrix[i]=new T[this->columns];

        for(int i=0;i<this->rows;i++){
            for(int j=0;j<this->columns;j++){
                if(i==j)
                    this->matrix[i][j]=1;
            }
        }
    }
    else if(value=='r'){
        this->rows = rowSize;
        this->columns = columnSize;

        this->matrix = new T *[rows];
        for(int i = 0; i < this->rows; i++)
            this->matrix[i]=new T[this->columns];

        for(int i=0;i<this->rows;i++){
            for(int j=0;j<this->columns;j++){
                this->matrix[i][j]=rand()%256;
            }
        }
    }
    else{
        cout<<"Lutfen Gecerli 'e' veya 'r' Parametrelerinden Birini Giriniz!!"<<endl;
    }
}

template<typename T>
void Matrix<T>::matrixResize(int newRowIndex,int newColumnIndex){
    if((this->matrix[0][0] == this->matrix[1][0]) && (this->matrix[0][1] == this->matrix[1][1])){//tüm elemanlar aynı ise
        T value=this->matrix[1][1];
        this->rows = newRowIndex;
        this->columns = newColumnIndex;

        this->matrix = new T *[this->rows];
        for(int i = 0; i < this->rows; i++)
            this->matrix[i]=new T[this->columns];

        for(int i=0;i<this->rows;i++){
            for(int j=0;j<this->columns;j++){
                this->matrix[i][j]=value;
            }
        }
    }
    else if(this->matrix[0][0] != this->matrix[0][1] != this->matrix[1][1] !=this->matrix[1][0]){//random olma durumu
        this->rows = newRowIndex;
        this->columns = newColumnIndex;

        this->matrix = new T *[this->rows];
        for(int i = 0; i < this->rows; i++)
            this->matrix[i]=new T[this->rows];

        for(int i=0;i<this->rows;i++){
            for(int j=0;j<this->columns;j++){
                this->matrix[i][j]=rand()%256;
            }
        }
    }
    else if(this->matrix[0][0]==1 && this->matrix[1][0]==0 && this->matrix[0][1]==0 && this->matrix[1][1]==1){//birim matris olma durumu
        this->rows = newRowIndex;
        this->columns = newColumnIndex;

        this->matrix = new T *[this->rows];
        for(int i = 0; i < this->rows; i++)
           this-> matrix[i]=new T[this->columns];

        for(int i=0;i<this->rows;i++){
            for(int j=0;j<this->columns;j++){
                if(i==j)
                    this->matrix[i][j]=1;
            }
        }
    }
}

template<typename T>
void Matrix<T>::print()const{
    for(int i=0;i<this->rows;i++){
        for(int j=0;j<this->columns;j++){
            cout<<this->matrix[i][j]<<" ";
        }
        cout<<"\n";
    }
}

template<typename T>
void Matrix<T>::print(const string fileName)const{
    ofstream writingFile;
    writingFile.open(fileName.c_str());
    for(int i=0;i<this->rows;i++){
        for(int j=0;j<this->columns;j++){
            writingFile<<this->matrix[i][j]<<" ";
        }
        writingFile<<"\n";
    }
    writingFile.close();
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& matrixIn)const{
    if(this->columns == matrixIn.columns && this->rows == matrixIn.rows){
        Matrix<T> outMatrix(this->rows,this->columns,'r');
        for(int i=0;i < this->rows; i++ ){
            for(int j=0;j < this->columns; j++){
                outMatrix.matrix[i][j] = this->matrix[i][j] + matrixIn.matrix[i][j];
            }
        }
        return outMatrix;
    }
    else{
        return *this;
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& matrixIn)const{
    if(this->columns == matrixIn.columns && this->rows == matrixIn.rows){
        Matrix<T> outMatrix(this->rows,this->columns,'r');
        for(int i=0;i < this->rows; i++ ){
            for(int j=0;j < this->columns; j++){
                outMatrix.matrix[i][j] = this->matrix[i][j] - matrixIn.matrix[i][j];
            }
        }
        return outMatrix;
    }
    else{
        return *this;
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& matrixIn)const{
    if(this->columns == matrixIn.columns && this->rows == matrixIn.rows){
        Matrix<T> outMatrix(this->rows,this->columns,'r');
        for(int i=0;i < this->rows; i++ ){
            for(int j=0;j < this->columns; j++){
                outMatrix.matrix[i][j] = this->matrix[i][j] * matrixIn.matrix[i][j];
            }
        }
        return outMatrix;
    }
    else{
        return *this;
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const T scalarIn)const{
    Matrix<T> outMatrix(this->rows,this->columns,'r');
    for(int i=0;i < this->rows; i++ ){
        for(int j=0;j < this->columns; j++){
            outMatrix.matrix[i][j] = this->matrix[i][j] + scalarIn;
        }
    }
    return outMatrix;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const T scalarIn)const{
    Matrix<T> outMatrix(this->rows,this->columns,'r');
    for(int i=0;i < this->rows; i++ ){
        for(int j=0;j < this->columns; j++){
            outMatrix.matrix[i][j] = this->matrix[i][j] - scalarIn;
        }
    }
    return outMatrix;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T scalarIn)const{
    Matrix<T> outMatrix(this->rows,this->columns,'r');
    for(int i=0;i < this->rows; i++ ){
        for(int j=0;j < this->columns; j++){
            outMatrix.matrix[i][j] = this->matrix[i][j] * scalarIn;
        }
    }
    return outMatrix;
}


template<typename T>
Matrix<T> Matrix<T>::operator/(const T scalarIn)const{
    Matrix<T> outMatrix(this->rows,this->columns,'r');
    for(int i=0;i < this->rows; i++ ){
        for(int j=0;j < this->columns; j++){
            outMatrix.matrix[i][j] = this->matrix[i][j] / scalarIn;
        }
    }
    return outMatrix;
}

template<typename T>
Matrix<T> Matrix<T>::operator%(const T scalarIn)const{
    Matrix<T> outMatrix(this->rows,this->columns,'r');
    for(int i=0;i < this->rows; i++ ){
        for(int j=0;j < this->columns; j++){
            outMatrix.matrix[i][j]=fmod(this->matrix[i][j],scalarIn);
        }
    }
    return outMatrix;
}

template<typename T>
Matrix<T> Matrix<T>::operator^(const T scalarIn)const{
    Matrix<T> outMatrix(this->rows,this->columns,'r');
    for(int i=0;i < this->rows; i++ ){
        for(int j=0;j < this->columns; j++){
            outMatrix.matrix[i][j] = pow(this->matrix[i][j],scalarIn);
        }
    }
    return outMatrix;
}

template<typename T>
Matrix<T> Matrix<T>::transpose(){
	Matrix<T> temp(this->columns,this->rows,'r');
        for(int i=0;i<this->rows;i++) {
            for(int j=0;j<this->columns;j++) {
                temp.matrix[j][i] = this->matrix[i][j];
            }
        }
        return temp;
}

template<typename T>
Matrix<T> Matrix<T>::emul(const Matrix<T>& matrixIn){
    Matrix<T> tempMatrix(this->rows,matrixIn.columns,'r');
    if(this->columns==matrixIn.rows){
        for(int i=0;i < this->rows;i++){
            for(int j=0;j < matrixIn.columns;j++){
                tempMatrix.matrix[i][j]=0;
                for(int k=0;k < matrixIn.rows;k++){
                    tempMatrix.matrix[i][j] += this->matrix[i][k] * matrixIn.matrix[k][j];
                }
            }
        }
        return tempMatrix;
    }

    else{
        cout<<"Bu Matrislerin Carpimi Yapilamaz!!"<<endl;
        return *this;
    }
}

template<typename T>
T Matrix<T>::setDeterminant(const Matrix<T>& matrixIn,int n){//n:matris boyutu
    if(matrixIn.rows==matrixIn.columns){
        T determinant=0;
        Matrix<T> tempMatrix(10,10,'r');//2'nin üstünde bir sayı olması için rastgele boyunladırıldı
        if (n == 2){
            return (matrixIn.matrix[0][0] * matrixIn.matrix[1][1]) - (matrixIn.matrix[1][0] * matrixIn.matrix[0][1]);
        }
        else{
            for(int x = 0; x < n; x++) {
                int tempI = 0;
                for (int i = 1; i < n; i++) {
                   int tempJ = 0;
                   for(int j = 0; j < n; j++) {
                      if(j == x)
                        continue;
                      tempMatrix.matrix[tempI][tempJ] = matrixIn.matrix[i][j];
                      tempJ++;
                   }
                   tempI++;
                }
                determinant = determinant + (pow(-1, x) * matrixIn.matrix[0][x] * setDeterminant( tempMatrix, n - 1 ));
          }
            return determinant;
        }
    }
    else{
        cout<<"Lutfen Kare Matris Giriniz!"<<endl;
        return 0;
    }
}

template<typename T>
T Matrix<T>::det(){
    T result=this->setDeterminant(*this,this->rows);
    return result;

}

template<typename T>
void Matrix<T>::inverse(){//inverse fonksiyonunda sonuçların double çıkması için main.cpp'de Matrix sınıfı double olarak oluşturulmalıdır
    Matrix<T> tempMatrix(this->rows,this->columns,'e');//gauss-jordan yönteminde sağ kısım için birim matris
    double d;//diagon-köşegen elemanları
    double k;//satırdaki köşegen elemanları
    for(int i=0;i<this->rows;i++){
        d=this->matrix[i][i];
        for(int j=0;j<this->columns;j++){
            this->matrix[i][j]=this->matrix[i][j]/d;
            tempMatrix.matrix[i][j]=tempMatrix.matrix[i][j]/d;
        }
        for(int x=0;x<this->rows;x++){
            if(x!=i){
                k=this->matrix[x][i];
                for(int j=0;j<this->columns;j++){
                    this->matrix[x][j]=this->matrix[x][j]-(this->matrix[i][j]*k);
                    tempMatrix.matrix[x][j]=tempMatrix.matrix[x][j]-(tempMatrix.matrix[i][j]*k);
                }
           }
        }
    }

    for(int i=0;i<this->rows;i++){
        for(int j=0;j<this->columns;j++){
            this->matrix[i][j]=tempMatrix.matrix[i][j];
        }
    }
}

template<typename T>
Matrix<T>::~Matrix(){

}

template <typename T>
class Table : public Matrix<T>
{
    public:
        Table();
        Table(int rowSize,int columnSize,T value);
        Table(int rowSize,int columnSize,char value);
        int itemAt(int rowIndex,int columnIndex);
        int itemAt(string index);
        int itemAt(string rowIndex,string columnIndex);
        void setRowNames(string s[],int n);
        void setColumnNames(string s[],int n);
        void print();
        virtual ~Table();

    protected:

    private:
        string rowNames[24]={"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23"};
        string columnNames[23]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","R","S","T","U","V","Y","Z"};

};

template <typename T>
Table<T>::Table():Matrix<T>(){
}

template <typename T>
Table<T>::Table(int rowSize,int columnSize,T value):Matrix<T>(rowSize,columnSize,value){
}

template <typename T>
Table<T>::Table(int rowSize,int columnSize,char value):Matrix<T>(rowSize,columnSize,value){
}

template<typename T>
int Table<T>::itemAt(int rowIndex,int columnIndex){
    if((rowIndex < 1 || rowIndex > this->rows) || (columnIndex < 1 || columnIndex > this->columns)){
        cout<<"Lutfen Gecerli Bir Index Giriniz!!";
        return 0;
    }
    else
        return this->matrix[rowIndex-1][columnIndex-1];
}

template<typename T>
int Table<T>::itemAt(string rowIndex,string columnIndex){
    int temp_row,temp_column;
    for(int i=0;i<this->rows;i++){
        if(rowIndex==rowNames[i])
            temp_row=i;
    }
    for(int i=0;i<this->columns;i++){
        if(columnIndex==columnNames[i])
            temp_column=i;
    }
    return this->matrix[temp_row][temp_column];

}

template<typename T>
int Table<T>::itemAt(string index){
    string row=string(1,index[1]);
    string column=string(1,index[0]);

    int temp_row,temp_column;
    for(int i=0;i<this->rows;i++){
        if(row==rowNames[i])
            temp_row=i;
    }
    for(int i=0;i<this->columns;i++){
        if(column==columnNames[i])
            temp_column=i;
    }
    return this->matrix[temp_row][temp_column];
}

template<typename T>
void Table<T>::print(){
    cout<<"  ";
    for(int i=0;i<this->columns;i++)
        cout<<columnNames[i]<<" ";
    cout<<"\n";
    for(int i=0;i<this->rows;i++){
        cout<<rowNames[i]<<" ";
        for(int j=0;j<this->columns;j++){
            cout<<this->matrix[i][j]<<" ";
        }
        cout<<"\n";
    }
}

template<typename T>
void Table<T>::setRowNames(string s[],int n){
    for(int i=0;i<n;i++){
        rowNames[i]=s[i];
    }
}

template<typename T>
void Table<T>::setColumnNames(string s[],int n){
    for(int i=0;i<n;i++){
        columnNames[i]=s[i];
    }
}

template<typename T>
Table<T>::~Table(){

}

int main()
{

    return 0;
}
