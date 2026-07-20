/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhen <xzhen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:39:15 by fatkeski          #+#    #+#             */
/*   Updated: 2026/07/06 17:59:49 by xzhen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect2.hpp"

vect2::vect2()
{
	this->x = 0;
	this->y = 0;
}
//不用return!!
vect2::vect2(int num1, int num2)
{
	this->x = num1;
	this->y = num2;
}

vect2::vect2(const vect2& copy)
{
	*this = copy;//一次复制
}

vect2& vect2::operator=(const vect2& other)
{
	if(this != &other) 
	{
		this->x = other.x;
		this->y = other.y;
	}
	return(*this);//return!!!
}
vect2::~vect2(){}
//------------------------------------------
//0.[]
int vect2::operator[](int index) const
{
	if(index == 0)
		return(this->x);
	return(this->y);
}

int& vect2::operator[](int index)
{
	if(index == 0)
		return(this->x);
	return(this->y);
}
//1.标量运算 vector * int
vect2 vect2::operator*(int num) const
{
	vect2 temp;

	temp.x = this->x * num;
	temp.y = this->y * num;
	return(temp);
}

vect2& vect2::operator*=(int num)
{
	this->x *= num;
	this->y *= num;
	return(*this);
}
//2.向量运算 vector 和 vector
vect2 vect2::operator+(const vect2& obj) const
{
	vect2 temp = *this;

	temp.x += obj.x;
	temp.y += obj.y;
	return(temp);
}
vect2 vect2::operator-(const vect2& obj) const
{
	vect2 temp = *this;
	temp.x -= obj.x;
	temp.y -= obj.y;
	return(temp);
}
vect2 vect2::operator*(const vect2& obj) const
{
	vect2 temp = *this;
	temp.x *= obj.x;
	temp.y *= obj.y;
	return(temp);
}
vect2& vect2::operator+=(const vect2& obj)
{
	this->x += obj.x;
	this->y += obj.y;
	return(*this);
}

vect2& vect2::operator-=(const vect2& obj)
{
	this->x -= obj.x;
	this->y -= obj.y;
	return(*this);
}

vect2& vect2::operator*=(const vect2& obj)
{
	this->x *= obj.x;
	this->y *= obj.y;
	return(*this);
}

//3.前置,后置,int没有实际作用，只是用来区分两种重载,不能加cosnt因为最终一定会改vector
vect2& vect2::operator++()
{
	this->x += 1;
	this->y += 1;
	return(*this);
}

vect2 vect2::operator++(int)
{
	vect2 temp = *this;

	++(*this);
	return(temp);
}

vect2& vect2::operator--()
{
	this->x -= 1;
	this->y -= 1;
	return(*this);
}

vect2 vect2::operator--(int)
{
	vect2 temp = *this;

	--(*this);
	return(temp);
}
//4.比较运算
bool vect2::operator==(const vect2& obj) const
{
	if((this->x == obj.x) && (this->y == obj.y))
		return(true);
	return(false);
}

bool vect2::operator!=(const vect2& obj) const
{
	return(!(obj == *this));
}
//5.向量取反:-v=(-3, -4),不会修改原对象所以是const
vect2 vect2::operator-() const
{
	vect2 temp = *this;
	temp[0] = -temp[0];
	temp[1] = -temp[1];
	return(temp);
}

/---------------------------------------------------
//6.标量运算 为了支持int*vector;2*a;  之前成员函数只能支持vector*int
vect2 operator*(int num, const vect2& obj)
{
	vect2 temp(obj);
	temp *= num;
	return(temp);
}
std::ostream& operator<<(std::ostream& out,const vect2& obj)
{
	std::cout << "{" << obj[0] << ", " << obj[1] << "}";
	return(out);
}

