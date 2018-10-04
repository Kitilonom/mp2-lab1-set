// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
	//TBitField BitField(mp);
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
	//BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
	BitField = bf;
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem > MaxPower) throw 0;
	if (BitField.GetBit(Elem))
		return 1;
    return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem > MaxPower) throw 0;
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem > MaxPower) throw 0;
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (s != *this)
	{
		MaxPower = s.MaxPower;
		BitField = s.BitField;
	}
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if ((MaxPower != s.MaxPower) && (BitField != s.BitField))
		return 0;
    return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if ((MaxPower == s.MaxPower) && (BitField == s.BitField))
		return 0;
	return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	unsigned max = 1;
	MaxPower > s.MaxPower ? max = s.MaxPower : max = MaxPower;
	TSet tmp(max);
	tmp.BitField = BitField | s.BitField;
	return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	unsigned max = 1;
	MaxPower > Elem ? max = Elem : max = MaxPower;
	TSet tmp(max);
	TBitField k(Elem);
	k.SetBit(Elem);
	tmp.BitField = BitField | k;
	return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet a(1);
	return a;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet a(1);
	return a;
}

TSet TSet::operator~(void) // дополнение
{
	TSet a(1);
	return a;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	return ostr;
}
