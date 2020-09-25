#pragma once

#include <iostream>
#include<algorithm>
#include<vector>
#include"DCT color with distance calc.h"

class colour_table_data_class
{
	void data_2020_set_15()
	{
		data.reserve(147);

		//直接在这儿改数据，其他不用管。格式，无符号char，0到255，顺序是rgb。

		__add_data(110, 154, 48);
		__add_data(213, 201, 141);
		__add_data(172, 172, 172);
		__add_data(220, 0, 0);
		__add_data(138, 138, 220);
		__add_data(144, 144, 144);
		__add_data(220, 220, 220);
		__add_data(141, 145, 159);
		__add_data(130, 94, 66);
		__add_data(97, 97, 97);
		__add_data(123, 103, 62);
		__add_data(220, 217, 211);
		__add_data(186, 110, 44);
		__add_data(154, 66, 186);
		__add_data(88, 132, 186);
		__add_data(198, 198, 44);
		__add_data(110, 176, 22);
		__add_data(209, 110, 142);
		__add_data(66, 66, 66);
		__add_data(132, 132, 132);
		__add_data(66, 110, 132);
		__add_data(110, 54, 154);
		__add_data(44, 66, 154);
		__add_data(88, 66, 44);
		__add_data(88, 110, 44);
		__add_data(132, 44, 44);
		__add_data(22, 22, 22);
		__add_data(216, 205, 66);
		__add_data(79, 189, 184);
		__add_data(64, 110, 220);
		__add_data(0, 187, 50);
		__add_data(111, 74, 42);
		__add_data(97, 2, 0);
		__add_data(180, 153, 139);
		__add_data(137, 71, 31);
		__add_data(129, 75, 93);
		__add_data(97, 93, 119);
		__add_data(160, 115, 31);
		__add_data(89, 101, 46);
		__add_data(138, 66, 67);
		__add_data(49, 35, 30);
		__add_data(116, 92, 85);
		__add_data(75, 79, 79);
		__add_data(105, 63, 76);
		__add_data(66, 53, 79);
		__add_data(66, 43, 30);
		__add_data(66, 71, 36);
		__add_data(123, 52, 40);
		__add_data(32, 19, 14);
		__add_data(127, 178, 56);
		__add_data(247, 233, 163);
		__add_data(199, 199, 199);
		__add_data(255, 0, 0);
		__add_data(160, 160, 255);
		__add_data(167, 167, 167);
		__add_data(255, 255, 255);
		__add_data(164, 168, 184);
		__add_data(151, 109, 77);
		__add_data(112, 112, 112);
		__add_data(143, 119, 72);
		__add_data(255, 252, 245);
		__add_data(216, 127, 51);
		__add_data(178, 76, 216);
		__add_data(102, 153, 216);
		__add_data(229, 229, 51);
		__add_data(127, 204, 25);
		__add_data(242, 127, 165);
		__add_data(76, 76, 76);
		__add_data(153, 153, 153);
		__add_data(76, 127, 153);
		__add_data(127, 63, 178);
		__add_data(51, 76, 178);
		__add_data(102, 76, 51);
		__add_data(102, 127, 51);
		__add_data(153, 51, 51);
		__add_data(25, 25, 25);
		__add_data(250, 238, 77);
		__add_data(92, 219, 213);
		__add_data(74, 128, 255);
		__add_data(0, 217, 58);
		__add_data(129, 86, 49);
		__add_data(112, 2, 0);
		__add_data(209, 177, 161);
		__add_data(159, 82, 36);
		__add_data(149, 87, 108);
		__add_data(112, 108, 138);
		__add_data(186, 133, 36);
		__add_data(103, 117, 53);
		__add_data(160, 77, 78);
		__add_data(57, 41, 35);
		__add_data(135, 107, 98);
		__add_data(87, 92, 92);
		__add_data(122, 73, 88);
		__add_data(76, 62, 92);
		__add_data(76, 50, 35);
		__add_data(76, 82, 42);
		__add_data(142, 60, 46);
		__add_data(37, 22, 16);
		__add_data(90, 126, 40);
		__add_data(174, 164, 115);
		__add_data(140, 140, 140);
		__add_data(180, 0, 0);
		__add_data(113, 113, 180);
		__add_data(118, 118, 118);
		__add_data(180, 180, 180);
		__add_data(116, 119, 130);
		__add_data(107, 77, 54);
		__add_data(79, 79, 79);
		__add_data(101, 84, 51);
		__add_data(180, 178, 173);
		__add_data(152, 90, 36);
		__add_data(126, 54, 152);
		__add_data(72, 108, 152);
		__add_data(162, 162, 36);
		__add_data(90, 144, 18);
		__add_data(171, 90, 116);
		__add_data(54, 54, 54);
		__add_data(108, 108, 108);
		__add_data(54, 90, 108);
		__add_data(90, 44, 126);
		__add_data(36, 54, 126);
		__add_data(72, 54, 36);
		__add_data(72, 90, 36);
		__add_data(108, 36, 36);
		__add_data(18, 18, 18);
		__add_data(176, 168, 54);
		__add_data(65, 155, 150);
		__add_data(52, 90, 180);
		__add_data(0, 153, 41);
		__add_data(91, 61, 35);
		__add_data(79, 1, 0);
		__add_data(148, 125, 114);
		__add_data(112, 58, 25);
		__add_data(105, 61, 76);
		__add_data(79, 76, 97);
		__add_data(131, 94, 25);
		__add_data(73, 83, 37);
		__add_data(113, 54, 55);
		__add_data(40, 29, 25);
		__add_data(95, 76, 69);
		__add_data(61, 65, 65);
		__add_data(86, 52, 62);
		__add_data(54, 44, 65);
		__add_data(54, 35, 25);
		__add_data(54, 58, 30);
		__add_data(100, 42, 32);
		__add_data(26, 16, 11);


	}
	void debug_data1()
	{
		data.reserve(20);

		__add_data(0, 0, 0);
		__add_data(0, 0, 1);
		__add_data(0, 0, 2);
		__add_data(0, 0, 3);
		__add_data(1, 0, 0);
		__add_data(1, 0, 1);
		__add_data(1, 0, 2);
		__add_data(2, 0, 0);
		__add_data(2, 0, 1);
		__add_data(3, 0, 0);
		__add_data(4, 0, 0);
		__add_data(5, 0, 0);
		__add_data(6, 0, 0);
		__add_data(6, 0, 1);
		__add_data(7, 0, 0);
		__add_data(8, 0, 0);
		__add_data(8, 0, 1);
		__add_data(8, 0, 2);
		__add_data(8, 0, 3);
		__add_data(9, 0, 0);
		__add_data(9, 0, 1);
		__add_data(10, 0, 0);
		__add_data(11, 0, 0);
		__add_data(12, 0, 0);
		__add_data(12, 0, 1);
		__add_data(12, 0, 2);
	}
	void debug_data2()
	{
		data.reserve(128);
		for (int redred = 0; redred < 255; redred += 64)
			for (int greengreen = 0; greengreen < 255; greengreen += 32)//This one is different.
				for (int blueblue = 0; blueblue < 255; blueblue += 64)
				{
					__add_data(redred, greengreen, blueblue);
				}
	}

	//CTOR CTOR CTOR CTOR CTOR CTOR CTOR CTOR CTOR CTOR CTOR CTOR 
public:
	colour_table_data_class()
	{
#ifdef _DEBUG
		debug_data2();
#else
		data_2020_set_15();
#endif // _DEBUG

		std::sort(data.begin(), data.end());

#ifdef _DEBUG
		if (std::unique(data.begin(), data.end()) != data.end())
		{
			//如果你遇到这个问题了，那就是颜色表数据里面有重复的。在release里面，会自动去掉重复的。
			//总之我还是希望你们可以确保初始数据是尽量ok的。
			throw;
		}
#else
		//没问题了就把这个地方注释掉，可以稍微快一点点。
		data.erase(std::unique(data.begin(), data.end()), data.end());
#endif
	}
	
	//The REAL CONTENT
public:
	std::vector<DCT_color_with_distance_calc> data;

	//inner util
private:
	void __add_data(unsigned char in_r, unsigned char in_g, unsigned char in_b)
	{
		data.push_back(DCT_color_with_distance_calc(in_r, in_g, in_b));
	}


};

extern const colour_table_data_class colour_table_data_2020sep15;

