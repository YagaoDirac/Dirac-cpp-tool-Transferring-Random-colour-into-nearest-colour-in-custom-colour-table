#include"include\DCT color table helper.h"

//int main1(int argc, char *argv[])
//{
//
//	DCT_color_index_form_rgb_uchar r[8];
//	r[0] = DCT_color_index_form_rgb_uchar(1 << 0, 0, 0);
//	r[1] = DCT_color_index_form_rgb_uchar(1 << 1, 0, 0);
//	r[2] = DCT_color_index_form_rgb_uchar(1 << 2, 0, 0);
//	r[3] = DCT_color_index_form_rgb_uchar(1 << 3, 0, 0);
//	r[4] = DCT_color_index_form_rgb_uchar(1 << 4, 0, 0);
//	r[5] = DCT_color_index_form_rgb_uchar(1 << 5, 0, 0);
//	r[6] = DCT_color_index_form_rgb_uchar(1 << 6, 0, 0);
//	r[7] = DCT_color_index_form_rgb_uchar(1 << 7, 0, 0);
//
//	DCT_color_index_form_rgb_uchar g[8];
//	g[0] = DCT_color_index_form_rgb_uchar(0, 1 << 0, 0);
//	g[1] = DCT_color_index_form_rgb_uchar(0, 1 << 1, 0);
//	g[2] = DCT_color_index_form_rgb_uchar(0, 1 << 2, 0);
//	g[3] = DCT_color_index_form_rgb_uchar(0, 1 << 3, 0);
//	g[4] = DCT_color_index_form_rgb_uchar(0, 1 << 4, 0);
//	g[5] = DCT_color_index_form_rgb_uchar(0, 1 << 5, 0);
//	g[6] = DCT_color_index_form_rgb_uchar(0, 1 << 6, 0);
//	g[7] = DCT_color_index_form_rgb_uchar(0, 1 << 7, 0);
//
//	DCT_color_index_form_rgb_uchar b[8];
//	b[0] = DCT_color_index_form_rgb_uchar(0, 0, 1 << 0);
//	b[1] = DCT_color_index_form_rgb_uchar(0, 0, 1 << 1);
//	b[2] = DCT_color_index_form_rgb_uchar(0, 0, 1 << 2);
//	b[3] = DCT_color_index_form_rgb_uchar(0, 0, 1 << 3);
//	b[4] = DCT_color_index_form_rgb_uchar(0, 0, 1 << 4);
//	b[5] = DCT_color_index_form_rgb_uchar(0, 0, 1 << 5);
//	b[6] = DCT_color_index_form_rgb_uchar(0, 0, 1 << 6);
//	b[7] = DCT_color_index_form_rgb_uchar(0, 0, 1 << 7);
//
//	return 0;
//}


int main(int argc, char *argv[])
{

	DCT_color_table_helper test;

	std::cout << std::endl;
	std::cout << "table size (elements):"<< test.mapping_cache.size();
	std::cout << std::endl;

	std::cout << "table elements size (bytes):" << sizeof(DCT_color_mapping_element);
	std::cout << std::endl;

	return 0;
}