// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

using std::out_of_range;

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
    MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить максимальное количествово элементовтов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem > 0 && Elem < MaxPower + 1)
    {
        return BitField.GetBit(Elem);
    }
    else
        throw out_of_range("Elem beyond the limit of the MxPower of the set");
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem > 0 && Elem < MaxPower + 1)
    {
        BitField.SetBit(Elem);
    }
    else
        throw out_of_range("Elem beyond the limit of the MxPower of the set");
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem > 0 && Elem < MaxPower + 1)
    {
        BitField.ClrBit(Elem);
    }
    else
        throw out_of_range("Elem beyond the limit of the MxPower of the set");
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower == s.MaxPower && BitField == s.BitField)
    {
        cout << "The objects are equal" << endl;
        return 1;
    }
    else
    {
        cout << "The objects are not equal" << endl;
        return 0;
    }
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower || BitField == s.BitField)
    {
        cout << "The objects are not equal" << endl;
        return 1;
    }
    else
    {
        cout << "The objects are equal" << endl;
        return 0;
    }
}

TSet TSet::operator+(const TSet &s) // объединение
{
    MaxPower = max(MaxPower, s.MaxPower);
    BitField = BitField | s.BitField;
    return *this;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem > 0 && Elem < MaxPower + 1)
    {
        this->InsElem(Elem);
        return *this;
    }
    else
        throw out_of_range("Elem beyond the limit of the MxPower of the set");
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if(Elem > 0 && Elem < MaxPower + 1)
    {
        this->DelElem(Elem);
        return *this;
    }
    else
    throw out_of_range("Elem beyond the limit of the MxPower of the set");
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    return (BitField & s.BitField);
}

TSet TSet::operator~(void) // дополнение
{
    return ~BitField; //Почему?
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    istr >> s.MaxPower;
    istr >> s.BitField;
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    ostr << s.BitField;
    return ostr;
}
