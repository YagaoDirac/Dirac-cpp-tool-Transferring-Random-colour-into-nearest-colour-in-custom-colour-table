/*
这个index的做法，主要是希望让内存里面的数据在加法意义上连续的时候，他们所对应的最终的答案颜色尽量相同，如此一来就可以只存答案区间，而不用存所有2 to 24次方个element在最终的答案表里面。

顺便利用硬件的加法器，位运算，来加速其中的一些操作。

这个版本采用的混合逻辑是
r  r  r  r  r  r  r  r
 g  g  g  g  g  g  g  g
  b  b  b  b  b  b  b  b
左边高，右边低。混合前后，同一个通道内的为的高低顺序不变。

不过还是有一个问题，如果以后不用这种混合方式了，是否还有类似的简洁高效的处理方法？毕竟这种混合方法，太过内存，不够视觉。
*/


#pragma once

#include"DCT color with distance calc.h"


class DCT_color_index
{
public:
	int index;

//ctor
public:
	DCT_color_index() { index = -1; };
	DCT_color_index(unsigned char r, unsigned char g, unsigned char b)
	{
		set_value(r, g, b);
	}
	DCT_color_index(const DCT_color_with_distance_calc& in)
	{
		//This might crash..
		set_value(in.red(), in.green(), in.blue());
	}
	DCT_color_index(const int in) {index = in;correct();};


	DCT_color_index(const DCT_color_index& in) { index = in.index; };
	DCT_color_index(DCT_color_index&& in) { index = in.index; };
	DCT_color_index & operator=(const DCT_color_index& in)
	{ index = in.index; return *this; };
	DCT_color_index & operator=(DCT_color_index&& in)
	{index = in.index;  return *this;};

	//colour info
public:
	void set_value(unsigned char r, unsigned char g, unsigned char b)
	{
		int part1(0);
		int part2(0);
		int temp_channel(0);
		index = 0;//This line is optimizable. But I left it to the compiler.
		
		//0000000000000000vvvvcccc
		//00000000vvvv00000000cccc
		//00000000vvcc00000000vvcc
		//0000vv0000cc0000vv0000cc
		//0000vc0000vc0000vc0000vc
		//00v00c00v00c00v00c00v00c
		//Then shift left for r and g channels. Red needs 2 bits towards left, green needs 1.

		//Work:
		//Red channel
		part1 = r & 0b00001111;
		part2 = r & 0b11110000;
		//////////////vvvvcccc
		temp_channel = part1 | (part2<<8);
		part1 = temp_channel & 0b0011000000000011;
		part2 = temp_channel & 0b1100000000001100;
		/////////////////////////vvcc00000000vvcc
		temp_channel = part1 | (part2 << 4);
		part1 = temp_channel & 0b01000001000001000001;
		part2 = temp_channel & 0b10000010000010000010;
		/////////////////////////vc0000vc0000vc0000vc
		temp_channel = part1 | (part2 << 2);
		index |= temp_channel << 2;//If you are restrict with performance, change the |= to =. "index" is 0 before this line.

		//Green channel
		part1 = g & 0b00001111;
		part2 = g & 0b11110000;
		//////////////vvvvcccc
		temp_channel = part1 | (part2 << 8);
		part1 = temp_channel & 0b0011000000000011;
		part2 = temp_channel & 0b1100000000001100;
		/////////////////////////vvcc00000000vvcc
		temp_channel = part1 | (part2 << 4);
		part1 = temp_channel & 0b01000001000001000001;
		part2 = temp_channel & 0b10000010000010000010;
		/////////////////////////vc0000vc0000vc0000vc
		temp_channel = part1 | (part2 << 2);
		index |= temp_channel << 1;
	
		//Blue channel
		part1 = b & 0b00001111;
		part2 = b & 0b11110000;
		//////////////vvvvcccc
		temp_channel = part1 | (part2 << 8);
		part1 = temp_channel & 0b0011000000000011;
		part2 = temp_channel & 0b1100000000001100;
		/////////////////////////vvcc00000000vvcc
		temp_channel = part1 | (part2 << 4);
		part1 = temp_channel & 0b01000001000001000001;
		part2 = temp_channel & 0b10000010000010000010;
		/////////////////////////vc0000vc0000vc0000vc
		temp_channel = part1 | (part2 << 2);
		index |= temp_channel << 0;
	};
	unsigned char r()const {return __b(index >> 2);};
	unsigned char g()const{return __b(index >> 1);};
	unsigned char b()const{return __b(index);};
	inline unsigned char __b (int in)const
	{
		int part1 = in & 0b1000001000001000001000;
		int part2 = in & 0b0001000001000001000001;
		part1 >>= 2;
		int temp = part1 | part2;//results in 87000065000043000021
		part1 = temp & 0b11000000000011000000;
		part2 = temp & 0b00000011000000000011;
		/////////////////87000065000043000021
		part1 >>= 4;
		temp = part1 | part2;//results in 8765000000004321
		part1 = temp & 0b1111000000000000;
		/////////////////8765000000004321
		part2 = temp & 0b0000000000001111;
		part1 >>= 8;
		return part1 | part2;
	};

//util
public:

