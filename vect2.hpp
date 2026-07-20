/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xzhen <xzhen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:20:54 by fatkeski          #+#    #+#             */
/*   Updated: 2026/07/06 17:59:16 by xzhen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2
{
	private:
		int x;
		int y;
	public:
		vect2();
		vect2(int num1, int num2);
		vect2(const vect2& source);
		vect2& operator=(const vect2& source);
		~vect2();
		//-----------------------------
		//0.[]返回int!!!
		int operator[](int index) const;//const不能修改vector2内容,所以返回int;不可以a[0]=100;
		int& operator[](int index);//non const能修改,所以返回&vect2;可以a[0]=100;

		//1.标量运算 vector * int; * *=
		vect2 operator*(int num) const;//vect2 b = a*2;不能修改a
		vect2& operator*=(int num);//会修改;a*=2;能修改a
		//2.向量运算 vector 和 vector; + - * += -= *=
		vect2 operator+(const vect2& obj) const;//c=a+b;不能修改a本身
		vect2 operator-(const vect2& obj) const;//c=a-b;
		vect2 operator*(const vect2& obj) const;//c=a*b
		
		vect2& operator+=(const vect2& obj);//a+=b;可以修改ia本身
		vect2& operator-=(const vect2& obj);//a-=b;
		vect2& operator*=(const vect2& obj);//a*=b;
		
		//3.前置,后置,int没有实际作用，只是用来区分两种重载
		vect2& operator++();//++a
		vect2 operator++(int);//a++
		vect2& operator--();//--a
		vect2 operator--(int);//a--
		//4.比较运算 == !=
		bool operator==(const vect2& obj) const;//(1,2)==(1,2) return true
		bool operator!=(const vect2& obj) const;//(1,2)!=(2,1) return true
		//5.向量取反:-v=(-3, -4),不会修改原对象所以是const
		vect2 operator-() const;
};
//6.标量运算 为了支持int*vector;2*a;  之前成员函数只能支持vector*int
vect2 operator*(int num, const vect2& obj);
//7.<<
std::ostream& operator<<(std::ostream& out,const vect2& obj);

#endif

