#pragma once


class DCT_color_with_distance_calc
{
	//To keep things simple, the data is public. They should be private to be safe.
public:
	inline unsigned char red()const { return static_cast<unsigned char>(rgb >> 16); };
	inline unsigned char green()const { return static_cast<unsigned char>(rgb >> 8); };
	inline unsigned char blue()const { return static_cast<unsigned char>(rgb);};
private:
	inline unsigned char r()const { return static_cast<unsigned char>(rgb >> 16); };
	inline unsigned char g()const { return static_cast<unsigned char>(rgb >> 8); };
	inline unsigned char b()const { return static_cast<unsigned char>(rgb); };
public:
	int rgb;

	//ctor
public:
	DCT_color_with_distance_calc() {rgb= -1;};
	DCT_color_with_distance_calc(unsigned char in_r, unsigned char in_g, unsigned char in_b){
		rgb = static_cast<int>(in_r) << 16 | static_cast<int>(in_g) << 8 | in_b;};

	DCT_color_with_distance_calc(const DCT_color_with_distance_calc& in){
		rgb = in.rgb;	};
	DCT_color_with_distance_calc(DCT_color_with_distance_calc&& in)	{
		rgb = in.rgb; };

	DCT_color_with_distance_calc& operator=(const DCT_color_with_distance_calc& in)
	{rgb = in.rgb; return *this;};
	DCT_color_with_distance_calc& operator=(DCT_color_with_distance_calc&& in)
	{rgb = in.rgb; return *this;};

//main util.
public:
	int distance(const DCT_color_with_distance_calc& in)const
	{
		int temp = r() - in.r();
		int result = temp * temp;
		temp = g() - in.g();
		result += temp * temp;
		temp = b() - in.b();
		result += temp * temp;
		return result;
	}

	bool operator<(const DCT_color_with_distance_calc& rhs) { return rgb < rhs.rgb; };
	bool operator==(const DCT_color_with_distance_calc& rhs) { return rgb == rhs.rgb; };
	//bool operator>(const DCT_color_rgb_uchar_with_distance_calc& rhs) { return rgb > rhs.rgb; };
	//bool operator<=(const DCT_color_rgb_uchar_with_distance_calc& rhs) { return rgb <= rhs.rgb; };
	//bool operator>=(const DCT_color_rgb_uchar_with_distance_calc& rhs) { return rgb >= rhs.rgb; };
	//bool operator!=(const DCT_color_rgb_uchar_with_distance_calc& rhs) { return rgb != rhs.rgb; };

	//validator. Not important. Debug purpose.
	inline bool valid()const { return (rgb >= 0 && rgb <= 0xffffff); };


};

class less_by_red
{
public:
	less_by_red() {};
	bool operator()(const DCT_color_with_distance_calc& lhs, const DCT_color_with_distance_calc& rhs) 
	{return (lhs.rgb&0xff0000) < (rhs.rgb & 0xff0000); };
};
//extern const less_by_red_functor less_by_red;

class less_by_green
{
public:
	less_by_green() {};
	bool operator()(const DCT_color_with_distance_calc& lhs, const DCT_color_with_distance_calc& rhs) 
	{return (lhs.rgb & 0xff00) < (rhs.rgb & 0xff00);};
};
//extern const less_by_green_functor less_by_green;

class less_by_blue
{
public:
	less_by_blue() {};
	bool operator()(const DCT_color_with_distance_calc& lhs, const DCT_color_with_distance_calc& rhs)
	{return (lhs.rgb & 0xff) < (rhs.rgb & 0xff);};
};
//extern const less_by_blue_functor less_by_blue;









namespace DCT_color
{
	int color_dist(const DCT_color_with_distance_calc& lhs, const DCT_color_with_distance_calc& rhs);
}