	bool valid() const{ return (index >= 0 && index < (1 << 24)); };
	explicit operator int()const { return index; };
	void correct(){ if (index < 0)index = 0; if (index >= (1 << 24))index = (1 << 24) - 1; }
	DCT_color_index operator+(int rhs) { DCT_color_index temp(index + rhs); temp.correct(); return temp; };
	DCT_color_index operator-(int rhs) { DCT_color_index temp(index - rhs); temp.correct(); return temp; };
	DCT_color_index& operator+=(int rhs) { index += rhs; correct(); return *this; };
	DCT_color_index& operator-=(int rhs) { index -= rhs; correct(); return *this; };
	operator DCT_color_with_distance_calc() const{
		return DCT_color_with_distance_calc(r(), g(), b());
	}

	DCT_color_with_distance_calc to_color()const  {
		return DCT_color_with_distance_calc(r(), g(), b());
	}

private:
	static const int __bit_mask = 0b100100100100100100100;//To be honest, I didn't expected to invent this. Looks good. 
public:
	//If the index is <=0 or >= 1<<24, this might crash.
	DCT_color_index neighbour_with_less_index()const
	{
		if (index & 1)return DCT_color_index(index - 1);
		else if (index & (1 << 1))return DCT_color_index(index - (1 << 1));
		else if (index & (1 << 2))return DCT_color_index(index - (1 << 2));
		else if (index & (1 << 3))return DCT_color_index(index - (1 << 3) + (__bit_mask >> 20));//8 >>> 1
		else if (index & (1 << 4))return DCT_color_index(index - (1 << 4) + (__bit_mask >> 19));//16 >>> 2
		else if (index & (1 << 5))return DCT_color_index(index - (1 << 5) + (__bit_mask >> 18));//32 >>> 4
		else if (index & (1 << 6))return DCT_color_index(index - (1 << 6) + (__bit_mask >> 17));//64 >>> 9
		else if (index & (1 << 7))return DCT_color_index(index - (1 << 7) + (__bit_mask >> 16));
		else if (index & (1 << 8))return DCT_color_index(index - (1 << 8) + (__bit_mask >> 15));
		else if (index & (1 << 9))return DCT_color_index(index - (1 << 9) + (__bit_mask >> 14));
		else if (index & (1 << 10))return DCT_color_index(index - (1 << 10) + (__bit_mask >> 13));
		else if (index & (1 << 11))return DCT_color_index(index - (1 << 11) + (__bit_mask >> 12));
		else if (index & (1 << 12))return DCT_color_index(index - (1 << 12) + (__bit_mask >> 11));
		else if (index & (1 << 13))return DCT_color_index(index - (1 << 13) + (__bit_mask >> 10));
		else if (index & (1 << 14))return DCT_color_index(index - (1 << 14) + (__bit_mask >> 9));
		else if (index & (1 << 15))return DCT_color_index(index - (1 << 15) + (__bit_mask >> 8));
		else if (index & (1 << 16))return DCT_color_index(index - (1 << 16) + (__bit_mask >> 7));
		else if (index & (1 << 17))return DCT_color_index(index - (1 << 17) + (__bit_mask >> 6));
		else if (index & (1 << 18))return DCT_color_index(index - (1 << 18) + (__bit_mask >> 5));
		else if (index & (1 << 19))return DCT_color_index(index - (1 << 19) + (__bit_mask >> 4));
		else if (index & (1 << 20))return DCT_color_index(index - (1 << 20) + (__bit_mask >> 3));
		else if (index & (1 << 21))return DCT_color_index(index - (1 << 21) + (__bit_mask >> 2));
		else if (index & (1 << 22))return DCT_color_index(index - (1 << 22) + (__bit_mask >> 1));
		else if (index & (1 << 23))return DCT_color_index(index - (1 << 23) + (__bit_mask));
	}
	bool neighbour_with_less_index_safe(DCT_color_index& out__result)const
	{
		if (index <= 0 || index >= (1 << 24))
			return false;

		out__result = neighbour_with_less_index();
		return true;
	}




