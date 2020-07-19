class Matrix{
public:
    int m;
    int n;
    class Row {
    private:
        Matrix *matrix;
        int i;
    public:
        Row(Matrix *matrix, int i);
        int& operator [] (int j);
    };

    Matrix::Row operator[] (int i) {
        return Row(this,i);
    }
};