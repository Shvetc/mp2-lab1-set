// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if(len < 0)
	{
		throw "negative length";
	}
	else
	{
		BitLen = len;
		if( (len % (sizeof(TELEM)*8)) == 0 )
		{
			MemLen = len / (sizeof(TELEM)*8);
		}
		else
		{
			MemLen = 1 + len / (sizeof(TELEM)*8);
		}
		pMem = new TELEM[MemLen];
		for(int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
		

}
/*nt TBitField::GetMemLen() const
{
	return MemLen;
}
TELEM* TBitField::GetPmem() const
{
	return pMem;
}
*/
TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	this ->BitLen=bf.BitLen;
	this->MemLen= bf.MemLen;

	this->pMem = new TELEM[bf.MemLen];

	for (int i=0;i<bf.MemLen;i++)
	{
		this->pMem[i]= bf.pMem[i];
	}

}

TBitField::~TBitField()
{
	delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n / (sizeof(TELEM)*8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM mask = 1;
	TELEM position = n % (sizeof(TELEM)*8);
	mask = mask<<position;
	return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= 0 && n < BitLen)
	{
		int num = n / (sizeof(TELEM)*8);// в какой ячейке массива содержится бит
		int position = n % (sizeof(TELEM)*8);// на какой позиции находится бит в ячейке массива
		pMem[num] = pMem[num]  | GetMemMask(position);
	}
	else
	{
		throw "not correct index";
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n < BitLen)
	{
		int num = n / (sizeof(TELEM)*8);// в какой ячейке массива содержится бит
		int position = n % (sizeof(TELEM)*8);// на какой позиции находится бит в ячейке массива
		pMem[num] = pMem[num]  & ~GetMemMask(position);
	}
	else
	{
		throw "not correct index";
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if (n>= 0 && n< BitLen)
  {
	  return pMem[n/(sizeof(TELEM) *8)] & GetMemMask(n);
  }
  else
  {
	  throw " not correct index" ;
  }

}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{/*
	MemLen = bf.MemLen();
	BitLen = bf.GetLength();
	if (pMem != NULL)
	{
		delete [] pMem;
	}
	pMem = new TELEM[bf.GetMemLen()];

	for(int i=0;i<bf.GetMemLen();i++)
	{
		pMem[i]=bf.GetpMem()[i];
	}
	return *this;
	*/
}


int TBitField::operator==(const TBitField &bf) const // сравнение
{
 /* return (BitLen == bf.GetLength() && MemLen==bf.GetMemLen());*/
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	/*if(BitLen != bf.GetLength() || MemLen != bf.GetMemLen())
	{
		return 1;
	}
	if(BitLen == bf.GetLength() && MemLen == bf.GetMemLen())
	{
		for(int i = 0; i < MemLen; i++)
		{
			if(pMem[i] != bf.GetPmem()[i])
				return 1;
		}
	}
	return 0;
  */
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
}

TBitField TBitField::operator~(void) // отрицание
{
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
}