	//Relationship op
	bool operator< (const DCT_color_index& rhs)const { return index <  rhs.index;};
	bool operator==(const DCT_color_index& rhs)const { return index == rhs.index; };
	bool operator> (const DCT_color_index& rhs)const { return index >  rhs.index; };
	bool operator<=(const DCT_color_index& rhs)const { return index <= rhs.index; };
	bool operator>=(const DCT_color_index& rhs)const { return index >= rhs.index; };
	bool operator!=(const DCT_color_index& rhs)const { return index != rhs.index;};
	bool operator< (const int& rhs)const { return index <  rhs; };
	bool operator==(const int& rhs)const { return index == rhs; };
	bool operator> (const int& rhs)const { return index >  rhs; };
	bool operator<=(const int& rhs)const { return index <= rhs; };
	bool operator>=(const int& rhs)const { return index >= rhs; };
	bool operator!=(const int& rhs)const { return index != rhs; };
	


};


class DCT_color_mapping_element
{
public:
	DCT_color_index greater_equal;
	//DCT_color_index less;
	DCT_color_with_distance_calc answer;

	//ctor
public:
	DCT_color_mapping_element(const DCT_color_index& in_greater_equal, const DCT_color_with_distance_calc& in_answer)
	{
		greater_equal = in_greater_equal;
		//less = in_less;
		answer = in_answer;
	}
	//core util
public:
	//bool contain(const DCT_color_index& rhs)const
	//{
	//	return ((rhs >= greater_equal); && (rhs < less));
	//}
	//bool less_than(const DCT_color_index& rhs)const
	//{
	//	return (rhs < greater_equal);
	//}
	
	
	//bool contain(const DCT_color_with_distance_calc& rhs)const
	//{
	//	DCT_color_index index = DCT_color_index(rhs);
	//	return ((index >= greater_equal) && (index < less));
	//}
	//bool less_than(const DCT_color_with_distance_calc& rhs)const
	//{
	//	DCT_color_index index = DCT_color_index(rhs);
	//	return (index < greater_equal);
	//}

	//This is fragile. Make sure everything is correct before calling this function
	bool operator<(const DCT_color_mapping_element rhs)const
	{
		return greater_equal < rhs.greater_equal;
	}
	//This is fragile. Make sure everything is correct before calling this function
	bool operator==(const DCT_color_mapping_element rhs)const
	{
		return greater_equal == rhs.greater_equal;
	}
};
//可能需要几个functor，看情况。

