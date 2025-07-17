#include <iostream>
#include <math.h>

class Shape // 抽象类，表示几何形状
{
public:
    Shape(double a, double b, int Angle) : a_(a), b_(b), Angle_(Angle) { Count++; }; // 构造函数，接受两条边和一个角度
    Shape(double a, double b, double c) : a_(a), b_(b), c_(c) { Count++; };          // 构造函数，接受三条边
    // 构造函数，接受曲线的起始点和结束点以及曲线函数指针
    Shape(double x1, double x2, double y1, double (*Curve_Func)(double)) : a_(x1), b_(x2), c_(y1), Curve_Func_(Curve_Func) { Count++; };

    virtual double Area(void) const = 0;      // 纯虚函数，计算面积
    virtual double Perimeter(void) const = 0; // 纯虚函数，计算周长
    virtual void Print(void) const = 0;       // 纯虚函数，打印信息

    static size_t Count; // 静态成员变量，记录实例数量

    ~Shape() // 析构函数，减少实例计数
    {
        Count--;
    }

protected:
    double a_;                     // 第一条边或曲线起始点
    double b_;                     // 第二条边或曲线结束点
    double c_;                     // 第三条边或曲线高度（对于曲线来说是y值）
    int Angle_;                    // 角度（对于平行四边形来说）
    double (*Curve_Func_)(double); // 曲线函数指针
};

class Triangle final : public Shape
{
public:
    Triangle(double a, double b, double c) : Shape(a, b, c) {} // 构造函数，接受三条边

    double Area(void) const override // 计算三角形面积
    {
        if (a_ <= 0 || b_ <= 0 || c_ <= 0 || a_ + b_ <= c_ || a_ + c_ <= b_ || b_ + c_ <= a_)
        {
            std::cout << "三角形参数错误!" << std::endl;
            return 0.0;
        }
        double s = (a_ + b_ + c_) / 2;
        return sqrt(s * (s - a_) * (s - b_) * (s - c_));
    }

    double Perimeter(void) const override // 计算三角形周长
    {
        if (a_ <= 0 || b_ <= 0 || c_ <= 0 || a_ + b_ <= c_ || a_ + c_ <= b_ || b_ + c_ <= a_)
        {
            std::cout << "三角形参数错误!" << std::endl;
            return 0.0;
        }
        return a_ + b_ + c_;
    }

    void Print(void) const override // 打印三角形信息
    {
        std::cout << "三角形面积 = " << Area() << ", 周长 = " << Perimeter() << ", 实例 - " << Count << std::endl;
    }
};

class Parallelogram final : public Shape // 平行四边形类，继承自 Shape 类
{
public:
    Parallelogram(double a, double b, int Angle) : Shape(a, b, (int)Angle) {}; // 构造函数，接受两条边和一个角度

    double Area(void) const override // 计算平行四边形面积
    {
        return a_ * b_ * sin(Angle_ * 3.14159265358979323846 / 180.0);
    }

    double Perimeter(void) const override // 计算平行四边形周长
    {
        return 2 * (a_ + b_);
    }

    void Print(void) const override // 打印平行四边形信息
    {
        std::cout << "平行四边形面积 = " << Area() << ", 周长 = " << Perimeter() << ", 实例 - " << Count << std::endl;
    }
};

class Curve final : public Shape // 曲线类，继承自 Shape 类
{
public:
    Curve(double x1, double x2, double y, double (*Curve_Func)(double)) : Shape(x1, x2, y, Curve_Func) {}; // 构造函数，接受曲线的起始点和结束点以及曲线函数指针

    double Area(void) const override // 计算曲线下的面积
    {
        if (a_ >= b_)
        {
            std::cout << "曲线参数错误!" << std::endl;
            return 0.0;
        }
        double area = 0.0;

        for (double x = a_; x < b_; x += 0.01)
        {
            area += (Curve_Func_(x) + Curve_Func_(x + 0.01) - 2 * c_) * 0.01 / 2.0;
        }
        return area;
    }
    double Perimeter(void) const override // 计算曲线周长
    {
        if (a_ >= b_)
        {
            std::cout << "曲线参数错误!" << std::endl;
            return 0.0;
        }

        double perimeter = 0.0;

        for (double x = a_; x < b_; x += 0.001)
        {
            perimeter += sqrt(pow(0.001, 2.0) + pow((Curve_Func_(x + 0.001) - Curve_Func_(x)), 2.0));
        }
        perimeter += (b_ - a_) + Curve_Func_(a_) + Curve_Func_(b_) - 2 * c_;
        return perimeter;
    }

    void Print(void) const override // 打印曲线信息
    {
        std::cout << "曲面梯形面积 = " << Area() << ", 周长 = " << Perimeter() << ", 实例 - " << Count << std::endl;
    }
};

double Curve_F(double x) // 曲线函数，计算给定 x 值的曲线高度
{
    return (double)(x * x) + 1.0;
}

size_t Shape::Count = 0;

int main(void)
{
    Triangle T1(3.0, 4.0, 5.0); // 三角形三条边分别为 3.0, 4.0, 5.0
    T1.Print();

    Parallelogram P1(5, 5, 30); // 平行四边形两条边分别为 5, 5，角度为 30 度
    P1.Print();

    Curve C1(0.0, 1.0, 0.0, &Curve_F); // 曲线起始点为 0.0，结束点为 1.0，曲线函数为 Curve_F
    C1.Print();
}
