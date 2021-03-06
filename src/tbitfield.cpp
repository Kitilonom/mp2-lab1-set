// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0) throw 0;
	BitLen = len;
	MemLen = floor(BitLen/sizeof(TELEM));
	MemLen++;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[]pMem;
	BitLen = NULL;
	MemLen = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n / sizeof(TELEM));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ( (n / sizeof(TELEM)) == (MemLen - 1) )
		return  1 << ((BitLen % sizeof(TELEM)) - (n % sizeof(TELEM)));
	return 1 << (sizeof(TELEM)-(n % sizeof(TELEM)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= BitLen) throw 0;
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen) throw 0;
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n > BitLen) throw 0;
	return (pMem[GetMemIndex(n)] & GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (bf != *this)
	{
		delete[]pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
	}
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
				return 0;
		return 1;
	}
	return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
				return 1;
		return 0;
	}
	return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TELEM max = 0;
	BitLen > bf.BitLen ? max = BitLen : max = bf.BitLen;
	TBitField tmp(max);
	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = tmp.pMem[i] | pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] = tmp.pMem[i] | bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (BitLen > bf.BitLen)
	{
		TBitField tmp(BitLen);
		for (int i = 0; i < bf.MemLen; i++)
			tmp.pMem[i] = pMem[i] & bf.pMem[i];
		return tmp;
	}
	else
	{
		TBitField tmp(bf.BitLen);
		for (int i = 0; i < MemLen; i++)
			tmp.pMem[i] = bf.pMem[i] & pMem[i];
		return tmp;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(*this);
	for (int i = 0; i < tmp.BitLen; i++)
		if (tmp.GetBit(i))
			tmp.ClrBit(i);
		else
			tmp.SetBit(i);
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	istr >> bf.BitLen;
	istr >> bf.MemLen;
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	ostr << bf.BitLen;
	ostr << bf.MemLen;
	ostr << bf.pMem;
	return ostr;
}
