/*
标准颜色表的处理方法。
1，标准颜色表排序，去掉重复。
2，根据颜色通道，稳定排序，得到3个表，分别是color_table_by_red和另外2个名字。
3，分通道，把0到255的颜色所需要考虑的颜色记录到新的3个表里面，分别是red_table和另外2个名字。
代码里面，是根据前面的color_table_by_red进行遍历，而不是for i=0 i<256这样。
4，清理不用的表，color_table_by_red和其他2个。其实不大，也就无所谓了。
5，使用DCT_color_index作为索引，遍历整个rgb888的所有颜色，将他们的连续段的信息记录到最终的查询表里面。最终的表叫做mapping_cache。

此外，最终的查询表里面，第一个元素是重复的，不管他，不影响结果。
*/










#pragma once

#include<iostream>
#include<algorithm>
#include <ctime>

#include"colour table data.h"
#include"DCT color index form.h"



class DCT_color_table_helper
{
public:
	const colour_table_data_class* source_data;
	std::vector<DCT_color_with_distance_calc> color_table_by_red;
	std::vector<DCT_color_with_distance_calc> color_table_by_green;
	std::vector<DCT_color_with_distance_calc> color_table_by_blue;
	std::vector < std::vector<DCT_color_with_distance_calc>> red_table;
	std::vector < std::vector<DCT_color_with_distance_calc>> green_table;
	std::vector < std::vector<DCT_color_with_distance_calc>> blue_table;
	
