



#include"..\include\DCT color with distance calc.h"


//const less_by_red_functor less_by_red{};
//const less_by_green_functor less_by_green{};
//const less_by_blue_functor less_by_blue{};



int DCT_color::color_dist(const DCT_color_with_distance_calc & lhs, const DCT_color_with_distance_calc & rhs)
{
	return lhs.distance(rhs);
};