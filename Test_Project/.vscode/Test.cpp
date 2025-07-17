#include <iostream>

class Player // 游戏玩家，抽象类
{
public:
    Player(size_t Health, size_t Energy) : Health_(Health), Energy_(Energy) {}
    virtual void Technique() = 0; // 输出技能，纯虚函数
    static size_t Ammunition;     // 弹药量，静态成员变量

    void PrintStatus(void) // 输出生命值和能量值
    {
        std::cout << "Health: " << Health_ << ", Energy: " << Energy_ << std::endl;
    }

protected:
    size_t Health_; // 生命值
    size_t Energy_; // 能量值
};

class Raiders : public Player // 突击兵，继承自 Player 类
{
public:
    Raiders(size_t Health, size_t Energy) : Player(Health, Energy) {}

    void Technique() override // 技能输出
    {
        std::cout << "Raiders" << std::endl;
    }
};

class Medical_Soldier final : public Player // 医疗兵，继承自 Player 类
{
public:
    Medical_Soldier(size_t Health, size_t Energy) : Player(Health, Energy) {}

    void Technique() override // 技能输出
    {
        std::cout << "Medical_Soldier" << std::endl;
    }
};

class Investigator final : public Player // 侦察兵，继承自 Player 类
{
public:
    Investigator(size_t Health, size_t Energy) : Player(Health, Energy) {}
    void Technique() override // 技能输出
    {
        std::cout << "Investigator" << std::endl;
    }
};

class Engineer_Raiders final : public Raiders // 工程突击兵，继承突击兵类
{
public:
    Engineer_Raiders(size_t Health, size_t Energy) : Raiders(Health, Energy) {}

    void Technique() override // 技能输出
    {
        std::cout << "Engineer_Raiders" << std::endl;
    }
};

size_t Player::Ammunition = 1000; // 弹药，静态成员变量初始化

int main(void)
{
    Raiders R1(100, 100); // 创建突击兵对象 R1
    R1.PrintStatus();
    R1.Technique();

    Engineer_Raiders E1(100, 80); // 创建工程突击兵对象 E1
    E1.PrintStatus();
    E1.Technique();
    E1.Raiders::Technique();

    Medical_Soldier M1(80, 50); // 创建医疗兵对象 M1
    M1.PrintStatus();
    M1.Technique();

    Investigator I1(90, 60); // 创建侦察兵对象 I1
    I1.PrintStatus();
    I1.Technique();

    Player *P = &R1; // 多态
    P->Technique();  // 调用突击兵的技能输出

    std::cout << "R1-Ammunition:" << R1.Ammunition << std::endl; // 输出弹药量
    std::cout << "E1-Ammunition:" << E1.Ammunition << std::endl;
    std::cout << "M1-Ammunition:" << M1.Ammunition << std::endl;
    std::cout << "I1-Ammunition:" << I1.Ammunition << std::endl;
    std::cout << "P-Ammunition:" << P->Ammunition << std::endl; // 输出多态指针的弹药量
}