	std::vector<DCT_color_mapping_element> mapping_cache;


//ctor dtor
public:
	DCT_color_table_helper()
	{
		source_data = &colour_table_data_2020sep15;


		//copies data
		color_table_by_red.resize(source_data->data.size());
		color_table_by_green.resize(source_data->data.size());
		color_table_by_blue.resize(source_data->data.size());
		std::copy(source_data->data.begin(), source_data->data.end(), color_table_by_red.begin());
		std::copy(source_data->data.begin(), source_data->data.end(), color_table_by_green.begin());
		std::copy(source_data->data.begin(), source_data->data.end(), color_table_by_blue.begin());

		//sorting.
		std::stable_sort(color_table_by_red.begin(), color_table_by_red.end(), less_by_red());
		std::stable_sort(color_table_by_green.begin(), color_table_by_green.end(), less_by_green());
		std::stable_sort(color_table_by_blue.begin(), color_table_by_blue.end(), less_by_blue());

		//The red table. Actually dictionary by red channel.
		red_table.resize(256);
		{
			auto __temp_pair =
				std::equal_range(color_table_by_red.begin(), color_table_by_red.end(),
					color_table_by_red.front(), less_by_red());
			std::vector<DCT_color_with_distance_calc>::iterator small_begin(__temp_pair.first);
			std::vector<DCT_color_with_distance_calc>::iterator small_end(__temp_pair.second);

			if (color_table_by_red.end() == small_end)
			{
				for (size_t i = 0; i < 256; i++)
				{
					red_table[i].resize(color_table_by_red.size());
					std::copy(color_table_by_red.begin(), color_table_by_red.end(), red_table[i].begin());
				}
			}
			else
			{
				__temp_pair =
					std::equal_range(color_table_by_red.begin(), color_table_by_red.end(),
						*(small_end), less_by_red());
				std::vector<DCT_color_with_distance_calc>::iterator big_begin(__temp_pair.first);
				std::vector<DCT_color_with_distance_calc>::iterator big_end(__temp_pair.second);

				int min_of_red = color_table_by_red.front().red();
				for (int i = 0; i <= min_of_red; ++i)
				{
					red_table[i].resize(std::distance(small_begin, small_end));
					std::copy(small_begin, small_end, red_table[i].begin());
				}

				int count_small;
				int count_big;
				while (big_end != color_table_by_red.end())
				{
					count_small = std::distance(small_begin, small_end);
					count_big = std::distance(big_begin, big_end);
					//*small+1 to *big-1
					size_t red_channel_of_small = (*small_begin).red();
					size_t red_channel_of_big = (*big_begin).red();
					for (size_t i = red_channel_of_small + 1; i < red_channel_of_big; i++)
					{
						red_table[i].resize(count_small + count_big);
						auto pos = std::copy(small_begin, small_end, red_table[i].begin());
						std::copy(big_begin, big_end, pos);
					}

					//big  itself
					red_table[red_channel_of_big].resize(count_big);
					std::copy(big_begin, big_end, red_table[red_channel_of_big].begin());

					//finds the next thing to process
					small_begin = big_begin;
					small_end = big_end;

					auto __temp_pair =
						std::equal_range(color_table_by_red.begin(), color_table_by_red.end(),
							*(small_end), less_by_red());
					big_begin = __temp_pair.first;
					big_end = __temp_pair.second;
				}

				int max_of_red = (*big_begin).red();
				count_big = std::distance(big_begin, big_end);
				for (size_t i = max_of_red; i < 256; ++i)
				{//If any original colour table has a red channel of 255, this for loop is simply ignored.
					red_table[i].resize(count_big);
					std::copy(big_begin, big_end, red_table[i].begin());
				}
			}
		}//The red table. Actually dictionary by red channel. //scope

		//The green table. Actually dictionary by green channel.
		green_table.resize(256);
		{
			auto __temp_pair =
				std::equal_range(color_table_by_green.begin(), color_table_by_green.end(),
					color_table_by_green.front(), less_by_green());
			std::vector<DCT_color_with_distance_calc>::iterator small_begin(__temp_pair.first);
			std::vector<DCT_color_with_distance_calc>::iterator small_end(__temp_pair.second);
		
			if (color_table_by_green.end() == small_end)
			{
				for (size_t i = 0; i < 256; i++)
				{
					green_table[i].resize(color_table_by_green.size());
					std::copy(color_table_by_green.begin(), color_table_by_green.end(), green_table[i].begin());
				}
			}
			else
			{
				__temp_pair =
					std::equal_range(color_table_by_green.begin(), color_table_by_green.end(),
						*(small_end), less_by_green());
				std::vector<DCT_color_with_distance_calc>::iterator big_begin(__temp_pair.first);
				std::vector<DCT_color_with_distance_calc>::iterator big_end(__temp_pair.second);

				int min_of_green = color_table_by_green.front().green();
				for (int i = 0; i <= min_of_green; ++i)
				{
					green_table[i].resize(std::distance(small_begin, small_end));
					std::copy(small_begin, small_end, green_table[i].begin());
				}

				int count_small;
				int count_big;
				while (big_end != color_table_by_green.end())
				{
					count_small = std::distance(small_begin, small_end);
					count_big = std::distance(big_begin, big_end);
					//*small+1 to *big-1
					size_t green_channel_of_small = (*small_begin).green();
					size_t green_channel_of_big = (*big_begin).green();
					for (size_t i = green_channel_of_small + 1; i < green_channel_of_big; i++)
					{
						green_table[i].resize(count_small + count_big);
						auto pos = std::copy(small_begin, small_end, green_table[i].begin());
						std::copy(big_begin, big_end, pos);
					}

					//big  itself
					green_table[green_channel_of_big].resize(count_big);
					std::copy(big_begin, big_end, green_table[green_channel_of_big].begin());

					//finds the next thing to process
					small_begin = big_begin;
					small_end = big_end;

					auto __temp_pair =
						std::equal_range(color_table_by_green.begin(), color_table_by_green.end(),
							*(small_end), less_by_green());
					big_begin = __temp_pair.first;
					big_end = __temp_pair.second;
				}

				int max_of_green = (*big_begin).green();
				count_big = std::distance(big_begin, big_end);
				for (size_t i = max_of_green; i < 256; ++i)
				{//If any original colour table has a green channel of 255, this for loop is simply ignored.
					green_table[i].resize(count_big);
					std::copy(big_begin, big_end, green_table[i].begin());
				}
			}
		}//The green table. Actually dictionary by green channel. //scope

		//The blue table. Actually dictionary by blue channel.
		blue_table.resize(256);
		{
			auto __temp_pair =
				std::equal_range(color_table_by_blue.begin(), color_table_by_blue.end(),
					color_table_by_blue.front(), less_by_blue());
			std::vector<DCT_color_with_distance_calc>::iterator small_begin(__temp_pair.first);
			std::vector<DCT_color_with_distance_calc>::iterator small_end(__temp_pair.second);

			if (color_table_by_blue.end() == small_end)
			{
				for (size_t i = 0; i < 256; i++)
				{
					blue_table[i].resize(color_table_by_blue.size());
					std::copy(color_table_by_blue.begin(), color_table_by_blue.end(), blue_table[i].begin());
				}
			}
			else
			{
				__temp_pair =
					std::equal_range(color_table_by_blue.begin(), color_table_by_blue.end(),
						*(small_end), less_by_blue());
				std::vector<DCT_color_with_distance_calc>::iterator big_begin(__temp_pair.first);
				std::vector<DCT_color_with_distance_calc>::iterator big_end(__temp_pair.second);

				int min_of_blue = color_table_by_blue.front().blue();
				for (int i = 0; i <= min_of_blue; ++i)
				{
					blue_table[i].resize(std::distance(small_begin, small_end));
					std::copy(small_begin, small_end, blue_table[i].begin());
				}

				int count_small;
				int count_big;
				while (big_end != color_table_by_blue.end())
				{
					count_small = std::distance(small_begin, small_end);
					count_big = std::distance(big_begin, big_end);
					//*small+1 to *big-1
					size_t blue_channel_of_small = (*small_begin).blue();
					size_t blue_channel_of_big = (*big_begin).blue();
					for (size_t i = blue_channel_of_small + 1; i < blue_channel_of_big; i++)
					{
						blue_table[i].resize(count_small + count_big);
						auto pos = std::copy(small_begin, small_end, blue_table[i].begin());
						std::copy(big_begin, big_end, pos);
					}

					//big  itself
					blue_table[blue_channel_of_big].resize(count_big);
					std::copy(big_begin, big_end, blue_table[blue_channel_of_big].begin());

					//finds the next thing to process
					small_begin = big_begin;
					small_end = big_end;

					auto __temp_pair =
						std::equal_range(color_table_by_blue.begin(), color_table_by_blue.end(),
							*(small_end), less_by_blue());
					big_begin = __temp_pair.first;
					big_end = __temp_pair.second;
				}

				int max_of_blue = (*big_begin).blue();
				count_big = std::distance(big_begin, big_end);
				for (size_t i = max_of_blue; i < 256; ++i)
				{//If any original colour table has a blue channel of 255, this for loop is simply ignored.
					blue_table[i].resize(count_big);
					std::copy(big_begin, big_end, blue_table[i].begin());
				}
			}
		}//The blue table. Actually dictionary by blue channel. //scope


		//OK, now the tables by channel are ready. Time for the answer table.
		//answer table is organized by the customized index, rather than normal rgb form int.

		if (0)
		{
			color_table_by_red.clear();
			color_table_by_green.clear();
			color_table_by_blue.clear();
		}

#ifdef _DEBUG
		//调试

		//calc_the_answer(DCT_color_index(0), DCT_color_with_distance_calc(0, 0, 0));
		//calc_the_answer(DCT_color_index(1), DCT_color_with_distance_calc(0, 0, 0));
		//这两个可能已经正常了。但是应该还不够，还要多测试几个。
		
		
#endif // _DEBUG

		//Now it's time for the final table, the dictinary.
		int greater_eq = 0;

		DCT_color_with_distance_calc last_answer = calc_the_answer(0, DCT_color_with_distance_calc(255, 255, 255));
		
		//This pushing_back makes the table with a repeated first element. But it doesn't matter.
		mapping_cache.push_back(DCT_color_mapping_element(DCT_color_index(0), last_answer));


		DCT_color_with_distance_calc answer_of_neighbour = last_answer;

		//A giant loop. Not for the first one, neither for the last one.
		//const int __bit_mask(0b100100100100100100100);//To be honest, I didn't expected to invent this. Looks good. 
		DCT_color_index neighbour_index;

#ifdef _DEBUG
		for (int color_index = 1; color_index < (1 << 14); color_index += 1)
#else
		for (int color_index = 1; color_index < (1 << 24); color_index += 1)
#endif // _DEBUG
		{
			//from 1 rathan 0. The code for 0 is spicial and before this for loop.

			DCT_color_index temp_index(color_index);
			neighbour_index = temp_index.neighbour_with_less_index();

			//step 2 finds out the answer of neighbour.
			
			//For all the indec less than the index being processed now, they are all logically saved into the dictionary system.
			//The first element in the final table is repeated, so this invoking is safe.
			answer_of_neighbour = find_answer(neighbour_index);
			DCT_color_with_distance_calc answer = calc_the_answer(color_index, answer_of_neighbour);

			//step 3 save the info into the final dictionary system(mapping_cache).
			if (answer == last_answer)
			{
				continue;
			}
			else//>>> (answer != last_answer)
			{
				mapping_cache.push_back(DCT_color_mapping_element(greater_eq, last_answer));
				last_answer = answer;
				greater_eq = color_index;
			}
		}//for color_index = 1;  < (1 << 24)

		//Finally the last one.
		mapping_cache.push_back(DCT_color_mapping_element(greater_eq, last_answer));
		
		//In this way, mapping_cache is already sorted.

		std::cout << "Before validation" << std::endl;

#ifdef _DEBUG
//Validates the whole algorithm.
#endif // _DEBUG
		__validation();
	


	}//end of this looooong ctor



private:
	DCT_color_with_distance_calc calc_the_answer(const DCT_color_index& in_question, const DCT_color_with_distance_calc& answer_of_neighbour)
	{
		DCT_color_with_distance_calc q(in_question.to_color());
		if (q == answer_of_neighbour)
		{
			return answer_of_neighbour;//If the neighbour is the answer, return it.
		}

		int min_distance(q.distance(answer_of_neighbour));//actually the possible max is less than 3x255x255, which is less than 0x30000
		DCT_color_with_distance_calc answer(answer_of_neighbour);//The first time of comparing is destined to modify this. So init value doesn't effect anything.

		std::vector < std::vector<DCT_color_with_distance_calc>>::iterator iter;
		int temp_distance;

		//step 1, find out the best among recommended elements according to the red_table green_table and blue_table.
		iter = red_table.begin()+q.red();
		for(DCT_color_with_distance_calc& element:(*iter))
		{
			if (q == element)
			{
				return element;//Specialized return timing if it gets the answer.
			}
			temp_distance = q.distance(element);
			if (temp_distance < min_distance)
			{
				min_distance = temp_distance;
				answer = element;
			}
		}

		//If the program gets to this point, it means the r of the real answer is not possible to equal to the r of "question". Or the red_table is wrong. If that happens, then all the other tables are very likely to be wrong.

		iter = green_table.begin() + q.green();
		for (DCT_color_with_distance_calc& element : (*iter))
		{
			temp_distance = q.distance(element);
			if (temp_distance < min_distance)
			{
				min_distance = temp_distance;
				answer = element;
			}
		}
		iter = blue_table.begin() + q.blue();
		for (DCT_color_with_distance_calc& element : (*iter))
		{
			temp_distance = q.distance(element);
			if (temp_distance < min_distance)
			{
				min_distance = temp_distance;
				answer = element;
			}
		}

		//step 2 
		//std::vector<DCT_color_with_distance_calc> candidate;
		{
			int temp_channel;
			temp_channel = static_cast<int>(q.red()); 
			temp_channel -= min_distance;
			temp_channel = std::max(0, temp_channel);
			std::vector<DCT_color_with_distance_calc>::iterator step_1_from =
				std::lower_bound(color_table_by_red.begin(), color_table_by_red.end(),
					DCT_color_with_distance_calc(temp_channel, 0, 0),
					less_by_red());

			temp_channel = static_cast<int>(q.red());
			temp_channel += min_distance;
			temp_channel = std::min(255, temp_channel);
			std::vector<DCT_color_with_distance_calc>::iterator step_1_to =
				std::upper_bound(color_table_by_red.begin(), color_table_by_red.end(),
					DCT_color_with_distance_calc(temp_channel, 0, 0),
					less_by_red());
			
			temp_channel = static_cast<int>(q.green());
			temp_channel -= min_distance;
			temp_channel = std::max(0, temp_channel);
			std::vector<DCT_color_with_distance_calc>::iterator step_2_from =
				std::lower_bound(step_1_from, step_1_to, 
					DCT_color_with_distance_calc(0, temp_channel, 0),
					less_by_green());

			temp_channel = static_cast<int>(q.green());
			temp_channel += min_distance;
			temp_channel = std::min(255, temp_channel);
			std::vector<DCT_color_with_distance_calc>::iterator step_2_to =
				std::upper_bound(step_1_to, step_1_to, 
					DCT_color_with_distance_calc(0, temp_channel, 0),
					less_by_green());

			temp_channel = static_cast<int>(q.blue());
			temp_channel -= min_distance;
			temp_channel = std::max(0, temp_channel);
			std::vector<DCT_color_with_distance_calc>::iterator step_3_from =
				std::lower_bound(step_2_from, step_1_to, 
					DCT_color_with_distance_calc(0, 0, temp_channel),
					less_by_blue());

			temp_channel = static_cast<int>(q.blue());
			temp_channel += min_distance;
			temp_channel = std::min(255, temp_channel);
			std::vector<DCT_color_with_distance_calc>::iterator step_3_to =
				std::upper_bound(step_2_to, step_1_to, 
					DCT_color_with_distance_calc(0, 0, temp_channel),
					less_by_blue());
			for (std::vector<DCT_color_with_distance_calc>::iterator i = step_3_from; i < step_3_to; i++)
			{
				temp_distance = q.distance(*i);
				if (temp_distance < min_distance)
				{
					min_distance = temp_distance;
					answer = *i;
				}
			}
		}

		return answer;
	}//end of function find_the_answer
public:
	inline DCT_color_with_distance_calc find_answer(const DCT_color_index& in)
	{
		DCT_color_mapping_element pseudo_element(in, DCT_color_with_distance_calc(0, 0, 0));
		std::vector<DCT_color_mapping_element>::iterator iter = std::upper_bound(mapping_cache.begin(), mapping_cache.end(), pseudo_element);
		//You have to handle the first index( which is always 0) manually. For the case of 0, you don't need this function at all.
		--iter;
		return iter->answer;
		//return DCT_color_with_distance_calc();
	}


