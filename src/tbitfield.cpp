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
		int num = GetMemIndex(n);// в какой ячейке массива содержится бит
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
{
	
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	if (pMem != NULL)
	{
		delete[] pMem;
	}
	pMem = new TELEM[MemLen];

	for (int i=0;i<MemLen;i++)
	{
		pMem[i]= bf.pMem[i];
	}

	return *this;
	
	
		
}


int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (BitLen == bf.GetLength()  && MemLen == bf.MemLen)
  {
	  for(int i=0;i< MemLen;i++)
	  {
		  if (pMem[i] == bf.pMem[i])
			  return 1;
	  }
  }
  else return 0;



}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if(BitLen != bf.GetLength() || MemLen != bf.MemLen)
		return 1;
	if(BitLen == bf.GetLength() && MemLen == bf.MemLen)
	{
		for(int i = 0; i < MemLen; i++)
		{
			if(pMem[i] != bf.pMem[i])
				return 1;
		}
	}
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	//TBitField res(bf.GetLength());
	TBitField res(BitLen <= bf.GetLength() ? bf.GetLength() : BitLen);
	for(int i = 0; i < MemLen; i++)
	{
		res.pMem[i] = pMem[i] | bf.pMem[i];
	}
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField res(BitLen <= bf.GetLength() ? bf.GetLength() : BitLen);
	for(int i = 0; i < MemLen; i++)
	{
		res.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for(int i = 0; i < BitLen; i++)
		tmp.SetBit(i);
	TBitField res(BitLen);
	for(int i = 0; i < MemLen; i++)
	{
		res.pMem[i] = ~pMem[i] & tmp.pMem[i];
	}
	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	
	for (int i=0;i<bf.MemLen;i++)
	{
		istr>> bf.pMem[i];
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	return ostr;
}
