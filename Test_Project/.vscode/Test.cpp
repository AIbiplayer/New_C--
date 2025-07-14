#include <iostream>

class Vector
{
private:
    const char *Name_; // 向量名称
    int Dimension_;    // 向量维数
    double *Memory_;   // 向量数组

public:
    Vector(int Dimension, const char *Name) : Dimension_(Dimension), Name_(Name) // 手动赋值构造函数
    {
        if (Dimension_ == 0) // 判断向量是否为0
        {
            exit(1);
        }

        Memory_ = new double[Dimension_]; // 申请内存
        if (Memory_ == nullptr)           // 判断是否申请成功
        {
            std::cout << Name_ << " 创建失败！" << std::endl;
            exit(1);
        }
        std::cout << Name_ << " 创建成功！" << std::endl;
    }

    Vector(const Vector &other, const char *NewName) // 深拷贝构造函数
    {
        if (other.Dimension_ == 0) // 判断向量是否为0
        {
            exit(1);
        }

        this->Dimension_ = other.Dimension_;          // 维数复制
        this->Name_ = NewName;                        // 名称复制
        this->Memory_ = new double[this->Dimension_]; // 申请内存

        if (this->Memory_ == nullptr) // 判断是否申请成功
        {
            std::cout << this->Name_ << " 创建失败！" << std::endl;
            exit(1);
        }
        for (uint8_t i = 0; i < this->Dimension_; i++) // 向量值填入
        {
            this->Memory_[i] = other.Memory_[i];
        }

        std::cout << this->Name_ << " 拷贝成功！" << std::endl;
    }

    Vector operator+(const Vector &V1) // 向量相加函数
    {
        if (V1.Dimension_ != this->Dimension_)
        {
            std::cout << "向量相加失败，维数不统一！" << std::endl;
            exit(1);
        }
        Vector SumVector(3, "SumVector");
        for (uint8_t i = 0; i < this->Dimension_; i++)
        {
            SumVector.Memory_[i] = this->Memory_[i] + V1.Memory_[i];
        }
        return SumVector;
    }

    Vector operator-(const Vector &V1) // 向量相减函数
    {
        if (V1.Dimension_ != this->Dimension_)
        {
            std::cout << "向量相减失败，维数不统一！" << std::endl;
            exit(1);
        }
        Vector LessVector(3, "LessVector");
        for (uint8_t i = 0; i < this->Dimension_; i++)
        {
            LessVector.Memory_[i] = this->Memory_[i] - V1.Memory_[i];
        }
        return LessVector;
    }

    Vector operator*(const Vector &V1) // 向量点乘函数
    {
        if (V1.Dimension_ != this->Dimension_)
        {
            std::cout << "向量点乘失败，维数不统一！" << std::endl;
            exit(1);
        }
        Vector MulVector(3, "MulVector");
        for (uint8_t i = 0; i < this->Dimension_; i++)
        {
            MulVector.Memory_[i] = this->Memory_[i] * V1.Memory_[i];
        }
        return MulVector;
    }

    void operator=(const Vector &other) // 向量赋值（深拷贝）
    {
        if (this->Dimension_ != other.Dimension_)
        {
            std::cout << "赋值失败，维数不统一！" << std::endl;
        }

        for (uint8_t i = 0; i < this->Dimension_; i++)
        {
            this->Memory_[i] = other.Memory_[i];
        }
    }

    void Vector_Printf(void) // 打印向量
    {
        std::cout << this->Name_ << '[';
        for (uint8_t i = 0; i < this->Dimension_; i++) // 向量值填入
        {
            std::cout << this->Memory_[i] << "\t";
        }
        std::cout << ']' << std::endl;
    }

    const double operator[](int Number) const // 读取单个向量
    {
        if (Number >= this->Dimension_)
        {
            exit(1);
        }
        return this->Memory_[Number];
    }

    double &operator[](int Number) // 向量赋值
    {
        if (Number >= this->Dimension_)
        {
            exit(1);
        }
        return this->Memory_[Number];
    }

    ~Vector() // 析构函数清空内存
    {
        delete[] (this->Memory_);
        this->Memory_ = nullptr;
    }
};

int main(void)
{
    Vector Vector1(3, "Vector1");
    Vector1[0] = 1.1;
    Vector1[1] = 3.2;
    Vector1[2] = 4.1;
    Vector1.Vector_Printf();

    Vector Vector2(Vector1, "Vector2");
    Vector2.Vector_Printf();

    Vector SumVector(3, "SumVector");
    SumVector = Vector1 + Vector2;
    SumVector.Vector_Printf();

    Vector LessVector(3, "LessVector");
    LessVector = Vector1 - Vector2;
    LessVector.Vector_Printf();

    Vector MulVector(3, "MulVector");
    MulVector = Vector1 * Vector2;
    MulVector.Vector_Printf();
}