	void __validation()
	{
		size_t validation_count = 10000000;

	
		struct error_list_struct
		{
			error_list_struct(const DCT_color_with_distance_calc& in_question, const DCT_color_with_distance_calc& in_answer_from_table, const DCT_color_with_distance_calc& in_stable_answer) :question(in_question), answer_from_table(in_answer_from_table), stable_answer(in_stable_answer) {};
			DCT_color_with_distance_calc question;
			DCT_color_with_distance_calc answer_from_table;
			DCT_color_with_distance_calc stable_answer;
		};
		int correction_count(0);
		std::vector<error_list_struct> error_list;
			
		//std::srand(std::time(nullptr));
		const std::vector<DCT_color_with_distance_calc>* source_color_table = &(source_data->data);

		for (size_t validation_i = 0; validation_i < validation_count; validation_i++)
		{
#ifdef _DEBUG
			DCT_color_index question_index(std::rand()%(1<<14));
#else
			DCT_color_index question_index(std::rand()| ((std::rand()&0b111111111)<<9));
#endif // _DEBUG

			DCT_color_with_distance_calc question_color (question_index.to_color());

			DCT_color_with_distance_calc answer_from_table = find_answer(question_index);
			
			int min_dist(0xffffff);
			int temp_dist;
			int temp_best_i;
			size_t i = 0;
			for (; i < source_color_table->size(); ++i)
			{
				temp_dist = question_color.distance((*source_color_table)[i]);
				if (0 == temp_dist)
				{
					temp_best_i = i;
					break;
				}
				if (temp_dist < min_dist)
				{
					min_dist = temp_dist;
					temp_best_i = i;
				}
			}

			DCT_color_with_distance_calc stable_answer = (*source_color_table)[temp_best_i];
			if (question_color.distance(answer_from_table) == question_color.distance(stable_answer))
			{
				++correction_count;
			}
			else// >>> 2 distances DON'T equal.
			{
				error_list.push_back(error_list_struct(question_color, answer_from_table, stable_answer));
			}
		}
		
		// Outputs the validation result.
		std::cout << "Error list:" <<std::endl;
		for (size_t error_i = 0; error_i < error_list.size(); error_i++)
		{
			std::cout << "Q:              " << error_list[error_i].question.rgb << std::endl;
			std::cout << "Stable answer:  " << std::hex << error_list[error_i].stable_answer.rgb 
				<< "  dist:  " << std::dec << error_list[error_i].question .distance(error_list[error_i].stable_answer )
				<< std::endl;
			std::cout << "My answer:      " << std::hex << error_list[error_i].answer_from_table.rgb 
				<< "  dist:  " << std::dec << error_list[error_i].question.distance(error_list[error_i].answer_from_table)
				<<std::endl;
			
		}
		std::cout << std::dec;

		std::cout << "Tested " << validation_count << " times." << std::endl;
		std::cout << "Error " << error_list.size() << "" << std::endl;
		std::cout << "Correction ratio " << static_cast<float>(error_list.size())/ validation_count << "" << std::endl;

		return;
	}//void __validation()




	//inner util.
//private:
//	bool less_function(unsigned char lhs, unsigned char rhs)
//	{
//
//
//		return fjdklsj
//	}
//	//main function
//public:
//	int get_closest_color_index(const DCT_color_rgb_uchar_with_distance_calc& in)
//	{
//		std::binary_search(by_red.begin(), by_red.end(), in.r, less_function);//不对
//		
//
//
//
//
//
//	}


};



